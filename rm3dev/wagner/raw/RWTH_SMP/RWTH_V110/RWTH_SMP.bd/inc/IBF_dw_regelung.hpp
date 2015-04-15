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
   #define _IBF_dw_regelung_HPP

#ifndef  cos_zeta
/** 
 * @def cos_zeta
 * @brief Winkel am Messystem nach Zeichnung cos(Winkel °)
 */
#define  cos_zeta 0.64F
#endif

#ifndef  sin_zeta
/** 
 * @def sin_zeta
 * @brief Winkel Messsystem
 */
#define  sin_zeta 0.768F
#endif

#ifndef  regel_zyklus_fak
/** 
 * @def regel_zyklus_fak
 * @brief Regelzykluszeit = regel_zyklus_fak * Abtatszeit(0.1 sec)
 */
#define  regel_zyklus_fak  5
#endif

#ifndef  Arraygroesse
/**
 * @def Arraygroesse
 * @brief Definition der Größe eines Arrays
 */
#define  Arraygroesse  20
#endif

//Funktionsprototypen

// DW-Regelung
void Beta(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);
void Alpha(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);
void Gamma(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);
void T_Einlauf(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);
void Axial_Wanddicke_bestimmen(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);
void T_V(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);
void DW_Regelalgo(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);
void DA_Jenkouk_Regler(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);

void RS_nach_Messwert_Fahren(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);

// AG-Regelung
void AG_Regelalgo(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);
void DA_Jenkouk_Regler_AG(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);
void DA_Jenkouk_Regler(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF);

// Struktur
// DWR == Dornwalzenregelung
/** 
 * @struct Def_DW_Regelung_DA_Jenkouk
 * @brief Regelung der Dornwalze
 */
struct Def_DW_Regelung_DA_Jenkouk
{
	int Funktios_Iter;         ///> Zähler zur Überprüfung, ob Funktion aufgerufen wird
	// Eingangswerte 
	// Dyn. Werte
	float Messwert_A;          ///> Messwert des temporäres Messsystems (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
	float Messwert_A_mf;       ///> Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
	float Messwert_A_alt_mf;   ///> Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]

	float Messwert_A_unten;          ///> Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
	float Messwert_A_unten_mf;       ///> Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
	float Messwert_A_unten_alt_mf;   ///> Messwert vom temporaeres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]

	//Konstanten
	/** @var Abstand_C
	 * @brief const. Abstand am temporaeren Messystem zur Achse des Ringwalzwerks (vgl. Zeichnung Abb. 4.6 DA Jenkouk)  [mm]*/
	float Abstand_C;			// const. Abstand am temporaeren Messystem (vgl. Zeichnung Abb. 3.2 DA Jenkouk)  [mm]
	//float cos_zeta;			// const. Cos(zeta)        Winkel nach Zeichnung                              [°]
	//float sin_zeta;			// const. Sin(zeta)        Winkel nach Zeichnung                              [°]
	
	float Tastrollen_Radius;   ///> const. Radius der Tastrolle am temporaeren Messsystem                         [mm]
	float Offset; ///> Offset th. Spitze_Kegelwalze bis Lot 'Nullpunkt-MS' auf Maschinenlaengsachse               [mm]

	float Messwert_Nullpunkt;  ///> Messwerte des Messystem 'innen', der angezeigt wird, wenn Zylinderstange ganz eingefahren ist [mm]
	float Messwert_Nullpunkt_unten; ///> Messwert aussen                                                         [mm]
	float U_v_HW;              ///> Umfangsgeschwindgkeit an Hauptwalze                                         [mm/s]
	float DW_Durchmesser;      ///> Durchmesser der Dornwalze                                                   [mm]


	// Ausgangwerte / berechnete Variablen
	float Wanddicke_berechnet;		///> Berechnete Wanddicke
	float DW_Pos_soll;				///> Soll-Position der Dornwalze
	float T_Einlauf;				///> Zeit, die benoetigt wird von der Messposition zum Radialwalzspalt [sec]
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
	float Beta;		///> Winkel vom Messsystem bis Einlauf Radial-Walzspalt bez. Kreismittelpunkt in [° ]
	float Alpha;	///> Winkel  Maschinenachse bis Messsystem  bez. Kreismittelpunkt in [° ]
	float Gamma;	///> Winkel vom Einlauf Radialwalzspalt bis Maschineneachse in [° ]

	float ri;								///> Berechneter Innenradius mit Messvorrichtung in [mm]
	float DW_soll_Pos[Arraygroesse];		///> Feld mit berechneten Sollpositionen fuer die Dornwalze in [mm]
	float DW_soll_Pos_Hilf[Arraygroesse];	///> Feld mit den berechneten Sollpositionen fuer die Dornwalze in [mm]
	float Aufrufzeit_Regelzykl;				///> Aufrufzeit des Regelzykluses in [100 ms]

	// TODO comments for doxygen
	float ri_block1;
	float ri_block2;

	float TestOffset;		///> temporaerer Testwert zum Testen des vorliegenden Offset am Messsystem
	float Wanddicke_MS;		///> temp Wanddicke durch beide Sensoren

	float Startmesswert;	///> Messwert des Innenliegenden Messwertes
	float Messwertdifferenz;///> Differenz zwischen Start und aktuellem Messwert
};

// Struktur Axialgeruestpositionierung
/** 
 * @struct Axialgeruest_Regelung
 * @brief Enthält Informationen über die aktuelle Werte und Soll-Werte des Rings im Bezug auf die Achse */
struct Axialgeruest_Regelung
{
	float Sollaxialwanddicke;	///> berechnete Wanddicke
	float psi;					///> Verhältnis von Abstand 'Profilposition-Außenmantel'/Startwanddicke
	float Wanddicke_axial_soll[Arraygroesse];	///> in den Axialwalzspalt einlaufende Wandicken,
												///> welche vor halben Umdrehung aus dem Radialwalzspalt
	float Wanddicke_axial_Hilf[Arraygroesse];	///> Hilfsgroesse
	float Wanddicke_axial_Aussensegment;		///> ermittlete Wanddicke

	int Aufrufzeit_Regelzykl;					///> Zykluszeit in [s]

	float Sprunghoehe;                          ///> Fuer Regelerident...
	float Haltezeit;                            ///> Haltezeit fuer naechsten Sprung

	float wanddicke_hilf;						///> Soll-Wanddicke Axial für Logger
};

#endif
