/*--FILE HEADER---------------------------------------------------------------
;   filename        : IBF_radflex.hpp
;   version         : V1.0
;   contents        : IBF-Variablen IBF software 
;   author          : D. Michl, IBF RWTH Aachen
;   date            : October, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   enth�lt alle Strukturen, die f�r das flexible radiale 
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
    };


#endif
