#ifndef _IBF_struct_HPP
   #define _IBF_struct_HPP

//#define MRAW 0          // 0= Modellwalzwerk || 1=Banning Ringwalzwerk
#define RAW  0

//---------------------------------------------------------------------------
//          Protottypen der IBF_Funktionen                                    
//---------------------------------------------------------------------------

    void Einlesen_IBF_Parameter(struct Def_Ein_Puff *Ein_Puff);

    void IBF_Werte(struct Def_IBF_Allgemein_SOLL *Soll_IBF, struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_Ein_Puff Ein_Puff);




//---------------------------------------------------------------------------
//                  Allgemeine IST-Werte der IBF-Module
//---------------------------------------------------------------------------
    struct Geometrie
    {
        //int a;
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
    };



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
        
        float Afpos_dw;         /*Postion die der Dorn angefahren ist um Zustellung f�r ersten Ringumdrehung zu berechnen mm]*/ // Radial Profilieren   
                               
    
   /*Geometrie*/
        float s_f ;             /* in interfac gefilterte Wanddicke       [mm]*/ //Modellwalzwerk


    /*---------------------------------------------------------------------------*/
    /*  Variablen die vor Programmlaufzeit durch Benutzer vorgegeben werden      */
    /*---------------------------------------------------------------------------*/

    /*Wahlschalter 'extern' gesetzt*/
        float Schalter_Kont_DisKo;      /* 0 = kontinuierlicher Vorschub, 1= diskontinuierlicher Vorschub (eps/Weg), 2=(eps/Geschwindigkeit)*/
        struct IBF_Flag Flag;

    /*Kraft*/
        float RS_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
        float AS_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
        float AG_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
        float ZAR_Kraft_Vorgabe; /* Kraft [N] die in IBFPARA.ini definiert wird */
        float ZAL_Kraft_Vorgabe; /* Kraft [N] die in IBFPARA.ini definiert wird */
        
        float RS_Kraft_Anfahren; /* Anwalzkraft [N] aus IPFPARA.ini */
        float AS_Kraft_Anfahren; /* Anwalzkraft [N] aus IPFPARA.ini */
    
    /*Positionen*/
    

    /*Geometrie*/
        struct Geometrie Vorring;

    /*Dynamik*/
    float eps_Vorschub; // Epsilon f�r diskontinuierlich 



//---------------------------------------------------------------------------
// TO-DO : in separate Struktur "AxialeVariable" �berf�hren

struct Geometrie Kragenwalze;


float Del_Kr_AGR;       // Wert f�r Axialprofilieren
float Pos_auf_Mantel;   // Position des Ringau�endurchmessers auf der Mantelfl�che	

//---------------------------------------------------------------------------
//--------------------------Variablen aus IBFPARA3.c-------------------------
//---------------------------------------------------------------------------
   
//-> To-Do in separate Struktur �berf�hren
float Werkzeugdurchmesser; // Durchmesser Dornwalzenaufsatz

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
    float RS_Kraft;                 /* Kraft [N] die an SMS-Struktur �bergeben wird */
    float AS_Kraft;                 /* Kraft [N] die an SMS-Struktur �bergeben wird */
    float AG_Kraft;                 /* Kraft [N] die an SMS-Struktur �bergeben wird */
    //float Soll_Inter.zen_kraft;   /* Kraft [N] die an SMS-Struktur �bergeben wird */
    //float Soll_Inter.zar_kraft;   /* Kraft [N] die an SMS-Struktur �bergeben wird */

    /*Positionen*/
    float RS_Pos;           // Sollposition Radialschlitten
    float ASO_Pos;          // Sollposition Axialschlitten oben
    float AG_Pos;           // Sollposition Axialger�st
    float TR_Pos;           // Aktuelle Tastrollen-(Laser-)position 

    /*Geschwindigkeiten*/
    float RS_V;             // Sollgeschwindigkeit Radialschlitten 
    float ASO_V;            // Sollgeschwindigkeit Axialschlitten oben
    float AG_V;             // Sollgeschwindigkeit Axialger�st
    float Soll_ZAR_V;       // Sollgeschwindigkeit Zentrierarm rechts
    float Soll_ZAL_V;       // Sollgeschwindigkeit Zentrierarm links   

    /*Positionen Merker*/
    float RS_Pos_Null;      // Initialisierung nach manueller Anfahrt / vor Profilieren 
    float RS_Pos_Start;     // Positionen in 'Walzen' vor Profilieren 
    float Soll_RS_Pos_end;  // Soll-Endposition

    float Soll_ASO_Pos_alt; // Sollposition des oberen Axialschlitten zum Zeitpunkt t-1 ben�tigt in case 12/13
    float ASO_Pos_Null;
    float ASO_Pos_Start;

    float AG_Pos_Null;           
    float AG_Pos_Start;

    /*Geometrie*/


    /*---------------------------------------------------------------------------*/
    /*  Variablen die vor Programmlaufzeit durch Benutzer vorgegeben werden      */
    /*---------------------------------------------------------------------------*/

    /*Wahlschalter 'extern' gesetzt*/
    struct IBF_Flag Flag;

    
    
    
    /*Dynamik*/
    float Vorschubgeschw_Dw;   // Vorschubgeschwindigkeit Dornwalze
    float Umdrehungen;         // Umdrehungen f�r Rundungsphase

    /*Geometrie*/
    float Steg;                // Verbleibende Stegst�rke
    float delta_s;             // Eindringtiefe 

    //-----------------------------------------------------------------------------
   
    /* Axialschlitten unten  */
    #ifdef MRAW
    float ASU_Pos;          // Aktuelle Axialschlittenposition unten
    #endif
    float Soll_ASU_Pos;     // Sollposition Axialschlitten unten
    float Soll_ASU_V;       // Sollgeschwindigkeit Axialschlitten unten
  
  

};




#endif	
