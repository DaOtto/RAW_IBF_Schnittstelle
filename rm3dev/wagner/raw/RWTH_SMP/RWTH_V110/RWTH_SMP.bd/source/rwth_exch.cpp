/*--FILE HEADER---------------------------------------------------------------
;   filename        : rwth_exch.cpp
;   version         : V1.01
;   contents        : Data transfer from CNC to TRT to RWTH and back
;   author          : K. Brauckmann, SMS Eumuco GmbH
;   date            : May, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   Datenstrukturen aus und in den globalen
;               Speicherpool kopieren
;
;       RMOS3 Version 3.30
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   May , 10. 2006  0001  K.B.  original issue
;   Jan , 15. 2015  0002  D.O.  aenderung der Initialisierung der IBF-Parameter
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
/****************************************************************************/
/*  includes                                                                */
/****************************************************************************/
/* includes from outside the project */

#include "rmos_inc.h"
#include "time.h"

#define Powercon_Modul	//muss in allen drei Projekten (RAW_SMP, TRT_SMP und
						//RWTH_SMP) genau einmal definiert werden!

/* declarations from inside the project */
#include "rwth_task.hpp"
#include "ibf_tool.hpp"

/****************************************************************************/
// Konstruktor
/****************************************************************************/
RWTH_EXCH::RWTH_EXCH(void)
{

	time_t start, end;
	
	ctime(&start);   // Starten des Timers mit dem die Zeit eines Funktionsaufrufes gemessen werden kann.

	// Initialisierung der IBF-Strukturen

	Def_Ist_Inter			II_null = {};
	Def_Soll_Inter			SI_null = {};
	Def_IBF_Allgemein_SOLL	SIBF_null = {};
	Def_IBF_Allgemein_IST	IIBF_null = {};

	Ist_Inter_Ini	= II_null;
	Soll_Inter_Ini	= SI_null;
	Ist_IBF_Ini		= IIBF_null;
	Soll_IBF_Ini	= SIBF_null;

	Soll_IBF_Ini.Profilflag = -1;

	Soll_IBF_Ini.InitAchse = 'a';
	Soll_IBF_Ini.ExitAchse = 'a';
	Soll_IBF_Ini.Zeit.t_Halte = 20;    // Sollwartezeit beim Anfahren
	Soll_IBF_Ini.stuetz_var.skip_faktor = 1;	// IBF-Stuetzstelle
	Soll_IBF_Ini.stuetz_var.merker = 0;			// IBF-Stuetzstelle
	Soll_IBF_Ini.stuetz_var.crtimer = 0;		// IBF-Stuetzstelle

	Ist_IBF_Ini.Axial.Kr_geo.sin_kw_winkel_halbe = 0.3826834323650897717284599840304F;  // sin(22.5)  
	
	//-------------------------------------------------------------------------------
	//----- Einlesen der IBF_Data.ini (entspricht der ipfpara auf dem MRAW)     -----
	//----- Datei liegt in dem smp16-Verzeichnis auf dem Windowsrechner         -----
	//----- und wird von der Sicomp-Einheit bei jedem Reset geladen.            -----
	//----- Ini-Datei darf nicht veraendert werden, ohne dass diese Aenderungen -----
	//----- hier im Quelltext uebernommen werden!                               -----
	//-------------------------------------------------------------------------------
	MyLogFile << "Gleich soll IBF_Data geoeffnet werden...." << endl;
	if (!rpw->IBFPARA_auslesen(Ist_IBF_Ini, Soll_IBF_Ini, Ist_Inter_Ini))
	{
		MyLogFile << "konnte IBF_Data nicht oeffnen" << endl;
	}
	else
	{
		MyLogFile << "konnte IBF_Data oeffnen" << endl;
	}

	ctime(&end);   // Stoppen des Timers, mit dem die Zeit eines Funktionsaufrufes gemessen wurde

	Ist_Inter_Ini.Systemzeit = difftime(end, start);    // Zeitdifferenz berechnen. Angabe in Sekunden

	// Funktionsaufrufe: hier IBF-Modul Flexibel axiales Profilieren (Funktionen stehen in der ibf_tool.cpp)

	rpw->Kr_Geo_berechnen(Ist_IBF_Ini);
	rpw->Kr_Geo_pruefen(Ist_IBF_Ini);

	// Funktionsaufrufe: Modus des Axialgeruestes
	rpw->Modus_AG(Soll_Inter_Ini, Ist_IBF_Ini, Ist_IBF_Ini.Flag.Axial_Radialwalzen);

	// Modus der Druckrollen /D.O. 20.4.2015/
	rpw->Modus_DR( Soll_IBF_Ini , Ist_IBF_Ini );

	if ((Ist_IBF_Ini.Flag.Axial_Radialwalzen == 1)||(Ist_IBF_Ini.Flag.Axial_Radialwalzen == 2))// Radialprof. od Formenspek.
	{
		Soll_IBF_Ini.min_RS_Pos  = 10.0F; // minimale Wanddickeposition, die erreicht werden darf. Wert ist von Carwin-Vorgabe unabhaengig
		Soll_IBF_Ini.min_ASO_Pos = 85.0F; // min. Ringhoehe, wenn mit Tastrollenerhoehung gearbeitet wird  ||107.0F -> Radialprofilieren Aufsatz 1
	}
	else
		Soll_IBF_Ini.min_ASO_Pos = 25.0F;

	Ist_IBF_Ini.Axial.Biss.Anzahl_zweite_Ebene = Ist_IBF_Ini.Axial.Biss.Anzahl + Ist_IBF_Ini.Axial.Biss.Anzahl;

	MyLogFile << "Allgemeine Information" << endl;
	MyLogFile << "System hat " << Ist_Inter_Ini.Systemzeit * 1000.0 << " Sekunden benoetigt, um Datei einzulesen" << endl;
	MyLogFile << "Minimale IBF-Wandposition (kann von der CARWIN-Wanddicke abweichen) " << Soll_IBF_Ini.min_RS_Pos << endl;
	MyLogFile << "Minimale Ringhoehe                                                   " << Soll_IBF_Ini.min_ASO_Pos << endl;
	MyLogFile << endl;
	MyLogFile << endl;
	
	// Walzstrategie

	MyLogFile << "Gewaehlte Walzstrategie :  " << Ist_IBF_Ini.Flag.Axial_Radialwalzen << endl << endl;
	//Kontrolle der eingelesenen IBF-Werte in LoggerFile

	MyLogFile << "Folgende Werte wurden aus IBF_Data gelesen und wie folgt zugeordnet" << endl;
	MyLogFile << endl;

	MyLogFile << "Abschalten nach SMS (0) oder IBF (1)" << ":" << " " << Ist_IBF_Ini.Flag.IBF_Abschaltung << endl;
	MyLogFile << endl;
	MyLogFile << "Weg-Kraftschalter RS aktiv  [1=ja, 0=nein]" << ":" << " " << Ist_IBF_Ini.Flag.rs_kraftregler_aktiv <<	endl;
	MyLogFile << "Weg-Kraftschalter AS aktiv  [1=ja, 0=nein]" << ":" << " " << Ist_IBF_Ini.Flag.as_kraftregler_aktiv <<	endl;
	MyLogFile << "Weg-Kraftschalter AG aktiv  [1=ja, 0=nein]" << ":" << " " << Ist_IBF_Ini.Flag.ag_kraftregler_aktiv <<	endl;
	MyLogFile << "Weg-Kraftschalter ZAL aktiv [1=ja, 0=nein]" << ":" << " " << Ist_IBF_Ini.Flag.zal_kraftregler_aktiv << endl;
	MyLogFile << "Weg-Kraftschalter ZAR aktiv [1=ja, 0=nein]" << ":" << " " << Ist_IBF_Ini.Flag.zar_kraftregler_aktiv << endl;
	MyLogFile << endl;

	MyLogFile << "RS_Kraftvorgabe " << "= " << " " << Soll_IBF_Ini.RS_Kraft_Vorgabe << " N" << endl;
	MyLogFile << "AS_Kraftvorgabe " << "= " << " " << Soll_IBF_Ini.AS_Kraft_Vorgabe << " N" << endl;
	MyLogFile << "AG_Kraftvorgabe " << "= " << " " << Soll_IBF_Ini.AG_Kraft_Vorgabe << " N" << endl;
	MyLogFile << "ZAL_Kraftvorgabe" << "= " << " " << Soll_IBF_Ini.ZAL_Kraft_Vorgabe << " N" << endl;
	MyLogFile << "ZAR_Kraftvorgabe" << "= " << " " << Soll_IBF_Ini.ZAR_Kraft_Vorgabe << " N" << endl;
	MyLogFile << endl;
	MyLogFile << endl;

	MyLogFile << "Anwalzen in Kraft" << endl;

	// Schalter: Walzen mit Kraftsteuerung [1], Positionssteuereung [0]
	MyLogFile << "Dornwalze in Kraft beim Anwalzen [1=AN, 0=AUS]" << ":" << " " << Ist_IBF_Ini.Flag.rs_kraftanfahren_aktiv << endl;
	if (Ist_IBF_Ini.Flag.rs_kraftanfahren_aktiv == 0)
		MyLogFile << "Radiales Anwalzen in Kraft wurde nicht vorgewaehlt " << endl;
	else
		MyLogFile << "Radiales Anwalzen mit der Kraft FR" << "= " << " " << Soll_IBF_Ini.RS_Kraft_Anfahren << " vorgewaehlt" << endl;

	MyLogFile << endl;

	MyLogFile << "Kegelwalze in Kraft beim Anwalzen [1=AN, 0=AUS]" << ":" << " " << Ist_IBF_Ini.Flag.as_kraftanfahren_aktiv << endl;
	if (Ist_IBF_Ini.Flag.as_kraftanfahren_aktiv == 0)
		MyLogFile << "Axiales Anwalzen in Kraft wurde nicht vorgewaehlt" << endl;
	else
		MyLogFile << "Axiales Anwalzen mit der Kraft FA" << "= " << " " << Soll_IBF_Ini.AS_Kraft_Anfahren << " vorgewaehlt" << endl;

	MyLogFile << endl << endl << endl;
	
	MyLogFile << "Auswahl des IBF-Modul:";
	if (Ist_IBF_Ini.Flag.Axial_Radialwalzen == 1)
	{
		MyLogFile << "***IBF - Flexibel radial Profilieren***" << endl;

		MyLogFile << "Vorschubsart " << ": ";
		switch (Ist_IBF_Ini.Radial.Schalter_Kont_DisKo)
		{

		case 0:
			MyLogFile << "const. Vorschub (Schalterstellung = 0)" << endl;
			break;
		case 1:
			MyLogFile << "Epsilon/Weg (Schalterstellung = 1) " << endl;
			MyLogFile << "Vorgabe des Epsilon " << "= " << Soll_IBF_Ini.Radial.eps_Vorschub << endl;
			break;
		case 2:
			MyLogFile << "Walzspaltverhaelnis (Schalterstellung = 2)" << endl;
			MyLogFile << "Fuer Cr wurde " << Soll_IBF_Ini.Radial.Walzspalt_Cr << " vorgegeben " << endl;
			break;
		}

		MyLogFile << endl;

		MyLogFile << "Profilierwerkzeugbreite       " << "= " << Ist_IBF_Ini.Radial.Werkzeugbreite << endl;
		MyLogFile << "const.Vorschubgeschwindigkeit " << "= " << Soll_IBF_Ini.Radial.Vorschubgeschw_Dw << endl;
		if (Soll_IBF_Ini.Radial.delta_s != 0.0F && Soll_IBF_Ini.Radial.Stegstaerke != 0.0F)
		{
			MyLogFile << endl;
			MyLogFile << "ACHTUNG !!!  Vorgabe von Soll-Stegstaerke und Delta_s unzulaessig! " <<	"=> Delta_s wurde Null gesetzt " << endl;
			Soll_IBF_Ini.Radial.delta_s = 0.0;

			MyLogFile << "Soll-Stegstaerke              " << "= " << Soll_IBF_Ini.Radial.Stegstaerke << endl;
			MyLogFile << "Delta_s                       " << "= " << Soll_IBF_Ini.Radial.delta_s << endl;
			MyLogFile << endl;
		}

		else if (Soll_IBF_Ini.Radial.delta_s == 0.0F && Soll_IBF_Ini.Radial.Stegstaerke == 0.0F)
		{
			MyLogFile << endl;
			MyLogFile << "ACHTUNG !!!  Soll-Stegstaerke und Delta_s beide NULL ist unzulaessig! " << endl;
			Soll_IBF_Ini.Radial.delta_s = 0.0;
			Soll_IBF_Ini.Radial.Stegstaerke = 40.0F;

			MyLogFile << "Soll-Stegstaerke (DEFAULT-Wert)" << "= " << Soll_IBF_Ini.Radial.Stegstaerke << endl;
			MyLogFile << "Delta_s                        " << "= " << Soll_IBF_Ini.Radial.delta_s << endl;
			MyLogFile << endl;
		}
		else
		{
			MyLogFile << "Soll-Stegstaerke               " << "= " << Soll_IBF_Ini.Radial.Stegstaerke << endl;
			MyLogFile << "Delta_s                        " << "= " << Soll_IBF_Ini.Radial.delta_s << endl;
		}

		MyLogFile << endl;
		MyLogFile << endl;
		MyLogFile << "Anzahl der Umdrehungen in der Rundungsphase" << "= " << Soll_IBF_Ini.Radial.Umdrehungen << endl;
		MyLogFile << endl;
		MyLogFile << "Rohlingshoehe" << "= " << Soll_IBF_Ini.Radial.Rohlinghoehe << endl;
		MyLogFile << endl;
		MyLogFile << "Vorschubgeschwindigkeit Axialschlitten (nur im case 17)" << "= " << Soll_IBF_Ini.Radial.Vorschubgeschw_ASO << endl;
		MyLogFile << endl;
	} //endif (Ist_IBF_Ini.Flag.Axial_Radialwalzen != 0)

	else if (Ist_IBF_Ini.Flag.Axial_Radialwalzen == 0)
	{
		MyLogFile << "***IBF - Flexibel axial Profilieren***" << endl;

		MyLogFile << " Kragenbreite                                " << "= " << Ist_IBF_Ini.Axial.Kr_geo.Kr_Br << endl;
		MyLogFile << " Kragendurchmesser vordere Kante             " << "= " << Ist_IBF_Ini.Axial.Kr_geo.Kr_d_nenn_vorne <<	endl;
		MyLogFile << " berechneter Nenndurchmesser Kragenmittelpkt." << "= " << Ist_IBF_Ini.Axial.Kr_geo.Kr_d_nenn_mitte <<	endl;
		MyLogFile << " Kragendurchmesser vordere Kante             " << "= " << Ist_IBF_Ini.Axial.Kr_geo.Kr_d_nenn_hinten << endl;
		MyLogFile << " berechneter Abstand Del_Kr_Br               " << "= " << Ist_IBF_Ini.Axial.Kr_geo.Del_Kr_AGR << endl;
		MyLogFile << " max. Profilierungstiefe                     " << "= " << Ist_IBF_Ini.Axial.Kr_geo.max_Pr_Tiefe << endl;
		MyLogFile << " Anfahrdurchmesser                           " << "= " << Ist_IBF_Ini.Axial.Anfahrdurchm << endl;
		MyLogFile << " Zustellgeschwindigkeit des Axialschlittens  " << "= " << Ist_IBF_Ini.Axial.Vorschub << " [mm/U]" << endl;

		MyLogFile << " Anzahl der Profile                          " << "= " << Ist_IBF_Ini.Axial.Profilanzahl << endl;
		for (int i = 0; i < Ist_IBF_Ini.Axial.Profilanzahl; i++)
		{
			MyLogFile << i + 1 << ". Profilierposition                   " << "= " << Ist_IBF_Ini.Axial.AGR_Pr[i] << endl;
			MyLogFile << i + 1 << ". Profiliertiefe                      " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[i] << endl;
		}
		MyLogFile << endl;
		MyLogFile << " Minimale Walzhoehe ist vorgegeben mit" << "= " << Soll_IBF_Ini.min_ASO_Pos << endl;
		MyLogFile << " Soll_Inter.ag_mode" << "= " << Soll_Inter_Ini.ag_mode << endl;
	}

	if (Ist_IBF_Ini.Axial.Turbine.Turbinenscheibe == 1)
	{
		MyLogFile << "Strategie Turbinenscheibe vorgewaehlt" << endl;
		MyLogFile << endl;
		if (Ist_IBF_Ini.Flag.Bissverhaeltnis == 1)
		{
			MyLogFile << "Pro Ebene werden " << Ist_IBF_Ini.Axial.Biss.Anzahl << " Bisse mit dem Versatz von je  " << Ist_IBF_Ini.Axial.Biss.Verhaeltnis << "  Prozent gemacht" << endl;
			MyLogFile << " Insgesamt werden " << Ist_IBF_Ini.Axial.Biss.Anzahl_zweite_Ebene << " Bisse gewalzt" << endl;
			MyLogFile << endl;
			MyLogFile << "1. Profiltiefe (1. Ebene 1. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[0] << endl;
			MyLogFile << "2. Profiltiefe (1. Ebene 2. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[1] << endl;
			MyLogFile << "3. Profiltiefe (1. Ebene 3. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[2] << endl;
			MyLogFile << endl;
			MyLogFile << "4. Profiliertiefe (2. Ebene 1. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[3] << endl;
			MyLogFile << "5. Profiliertiefe (2. Ebene 2. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[4] << endl;
			MyLogFile << "6. Profiliertiefe (2. Ebene 3. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[5] << endl;
			MyLogFile << endl;
			MyLogFile << "1. Profilierposition 1. Ebene                      " << "= " << Ist_IBF_Ini.Axial.AGR_Pr[0] << " mm" << endl;
			MyLogFile << "1. Profilierposition 2. Ebene                      " << "= " << Ist_IBF_Ini.Axial.AGR_Pr[3] << " mm" << endl;
			MyLogFile << endl;
		}
		else
		{
			MyLogFile << "ACHTUNG !!! Biss nicht vorgewaehlt !!!" << endl;
		}
	}

	MyLogFile << endl;
	if (Ist_IBF_Ini.Flag.DA_Jenkouk_DW_Regelung == 1)
	{
		MyLogFile << "***!!! DA-Dornwalzenregelung vorgewaehlt !!!***" << endl;
		if (Ist_IBF_Ini.Flag.DA_Jenkouk_Messen_ohne_Fahren != 0)
		{
			MyLogFile << "Es wird gemessen und die Dornwalze (idealerweise) verfahren" << endl;
		}
		else
			MyLogFile << "Es wird NUR gemessen" << endl;
			MyLogFile << "Nachfolgende Werte wurden eingelesen" << endl;
			MyLogFile << "Abstand C :" << Ist_IBF_Ini.DW_Regelung.Abstand_C << endl;
			MyLogFile << "Nullpunkt :" << Ist_IBF_Ini.DW_Regelung.Messwert_Nullpunkt << endl;
			MyLogFile << "TR-Radius :" << Ist_IBF_Ini.DW_Regelung.Tastrollen_Radius << endl;
			MyLogFile << "Offset    :" << Ist_IBF_Ini.DW_Regelung.Offset << endl;
		}
	else
		MyLogFile << "Jenkouk Regler EIN(1) oder AUS(0) ? ->:" << Ist_IBF_Ini.Flag.DA_Jenkouk_DW_Regelung << endl << endl;
	
	if (Ist_IBF_Ini.Test.Flag == 1)
	{
		MyLogFile << "***IBF - Testwalzungen vorgewaehlt !!!***" << endl;
		MyLogFile << " Simulierter Ringdurchmesser                   " << "= " << Ist_IBF_Ini.Test.Ring_AD << endl;
	}
	
	/* Bissverhaeltnis*/
	if (Ist_IBF_Ini.Flag.Bissverhaeltnis == 1)
	{
		Soll_IBF_Ini.Axial.AGR_Pr[0] = Ist_IBF_Ini.Axial.AGR_Pr[0]; // Notwendig wenn mehrere Bisse gewalzt werden, damit die AG nach Positionierung per Biss nicht auf ersten Wert 'zurÃ¼ckfÃ¤hrt'
		Soll_IBF_Ini.Axial.Biss.AGR_Pr_Merker = Ist_IBF_Ini.Axial.AGR_Pr[0];
	}

	// Initialisierung der globalen IBF Strukturen
	iter_IBF	= 0;
	Ist_Inter	= Ist_Inter_Ini;
	Soll_Inter	= Soll_Inter_Ini;
	Soll_IBF	= Soll_IBF_Ini;
	Ist_IBF		= Ist_IBF_Ini;

	//-----------------------------------------------------------------------
	//-------------             SMS-Code                                -----
	//-----------------------------------------------------------------------

	running_flag = TRUE;
	finish_flag = FALSE;

	Blinker = 0;

	if (RmGetEntry(RM_SECOND(15), Mailboxl, &Entry) == RM_GOT_TIMEOUT)
	{
		cout << "Mailbox " << Mailboxl << " nicht vorhanden!  CNC Task gestartet ?" << endl;
		MyLogFile << "Mailbox " << Mailboxl << " nicht vorhanden!  CNC Task gestartet ?" << endl;
		running_flag = FALSE;
	}
	else
	{
		TRT_Mail_id = Entry.id;

		if (RmGetEntry(RM_SECOND(1), Powercon_SendSema, &Entry) == RM_GOT_TIMEOUT)
		{
			cout << "Semaphor " << Powercon_SendSema << " nicht vorhanden!" << endl;
			MyLogFile << "Semaphor " << Powercon_SendSema << " nicht vorhanden!" << endl;
			running_flag = FALSE;
		}
		else
		{
			Sema_PowerSendID = Entry.id;    //Send gilt fuer die CNC Seite, TRT empfaengt!

			if (RmGetEntry(RM_SECOND(1), Powercon_RecSema, &Entry) == RM_GOT_TIMEOUT)
			{
				cout << "Semaphor " << Powercon_RecSema << " nicht vorhanden!" << endl;
				MyLogFile << "Semaphor " << Powercon_RecSema << " nicht vorhanden!" << endl;
				running_flag = FALSE;
			}
			else
			{
				Sema_PowerRecID = Entry.id; //Receive gilt fuer die CNC Seite, TRT sendet!

				if (RmReceiveMail(RM_SECOND(1), TRT_Mail_id, &TRT_Mail) == RM_GOT_TIMEOUT)
				{
					cout << "Keine Mail empfangen!" << endl;
					MyLogFile << "Keine Mail empfangen!" << endl;
					running_flag = FALSE;
				}
				else
				{
					RwwtPool = (RwwtPool_tag*)TRT_Mail.adr;
					if (TRT_Mail.len != sizeof(RwwtPool_tag))
					{
						cout << "Poolgroesse unterschiedlich! Falsche Version!" << endl;
						MyLogFile << "Poolgroesse unterschiedlich! Falsche Version!" << endl;
						running_flag = FALSE;
					}
					else
					{
						RwwtPool->pLTableRWTH = Logger->getLogPointer();
						RwwtPool->pTeDat = &TeDat;

						RwwtPool->Steuer_RWTH = TRT_Init_done;
					}
				}
			}
		}
	}
}

/****************************************************************************/
// Destruktor
/****************************************************************************/
RWTH_EXCH::~RWTH_EXCH()
{
	if (running_flag == TRUE)
		RwwtPool->Steuer_RWTH = TRT_Finished;

	running_flag = FALSE;
}

/****************************************************************************/
// Memorypool belegen (aus_puff und aus_onli) 
/****************************************************************************/
int RWTH_EXCH::put_puff(void)
{
	if (running_flag && RwwtPool->Data_initialed && RwwtPool->Data_available)
	{
		if (RmGetBinSemaphore(RM_MILLISECOND(25), Sema_PowerRecID) == RM_GOT_TIMEOUT)
			return (FALSE);

		RwwtPool->ein_puff_RWTH = ein_puff;
		RwwtPool->ein_onli_RWTH = ein_onli;
		RwwtPool->aus_puff_RWTH = aus_puff;
		RwwtPool->aus_onli_RWTH = aus_onli;

		RwwtPool->Status_RWTH = TRT_fertig | Blinker;
		RwwtPool->Data_availableRWTH = TRUE;

		RmReleaseBinSemaphore(Sema_PowerRecID);

		TestCounter[1]++;
	}
	return (TRUE);
}


/****************************************************************************/
// Memorypool auf lokale Strukturen kopieren (ein_puff, ein_onli)
/****************************************************************************/
int RWTH_EXCH::get_puff(void)
{
	if (running_flag)
	{
		if (RwwtPool->Steuer_RWTH == TRT_Stop)
			finish_flag = TRUE;
	}
	if (running_flag && RwwtPool->Data_initialed && RwwtPool->Data_available)
	{
		RwwtPool->Status_RWTH = TRT_neustart | Blinker;

		if (RmGetBinSemaphore(RM_MILLISECOND(25), Sema_PowerRecID) == RM_GOT_TIMEOUT)
			return (FALSE);

		ein_puff = RwwtPool->ein_puff_back;
		ein_onli = RwwtPool->ein_onli_back;
		aus_puff = RwwtPool->aus_puff;
		aus_onli = RwwtPool->aus_onli;
		lokal_puff = RwwtPool->lokal_puff;

		RmReleaseBinSemaphore(Sema_PowerRecID);

		TestCounter[2]++;
	}
	return (TRUE);
}

/****************************************************************************/
// IBF Algorithmen aufrufen 
/****************************************************************************/
/** 
 * Diese Methode kann in zwei Teile gegliedert werden. Der erste Teil wird nur
 * ausgefuehrt, wenn das Programm RWTH_Task das erste mal
 * durchlaufen wird. Der zweite Teil wird nur dann durchlaufen, wenn der erste
 * Teil bereits durchlaufen wurde.
 *
 * Im ersten Teil werden Vorbereitungen fuer das Walzen getroffen. Hier wird
 * festgelegt, welcher Pfad in der RPW::Main() fuer die
 * Walzvorbereitung verwendet wird. Dies wird mit Hilfe der Variable 
 * Def_IBF_Allgemein_SOLL.InitAchse festgelegt.
 */
int RWTH_EXCH::Main_Control(void)
{
	if (running_flag && RwwtPool->Data_initialed && RwwtPool->Data_available)
	{
		if (++CountBlinker > 10)
		{
			CountBlinker = 0;
			Blinker ^= TRT_Blinker;
		}
		RwwtPool->Status_RWTH = TRT_laeuft | Blinker;

		//***********************************************************************
		// ==> Hier koennen eigene Methoden aufgerufen werden ! <==
		//***********************************************************************

	    time_t start, end;
		ctime(&start);
		//jeweils zum Walzenstart (Walzenstartflag) muessen einige Variablen vordefiniert werden, damit richtige CASE-Anweisungen im rpw.cpp (IBF-Modul) ausgefuehrt werden
		if (ein_puff.walzenstart_flag)
		{
			Ist_IBF.StartPos = 1;

			// Initialisierung der globalen IBF Strukturen
			iter_IBF	= 0;

			Ist_Inter	= Ist_Inter_Ini;
			Soll_Inter	= Soll_Inter_Ini;
			Ist_IBF		= Ist_IBF_Ini;
			Soll_IBF	= Soll_IBF_Ini;

			Soll_IBF.Axial.Pr_Num = 0;
			Soll_IBF.Flag.AG_Start_erreicht = 0;

			// Vor Walzenstart Ibf_Data.ini neu einlesen,
			// um aenderungen ohne neustart der CNC zu uebernehmen
			rpw->IBFPARA_auslesen(Ist_IBF, Soll_IBF, Ist_Inter);

			// Spezielle Anfahrroutine fuer Schuesselwalzen (11.1.2015 d.Otto)
			if (Ist_IBF.Flag.Axial_Radialwalzen == 3)
			{
				Soll_IBF.InitAchse = 's';
				Soll_IBF.Profilflag = -1;
			}
			//// Achsenmodi initialisieren (9.1.2015 d.Otto)
			Soll_Inter.RS_act	=	1;
			Soll_Inter.AS_act	=	1;
			Soll_Inter.zen_act	=	0;
			
			// Bissverhaeltnis
			Soll_IBF.Axial.Biss.Anzahl = 0;
			Soll_IBF.Axial.AGR_Pr[0] = Soll_IBF.Axial.Biss.AGR_Pr_Merker;
			Soll_IBF.Axial.Biss.AG_Pos_Erreicht = 0;
			Soll_IBF.Axial.Turbine.AG_Pos_Erreicht = 0;
			Soll_IBF.Axial.Turbine.Stufe_erreicht = 0;
			Soll_IBF.Axial.Turbine.zweite_Ebene_erreicht = 0;

			// IBF-Stuetzstelle 
			Soll_IBF.stuetz_var.skip_faktor = 1; // IBF-Stuetzstelle
			Soll_IBF.stuetz_var.merker = 0;		 // IBF-Stuetzstelle
			Soll_IBF.stuetz_var.crtimer = 0;	 // IBF-Stuetzstelle

			//Formenspektrum
			Soll_IBF.Formen.Profilflag = 1;
		}
		else
		{
			iter_IBF++;
		}
		
		rpw->Main_RAW(	iter_IBF,
						ein_puff,
						lokal_puff,
						aus_puff,
						ein_onli,
						aus_onli,
						Ist_Inter,
						Soll_Inter,
						Soll_IBF,
						Ist_IBF );

		ctime(&end);
		Ist_Inter.Systemzeit = difftime(end, start);    // Zeitdifferenz berechnen. Angabe in Sekunden

		// Zuweisungen fuer die Steuerung 

		/* zu setzende Flags mit denen IBF-Positionsvorgaben gültig werden */
		aus_onli.Ibf_nominal.RS_act		= Soll_Inter.RS_act;	// Flag Sollwerte Radialschlitten von Ibf auswertbar 1, nicht auswertbar 0
		aus_onli.Ibf_nominal.AS_act		= Soll_Inter.AS_act;	// Flag Sollwerte Axialschlitten von Ibf auswertbar
		aus_onli.Ibf_nominal.AG_act		= Soll_Inter.ag_act;	// Flag Sollwerte Axialgeruest von Ibf auswertbar
		aus_onli.Ibf_nominal.Zen_act	= Soll_Inter.zen_act;	// Flag Sollwerte Zentrierarme von Ibf auswertbar 1, nicht auswertbar 0
		
		/* Schalter Kraftregler */
		aus_onli.Ibf_nominal.RS_mode	= Soll_Inter.rs_mode;	// Betriebsart Vorschub (Bit0=0) oder Kraftregelung (Bit0=1)
		aus_onli.Ibf_nominal.AS_mode	= Soll_Inter.aso_mode;	// Betriebsart Vorschub (Bit0=0) oder Kraftregelung (Bit0=1)
		aus_onli.Ibf_nominal.AG_mode	= Soll_Inter.ag_mode;	// Betriebsart Vorschub (Bit0=0) oder Kraftregelung (Bit0=1)
		aus_onli.Ibf_nominal.Zen_mode	= Soll_Inter.zen_mode;	// Betriebsart Vorschub (Bit0=0) oder Kraftregelung (Bit0=1) !!! Betriebsart für beide Arme !!! 
		
		/* Zustellgeschwindigkeiten */
		aus_onli.ds_dh_sp_hp.s_punkt	= Soll_Inter.rs_v  * ein_onli.rwg_poti_wert;	/* Radialschlitten     	[mm/s]*/
		aus_onli.ds_dh_sp_hp.h_punkt	= Soll_Inter.aso_v * ein_onli.rwg_poti_wert;	/* Axialschlitten oben	[mm/s]*/
		aus_onli.Ibf_nominal.Soll_AG_V	= Soll_Inter.ag_v;								/* Axialgeruest			[mm/s]*/
		aus_onli.Ibf_nominal.Soll_ZA_V	= Soll_Inter.zal_v;								/* Zentrierarm links	[mm/s]*/
		aus_onli.Ibf_nominal.Soll_ZE_V	= Soll_Inter.zar_v;								/* Zentrierarm rechts	[mm/s]*/

		/* Sollpositionen */
		aus_onli.Ibf_nominal.Soll_RS_Pos = Soll_Inter.rs_pos;	/* Radialschlitten				[mm]*/
		aus_onli.Ibf_nominal.Soll_AS_Pos = Soll_Inter.aso_pos;	/* Axialschlitten oben			[mm]*/
		aus_onli.Ibf_nominal.Soll_AG_Pos = Soll_Inter.ag_pos;	/* Axialschlitten				[mm]*/
		aus_onli.Ibf_nominal.Soll_ZA_Pos = Soll_Inter.zar_pos;	/* Zentrierarm rechts Auslauf	[mm]*/
		aus_onli.Ibf_nominal.Soll_ZE_Pos = Soll_Inter.zal_pos;	/* Zentrierarm links Einlauf	[mm]*/
		
		/* Drehzahlen */
		aus_puff.n_omega.n_hw_motor		= Soll_Inter.hw_n;		/* Hauptwalze 			[1/min]*/
		aus_puff.n_omega.n_aw_motor_g_o = Soll_Inter.kwo_n;		/* Kegelwalze oben		[1/min]*/
		aus_puff.n_omega.n_aw_motor_g_u = Soll_Inter.kwu_n;		/* Kegelwalze unten		[1/min]*/

		/* Schrittnummer */
		// Soll_Inter.schritt_nr;			

		/* Sollkraefte */
		aus_onli.Ibf_nominal.Soll_FR	= Soll_Inter.rs_kraft;		/* Radialkraft	[N] */
		aus_onli.Ibf_nominal.Soll_FA	= Soll_Inter.aso_kraft;		/* Axialkraft	[N] */
		aus_onli.Ibf_nominal.Soll_FAG	= Soll_Inter.ag_kraft;		/* Axialgeruest [N] */
		aus_onli.Ibf_nominal.Soll_FZ	= Soll_Inter.zal_kraft;		/* Zentrierarme	[N] */

		if (Ist_IBF.Flag.Axial_Radialwalzen == 0)
			/* !!! Darf nur aktiv sein, wenn Axialprofilieren angewaehlt wird und Kragenwalze verbaut ist !!! */
		{
			aus_onli.fa_max_axialwalze = 400000.0F;
				/* Kraftgrenzenregler fuer Kragenwalze auf 40T, ansonsten wird Kraft anhang Kegelwalze auf mittlerer Wanddicke begrenzt */
		}

		// Sollwertvorgaben fuer Druckrollen. 2.12.2012 D.O	
		aus_onli.Ibf_nominal.DRR_A_act		= Soll_Inter.DRR_Param.DrR_A.act;
		aus_onli.Ibf_nominal.DRR_E_act		= Soll_Inter.DRR_Param.DrR_E.act;
		aus_onli.Ibf_nominal.DRR_A_mode		= Soll_Inter.DRR_Param.DrR_A.mode;
		aus_onli.Ibf_nominal.DRR_E_mode		= Soll_Inter.DRR_Param.DrR_E.mode;
		aus_onli.Ibf_nominal.Soll_DRR_A_V	= Soll_Inter.DRR_Param.DrR_A.V;
		aus_onli.Ibf_nominal.Soll_DRR_E_V	= Soll_Inter.DRR_Param.DrR_E.V;
		aus_onli.Ibf_nominal.Soll_DRR_A_Pos	= 940.9F - Soll_Inter.DRR_Param.DrR_A.Pos;
		aus_onli.Ibf_nominal.Soll_DRR_E_Pos	= 940.9F - Soll_Inter.DRR_Param.DrR_E.Pos;
		aus_onli.Ibf_nominal.Soll_FDRR_A	= Soll_Inter.DRR_Param.DrR_A.Kraft;
		aus_onli.Ibf_nominal.Soll_FDRR_E	= Soll_Inter.DRR_Param.DrR_E.Kraft;
	}
	return (TRUE);
}

int In_RWTH_LOG_Schreiben(char* buffer)
{
	MyLogFile << buffer << endl;

	return TRUE;
}
