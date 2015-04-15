/*--FILE HEADER---------------------------------------------------------------
;   filename        : ibf_stuetz.hpp
;   version         : V1.0
;   contents        : IBF-Stützstellenberechnung  
;   author          : S. Frank, IBF RWTH Aachen
;   date            : März, 2008
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
;   März , 17.2008  0001  S.F.  original issue V1.0
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _IBF_stuetz_HPP
   #define _IBF_stuetz_HPP

/** \def maxstellen 
 * @brief Legt (max.) Anzahl von Stützstellen fest. Vorhandensein der Variable vereinfacht das Handling des Array in 
 * Schleifen. Ein Wert von mehr als 50 vermutlich nicht sinnvoll. Je nach Zustellgeschwindigkeit (und anderen
 * Parametern bzgl. des Walzspaltverhältnisses) wird sich evtl. eine charakteristische zustellen-Pause-zustellen... 
 * Folge auftreten. Existieren zu viele Stützstellen, ist die Geschwindigkeit zu gering, etc., so entfallen die
 * Pausen da Zustellung langsamer erfolgt als Stützstellenwechsel!*/
#define maxstellen 25


// Funktionsprototypen 
void stuetzstellen(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF,
				   struct Def_IBF_Allgemein_SOLL* Soll_IBF);

void konst_cr_radial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF,
					 struct Def_IBF_Allgemein_SOLL* Soll_IBF);

void konst_cr_axial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF,
					struct Def_IBF_Allgemein_SOLL* Soll_IBF);


/** \struct stuetzstellen_var
 * @brief Struktur enthält Parameter zur Stützstellenberechnung*/
struct stuetzstellen_var
{
	/** @var t_U
	 * @brief Zeit für eine Ringumdrehung gemessen in [s]
	 * t_U = (float)(diam_f/(diam_hw*f_H))
	 */
	float t_U; 					       //t_U = (float)(diam_f/(diam_hw*f_H));
	/** @var crtimer
	 * @brief als Zählvariable zur Bestimmung des Stützstellenwechsels. */
	float crtimer;


	/** @var stellen
	 * @brief Array zur Aufnahme der Stützstellen. 0. Spalte fuer Wanddicke 1. fuer Hoehe*/
	float stellen[2][maxstellen];
	/** @var merker
	 * @brief Variable, welche die jeweils aktive Stützstelle im Array aufnimmt*/
	int merker;
	/** @var skip_faktor
	 * @brief Wird verwendet um hohe Werte von maxstellen bei kleinen Ringen umsetzen zu können*/
	int skip_faktor;
	/** @var kontrollmerker
	  * Merker zur Korrektur der Nachkommastelle*/
	float kontrollmerker;
	/** @var cr
	 * @brief Walzspaltzverhältnis Radial*/
	float cr;
	/** @var ca
	 * @brief Walzspaltverhältnis Axial*/
	float ca;

	/** @var delta_h
	 * @brief Stichabnahme für 1 Ringumdrehung an Stützstelle i*/
	float delta_h;
	/** delta_s
	 * @brief Stichabnahme für 1 Ringumdrehung an Stützstelle i*/
	float delta_s;
};


#endif
