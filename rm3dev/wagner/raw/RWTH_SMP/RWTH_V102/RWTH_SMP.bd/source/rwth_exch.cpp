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



/****************************************************************************/
// Konstruktor
/****************************************************************************/
RWTH_EXCH::RWTH_EXCH(void)
{

    //int i; //derzeit nur Hilfsfunktion f�r INIFileTest -> definition der IBF_PARA
    
    struct Def_Ist_Inter           Ist_Inter_Ini   = {0};
    struct Def_Soll_Inter          Soll_Inter_Ini  = {0};
    struct Def_IBF_Allgemein_SOLL  Soll_IBF_Ini    = {0};
    struct Def_IBF_Allgemein_IST   Ist_IBF_Ini     = {0};    

    
    // Initialisierung der globalen IBF Strukturen
    iter_IBF = 0;    
    Ist_Inter  = Ist_Inter_Ini;
    Soll_Inter = Soll_Inter_Ini;
    Soll_IBF   = Soll_IBF_Ini; 
    Ist_IBF    = Ist_IBF_Ini;

    Soll_IBF.Profilflag   = -1;
    
    Soll_IBF.InitAchse    = 'a';
    //Soll_IBF.InitAchse    = 'v';
    
    Soll_Inter.ag_mode = 0; // Axialger�st f�hrt beim Anfahren auf die SMS vorgegebene Position
    Soll_Inter.ag_act  = 1;
   


    //-----------------------------------------------------------------------------
    //----- Einlesen der IBF_Data.ini (entspricht der ipfpara auf dem MRAW)   -----
    //----- Datei liegt in dem smp16-Verzeichnis auf dem Windowsrechner       -----
    //----- und wird von der Sicomp-Einheit bei jedem Reset geladen.          -----
    //----- Ini-Datei darf nicht ver�ndert werden, ohne dass diese �nderungen -----
    //----- hier im Quelltext �bernommen werden!                              -----
    //-----------------------------------------------------------------------------
    
    // �ffnen der IBF_DATA um vorgegebene Werte einzulesen
    CIniFile iniFile( "IBF_Data.ini");
         if(!iniFile.ReadFile()) //Fehlerbehandlung
           { 
            MyLogFile <<"konnte IBF_Data nicht �ffnen"<< endl ;
           }
         else 
           {
            MyLogFile << "----------------------"<< endl;
            MyLogFile << "IBF_Data wurde ge�ffnet"<< endl;
            
            //Einlesen der Sxhl�sselidentifikation
            iniFile.NumValues( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)"); 
            //Einlesen der Werte unterhalb der Schl�ssel-ID, wenn Wert nicht vorhanden wird DEFAULT-Wert verwendet
            Ist_IBF.Flag.rs_kraftregler_aktiv  = iniFile.GetValueI( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)", "Schalter_RS_Kraft_Weg", 0);
            Ist_IBF.Flag.as_kraftregler_aktiv  = iniFile.GetValueI( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)", "Schalter_AS_Kraft_Weg", 0);
            Ist_IBF.Flag.ag_kraftregler_aktiv  = iniFile.GetValueI( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)", "Schalter_AG_Kraft_Weg", 0);
            Ist_IBF.Flag.zal_kraftregler_aktiv = iniFile.GetValueI( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)", "Schalter_ZAL_Kraft_Weg", 0);
            Ist_IBF.Flag.zar_kraftregler_aktiv = iniFile.GetValueI( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)", "Schalter_ZAR_Kraft_Weg", 0);

            iniFile.NumValues( "IBF_Vorgabe Kraft"); 
            Soll_IBF.RS_Kraft_Vorgabe  = iniFile.GetValueF( "IBF_Vorgabe Kraft", "RS_Kraftvorgabe", 80000.0);
            Soll_IBF.AS_Kraft_Vorgabe  = iniFile.GetValueF( "IBF_Vorgabe Kraft", "AS_Kraftvorgabe", 60000.0);
            Soll_IBF.AG_Kraft_Vorgabe  = iniFile.GetValueF( "IBF_Vorgabe Kraft", "AG_Kraftvorgabe", 5000.0);
            Soll_IBF.ZAL_Kraft_Vorgabe = iniFile.GetValueF( "IBF_Vorgabe Kraft", "ZAL_Kraftvorgabe", 2000.0);
            Soll_IBF.ZAR_Kraft_Vorgabe = iniFile.GetValueF( "IBF_Vorgabe Kraft", "ZAR_Kraftvorgabe", 2000.0);

            iniFile.NumValues( "IBF_Wahlschalter Anwalzen in Kraft"); 
            Ist_IBF.Flag.rs_kraftanfahren_aktiv = iniFile.GetValueI( "IBF_Wahlschalter Anwalzen in Kraft", "Schalter_Wanddicke", 0);
            Ist_IBF.Flag.as_kraftanfahren_aktiv = iniFile.GetValueI( "IBF_Wahlschalter Anwalzen in Kraft", "Schalter_Ringhoehe", 0);
           
            iniFile.NumValues( "IBF_Vorgabe Anwalzkraft"); 
            Soll_IBF.RS_Kraft_Anfahren = iniFile.GetValueF( "IBF_Vorgabe Anwalzkraft", "RS_Kraft_Anfahren", 1000.0);
            Soll_IBF.AS_Kraft_Anfahren = iniFile.GetValueF( "IBF_Vorgabe Anwalzkraft", "AS_Kraft_Anfahren", 1000.0);

            iniFile.NumValues ("IBF-Variablen Radialprofilieren");
            Ist_IBF.Radial.Schalter_Kont_DisKo = iniFile.GetValueI( "IBF-Variablen Radialprofilieren", "Vorschubsart (0->const_Vorschub 1->Epsilon/Weg 2->mit Walzspaltverh�ltnis Cr)", 0);
            Ist_IBF.Radial.Werkzeugbreite      = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Profilierwerkzeugbreite", 10.0);   
            Soll_IBF.Radial.Vorschubgeschw_Dw  = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "const.Vorschubgeschwindigkeit", 0.0);   
            Soll_IBF.Radial.Stegstaerke        = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Endstegstaerke", 0.0);
            Soll_IBF.Radial.delta_s            = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "delta_s", 0.0);
            Soll_IBF.Radial.Umdrehungen        = iniFile.GetValueI( "IBF-Variablen Radialprofilieren", "Umdrehungen in Rundungsphase", 0);
            Soll_IBF.Radial.eps_Vorschub       = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Espilon f�r Auswahl 'Epsilon/Weg'", 0);
            Soll_IBF.Radial.Walzspalt_Cr       = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Walzspaltverh�ltnis Cr", 0);
            Soll_IBF.Radial.Rohlinghoehe       = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Rohlinghoehe", 100);
            Soll_IBF.Radial.Vorschubgeschw_ASO = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Vorschubgeschw._ASO", 5.0);

            
            }        
    Soll_IBF.min_RS_Pos  = 10.0F; // minimale Wanddickeposition, die erreicht werden darf. Wert ist von Carwin-Vorgabe unabh�ngig
    Soll_IBF.min_ASO_Pos = 85.0F; // min. Ringh�he, wenn mit Tastrollenerh�hung gearbeitet wird  ||107.0F -> Radialprofieren Aufsatz 1

    MyLogFile << "Allgemeine Information" <<  endl;
    MyLogFile << "Minimale IBF-Wandposition (kann von der CARWIN-Wanddicke abweichen) " << Soll_IBF.min_RS_Pos << endl;
    MyLogFile << "Minimale Ringh�ge                                                   " << Soll_IBF.min_ASO_Pos << endl;
    MyLogFile << endl;
    MyLogFile << endl;

    //Kontrolle der eingelesenen IBF-Werte in LoggerFile
    
    MyLogFile << "Folgende Werte wurden aus IBF_Data gelesen und wie folgt zugeordnet" << endl;
    MyLogFile << endl;
    
    MyLogFile << "Weg-Kraftschalter RS aktiv  [1=ja, 0=nein]" << ":" << " "<< Ist_IBF.Flag.rs_kraftregler_aktiv << endl;
    MyLogFile << "Weg-Kraftschalter AS aktiv  [1=ja, 0=nein]" << ":" << " "<< Ist_IBF.Flag.as_kraftregler_aktiv << endl;
    MyLogFile << "Weg-Kraftschalter AG aktiv  [1=ja, 0=nein]" << ":" << " "<< Ist_IBF.Flag.ag_kraftregler_aktiv << endl;
    MyLogFile << "Weg-Kraftschalter ZAL aktiv [1=ja, 0=nein]" << ":" << " "<< Ist_IBF.Flag.zal_kraftregler_aktiv << endl;
    MyLogFile << "Weg-Kraftschalter ZAR aktiv [1=ja, 0=nein]" << ":" << " "<< Ist_IBF.Flag.zar_kraftregler_aktiv << endl;
    MyLogFile << endl;

    MyLogFile << "RS_Kraftvorgabe "<< "= " << " "<< Soll_IBF.RS_Kraft_Vorgabe << " N" << "!! DERZEIT ALLE KRAFTVORGABEN NOCH DEFAULT !!!!" <<endl;
    MyLogFile << "AS_Kraftvorgabe "<< "= " << " "<< Soll_IBF.AS_Kraft_Vorgabe << " N" << endl;
    MyLogFile << "AG_Kraftvorgabe "<< "= " << " "<< Soll_IBF.AG_Kraft_Vorgabe << " N" << endl;
    MyLogFile << "ZAL_Kraftvorgabe"<< "= " << " "<< Soll_IBF.ZAL_Kraft_Vorgabe <<" N" << endl;
    MyLogFile << "ZAR_Kraftvorgabe"<< "= " << " "<< Soll_IBF.ZAR_Kraft_Vorgabe <<" N" << endl;
    MyLogFile << endl;
    MyLogFile << endl;

    MyLogFile << "Anwalzen in Kraft" << endl;
    
    MyLogFile << "Dornwalze in Kraft beim Anwalzen [1=AN, 0=AUS]" << ":" << " "<< Ist_IBF.Flag.rs_kraftanfahren_aktiv << endl; // Schalter: Walzen mit Kraftsteuerung [1], Positionssteuereung [0] 
    if (Ist_IBF.Flag.rs_kraftanfahren_aktiv == 0 )
        MyLogFile << "Radiales Anwalzen in Kraft wurde nicht vorgew�hlt " << endl;
    else
        MyLogFile << "Radiales Anwalzen mit der Kraft FR" << "= " << " "<< Soll_IBF.RS_Kraft_Anfahren << " vorgew�hlt" <<endl;

    MyLogFile << endl;

    MyLogFile << "Kegelwalze in Kraft beim Anwalzen [1=AN, 0=AUS]" << ":" << " "<< Ist_IBF.Flag.as_kraftanfahren_aktiv << endl;
    if (Ist_IBF.Flag.as_kraftanfahren_aktiv == 0 )
        MyLogFile << "Axiales Anwalzen in Kraft wurde nicht vorgew�hlt" << endl;
    else
        MyLogFile << "Axiales Anwalzen mit der Kraft FA" << "= " << " "<< Soll_IBF.AS_Kraft_Anfahren << " vorgew�hlt" << endl;
    
    MyLogFile << endl;
    MyLogFile << endl;
    MyLogFile << endl;



    MyLogFile << "Vorschubsart " << ": " ;
    switch(Ist_IBF.Radial.Schalter_Kont_DisKo)
         { 

          case 0:   MyLogFile << "const. Vorschub (Schalterstellung = 0)" << endl;
                    break;
          case 1:   MyLogFile << "Epsilon/Weg (Schalterstellung = 1) " << endl;
                    MyLogFile << "Vorgabe des Epsilon " << "= " << Soll_IBF.Radial.eps_Vorschub << endl;
                    break;
          case 2:   MyLogFile << "Walzspaltverh�lnis (Schalterstellung = 2)" << endl;
                    MyLogFile << "F�r Cr wurde " << Soll_IBF.Radial.Walzspalt_Cr << " vorgegeben " << endl;
                    break;
          }

     MyLogFile << endl;

     MyLogFile << "Profilierwerkzeugbreite       " << "= " << Ist_IBF.Radial.Werkzeugbreite << endl;     
     MyLogFile << "const.Vorschubgeschwindigkeit " << "= " << Soll_IBF.Radial.Vorschubgeschw_Dw << endl ;
     if(Soll_IBF.Radial.delta_s != 0.0F && Soll_IBF.Radial.Stegstaerke != 0.0F)
        {   
            MyLogFile << endl;
            MyLogFile << "ACHTUNG !!!  Vorgabe von Soll-Stegst�rke und Delta_s unzul�ssig! " << "=> Delta_s wurde Null gesetzt " << endl;
            Soll_IBF.Radial.delta_s     = 0.0;

            MyLogFile << "Soll-Stegst�rke               " << "= "<< Soll_IBF.Radial.Stegstaerke  << endl ;
            MyLogFile << "Delta_s                       " << "= "<< Soll_IBF.Radial.delta_s << endl;
            MyLogFile << endl;
        }

     else if(Soll_IBF.Radial.delta_s == 0.0F && Soll_IBF.Radial.Stegstaerke == 0.0F)
           {
            MyLogFile << endl;
            MyLogFile << "ACHTUNG !!!  Soll-Stegst�rke und Delta_s beide NULL ist unzul�ssig! "  << endl;
            Soll_IBF.Radial.delta_s     = 0.0;
            Soll_IBF.Radial.Stegstaerke  = 40.0F;

            MyLogFile << "Soll-Stegst�rke (DEFAULT-Wert)" << "= "<< Soll_IBF.Radial.Stegstaerke  << endl ;
            MyLogFile << "Delta_s                       " << "= "<< Soll_IBF.Radial.delta_s << endl;
            MyLogFile << endl;
           }

    else

        {
            MyLogFile << "Soll-Stegst�rke               " << "= " << Soll_IBF.Radial.Stegstaerke << endl ;
            MyLogFile << "Delta_s                       " << "= " << Soll_IBF.Radial.delta_s << endl;
        }

     MyLogFile << endl;
     MyLogFile << endl;
     MyLogFile << "Anzahl der Umdrehungen in der Rundungsphase" << "= " << Soll_IBF.Radial.Umdrehungen << endl;
     MyLogFile << endl;
     MyLogFile << "Rohlingsh�he" << "= " << Soll_IBF.Radial.Rohlinghoehe << endl;
     MyLogFile << endl;
     MyLogFile << "Vorchubgeschwindigkeit Axialschlitten (nur im case 17)" << "= " << Soll_IBF.Radial.Vorschubgeschw_ASO << endl;
     MyLogFile << endl;
     
     

                                                              



    


    
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
            Sema_PowerSendID = Entry.id;    //Senden gilt f�r die CNC Seite, TRT empf�ngt!

            if(RmGetEntry(RM_SECOND(1), Powercon_RecSema, &Entry) == RM_GOT_TIMEOUT)
            {
                cout << "Semaphor " << Powercon_RecSema << " nicht vorhanden!" << endl;
                MyLogFile << "Semaphor " << Powercon_RecSema << " nicht vorhanden!" << endl;
                running_flag = FALSE;
            }
            else
            {
                Sema_PowerRecID = Entry.id; //Receive gilt f�r die CNC Seite, TRT sendet!

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
      // ==> Hier k�nnen eigene Methoden aufgerufen werden ! <==
      //***********************************************************************

#ifdef debye
      //die folgenden Zeilen nur zum Test!
      TestCounter[0]++;
      
      //Test: aus_puff wird ver�ndert
      aus_puff.istanz_ru = TestCounter[0];  //Nur Test, muss entfernt werden! durch ifdef wurde dies entfernt/ausgeschaltet
      
      //Test: Laufzeit wird verl�ngert
      for(int i = 0; i < 30; i++)           //Nur Test, muss entfernt werden!
         RmPauseTask(RM_MILLISECOND(2));   //Nur Test, muss entfernt werden!
#endif

    //jeweils zum Walzenstart (Walzenstartflag) m�ssen einige Variablen vordefiniert werden, damit richtige CASE-Anweisungen im rpw.cpp (IBF-Modul) ausgef�hrt werden
      if (ein_puff.walzenstart_flag)
      {
         Ist_IBF.AUTO          = 1;
         Ist_IBF.StartPos      = 1;
         
         Soll_IBF.Profilflag   = -1;
         //Soll_IBF.InitAchse    = 'v';
         Soll_IBF.InitAchse    = 'a';
         Soll_IBF.ExitAchse    = 'a';
         Soll_Inter.ag_mode    = 0;   // Axialger�st f�hrt beim Anfahren auf die SMS vorgegebene Position
         Soll_Inter.ag_act     = 1;

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
        
      }
      else
      {
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
      }
      
      // Zuweisungen f�r die Steuerung 

      /* zu setzende Flags mit denen IBF-Positionsvorgaben g�ltig werden */

      aus_onli.Ibf_nominal.RS_act  = 1;     //Flag Sollwerte Radialschlitten von Ibf auswertbar 1, nicht auswertbar 0
      aus_onli.Ibf_nominal.AS_act  = 1;     //Flag Sollwerte Axialschlitten von Ibf auswertbar
      aus_onli.Ibf_nominal.Zen_act = 0;    //in IBF_struct zu definierende Variable oder hier mit 1 konstant aktivieren;    //Flag Sollwerte Zentrierarme von Ibf auswertbar
      aus_onli.Ibf_nominal.AG_act  = Soll_Inter.ag_act;     //in IBF_struct zu definierende Variable oder hier mit 1 konstant aktivieren;     //Flag Sollwerte Axialger�st von Ibf auswertbar
                                     
      /* Schalter Kraftregler */
      if(Ist_IBF.Flag.rs_kraftanfahren_aktiv == 1)
        {
            aus_onli.Ibf_nominal.RS_mode  = 1;
        }
      else  aus_onli.Ibf_nominal.RS_mode  = Soll_Inter.rs_kraftregler_aktiv ;     // Betiebsart Vorschub (0) oder Kraftregelung (1)

      if(Ist_IBF.Flag.as_kraftanfahren_aktiv == 1)
        {
           aus_onli.Ibf_nominal.AS_mode  = 1;    
        }
      else aus_onli.Ibf_nominal.AS_mode  = Soll_Inter.aso_kraftregler_aktiv;     // Betiebsart Vorschub (0) oder Kraftregelung (1)
      

      aus_onli.Ibf_nominal.AG_mode  = Soll_Inter.ag_mode;                   // Soll_Inter.ag_kraftregler_aktiv;     //Betiebsart Vorschub (0) oder Kraftregelung (1)
      aus_onli.Ibf_nominal.Zen_mode = Soll_Inter.zar_kraftregler_aktiv;     //!!! Betriebsart f�r beide Arme !!! Betiebsart Vorschub (0) oder Kraftregelung (1) 

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
      
      /* �bergabe und Art der Zentrierung �berpr�fen */
      aus_onli.Ibf_nominal.Soll_ZA_Pos = Soll_Inter.zar_pos ;         /* Zentrierarm rechts Auslauf             [mm]*/ 
      aus_onli.Ibf_nominal.Soll_ZE_Pos = Soll_Inter.zal_pos ;         /* Zentrierarm links Einlauf              [mm]*/ 
      		 	
      /* Drehzahlen */
      //Soll_Inter.hw_n;                                             /* Hauptwalze 			               	[1/min]*/
      //aus_puff.n_omega.n_aw_motor_g_o = Soll_Inter.kwo_n * MIN_FAK;  /* Kegelwalze oben                     [1/min]*/
      //aus_puff.n_omega.n_aw_motor_g_u = Soll_Inter.kwu_n * MIN_FAK;  /* Kegelwalze unten                    [1/min]*/
      
      /* Schrittnummer */
      // Soll_Inter.schritt_nr;			

      /* Sollkr�fte */
      aus_onli.Ibf_nominal.Soll_FR  = Soll_Inter.rs_kraft;           /* Radialkraft [N] */
      aus_onli.Ibf_nominal.Soll_FA  = Soll_Inter.aso_kraft;          /* Axialkraft  [N] */   
      aus_onli.Ibf_nominal.Soll_FAG = Soll_Inter.ag_kraft;           /* Axialger�st [N] */
      aus_onli.Ibf_nominal.Soll_FZ  = Soll_Inter.zal_kraft;          /* Zentrierarme[N]*/
      
      //Soll_Inter.zal_kraft = Soll_IBF->ZAR_Kraft;
      //Soll_Inter->zar_kraft = Soll_IBF->ZAL_Kraft;
      // Soll_Inter.zal_kraft;                                      /*Zentirerkarft derzeit nur eine Variable f�r beide Zentirerarme m�glich. 060718, Michl*/
      // Soll_Inter.zar_kraft;
    }
    
    return(TRUE);
}

int In_RWTH_LOG_Schreiben(char *buffer)
{
     MyLogFile << buffer << endl;

     return TRUE;
}
