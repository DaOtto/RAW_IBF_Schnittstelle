/*--FILE HEADER---------------------------------------------------------------
;   filename        : IBF_axproflex.hpp
;   version         : V1.0
;   contents        : IBF-Variablen IBF software 
;   author          : D. Michl, IBF RWTH Aachen
;   date            : July, 2007
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   enth�lt alle Strukturen, die f�r das flexible axiale 
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


//---------------------------------------------------------------------------
// Setzungen
//---------------------------------------------------------------------------
   // Maximale Anzahl der walzbaren Profile
   #define PROF_ANZ_MAX 6
  

    //Los geht�s


    struct Def_Kragen_Geo
    {
        float Kr_Br;                            // Kragenbreite                                                 [mm]
        float Kr_d_nenn_mitte;                  // Nenndurchmesser Kragenmittelpunkt                            [mm]
        float Kr_d_nenn_vorne;                  // Nenndurchmesser Kragenvorderkante                            [mm]
        float Kr_d_nenn_hinten;                 // Nenndurchmesser Kragenhinterkante                            [mm]
        float Del_Kr_AGR;                       // Abstand hintere Kante Kragenwalze- theoretische Spitze       [mm]
        float max_Pr_Tiefe;                     // max. walzbare Profiltiefe durch H�he der Kragenschenkel      [mm]
        float sin_kw_winkel_halbe;              // Halber Sinus-Winkel Kragenwalze                              [�]
        float l_fehlende_spitze_ukw;            // L�nge der fehlenden Spitze an der unteren Kegelwalze         [mm]
        float l_mantel_ukw_o_fehlende_spitze;   // L�nge der unteren KW von der reellen Spite bis Kragenwalze   [mm]
    };

    struct Def_Biss_Ver
    {
        float Verhaeltnis;          // Bissverh�ltnis f�r breite Profile                                    [%]
        float AG_Pos_alt;           // Merker der vorherige Axialger�stposition                             [mm]
        
        
        int Position;               // Position des Bissversatzes Rechts- oder Links neben erster Stufe     [-]
        int Anzahl;                 // Anzahl der Bisse erste Ebene
        int Anzahl_zweite_Ebene;    // Anzahl der Bisse zweite Ebene

        float AGR_Pr_Merker;        // Zahlen-Merker der in IBFPare.ini vorgebenen Axialger�stposition [0] f�r Neustart [mm]
        int AG_Pos_Erreicht;        // Merker f�r Positonierung des AG in case 13 (Profilflag.Axial....)

    };
    
    struct Def_Turbine
    {
        int Turbinenscheibe;          // Schalter in inipara setzen
                
        int Ebene1_fertig;           // Erste Ebene bestehend aus x-Biss gewalzt
        int AG_Pos_Erreicht;         // Neuposition f�r zweite Ebende
        
        float s_akt_Merker;            // Merker der aktuellen Wanddicke nach erreichen der ersten Ebene
        
        int Stufe_erreicht;         // Erreichen der zweiten Stufe
        int zweite_Ebene_erreicht;  // Erreichen der zeiten Ebene
    };


    
    //float Pos_auf_Mantel;   // Position des Ringau�endurchmessers auf der Mantelfl�che

    struct Axial_Flex_Prof
    {
       
        int Profilflag;                 // Profilflag f�r die Funktion Axialprofilieren
        
        float Anfahrdurchm;             // Vorgeg. Ringdurchmesser zum Anfahren des AG        [mm]
        int Umdrehungen;                // Umdrehungen in der Rundungsphase                   [-]
        
        struct Def_Kragen_Geo Kr_geo;   // Struktur Kragenwalzengeometrie                     [mm]
        struct Def_Biss_Ver Biss;       // Struktur Bissverh�ltnis
        struct Def_Turbine Turbine;     // Struktur zum walzen verschiedener Ebenenen wie bei Turbinenscheiben

        
        int Profilanzahl;               // Anzahl der zu walzenden Profile
        int Pr_Num;                     // aktuelle zu walzende Profilnummer

        float AGR_Pr[PROF_ANZ_MAX];     // Profilierposition auf Ringstrinseite               [mm]
        float Pr_Tiefe[PROF_ANZ_MAX];   // Profiltiefe                                        [mm]
        float Vorschub;                 // Zustellgeschwindigkeit der Kragenwalze             [mm/U]

        float Verh_pr_sf_proz_start;    // Verh�ltnis der Profilposition zur Vorringwanddicke [%]
        float Verh_pr_sf_proz;          // Verh�ltnis der Profilposition zur Wanddicke        [%]
        int Wert;                       // Variable in Funktion AGR_Nachfuehr_Entscheider()   ['A'/'I']

   
        
    };


#endif