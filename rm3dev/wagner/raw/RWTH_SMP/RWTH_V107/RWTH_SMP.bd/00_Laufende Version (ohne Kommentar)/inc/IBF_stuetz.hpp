/*--FILE HEADER---------------------------------------------------------------
;   filename        : ibf_stuetz.hpp
;   version         : V1.0
;   contents        : IBF-St�tzstellenberechnung  
;   author          : S. Frank, IBF RWTH Aachen
;   date            : M�rz, 2008
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
;   M�rz , 17.2008  0001  S.F.  original issue V1.0
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/






#ifndef _IBF_stuetz_HPP
   #define _IBF_stuetz_HPP


#define maxstellen 25           // Legt (max.) Anzahl von St�tzstellen fest. Vorhandensein der Variable vereinfacht das Handling des Array in 
						       // Schleifen. Ein Wert von mehr als 50 vermutlich nicht sinnvoll. Je nach Zustellgeschwindigkeit (und anderen
						       // Parametern bzgl. des Walzspaltverh�ltnisses) wird sich evtl. eine charakteristische zustellen-Pause-zustellen... 
 						       // Folge auftreten. Existieren zu viele St�tzstellen, ist die Geschwindigkeit zu gering, etc., so entfallen die
						       // Pausen da Zustellung langsamer erfolgt als St�tzstellenwechsel!


// Funktionsprototypen 
void stuetzstellen(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

void konst_cr_radial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
void konst_cr_axial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);



struct stuetzstellen_var
{
	//stuetz_var enth�lt Variablen zur St�tzstellenberechnung!

	float t_U; 					       // Zeit f�r eine Ringumdrehung gemessen in s //t_U = (float)(diam_f/(diam_hw*f_H));
	float crtimer;                     //als Z�hlvariable zur Bestimmung des St�tzstellenwechsels

	float stellen[2][maxstellen];	  // Array zur Aufnahme der St�tzstellen. 0. Spalte f�r Wanddicke, 1. f�r H�he!
	int merker;		                  // Variable, welche die jeweils aktive St�tzstelle im Array aufnimmt
	int skip_faktor;	              // Wird verwendet um hohe Werte von maxstellen bei kleinen Ringen umsetzen zu k�nnen
    float kontrollmerker;             // Merker zur Korrektur der Nachkommastelle

	float cr;      //Walzspaltverh�ltnis Radial
	float ca;      //Walzspaltverh�ltnis Axial

    float delta_h;  // Stichabnahme f�r 1 Ringumdrehung an Stutzstelle i
    float delta_s;  // Stichabnahme f�r 1 Ringumdrehung an Stutzstelle i

};


#endif
