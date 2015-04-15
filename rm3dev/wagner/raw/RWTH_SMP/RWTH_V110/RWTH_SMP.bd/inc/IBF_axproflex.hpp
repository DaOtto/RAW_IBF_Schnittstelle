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

   #include "rpw.hpp"

/*-----------------------------------------------------------------------------------------*/
/*          Protottypen der IBF_Funktionen                                                 */
/*-----------------------------------------------------------------------------------------*/


//---------------------------------------------------------------------------
// Setzungen
//---------------------------------------------------------------------------
   // Maximale Anzahl der walzbaren Profile
   #define PROF_ANZ_MAX 6
  

    //Los geht´s

    /** \struct Def_Kragen_Geo
      * @brief Informationen über die Kragenwalze
      */
    struct Def_Kragen_Geo
    {
    	/** @var Kr_Br
    	 * @brief Kragenbreite in [mm]*/
        float Kr_Br;
        /** @var Kr_d_nenn_mitte
         * @brief Nennduchmesser Kragenmittelpunk in [mm]*/
        float Kr_d_nenn_mitte;
        /** @var Kr_d_nenn_vorne
         * @brief Nennduchmesser Kragenvorderkante in [mm]*/
        float Kr_d_nenn_vorne;
        /** @var Kr_d_nenn_hinten
         * @brief Nennduchmesser Kragenhiterkante in [mm]*/
        float Kr_d_nenn_hinten;
        /** @var Del_Kr_AGR
         * @brief Abstand hintere Kante kragenwalze -theorethische Spitze in [mm]*/
        float Del_Kr_AGR;

        /** @var max_Pr_Tiefe
         * @brief maximale walzbare Profieltiefe durch Hoehe der Kragenschenkel [mm]*/
        float max_Pr_Tiefe;
        /** @var sin_kw_winkel_halbe
         * @brief Halber Sinus-Winkel Kragenwalze in [°]*/
        float sin_kw_winkel_halbe;
        /** @var l_fehlende_spitze_ukw
         * @brief Laenge der fehlenden Spitze an der unteren Kegelwalze in [mm]*/
        float l_fehlende_spitze_ukw;
        /** @var l_mantel_ukw_o_fehlende_spitze
         * @brief Laenge der unteren Kegelwalze von der reellen Spitze bis 
         * Kragenwalze in [mm]*/
        float l_mantel_ukw_o_fehlende_spitze;
        // Länge der unteren KW von der reellen Spite bis Kragenwalze   [mm]
    };

    /** \struct Def_Biss_Ver
      * @brief
      */
    struct Def_Biss_Ver
    {
        float Verhaeltnis;
        // Bissverhältnis für breite Profile                                    [%]
        float AG_Pos_alt;
        // Merker der vorherige Axialgerüstposition                             [mm]
        
        
        int Position;
        // Position des Bissversatzes Rechts- oder Links neben erster Stufe     [-]
        int Anzahl;
        // Anzahl der Bisse erste Ebene
        int Anzahl_zweite_Ebene;
        // Anzahl der Bisse zweite Ebene

        float AGR_Pr_Merker;
        // Zahlen-Merker der in IBFPare.ini vorgebenen Axialgerüstposition [0] für Neustart [mm]
        int AG_Pos_Erreicht;
        // Merker für Positonierung des AG in case 13 (Profilflag.Axial....)

    };
    
    struct Def_Turbine
    {
        int Turbinenscheibe;          // Schalter in inipara setzen
                
        int Ebene1_fertig;
        // Erste Ebene bestehend aus x-Biss gewalzt
        int AG_Pos_Erreicht;
        // Neuposition für zweite Ebende
        
        float s_akt_Merker;
        // Merker der aktuellen Wanddicke nach erreichen der ersten Ebene
        
        int Stufe_erreicht;
        // Erreichen der zweiten Stufe
        int zweite_Ebene_erreicht;
        // Erreichen der zeiten Ebene
    };


    /** 
	  * @struct Axial_Flex_Prof
      * Nötige Information über das axiale Profilieren.
      */
    struct Axial_Flex_Prof
    {
       /** 
	    * @var Profilflag
        * Profilflag fuer die Funtion Axialprofilieren
        * <p> Unter anderem sind die Werte </p>
        * <p> 9 Axialschlitten mit const. vorgegebener Geschwindigkeit zustellen
        * Axialgerüst mit Funktion AGR_Soll_Pos() positionieren Radialschlitten in
        * Kraftsteuerung an Ring andrücken, dafür muss allerdings Kraftsteuerung 
        * vorgewählt sein.
        * </p>
        * <p> 11 für die Rundungsphase </p>
        * <p> 12 Hochfahren des Axialschlittens und Abfragen, ob weitere Profilstufe 
        * gewalzt werden soll </p>
	      */
        int Profilflag;

        /** @var Anfahrdurchm
         * @brief Vorgegebenr Ringdurchmesser zum Anfahren des Axialgeruests in [mm]*/
        float Anfahrdurchm;
        /** @var Umdrehungen
         * @brief Umdrehungen in Rundungsphase in [-]*/
        int Umdrehungen;

        
        /** @var Kr_geo
         * @brief Strucktur vom Type \link Def_Kragen_Geo \endlink zur Beschreibung
         * der Kragenzwalzgeomtrie*/
        struct Def_Kragen_Geo Kr_geo;

        /** @var Biss
          * @brief Struktur mit Informationen über das Bissverhältnis*/
        struct Def_Biss_Ver Biss;
        // Struktur Bissverhältnis
        struct Def_Turbine Turbine;
        // Struktur zum walzen verschiedener Ebenenen wie bei Turbinenscheiben

        /** @var Profilanzahl
         * @brief Anzahl der zu walzenden Profile*/
        int Profilanzahl;
        /** @var Pr_Num
         * @brief Aktuelle zu walzende Profilnummer*/
        int Pr_Num;
        

        /** @var AGR_Pr[]
         * @brief Profilierposition auf der Ringstrinseite [mm]*/
        float AGR_Pr[PROF_ANZ_MAX];
        /** @var Pr_Tiefe[]
         * @brief Profieltefe*/
        float Pr_Tiefe[PROF_ANZ_MAX];
        /** @var Vorschub
         * @brief Zustellungsgeschwindigkeit der Kragenwalze in [mm/U]*/
        float Vorschub;


        /** Verh_pr_sf_proz_start
         * @brief Verhaeltnis der Profilposition zur Vorringwanddicke in [%]*/
        float Verh_pr_sf_proz_start;
        /** @var Verh_pr_sf_proz
         * @brief Verhaeltnis der Profilposition zur Wanddicke in [%]*/
        float Verh_pr_sf_proz;
        /** @var Wert
         * @brief Variable in Funtkion 
         * \link AGR_Nachfuehr_Entscheider() \endlink ['A'/'I'] */
        int Wert;

    };


#endif
