/*--FILE HEADER---------------------------------------------------------------
;   filename        : IBF_radflex.hpp
;   version         : V1.0
;   contents        : IBF-Variablen IBF software 
;   author          : D. Michl, IBF RWTH Aachen
;   date            : October, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   enthält alle Strukturen, die für das flexible radiale 
;               Profilieren notwendig sind
;               
;
;       RMOS3  Version 3.30
;       CAD-UL Version V120C
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   Maerch , 10. 2006  0001  D.M.  original issue V1.1
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _IBF_radflex_HPP
   #define _IBF_radflex_HPP


/*-----------------------------------------------------------------------------------------*/
/*          Protottypen der IBF_Funktionen                                                 */
/*-----------------------------------------------------------------------------------------*/
    #include "ibf_tool.hpp"
        
    
/*-----------------------------------------------------------------------------------------*/ 
/*                  Struktur  Radial-Profilieremodul                                     */
/*-----------------------------------------------------------------------------------------*/

  struct Cr_Berechnung
    {
      /** @var a
       * @brief Hauptwalzendurchmesser * Durchmesser */
      float a;            
	   	/** @var b
	   	 * @brief Innendurchmesser(Durchmesser -2*Wandstaerke)*Dornwalze*/
      float b;            
	   	/** @var c
	   	 * Hauptwalzndurchmesser + Durchmesser*/
      float c;            
	   	/** @var d
	   	 * @brief Durchmesser - Dornwalze*/
      float d;      		
	   	/** @var e
	   	 * @brief Cr * Cr */
      float e;            /* Cr * Cr */

      /** @var o
       * @brief (\link a \endlink / \link c \endlink ) * (\link b \endlink / \link d \endlink )*/
	   	float o;
	   	/** @var u
	   	 * @brief (\link a \endlink / \link c \endlink ) + (\link b \endlink / \link d \endlink )*/
	   	float u;            /*  */

	   	/** @var g
	   	 * @brief (Wanddicke + 1/\link e \endlink *(\link o \endlink / \link u \endlink ))*/
	   	float g;            /* ; */
	   	/** @var f
	   	 * @brief 2 * g*/
      float f;            /* 2 * g */

      /* Variablendeklaration*/

      /** @var os_i
       * @brief Feldnummer*/
      int os_i;           /* Feldnummer */
      /** @var Array[2]
       * @brief Feld fuer Wanddicke in [mm]*/
      float Array[2];     /* Feld für Wanddicke [mm] */
		                
    };

    /** \struct Breitung
      * @brief Informationen zur Breitung eines Ringes, auch im Vergleich zum 
      *   ursprünglichen Rohlings
      */
    struct Breitung
    {
	  /** @var mr
	   * @brief Breitungseponent*/
        float mr;
        /** @var qf
         * @brief Verhaeltnis Wanddicke zu Werkzeughoehe*/
        float qf;
        /** @var ga
         * @brief Verhaeltnis Wanddicke zu Rohlingshoehe h0*/
        float ga;
        /** @var e_mr
         * @brief natuerlicher Logarithmus der Breitung*/
        float e_mr;

        /** @var Da_t2
         * @brief berechneter Durchmesser zum naechsten Zeitpunk in [mm]*/
        float Da_t2;
        /** @var Di_t2
         * @brief berechneter Durchmesser zum naechsten Zeitpunkt in [mm]*/
        float Di_t2;
        /** @var Da_t2_h2
         * @brief quadierter Wert [mm^2]*/
        float Da_t2_h2;
        /** @var Di_t2_h2
         * @brief quadrierter Wert [mm^2]*/
        float Di_t2_h2;


        /** @var Volumen_t1
         * @brief aktuelles Volumen der Umformzone in [mm^3]*/
        float Volumen_t1;
        /** @var Volumen_t2
         * @brief berechnetes Volumen zum nachfolgenden Zeitpunk  [mm^3]*/
        float Volumen_t2;
        /** @var Volumen_diff
         * @brief Volumendifferenz des verdraengten Volumenanteils [mm^3]*/
        float Volumen_diff; 
        /** @var delta_h
         * @brief Hoehenzuname Axialschlitten in [mm]*/
        float delta_h;
    };

    
    struct Filter
    {
        float yF_neu;
        float yF_alt;        
    };

    /** \struct Radial_Flex_Prof
      * @brief Notwendige informationen zum Radialen Profilieren*/
    struct Radial_Flex_Prof
    {
        /* Wahlschalter /spezial Flags  */
	/** @var Schalter_Kont_DisKo
	  * @brief <p>Diese Variable legt fest, wie sich der Vorschub beim radialen 
    * Profilieren verhaelt.</p>
	  * <p> 0 => Kontinuierlicher Vorschub</p>
	  * <p> 1 => Diskontinuierlicher Vorschub </p>
	  * <p> 2 => Ingos Cr-Berechnung </p>*/
        int Schalter_Kont_DisKo; 
        int t_warte_flag;
        /** @var Profilflag
	  * @brief Legt fest, in welcher Phase des radialen Profilierens sich der Ring
    * gerade befindet
    */
	int Profilflag;


        /* Kräfte */

        /* Positionen / Abnahmen */

        /** @var delta_h
         * @brief berechnet die Hoehenabnahme zum Zeitpunkt t fuer den Zeitpunkt t+1 in [mm]*/
        float delta_h;
        /** @var delta_s
         * @brief */
        float delta_s;              
        /** @var abnahme_s
         * @brief Abnahme der Wanddicke fuer diskont. Vorschub ueber Weg in [mm]*/
        float abnahme_s;            


        /** @var Soll_Wanddicke
         * @brief Soll-Wanddicke fuer Modus mit Walzspaltzustellung Cr in [mm]*/
        float Soll_Wanddicke;       


        /* Positionsmerker / Zeitmarken */

        /** @var t_dis_h
         * @brief Haltezeit fuer diskontinuierliche Walzung*/
        float t_dis_h;               
        /** @var Umdrehungen
         * @brief Anzahl der Umdrehungen in de Rundungsphase aus IBF_Para.ini*/
        int Umdrehungen;             /* Anzahl der Umdrehungen in der Rundungsphase aus IBF_Para.ini*/
        /** @var t_warte
         * @brief Wartezeit*/
        float t_warte;               

        
        /* Geometrien: weitere Variablen */

        /** @var s_f
         * @brief Auslaufende Wanddicke zur Zeit t (Daten aus TRT-Task) in [mm]*/
        float s_f;                 
        /** @var s_f_alt
         * @brief Auslaufende Wanddicke zur Zeit t-1 (Daten aus TRT-Task) in [mm]*/
        float s_f_alt;              

        /** @var s_f_Filter
         * @brief Struktur eines Filters mit aktuellen Wandpositionen fuer sehr kleine Positionierungen*/
        struct Filter s_f_Filter;   
        
        /** @var Werkzeugbreite
         * @brief Breite Profilierwerkzeug aus IBF_Para.ini*/
        float Werkzeugbreite;       

        /** @var Anfangsposition_DW
         * @brief Position die der Dorn angefahren ist, um Zustellung fuer ersten Ringumdrehung zu berechen (MRW -> Afpos_dw) in [mm]*/
        float Anfangsposition_DW;   

        /** @var Stegstaerke
         * @brief Stegstearke (Soll & Ist) aus IBF_Data.ini in [mm]*/
        float Stegstaerke;          

        /** @var Rohlinghoehe
         * @brief Variable wird fuer Axialschlittenposition benoetigt aus IBF_Data.ini in [mm]*/
        float Rohlinghoehe;        
        
       

        /* Dynamik */
        /** @var Vorschubgeschw_Dw
         * @brief Vorschubsgeschwindigkeit Dornwalze -> IBF_Para.ini in [mm/s]*/
        float Vorschubgeschw_Dw;   
        /** @var Vorschubgeschw_ASO
         * @brief Vorschubgeschwindigkeit Kegelwalze -> IBF_Para.ini in [mm/s] in case 17*/
        float Vorschubgeschw_ASO;  
        /** @var eps_Vorschub
         * @brief Epsilon fuer disk. Vorschub ueber Weg*/
        float eps_Vorschub;        
        //float Vorschub_v;        /* Berechnete Vorschubgeschwindigkeit ÜBERPRÜFEN, ob diese Variable noch benötigt wird         [mm/s] */
        /** @var dw_vn
         * @brief Vorschubgeschwindigkeit fuer VOrschub mit Cr-Berechnung in [mm/s]*/
        float dw_vn;               

        /* Verhätlnis */

        /** @var Walzspalt_Cr
         * @brief Walzspaltverhaeltnis aus IBF_Data.ini*/
        float Walzspalt_Cr;          
        
        struct Cr_Berechnung Cr;     
        
        /** @var Breitung
         * @brief Struktur fuer Berechnung des Breitungsfaktor*/
        struct Breitung Breitung;   
    };


#endif
