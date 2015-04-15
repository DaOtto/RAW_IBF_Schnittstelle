/*--FILE HEADER---------------------------------------------------------------
;   filename        : ibf_struct.hpp
;   version         : V1.0
;   contents        : IBF-Variablen IBF software 
;   author          : D. Michl, IBF RWTH Aachen
;   date            : October, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   folgende Strukturen enthalten: Ist_Inter, Soll_Inter, 
;                                              IBF_FLag, Radial_Flexibel 
;               
;               
;
;       RMOS3  Version 3.30
;       CAD-UL Version V120C
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   October , 10. 2006  0001  D.M.  original issue V1.0
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _IBF_struct_HPP
   #define _IBF_struct_HPP

//#define MRAW 0          // 0= Modellwalzwerk || 1=Banning Ringwalzwerk
#define RAW  0

// Definition von PI 
#ifndef  PI
#define  PI 3.14159265358979323846            
#endif 


/*-----------------------------------------------------------------------------------------*/
/*          Protottypen der IBF_Funktionen                                                 */
/*-----------------------------------------------------------------------------------------*/
    #include "ibf_tool.hpp"
    #include "IBF_radflex.hpp"
    #include "IBF_axproflex.hpp"

    
/*-----------------------------------------------------------------------------------------*/ 
/*                  Strucktur Geometrie | IBF-Flags | Radial-Profilierenodule              */
/*-----------------------------------------------------------------------------------------*/
    struct Geometrie
    {
        
        float D_Null;              // Aussendurchmesser 
        float Wandstaerke_Null;    // Anfangswanddicke ->notwendig, da am Modellwalzwerk Daten nicht eingelesen werden können
        float Start_Ringhoehe;     // Anfangsringhöhe
    };



    struct IBF_Flag
    {
        int rs_kraftregler_aktiv;    /* Flag zum Arbeiten mit/ohne Radialschlittenkraft  [0-1] */
        int as_kraftregler_aktiv;    /* Flag zum Arbeiten mit/ohne Axialschlittenkraft   [0-1] */
  
        int ag_kraftregler_aktiv;    /* Flag zum Arbeiten mit/ohne Axialgerüstkraft      [0-1] */
        int zal_kraftregler_aktiv;   /* Flag zum Arbeiten mit/ohne Zentrierarmkraftkraft [0-1] */
        int zar_kraftregler_aktiv;   /* Flag zum Arbeiten mit/ohne Zentrierarmkraftkraft [0-1] */

        int rs_kraftanfahren_aktiv;  /* Flag zum Kraftanfahren RADIAL an Rohlings [0-1] */
        int as_kraftanfahren_aktiv;  /* Flag zum Kraftanfahren AXIAL an Rohlings [0-1] */

        int as_kraft_anfahren_erreicht; /* Flag, dass Anfahrkraft erreicht wurde */
        int rs_kraft_anfahren_erreicht; /* Flag, dass Anfahrkraft erreicht wurde */

        int ag_mode;                 /* 0 = Vorschubregelung, Abschaltmaß nicht erreicht, AG schließt auf SMS-Position
                                        1 = Kraftregelung, Abschaltmaß nicht erreicht, AG schließt auf SMS-Position
                                        2 = Vorschubregelung, Abschaltmaß erreicht, AG schließt auf SMS-Position
                                        3 = Kraftregelung, Abschaltmaß  erreicht, AG schließt auf SMS-Position
                                        4 = Vorschubregelung, Abschaltung nicht erreicht, IBF-Position
                                        5 = Kraftregelung, Abschaltung nicht erreicht, IBF-Position
                                        6 = Vorschubregelung, Abschaltung erreicht, IBF-Position
                                     */
        int ag_act;

        int aso_mode;                /*  0 = Vorschubsteuerung
                                        1 = Kraftregelung 
                                    */

        int rs_mode;                /*  0 = Vorschubsteuerung
                                        1 = Kraftregelung 
                                    */    

        int Axial_Radialwalzen;     /* Flag zur Auswahl Axialprofilieren (0) bzw. Radialprofilieren (1)*/
        int IBF_Abschaltung;        /* Flag zur Setzung der Abschaltung nach IBF-Vorgabe */


        



    };

    struct Def_Zeit
    {
        float Ringumdrehung;        /* Zeit für eine Ringumdrehung*/ 
        float Halbe_Ringumdrehung;  /* Zeit für 1/2 Ringumdrung*/
        float t_Halte;              /* Haltezeit in sec (1sec = 1000 ms) */
    

    };


 

/*----------------------------------------------------------------------------- */
/*                         IBF-IST Variablen                                    */
/*------------------------------------------------------------------------------*/



     struct Def_IBF_Allgemein_IST
        {

        /*---------------------------------------------------------------------------*/
        /*      Definition der allgemeinen Variabeln (ehemals axpro.h)               */
        /*                                                                           */
        /*       Variablen die zur Programmlaufzeit vorgegeben werden                */
        /*---------------------------------------------------------------------------*/

        
 
    /*Wahlschalter 'intern' gesetzte*/ 

        int StartPos;           /* Bedingung für Anfahren der Startpositionen (erste Profilposition) */
                                /* Info Modellwalzwerk: wird in mapwonli zu Null und in interfac wieder 1 gesetzt */
        char ManAuswahl;        /* Auswahl von Aktion bei manueller Steuerung */

        int  Profilflag;        /* Einlesen des Profilflags, das in der Soll-Struktur geschrieben wird */
        char InitAchse;         /* Einlesen des Flags für Anfahren der Startposition in Reihenfolge RS, AG, AS */
        char ExitAchse;         /* Flag für Lüften in Reihenfolge vgl InitAchse */
    
    /*Kräfte*/
        float FR;               /* aktuelle rad. Walzkraft  (Banning gefiltert)            [N]*/  
        float FA;               /* aktuelle axiale Walzkraft(Banning gefiltert)            [N]*/
        float FR_f;             /* gefilterte Kraft Radial   MRAW)                         [N]*/ // Modellwalzwerk
        float FA_f;             /* in Intefac gefiltere Kraft Axial (MRAW)                 [N]*/ // Modellwalzwerk
    
    /*Positionen aktuell*/
        float RS_Pos;           /* Aktuelle Dornposition                [mm]*/
        float AG_Pos;           /* Aktuelle Position Axialgerüst        [mm]*/
        float ASO_Pos;          /* Aktuelle Axialschlittenposition oben [mm]*/
        float TR_Pos;           /* Aktuelle Tastrollen-(Laser-)position [mm]*/   
        float ZAR_Pos;              /* Aktuelle Zentrierarm rechts          [mm]*/
        float ZAL_Pos;              /* Aktuelle Zentrierarm links           [mm]*/
        
     
    #ifdef MRAW
        float ASU_Pos;          /* Aktuelle Axialschlittenposition unten*/
    #endif

    /*Positionen Merker*/
        float RS_Pos_Null;      /* Vorformwanddicke, als Merker           [mm]*/
        float ASO_Pos_Null;     /* Vorförmhöhe als Merker                 [mm]*/
        float AG_Pos_Null;      /* axial Profilieren                      [mm]*/
        float RS_Pos_Start;     /* Positionen in 'Walzen' vor Profilieren [mm]*/
        float AG_Pos_Start;     /* Positionen in 'Walzen' vor Profilieren [mm]*/
        float ASO_Pos_Start;    /* Positionen in 'Walzen' vor Profilieren [mm]*/  

                               
    
     /*Geometrie*/
       
       float Wanddicke_Ist;  /* aktuelle Wanddicke, Auslausseite Radialschlitten */
    
    /*---------------------------------------------------------------------------*/
    /*  Variablen die vor Programmlaufzeit durch Benutzer vorgegeben werden      */
    /*---------------------------------------------------------------------------*/

    /*Wahlschalter 'extern' gesetzt*/
        
        struct IBF_Flag Flag;

    /*Kraft*/
     //   float RS_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
     //   float AS_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
     //   float AG_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
     //   float ZAR_Kraft_Vorgabe; /* Kraft [N] die in IBFPARA.ini definiert wird */
     //   float ZAL_Kraft_Vorgabe; /* Kraft [N] die in IBFPARA.ini definiert wird */
        
     //   float RS_Kraft_Anfahren; /* Anwalzkraft [N] aus IPFPARA.ini */
     //   float AS_Kraft_Anfahren; /* Anwalzkraft [N] aus IPFPARA.ini */
    
    /*Positionen*/
    

    /*Geometrie*/
        struct Geometrie Vorring;

    /*Dynamik*/
    float eps_Vorschub; // Epsilon für diskontinuierlich 
    
    
    struct Def_Zeit Zeit;

    /* Strukturen zu IBF-Module "Flexibel Radial" und "Flexibel Axial" */

    struct Radial_Flex_Prof Radial;
    struct Axial_Flex_Prof Axial;
	



};



//--------------------------------------------------------------------------------------------------------------------------
//                  Allgemeine SOLL-Werte der IBF-Module
//--------------------------------------------------------------------------------------------------------------------------

struct Def_IBF_Allgemein_SOLL
{

//---------------------------------------------------------------------------
// Definition der allgemeinen Variabeln
// ehemals Axpro.H
//---------------------------------------------------------------------------
   
    /*Wahlschalter 'intern' gesetzte*/ 
    int  Profilflag;        // Schreiben des Profilflags, das in der Ist-Struktur eingelesen wird 
    char InitAchse;         // Schreiben des Flags für Anfahren der Startposition in Reihenfolge RS, AG, AS
    char ExitAchse;         // Flag für Lüften in Reihenfolge vgl InitAchse
    
    /* Schalter Kraftregler */
    
    
    /* Sollkräfte */
    float RS_Kraft;         /* Kraft [N] die an SMS-Struktur übergeben wird */
    float AS_Kraft;         /* Kraft [N] die an SMS-Struktur übergeben wird */
    float AG_Kraft;         /* Kraft [N] die an SMS-Struktur übergeben wird */
    float ZAL_Kraft;        /* Kraft [N] die an SMS-Struktur übergeben wird */
    float ZAR_Kraft;        /* Kraft [N] die an SMS-Struktur übergeben wird */

    /*Positionen*/
    float RS_Pos;           /* Sollposition Radialschlitten     [mm] */
    float ASO_Pos;          /* Sollposition Axialschlitten oben [mm] */
    float AG_Pos;           /* Sollposition Axialgerüst         [mm] */
    
    float ZAR_Pos;          /* Sollposition Zentrierarm rechts  [mm] */
    float ZAL_Pos;          /* Sollposition Zentrierarm links   [mm] */

    float RS_Pos_end;       /* Soll-Endposition der DW, speziell wenn mehrere Soll-Positionen während Laufzeit definiert werden      [mm]*/


    float min_RS_Pos;       /* minimale Dornwalzenposition      [mm] */
    float min_ASO_Pos;      /* minimale Axialwalzenhöhe         [mm] */
 

    /*Geschwindigkeiten*/
    float RS_V;             // Sollgeschwindigkeit Radialschlitten 
    float ASO_V;            // Sollgeschwindigkeit Axialschlitten oben
    float AG_V;             // Sollgeschwindigkeit Axialgerüst
    float ZAR_V;       // Sollgeschwindigkeit Zentrierarm rechts
    float ZAL_V;       // Sollgeschwindigkeit Zentrierarm links   

    /*Positionen Merker*/
    float RS_Pos_Null;      // Initialisierung nach manueller Anfahrt / vor Profilieren 
    float RS_Pos_Start;     // Positionen in 'Walzen' vor Profilieren 
    float Soll_RS_Pos_end;  // Soll-Endposition

    float Soll_ASO_Pos_alt; // Sollposition des oberen Axialschlitten zum Zeitpunkt t-1 benötigt in case 12/13
    float ASO_Pos_Null;
    float ASO_Pos_Start;

    float AG_Pos_Null;           
    float AG_Pos_Start;

    /*Wartezeiten*/
    
    //float t_Halte;          // Haltezeit in sec (1sec = 1000 ms) 
    struct Def_Zeit Zeit;


    /*Geometrie*/


    /*---------------------------------------------------------------------------*/
    /*  Variablen die vor Programmlaufzeit durch Benutzer vorgegeben werden      */
    /*---------------------------------------------------------------------------*/

    /*Wahlschalter 'extern' gesetzt*/
    struct IBF_Flag Flag;

   /* Flexibel Radial Profliert */

    struct Radial_Flex_Prof Radial;
    struct Axial_Flex_Prof Axial;
	

    
    /*Kraft*/
     float RS_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
     float AS_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
     float AG_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
     float ZAR_Kraft_Vorgabe; /* Kraft [N] die in IBFPARA.ini definiert wird */
     float ZAL_Kraft_Vorgabe; /* Kraft [N] die in IBFPARA.ini definiert wird */
        
     float RS_Kraft_Anfahren; /* Anwalzkraft [N] aus IPFPARA.ini */
     float AS_Kraft_Anfahren; /* Anwalzkraft [N] aus IPFPARA.ini */
 
    
    
    /*Dynamik*/

    /*Geometrie*/
  
    //-----------------------------------------------------------------------------
   
    /* Axialschlitten unten  */
    #ifdef MRAW
    float ASU_Pos;          // Aktuelle Axialschlittenposition unten
    #endif
    float Soll_ASU_Pos;     // Sollposition Axialschlitten unten
    float Soll_ASU_V;       // Sollgeschwindigkeit Axialschlitten unten
  
  

};




#endif	
