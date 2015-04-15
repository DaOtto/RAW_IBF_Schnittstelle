/*--FILE HEADER---------------------------------------------------------------
;   filename        : raw_t_pool.hpp
;   version         : V2.0
;   contents        : DATA POOL to exchange data between global tasks
;   author          : K. Brauckmann, SMS Eumuco GmbH
;   date            : May, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   stellt Strukturen und Speicher zum globelen Datenaustausch zur
;               Verfügung.
;               Diese Datei muss in alle Projekte von SMS und IBF eingebunden
;               werden.
;
;       RMOS3  Version 3.30
;       CAD-UL Version V120C
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   May , 11. 2006  0001  K.B.  original issue V2.0
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
#ifndef RAW_T_Pool_h
#define RAW_T_Pool_h
    #include "puff_cnc_s.hpp"
    #include "onli_cnc_s.hpp"

    #define TRT_Init_done   0
    #define TRT_Init        1
    #define TRT_Stop        2
    #define TRT_Finished    4

    #define TRT_gestartet   1
    #define TRT_laeuft      2
    #define TRT_neustart    3
    #define TRT_gestoppt    4
    #define TRT_fertig      0
    #define TRT_Fehler     -1
    #define TRT_Blinker     16

    #define MAX_LOG_KANAELE_RWTH    300
    
    struct LOG_CHANNEL_DEF
    {
        int    type;                        //0:  Kanal nicht definiert
                                            //1:  short  (16 bits)
                                            //2:  long   (32 bits)
                                            //3:  float  (32 bits)
                                            //4:  double (64 bits)
                                            //11: binär  (16 bits)

        double faktor;                      //wird bei Typ 3 und 4 verwendet
                                            //damit werden die Variablen
                                            //multipliziert und auf long
                                            //gecastet. Der Logger
                                            //überträgt ausschließlich long!

        void * pAdresse;                    //Adresse der Variablen in der 
                                            //Form: (void *)&Variablenname
    };


    struct TeDat4_type
    {
       char     Teststring[4][80];          // Textstring CNC -> PC 
       long     TeDa[4][10];                // Testwerte CNC -> PC              
    }; 


    struct RwwtPool_tag
    {
       int  Status_TRT;                     //Status der TRT Bearbeitung
       int  Steuer_TRT;                     //Starten, Beenden
       int  Status_RWTH;                    //Status der IBF Bearbeitung
       int  Steuer_RWTH;                    //Starten, Beenden

       int  Data_available;                 //Daten TRT mindestens einmal berechnet
       int  Data_availableRWTH;             //Daten IBF mindestens einmal berechnet

       int  Data_initialed;                 //Daten von CARWIN übertragen

       LOG_CHANNEL_DEF        *pLTableRWTH; //Zeiger auf Tabelle mit Loggerkanälen

       TeDat4_type            *pTeDat;      //Zeiger auf Testwerte

       struct Def_Ein_Puff    ein_puff;
       struct Def_Ein_Puff    ein_puff_back;
       struct Def_Ein_Puff    ein_puff_RWTH;
       struct Def_Aus_Puff    aus_puff;
       struct Def_Aus_Puff    aus_puff_RWTH;
       struct Def_Ein_Onli    ein_onli;
       struct Def_Ein_Onli    ein_onli_back;
       struct Def_Ein_Onli    ein_onli_RWTH;
       struct Def_Aus_Onli    aus_onli;
       struct Def_Aus_Onli    aus_onli_RWTH;
       struct Def_Lokal_Puff  lokal_puff;
    };

    #ifdef Powercon_Modul
        RwwtPool_tag    *RwwtPool;
    #else
        extern RwwtPool_tag *RwwtPool;
    #endif

    const char far Powercon_SendSema[] = "Power_SendSema";
    const char far Powercon_RecSema[] = "Power_RecSema";
    const char far Mailboxl[] = "TRT_MAILBOX";
#endif

