#ifndef _RPW_HPP
   #define _RPW_HPP

   #include <stdio.h>
 //  #include <conio.h>
   #include <math.h>

   #define CPP_T_EXPORT
   #define GUI_T_EXPORT
   #define UFT_T_EXPORT
   #define RAW_T_EXPORT


//   #define TRUE  1
//   #define FALSE 0

   #define IBF_PARA_MAX        10          // max. Anzahl der IBF-Werte, die eingelesen werden
   #define Byte unsigned char

   #include "teso.hpp"
   #include "puff_cnc_s.hpp" 
   #include "onli_cnc_s.hpp"
   #include "IBF_struct.hpp"

/*--------------------------------------------------------------------------*/
/*	Ist-Werte                                                                */
/*--------------------------------------------------------------------------*/
   struct Rohling
   {
   float sm;
   float hm;
   float da;
   };

   struct Def_Ist_Inter
   {  
      /* Positionen */
      float rs_pos;           /* Radialschlitten                  [mm]*/
      float aso_pos;          /* Axialschlitten oben              [mm]*/
      float asu_pos;          /* Axialschlitten unten             [mm]*/   // Nur Modellwalzwerk
      float ag_pos;           /* Axialschlitten                   [mm]*/
      float zal_pos;          /* Zentrierarm links                [mm]*/ 
      float zar_pos;          /* Zentrierarm rechts               [mm]*/ 
      float tr_pos;           /* Tastrolle                   		[mm]*/
      
      /* Soll-Positionen */
      float rs_soll;          /* Radialschlitten                  [mm]*/
      float aso_soll;         /* Axialschlitten oben              [mm]*/
      float asu_soll;         /* Axialschlitten unten             [mm]*/  // Nur Modellwalzwerk
      float ag_soll;          /* Axialschlitten                   [mm]*/  
      float zal_soll;         /* Zentrierarm links                [mm]*/ 
      float zar_soll;         /* Zentrierarm rechts               [mm]*/ 
      		 	
      /* Kraefte */
      float rs_f;             /* Radialschlitten                     [N]*/
      float as_f;             /* Axialschlitten                      [N]*/
      float ag_f;             /* Axialgerüst                         [N]*/
      float	zal_fx;           /* Zentrierarm links  x-Komponente 	   [N]*/ // Nur Modellwalzwerk
      float	zal_fy;           /* Zentrierarm links  y-Komponente 	   [N]*/ // Nur Modellwalzwerk
      float zal_f;            /* gesamte Kraft -> Zentrierarm links  [N]*/ 
      float	zar_fx;           /* Zentrierarm links  x-Komponente 	   [N]*/ // Nur Modellwalzwerk
      float	zar_fy;           /* Zentrierarm links  y-Komponente 	   [N]*/ // Nur Modellwalzwerk
      float zar_f;            /* gesamte Kraft -> Zentrierarm rechts [N]*/ 
      
      /* Strom */
      float hw_i;          /* HW Motor                           [A]*/
      float kwo_i;         /* KWO                                [A]*/
      float kwu_i;         /* KWU                                [A]*/
                                                            
      /* Drehzahlen */                                      
      float hw_n;          /* HW Motor                      [1/min]*/
      float kwo_n;         /* KWO                           [1/min]*/
      float kwu_n;         /* KWU                           [1/min]*/
      
      /* Korrekturpotentiometer */
      Byte        poti_kw_n_255;             /* Vertrim. Kegelwalze           [-] */      // Nur Modellwalzwerk
      Byte        poti_za_d_255;             /* Zentrierposition              [-] */      // Nur Modellwalzwerk
                                                                              
      Byte        poti_vrelproz_255;         /* Autom. Ringverlagerung        [-] */      // Nur Modellwalzwerk
      Byte        poti_endphase_255;         /* Endphasenlaenge               [-] */      // Nur Modellwalzwerk
                                                                              
      Byte        poti_hand_r_255;           /* Dornwalze von Hand            [-] */      // Nur Modellwalzwerk
      Byte        poti_dpmax_255;            /* Walzenvorschub gekoppelt      [-] */      // Nur Modellwalzwerk
                                                                              
      Byte        poti_fz_255;               /* Zentrierdruck                 [-] */      // Nur Modellwalzwerk
      Byte        poti_hand_a_255;           /* Kegelwalze von Hand           [-] */      // Nur Modellwalzwerk
                                                                              
      Byte        poti_kw_n_oben_unten_255;  /* Drehzahlen KW oben, unten     [-] */      // Nur Modellwalzwerk
      Byte        poti_reserve_255;          /* Man. Ringverlagerung          [-] */      // Nur Modellwalzwerk
      
      
      /* Korrekturpotentiometer */
      short       taster_poti_kw_n;             /* Vertrim. Kegelwalze           [-] */   // Nur Modellwalzwerk		
      short       taster_poti_za_d;             /* Zentrierposition              [-] */   // Nur Modellwalzwerk
                  
      short       taster_poti_vrelproz;         /* Autom. Ringverlagerung        [-] */  // Nur Modellwalzwerk
      short       taster_abschaltung_aus;       /* Abschaltung aus               [-] */  // Nur Modellwalzwerk
                  
      short       taster_poti_hand_r;           /* Dornwalze von Hand            [-] */  // Nur Modellwalzwerk
      short       taster_power;                 /* Power-Taster                  [-] */  // Nur Modellwalzwerk
                  
      short       taster_poti_fz;               /* Zentrierdruck                 [-] */  // Nur Modellwalzwerk  		
      short       taster_poti_hand_a;           /* Kegelwalze von Hand           [-] */  // Nur Modellwalzwerk  
                                                                           
      short       taster_poti_kw_n_oben_unten;  /* Drehzahlen KW oben, unten     [-] */  // Nur Modellwalzwerk
      short       taster_poti_reserve;          /* Man. Ringverlagerung          [-] */  // Nur Modellwalzwerk
                  
      Byte        poti_taster[2];               /* Taster                        [-] */  // Nur Modellwalzwerk
      
      /* Abstand Zentrierrollenachse - Hauptwalzenachse in x-Richtung (parallel zur Walzwerksachse) */
      float       za_x_abstand;      // Nur Modellwalzwerk
      	
      /* Ringgeometrie TEST TEST TEST*/
      float da;                     /* Aeusserer Durchmesser        [mm]    */
      float da_of;                  
      float di;                     /* Innerer   Durchmesser        [mm]    */
      float di_of;                  
      float dm;                     /* Mittlerer Durchmesser        [mm]    */
      float dm_of;    
      float fertig_ho_soll;
      float fertig_wd_soll;
      float h0a;                    /* Ringhoehe axial  einlaufend  [mm]    */
      float h0r;                    /* Ringhoehe radial einlaufend  [mm]    */
      float h1r;                    /* Ringhoehe radial auslaufend  [mm]    */
      float h1a;                    /* Ringhoehe axial  auslaufend  [mm]    */
      float h1a_of;                 
      float s0a;                    /* Wanddicke axial  einlaufend  [mm]    */
      float s0r;                    /* Wanddicke radial einlaufend  [mm]    */
      float s1a;                    /* Wanddicke axial  auslaufend  [mm]    */
      float s1r;                    /* Wanddicke radial auslaufend  [mm]    */
      float s1r_of;                 
      float sfh;                    /* Wanddicke bei Fertighoehe    [mm]    */
      float skw;                    
      float skw_of;                 
      float wa_dvol;                /* Berechnete Volumendifferenz [%]      */

      /*Erweiterung gegenüber MRAW*/
     struct  Rohling Vorform;
      
      // TEST TEST TEST
      float h1a_o_of; // Nur Modellwalzwerk
      float h1a_u_of; // Nur Modellwalzwerk
      
      /* Reserve Byte */      
      char  dummy[522];              
      
      //short			speichern_zeit_flag;
      //short			speichern_inkrement;
	};        

/*--------------------------------------------------------------------------*/
/*	(schnelle) Soll-Werte fuer Walzwerk                                      */
/*--------------------------------------------------------------------------*/
   struct Def_Soll_Inter
   { 
      /* Zustellgeschwindigkeiten */
      float rs_v;                /* Radialschlitten     	             [mm/s]*/
      float aso_v;               /* Axialschlitten oben                  [mm/s]*/
      float asu_v;               /* Axialschlitten unten                 [mm/s]*/
      float ag_v;                /* Axialgeruest                         [mm/s]*/
      float zal_v;               /* Zentrierarm links                    [mm/s]*/
      float zar_v;               /* Zentrierarm rechts                   [mm/s]*/
      
      /* Sollpositionen */
      float rs_pos;              /* Radialschlitten                        [mm]*/
      float aso_pos;             /* Axialschlitten oben                    [mm]*/
      float asu_pos;             /* Axialschlitten unten                   [mm]*/
      float ag_pos;              /* Axialschlitten                         [mm]*/
      float zal_pos;             /* Zentrierarm links                      [mm]*/ 
      float zar_pos;             /* Zentrierarm rechts                     [mm]*/ 
      		 	
      /* Drehzahlen */
      float hw_n;                /* Hauptwalze 			               	[1/min]*/
      float kwo_n;               /* Kegelwalze oben                     [1/min]*/
      float kwu_n;               /* Kegelwalze unten                    [1/min]*/
      
      /* Schrittnummer */
      short schritt_nr;			
      
      /* Abstand Zentrierrollenachse - Hauptwalzenachse in x-Richtung (parallel zur Walzwerksachse) */
      float za_x_abstand;

      int   rs_kraftregler_aktiv;   /* [0-1] */
      int   aso_kraftregler_aktiv;
      int   asu_kraftregler_aktiv;
      int   ag_kraftregler_aktiv;
      int   zal_kraftregler_aktiv;
      int   zar_kraftregler_aktiv;

      float rs_kraft;               /* Kraft [N] */
      float aso_kraft;
      float asu_kraft;
      float ag_kraft;
      float zal_kraft;
      float zar_kraft;
   };

/*-----------------------------------------------------------------------*/
/* Definition der Steuerbytes von PC an Modellwalzwerk                   */
/*-----------------------------------------------------------------------*/
struct Def_Steuerbyte
{
   Byte        modus;             /* --- Drei Betriebszustaende --- */
                                  /* Wert = 0 : Inaktiv             */
                                  /* Wert = 1 : Handbetrieb         */
                                  /* Wert = 2 : Automatikbetrieb    */
                                  /* Wert = 3 : Kalibrierbetrieb    */

   Byte      freigabe;            /* --- Freigabesignale fuer die Antriebe --- */
                                  /*   1 Bit 0: Radialschlitten      */
                                  /*   2 Bit 1: Axialgeruest NEU, war -schlitten */
                                  /*   4 Bit 2: Axialschlitten oben NEU, war -geruest */
                                  /*   8 Bit 3: Zentrierarm links    */
                                  /*  16 Bit 4: Zentrierarm rechts   */
                                  /*  32 Bit 5: Axialschlitten unten NEU, war Walzenantriebe */
                                  /*  64 Bit 6: Walzenantriebe NEU, war Axialschlittenbremse */
                                  /* 128 Bit 7: Axialschlittenbremse NEU */
};

int In_RWTH_LOG_Schreiben(char *buffer);

//class---------------------------------------------------------------------
   class RPW
   {
      public:
        float  diam_hw;             /* Werkzeugdurchmesser Hauptwalze [mm] */
        float  diam_dw;             /* Werkzeugdurchmesser Dornwalze  [mm] */

        float  hw_ir;               /* Getriebeuntersetzung Hauptwalzenmotor */
        float  kw_ia;               /* Getriebeuntersetzung Kegelwalzenmotor */
        float  sin_kw_winkel_halbe; /* Wert des Sinus vom 'halben Kegelwalzenwinkel' {sin(22.5°)} */


        float offset_rs; 
        float offset_agr;
        float offset_aso;
        float offset_asu;
        float offset_tr;	

      public:

      RPW();

      int Main_RAW(  int    ITER,
                     struct Def_Ein_Puff    Ein_Puff,
                     struct Def_Lokal_Puff  Lokal_Puff,
                     struct Def_Aus_Puff    Aus_Puff,
                     struct Def_Ein_Onli    Ein_Onli,
                     struct Def_Aus_Onli    Aus_Onli,
                     float  IBF_PARA[IBF_PARA_MAX],
                     struct Def_Ist_Inter   *ist_inter,
                     struct Def_Soll_Inter  *soll_inter,
                     struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                     struct Def_IBF_Allgemein_IST * Ist_IBF);


      int Istwerte_RAW(struct Def_Ein_Puff    Ein_Puff,
                       struct Def_Lokal_Puff  Lokal_Puff,
                       struct Def_Aus_Puff    Aus_Puff,
                       struct Def_Ist_Inter   *ist_inter);

      int Main(struct Def_Ist_Inter          Ist_Inter,
               float  IBF_PARA[IBF_PARA_MAX], 
               struct Def_IBF_Allgemein_IST  *Ist_IBF, 
               struct Def_Soll_Inter         *Soll_Inter,
               struct Def_IBF_Allgemein_SOLL *Soll_IBF);
   };

#endif




