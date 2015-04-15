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
void stuetzstellen(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

void konst_cr_radial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
void konst_cr_axial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);


/** \struct stuetzstellen_var
 * @brief Struktur enthŠlt variablen zur Stutzstellenberechnung*/
struct stuetzstellen_var
{
	//stuetz_var enthält Variablen zur Stützstellenberechnung!

	/** @var t_U
	 * @brief Zeit fuer eine Ringumdrehung gemessein in [s]*/
	float t_U; 					       //t_U = (float)(diam_f/(diam_hw*f_H));
	/** @var crtimer
	 * @brief als Zaehlvariable zur Bestimmung des Stuetzstellenwechsel*/
	float crtimer;                     //als Zählvariable zur Bestimmung des Stützstellenwechsels


	/** @var stellen
	 * @brief Array zur Aufnahme der Stuetzstellen. 0. Spalte fuer Wanddicke 1. fuer Hoehe*/
	float stellen[2][maxstellen];	  // Array zur Aufnahme der Stützstellen. 0. Spalte für Wanddicke, 1. für Höhe!
	/** @var merker
	 * @brief Variable, welche die jeweils aktive Stuetzstelle im Array aufnimmt*/
	int merker;		                  // Variable, welche die jeweils aktive Stützstelle im Array aufnimmt
	/** @var skip_faktor
	 * @brief Wird verwendet um hohe Werte von Maxsgellen bei kleinen Ringen umsetzten zu koennen*/
	int skip_faktor;	              // Wird verwendet um hohe Werte von maxstellen bei kleinen Ringen umsetzen zu können
  /** @var kontrollmerker
    * Merker zur Korrektur der nachkommastelle*/
  float kontrollmerker;
	/** @var cr
	 * @brief Walzspaltzverhaetnis Radial*/
	float cr;      //Walzspaltverhältnis Radial
	/** @var ca
	 * @brief Walzspaltverhaeltnis Axial*/
	float ca;      //Walzspaltverhältnis Axial

	/** @var delta_h
	 * @brief Stichabnahme fuer 1 Ringumdrehung an Stuetzstelle i*/
    float delta_h;  // Stichabnahme für 1 Ringumdrehung an Stutzstelle i
    /** delta_s
     * @brief Stichabnahme fuer 1 Ringumdrehung an Stuetzstelle i*/
    float delta_s;  // Stichabnahme für 1 Ringumdrehung an Stutzstelle i

};


#endif
