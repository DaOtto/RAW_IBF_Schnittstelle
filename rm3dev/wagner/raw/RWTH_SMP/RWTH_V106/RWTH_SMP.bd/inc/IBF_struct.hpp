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
/*          Includedatein die f�r die IBF-Strukturen ben�toigt werden                      */
/*-----------------------------------------------------------------------------------------*/
    #include "ibf_tool.hpp"
    #include "IBF_radflex.hpp"
    #include "IBF_axproflex.hpp"
    #include "IBF_stuetz.hpp"
    #include "IBF_dw_regelung.hpp"

    
/*-----------------------------------------------------------------------------------------*/ 
/*                  Strucktur Geometrie | IBF-Flags | Radial-Profilierenodule              */
/*-----------------------------------------------------------------------------------------*/

    struct IBF_Testfahrt
    {
        int Flag;               /* Schalter f�r Testfahrt           [0=Aus 1= AN] */
        float Ring_AD;          /* simulierter Ringdurchmesser f�r Testfahrt [mm] */
    };
 

    struct Geometrie
    {
        
        float D_Null;              // Aussendurchmesser 
        float Wandstaerke_Null;    // Anfangswanddicke ->notwendig, da am Modellwalzwerk Daten nicht eingelesen werden k�nnen
        float Start_Ringhoehe;     // Anfangsringh�he
    };



    struct IBF_Flag
    {
        int rs_kraftregler_aktiv;    /* Flag zum Arbeiten mit/ohne Radialschlittenkraft  [0-1] */
        int as_kraftregler_aktiv;    /* Flag zum Arbeiten mit/ohne Axialschlittenkraft   [0-1] */
  
        int ag_kraftregler_aktiv;    /* Flag zum Arbeiten mit/ohne Axialger�stkraft      [0-1] */
        int zal_kraftregler_aktiv;   /* Flag zum Arbeiten mit/ohne Zentrierarmkraftkraft [0-1] */
        int zar_kraftregler_aktiv;   /* Flag zum Arbeiten mit/ohne Zentrierarmkraftkraft [0-1] */

        int rs_kraftanfahren_aktiv;  /* Flag zum Kraftanfahren RADIAL an Rohlings [0-1] */
        int as_kraftanfahren_aktiv;  /* Flag zum Kraftanfahren AXIAL an Rohlings [0-1] */

        int as_kraft_anfahren_erreicht; /* Flag, dass Anfahrkraft erreicht wurde */
        int rs_kraft_anfahren_erreicht; /* Flag, dass Anfahrkraft erreicht wurde */

        int ag_mode;                 /* 0 = Vorschubregelung, Abschaltma� nicht erreicht, AG schlie�t auf SMS-Position
                                        1 = Kraftregelung, Abschaltma� nicht erreicht, AG schlie�t auf SMS-Position
                                        2 = Vorschubregelung, Abschaltma� erreicht, AG schlie�t auf SMS-Position
                                        3 = Kraftregelung, Abschaltma�  erreicht, AG schlie�t auf SMS-Position
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

        int AG_Start_erreicht;      /* Flag: Startposition Axialger�st erreicht = 1*/
        int Bissverhaeltnis;        /* Flag: Walzen mit Bissverh�ltnis (1)|| ohne Bissverh�ltnis (0)*/

        int DA_Jenkouk_DW_Regelung; /* Flag zum zuschalten/abschalten der Dornwalzenreglung aus der DA Jenkouk 2008*/
                                    /* ben�tigt derzeit den tempor�ren Messaufbau */
        int DA_Jenkouk_Messen_ohne_Fahren; /*nur tempor�r f�r Einrichtebetrieb -> danach wieder l�schen !!!!!!!!*/
        int DA_Jenkouk_AG_Analyse;      /* Schalter f�r Regelanalyse des Axialger�stes */


        



    };

    struct Def_Zeit
    {
        float Ringumdrehung;        /* Zeit f�r eine Ringumdrehung*/ 
        float Halbe_Ringumdrehung;  /* Zeit f�r 1/2 Ringumdrung*/
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

        int StartPos;           /* Bedingung f�r Anfahren der Startpositionen (erste Profilposition) */
                                /* Info Modellwalzwerk: wird in mapwonli zu Null und in interfac wieder 1 gesetzt */
        char ManAuswahl;        /* Auswahl von Aktion bei manueller Steuerung */

        int  Profilflag;        /* Einlesen des Profilflags, das in der Soll-Struktur geschrieben wird */
        char InitAchse;         /* Einlesen des Flags f�r Anfahren der Startposition in Reihenfolge RS, AG, AS */
        short InitAchse_gecastet;
        char ExitAchse;         /* Flag f�r L�ften in Reihenfolge vgl InitAchse */
    
    /*Kr�fte*/
        float FR;               /* aktuelle rad. Walzkraft  (Banning gefiltert)            [N]*/  
        float FA;               /* aktuelle axiale Walzkraft(Banning gefiltert)            [N]*/
        float FR_f;             /* gefilterte Kraft Radial   MRAW)                         [N]*/ // Modellwalzwerk
        float FA_f;             /* in Intefac gefiltere Kraft Axial (MRAW)                 [N]*/ // Modellwalzwerk
    
    /*Positionen aktuell*/
        float RS_Pos;           /* Aktuelle Dornposition                [mm]*/
        float AG_Pos;           /* Aktuelle Position Axialger�st        [mm]*/
        float ASO_Pos;          /* Aktuelle Axialschlittenposition oben [mm]*/
        float TR_Pos;           /* Aktuelle Tastrollen-(Laser-)position [mm]*/   
        float ZAR_Pos;              /* Aktuelle Zentrierarm rechts          [mm]*/
        float ZAL_Pos;              /* Aktuelle Zentrierarm links           [mm]*/
        
     
    #ifdef MRAW
        float ASU_Pos;          /* Aktuelle Axialschlittenposition unten*/
    #endif

    /*Positionen Merker*/
        float RS_Pos_Null;      /* Vorformwanddicke, aus Carwin           [mm]*/
        float ASO_Pos_Null;     /* Vorf�rmh�he aus Carwin                 [mm]*/
        float AG_Pos_Null;      /* Axial Profilieren                      [mm]*/
        float RS_Pos_Start;     /* Positionen in 'Walzen' vor Profilieren [mm]*/
        float AG_Pos_Start;     /* Positionen in 'Walzen' vor Profilieren [mm]*/
        float ASO_Pos_Start;    /* Positionen in 'Walzen' vor Profilieren [mm]*/  

        float ASO_Pos_Differenz;    /* Ist_IBF.ASO_Pos_Differenz = Korektur der Starth�he aus Carwin (in IBF_ini definiert) */
                                    /* ASO wird sonst auf Starth�he gesetzt und beim 'Positonieren des AG rutscht ASO �ber  */
                                    /* Stirnseite                                                                       [mm]*/


                               
    
     /*Geometrie*/
       
       float Wanddicke_Ist;             /* aktuelle Wanddicke, Auslausseite Radialschlitten */
       float Rohling_h_angefahren;      /* Rohlingsh�he nach dem Anfahren       [mm] */
       float Rohling_s_angefahren;      /* Rohlingswanddicke nach dem Anfahren  [mm] */
       float da;                        /* aktueller Au�endurchmesser           [mm] */
       float di;                        /* aktueller Innendurchmesser           [mm] */
    
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
    
    float delta_tr;                 /* Tastrollendifferenz: Zum Positionieren des Axialger�stes beim Start [mm]*/

    /*Geometrie*/
        struct Geometrie Vorring;

    /*Dynamik*/
    float eps_Vorschub; // Epsilon f�r diskontinuierlich 
    
    
    struct Def_Zeit Zeit;

    /* Strukturen zu IBF-Module "Flexibel Radial" und "Flexibel Axial" */

    struct Radial_Flex_Prof Radial;
    struct Axial_Flex_Prof Axial;

    /*--------------------------------------------------------------------------*/
    /*                                                                          */
    /*  Strukturen und Variablen, die aus Studienarbeiten und Diplomarbeiten    */
    /*  hervorgehen.                                                            */
    /*--------------------------------------------------------------------------*/
    
    struct stuetzstellen_var stuetz_var;            // Struktur St�tzstellenberechnung SA Sascha Frank, Mai 2008
    struct Def_DW_Regelung_DA_Jenkouk DW_Regelung;  // Struktur Dornwalzenregelung f�r das axiale Profilieren DA Jenkouk April-Juli 2008
    struct Axialgeruest_Regelung AG_Regelung;       // Struktur Dornwalzenregelung f�r das axiale Profilieren DA Jenkouk April-Juli 2008
   
        
    struct IBF_Testfahrt Test;


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
    char InitAchse;         // Schreiben des Flags f�r Anfahren der Startposition in Reihenfolge RS, AG, AS
    char ExitAchse;         // Flag f�r L�ften in Reihenfolge vgl InitAchse
    
    /* Schalter Kraftregler */
    
    
    /* Sollkr�fte */
    float RS_Kraft;         /* Kraft [N] die an SMS-Struktur �bergeben wird */
    float AS_Kraft;         /* Kraft [N] die an SMS-Struktur �bergeben wird */
    float AG_Kraft;         /* Kraft [N] die an SMS-Struktur �bergeben wird */
    float ZAL_Kraft;        /* Kraft [N] die an SMS-Struktur �bergeben wird */
    float ZAR_Kraft;        /* Kraft [N] die an SMS-Struktur �bergeben wird */

    /*Positionen*/
    float RS_Pos;           /* Sollposition Radialschlitten     [mm] */
    float ASO_Pos;          /* Sollposition Axialschlitten oben [mm] */
    float AG_Pos;           /* Sollposition Axialger�st         [mm] */
    
    float ZAR_Pos;          /* Sollposition Zentrierarm rechts  [mm] */
    float ZAL_Pos;          /* Sollposition Zentrierarm links   [mm] */

    float RS_Pos_end;       /* Soll-Endposition der DW, speziell wenn mehrere Soll-Positionen w�hrend Laufzeit definiert werden      [mm]*/


    float min_RS_Pos;       /* minimale Dornwalzenposition      [mm] */
    float min_ASO_Pos;      /* minimale Axialwalzenh�he         [mm] */

    float tr_pos;           /* Sollposition f�r Tastrolle beim Axialprofilieren [mm]*/
    float delta_tr;                 /* Tastrollendifferenz: Zum Positionieren des Axialger�stes beim Start [mm]*/
 

    /*Geschwindigkeiten*/
    float RS_V;             // Sollgeschwindigkeit Radialschlitten 
    float ASO_V;            // Sollgeschwindigkeit Axialschlitten oben
    float AG_V;             // Sollgeschwindigkeit Axialger�st
    float ZAR_V;       // Sollgeschwindigkeit Zentrierarm rechts
    float ZAL_V;       // Sollgeschwindigkeit Zentrierarm links   

    /*Positionen Merker*/
    float RS_Pos_Null;      // Initialisierung nach manueller Anfahrt / vor Profilieren 
    float RS_Pos_Start;     // Positionen in 'Walzen' vor Profilieren 
    float Soll_RS_Pos_end;  // Soll-Endposition

    float Soll_ASO_Pos_alt; // Sollposition des oberen Axialschlitten zum Zeitpunkt t-1 ben�tigt in case 12/13
    float ASO_Pos_Null;
    float ASO_Pos_Start;

    float AG_Pos_Null;           
    float AG_Pos_Start;

    /*Wartezeiten*/
    
    //float t_Halte;          // Haltezeit in sec (1sec = 1000 ms) 
    struct Def_Zeit Zeit;


    /*Geometrie*/

    float Rohling_h_angefahren;      /* Rohlingsh�he nach dem Anfahren       [mm] */
    float Rohling_s_angefahren;      /* Rohlingswanddicke nach dem Anfahren  [mm] */
    


    /*---------------------------------------------------------------------------*/
    /*  Variablen die vor Programmlaufzeit durch Benutzer vorgegeben werden      */
    /*---------------------------------------------------------------------------*/

    /*Wahlschalter 'extern' gesetzt*/
    struct IBF_Flag Flag;

   /* Flexibel Radial Profliert */

    struct Radial_Flex_Prof Radial;
    struct Axial_Flex_Prof Axial;
    struct stuetzstellen_var stuetz_var;   // Struktur St�tzstellenberechnung
    	

    
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

    /*--------------------------------------------------------------------------*/
    /*                                                                          */
    /*  Strukturen und Variablen, die aus Studienarbeiten und Diplomarbeiten    */
    /*  hervorgehen.                                                            */
    /*--------------------------------------------------------------------------*/
  
    struct Def_DW_Regelung_DA_Jenkouk DW_Regelung;  // Struktur Dornwalzenregelung f�r das axiale Profilieren DA Jenkouk April-Juli 2008
    struct Axialgeruest_Regelung AG_Regelung;       // Struktur Dornwalzenregelung f�r das axiale Profilieren DA Jenkouk April-Juli 2008

    
  

};




#endif	