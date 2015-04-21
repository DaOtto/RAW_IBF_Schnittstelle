/*--DATEI HEADER---------------------------------------------------------------
;   Dateiname       : IBF_Schuessel.cpp
;   Version         : V1.00a
;   Beschreibung    : Steuerungsmethoden der Schuesselwalzstrategie
;	Plattform		: RMOS3,WIN32				  
;
;                    
;
;   Autor           : D.Otto
;   date            : Januar 2015
;
-----------------------------------------------------------------------------*/
#include "rpw.hpp"
#include <iostream>
#include <math.h>

#define SIN_KWW_HALBE 0.382683432F
//#define MIT_RING

/*-----------------------------------------------------------------------------
*
* Funktion 'Main'
*
* Wird aus der Funktion 'rpw::Main' in den 'case'-Abschnitten
* Ist_IBF.Profilflag == -1
* Ist_IBF.Profilflag == 0 && InitAchse == 's' und
* Ist_IBF.Profilflag == 1
*
* aufgerufen.
*
* Hier werden zunaechst einige Zustandsflags aktualisiert, und dann in die
* aktuellen Hauptroutinen des Prozessablaufs verzweigt.
* Nach Rückkehr aus den Hauptroutinen erfolgt eine Fehlerverarbeitung,
* bevor die neuen Sollparameter an die CNC uebergeben werden.
*
-----------------------------------------------------------------------------*/

int IBF_Schuessel::Main(	struct Def_Ist_Inter			&Ist_Inter,
							struct Def_IBF_Allgemein_IST	&Ist_IBF,
							struct Def_Soll_Inter			&Soll_Inter,
							struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	int err = 0;

	if (Ist_IBF.Schuessel.Test.Flag_oRing)
	{
		if ( Ist_IBF.ASO_Pos < Ist_IBF.Schuessel.Walzform.hm+Ist_IBF.Schuessel.eps) Ist_IBF.Flag.as_kraft_anfahren_erreicht = 1;
		else Ist_IBF.Flag.as_kraft_anfahren_erreicht = 0;

		if ( fabs(Ist_IBF.DRR_Param.DrR_A.delta_Ring) < Ist_IBF.Schuessel.eps ) Ist_IBF.Flag.DRA_kraft_anfahren_erreicht = 1;
		else Ist_IBF.Flag.DRA_kraft_anfahren_erreicht = 0;
		
		if ( fabs(Ist_IBF.DRR_Param.DrR_E.delta_Ring) < Ist_IBF.Schuessel.eps ) Ist_IBF.Flag.DRE_kraft_anfahren_erreicht = 1;
		else Ist_IBF.Flag.DRE_kraft_anfahren_erreicht = 0;
	}

	// Haltezeit abwarten
	if (Ist_IBF.Zeit.t_Halte)
	{
		Soll_IBF.Zeit.t_Halte -= 1;
		return ERR_WAIT;
	}
				
	// Verzweigung in die aktuelle Walzphase
	switch(Ist_IBF.Profilflag)
	{
	case -1: // Startpositionen anfahren
		err = Anfahren(Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
		break;

	case 0: // Wird von rpw bei Profilflag==0 und Initachse=='s' aufgerufen
		// Walzenantriebe Steuern
		WA_Regler( Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
		err = Anwalzen(Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
		break;

	case 1: // Walzphase
		err = Walzen(Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
		break;
	
	case 2: // Rundungsphase
		err = Rundung(Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
		break;

	default:  // Fehler/Fertig -> Oeffnen
		
		break;
	}
	return err;
};

/*-----------------------------------------------------------------------------
*
* Hauptroutinen zur Kontrolle des Prozessablaufs
*
* 1. 'Anfahren' : Anfahren der CARWIN-Startpositionen und Anwalzen
* 2. 'Walzen'	: Walzvorgang bis Soll-Form erreicht wird.
* 3. 'Oeffnen'	: RAW oeffnen zum entladen.
*
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
* Funktion 'Anfahren'
*
* Der Ablauf ist in zwei Stufen eingeteilt:
*
* 1. Alle Achsen Weggebunden an den Ring, wie er von CARWIN vorgegeben wird,
*    bis auf einen gewissen Sicherheitsabstand anfahren.
* 2. Druckrollen, Zentrierrollen, AG und AS bis zum Kontakt anfahren und
*    anschliessend Motoren starten. Ab hier beginnt dann die Online-berechnung
*    der Ringgeometrie aus Tastrollen- und Druckrollenposition
*
* Sobald der Sollzustand der 2.Stufe erreicht ist, wird die Kontrolle an die
* Funktion 'Walzen' uebergeben.
-----------------------------------------------------------------------------*/

int IBF_Schuessel::Anfahren(struct Def_Ist_Inter			&Ist_Inter,
							struct Def_IBF_Allgemein_IST	&Ist_IBF,
							struct Def_Soll_Inter			&Soll_Inter,
							struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	// Fehlercode (Returnvalue)
	int err = ERR_OK;
	
	// Lokale Variablen
	float	dist, 
			delta, 
			vmax=120,
			dir;

	switch(Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag)
	{
		case 0: // Zunächst alle Achsen stopp und auf Positionssteuerung durch IBF
			err = Initialisieren(Ist_Inter, Soll_Inter, Ist_IBF, Soll_IBF);
			Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag += 1;
			break;

		case 1: // RS an StartPos
			
			cout << "RS an StartPos.\r";

			// Distanz zwischen Zielposition und Istposition
			dist = Ist_IBF.Schuessel.StartPos.RS_startPos - Ist_IBF.RS_Pos;
			delta = dist * 0.707F;
			dir = sgn(delta);
								
			// Zielposition erreicht?
			if ( fabs(dist) < ( Ist_IBF.Schuessel.eps * 2.0F) )
			{
				Soll_IBF.RS_V			= 0.0F;
				Soll_IBF.RS_act			= ACT_IBF;
				Soll_IBF.Flag.rs_mode	= WEG;
				Soll_IBF.RS_Pos			= Ist_IBF.Schuessel.StartPos.RS_startPos;
				
				cout  << endl;
				Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag += 1;
				err = ERR_OK;
			}
			else
			{
				// Weiter richtung Zielpos fahren
				if (dir>0)
				{
					Soll_IBF.RS_V			= min((dir*vmax),delta)+dir;
				}
				else
				{
					Soll_IBF.RS_V			= max((dir*vmax),delta)+dir;
				}
			
				Soll_IBF.RS_act			= ACT_IBF;
				Soll_IBF.Flag.rs_mode	= WEG;
				Soll_IBF.RS_Pos			= Ist_IBF.RS_Pos + Soll_IBF.RS_V - dir;
				Soll_IBF.RS_Kraft		= Soll_IBF.RS_Kraft_Vorgabe * 0.1F; // 10% Kraftvorgabe
				
				err = ERR_OK;
			}
			break;

		case 2: // AS an StartPos
			
			cout << "AS an StartPos.\r";
			
			// Distanz zwischen Zielposition und Istposition
			dist = Ist_IBF.Schuessel.StartPos.AS_startPos-Ist_IBF.ASO_Pos;
			delta =dist * 0.707F;
			dir = sgn(delta);
								
			// Zielposition erreicht?
			if (fabs(dist) < (Ist_IBF.Schuessel.eps * 2.0F) )
			{
				Soll_IBF.ASO_V			= 0.0F;
				Soll_IBF.AS_act			= ACT_IBF;
				Soll_IBF.Flag.aso_mode	= WEG;
				Soll_IBF.ASO_Pos		= Ist_IBF.Schuessel.StartPos.AS_startPos;
				
				cout  << endl;
				Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag += 1;
				err = ERR_OK;
			}
			else
			{
				// Weiter richtung Zielpos fahren
				if (dir>0)
				{
					Soll_IBF.ASO_V			= min((dir*vmax),delta)+dir;
				}
				else
				{
					Soll_IBF.ASO_V			= max((dir*vmax),delta)+dir;
				}
			
				Soll_IBF.AS_act			= ACT_IBF;
				Soll_IBF.Flag.aso_mode	= WEG;
				Soll_IBF.ASO_Pos		= Ist_IBF.ASO_Pos + Soll_IBF.ASO_V-dir;
				Soll_IBF.AS_Kraft		= Soll_IBF.AS_Kraft_Vorgabe * 0.1F; // 10% Kraftvorgabe
				
				err = ERR_OK;
			}
			break;

		case 3: // AG an StartPos
			
			cout << "AG an StartPos.\r";
			
			// Distanz zwischen Zielposition und Istposition
			dist = Ist_IBF.Schuessel.StartPos.AG_startPos-Ist_IBF.AG_Pos;
			delta = dist*0.707F;
			dir = sgn(delta);

			// Zielposition erreicht?
			if (fabs(dist) < (Ist_IBF.Schuessel.eps * 2.0F))
			{
				// AG stoppen und naechste Achse
				Soll_IBF.AG_V			= 0.0F;
				Soll_IBF.Flag.ag_act	= ACT_IBF;
				Soll_IBF.Flag.ag_mode	= AG_WEG | AG_nABS | AG_SIBF;
				Soll_IBF.AG_Pos			= Ist_IBF.Schuessel.StartPos.AG_startPos;
				Soll_IBF.AG_Kraft		= Soll_IBF.AG_Kraft_Vorgabe * 0.1F;

				cout  << endl;
				Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag += 1;
				err = ERR_OK;
			}
			else
			{
				// Weiter richtung Zielpos fahren
				if (dir>0)
				{
					Soll_IBF.AG_V			= min((dir*vmax),dist)+dir;
				}
				else
				{
					Soll_IBF.AG_V			= max((dir*vmax),dist)+dir;
				}
			
				Soll_IBF.Flag.ag_act	= ACT_IBF;
				Soll_IBF.Flag.ag_mode	= AG_WEG | AG_nABS | AG_SIBF;
				Soll_IBF.AG_Pos			= Ist_IBF.AG_Pos + Soll_IBF.AG_V-dir;
				Soll_IBF.AG_Kraft		= Soll_IBF.AG_Kraft_Vorgabe * 0.1F;
				err = ERR_OK;
			}
			break;

		case 4: // Zentrr. an StartPos
			cout << "Zentrr. an StartPos.\r";
			Soll_IBF.ZER_Param.act				= ACT_IBF;
			Soll_IBF.ZER_Param.mode				= ZEN_MODE_WEG;
			Soll_IBF.ZER_Param.ZRA.delta_Ring	= Ist_IBF.Schuessel.StartPos.ZR_startPos;
			Soll_IBF.ZER_Param.ZRE.delta_Ring	= Soll_IBF.ZER_Param.ZRA.delta_Ring;

			ZER_trans_Soll(Soll_Inter,Soll_IBF,Ist_IBF);

			// Distanz zwischen Zielposition und Istposition
			dist	= Ist_IBF.ZER_Param.ZRA.MTS-Soll_Inter.zar_pos;
			delta 	= dist * 0.707F;
			dir		= sgn(delta);
			
			// Zielposition erreicht?
			if (fabs(dist) < (Ist_IBF.Schuessel.eps * 2.0F) )
			{
				// Zentrierrolle (Auslaufseite) auf Position halten
				//Soll_IBF.ZER_Param.ZRA.V_Spur		= 0.0F;
				Soll_IBF.ZER_Param.act				= ACT_IBF;
				Soll_IBF.ZER_Param.mode				= ZEN_MODE_WEG;
				cout  << endl;
				Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag += 1;
				err = ERR_OK;
			}
			else
			{
				// Weiter richtung Zielpos fahren
				if (dir>0)
				{
					Soll_IBF.ZER_Param.ZRA.V_Spur = min((dir*vmax),delta)+dir;
				}
				else
				{
					Soll_IBF.ZER_Param.ZRA.V_Spur = max((dir*vmax),delta)+dir;
				}
				
				err = ERR_OK;
			}
								
			break;

		case 5: // Druckr. an StartPos

			cout << "Druckr. an StartPos.\r";
			
			Soll_IBF.DRR_Param.DrR_A.V_DrR				= vmax;
			Soll_IBF.DRR_Param.DrR_A.Kraft				= Ist_IBF.Schuessel.F_Soll_DrR;
			Soll_IBF.DRR_Param.DrR_A.act				= ACT_IBF;
			Soll_IBF.DRR_Param.DrR_A.mode				= DRR_MODE_WEG;
			Soll_IBF.DRR_Param.DrR_A.delta_Ring			= Ist_IBF.Schuessel.StartPos.DRA_startPos;
			
			Soll_IBF.DRR_Param.DrR_E.V_DrR				= vmax;
			Soll_IBF.DRR_Param.DrR_E.Kraft				= Ist_IBF.Schuessel.F_Soll_DrR;
			Soll_IBF.DRR_Param.DrR_E.act				= ACT_IBF;
			Soll_IBF.DRR_Param.DrR_E.mode				= DRR_MODE_WEG;
			Soll_IBF.DRR_Param.DrR_E.delta_Ring			= Ist_IBF.Schuessel.StartPos.DRE_startPos;

			if (max(fabs(Soll_IBF.DRR_Param.DrR_A.delta_Ring-Ist_IBF.DRR_Param.DrR_A.delta_Ring),
					fabs(Soll_IBF.DRR_Param.DrR_E.delta_Ring-Ist_IBF.DRR_Param.DrR_E.delta_Ring)) < (Ist_IBF.Schuessel.eps * 10.0F) ) // Position erreicht ?
			{
				//Soll_IBF.DRR_Param.DrR_A.V_DrR				= 0.0F;
				Soll_IBF.DRR_Param.DrR_A.act				= ACT_IBF;
				Soll_IBF.DRR_Param.DrR_A.mode				= DRR_MODE_WEG;
				Soll_IBF.DRR_Param.DrR_A.delta_Ring			= Ist_IBF.DRR_Param.DrR_A.delta_Ring;
			
				//Soll_IBF.DRR_Param.DrR_E.V_DrR				= 0.0F;
				Soll_IBF.DRR_Param.DrR_E.act				= ACT_IBF;
				Soll_IBF.DRR_Param.DrR_E.mode				= DRR_MODE_WEG;
				Soll_IBF.DRR_Param.DrR_E.delta_Ring			= Ist_IBF.DRR_Param.DrR_E.delta_Ring;
				
				cout  << endl;
				Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag += 1;
				err = ERR_OK;
			}

			break;

		case 6: // Weiter zu naechster Walzphase (Anwalzen)
			cout << "Alle Startpositionen erreicht.\r" << endl;
			Soll_IBF.Profilflag = 0;
			Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag = 0;
			err = ERR_OK;
			break;

		default:
			cout << "Was mach ich hier??" << endl;
			err = ERR_FATAL;
			break;
	} // switch(Ist_IBF.Schuessel.InitFlag)

	return err;
};


int IBF_Schuessel::Anwalzen(struct Def_Ist_Inter			&Ist_Inter, 
							struct Def_IBF_Allgemein_IST	&Ist_IBF,
							struct Def_Soll_Inter			&Soll_Inter,
							struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	int err = ERR_OK;

	switch(Ist_IBF.Schuessel.AblaufFlags.AnwalzFlag)
	{
	case 0: // Druckrollen an Ring (Einlauf: Kraft; Auslauf: Weg)
		
		cout << "Druckr. anfahren (Einlauf in Kraftsteuerung, Auslauf folgt Einlauf.)\r";

		// Druckrolle Einlaufseite
		Soll_IBF.DRR_Param.DrR_E.V_DrR				= 7.0F;
		Soll_IBF.DRR_Param.DrR_E.act				= ACT_IBF;
		Soll_IBF.DRR_Param.DrR_E.mode				= DRR_MODE_KRAFT;
		Soll_IBF.DRR_Param.DrR_E.delta_Ring			= -1.0F;
		Soll_IBF.DRR_Param.DrR_E.Kraft				= Ist_IBF.Schuessel.F_Soll_DrR;

		//DRR_trans_Soll(Ist_IBF , Soll_IBF);
		
		// Druckrolle Auslaufseite
		Soll_IBF.DRR_Param.DrR_A.V_DrR				= 7.0F;
		Soll_IBF.DRR_Param.DrR_A.act				= ACT_IBF;
		Soll_IBF.DRR_Param.DrR_A.mode				= DRR_MODE_WEG;
		Soll_IBF.DRR_Param.DrR_A.delta_Ring			= Ist_IBF.DRR_Param.DrR_E.delta_Ring;
		Soll_IBF.DRR_Param.DrR_A.Kraft				= Ist_IBF.Schuessel.F_Soll_DrR;
		
		if (Ist_IBF.Flag.DRE_kraft_anfahren_erreicht)
		{
			cout  << endl;
			Ist_IBF.Schuessel.AblaufFlags.AnwalzFlag += 1;
			err = ERR_OK;
		}

		break;

	case 1: // Zentrierrollen an Ring (Weg)

		cout << "Zentrierrollen anfahren (Weg)\r";
		
		// Zentrierarme (Einlauf- und Auslaufseite)
		Soll_IBF.ZER_Param.ZRA.V_Spur				= 100.0F;
		Soll_IBF.ZER_Param.ZRE.V_Spur				= 100.0F;
		Soll_IBF.ZER_Param.act						= ACT_IBF;
		Soll_IBF.ZER_Param.mode						= ZEN_MODE_WEG;
		Soll_IBF.ZER_Param.ZRA.delta_Ring			= -2.0F;
		Soll_IBF.ZER_Param.ZRE.delta_Ring			= -2.0F;
		Soll_IBF.ZER_Param.Kraft					= Soll_IBF.ZAR_Kraft_Vorgabe; // gilt fuer beide ZA
		
		// Um die Abbruchbedingung erfüllen zu können, müssen schon hier Soll-Parameter berechnet werden
		ZER_trans_Soll(Soll_Inter,Soll_IBF,Ist_IBF);
		
		if (Ist_IBF.ZER_Param.ZRA.Flag_Kontakt) // Position erreicht ?
		{
			Soll_IBF.ZER_Param.ZRA.V_Spur		= 0.0F;
			Soll_IBF.ZER_Param.ZRE.V_Spur		= 0.0F;
			Soll_IBF.ZER_Param.act				= ACT_IBF;
			Soll_IBF.ZER_Param.mode				= ZEN_MODE_WEG;
			cout  << endl;
			Ist_IBF.Schuessel.AblaufFlags.AnwalzFlag += 1;
			Soll_IBF.Zeit.t_Halte = 0;
			err = ERR_OK;
		}
		break;

	case 2: // Axialschlitten anfahren (Kraft)

		cout << "Axialschlitten anfahren (Kraft)\r";

		// Axialschlitten
		Soll_IBF.ASO_V								= 7.0F;
		Soll_IBF.AS_act								= ACT_IBF;
		Soll_IBF.Flag.aso_mode						= KRAFT;
		Soll_IBF.ASO_Pos							= Ist_IBF.ASO_Pos-10;
		Soll_IBF.AS_Kraft							= Soll_IBF.AS_Kraft_Anfahren;

		if (Ist_IBF.Flag.as_kraft_anfahren_erreicht)
		{
			Soll_IBF.ASO_V								= 0.0F;
			Soll_IBF.AS_act								= ACT_IBF;
			Soll_IBF.Flag.aso_mode						= WEG;
			Soll_IBF.ASO_Pos							= Ist_IBF.ASO_Pos;
			Soll_IBF.AS_Kraft							= Soll_IBF.AS_Kraft_Anfahren;

			cout  << endl;
			Ist_IBF.Schuessel.AblaufFlags.AnwalzFlag += 1;
			err = ERR_OK;
		}
		break;

	default:
		Soll_IBF.Profilflag = 1;
		break;
	}
	
	return err;
};

/*-----------------------------------------------------------------------------
* Funktion 'Walzen'
*
* Der Ablauf:
*
*
-----------------------------------------------------------------------------*/

int IBF_Schuessel::Walzen(	struct Def_Ist_Inter			&Ist_Inter, 
							struct Def_IBF_Allgemein_IST	&Ist_IBF,
							struct Def_Soll_Inter			&Soll_Inter,
							struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	int err = ERR_OK;

	// Abbruchbedingungen pruefen
	if (Ist_IBF.Schuessel.Walzform.hm < Ist_IBF.Schuessel.Endform.Ende_h_min_mm) Ist_IBF.Schuessel.Endform.erreicht = 1;
	if (Ist_IBF.Schuessel.Walzform.Kletterhoehe > Ist_IBF.Schuessel.Endform.Ende_max_Kletterhoehe ) Ist_IBF.Schuessel.Endform.erreicht = 1;
	if (Ist_IBF.Schuessel.Walzform.Kletterwinkel > (Ist_IBF.Schuessel.Endform.Ende_alpha_grad*PI/180)) Ist_IBF.Schuessel.Endform.erreicht = 1;

	if ( Ist_IBF.Schuessel.Endform.erreicht )
	{

		Soll_IBF.Profilflag += 1;
		return ERR_OK;
	}

	// Pruefen, ob Zentrierung geschlossen werden soll
	if (Ist_IBF.Schuessel.Walzform.Kletterwinkel > (7.0F*PI/180.0F)) Ist_IBF.Schuessel.Flag_Zen_geoeffnet = 0;
	else Ist_IBF.Schuessel.Flag_Zen_geoeffnet = 1;


	err=AS_Regler( Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
	RS_Regler( Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
	AG_Regler( Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
	DR_Regler( Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
	ZR_Regler( Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
	WA_Regler( Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);

	Ist_IBF.K_Iter++;

	return err;
};	

/*-----------------------------------------------------------------------------
* Funktion 'Oeffnen'
*
* Der Ablauf:
*
*
-----------------------------------------------------------------------------*/

int IBF_Schuessel::Rundung(	struct Def_Ist_Inter			&Ist_Inter, 
							struct Def_IBF_Allgemein_IST	&Ist_IBF,
							struct Def_Soll_Inter			&Soll_Inter,
							struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	int err = ERR_OK;
	if (Ist_IBF.Schuessel.AblaufFlags.OeffnenFlag)
	{
		Soll_IBF.Profilflag += 1;
		return ERR_FERTIG_HM;
	}
	Soll_IBF.AS_act			= ACT_IBF;
	Soll_IBF.Flag.aso_mode	= WEG;
	Soll_IBF.ASO_Pos		= Ist_IBF.Schuessel.Endform.Ende_h_min_mm;	// Endpunkt der Walzung. Vorgabe aus IBF_Data.ini
	Soll_IBF.ASO_V			= 1.0F;										// Minimal Zustellen um gleichmaessige Höhe zu erreichen
	Soll_IBF.AS_Kraft		= Soll_IBF.AS_Kraft_Vorgabe;				// (Grenz-)Kraftvorgabe aus IBF_Data.ini

	//Drehzahl der Walzenantriebe Steuern
	WA_Regler( Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
	
	// Oeffnen nach Ablauf der Haltezeit
	Ist_IBF.Schuessel.AblaufFlags.OeffnenFlag = 1;
	Soll_IBF.Zeit.t_Halte = 30;
	
	return err;
};

/*-----------------------------------------------------------------------------
*
* Subroutinen
*
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
* Funktion 'Initialisieren'
*
* Zweck: Initialisierung der Soll-Größen VOR beginn des Walzprogramms
*
*
-----------------------------------------------------------------------------*/

int IBF_Schuessel::Initialisieren(	struct Def_Ist_Inter			&Ist_Inter,
									struct Def_Soll_Inter			&Soll_Inter,
									struct Def_IBF_Allgemein_IST	&Ist_IBF, 
									struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	/// Vorbereitung einiger konstanter Parameter für den Prozess

	// Geometrie der Vorform berechnen
	Vorform_geo_berechnen( Ist_IBF );
	
	// Geometrie der Walzform berechnen
	Schuessel_Form_IST( Ist_IBF , Ist_Inter );
	
	// Startpositionen aus Vorringgeometrie ermitteln
	Ist_IBF.Schuessel.StartPos.RS_startPos = Ist_IBF.Schuessel.Walzform.dw_min_Pos + Ist_IBF.Schuessel.offset_DW;
	Ist_IBF.Schuessel.StartPos.AS_startPos = Ist_IBF.Schuessel.Vorform.hm_mm + 15;
	Ist_IBF.Schuessel.StartPos.AG_startPos = Ist_IBF.Schuessel.Vorform.da_mm / 2.0F;
	Ist_IBF.Schuessel.StartPos.ZR_startPos = Ist_IBF.Schuessel.offset_ZEN;
	Ist_IBF.Schuessel.StartPos.DRA_startPos= 20.0F;
	Ist_IBF.Schuessel.StartPos.DRE_startPos= 20.0F;

	/// Zunächst alle Achsen stopp und auf Positionssteuerung durch IBF, Kraefte auf 10%
	
	// Axialschlitten
	Soll_IBF.ASO_V								= 0.0F;
	Soll_IBF.AS_act								= ACT_IBF;
	Soll_IBF.Flag.aso_mode						= WEG;
	Soll_IBF.ASO_Pos							= Ist_IBF.ASO_Pos;
	Soll_IBF.AS_Kraft							= Soll_IBF.AS_Kraft_Anfahren;

	// Radialschlitten
	Soll_IBF.RS_V								= 0.0F;
	Soll_IBF.RS_act								= ACT_IBF;
	Soll_IBF.Flag.rs_mode						= WEG;
	Soll_IBF.RS_Pos								= Ist_IBF.RS_Pos;
	Soll_IBF.RS_Kraft							= Soll_IBF.RS_Kraft_Vorgabe * 0.1F;

	// Axialgeruest
	Soll_IBF.AG_V								= 0.0F;
	Soll_IBF.Flag.ag_act						= ACT_IBF;
	Soll_IBF.Flag.ag_mode						= AG_WEG | AG_nABS | AG_SIBF;
	Soll_IBF.AG_Pos								= Ist_IBF.AG_Pos;
	Soll_IBF.AG_Kraft							= Soll_IBF.AG_Kraft_Vorgabe * 0.1F;

	// Zentrierarme (Einlauf- und Auslaufseite)
	Soll_IBF.ZER_Param.ZRA.V_Spur				= 20.0F;
	Soll_IBF.ZER_Param.ZRE.V_Spur				= 20.0F;
	Soll_IBF.ZER_Param.act						= ACT_IBF;
	Soll_IBF.ZER_Param.mode						= ZEN_MODE_WEG;
	Soll_IBF.ZER_Param.ZRA.delta_Ring			= Ist_IBF.Schuessel.offset_ZEN;
	Soll_IBF.ZER_Param.ZRE.delta_Ring			= Ist_IBF.Schuessel.offset_ZEN;
	Soll_IBF.ZER_Param.Kraft					= Soll_IBF.ZAR_Kraft_Vorgabe * 0.1F; // gilt fuer beide ZA
	
	// Druckrolle Auslaufseite
	Soll_IBF.DRR_Param.DrR_A.V_DrR				= 200;
	Soll_IBF.DRR_Param.DrR_A.act				= ACT_IBF;
	Soll_IBF.DRR_Param.DrR_A.mode				= DRR_MODE_WEG;
	Soll_IBF.DRR_Param.DrR_A.delta_Ring			= Ist_IBF.Schuessel.StartPos.DRA_startPos;
	Soll_IBF.DRR_Param.DrR_A.Kraft				= Ist_IBF.Schuessel.F_Soll_DrR;

	// Druckrolle Einlaufseite
	Soll_IBF.DRR_Param.DrR_E.V_DrR				= 200;
	Soll_IBF.DRR_Param.DrR_E.act				= ACT_IBF;
	Soll_IBF.DRR_Param.DrR_E.mode				= DRR_MODE_WEG;
	Soll_IBF.DRR_Param.DrR_E.delta_Ring			= Ist_IBF.Schuessel.StartPos.DRE_startPos;
	Soll_IBF.DRR_Param.DrR_E.Kraft				= Ist_IBF.Schuessel.F_Soll_DrR;

	// Walzenantriebe Steuern
	WA_Regler( Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
	
	Ist_IBF.K_Iter = 0;
	return ERR_OK;
};

int RS_Regler(	const  Def_Ist_Inter			&Ist_Inter,
				const  Def_IBF_Allgemein_IST	&Ist_IBF,
				struct Def_Soll_Inter			&Soll_Inter,
				struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	float Soll_pos	= Ist_IBF.Schuessel.Walzform.dw_min_Pos + Ist_IBF.Schuessel.offset_DW;
	float Distanz	= Soll_pos - Ist_IBF.RS_Pos;
	float Soll_V	= ( Distanz / 0.1F ) * 2.0F;
	float dir		= sgn( Distanz );
	const float	vmax = 100;
	
	Soll_IBF.RS_act			= ACT_IBF;
	Soll_IBF.Flag.rs_mode	= WEG;
	Soll_IBF.RS_Pos			= Soll_pos;
	Soll_IBF.RS_V			= ( dir > 0 ) ? min( ( dir * vmax ) , Soll_V ) : max( ( dir * vmax ) , Soll_V );
	Soll_IBF.RS_Kraft		= Soll_IBF.RS_Kraft_Vorgabe;

	return ERR_OK;
};

int AG_Regler(	const  Def_Ist_Inter			&Ist_Inter,
				const  Def_IBF_Allgemein_IST	&Ist_IBF,
				struct Def_Soll_Inter			&Soll_Inter,
				struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	float Soll_pos	= max( ( Soll_IBF.RS_Pos + Ist_Inter.Werkzeug.Durchmesser_DW - Ist_Inter.Werkzeug.l_fehlende_spitze + 5 ) , Ist_IBF.Schuessel.Walzform.da_mf / 2.0F );
	float Distanz	= Soll_pos - Ist_IBF.AG_Pos;
	float Soll_V	= ( Distanz / 0.1F ) * 2.0F;
	float dir		= sgn( Distanz );
	const float	vmax = 100;

	Soll_IBF.Flag.ag_act	= ACT_IBF;
	Soll_IBF.Flag.ag_mode	= AG_WEG | AG_nABS | AG_SIBF;
	Soll_IBF.AG_Pos			= Soll_pos;
	Soll_IBF.AG_V			= ( dir > 0 ) ? min( ( dir * vmax ) , Soll_V ) : max( ( dir * vmax ) , Soll_V );
	Soll_IBF.AG_Kraft		= Soll_IBF.AG_Kraft_Vorgabe;

	return ERR_OK;			
};

int AS_Regler(	const  Def_Ist_Inter			&Ist_Inter,
				const  Def_IBF_Allgemein_IST	&Ist_IBF,
				struct Def_Soll_Inter			&Soll_Inter,
				struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	// Soll Ringhoehe erreicht?
	if ( Ist_IBF.ASO_Pos <= Ist_IBF.Schuessel.Endform.Ende_h_min_mm )
	{
		Soll_IBF.AS_act			= ACT_IBF;
		Soll_IBF.Flag.aso_mode	= WEG;
		Soll_IBF.ASO_V			= 0.0F;
		Soll_IBF.ASO_Pos		= Ist_IBF.ASO_Pos;
		return ERR_FERTIG_HM;
	}

	Soll_IBF.AS_act			= ACT_IBF;
	Soll_IBF.Flag.aso_mode	= WEG;
	Soll_IBF.ASO_Pos		= Ist_IBF.Schuessel.Endform.Ende_h_min_mm;	// Endpunkt der Walzung. Vorgabe aus IBF_Data.ini
	Soll_IBF.ASO_V			= Ist_IBF.Schuessel.V_Soll_AS;				// Vorgabe aus IBF_Data.ini
	Soll_IBF.AS_Kraft		= Soll_IBF.AS_Kraft_Vorgabe;				// (Grenz-)Kraftvorgabe aus IBF_Data.ini
	return ERR_OK;
};

int ZR_Regler(	const  Def_Ist_Inter			&Ist_Inter,
				const  Def_IBF_Allgemein_IST	&Ist_IBF,
				struct Def_Soll_Inter			&Soll_Inter,
				struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	Soll_IBF.ZER_Param.ZRA.V_Spur				= 100.0F;
	Soll_IBF.ZER_Param.ZRE.V_Spur				= 100.0F;
	Soll_IBF.ZER_Param.act						= ACT_IBF;
	Soll_IBF.ZER_Param.mode						= ZEN_MODE_WEG;
	Soll_IBF.ZER_Param.ZRA.delta_Ring			= Ist_IBF.Schuessel.offset_ZEN * Ist_IBF.Schuessel.Flag_Zen_geoeffnet;
	Soll_IBF.ZER_Param.ZRE.delta_Ring			= Ist_IBF.Schuessel.offset_ZEN * Ist_IBF.Schuessel.Flag_Zen_geoeffnet;
	Soll_IBF.ZER_Param.Kraft					= Soll_IBF.ZAR_Kraft_Vorgabe; // (Grenz-)Kraftvorgabe aus IBF_Data.ini. Gilt fuer beide ZA
	
	return ERR_OK;
};

int DR_Regler(	const  Def_Ist_Inter			&Ist_Inter,
				const  Def_IBF_Allgemein_IST	&Ist_IBF,
				struct Def_Soll_Inter			&Soll_Inter,
				struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	// Druckrolle Einlaufseite
	Soll_IBF.DRR_Param.DrR_E.V_DrR				= 100.0F;
	Soll_IBF.DRR_Param.DrR_E.act				= ACT_IBF;
	Soll_IBF.DRR_Param.DrR_E.mode				= DRR_MODE_KRAFT;
	Soll_IBF.DRR_Param.DrR_E.delta_Ring			= -1.0F;
	Soll_IBF.DRR_Param.DrR_E.Kraft				= Ist_IBF.Schuessel.F_Soll_DrR;

	// Druckrolle Auslaufseite
	Soll_IBF.DRR_Param.DrR_A.V_DrR				= 100.0F;
	Soll_IBF.DRR_Param.DrR_A.act				= ACT_IBF;
	Soll_IBF.DRR_Param.DrR_A.mode				= DRR_MODE_WEG;
	Soll_IBF.DRR_Param.DrR_A.delta_Ring			= Ist_IBF.DRR_Param.DrR_E.delta_Ring + Ist_IBF.Schuessel.offset_DrR_A;
	Soll_IBF.DRR_Param.DrR_A.Kraft				= Ist_IBF.Schuessel.F_Grenz_DrR;

	return ERR_OK;
};

int WA_Regler(	const  Def_Ist_Inter			&Ist_Inter,
				const  Def_IBF_Allgemein_IST	&Ist_IBF,
				struct Def_Soll_Inter			&Soll_Inter,
				struct Def_IBF_Allgemein_SOLL	&Soll_IBF)
{
	float	i_HW_Ring,
			i_Ring_AWU,
			i_Ring_AWO;
	
	// Bei den Drehzahlen sei zu beachten, dass Soll-Werte als Motor-Drehzahl [U/s] angegeben werden,
	// und Ist-Werte der Walzendrehzahl entsprechen!!!
	
	i_HW_Ring	= Ist_Inter.Werkzeug.Durchmesser_HW  / ( Ist_IBF.Schuessel.Walzform.RingGeo.b * 2.0F );
	i_Ring_AWO	= Ist_IBF.Schuessel.Walzform.r_eff_o / ( SIN_KWW_HALBE * ( Ist_IBF.Schuessel.Walzform.da_mf - Ist_IBF.AG_Pos ) );
	i_Ring_AWU	= Ist_IBF.Schuessel.Walzform.r_eff_u / ( SIN_KWW_HALBE * ( Ist_IBF.Schuessel.Walzform.da_mf - Ist_IBF.AG_Pos ) );
	
	Soll_Inter.hw_n		= Ist_IBF.Schuessel.n_HW *							Ist_Inter.hw_ir / (2.0F * PI);	
	Soll_Inter.kwo_n	= Ist_IBF.Schuessel.n_HW * i_HW_Ring * i_Ring_AWO * Ist_Inter.kw_ia / (2.0F * PI);
	Soll_Inter.kwu_n	= Ist_IBF.Schuessel.n_HW * i_HW_Ring * i_Ring_AWU * Ist_Inter.kw_ia / (2.0F * PI);

	return ERR_OK;
};

float sgn(float fi) { return (0.0F+(fi>0)-(fi<0)); };
