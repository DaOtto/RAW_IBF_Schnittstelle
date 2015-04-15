/*--FILE HEADER---------------------------------------------------------------
;   filename        : DW-Regel.hpp
;   version         : V1.0
;   contents        : IBF-Regelfunktion DW
;   author          : V. Jenkouk, D. Michl IBF RWTH Aachen
;   date            : Mai, 2008
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
;   März , 17.2008  0001  V.J.; D.M.  original issue V1.0
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/






#ifndef _DW_Regel_HPP
   #define _DW_Regel_HPP


//Funktionsprototypen





// Struktur
struct NAME_Eingang
{

 // Dyn. Werte    
 float Messwert_a;          // Messwert vom temporäres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
 
 //Const. Werte
 float Abstand_C;           // const. Abstand am temporären Messystem (vgl. Zeichnung Abb. 3.2 DA Jenkouk)  [mm]
 float cos_zeta;            // const. Cos(zeta)        Winkel nach Zeichnung                                [°]
 float sin_zeta;            // const. Sin(zeta)        Winkel nach Zeichnung                                [°]
 float Tastrollen_Radius;   // const. Radius der Tastrolle am temporären Messsystem                         [mm]
 float Offset_th_Spitze_MS; // Offset th. Spitze_Kegelwalze bis Lot 'Nullpunkt-MS' auf Maschinenlängsachse  [mm]
 
 
};

struct NAME_Ausgang
{
    
  float Wanddicke_berechnet; // berechnete Wanddicke                                                        [mm]
  float DW_Pos_soll;         // Soll DW-Position                                                            [mm]

};



#endif


