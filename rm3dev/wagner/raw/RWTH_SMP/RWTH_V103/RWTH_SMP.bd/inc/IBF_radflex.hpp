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
        float a;            /* Hauptwalzendurch. * Durchmesser */
	   	float b;            /* Innendurchmesser(Durchmesser-2*Wandstärke) * Dornwalze */
	   	float c;            /* Hauptwalzemdurch. + Durchmesser */
	   	float d;      		/* Durchmesser - Dornwalze */
	   	float e;            /* Cr * Cr */
	   				    
	   	float o;            /* (a/c) * (b/d) */
	   	float u;            /* (a/c) + (b/d) */ 
	   				    
	   	float g;            /* (Wanddicke + 1/e*(o/u)); */
		float f;            /* 2 * g */

        /* Variablendeklaration*/

        int os_i;           /* Feldnummer */
        float Array[2];     /* Feld für Wanddicke [mm] */
		                
    };

    struct Breitung
    {
        float mr;           /* Breitungsexponent */
        float qf;           /* Verhältnis Wanddicke-Werkzeughöhe*/
        float ga;           /* Verhältnis Wanddicke-Rohlingshöhe h0*/
        float e_mr;         /* natürlichen Logarithmus der Breitung */

        float Da_t2;        /* berechneter Durchmesser zum nächsten Zeitpunkt (mm)*/
        float Di_t2;        /* berechneter Durchmesser zum nächsten Zeitpunkt (mm)*/
        float Da_t2_h2;     /* quadrierter Wert (mm^2) */
        float Di_t2_h2;     /* quadrierter Wert (mm^2) */

        float Volumen_t1;   /* aktuelles Volumen der Umformzone (mm^3)*/
        float Volumen_t2;   /* berechnetes Volumen zum nachfolgenden Zeitpunkt (mm^3) */
        float Volumen_diff; /* Volumendifferenz, des verdrängten Volumenanteils (mm^3)*/
        float delta_h;      /* Höhenzunahme Axialschlitten (mm) */
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


        /* Kräfte */

        /* Positionen / Abnahmen */

        float delta_h;              /* berechnete Höhenabnahme zum Zeitpunkt t für den Zeitpunkt t+1 [mm] */
        float delta_s;              /* Eindringtiefe in Ringwand aus IBF_Data.ini                    [mm] */
        float abnahme_s;            /* Abnahme der Wanddicke für diskont. Vorschub über Weg          [mm] */

        float Soll_Wanddicke;       /* Soll-Wanddicke für Modus mit Walzspaltzustellung Cr           [mm] */


        /* Positionsmerker / Zeitmarken */

        float t_dis_h;               /* Haltezeit für diskontinuierliche Walzung */
        int Umdrehungen;             /* Anzahl der Umdrehungen in der Rundungsphase aus IBF_Para.ini*/
        float t_warte;               /* WartezeiFt */

        
        /* Geometrien: weitere Variablen */

        float s_f;                  /* Auslaufende Wanddicke zur Zeit t (Daten aus TRT-Task)                  [mm] */
        float s_f_alt;              /* Auslaufende Wanddicke zur Zeit t-1 (Daten aus TRT-Task)                [mm] */

        struct Filter s_f_Filter;   /* Filter der aktuellen Wandposition für sehr kleine Positionierungen */
        
        float Werkzeugbreite;       /* Breite Profilierwerkzeug aus IBF_Para.ini        [mm] */

        float Anfangsposition_DW;   /* Postion die der Dorn angefahren ist, um Zustellung für ersten Ringumdrehung zu berechnen (MRAW ->Afpos_dw)  [mm] */    

        float Stegstaerke;          /* Stegstärke (Soll & Ist) aus IBF_Data.ini             [mm] */

        float Rohlinghoehe;        /* Variable wird für Axialschlittenposition benötig aus IBF_Data.ini [mm]*/
        
       

        /* Dynamik */
        float Vorschubgeschw_Dw;   /* Vorschubgeschwindigkeit Dornwalze ->IBF_Para.ini       [mm/s] */
        float Vorschubgeschw_ASO;  /* Vorschubgeschwindigkeit Kegelwalze->IBF_Para.ini       [mm/s] in case 17 */
        float eps_Vorschub;        /* Epsilon für disk. Vorschub über Weg                    [o.E.] */
        //float Vorschub_v;        /* Berechnete Vorschubgeschwindigkeit ÜBERPRÜFEN, ob diese Variable noch benötigt wird         [mm/s] */
        float dw_vn;               /* Vorschubgeschwindigkeit für Vorschub mit Cr-Berechnung [mm/s] */

        /* Verhätlnis */

        float Walzspalt_Cr;          /* Walzspaltverhältnis aus IBF_Data.ini */
        
        struct Cr_Berechnung Cr;     /* */
        
        struct Breitung Breitung;   /* Struktur für Berechnung des Breitungsfaktors*/
    };


#endif
