/*--FILE HEADER---------------------------------------------------------------
;   filename        : rpw.hpp
;   version         : V1.0
;   contents        : Tool for IBF software 
;   author          : J.Debye, SMS Eumuco; D. Michl, IBF RWTH Aachen
;   date            : October, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   struct Def_Ist_Inter Ist_Inter, 
                struct Def_Soll_Inter struct Soll_Inter 
;
;       RMOS3  Version 3.30
;       CAD-UL Version V120C
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   October , 10. 2006  0001  D.M.  original issue V1.0
;   
;	December, 01. 2014	0002  D.O.  Druckrollenerweiterung
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef RPW_HPP
   #define RPW_HPP

   #include <stdio.h>
//   #include <../inc/conio.h>
//   #include <math.h>


   #define CPP_T_EXPORT
   #define GUI_T_EXPORT
   #define UFT_T_EXPORT
   #define RAW_T_EXPORT
   #define SCHUESSEL_WALZEN 3

//   #define TRUE  1
//   #define FALSE 0

   #define Byte unsigned char

   #include "teso.hpp"
   #include "puff_cnc_s.hpp"
   #include "onli_cnc_s.hpp"
   #include "IBF_struct.hpp"
   #include "iniFile.h"
   
//   #include "IBF_Schuessel_Form.hpp"
   #include "ibf_Schuessel.hpp"

   #define Testcode TRUE

/*--------------------------------------------------------------------------*/
/*	Ist-Werte    : Ist_Inter                                                */
/*--------------------------------------------------------------------------*/

/**
 * @struct Rohling
 * Geometrie eines Rohlings
 */
struct Rohling
{
	float	sm;					///< Rohling Wandstärke in [mm]
	float	hm;					///< Rohling Höhe in [mm]
	float	da;					///< Rohling Aussendurchmesser in [mm]
};

/** 
 * @struct Antriebe
 * Angaben über Ist- und Solldrehmomente
 */
struct Antriebe
{
	float	ma_ist;				///< Ist-Drehmoment in [N/mm]
	float	ma_soll;			///< Soll-Drehmoment [N/mm]
};

/** Informationen über das Werkzeug. Dies beinhaltet Informationen über die
  * Walzdurchmesser, Windekgeschwindigkeiten, Drehzahlen und Ringumdrehungen. */
struct Werkzeug
{
	float	Durchmesser_HW;				///< Hauptwalzdurchmesser aus Carwin [mm]
	float	Durchmesser_DW;				///< Durchmesser der Dornwalze aus Carwin [mm]
	float	Winkelgeschw_omega_HW;		///< Winkelgeschwindigkeit Omega (rad) der Hauptwalze [1/s]
	float	Drehzahl_HW;				///< Drehzahl n (grad) der Hauptwalze [1/s]
	float	tU_HW;						///< Zeit für 1 Umdrehung der Hauptwalze in [s]
	float	Winkel_grad_tU_HW;			///< Aktueller Drehwinkel in Grad [°]
	float	U_v_HW;						///< Umfangsgeschwindigkeit der Hauptwalze in [mm/s]
	float	Ringumdrehung;				///< Zeit fuer eine Rindumdrehung in [s]
	float	omega_Ring;					///< Winkelgeschwindigkeit des Rings in [1/s]
	float	Winkel_grad_tU_Ring;		///< Aktueller Drehwinkel des Rings in Grad [°]
	float	l_fehlende_spitze;			///< Länge der fehlenden Spitzen an unteren Kegelwalze in [mm]
	struct	Antriebe Antrieb_ASO;		///< Struktur Antrieb des Axialschlitten oben
	struct	Antriebe Antrieb_ASU;		///< Struktur Antrieb des Axialschlitten unten
};

/** Beinhaltet detailliert Informationen über den aktuellen Zustand des Ringwalzwerks.
  * Darunter die aktuellen Positionen der Axial- und Radialschlitten. Desweiteren die Sollpositionen
  * der Radial- und Axialschlitten. Außerdem zusätzlich die Position des Axialschlittens unten für das
  * Modellwalzwerk.
  * Außerdem sind Informationen über die aktuellen Kräfte, Drehzahlen, Motoren und zwei unterschiedlich
  * präzise Korrekturpotentiometer vor. Zu guter letzt enthält die Struktur Informationen über die aktuelle
  * Ringgeometrie. */
struct Def_Ist_Inter
{  
	double Systemzeit;	///< Test zum ausmessen der benötigten Zeiten 

// aktuelle Positionen
	float rs_pos;		///< Aktuelle Position Radialschlitten in [mm] 
	float aso_pos;		///< Aktuelle Position Axialschlitten oben in [mm]
	float asu_pos;		///< Aktuelle Position Axialschlitten unten in [mm] NUR beim Modellwalzwerk verfügbar
	float ag_pos;		///< Aktuelle Position Axialgerüsts in [mm] 
	float zal_pos;		///< Aktuelle Position Zentrierarm links in [mm] 
	float zar_pos;		///< Aktuelle Position Zentrierarm rechts in [mm] 
	float tr_pos;		///< Aktuelle Position Tastrolle in [mm] 
	
// Kräfte
	float rs_f;			///< Kraft des Radialschlittens in [N]
	float as_f;			///< Kraft des Axialschlittens in [N] 
	float ag_f;			///< Kraft des Axialgeruestes in [N]
	float zal_fx;		///< Kraft der x-Komponente des linken Zentrierarms in [N]. NUR beim Modellwalzwerk verfügbar
	float zal_fy;		///< Kraft der y-Komponente des linken Zentrierarms in [N]. NUR beim Modellwalzwerk verfügbar
	float zal_f;		///< Gesamte Kraft des linken Zentrierarms in [N] 
	float zar_fx;		///< Kraft der x-Komponente des rechten Zentrierarms in [N]. NUR beim Modellwalzwerk verfügbar
	float zar_fy;		///< Kraft der y-Komponente des rechten Zentrierarms in [N]. NUR beim Modellwalzwerk verfügbar
	float zar_f;		///< Gesamte Kraft des rechten Zentrierarms in [N]

// Ströme
	float hw_i;			///< Stromstärke für den Hauptwalzmotors in [A]
	float kwo_i;		///< Stromstärke für die Kegelwalze oben in [A]
	float kwu_i;		///< Stromstärke für die Kegelwalze unten in [A]

// Drehzahlen
	float hw_n;			///< Drehzahl der Hauptwalze.
						///<* Banning [1/s]
						///<* MRAW [1/min]
	float kwo_n;		///< Drehzahl der Kegelwalze oben.
						///<* Banning [1/s]
						///<* MRAW [1/min]
	float kwu_n;		///< Drehzahl der Kegelwalz unten.
						///<* Banning [1/s]
						///<* MRAW [1/min]
	float n_hw_motor_ist;	///< Aktuelle Drehzahl des Motors der Hauptwalze in [1/s]
	float n_kwo_motor_ist;	///< Aktuelle Drehzahl des Motors der Kegelwalze oben in [1/s]
	float n_kwu_motor_ist;	///< Aktuelle Drehzahl des Motors der Kegelwalze unten in [1/s]
	
// Korrekturpotentiometer
	Byte poti_kw_n_255;             ///< Vertrim. Kegelwalze           [-] (Nur Modellwalzwerk)
	Byte poti_za_d_255;             ///< Zentrierposition              [-] (Nur Modellwalzwerk)

	Byte poti_vrelproz_255;         ///< Autom. Ringverlagerung        [-] (Nur Modellwalzwerk)
	Byte poti_endphase_255;         ///< Endphasenlaenge               [-] (Nur Modellwalzwerk)

	Byte poti_hand_r_255;           ///< Dornwalze von Hand            [-] (Nur Modellwalzwerk)
	Byte poti_dpmax_255;            ///< Walzenvorschub gekoppelt      [-] (Nur Modellwalzwerk)

	Byte poti_fz_255;               ///< Zentrierdruck                 [-] (Nur Modellwalzwerk)
	Byte poti_hand_a_255;           ///< Kegelwalze von Hand           [-] (Nur Modellwalzwerk)

	Byte poti_kw_n_oben_unten_255;  ///< Drehzahlen KW oben, unten     [-] (Nur Modellwalzwerk)
	Byte poti_reserve_255;          ///< Man. Ringverlagerung          [-] (Nur Modellwalzwerk)
	
	
// Korrekturpotentiometer
	short taster_poti_kw_n;				///< Vertrim. Kegelwalze           [-] (Nur Modellwalzwerk)
	short taster_poti_za_d;				///< Zentrierposition              [-] (Nur Modellwalzwerk)

	short taster_poti_vrelproz;			///< Autom. Ringverlagerung        [-] (Nur Modellwalzwerk)
	short taster_abschaltung_aus;		///< Abschaltung aus               [-] (Nur Modellwalzwerk)

	short taster_poti_hand_r;			///< Dornwalze von Hand            [-] (Nur Modellwalzwerk)
	short taster_power;					///< Power-Taster                  [-] (Nur Modellwalzwerk)

	short taster_poti_fz;				///< Zentrierdruck                 [-] (Nur Modellwalzwerk)
	short taster_poti_hand_a;			///< Kegelwalze von Hand           [-] (Nur Modellwalzwerk)

	short taster_poti_kw_n_oben_unten;	///< Drehzahlen KW oben, unten     [-] (Nur Modellwalzwerk)
	short taster_poti_reserve;			///< Man. Ringverlagerung          [-] (Nur Modellwalzwerk)

	Byte poti_taster[2];				///< Taster                        [-] (Nur Modellwalzwerk)
	
	float za_x_abstand;				///< Abstand Zentrierrollenachse - Hauptwalzenachse in x-Richtung (parallel zur Walzwerksachse)
									///< Nur Modellwalzwerk.
	
// Ringgeometrie
	float da;				///< Äusserer Durchmesser des Rings in [mm]
	float da_of;			///< TODO Add Doxygen Comments
	float di;				///< Innerer Durchmesser des Rings in [mm]
	float di_of;			///< TODO Add Doxygen Comments
	float dm;				///< Mittlerer Durchmesser des Rings in [mm]
	float dm_of;			///< TODO Add Doxygen Comments
	float fertig_ho_soll;	///< TODO Add Doxygen Comments
	float fertig_wd_soll;	///< TODO Add Doxygen Comments
	float h0a;				///< Ringhöhe axial einlaufend in [mm]
	float h0r;				///< Ringhöhe radial einlaufend in [mm] 
	float h1r;				///< Ringhöhe radial auslaufend in [mm]
	float h1a;				///< Ringhöhe axial auslaufend in [mm] 
	float h1a_of;			///< TODO Add Doxygen Comments
	float s0a;				///< Wanddicke axial einlaufend [mm]
	float s0r;				///< Wanddicke radial einlaufend in [mm]
	float s1a;				///< Wanddicke axial auslaufend in [mm]
	float s1r;				///< Wanddicke radial auslaufend in [mm]
	float s1r_of;			///< TODO Add Doxygen Comments
	float sfh;				///< Wanddicke bei Fertighöhe in [mm]
	float skw;				///< TODO Add Doxygen Comments
	float skw_of;			///< TODO Add Doxygen Comments
	float wa_dvol;			///< Berechnete Volumendifferenz in [%]			
	
// Erweiterung gegenüber MRAW
	struct Rohling Vorform;		///< Struktur eines Rohlings 
	struct Werkzeug Werkzeug;	///< Struktur eines Werkzeugs

	float hw_ir;				///< Getriebeübersetzung Hauptwalze in [-].
								///< Getriebeuntersetzung Hauptwalzenmotor  i=n_Antrieb/n_Abtrieb (i>1 ist Untersetzung)
	float kw_ia;				///< Getriebeübersetzung Kegelwalzen in [-]

	float Ibf_Achse1;			///< Messachse IBF 1 in [mm] Erweiterung des Bannings
	float Ibf_Achse2;			///< Messachse IBF 2 in [mm] Erweiterung des Bannings
	float Ibf_Achse3;			///< Messachse IBF 3 in [mm] Erweiterung des Bannings
	float Ibf_Achse4;			///< Messachse IBF 4 in [mm] Erweiterung des Bannings

	float ag_pos_real;			///< Testen der Anzeige der realen Axialgerüstposition

	struct IBF_Testfahrt Test;	///< Struktur einer Testfahrt

// DA Otto: Dezember 2014
// Ist-Werte der regelbaren Achsen.
// Strukturen wurden eingeführt im Rahmen des Projekts 'Schuesselwalzen'

	Def_Ist_Inter_DRR	DRR_Param;	///< Aktuelle Parameter der Druckrollen

// Ende Schuesselwalzen

// TEST TEST TEST
	float h1a_o_of;				///< Nur Modellwalzwerk
	float h1a_u_of;				///< Nur Modellwalzwerk

// Reserve Byte
	char  dummy[522];

};

/*--------------------------------------------------------------------------*/
/*	Soll-Werte: Soll_Inter                                                  */
/*--------------------------------------------------------------------------*/
/** Diese Struktur enthält Informationen über den Verarbeitungs Prozess. Es ist
  * hinterlegt sind Zustellgeschwindigkeiten, Endpositionen der Schlitten und
  * Angaben zu Drehzahl hinterlegt. Außerdem ist eine präzise Angabe vorhanden
  * welche Kraftregler aktiv sind und mit welcher Kraft sie, sollten sie aktiv sein
  * wirken. Zuletzt sind auch Angaben über die Betriebsart hinterlegt.
  * Weitere Infomrationen zu den Variablen sind im Quellcode als Kommentare zu den
  * jeweiligen Variablen hinterlegt. */
struct Def_Soll_Inter
	{
// Zustellgeschwindigkeiten
	float rs_v;		///< Zustellgeschwindigkeit des Radialschlittens in [mm/s]
	float aso_v;	///< Zustellgeschwindigkeit des Axialschlittens oben in [mm/s]
	float asu_v;	///< Zustellgeschwindigkeit des Axialschlitten unten in [mm/s]
	float ag_v;		///< Zustellgeschwindigkeit des Axialgeruests in [mm/s]
	float zal_v;	///< Zustellungsgeschwindigkeit des Zentrierarms links in [mm/s]
	float zar_v;	///< Zustellungsgeschwindigkeit des Zentrierarms rechts in [mm/s]

// Sollpositionen
	float rs_pos;	///< Soll-Position des Radialschlittens in [mm]
	float aso_pos;	///< Soll-Position des Axialschlittens oben in [mm]
	float asu_pos;	///< Soll-Position des Axialschlittens unten in [mm]
	float ag_pos;	///< Soll-Position des Axialgeruestes in [mm]
	float zal_pos;	///< Soll-Position des Zerntrierarms links in [mm]
	float zar_pos;	///< Soll-Position des Zentrierarms rechts in [mm]

// Drehzahlen
	float hw_n;			///< Soll-Drehzahl der Hauptwalze in [1/min]
	float kwo_n;		///< Soll-Drehzahl der Kegelwalze oben in [1/min]
	float kwu_n;		///< Soll-Drehzahl der Kegelwalze unten in [1/min]
	
	short schritt_nr;	///< Schrittnummer			
	
	float za_x_abstand;	///< Abstand Zentrierrollenachse - Hauptwalzenachse in x-Richtung (parallel zur Walzwerksachse)
	
	int   rs_kraftregler_aktiv;		///< Kraftregler Radialschlitten
									///< * 1 == aktiv 
									///< * 0 == inaktiv
	int   aso_kraftregler_aktiv;	///< Kraftregler Axialschlitten oben
									///< * 1 == aktiv 
									///< * 0 == inaktiv
	int   asu_kraftregler_aktiv;	///< Kraftregler Axialschlitten unten
									///< * 1 == aktiv 
									///< * 0 == inaktiv
	int   ag_kraftregler_aktiv;		///< Kraftregler Axialgerüst
									///< * 1 == aktiv 
									///< * 0 == inaktiv
	int   zal_kraftregler_aktiv;	///< Kraftregler Zentrierarm links
									///< * 1 == aktiv 
									///< * 0 == inaktiv
	int   zar_kraftregler_aktiv;	///< Kraftregler Zentrierarm rechts
									///< * 1 == aktiv 
									///< * 0 == inaktiv
	
	float rs_kraft;			///< Soll-Kraft Radialschlitten [N]
	float aso_kraft;		///< Soll-Kraft Axialschlitten oben [N]
	float asu_kraft;		///< Soll-Kraft Axialschlitten unten [N]
	float ag_kraft;			///< Soll-Kraft Axialgerüsts [N]

	float zal_kraft;		///< Soll-Kraft Zentrierarm links [N]
	float zar_kraft;		///< Soll-Kraft Zentrierarm rechts [N]

	struct Def_Soll_Inter_DRR	DRR_Param;	///< Soll-Werte der Druckrollen

	int   ag_act;			///< Flag Sollwerte Axialgerüst von Ibf auswertbar
	int	  zen_act;			///< Neu: Flag Sollwerte Zentrierarme vom Ibf auswertbar
	int   RS_act;			///< Neu: Flag Sollwerte Radialschlitten vom Ibf auswertbar
	int   AS_act;			///< Neu: Flag Sollwerte Axialschlitten vom Ibf auswertbar

// Betriebsarten
	int   rs_mode;		///< Betriebsart Vorschub (= 0) oder Kraftregelung (= 1)
	int   aso_mode;		///< Betriebsart Vorschub (= 0) oder Kraftregelung (= 1)
	int   ag_mode;		///< Betriebsart Vorschub (= 0) oder Kraftregelung (= 1)
	int   zen_mode;		///< Betriebsart Vorschub (= 0) oder Kraftregelung (= 1)
};

/** @struct Def_Steuerbyte
  * Definition der Steuerbytes von PC an Modellwalzwerk
  */
struct Def_Steuerbyte

{
	Byte modus;		///< Es existieren drei Betriebszustände:
					///< *		0		= Inaktiv
					///< *		1		= Handbetrieb
					///< *		2		= Automatikbetrieb
					///< *		3		= Kalibrierbetrieb

	Byte freigabe;	///< Es exisistieren für die 8 Antriebe jeweils ein Bit für die Freigabe
					///< *		1 Bit 0			: Radialschlitten
					///< *		2 Bit 1			: Axialgerüst NEU, war -schlitten
					///< * 		4 Bit 2			: Axialschlitten NEU, war -gerüst
					///< *		8 Bit 3			: Zentrierarm links
					///< *	   16 Bit 4			: Zentrierarm rechts
					///< *	   32 Bit 5			: Axialschlitten unten NEU, war Walzantrieb
					///< *	   64 Bit 6			: Walzenantriebe NEU, war Axialschlittenbremse
					///< *	  128 Bit 7			: Axialschlittenbremse NEU
};

int In_RWTH_LOG_Schreiben(char *buffer);

//class---------------------------------------------------------------------
class RPW
{
public:
	
	float offset_rs;			///< Offset des Radialschlittens
	float offset_agr;			///< Offset des Axialgerüsts
	float offset_aso;			///< Offset des Axialschlittens oben
	float offset_asu;			///< Offset des Axialschlittens unten
	float offset_tr;			///< Offset der Tastrolle
	
	float sin_kw_winkel_halbe;  ///< Hilfsvariable
/**
 * Initialisiert die von den neuen Ist-Werten abhängigen Parameter der Eingabestrukturen,
 * und verzweigt in die Funktion RPW::Main in der neuen Sollwerte erzeugt werden.
 */
	int Main_RAW(		int							 	ITER		/** [in] Iterationszähler																				 */,
						const	Def_Ein_Puff& 			Ein_Puff	/** [in] Referenz auf Parameter Struktur vom Typ Def_Ein_Puff			*/ ,
						const	Def_Lokal_Puff&			Lokal_Puff	/** [in] Referenz auf Parameter Struktur vom Typ Def_Lokal_Puff			*/ ,
						const	Def_Aus_Puff& 			Aus_Puff	/** [in] Referenz auf Parameter Struktur vom Typ Def_Aus_Puff			*/ ,
						const	Def_Ein_Onli& 			Ein_Onli	/** [in] Referenz auf Parameter Struktur vom Typ Def_Ein_Onli			*/ ,
						const	Def_Aus_Onli& 			Aus_Onli	/** [in] Referenz auf Parameter Struktur vom Typ Def_Aus_Onli			*/ ,
						struct	Def_Ist_Inter& 			Ist_Inter	/** [in,out] Referenz auf Parameter Struktur vom Typ Def_Ist_Inter		    */ ,
						struct	Def_Soll_Inter&			Soll_Inter	/** [in,out] Referenz auf Parameter Struktur vom Typ Def_Soll_Inter		    */ ,
						struct	Def_IBF_Allgemein_SOLL&	Soll_IBF	/** [in,out] Referenz auf Parameter Struktur vom Typ Def_IBF_Allgemein_SOLL */ ,
						struct	Def_IBF_Allgemein_IST& 	Ist_IBF		/** [in,out] Referenz auf Parameter Struktur vom Typ Def_IBF_Allgemein_IST  */ );

/**
 * Deklariert in der Def_Ist_Inter Struktur die Variablen die mit
 * den Positionen des aktuellen Status des Walzwerks,der Geometrien (Ring- und
 * Maschinengeometrie), den aktuellen Drehzahlen der Walzen und Motoren, den
 * Werkzeugen, den gefilterten Kräften oder Messwerte der IBF-Zusatzachse zu tun
 * haben.
 */
	int Istwerte_RAW(	const	Def_Ein_Onli			&Ein_Onli   /** [in,out] Referenz auf Parameter Struktur vom Typ Def_Ein_Onli   */ ,
						const	Def_Ein_Puff			&Ein_Puff 	/** [in,out] Referenz auf Parameter Struktur vom Typ Def_Ein_Puff 	*/ ,
						const	Def_Lokal_Puff			&Lokal_Puff /** [in,out] Referenz auf Parameter Struktur vom Typ Def_Lokal_Puff	*/ ,
						const	Def_Aus_Puff			&Aus_Puff 	/** [in,out] Referenz auf Parameter Struktur vom Typ Def_Aus_Puff 	*/ ,
						struct	Def_Ist_Inter			&ist_inter  /** [in,out] Referenz auf Parameter Struktur vom Typ Def_Ist_Inter	*/ );

/**
 * Schreibt Daten aus einer Def_Ist_Inter Struktur die das aktuelle 
 * Walzwerk beschreiben in eine Def_IBF_Allgemein_IST Struktur. Diese
 * Struktur ist vom IBF und auf dieser wird überwiegend gearbeitet. Die Daten
 * beziehen sich auf Geometrie des Ringes Position der Walzen und Filter des
 * Radialschlittens.
 */
 	int IstIBF_IstInter(struct Def_Ist_Inter			&Ist_Inter /** [in,out] Referenz auf Parameter Struktur vom Typ Def_Ist_Inter. Enthält den aktuellen Status des Walzwerks. */ ,
	                    struct Def_IBF_Allgemein_IST	&Ist_IBF   /** [in,out] Referenz auf Parameter Struktur vom Typ Def_IBF_Allgemein_IST in die einige Daten aus Def_Ist_Inter geschrieben werden. */ );

/**
 * Aktualisiert die Werte in der Struktur Def_IBF_Allgemein_IST
 * mit den Werte aus Def_IBF_Allgemein_SOLL
 */
	int IstIBF_SollIBF(	struct Def_IBF_Allgemein_SOLL	&Soll_IBF /** [in,out] Referenz auf Parameter Struktur vom Typ Def_IBF_Allgemein_SOLL 	*/ ,
						struct Def_IBF_Allgemein_IST	&Ist_IBF  /** [in,out] Referenz auf Parameter Struktur vom Typ Def_IBF_Allgemein_IST 	*/ );

/** 
 * Verhalten des Ringwalzwerks in Abhängigkeit von 
 * Def_IBF_Allgemein_IST.Profilflag.
 * <p>
 * Wenn Def_IBF_Allgemein_IST.Profilflag = -1 ist, werden die
 * Startpositionen  des Ringwalzwerks bestimmt. Es findet noch keine Zustellung
 * statt. Das heisst, das in diesem Fall auch noch nicht gewalzt wird, sondern die
 * Walzung nur vorbereitet wird. Sollte  Def_IBF_Allgemein_IST.Profilflag
 * = 3 sein (es soll eine Schüssel gewalzt werden), so wird die Methode 
 * schuesselWalzen::Main aufgerufen.
 * </p>
 * <p>
 * Wenn Def_IBF_Allgemein_IST.Profilflag = 1 ist, befindet sich das
 * Walzwerk
 * in der Profilierphase. In diesem Fall wird flexibel_Axial()
 * aufgerufen, sollte es sich um axiales Profilieren handeln
 * (IBF_Flag.Axial_Radialwalzen = 0). Die gleiche Methode wird beim Radial
 * Walzen aufgerufen. Sollte keine der beiden Profilierungen mehr
 * vorgenommen werden, so wird das Def_IBF_Allgemein_IST.Profilflag
 * auf 13 gesetzt, was gleich bedeutend ist mit, es wird abgeschaltet.
 * </p>
 * <p>
 * Wenn Def_IBF_Allgemein_IST.Profilflag = 2 ist, werden
 * Radialschlitten, Axialschlitten oben und Axialgerüst solange vorgefahren, bis
 * die Zeit Def_Zeit.t_Halte abgelaufen ist. Die Kräfte, die
 * während der Zeit wirken werden mit Hilfe von Kraftsteuerung
 * berechnet. Wenn Def_Zeit.t_Halte abgelaufen ist, wird mit Fall
 * '3' fortgefahren.
 * </p>
 * <p>
 * </p>
 * Wenn Def_IBF_Allgemein_IST.Profilflag = 3 ist, ist das
 * Abschaltmass nach 'Banning' erreicht. Das Walzwerk wird durch
 * IBF_Abschaltung() abgeschaltet.
 * <p>
 * Wenn Def_IBF_Allgemein_IST.Profilflag = 9 ist, fährt das
 * Walzwerk zu den vorher festgelegten Positionen vor. Auch hier wird noch nicht
 * gewalzt, das Walzwerk befindet sich noch in der Vorbereitung. Wenn das Walzwerk
 * komplett vorgefahren ist, so wird der Def_IBF_Allgemein_IST.Profilflag auf 11 gesetzt.
 * </p>
 * <p>
 * Wenn Def_IBF_Allgemein_IST.Profilflag = 11 ist, befindet sich das
 * Walzwerk in der Rundungsphase.Die Walzen arbeiten mit konstanter
 * Geschwindigkeit. Die Kraft der Walzen wird bei jeder Iteration mit Hilfe von
 * Kraftsteuerung neu berechnet. Die Drehzahlen werden mit Hilfe von
 * KW_Drehzahl_axial berechnet. Die Def_IBF_Allgemein_SOLL.AG_Pos wird durch
 * AGR_Soll_Pos berechnet. Wenn die Rundungsphase vorbei ist
 * (Def_Zeit.t_Halte <= 0 ) wird die nächste Walzphase eingeleitet,
 * in dem Def_IBF_Allgemein_SOLL.Profilflag
 * auf 12 gesetzt wird.
 * </p>
 * <p>
 * Wenn Def_IBF_Allgemein_IST.Profilflag = 12 ist, befindet sich die
 * Walzung in einem Zwischenstadium. An dieser Stelle sind Verzweigungen möglich.
 * Zunächst fährt der Axialschlitten hoch. Es folgt eine Abfrage, ob weitere
 * Profilierungen vorgenommen werden sollen. Sollte dies der Fall sein, so wird
 * Def_IBF_Allgemein_SOLL.Profilflag auf 0 gesetzt. Siehe oben
 * genannter Fall. Wenn keine weiteren Profilierungen mehr vollzogen werden sollen,
 * wird Def_IBF_Allgemein_SOLL.Profilflag auf 13 gesetzt. Siehe
 * nächster Fall.
 * </p>
 * <p>
 * Wenn Def_IBF_Allgemein_IST.Profilflag = 13 ist, befindet sich
 * das  Walzwerk am Ende der Walzung.Es wird nun mit Hilfe der Funktion
 * IBF_Abschaltung() abgeschaltet, und aufgefahren.
 * </p>
 *@todo Fall 0 wurde noch nicht zu den Doxygen Kommentaren hinzugefügt
 */	                      
	int Main(			struct Def_Ist_Inter			&Ist_Inter  /** [in,out] Referenz auf Parameter Struktur vom Typ Def_Ist_Inter			*/ ,
						struct Def_IBF_Allgemein_IST	&Ist_IBF    /** [in,out] Referenz auf Parameter Struktur vom Typ Def_IBF_Allgemein_SOLL */ ,
						struct Def_Soll_Inter			&Soll_Inter /** [in,out] Referenz auf Parameter Struktur vom Typ Def_Soll_Inter		    */ ,
						struct Def_IBF_Allgemein_SOLL	&Soll_IBF   /** [in,out] Referenz auf Parameter Struktur vom Typ Def_IBF_Allgemein_SOLL */ );

/**
 * <p> Im einfachsten Fall, dem dass die Profilwalzung noch bevor steht, werden sich nur die alten
 * Positionen des Axialschlittens oben und die Kraft des Radialschlittens gemerkt. Ausserdem wird
 * in desem Methodenteil festgelegt, wie sich im weiteren Verlauf des Profilierens verhalten werden
 * soll. Diese Information befindet sich im Flag Radial_Flex_Prof.Profilflag . Die möglichen Verläufe
 * sind kontinuierlicher Vorschub (Radial_Flex_Prof.Profilflag = 11), diskontinuierlicher Vorschub (Radial_Flex_Prof.Profilflag
 * = 12) und ein Vorschub nach 'Ingo Cr-Berechnung' (Radial_Flex_Prof.Profilflag = 15). 
 * Welcher Vorschub verwendet wird, wird in Radial_Flex_Prof.Schalter_Kont_DisKo festgelegt. </p>
 */		
	int flexibel_Radial(struct Def_Ist_Inter			&Ist_Inter  /** [in,out] Referenz auf Parameter Struktur Def_Ist_Inter			*/ ,
	                    struct Def_IBF_Allgemein_IST	&Ist_IBF 	/** [in,out] Referenz auf Parameter Struktur Def_IBF_Allgemein_IST 	*/ ,
	                    struct Def_Soll_Inter			&Soll_Inter	/** [in,out] Referenz auf Parameter Struktur Def_Soll_Inter 		*/ ,
	                    struct Def_IBF_Allgemein_SOLL	&Soll_IBF	/** [in,out] Referenz auf Parameter Struktur Def_IBF_Allgemein_SOLL */ );

/** 
 * Definiert das Verhalten, beim Axialprofilieren in den Verschiedenen Phasen.
 * <p>Für den Fall, daß sich der Ring in der ersten Phase befindet und somit
 * das Ringwalzwerk erst noch zugestellt werden muss, wird dies mit einer
 * konstanten vorgegeben Geschwindigkeit getan. Die Position, zu der zugestellt
 * wird, wird mit Hilfe von AGR_Soll_Pos berechnet. </p>
 * <p>Für den Fall, daß sich der Ring in der Rundungsphase befindet, werden
 * konstante Geschwindigkeiten für Radial-, Axialschlitten oben und unten, sowie
 * für die Zentrierrollen rechts und links festgelegt. Die Kräfte der Rollen
 * werden mit Hilfe der Funktion Kraftsteuerung() festgelegt.
 * Die Drehzahlen für die obere und untere Kegelwalze werden mit Hilfe
 * der Funktion KW_Drehzahl_axial() festgelegt. Die Anzahl der Methodenaufrufe während
 * der Rundungsphase entspricht der Anzahl der Glättungsrunden. Ist die Anzahl
 * erreicht, wird das Axial_Flex_Prof.Profilflag auf '12' gesetzt und 
 * somit die nächste Phase eingeleitet.</p>
 * <p> Für den Fall, dass der Ring gerade eine Rundungsphase beendet hat, werden
 * konstante Geschwindigkeiten für Radial-,Axialschlitten oben und unten, sowie
 * für die Zentrierarme rechts und links gesetzt. Die Kräfte der Rollen werden
 * mit Hilfe von Kraftsteuerung() und die Drehzahlen mit 
 * KW_Drehzahl_axial() berechnet. Es folgt eine Abfrage, ob weitere Profile
 * gewalzt werden sollen.
 *
 * @return[out] Nach Ablauf der Methode beziehungsweise nach Beendigung einer der 
 * Profilierphasen, wird der Rückgabewert \link TRUE \endlink zurückgegeben.
 */	
	int flexibel_Axial(	struct Def_Ist_Inter			&Ist_Inter  /** [in,out] Referenz auf Parameter Struktur Def_Ist_Inter			*/ ,
						struct Def_IBF_Allgemein_IST	&Ist_IBF 	/** [in,out] Referenz auf Parameter Struktur Def_IBF_Allgemein_IST 	*/ ,
						struct Def_Soll_Inter			&Soll_Inter	/** [in,out] Referenz auf Parameter Struktur Def_Soll_Inter 		*/ ,
						struct Def_IBF_Allgemein_SOLL	&Soll_IBF	/** [in,out] Referenz auf Parameter Struktur Def_IBF_Allgemein_SOLL */ );

/**
 * @fn formenspektrum
 * ToDo : add DoxyGen Comments
 */
	int formenspektrum(	struct Def_Ist_Inter			&Ist_Inter  /** [in,out] Referenz auf Parameter Struktur Def_Ist_Inter			*/ ,
						struct Def_IBF_Allgemein_IST	&Ist_IBF 	/** [in,out] Referenz auf Parameter Struktur Def_IBF_Allgemein_IST 	*/ ,
						struct Def_Soll_Inter			&Soll_Inter	/** [in,out] Referenz auf Parameter Struktur Def_Soll_Inter 		*/ ,
						struct Def_IBF_Allgemein_SOLL	&Soll_IBF	/** [in,out] Referenz auf Parameter Struktur Def_IBF_Allgemein_SOLL */ );

/** 
 * @fn Modus_AG
 * Legt zu Beginn in Def_Soll_Inter die Verantwortung des Abschaltens und die Regelung 
 * des Axialgerüsts fest, ausgelesen wird dies aus dem Def_IBF_Allgemein_IST. Dannach wird
 * abhänging davon, ob in Def_IBF_Allgemein_IST ein Wert für die Kraft des Axialgerüsts hinterlegt
 * ist und von der gegeben Auswahl der Modus des Axialgerüsts festgelegt.
 * @return TRUE
 */
	int Modus_AG(		struct Def_Soll_Inter			&Soll_Inter	/** [in,out] Referenz auf Parameter Struktur Def_Soll_Inter 		*/ , 
						struct Def_IBF_Allgemein_IST	&Ist_IBF 	/** [in,out] Referenz auf Parameter Struktur Def_IBF_Allgemein_IST 	*/ , 
						int								Auswahl     /** [in] Auswahl Axialgerüstmodus                                   */ );
/**
 * @fn Kr_Geo_berechnen
 * Berechnet notwendige Kragenwalzengeometrien. Diese sind der Abstand Vorderkante
 * Kragenwalze - theoretische Spitze und der Kragendurchmesser am Mittelpunkt.
 * @return TRUE, sobald alle Berechnungen durchgeführt sind. \link TRUE \endlink ist hier ein Macro.
 */
	int Kr_Geo_berechnen(struct Def_IBF_Allgemein_IST &Ist_IBF	/** [in,out] Referenz auf Struktur vom Typ Def_IBF_Allgemein_IST */ );
/**
 * @fn Kr_Geo_pruefen
 * Berechnet die Länge der unteren Kegelwalze von der reellen Spitze bis Kragenwalze.
 * @return TRUE, sobald alle Berechnungen durchgeführt sind. \link TRUE \endlink ist hier ein Macro
 */	
	int Kr_Geo_pruefen  (struct Def_IBF_Allgemein_IST &Ist_IBF	/** [in,out] Referenz auf Struktur vom Typ Def_IBF_Allgemein_IST */ );

/** 
 * @fn IBFPARA_auslesen
  * Liest die Werte aus der IBF_Data.ini ein
  * @return Rückgabewert der Funktion ist 0 wenn, die Datei IBF_Data.ini mit Hilfe der Methode 
  * CIniFile::ReadFile() aus der Klasse CIniFile nicht korrekt gelesen werden
  * konnte, ansonsten ist der Rückgabewert 1.
  */
	static int IBFPARA_auslesen(struct Def_IBF_Allgemein_IST	&Ist_IBF 	/** [in,out] Referenz auf Parameter Struktur Def_IBF_Allgemein_IST 	*/ ,
								struct Def_IBF_Allgemein_SOLL	&Soll_IBF	/** [in,out] Referenz auf Parameter Struktur Def_IBF_Allgemein_SOLL */ ,
								struct Def_Ist_Inter			&Ist_Inter  /** [in,out] Referenz auf Parameter Struktur Def_Ist_Inter			*/ );

	RPW(void);		///< Standard Klassen Kontruktor
	~RPW(void){};	///< Standard Klassen Destruktor
};

#endif // RPW_HPP


