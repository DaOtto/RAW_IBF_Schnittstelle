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
    	/** @var type
    	 * @brief 0: Kanal nicht definiert
    	 * @brief 1: short (16 bits)
    	 * @brief 2: long (32 bits)
    	 * @brief 3: float (32 bits)
    	 * @brief 4: double (64 bits)
    	 * @brief 11: binaer (16 bits)*/
        int    type;                        //0:  Kanal nicht definiert
                                            //1:  short  (16 bits)
                                            //2:  long   (32 bits)
                                            //3:  float  (32 bits)
                                            //4:  double (64 bits)
                                            //11: binär  (16 bits)

        /** @var faktor
         * @brief wird bei \link type \endlink 3 und 4 verwendet damit werden
         * die Variablen multipliziert und auf long gecastet. Der logger uebertraegt
         * ausschliesslich long!*/
        double faktor;                      //wird bei Typ 3 und 4 verwendet
                                            //damit werden die Variablen
                                            //multipliziert und auf long
                                            //gecastet. Der Logger
                                            //überträgt ausschließlich long!

        /** @fn pAdresse
         * @brief Zeiger auf eine Methode ohne RŸckgabewert*/
        void * pAdresse;                    //Adresse der Variablen in der 
                                            //Form: (void *)&Variablenname
    };


    struct TeDat4_type
    {
    	/** @var Teststring[][]
    	 * @brief Tetstring CNC -> PC*/
       char     Teststring[4][80];          // Textstring CNC -> PC 
       /** @var TeDa[][]
        * @brief Testwerte CNC -> PC*/
       long     TeDa[4][10];                // Testwerte CNC -> PC              
    }; 


    struct RwwtPool_tag
    {
    	/** @var Status_TRT
    	 * @brief Status der TRT Bearbeitung*/
       int  Status_TRT;
       /** @var Steuer_TRT
        * @brief Starten, Beenden*/
       int  Steuer_TRT;
       /** @var Status_RWTH
        * @brief Status der IBF Bearbeitung*/
       int  Status_RWTH;
       /** @var Steuer_RWTH
        * @brief Starten, Beenden*/
       int  Steuer_RWTH;

       /** @var Data_available
        * @brief Daten TRT mindestens einmal berechnet*/
       int  Data_available;
       /** @var Data_availableRWTH
        * @brief Daten IBF mindestens eimal bberechnet*/
       int  Data_availableRWTH;

       /** @var Data_initialed
        * @brief Daten von CARWIN uebertragen*/
       int  Data_initialed;


       /** @var pLTableRWTH
        * @brief Zeiger auf Tabelle mit Loggerkanaelen*/
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

