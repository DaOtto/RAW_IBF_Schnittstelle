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
#define  cos_zeta 0.64F            // Winkel am Messsystem nach Zeichnung cos(Winkel°)
#endif 

#ifndef  sin_zeta
#define  sin_zeta 0.768F            // Winkel Messsystem
#endif 

#ifndef  regel_zyklus_fak
#define  regel_zyklus_fak  5        // Regelzykluszeit = regel_zyklus_fak * Abtastzeit(0,1 sec)
#endif 

#ifndef  Arraygroesse
#define  Arraygroesse  20           // Arraygröße
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
 void DA_Jenkouk_Regler        (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);






// Struktur
//DWR= Dornwalzenregelung
struct Def_DW_Regelung_DA_Jenkouk
{
    
  int Funktios_Iter;         // Zähler zur Überprüfung, ob Funktion aufgerufen wird
  // Eingangswerte 
  // Dyn. Werte    
  float Messwert_A;          // Messwert vom temporäres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
  float Messwert_A_mf;       // Messwert vom temporäres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
  float Messwert_A_alt_mf;   // Messwert vom temporäres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]

  float Messwert_A_unten;          // Messwert vom temporäres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
  float Messwert_A_unten_mf;       // Messwert vom temporäres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
  float Messwert_A_unten_alt_mf;   // Messwert vom temporäres Messsystem (vgl. Zeichnung Abb. 3.4 DA Jenkouk)      [mm]
 
 
 
 
  //Konstanten
  float Abstand_C;           // const. Abstand am temporären Messystem (vgl. Zeichnung Abb. 3.2 DA Jenkouk)  [mm]
  //float cos_zeta;            // const. Cos(zeta)        Winkel nach Zeichnung                              [°]
  //float sin_zeta;            // const. Sin(zeta)        Winkel nach Zeichnung                              [°]
  float Tastrollen_Radius;   // const. Radius der Tastrolle am temporären Messsystem                         [mm]
  float Offset; // Offset th. Spitze_Kegelwalze bis Lot 'Nullpunkt-MS' auf Maschinenlängsachse               [mm]

  float Messwert_Nullpunkt;  // Messwerte des Messystem 'innen', der angezeigt wird, wenn Zylinderstange ganz eingefahren ist [mm]
  float Messwert_Nullpunkt_unten; // Messwert außen                                                         [mm]
  float U_v_HW;              // Umfangsgeschwindgkeit an Hauptwalze                                         [mm/s]
  float DW_Durchmesser;      // Durchmesser der Dornwalze                                                   [mm]
  

  // Ausgangwerte / berechnete Variablen
  float Wanddicke_berechnet; // berechnete Wanddicke                                                        [mm]
  float DW_Pos_soll;         // Soll DW-Position                                                            [mm]
  float T_Einlauf;           //Zeit, die benötigt wird von der Messpostion zum Radialwalzspalt              [sec]
  float T_Verzoegerung;     // Verzögerungszeit                                                             [sec]
  int Anzahl_Zeitschritte;  // Differenz der Anzahl der Regelzyklen

  //-------Winkel---- alle Winkel mathematisch positiv (gegen den Uhrzeigersinn) siehe Abbildung 3.2 DA Vahid
  float Beta;               //Winkel vom Messsystem bis Einlauf Radial-Walzspalt bez. Kreismittelpunkt      [° ]
  float Alpha;               //Winkel  Maschinenachse bis Messsystem  bez. Kreismittelpunkt                 [° ]
  float Gamma;               //Winkel vom Einlauf Radialwalzspalt bis Maschineneachse                       [° ]

  float ri;                                  // Berechneter Innenradius mit Messvorrichtung                 [mm]
  float DW_soll_Pos[Arraygroesse];           // Feld mit den berechneten Sollpositionen für die DW          [mm]
  float DW_soll_Pos_Hilf[Arraygroesse];     // Feld mit den berechneten Sollpositionen für die DW          [mm]
  float Aufrufzeit_Regelzykl;                // Aufrufzeit des Regelzykluses in                         [100 ms]
  float ri_block1;
  float ri_block2;


  float TestOffset;                 // temporärer Testwert zum Testen des vorliegenden Offset am Messsystem 
  float Wanddicke_MS;               // temp Wanddicke durch beide Sensoren

  float Startmesswert;              // Messwert des Innenliegenden Messwertes
  float Messwertdifferenz;          // Differenz zwischen Start und aktuelle Messwert
 
  
};

// Struktur Axialgerüstpositionierung
struct Axialgeruest_Regelung
{
    float Sollaxialwanddicke;                       // berechnete Wanddicke
    float psi;                                      // Verhältnis von Abstand 'Profilposition-Aussenmantel'/Startwanddicke
    float Wanddicke_axial_soll[Arraygroesse];      // in den Axialwalzspalt einlaufende Wandicken, welche vor halben Umdrehung aus dem Radialwalzspalt 
    float Wanddicke_axial_Hilf[Arraygroesse];       // Hilsgröße
    float Wanddicke_axial_Aussensegment;            // ermittelte Wanddicke
    
    int Aufrufzeit_Regelzykl;                       // Zykluszeit in s

    float Sprunghoehe;                              // Für Regelerident...
    float Haltezeit;                                // Haltezeit für nächsten Sprung

};

#endif


