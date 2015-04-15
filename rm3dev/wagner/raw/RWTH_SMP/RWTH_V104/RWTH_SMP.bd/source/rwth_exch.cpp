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
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
/****************************************************************************/
/*  includes                                                                */
/****************************************************************************/
/* includes from outside the project */

#include "rmos_inc.h"

#define Powercon_Modul //muss in allen drei Projekten (RAW_SMP, TRT_SMP und
                       //RWTH_SMP) genau einmal definiert werden!

/* declarations from inside the project */
#include "rwth_task.hpp"
#include "ibf_tool.hpp"
#include "time.h"



/****************************************************************************/
// Konstruktor
/****************************************************************************/
RWTH_EXCH::RWTH_EXCH(void)
{

    //Initialisierung der IBF-Strukturen und einlesen von IBF_DATA.ini
    
    struct Def_Ist_Inter           Ist_Inter_Ini   = {0};
    struct Def_Soll_Inter          Soll_Inter_Ini  = {0};
    struct Def_IBF_Allgemein_SOLL  Soll_IBF_Ini    = {0};
    struct Def_IBF_Allgemein_IST   Ist_IBF_Ini     = {0};    

    //struct tm zeit ={0} ;
    time_t start, end;

   
   
    
    // Initialisierung der globalen IBF Strukturen
    iter_IBF = 0;    
    Ist_Inter  = Ist_Inter_Ini;
    Soll_Inter = Soll_Inter_Ini;
    Soll_IBF   = Soll_IBF_Ini; 
    Ist_IBF    = Ist_IBF_Ini;

    Soll_IBF.Profilflag   = -1;
    
    Soll_IBF.InitAchse    = 'a';
    //Soll_IBF.InitAchse    = 'v';
    
    // Wertevorgabe statischer IBF-Variablen, werden später in Funktion IstIBF_IstInter erneut eingelesen. 
    // Langfristig sollte geeignete Methode eingebunden werden, um Werte über Carwin-Maske vorgeben zu können. 20.07.2007 D.Michl
    
    // Winkel wird in nachfolgenden Funktionsaufrufen benötigt, dashalb hier bereits deklarieren
    Ist_IBF.Axial.Kr_geo.sin_kw_winkel_halbe = 0.3826834323650897717284599840304F;  // sin(22.5°)  
    
    
    ctime(&start);   // Starten des Timers mit dem die Zeit eines Funktionsaufrufes gemessen werden kann.

    //-----------------------------------------------------------------------------
    //----- Einlesen der IBF_Data.ini (entspricht der ipfpara auf dem MRAW)   -----
    //----- Datei liegt in dem smp16-Verzeichnis auf dem Windowsrechner       -----
    //----- und wird von der Sicomp-Einheit bei jedem Reset geladen.          -----
    //----- Ini-Datei darf nicht verändert werden, ohne dass diese Änderungen -----
    //----- hier im Quelltext übernommen werden!                              -----
    //-----------------------------------------------------------------------------
    MyLogFile <<"Gleich soll IBF_Data geöffnet werden...."<< endl ;
    if(!rpw->IBFPARA_auslesen(&Ist_IBF, &Soll_IBF))
        { 
            MyLogFile <<"konnte IBF_Data nicht öffnen"<< endl ;
        }
        else
        {
            MyLogFile <<"konnte IBF_Data öffnen"<< endl ;
        }

    ctime(&end);   // Stoppen des Timers, mit dem die Zeit eines Funktionsaufrufes gemessen wurde

    Ist_Inter.Systemzeit = difftime(end, start);    // Zeitdifferenz berechnen. Angabe in Sekunden

    // Funktionsaufrufe: hier IBF-Modul Flxibel axiales Profilieren (Funktionen stehen in der ibf_tool.cpp)
    
    rpw->Kr_Geo_berechnen(&Ist_IBF);
    rpw->Kr_Geo_pruefen(&Ist_IBF);

    // Funktionsaufrufe: Modus des Axialgerüstes
    rpw->Modus_AG(&Soll_Inter, &Ist_IBF, Ist_IBF.Flag.Axial_Radialwalzen);


    if (Ist_IBF.Flag.Axial_Radialwalzen != 0)
    {
    Soll_IBF.min_RS_Pos  = 10.0F; // minimale Wanddickeposition, die erreicht werden darf. Wert ist von Carwin-Vorgabe unabhängig
    Soll_IBF.min_ASO_Pos = 85.0F; // min. Ringhöhe, wenn mit Tastrollenerhöhung gearbeitet wird  ||107.0F -> Radialprofieren Aufsatz 1
    }
    else Soll_IBF.min_ASO_Pos = 25.0F;


    Soll_IBF.Zeit.t_Halte= 50;    // Sollwartezeit beim Anfahren

    MyLogFile << "Allgemeine Information" <<  endl;
    MyLogFile << "System hat " << Ist_Inter.Systemzeit * 1000.0 << " Sekunden benötigt, um Datei einzulesen" << endl;
    MyLogFile << "Minimale IBF-Wandposition (kann von der CARWIN-Wanddicke abweichen) " << Soll_IBF.min_RS_Pos << endl;
    MyLogFile << "Minimale Ringhöhe                                                   " << Soll_IBF.min_ASO_Pos << endl;
    MyLogFile << endl;
    MyLogFile << endl;

    //Kontrolle der eingelesenen IBF-Werte in LoggerFile
    
    MyLogFile << "Folgende Werte wurden aus IBF_Data gelesen und wie folgt zugeordnet" << endl;
    MyLogFile << endl;

    
    MyLogFile << "Abschalten nach SMS (0) oder IBF (1)" << ":" << " "<< Ist_IBF.Flag.IBF_Abschaltung << endl;
    MyLogFile << endl;
    MyLogFile << "Weg-Kraftschalter RS aktiv  [1=ja, 0=nein]" << ":" << " "<< Ist_IBF.Flag.rs_kraftregler_aktiv << endl;
    MyLogFile << "Weg-Kraftschalter AS aktiv  [1=ja, 0=nein]" << ":" << " "<< Ist_IBF.Flag.as_kraftregler_aktiv << endl;
    MyLogFile << "Weg-Kraftschalter AG aktiv  [1=ja, 0=nein]" << ":" << " "<< Ist_IBF.Flag.ag_kraftregler_aktiv << endl;
    MyLogFile << "Weg-Kraftschalter ZAL aktiv [1=ja, 0=nein]" << ":" << " "<< Ist_IBF.Flag.zal_kraftregler_aktiv << endl;
    MyLogFile << "Weg-Kraftschalter ZAR aktiv [1=ja, 0=nein]" << ":" << " "<< Ist_IBF.Flag.zar_kraftregler_aktiv << endl;
    MyLogFile << endl;

    MyLogFile << "RS_Kraftvorgabe "<< "= " << " "<< Soll_IBF.RS_Kraft_Vorgabe << " N" << endl;
    MyLogFile << "AS_Kraftvorgabe "<< "= " << " "<< Soll_IBF.AS_Kraft_Vorgabe << " N" << endl;
    MyLogFile << "AG_Kraftvorgabe "<< "= " << " "<< Soll_IBF.AG_Kraft_Vorgabe << " N" << endl;
    MyLogFile << "ZAL_Kraftvorgabe"<< "= " << " "<< Soll_IBF.ZAL_Kraft_Vorgabe <<" N" << endl;
    MyLogFile << "ZAR_Kraftvorgabe"<< "= " << " "<< Soll_IBF.ZAR_Kraft_Vorgabe <<" N" << endl;
    MyLogFile << endl;
    MyLogFile << endl;

    MyLogFile << "Anwalzen in Kraft" << endl;
    
    MyLogFile << "Dornwalze in Kraft beim Anwalzen [1=AN, 0=AUS]" << ":" << " "<< Ist_IBF.Flag.rs_kraftanfahren_aktiv << endl; // Schalter: Walzen mit Kraftsteuerung [1], Positionssteuereung [0] 
    if (Ist_IBF.Flag.rs_kraftanfahren_aktiv == 0 )
        MyLogFile << "Radiales Anwalzen in Kraft wurde nicht vorgewählt " << endl;
    else
        MyLogFile << "Radiales Anwalzen mit der Kraft FR" << "= " << " "<< Soll_IBF.RS_Kraft_Anfahren << " vorgewählt" <<endl;

    MyLogFile << endl;

    MyLogFile << "Kegelwalze in Kraft beim Anwalzen [1=AN, 0=AUS]" << ":" << " "<< Ist_IBF.Flag.as_kraftanfahren_aktiv << endl;
    if (Ist_IBF.Flag.as_kraftanfahren_aktiv == 0 )
        MyLogFile << "Axiales Anwalzen in Kraft wurde nicht vorgewählt" << endl;
    else
        MyLogFile << "Axiales Anwalzen mit der Kraft FA" << "= " << " "<< Soll_IBF.AS_Kraft_Anfahren << " vorgewählt" << endl;
    
    MyLogFile << endl;
    MyLogFile << endl;
    MyLogFile << endl;

    MyLogFile << "Auswahl des IBF-Modul:" ;
    if (Ist_IBF.Flag.Axial_Radialwalzen != 0)
    {
    MyLogFile << "***IBF - Flexibel radial Profilieren***" << endl;

        MyLogFile << "Vorschubsart " << ": " ;
        switch(Ist_IBF.Radial.Schalter_Kont_DisKo)
         { 

          case 0:   MyLogFile << "const. Vorschub (Schalterstellung = 0)" << endl;
                    break;
          case 1:   MyLogFile << "Epsilon/Weg (Schalterstellung = 1) " << endl;
                    MyLogFile << "Vorgabe des Epsilon " << "= " << Soll_IBF.Radial.eps_Vorschub << endl;
                    break;
          case 2:   MyLogFile << "Walzspaltverhälnis (Schalterstellung = 2)" << endl;
                    MyLogFile << "Für Cr wurde " << Soll_IBF.Radial.Walzspalt_Cr << " vorgegeben " << endl;
                    break;
          }

         MyLogFile << endl;
    
         MyLogFile << "Profilierwerkzeugbreite       " << "= " << Ist_IBF.Radial.Werkzeugbreite << endl;     
         MyLogFile << "const.Vorschubgeschwindigkeit " << "= " << Soll_IBF.Radial.Vorschubgeschw_Dw << endl ;
        if(Soll_IBF.Radial.delta_s != 0.0F && Soll_IBF.Radial.Stegstaerke != 0.0F)
        {   
            MyLogFile << endl;
            MyLogFile << "ACHTUNG !!!  Vorgabe von Soll-Stegstärke und Delta_s unzulässig! " << "=> Delta_s wurde Null gesetzt " << endl;
            Soll_IBF.Radial.delta_s     = 0.0;

            MyLogFile << "Soll-Stegstärke               " << "= "<< Soll_IBF.Radial.Stegstaerke  << endl ;
            MyLogFile << "Delta_s                       " << "= "<< Soll_IBF.Radial.delta_s << endl;
            MyLogFile << endl;
        }

        else if(Soll_IBF.Radial.delta_s == 0.0F && Soll_IBF.Radial.Stegstaerke == 0.0F)
           {
            MyLogFile << endl;
            MyLogFile << "ACHTUNG !!!  Soll-Stegstärke und Delta_s beide NULL ist unzulässig! "  << endl;
            Soll_IBF.Radial.delta_s     = 0.0;
            Soll_IBF.Radial.Stegstaerke  = 40.0F;

            MyLogFile << "Soll-Stegstärke (DEFAULT-Wert)" << "= "<< Soll_IBF.Radial.Stegstaerke  << endl ;
            MyLogFile << "Delta_s                       " << "= "<< Soll_IBF.Radial.delta_s << endl;
            MyLogFile << endl;
           }
       else
           {
            MyLogFile << "Soll-Stegstärke               " << "= " << Soll_IBF.Radial.Stegstaerke << endl ;
            MyLogFile << "Delta_s                       " << "= " << Soll_IBF.Radial.delta_s << endl;
           }
    
        MyLogFile << endl;
        MyLogFile << endl;
        MyLogFile << "Anzahl der Umdrehungen in der Rundungsphase" << "= " << Soll_IBF.Radial.Umdrehungen << endl;
        MyLogFile << endl;
        MyLogFile << "Rohlingshöhe" << "= " << Soll_IBF.Radial.Rohlinghoehe << endl;
        MyLogFile << endl;
        MyLogFile << "Vorchubgeschwindigkeit Axialschlitten (nur im case 17)" << "= " << Soll_IBF.Radial.Vorschubgeschw_ASO << endl;
        MyLogFile << endl;
     } //endif (Ist_IBF.Flag.Axial_Radialwalzen != 0)

    else
     {
     MyLogFile << "***IBF - Flexibel axial Profilieren***" << endl;

     MyLogFile << " Kragenbreite                                "   << "= " << Ist_IBF.Axial.Kr_geo.Kr_Br               << endl; 
     MyLogFile << " Kragendurchmesser vordere Kante             "   << "= " << Ist_IBF.Axial.Kr_geo.Kr_d_nenn_vorne     << endl;
     MyLogFile << " berechneter Nenndurchmesser Kragenmittelpkt."   << "= " << Ist_IBF.Axial.Kr_geo.Kr_d_nenn_mitte     << endl;
     MyLogFile << " Kragendurchmesser vordere Kante             "   << "= " << Ist_IBF.Axial.Kr_geo.Kr_d_nenn_hinten    << endl;
     MyLogFile << " berechneter Abstand Del_Kr_Br               "   << "= " << Ist_IBF.Axial.Kr_geo.Del_Kr_AGR          << endl;
     MyLogFile << " max. Profilierungstiefe                     "   << "= " << Ist_IBF.Axial.Kr_geo.max_Pr_Tiefe        << endl;
     MyLogFile << " Anfahrdurchmesser                           "   << "= " << Ist_IBF.Axial.Anfahrdurchm               << endl;
     MyLogFile << " Zustellgeschwindigkeit des Axialschlittens  "   << "= " << Ist_IBF.Axial.Vorschub      <<" [mm/U]"  << endl;
    
     MyLogFile << " Anzahl der Profile                          "   << "= " << Ist_IBF.Axial.Profilanzahl               << endl;
     for (int i=0; i< Ist_IBF.Axial.Profilanzahl; i++)
     {
     MyLogFile <<  i+1 << ". Profilierposition                   "  << "= " << Ist_IBF.Axial.AGR_Pr[i]                  << endl;
     MyLogFile <<  i+1 << ". Profiliertiefe                      "  << "= " << Ist_IBF.Axial.Pr_Tiefe[i]                << endl;     
     }
     MyLogFile <<  endl;
     MyLogFile << " Minimale Walzhöhe ist vorgegeben mit"           << "= " << Soll_IBF.min_ASO_Pos                     << endl;
     MyLogFile << " Soll_Inter.ag_mode"                             << "= " << Soll_Inter.ag_mode                       << endl;
     }

     if(Ist_IBF.Test.Flag == 1)
     {
     MyLogFile << "***IBF - Testwalzungen vorgewählt !!!***"          << endl;

     MyLogFile << " Simulierter Ringdurchmesser                   "   << "= " << Ist_IBF.Test.Ring_AD               << endl; 
     
     }
     
                                          



    


    
    //-----------------------------------------------------------------------
    //-------------             SMS-Code                                -----
    //-----------------------------------------------------------------------

    running_flag = TRUE;
    finish_flag = FALSE;

    Blinker = 0;



    if(RmGetEntry(RM_SECOND(15), Mailboxl, &Entry) == RM_GOT_TIMEOUT)
    {
        cout << "Mailbox " << Mailboxl << " nicht vorhanden!  CNC Task gestartet ?" << endl;
        MyLogFile << "Mailbox " << Mailboxl << " nicht vorhanden!  CNC Task gestartet ?" << endl;
        running_flag = FALSE;
    }
    else
    {
        TRT_Mail_id = Entry.id;

        if(RmGetEntry(RM_SECOND(1), Powercon_SendSema, &Entry) == RM_GOT_TIMEOUT)
        {
            cout << "Semaphor " << Powercon_SendSema << " nicht vorhanden!" << endl;
            MyLogFile << "Semaphor " << Powercon_SendSema << " nicht vorhanden!" << endl;
            running_flag = FALSE;
        }
        else
        {
            Sema_PowerSendID = Entry.id;    //Senden gilt für die CNC Seite, TRT empfängt!

            if(RmGetEntry(RM_SECOND(1), Powercon_RecSema, &Entry) == RM_GOT_TIMEOUT)
            {
                cout << "Semaphor " << Powercon_RecSema << " nicht vorhanden!" << endl;
                MyLogFile << "Semaphor " << Powercon_RecSema << " nicht vorhanden!" << endl;
                running_flag = FALSE;
            }
            else
            {
                Sema_PowerRecID = Entry.id; //Receive gilt für die CNC Seite, TRT sendet!

                if(RmReceiveMail(RM_SECOND(1), TRT_Mail_id, &TRT_Mail) == RM_GOT_TIMEOUT)
                {
                    cout << "Keine Mail empfangen!" << endl;
                    MyLogFile << "Keine Mail empfangen!" << endl;
                    running_flag = FALSE;
                }
                else
                {
                    RwwtPool = (RwwtPool_tag *)TRT_Mail.adr;
                    if(TRT_Mail.len != sizeof(RwwtPool_tag))
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
    if(running_flag == TRUE)
        RwwtPool->Steuer_RWTH = TRT_Finished;

    running_flag = FALSE;
}

/****************************************************************************/
// Memorypool belegen (aus_puff und aus_onli) 
/****************************************************************************/
int RWTH_EXCH::put_puff(void)
{
    if(running_flag && RwwtPool->Data_initialed && RwwtPool->Data_available)
    {
        if(RmGetBinSemaphore(RM_MILLISECOND(25), Sema_PowerRecID) == RM_GOT_TIMEOUT)
          return(FALSE);

        RwwtPool->ein_puff_RWTH   = ein_puff;
        RwwtPool->ein_onli_RWTH   = ein_onli;
        RwwtPool->aus_puff_RWTH   = aus_puff;
        RwwtPool->aus_onli_RWTH   = aus_onli;

        RwwtPool->Status_RWTH = TRT_fertig | Blinker;
        RwwtPool->Data_availableRWTH = TRUE;

        RmReleaseBinSemaphore(Sema_PowerRecID);

        TestCounter[1]++;
    }
    return(TRUE);
}


/****************************************************************************/
// Memorypool auf lokale Strukturen kopieren (ein_puff, ein_onli)
/****************************************************************************/
int RWTH_EXCH::get_puff(void)
{
    if(running_flag)
    {
        if(RwwtPool->Steuer_RWTH == TRT_Stop)
            finish_flag = TRUE;
    }
    if(running_flag && RwwtPool->Data_initialed && RwwtPool->Data_available)
    {
        RwwtPool->Status_RWTH = TRT_neustart | Blinker;

        if(RmGetBinSemaphore(RM_MILLISECOND(25), Sema_PowerRecID) == RM_GOT_TIMEOUT)
          return(FALSE);

        ein_puff   = RwwtPool->ein_puff_back;
        ein_onli   = RwwtPool->ein_onli_back;
        aus_puff   = RwwtPool->aus_puff;
        aus_onli   = RwwtPool->aus_onli;
        lokal_puff = RwwtPool->lokal_puff;

        RmReleaseBinSemaphore(Sema_PowerRecID);

        TestCounter[2]++;
    }
    return(TRUE);
}

/****************************************************************************/
// IBF Algorithmen aufrufen 
/****************************************************************************/
int RWTH_EXCH::Main_Control(void)
{
   if(running_flag && RwwtPool->Data_initialed && RwwtPool->Data_available)
   {
      if(++CountBlinker > 10)
      {
         CountBlinker = 0;
         Blinker ^= TRT_Blinker;
      }
      RwwtPool->Status_RWTH = TRT_laeuft | Blinker;


      //***********************************************************************
      // ==> Hier können eigene Methoden aufgerufen werden ! <==
      //***********************************************************************

#ifdef debye
      //die folgenden Zeilen nur zum Test!
      TestCounter[0]++;
      
      //Test: aus_puff wird verändert
      aus_puff.istanz_ru = TestCounter[0];  //Nur Test, muss entfernt werden! durch ifdef wurde dies entfernt/ausgeschaltet
      
      //Test: Laufzeit wird verlängert
      for(int i = 0; i < 30; i++)           //Nur Test, muss entfernt werden!
         RmPauseTask(RM_MILLISECOND(2));   //Nur Test, muss entfernt werden!
#endif
     time_t start, end;
    //jeweils zum Walzenstart (Walzenstartflag) müssen einige Variablen vordefiniert werden, damit richtige CASE-Anweisungen im rpw.cpp (IBF-Modul) ausgeführt werden
      if (ein_puff.walzenstart_flag)
      {
        ctime(&start); 
        Ist_IBF.StartPos      = 1;
         
         Soll_IBF.Profilflag   = -1;
         //Soll_IBF.InitAchse    = 'v';
         Soll_IBF.InitAchse    = 'a';
         Soll_IBF.ExitAchse    = 'a';
         Soll_IBF.Zeit.t_Halte= 50;    // Sollwartezeit beim Anfahren
         Soll_IBF.Axial.Pr_Num = 0;

         rpw->Modus_AG(&Soll_Inter, &Ist_IBF, Ist_IBF.Flag.Axial_Radialwalzen); //Setzen des AG-Modus Soll_Inter.ag_mode, notwendig wenn im vorherigen Zyklus Funktion Abschalten aufgerufen wurde
        
         
         iter_IBF              = 0;

         rpw->Main_RAW( iter_IBF,
                        ein_puff,
                        lokal_puff,
                        aus_puff,
                        ein_onli,
                        aus_onli,
                        &Ist_Inter,
                        &Soll_Inter,
                        &Soll_IBF,
                        &Ist_IBF);
        ctime(&end);
        Ist_Inter.Systemzeit = difftime(end, start);    // Zeitdifferenz berechnen. Angabe in Sekunden

        
      }
      else
      {
        ctime(&start);
        iter_IBF++;

         rpw->Main_RAW( iter_IBF,
                        ein_puff,
                        lokal_puff,
                        aus_puff,
                        ein_onli,
                        aus_onli,
                        &Ist_Inter,
                        &Soll_Inter,
                        &Soll_IBF,
                        &Ist_IBF);

         ctime(&end);
         Ist_Inter.Systemzeit = difftime(end, start);    // Zeitdifferenz berechnen. Angabe in Sekunden

      }
      
      // Zuweisungen für die Steuerung 

      /* zu setzende Flags mit denen IBF-Positionsvorgaben gültig werden */

      aus_onli.Ibf_nominal.RS_act  = 1;                     // Flag Sollwerte Radialschlitten von Ibf auswertbar 1, nicht auswertbar 0
      aus_onli.Ibf_nominal.AS_act  = 1;                     // Flag Sollwerte Axialschlitten von Ibf auswertbar
      aus_onli.Ibf_nominal.Zen_act = 0;                     // in IBF_struct zu definierende Variable oder hier mit 1 konstant aktivieren;    //Flag Sollwerte Zentrierarme von Ibf auswertbar
      aus_onli.Ibf_nominal.AG_act  = Soll_Inter.ag_act;     // in IBF_struct zu definierende Variable oder hier mit 1 konstant aktivieren;     //Flag Sollwerte Axialgerüst von Ibf auswertbar
                                     
      /* Schalter Kraftregler */
      aus_onli.Ibf_nominal.RS_mode  = Soll_Inter.rs_mode;                   // Betriebsart Vorschub (0) oder Kraftregelung (1)
      aus_onli.Ibf_nominal.AS_mode  = Soll_Inter.aso_mode;                  // Betriebsart Vorschub (0) oder Kraftregelung (1)
      aus_onli.Ibf_nominal.AG_mode = Soll_Inter.ag_mode;                   // Soll_Inter.ag_kraftregler_aktiv;     //Betiebsart Vorschub (0) oder Kraftregelung (1)
      aus_onli.Ibf_nominal.Zen_mode = Soll_Inter.zar_kraftregler_aktiv;     //!!! Betriebsart für beide Arme !!! Betiebsart Vorschub (0) oder Kraftregelung (1) 

      /* Zustellgeschwindigkeiten */
      aus_onli.ds_dh_sp_hp.s_punkt = Soll_Inter.rs_v  * ein_onli.rwg_poti_wert; /*Radialschlitten     	             [mm/s]*/
      aus_onli.ds_dh_sp_hp.h_punkt = Soll_Inter.aso_v * ein_onli.rwg_poti_wert; /*Axialschlitten oben                [mm/s]*/
      aus_onli.Ibf_nominal.Soll_AG_V = Soll_Inter.ag_v; //= -5.0F;              /* Axialgeruest                      [mm/s]*/
      aus_onli.Ibf_nominal.Soll_ZA_V = Soll_Inter.zal_v;                        /* Zentrierarm links                 [mm/s]*/
      aus_onli.Ibf_nominal.Soll_ZE_V = Soll_Inter.zar_v;                        /* Zentrierarm rechts                [mm/s]*/
      
      /* Sollpositionen */
      aus_onli.Ibf_nominal.Soll_RS_Pos = Soll_Inter.rs_pos;          /* Radialschlitten                        [mm]*/
      aus_onli.Ibf_nominal.Soll_AS_Pos = Soll_Inter.aso_pos;         /* Axialschlitten oben                    [mm]*/
      aus_onli.Ibf_nominal.Soll_AG_Pos = Soll_Inter.ag_pos;          /* Axialschlitten                         [mm]*/
      
      /* Übergabe und Art der Zentrierung überprüfen */
      aus_onli.Ibf_nominal.Soll_ZA_Pos = Soll_Inter.zar_pos ;         /* Zentrierarm rechts Auslauf             [mm]*/ 
      aus_onli.Ibf_nominal.Soll_ZE_Pos = Soll_Inter.zal_pos ;         /* Zentrierarm links Einlauf              [mm]*/ 
      		 	
      /* Drehzahlen */
      //Soll_Inter.hw_n;                                             /* Hauptwalze 			               	[1/min]*/
      aus_puff.n_omega.n_aw_motor_g_o = Soll_Inter.kwo_n; //* MIN_FAK;  /* Kegelwalze oben                     [1/min]*/
      aus_puff.n_omega.n_aw_motor_g_u = Soll_Inter.kwu_n; // * MIN_FAK;  /* Kegelwalze unten                    [1/min]*/
      
      /* Schrittnummer */
      // Soll_Inter.schritt_nr;			

      /* Sollkräfte */
      aus_onli.Ibf_nominal.Soll_FR  = Soll_Inter.rs_kraft;           /* Radialkraft [N] */
      aus_onli.Ibf_nominal.Soll_FA  = Soll_Inter.aso_kraft;          /* Axialkraft  [N] */   
      aus_onli.Ibf_nominal.Soll_FAG = Soll_Inter.ag_kraft;           /* Axialgerüst [N] */
      aus_onli.Ibf_nominal.Soll_FZ  = Soll_Inter.zal_kraft;          /* Zentrierarme[N]*/
      
      //Soll_Inter.zal_kraft = Soll_IBF->ZAR_Kraft;
      //Soll_Inter->zar_kraft = Soll_IBF->ZAL_Kraft;
      // Soll_Inter.zal_kraft;                                      /*Zentirerkarft derzeit nur eine Variable für beide Zentirerarme möglich. 060718, Michl*/
      // Soll_Inter.zar_kraft;
    }
    
    return(TRUE);
}

int In_RWTH_LOG_Schreiben(char *buffer)
{
     MyLogFile << buffer << endl;

     return TRUE;
}
