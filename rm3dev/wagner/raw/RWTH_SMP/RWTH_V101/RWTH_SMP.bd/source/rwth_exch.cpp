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




/****************************************************************************/
// Konstruktor
/****************************************************************************/
RWTH_EXCH::RWTH_EXCH(void)
{
    FILE *FHandle = NULL;
    int i;
    
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
    
    //Soll_IBF.InitAchse    = 'a';
    Soll_IBF.InitAchse    = 'v';
   


    //-----------------------------------------------------------------------
    //----- Einlesen der Textdatei (entspricht der ipfpara auf dem MRAW -----
    //----- Datei liegt auf dem Flash-Speicher der SMP16                -----
    //----- 
    for(i=0; i<IBF_PARA_MAX; i++)
    {
        IBF_PARA[i]= 0.0;
    }

    if((FHandle = fopen("IBFPARA.INI" , "rb")) == NULL)
    {
        MyLogFile << "IBFPARA.INI konnte nicht geoeffnet werden" << endl;  //Meldung in Logfile "RWTH_LOG.TXT" schreiben
    }
    else
    {
        
        MyLogFile << "IBFPARA.INI wurde geoeffnet" << endl;
      
          
        i=0;
        while((fscanf(FHandle,"%f",&IBF_PARA[i]) !=EOF) && (i < IBF_PARA_MAX))
        {
            MyLogFile << "folgender Wert wurde gelesen:" << IBF_PARA[i] << " " << i << endl;
            i++;
        }
           
        
        fclose(FHandle);
        FHandle = NULL;

    }
    
    //Zuordnen der Variablen
    MyLogFile << "Gelesene Werte wurden wie folgt zugeordnet" << endl;
   
    Ist_IBF.Flag.rs_kraftregler_aktiv = IBF_PARA[0]; /* Schalter: Walzen mit Kraftsteuerung [1], Positionssteuereung [0] */
    MyLogFile << "Kraftregler aktiv" << Ist_IBF.Flag.rs_kraftregler_aktiv << endl;
    
    //Ist_IBF.Flag.as_kraftregler_aktiv = IBF_PARA[0];             /* Schalter: Walzen mit Kraftsteuerung [1], Positionssteuereung [0] */
    //Ist_IBF.RS_Kraft_Vorgabe = IBF_PARA[0];                      /* Schalter: Walzen mit Kraftsteuerung [1], Positionssteuereung [0] */
    //Ist_IBF.AS_Kraft_Vorgabe = IBF_PARA[0];                      /* Schalter: Walzen mit Kraftsteuerung [1], Positionssteuereung [0] */
    //Ist_IBF.AG_Kraft_Vorgabe = IBF_PARA[0];                      /* Schalter: Walzen mit Kraftsteuerung [1], Positionssteuereung [0] */
    
    //Ist_IBF.Flag.rs_kraftanfahren_aktiv = IBF_Para[0];        /* Schalter: Anwalzen mit Kraftvorgabe [1], ohne [0]*/
    //Ist_IBF.RS_Kraft_Anfahren = IBF_PARA[0];                  /* Anwalzkraft in Verbindung mit Schalter rs_kraftanfahren_aktiv  [N]*/
    


    
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
      aus_puff.istanz_ru = TestCounter[0];  //Nur Test, muss entfernt werden!
      
      //Test: Laufzeit wird verlängert
      for(int i = 0; i < 30; i++)           //Nur Test, muss entfernt werden!
         RmPauseTask(RM_MILLISECOND(2));   //Nur Test, muss entfernt werden!
#endif

    //jeweils zum Walzenstart (Walzenstartflag) müssen einige Variablen vordefiniert werden, damit richtige CASE-Anweisungen im rpw.cpp (IBF-Modul) ausgeführt werden
      if (ein_puff.walzenstart_flag)
      {
         Ist_IBF.AUTO          = 1;
         Ist_IBF.StartPos      = 1;
         
        Soll_IBF.Profilflag   = -1;
        // Soll_IBF.InitAchse    = 'a';
         Soll_IBF.ExitAchse    = 'a';

         iter_IBF              = 0;

         rpw->Main_RAW( iter_IBF,
                        ein_puff,
                        lokal_puff,
                        aus_puff,
                        ein_onli,
                        aus_onli,
                        IBF_PARA,
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
                        IBF_PARA,
                        &Ist_Inter,
                        &Soll_Inter,
                        &Soll_IBF,
                        &Ist_IBF);
      }
      
      // Zuweisungen für die Steuerung 

      /* zu setzende Flags mit denen IBF-Positionsvorgaben gültig werden */

      aus_onli.Ibf_nominal.RS_act = 1;     //Flag Sollwerte Radialschlitten von Ibf auswertbar
      aus_onli.Ibf_nominal.AS_act = 1;     //Flag Sollwerte Axialschlitten von Ibf auswertbar
      //aus_onli.Ibf_nominal.ZEN_act = in IBF_struct zu definierende Variable oder hier mit 1 konstant aktivieren;    //Flag Sollwerte Zentrierarme von Ibf auswertbar
      //aus_onli.ibf_nominal.AG_act = in IBF_struct zu definierende Variable oder hier mit 1 konstant aktivieren;     //Flag Sollwerte Axialgerüst von Ibf auswertbar

      /* Schalter Kraftregler */
      aus_onli.Ibf_nominal.RS_mode = Soll_Inter.rs_kraftregler_aktiv ;     //Betiebsart Vorschub (0) oder Kraftregelung (1)
      aus_onli.Ibf_nominal.AS_mode = Soll_Inter.aso_kraftregler_aktiv;     //Betiebsart Vorschub (0) oder Kraftregelung (1)
      //aus_onli.Ibf_nominal.ZEN_mode = Soll_Inter.zen_kraftregler aktiv;    //Betiebsart Vorschub (0) oder Kraftregelung (1)
      //aus_onli.Ibf_nominal.AG_mode = Soll_Inter.ag_kraftregler_aktiv;     //Betiebsart Vorschub (0) oder Kraftregelung (1)
      

      /* Zustellgeschwindigkeiten */
      aus_onli.ds_dh_sp_hp.s_punkt = Soll_Inter.rs_v  * ein_onli.rwg_poti_wert; /*Radialschlitten     	             [mm/s]*/
      aus_onli.ds_dh_sp_hp.h_punkt = Soll_Inter.aso_v * ein_onli.rwg_poti_wert; /*Axialschlitten oben                [mm/s]*/
      // Soll_Inter.ag_v;                                                       /* Axialgeruest                      [mm/s]*/
      // Soll_Inter.zal_v;                                                      /* Zentrierarm links                 [mm/s]*/
      // Soll_Inter.zar_v;                                                      /* Zentrierarm rechts                [mm/s]*/
      
      /* Sollpositionen */
    //  aus_onli.Ibf_nominal.Soll_RS_Pos = Soll_Inter.rs_pos;        /* Radialschlitten                        [mm]*/
      aus_onli.Ibf_nominal.Soll_RS_Pos = Soll_Inter.rs_pos;          /* Radialschlitten                        [mm]*/
      aus_onli.Ibf_nominal.Soll_AS_Pos = Soll_Inter.aso_pos;         /* Axialschlitten oben                    [mm]*/
      // aus_onli.Ibf_nominal.Soll_AG_Pos = Soll_Inter.ag_pos;       /* Axialschlitten                         [mm]*/
      
      /* Übergabe und Art der Zentrierung überprüfen */
      // Soll_Inter.float zal_pos;                                   /* Zentrierarm links                      [mm]*/ 
      // Soll_Inter.float zar_pos;                                   /* Zentrierarm rechts                     [mm]*/ 
      		 	
      /* Drehzahlen */
      //Soll_Inter.hw_n;                                             /* Hauptwalze 			               	[1/min]*/
      aus_puff.n_omega.n_aw_motor_g_o = Soll_Inter.kwo_n * MIN_FAK;  /* Kegelwalze oben                     [1/min]*/
      aus_puff.n_omega.n_aw_motor_g_u = Soll_Inter.kwu_n * MIN_FAK;  /* Kegelwalze unten                    [1/min]*/
      
      /* Schrittnummer */
      // Soll_Inter.schritt_nr;			

      /* Sollkräfte */
      aus_onli.Ibf_nominal.Soll_FR = Soll_Inter.rs_kraft;           /* Radialkraft [N] */
      aus_onli.Ibf_nominal.Soll_FA = Soll_Inter.aso_kraft;          /* Axialkraft  [N] */   
      // aus_onli.Ibf_nominal.Soll_FAG = Soll_Inter.ag_kraft;        /* Axialgerüst [N] */
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
