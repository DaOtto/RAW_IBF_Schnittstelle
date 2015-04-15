/*--FILE HEADER---------------------------------------------------------------
;   filename        : IBF_formenspek.hpp
;   version         : V1.0
;   contents        : IBF-Variablen IBF software 
;   author          : J. Bedoui, D. Michl, IBF RWTH Aachen
;					: V.Goldbach	
;   date            : July, 2008
;					: February, 2009 (Go)
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   enthält alle Strukturen, die für das Projekt
;               Formenspektrum benötigt werden
;               
;
;       RMOS3  Version 3.30
;       CAD-UL Version V120C
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   July , 11.2008  0001  D.M.  original issue V1.0
;	Febr,  09.2009  0002
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _IBF_formenspek_HPP
   #define _IBF_formenspek_HPP

/*-----------------------------------------------------------------------------------------*/
/*          Prototypen der IBF_Funktionen                                                 */
/*-----------------------------------------------------------------------------------------*/


//
struct Formenspektrum
{
	int Profilflag;
	float t_U_Viola;		///< Zeitberechnung Viola
	float delta_s_Viola;	///< berechnetes wanddickeabnahme
	float t_Halte;			///< Halte Zeit  in sec
	float proz_s;			///< Begrenzung auf Zahl zwischen 0 und 94 (0%-94% Abnahme)
	float Soll_RS_Pos_end;
	float epsilon;			///< Epsilon fuer Walzung mit konst. Epsilon-Wert
};


#endif
