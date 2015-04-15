/*--FILE HEADER---------------------------------------------------------------
;   filename        : IBF_axproflex.hpp
;   version         : V1.0
;   contents        : IBF-Variablen IBF software 
;   author          : D. Michl, IBF RWTH Aachen
;   date            : July, 2007
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   enthält alle Strukturen, die für das flexible axiale 
;               Profilieren notwendig sind
;               
;
;       RMOS3  Version 3.30
;       CAD-UL Version V120C
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   July , 19. 2007  0001  D.M.  original issue V1.0
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _IBF_axproflex_HPP
   #define _IBF_axproflex_HPP

   #include <rpw.hpp>

/*-----------------------------------------------------------------------------------------*/
/*          Protottypen der IBF_Funktionen                                                 */
/*-----------------------------------------------------------------------------------------*/
  

    //Los geht´s


    struct Def_Kragen_Geo
    {
        float Kr_Br;                            // Kragenbreite                                                 [mm]
        float Kr_d_nenn_mitte;                  // Nenndurchmesser Kragenmittelpunkt                            [mm]
        float Kr_d_nenn_vorne;                  // Nenndurchmesser Kragenvorderkante                            [mm]
        float Kr_d_nenn_hinten;                 // Nenndurchmesser Kragenhinterkante                            [mm]
        float Del_Kr_AGR;                       // Abstand hintere Kante Kragenwalze- theoretische Spitze       [mm]
        float max_Pr_Tiefe;                     // max. walzbare Profiltiefe durch Höhe der Kragenschenkel      [mm]
        float sin_kw_winkel_halbe;              // Halber Sinus-Winkel Kragenwalze                              [°]
        float l_fehlende_spitze_ukw;            // Länge der fehlenden Spitze an der unteren Kegelwalze         [mm]
        float l_mantel_ukw_o_fehlende_spitze;   // Länge der unteren KW von der reellen Spite bis Kragenwalze   [mm]
    };


//float Pos_auf_Mantel;   // Position des Ringaußendurchmessers auf der Mantelfläche

    struct Axial_Flex_Prof
    {
       
        float Anfahrdurchm;             // Vorgeg. Ringdurchmesser zum Anfahren des AG        [mm]
        struct Def_Kragen_Geo Kr_geo;   // Struktur Kragenwalzengeometrie                     [mm]
        float AGR_Pr;                   // Profilierposition auf Ringstrinseite               [mm]
        float Verh_pr_sf_proz_start;    // Verhältnis der Profilposition zur Vorringwanddicke [%]
        float Verh_pr_sf_proz;          // Verhältnis der Profilposition zur Wanddicke        [%]
        int Wert;                       // Variable in Funktion AGR_Nachfuehr_Entscheider()   ['A'/'I']
        float Vorschub;            // Zustellgeschwindigkeit der Kragenwalze             [mm/U]

    };


#endif
