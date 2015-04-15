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


#ifndef _IBF_dw_regelung_HPP
   #define __IBF_dw_regelung_HPP


#ifndef  cos_zeta
		/** @var cos_zeta
		 * @brief Winkel am Messystem nach Zeichnung cos(Winkel °)*/
#define  cos_zeta 0.64F            // Winkel am Messsystem nach Zeichnung cos(Winkel°)
#endif 

#ifndef  sin_zeta
		/** \def sin_zeta
		 * @brief Windkel Messsystem*/
#define  sin_zeta 0.768F            // Winkel Messsystem
#endif 

#ifndef  regel_zyklus_fak
		/** @var regel_zyklus_fak
		 * @brief Regelzykluszeit = regel_zyklus_fak * Abtatszeit(0.1 sec)*/
#define  regel_zyklus_fak  5        // Regelzykluszeit = regel_zyklus_fak * Abtastzeit(0,1 sec)
#endif 

#ifndef  Arraygroesse
		/** \def Arraygroesse
		 * @brief Groesse des Arrays*/
#define  Arraygroesse  20           // Arraygroesse
#endif 

//Funktionsprototypen

 // DW-Regelung
 void Beta                     (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void Alpha                    (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void Gamma                    (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void T_Einlauf                (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void Axial_Wanddicke_bestimmen(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void T_V                      (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void DW_Regelalgo             (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void DA_Jenkouk_Regler        (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

 
 void RS_nach_Messwert_Fahren  (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

 // AG-Regelung
 void AG_Regelalgo             (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void DA_Jenkouk_Regler_AG     (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void DA_Jenkouk_Regler        (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);






// Struktur
//DWR= Dornwalzenregelung
/** \struct Def_DW_Regelung_DA_Jenkouk
 * @brief Regelung der Dornwalze*/
struct Def_DW_Regelung_DA_Jenkouk
{
    
  int Funktios_Iter;         // Zaehler zur Überpruefung, ob Funktion aufgerufen wird
  // Eingangswerte 
  // Dyn. Werte
  /** @var Messwert_A
   * @brief Messwert vom temoraeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk) [mm]*/
  float Messwert_A;          // Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
  /** @var Messwert_A_mf
   * @brief Entspricht dem Abstand vom nächsten Punkt auf dem Ringinnendurchmesser zum Messystem.
   Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 4-7 DA Jenkouk)      [mm]*/
  float Messwert_A_mf;       // Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
  /** @var Messwert_A_alt_mf
   * @brief Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]*/
  float Messwert_A_alt_mf;   // Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]

  /** @var Messwert_A_unten
   * @brief Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]*/
  float Messwert_A_unten;          // Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
  /** @var Messwert_A_unten_mf
   * @brief  Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]*/
  float Messwert_A_unten_mf;       // Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
  /** @var Messwert_A_unten_alt_mf
   * @brief Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]*/
  float Messwert_A_unten_alt_mf;   // Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
 
 
 
 
  //Konstanten
  /** @var Abstand_C
   * @brief const. Abstand am temporaeren Messystem zur Achse des Ringwalzwerks (vgl. Zeichnung Abb. 4.6 DA Jenkouk)  [mm]*/
  float Abstand_C;           // const. Abstand am temporaeren Messystem (vgl. Zeichnung Abb. 3.2 DA Jenkouk)  [mm]
  //float cos_zeta;            // const. Cos(zeta)        Winkel nach Zeichnung                              [°]
  //float sin_zeta;            // const. Sin(zeta)        Winkel nach Zeichnung                              [°]
  /** @var Tastrollen_Radius
   * @brief const. Radius der Tastrolle am temporaeren Messsystem [mm]*/
  float Tastrollen_Radius;   // const. Radius der Tastrolle am temporaeren Messsystem                         [mm]
  /** @var Offset
   * @brief Offset th. Spitze_Kegelwalze bis Lot 'Nullpunkt-MS' auf Maschinenlaengsachse [mm]*/
  float Offset; // Offset th. Spitze_Kegelwalze bis Lot 'Nullpunkt-MS' auf Maschinenlaengsachse               [mm]

  /** @var Messwert_Nullpunkt
   * @brief Messwerte des Messystem 'innen', der angezeigt wird, wenn Zylinderstange ganz eingefahren ist [mm]*/
  float Messwert_Nullpunkt;  // Messwerte des Messystem 'innen', der angezeigt wird, wenn Zylinderstange ganz eingefahren ist [mm]
  /** @var Messwert_Nullpunkt_unten
   * @brief Messwert aussen [mm]*/
  float Messwert_Nullpunkt_unten; // Messwert aussen                                                         [mm]
  /** @var U_v_HW
   * @brief Umfangsgeschwindikeit an der Hauptwalze [mm/s]*/
  float U_v_HW;              // Umfangsgeschwindgkeit an Hauptwalze                                         [mm/s]
  /** @var DW_Durchmesser
   * @brief Durchmesser der Dornwalze in [mm]*/
  float DW_Durchmesser;      // Durchmesser der Dornwalze                                                   [mm]
  

  // Ausgangwerte / berechnete Variablen
  /** @var Wanddicke_berechnet
   * @brief Berechnete Wanddicke*/
  float Wanddicke_berechnet;
  /** @var DW_Pos_soll
   * @brief Soll-Position der Dornwalze*/
  float DW_Pos_soll;
  /** @var T_Einlauf
   * @brief Zeit, die benoetigt wird von der Messposition zum Radialwalzspalt [sec]*/
  float T_Einlauf;
  /** @var T_Verzoegerung
   * @brief Verzoegerungszeit [sec]
   * <p> Nach Kommentar in der Mehtode \link DW_Regelalgo \endlink ist dies die Zeit vom Start des Walzwerks bis zum 
   * Beginn des Messens am Messsystem. </p>
   * @bug T_Verzoegerung ist von der Bedeutung bisher unbestaetigt und uneindeutig*/
  float T_Verzoegerung;
  /** @var Anzahl_Zeitschritte
   * @brief Differenz der Anzahl der Regelzyklen
   * <p> Anzahl der Zeitschritte zwischen Aktivierung des Messsystems und Positionierung der Dornwalze</p>*/
  int Anzahl_Zeitschritte;

  //-------Winkel---- alle Winkel mathematisch positiv (gegen den Uhrzeigersinn) siehe Abbildung 3.2 DA Vahid
  /** @var Beta
   * @brief Winkel vom Messsystem bis Einlauf Radial-Walzspalt bez. Kreismittelpunkt in [° ]*/
  float Beta;
  /** @var Alpha
   * @brief Winkel  Maschinenachse bis Messsystem  bez. Kreismittelpunkt in [° ]*/
  float Alpha;
  /** @var Gamma
   * @brief Winkel vom Einlauf Radialwalzspalt bis Maschineneachse in [° ]*/
  float Gamma;

  /** @var ri
   * @brief Berechneter Innenradius mit Messvorrichtung in [mm]*/
  float ri;
  /** @var DW_soll_Pos[Arraygroesse]
   * @brief Feld mit berechneten Sollpositionen fuer die Dornwalze in [mm]*/
  float DW_soll_Pos[Arraygroesse];
  /** @var DW_soll_Pos_Hilf[Arraygroesse]
   * @brief Feld mit den berechneten Sollpositionen fuer die Dornwalze in [mm]*/
  float DW_soll_Pos_Hilf[Arraygroesse];
  /** @var Aufrufzeit_Regelzykl
   * @brief Aufrufzeit des Regelzykluses in [100 ms]*/
  float Aufrufzeit_Regelzykl;

  // TODO comments for doxygen
  float ri_block1;

  float ri_block2;


  /** @var TestOffset
   * @brief temporaerer Testwert zum Testen des vorliegenden Offset am Messsystem*/
  float TestOffset;
  /** @var Wanddicke_MS
   * @brief temp Wanddicke durch beide Sensoren*/
  float Wanddicke_MS;

  /** @var Startmesswert
   * @brief Messwert des Innenliegenden Messwertes*/
  float Startmesswert;
  /** @var Messwertdifferenz
   * @brief Differenz zwischen Start und aktuellen Messwert*/
  float Messwertdifferenz;          // Differenz zwischen Start und aktuelle Messwert
 
  
};

// Struktur Axialgeruestpositionierung
/** \struct Axialgeruest_Regelung
 * @brief Enthaelt Informationen ueber die aktuelle und Soll-Werte des Rings im Bezug auf die Axe */
struct Axialgeruest_Regelung
{
	/** @var Sollaxialwanddicke
	 * @brief berechnete Wanddicke*/
    float Sollaxialwanddicke;
    /** @var psi
     * @brief Verhaeltnis von Abstand 'Profilposition-Aussenmantel'/Startwanddicke */
    float psi;
    /** @var Wanddicke_axial_soll[Arraygroesse]
     * @brief in den Axialwalzspalt einlaufende Wandicken, welche vor halben Umdrehung aus dem Radialwalzspalt*/
    float Wanddicke_axial_soll[Arraygroesse];
    /** @var Wanddicke_axial_Hilf[Arraygroesse]
     * @brief Hilfsgroesse*/
    float Wanddicke_axial_Hilf[Arraygroesse];
    /** @var Wanddicke_axial_Aussensegment
     * @brief ermittlete Wanddicke*/
    float Wanddicke_axial_Aussensegment;
    
    /** @var Aufrufzeit_Regelzykl
     * @brief Zykluszeit in [s]*/
    int Aufrufzeit_Regelzykl;

    /** @var Sprunghoehe
     * @brief Fuer Regelerident ...*/
    float Sprunghoehe;                              // Fuer Regelerident...
    /** @var Haltezeit
     * @brief Haltezeit fuer naechsten Sprung*/
    float Haltezeit;                                // Haltezeit fuer naechsten Sprung
    
    /** @var wanddicke_hilf
     * @brief Soll-Wanddicke Axial für Logger */
    float wanddicke_hilf;

};

#endif


