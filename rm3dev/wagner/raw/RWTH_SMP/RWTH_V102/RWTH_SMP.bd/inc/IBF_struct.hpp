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

    
/*-----------------------------------------------------------------------------------------*/ 
/*                  Strucktur Geometrie | IBF-Flags | Radial-Profilierenodule              */
/*-----------------------------------------------------------------------------------------*/
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

        int rs_kraftanfahren_aktiv;  /* Flag zum Kraftanfahren des Rohlings [0-1] */
        int as_kraftanfahren_aktiv;  /* Flag zum Kraftanfahren des Rohlings [0-1] */

        int ag_mode;                 /* 0 = Vorschubregelung, Abschaltma� nicht erreicht, AG schlie�t auf SMS-Position
                                        1 = Kraftregelung, Abschaltma� nicht erreicht, AG schlie�t auf SMS-Position
                                        2 = Vorschubregelung, Abschaltma� erreicht, AG schlie�t auf SMS-Position
                                        3 = Kraftregelung, Abschaltma�  erreicht, AG schlie�t auf SMS-Position
                                        4 = Vorschubregelung, Abschaltung nicht erreicht, IBF-Position
                                        5 = Kraftregelung, Abschaltung nicht erreicht, IBF-Position
                                        6 = Vorschubregelung, Abschaltung erreicht, IBF-Position
                                     */
        int ag_act;


        



    };

    struct Def_Zeit
    {
        float Ringumdrehung;        /* Zeit f�r eine Ringumdrehung*/ 
        float Halbe_Ringumdrehung;  /* Zeit f�r 1/2 Ringumdrung*/
        float t_Halte;              /* Haltezeit in sec (1sec = 1000 ms) */
    

    };


    struct Cr_Berechnung
    {
        float a;            /* Hauptwalzendurch. * Durchmesser */
	   	float b;            /* Innendurchmesser(Durchmesser-2*Wandst�rke) * Dornwalze */
	   	float c;            /* Hauptwalzemdurch. + Durchmesser */
	   	float d;      		/* Durchmesser - Dornwalze */
	   	float e;            /* Cr * Cr */
	   				    
	   	float o;            /* (a/c) * (b/d) */
	   	float u;            /* (a/c) + (b/d) */ 
	   				    
	   	float g;            /* (Wanddicke + 1/e*(o/u)); */
		float f;            /* 2 * g */

        /* Variablendeklaration*/

        int os_i;           /* Feldnummer */
        float Array[2];     /* Feld f�r Wanddicke [mm] */
		                
    };

    struct Breitung
    {
        float mr;           /* Breitungsexponent */
        float qf;           /* Verh�ltnis Wanddicke-Werkzeugh�he*/
        float ga;           /* Verh�ltnis Wanddicke-Rohlingsh�he h0*/
        float e_mr;         /* nat�rlichen Logarithmus der Breitung */

        float Da_t2;        /* berechneter Durchmesser zum n�chsten Zeitpunkt (mm)*/
        float Di_t2;        /* berechneter Durchmesser zum n�chsten Zeitpunkt (mm)*/
        float Da_t2_h2;     /* quadrierter Wert (mm^2) */
        float Di_t2_h2;     /* quadrierter Wert (mm^2) */

        float Volumen_t1;   /* aktuelles Volumen der Umformzone (mm^3)*/
        float Volumen_t2;   /* berechnetes Volumen zum nachfolgenden Zeitpunkt (mm^3) */
        float Volumen_diff; /* Volumendifferenz, des verdr�ngten Volumenanteils (mm^3)*/
        float delta_h;      /* H�henzunahme Axialschlitten (mm) */
    };

    struct Filter
    {
        float yF_neu;
        float yF_alt;        
    };

    struct Radial_Flex_Prof
    {
        /* Wahlschalter /spezial Flags  */

        int Schalter_Kont_DisKo; 
        int t_warte_flag;


        /* Kr�fte */

        /* Positionen / Abnahmen */

        float delta_h;              /* berechnete H�henabnahme zum Zeitpunkt t f�r den Zeitpunkt t+1 [mm] */
        float delta_s;              /* Eindringtiefe in Ringwand aus IBF_Data.ini                    [mm] */
        float abnahme_s;            /* Abnahme der Wanddicke f�r diskont. Vorschub �ber Weg          [mm] */

        float Soll_Wanddicke;       /* Soll-Wanddicke f�r Modus mit Walzspaltzustellung Cr           [mm] */


        /* Positionsmerker / Zeitmarken */

        float t_dis_h;               /* Haltezeit f�r diskontinuierliche Walzung */
        int Umdrehungen;             /* Anzahl der Umdrehungen in der Rundungsphase aus IBF_Para.ini*/
        float t_warte;               /* WartezeiFt */

        
        /* Geometrien: weitere Variablen */

        float s_f;                  /* Auslaufende Wanddicke zur Zeit t (Daten aus TRT-Task)                  [mm] */
        float s_f_alt;              /* Auslaufende Wanddicke zur Zeit t-1 (Daten aus TRT-Task)                [mm] */

        struct Filter s_f_Filter;   /* Filter der aktuellen Wandposition f�r sehr kleine Positionierungen */
        
        float Werkzeugbreite;       /* Breite Profilierwerkzeug aus IBF_Para.ini        [mm] */

        float Anfangsposition_DW;   /* Postion die der Dorn angefahren ist, um Zustellung f�r ersten Ringumdrehung zu berechnen (MRAW ->Afpos_dw)  [mm] */    

        float Stegstaerke;          /* Stegst�rke (Soll & Ist) aus IBF_Data.ini             [mm] */

        float Rohlinghoehe;        /* Variable wird f�r Axialschlittenposition ben�tig aus IBF_Data.ini [mm]*/
        
       

        /* Dynamik */
        float Vorschubgeschw_Dw;   /* Vorschubgeschwindigkeit Dornwalze ->IBF_Para.ini       [mm/s] */
        float Vorschubgeschw_ASO;  /* Vorschubgeschwindigkeit Kegelwalze->IBF_Para.ini       [mm/s] in case 17 */
        float eps_Vorschub;        /* Epsilon f�r disk. Vorschub �ber Weg                    [o.E.] */
        //float Vorschub_v;        /* Berechnete Vorschubgeschwindigkeit �BERPR�FEN, ob diese Variable noch ben�tigt wird         [mm/s] */
        float dw_vn;               /* Vorschubgeschwindigkeit f�r Vorschub mit Cr-Berechnung [mm/s] */

        /* Verh�tlnis */

        float Walzspalt_Cr;          /* Walzspaltverh�ltnis aus IBF_Data.ini */
        
        struct Cr_Berechnung Cr;     /* */
        
        struct Breitung Breitung;   /* Struktur f�r Berechnung des Breitungsfaktors*/

        //struct Def_Zeit Zeit;        Struktur zur Zeit
        
        

    };


    struct Axial_Flex_Prof
    {

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

        int AUTO;               /* 1: automatisch; 0: manuell gesteuerte Profilierung */
        int StartPos;           /* Bedingung f�r Anfahren der Startpositionen (erste Profilposition) */
                                /* Info Modellwalzwerk: wird in mapwonli zu Null und in interfac wieder 1 gesetzt */
        char ManAuswahl;        /* Auswahl von Aktion bei manueller Steuerung */

        int  Profilflag;        /* Einlesen des Profilflags, das in der Soll-Struktur geschrieben wird */
        char InitAchse;         /* Einlesen des Flags f�r Anfahren der Startposition in Reihenfolge RS, AG, AS */
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
        float RS_Pos_Null;      /* Vorformwanddicke, als Merker           [mm]*/
        float ASO_Pos_Null;     /* Vorf�rmh�he als Merker                 [mm]*/
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
    float eps_Vorschub; // Epsilon f�r diskontinuierlich 
    
    
    struct Def_Zeit Zeit;

    /* Flexibel Radial Profliert */

    struct Radial_Flex_Prof Radial;



//---------------------------------------------------------------------------
// TO-DO : in separate Struktur "AxialeVariable" �berf�hren

struct Geometrie Kragenwalze;


float Del_Kr_AGR;       // Wert f�r Axialprofilieren
float Pos_auf_Mantel;   // Position des Ringau�endurchmessers auf der Mantelfl�che	



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


    /*---------------------------------------------------------------------------*/
    /*  Variablen die vor Programmlaufzeit durch Benutzer vorgegeben werden      */
    /*---------------------------------------------------------------------------*/

    /*Wahlschalter 'extern' gesetzt*/
    struct IBF_Flag Flag;

   /* Flexibel Radial Profliert */

    struct Radial_Flex_Prof Radial;

    
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
