/*--FILE HEADER---------------------------------------------------------------
;   filename        : rpw.hpp
;   version         : V1.0
;   contents        : Tool for IBF software 
;   author          : J.Debye, SMS Eumuco; D. Michl, IBF RWTH Aachen
;   date            : October, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   struct Def_Ist_Inter Ist_Inter, 
                struct Def_Soll_Inter struct Soll_Inter 
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
#ifndef _RPW_HPP
   #define _RPW_HPP

   #include <stdio.h>
 //  #include <conio.h>
   #include <math.h>
   #include <iniFile.h>

   #define CPP_T_EXPORT
   #define GUI_T_EXPORT
   #define UFT_T_EXPORT
   #define RAW_T_EXPORT


//   #define TRUE  1
//   #define FALSE 0

   #define Byte unsigned char

   #include "teso.hpp"
   #include "puff_cnc_s.hpp" 
   #include "onli_cnc_s.hpp"
   #include "IBF_struct.hpp"
   #define Testcode TRUE

/*--------------------------------------------------------------------------*/
/*	Ist-Werte    : Ist_Inter                                                */
/*--------------------------------------------------------------------------*/
   
/**
 * \struct Testfahrt
 * @brief Enthaelt Informationen ueber die Art der Fahrt, ob Testfahrt oder nicht, sowie den simulierten Ringdurchmesser, sollte es sich um eine Testfahrt handeln
 */
   struct Testfahrt
    {
	   /**
	   * @var Flag
	   * @brief 0=Aus, 1=An */
        int Flag;               /*[0=Aus 1= AN] */
        /**
        * @var Ring_AD
        * @brief simulierter Ringdurchmesser für Testfahrt in mm */
        float Ring_AD;          /* simulierter Ringdurchmesser f¸r Testfahrt [mm] */
    };

/**
 * \struct Rohling
 * @brief Geometrie eines Rohlings*/
   struct Rohling
   {
	   /** @var sm
	    * @brief Ringwandstärke in [mm]*/
	   float sm;
	   /** @var hm
	    * @brief */
	   float hm;
	   /** @var da
		* Aussendurchmesser des Rings in [mm]*/
	   float da;
   };

   /**
    * \struct Antriebe
    * @brief Angaben ueber das Ist- und Solldrehmoment
    */
    struct Antriebe
    {
	   /** @var ma_ist
	    * @brief Ist-Drehmoment in [N/mm]*/
        float ma_ist;
        /** @var ma_soll
         * @brief Soll-Drehmoment in [N/mm]*/
        float ma_soll;               /* Soll-Drehmoment [N/mm]*/

    };

    /**
     * \struct Werkzeug
     * @brief Informationen über das Werkzeug. Dies beinhaltet Informationen über die
     * Walzdurchmesser, Windekgeschwindigkeiten, Drehzahlen und Ringumdrehungen
     */
    struct Werkzeug
    {
    	/** @var Durchmesser_HW
    	 * @brief Hauptwalzdurchmesser aus Carwin [mm]*/
        float Durchmesser_HW;
        /** @var Durchmesser_DW
         * @brief Durchmesser der Dornwalze aus Carwin [mm]*/
        float Durchmesser_DW;
        /** @var Winkelgeschw_omega_HW
         * @brief Winkelgeschwindigkeit omega (rad) der Hauptwalze [1/s] */
        float Winkelgeschw_omega_HW;
        /** @var Drehzahl_HW
         * @brief Drehzahl n (grad) der Hauptwalze [1/s]*/
        float Drehzahl_HW;
        /** @var tU_HW
         * @brief Zeit fuer 1 Umdrehung der Hauptwalze in [s]*/
        float tU_HW;
        /** @var Winkel_grad_tU_HW
         * @brief aktueller Drehwinkel in grad [∞]*/
        float Winkel_grad_tU_HW;
        /** @var U_v_HW
         * @brief Umfangsgeschwindigkeit der Hauptwalze in [mm/s]*/
        float U_v_HW;

        /** @var Ringumdrehung
         * @brief Zeit fuer eine Rindumdrehung in [s]*/
        float Ringumdrehung;
        /** @var omega_Ring
         * @brief Winkelgeschwindigkeit des Rings in [1/s]*/
        float omega_Ring;
        /** @var Winkel_grad_tU_Ring
         * @brief aktueller Drehwinkel des Rings in Grad [∞]*/
        float Winkel_grad_tU_Ring;


        /** @var l_fehlende_spitze
         * @brief Laenge der fehlenden Spitzen an unteren Kegelwalze in [mm]*/
        float l_fehlende_spitze;

        /** @var Antrieb_ASO
         * @brief Struktur Antrieb des Axialschlitten oben*/
        struct Antriebe Antrieb_ASO;
        /** @var Antrieb_ASU
         * @brief Struktur Antrieb des Axialschlitten unten*/
        struct Antriebe Antrieb_ASU;  /* Struktur Antrieb des Axialschlitten*/
        
    };


    /**
     * \struct Def_Ist_Inter
     * Beinhaltet detailliert Informationen über den aktuellen Zustand des Ringwalzwerks.
     * Darunter die aktuellen Positionen der Axial- und Radialschlitten. Desweiteren die Sollpositionen
     * der Radial- und Axialschlitten. Außerdem zusätzliche die Position des Axialschlitten unten für das
     * Modellwalzwerk.
     * Außerdem sind Informationen über die aktuellen Kräfte, Drehzahlen, Motoren und zwei unterschiedlich
     * präzise Korrektionmeter vor. Zu guter letzt enthält die Struktur Informationen über die aktuelle Ring-
     * geometrie.
     * Weitere Informationen über die Variablen sind im Quellcode als Kommentar hinter den jeweiligen Variablen
     * hinterlegt.
     */
   struct Def_Ist_Inter
   {  
      /** @var Systemzeit
       * @brief Test zum ausmessen der benoetigtn Zeiten*/
      double Systemzeit;
    	/* aktuelle Positionen */
    	/** @var rs_pos
    	 * @brief aktuelle Position Radialschlitten in [mm]*/
    	float rs_pos;
    	/** @var aso_pos
    	 * @brief aktuelle Position Axialschlitten oben in [mm] */
    	float aso_pos;
    	/** @var asu_pos
    	 * @brief aktuelle Position Axialschlitten unten in [mm] diese Variable ist jedoch nur beim Modellwalzwerk verfügbar */
    	float asu_pos;
    	/** @var ag_pos
    	 * @brief aktuelle Position Axialgerüsts in [mm] */
    	float ag_pos;
    	/** @var zal_pos
    	 * @brief aktuelle Position Zentrierarm links in [mm]*/
    	float zal_pos;
    	/** @var zar_pos
    	 * @brief aktuelle Position Zentrierarm rechts in [mm]*/
    	float zar_pos;
    	/** @var tr_pos
    	 * @brief aktuelle Position Tastrolle in [mm]*/
    	float tr_pos;

    	/* Soll-Positionen */
    	/** @var rs_soll
    	 * @brief Soll-Position des Radialschlittens in [mm]*/
    	float rs_soll;
    	/** @var aso_soll
    	 * @brief Soll-Position es Axialschlittens oben in [mm]*/
    	float aso_soll;
    	/** @var asu_soll
    	 * @brief Soll-Position des Axialschlittens unten int [mm] diese Variable ist jedoch nur beim Modelwalzwerk verfügbar*/
    	float asu_soll;
    	/** @var ag_soll
    	 * @brief Soll-Position des Axialgerüsts in [mm] */
    	float ag_soll;
    	/** @var zal_soll
    	 * @brief Soll-Position des Zentrierarmes links in [mm]*/
    	float zal_soll;
    	/** var zar_soll
    	 * @brief Soll-Position des Zentrierarmes rechts in [mm]*/
    	float zar_soll;         /* Zentrierarm rechts               [mm]*/


      /* Kraefte */
    	/** @var rs_f
    	 * @brief Kraft des Radialschlittens in [N]*/
    	float rs_f;
    	/** @var as_f
    	 * @brief Kraft des Axialschlittens in [N]*/
    	float as_f;
    	/** @var ag_f
    	 * @brief Kraft des Axialgeruestes in [N]*/
    	float ag_f;
    	/** @var zal_fx
    	 * Kraft der x-Komponente des Zentrierarms links in [N]. Diese Variable ist jedoch nur beim Modellwalzwerk verfügbar*/
    	float	zal_fx;
    	/** @var zal_fy
    	 * Kraft der y-Komponente des Zentrierarms links in [N]. Diese Variable ist jedoch nur beim Modellwalzwerk verfügbar*/
    	float	zal_fy;
    	/** @var zal_f
    	 * @brief gesamte Kraft des linken Zentrierarms in [N]*/
    	float zal_f;
    	/** @var zar_fx
    	 * Kraft der x-Komponente des Zentrierarms rechten in [N]. Diese Variable ist jedoch nur beim Modellwalzwerk verfügbar*/
    	float zar_fx;
    	/** @var zar_fy
    	 * Kraft der y-Komponente des Zentrierarms rechten in [N]. Diese Variable ist jedoch nur beim Modellwalzwerk verfügbar*/
    	float zar_fy;
    	/** @var zar_f
    	 * @brief gesamte Kraft des rechten Zentrierarms in [N]*/
    	float zar_f;


      /* Strom */
    	/** @var hw_i
    	 * @brief Stromstaerke fuer den Hauptwalzmotors in [A]*/
    	float hw_i;
    	/** @var kwo_i
    	 * @brief Stromstaerke fuer die Kegelwalze oben in [A]*/
    	float kwo_i;
    	/** @var kwu_i
    	 * @brief Stromstaerke fuer die Kegelwalze unten in [A]*/
    	float kwu_i;


      /* Drehzahlen */
    	/** @var hw_n
    	 * @brief Drehzahl der Hauptwalze in [1/s]->Banning [1/min]->MRAW*/
    	float hw_n;          /* HW                            [1/s]->Banning [1/min]->MRAW*/
    	/** @var kwo_n
    	 * @brief Drehzahl der Kegelwalze oben in [1/s]->Banning [1/min]->MRAW*/
    	float kwo_n;         /* KWO                           [1/s]->Banning [1/min]->MRAW*/
    	/** @var kwu_n
    	 * @brief Drehzahl der Kegelwalz unten in [1/s]->Banning [1/min]->MRAW*/
    	float kwu_n;         /* KWU                           [1/s]->Banning [1/min]->MRAW*/

    	/** @var n_hw_motor_ist
    	 * @brief aktuelle Drehzahl des Motors der Hauptwalze in [1/s]*/
    	float n_hw_motor_ist;
    	/** @var n_kwo_motor_ist
    	 * @brief aktuelle Drehzahl des Motors der Kegelwalze oben in [1/s]*/
    	float n_kwo_motor_ist;
    	/** @var n_kwu_motor_ist
    	 * @brief aktuelle Drehzahl des Motors der Kegelwalze unten in [1/s]*/
    	float n_kwu_motor_ist;

    	/* Korrekturpotentiometer */
    	Byte poti_kw_n_255;             /* Vertrim. Kegelwalze           [-] */      // Nur Modellwalzwerk
    	Byte poti_za_d_255;             /* Zentrierposition              [-] */      // Nur Modellwalzwerk

    	Byte poti_vrelproz_255;         /* Autom. Ringverlagerung        [-] */      // Nur Modellwalzwerk
    	Byte poti_endphase_255;         /* Endphasenlaenge               [-] */      // Nur Modellwalzwerk

    	Byte poti_hand_r_255;           /* Dornwalze von Hand            [-] */      // Nur Modellwalzwerk
    	Byte poti_dpmax_255;            /* Walzenvorschub gekoppelt      [-] */      // Nur Modellwalzwerk

    	Byte poti_fz_255;               /* Zentrierdruck                 [-] */      // Nur Modellwalzwerk
    	Byte poti_hand_a_255;           /* Kegelwalze von Hand           [-] */      // Nur Modellwalzwerk

    	Byte poti_kw_n_oben_unten_255;  /* Drehzahlen KW oben, unten     [-] */      // Nur Modellwalzwerk
    	Byte poti_reserve_255;          /* Man. Ringverlagerung          [-] */      // Nur Modellwalzwerk


    	/* Korrekturpotentiometer */
    	short taster_poti_kw_n;             /* Vertrim. Kegelwalze           [-] */   // Nur Modellwalzwerk
    	short taster_poti_za_d;             /* Zentrierposition              [-] */   // Nur Modellwalzwerk

    	short taster_poti_vrelproz;         /* Autom. Ringverlagerung        [-] */  // Nur Modellwalzwerk
    	short taster_abschaltung_aus;       /* Abschaltung aus               [-] */  // Nur Modellwalzwerk

    	short taster_poti_hand_r;           /* Dornwalze von Hand            [-] */  // Nur Modellwalzwerk
    	short taster_power;                 /* Power-Taster                  [-] */  // Nur Modellwalzwerk

    	short taster_poti_fz;               /* Zentrierdruck                 [-] */  // Nur Modellwalzwerk
    	short taster_poti_hand_a;           /* Kegelwalze von Hand           [-] */  // Nur Modellwalzwerk

    	short taster_poti_kw_n_oben_unten;  /* Drehzahlen KW oben, unten     [-] */  // Nur Modellwalzwerk
    	short taster_poti_reserve;          /* Man. Ringverlagerung          [-] */  // Nur Modellwalzwerk

    	Byte poti_taster[2];               /* Taster                        [-] */  // Nur Modellwalzwerk

    	/* Abstand Zentrierrollenachse - Hauptwalzenachse in x-Richtung (parallel zur Walzwerksachse) */
    	float za_x_abstand;      // Nur Modellwalzwerk

      /* Ringgeometrie */
    	/** @var da
    	 * @brief Aeusserer Durchmesser des Rings in [mm]*/
    	float da;
    	// TODO Add Doxygen Commnts
    	float da_of;
    	/** @var di
    	 * @brief Innerer Durchmesser des Rings in [mm]*/
    	float di;
    	// TODO Add Doxygen Commnts
    	float di_of;
    	/** @var dm
    	 * @brief Mittlerer Durchmesser des Rings in [mm]*/
    	float dm;
    	// TODO Add Doxygen Commnts
    	float dm_of;
    	// TODO Add Doxygen Commnts
    	 /* @brief */
    	float fertig_ho_soll;
    	 // TODO Add Doxygen Commnts
    	float fertig_wd_soll;
    	/** @var h0a
    	 * @brief Ringhoehe axial einlaufend in [mm]*/
    	float h0a;
    	/** @var h0r
    	 * @brief Ringhoehe radial einlaufend in [mm]*/
    	float h0r;
    	/** @var h1r
    	 * @brief Ringhoehe radial auslaufend in [mm]*/
    	float h1r;
    	/** @var h1a
    	 * @brief Ringhoehe axial auslaufend in [mm]*/
    	float h1a;
    	// TODO Add Doxygen Commnts
    	float h1a_of;
    	/** @var s0a
    	 * @brief Wanddicke axial einlaufend [mm]*/
    	float s0a;
    	/** @var s0r
    	 * @brief Wanddicke radial einlaufend in [mm]*/
    	float s0r;
    	/** @var s1a
    	 * @brief Wanddicke axial auslaufend in [mm]*/
    	float s1a;
    	/** var s1r
    	 * @brief Wanddicke radial auslaufend in [mm]*/
    	float s1r;
    	// TODO Add Doxygen Commnts
    	float s1r_of;
    	/** @var sfh
    	 * @brief Wanddicke bei Fertgihoehe in [mm]*/
    	float sfh;
    	// TODO Add Doxygen Commnts
    	float skw;
    	// TODO Add Doxygen Commnts
    	float skw_of;
    	/** @var wa_dvol
    	 * @brief Berechnete Volumendifferenz in [%]*/
    	float wa_dvol;

    	/*Erweiterung gegen¸ber MRAW*/
    	/** @var Vorform
    	 * @brief Struktur eines Rohlings*/
    	struct  Rohling Vorform;
    	/** @var Werkzeug
    	 * @brief Struktur eines Werkzeugs*/
    	struct Werkzeug Werkzeug;
    		/* Getriebeuntersetzung Hauptwalzenmotor  i= n_Antrieb/n_Abtrieb (i>1 ist Untersetzung) */
    	/** @var hw_ir
    	 * @brief Getriebeuebersetung Hauptwalze in [-]*/
    	float hw_ir;
    	/** @var kw_ia
    	 * @brief Getriebeuebersetzung Kegelswalze in [-]*/
    	float kw_ia;

    	/** @var Ibf_Achse1
    	 * @brief Messachse IBF 1 in [mm] Erweiterung des Bannings*/
    	float Ibf_Achse1;
    	/** @var Ibf_Achse2
    	 * @brief Messachse IBF 2 in [mm] Erweiterung des Bannings*/
    	float Ibf_Achse2;
    	/** @var Ibf_Achse3
    	 * @brief Messachse IBF 3 in [mm] Erweiterung des Bannings*/
    	float Ibf_Achse3;
    	/** @var Ibf_Achse4
    	 * @brief Messachse IBF 4 in [mm] Erweiterung des Bannings*/
    	float Ibf_Achse4;

    	/** @var ag_pos_real
    	 * @brief Test der Anzeige der realen Axialgeruestposition*/
    	float ag_pos_real;    // Testen der Anzeige der realen Axialger¸stposition

    	/** @var Test
    	 * @brief Struktur einer Testfahrt*/
    	struct Testfahrt Test;



    	// TEST TEST TEST
    	float h1a_o_of; // Nur Modellwalzwerk
    	float h1a_u_of; // Nur Modellwalzwerk

    	/* Reserve Byte */
    	char  dummy[522];

    	//short			speichern_zeit_flag;
    	//short			speichern_inkrement;
   };

/*--------------------------------------------------------------------------*/
/*	Soll-Werte: Soll_Inter                                                  */
/*--------------------------------------------------------------------------*/

/**
 * \struct Def_Soll_Inter
 * Diese Strukur enthält Informationen über den Verarbeitungs Prozess. Es ist
 * hinterlegt sind Zustellgeschwindigkeiten, Endpositionen der Schlitten und
 * Angaben zu Drehzahl hinterlegt. Außerdem ist eine präzise Angabe vorhanden
 * welche Kraftregler aktiv sind und mit welcher Kraft sie, sollten sie aktiv sein
 * wirken. Zuletzt sind auch Angaben über die Betriebsart hinterlegt.
 * Weitere Infomrationen zu den Variablen sind im Quellcode als Kommentare zu den
 * jeweiligen Variablen hinterlegt.
 *
 */
   struct Def_Soll_Inter
   { 
	   	   	   /* Zustellgeschwindigkeiten */
	   /** @var rs_v
	    * @brief Zustellgeschwindigkeit des Radialschlittens in [mm/s]*/
      float rs_v;
      /** @var aso_v
       * @brief Zustellgeschwindigkeit des Axialschlittens oben in [mm/s]*/
      float aso_v;
      /** @var asu_v
       * @brief Zustellgeschwindigkeit des Axialschlitten unten in [mm/s] */
      float asu_v;
      /** @var ag_v
       * @brief Zustellgeschwindigkeit des Axialgeruests in [mm/s]*/
      float ag_v;
      /** @var zal_v
       * @brief Zustellungsgeschwindigkeit des Zentrierarms links in [mm/s]*/
      float zal_v;
      /** @var zar_v
       * @brief Zustellungsgeschwindigkeit des Zentrierarms rechts in [mm/s]*/
      float zar_v;


      	  	  	  /* Sollpositionen */
      
      /** @var rs_pos
       * @brief Soll-Position des Radialschlittens in [mm]*/
      float rs_pos;
      /** @var aso_pos
       * @brief Soll-Position des Axialschlittens oben in [mm]*/
      float aso_pos;
      /** @var asu_pos
       * @brief Soll-Position des Axialschlittens unten in [mm]*/
      float asu_pos;
      /** @var ag_pos
       * @brief Soll-Position des Axialgeruestes in [mm]*/
      float ag_pos;
      /** @var zal_pos
       * @brief Soll-Position des Zerntrierarms links in [mm]*/
      float zal_pos;
      /** @var zar_pos
       * @brief Soll-Position des Zentrierarms rechts in [mm]*/
      float zar_pos;
      		 	

      	  	  	  	  /* Drehzahlen */
      /** @var hw_n
       * @brief Soll-Drehzahl der Hauptwalze in [1/min]*/
      float hw_n;
      /** @var kwo_n
       * @brief Soll-Drehzahl der Kegelwalze oben in [1/min]*/
      float kwo_n;
      /** @var kwu_n
       * @brief Soll-Drehzahl der Kegelwalze unten in [1/min]*/
      float kwu_n;
      
      /** @var schritt_nr
       * @brief Schrittnummer*/
      short schritt_nr;			
      
      /** @var za_x_abstand
       * @brief Abstand Zentrierrollenachse - Hauptwalzenachse in x-Richtung (parallel zur Walzwerksachse)*/
      float za_x_abstand;


      /** @var rs_kraftregler_aktiv
       * @brief 1 genau dann wenn der Kraftregler des Radialschlittens aktiv ist, sonst 0*/
      int   rs_kraftregler_aktiv;   /* [0-1] */
      /** @var aso_kraftregler_aktiv
       * @brief 1 genau dann wenn der Kraftregler des Axialsclittens oben aktiv ist, sonst 0 */
      int   aso_kraftregler_aktiv;
      /** @var asu_kraftregler_aktiv
       * @brief 1 genau dann wenn der Kraftregler des Axialschlittens unten aktiv ist, sonst 0 */
      int   asu_kraftregler_aktiv;
      /** @var ag_kraftregler_aktiv
       * @brief 1 genau dann wenn der Kraftregler des Axialgerüsts aktiv ist, sonst 0*/
      int   ag_kraftregler_aktiv;
      /** @var zal_kraftregler_aktiv
       * @brief 1 genau dann wenn der Kraftregler des Zentierarms links aktiv ist, sonst 0 */
      int   zal_kraftregler_aktiv;
      /** @var zar_kraftregler_aktiv
       * @brief 1 genau dann wenn der Kraftregler des Zentriearms rechts aktiv ist, sonst 0 */
      int   zar_kraftregler_aktiv;


      /** @var rs_kraft
       * @brief Soll-Kraft des Radialschlittens in [N]*/
      float rs_kraft;
      /** @var aso_kraft
       * @brief Soll-Kraft des Axialschlittens oben in [N]*/
      float aso_kraft;
      /** @var asu_kraft
       * @brief Soll-Kraft des Axialschlittens unten in [N]*/
      float asu_kraft;
      /** @var ag_kraft
       * @brief Soll-Kraft des Axialgerüsts in [N]*/
      float ag_kraft;
      /** @var zal_kraft
       * @brief Soll-Kraft des Zentrierarms links in [N]*/
      float zal_kraft;
      /** @var zar_kraft
       * @brief Soll-Kraft des Zentrierarm rechts in [N] */
      float zar_kraft;

      // TODO Add Doxygen Commnts
      int   ag_act;


      	  	  /* Betriebsarten */

      /** @var rs_mode
       * Betriebsart Vorschub (= 0) oder Kraftregelung (= 1)*/
      int   rs_mode;
      /** @var aso_mode
       * @brief Betriebsart Vorschub (= 0) oder Kraftregelung (= 1)*/
      int   aso_mode;
      /** @var ag_mode
       * @brief Betriebsart Vorschub (= 0) oder Kraftregelung (= 1)*/
      int   ag_mode;
      /** @var zen_mode
       *        * @brief Betriebsart Vorschub (= 0) oder Kraftregelung (= 1)*/
      int   zen_mode;
   };

/*-----------------------------------------------------------------------*/
/* Definition der Steuerbytes von PC an Modellwalzwerk                   */
/*-----------------------------------------------------------------------*/
/** \struct Def_Steuerbyte
 * @brief Definition der Steuerbytes von PC an Modellwalzwerk*/
struct Def_Steuerbyte
{
	   /** @var modus
	    * @brief Es existieren drei Betriebszustände:
	    * 											0 = Inaktiv
	    * 											1 = Handbetrieb
	    * 											2 = Autmatikbetrieb
	    * 											3 = kalibrierbetrib*/
	   Byte modus;

	   /** @var freigabe
	    * @brief Es exisistieren für die 8 Antriebe jeweils ein Bit für die Freigabe
	    * 				1 Bit 0: Radialschlitten
	    * 				2 Bit 1: Axialgeruest NEU, war -schlitten
	    * 				4 Bit 2: Axialschlitten NEU, war -geruest
	    * 				8 Bit 3: Zentrierarm links
	    * 			   16 Bit 4: Zentrierarm rechts
	    * 			   32 Bit 5: Axialschlitten unten NEU, war Walzantrieb
	    * 			   64 Bit 6: Walzenantribe NEU, war Axialschlittenbremse
	    * 			  128 Bit 7: Axialschlittenbremse NEU*/
	   Byte freigabe;
};

int In_RWTH_LOG_Schreiben(char *buffer);
//int irgendetwas(char *Hallo);
    


//class---------------------------------------------------------------------
   class RPW
   {
      public:
        //float  diam_hw;             /* Werkzeugdurchmesser Hauptwalze [mm] */
		/** @var diam_dw
		 * @brief Werkzeugdurchmesser Dornwalze in [mm]*/
        float  diam_dw;

        //float  hw_ir;               /* Getriebeuntersetzung Hauptwalzenmotor */
        //float  kw_ia;               /* Getriebeuntersetzung Kegelwalzenmotor */
        /** @var sin_kw_winkel_halbe
         * @brief Wert des Sinus vom 'halben Kegelwalzwinkel' {sin(22.5∞)}*/
        float  sin_kw_winkel_halbe;


        /** @var offset_rs
         * @brief Offset des Radialschlittens*/
        float offset_rs;
        /** @var offset_agr
         * @brief Offset des Axialgeruests*/
        float offset_agr;
        /** @var offset_aso
         * @brief Offset des Axialschlittens oben*/
        float offset_aso;
        /** var offset_asu
         * @brief Offset des Axialschlittens unten*/
        float offset_asu;
        /** @var offset_tr
         * @brief Offset der Tastrolle*/
        float offset_tr;	

      public:

      RPW();

      int Main_RAW(  int    ITER,
                     struct Def_Ein_Puff    Ein_Puff,
                     struct Def_Lokal_Puff  Lokal_Puff,
                     struct Def_Aus_Puff    Aus_Puff,
                     struct Def_Ein_Onli    Ein_Onli,
                     struct Def_Aus_Onli    Aus_Onli,
                     struct Def_Ist_Inter   *ist_inter,
                     struct Def_Soll_Inter  *soll_inter,
                     struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                     struct Def_IBF_Allgemein_IST * Ist_IBF);


      int Istwerte_RAW(struct Def_Ein_Onli    Ein_Onli,
                       struct Def_Ein_Puff    Ein_Puff,
                       struct Def_Lokal_Puff  Lokal_Puff,
                       struct Def_Aus_Puff    Aus_Puff,
                       struct Def_Ist_Inter   *ist_inter);

      int IstIBF_IstInter(struct Def_Ist_Inter          Ist_Inter,
                          struct Def_IBF_Allgemein_IST  *Ist_IBF);


      int IstIBF_SollIBF(struct Def_IBF_Allgemein_SOLL  Soll_IBF,
                         struct Def_IBF_Allgemein_IST  *Ist_IBF);
                            

      int Main(struct Def_Ist_Inter          Ist_Inter,
               struct Def_IBF_Allgemein_IST  Ist_IBF, 
               struct Def_Soll_Inter         *Soll_Inter,
               struct Def_IBF_Allgemein_SOLL *Soll_IBF);


      
      int flexibel_Radial(struct Def_Ist_Inter          Ist_Inter,
                          struct Def_IBF_Allgemein_IST  Ist_IBF, 
                          struct Def_Soll_Inter         *Soll_Inter,
                          struct Def_IBF_Allgemein_SOLL *Soll_IBF);

      int flexibel_Axial(struct Def_Ist_Inter          Ist_Inter,
                         struct Def_IBF_Allgemein_IST  Ist_IBF, 
                         struct Def_Soll_Inter         *Soll_Inter,
                         struct Def_IBF_Allgemein_SOLL *Soll_IBF);

	  int formenspektrum(struct Def_Ist_Inter           Ist_Inter,
                       struct Def_IBF_Allgemein_IST   Ist_IBF,
					   struct Def_Soll_Inter          *Soll_Inter,
					   struct Def_IBF_Allgemein_SOLL  *Soll_IBF);

      
      int Modus_AG(struct Def_Soll_Inter        *Soll_Inter, 
                   struct Def_IBF_Allgemein_IST *Ist_IBF, 
                   int    Auswahl);

      int Kr_Geo_berechnen(struct Def_IBF_Allgemein_IST *Ist_IBF);
      int Kr_Geo_pruefen(struct Def_IBF_Allgemein_IST *Ist_IBF);

      int IBFPARA_auslesen(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

      

   };


#endif




