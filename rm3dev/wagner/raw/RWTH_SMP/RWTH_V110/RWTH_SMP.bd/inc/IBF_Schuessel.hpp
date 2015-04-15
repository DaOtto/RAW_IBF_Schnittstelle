/*--DATEI HEADER---------------------------------------------------------------
;   Dateiname       : IBF_Schuessel.hpp
;   Version         : V1.00a
;   Beschreibung    : Steuerungsmethoden der Schuesselwalzstrategie
;	Plattform		: RMOS3,WIN32				  
;
;                    
;
;   Autor           : D.Otto
;   date            : Januar 2015
;
-----------------------------------------------------------------------------*/

#include "IBF_Schuessel_Form.hpp"

// Nachrichten-Codes der Reglerfunktionen
#define ERR_FATAL		0xFFFE;
#define ERR_OK			0x0000;
#define ERR_WAIT		0x1000;
#define ERR_FERTIG_HM	0x0100;
#define ERR_FERTIG_KW	0x0200;

#ifndef IBF_SCHUESSEL_HPP
  #define IBF_SCHUESSEL_HPP

//#define EPSW	0.5F		// Toleranz fuer Positionierung [mm] (+/- EPSW)

// Allgemein Act und Mode Bits
#define WEG			0x0000
#define KRAFT		0x0001
#define ACT_IBF		0x0001
#define ACT_SMS		0x0000

// AG_Mode Bits
#define AG_WEG		0x0000
#define AG_KRAFT	0x0001
#define AG_ABS		0x0000
#define AG_nABS		0x0002
#define AG_SSMS		0x0000
#define AG_SIBF		0x0004

// ZenBits
#define ZEN_MODE_WEG	0x0004
#define ZEN_MODE_KRAFT	0x0001

// DrRBits
#define DRR_MODE_WEG	0x0004
#define DRR_MODE_KRAFT	0x0000

struct StartPos_t
{
	float	AS_startPos;	///< Anfahrposition Axialschlitten.
	float	AG_startPos;	///< Anfahrposition Axialgeruest.
	float	RS_startPos;	///< Anfahrposition Radialschlitten.
	float	DRE_startPos;	///< Anfahrposition Druckrolle, Einlaufseite.
	float	DRA_startPos;	///< Anfahrposition Druckrolle, Auslaufseite.
	float	ZR_startPos;	///< Anfahrposition der Zentrierrollen. (Definiert als 'Abstand zur Ringkontur', d.H. 0mm = Kontakt zum Ring)
};

struct AblaufFlags_t
{
	int	AnfahrFlag;
	int AnwalzFlag;
	int WalzenFlag;
	int OeffnenFlag;
};

struct Vorform_t
{
	float Masse_kg;		///< Masse [kg] der Vorform. Aus IBF_Data.ini
	float Dichte_warm;	///< Dichte des warmen Ringes [kg/liter]. Aus IBF_Data.ini
	float Volumen;		///< Vorformvolumen [mm^3]. Berechnet aus Masse/Dichte
	float da_mm;		///< Durchmesser der Vorform [mm]. Aus IBF_Data.ini
	float hm_mm;		///< Mittlere Profilhoehe der Vorform [mm]. Aus IBF_Data.ini
	float sm_mm;		///< Mittlere Profilbreite der Vorform [mm]. Berechnet aus Hoehe, Durchmesser und Volumen der Vorform.
};

typedef Def_Schuessel_Walzform Walzform_t;

struct Endform_t
{
	float	Ende_h_min_mm;			///< Prozessabbruchkriterium 'mindest Profilhoehe'. (Aus IBF_Data.ini)
	float	Ende_alpha_grad;		///< Prozessabbruchkriterium 'erwarteter Schuesselwinkel'. (Aus IBF_Data.ini)
	float	Ende_max_Kletterhoehe;	///< Prozessabbruchkriterium 'Maximale Kletterhoehe'. (Aus IBF_Data.ini)
	int		erreicht;				///< Flag. Zeigt an ob eine mindestens eine Abbruchbedingung erfuellt ist.
};

struct Test_t
{
	int		Flag_oRing;
	float	Tastrolle_da;
};

struct Def_IBF_Schuessel
{
	int				InitFlag;			///< Flag. Zeigt an ob Startparameter initialisiert wurden.
	int				Flag_Zen_geoeffnet; ///< Flag gibt an ob Zentrierung geoeffnet ist. [0=Nein;1=Ja]
	StartPos_t		StartPos;			///< Anfahrpositionen aller Achsen. Abhaenig von Vorformgeometrie.
	AblaufFlags_t	AblaufFlags;		///< Flags zur Ablaufsteuerung der Walzstrategie.
	Vorform_t		Vorform;			///< Vorformgeometrie und -volumen.
	Walzform_t		Walzform;			///< Aktuelle, aus Sensordaten ermittelte Kennwerte der Ringgeometrie waehrend der Walzphase.
	Endform_t		Endform;			///< Geometrische Vorgaben fuer die Endform. Abbruch der Walzphase bei erreichen eines Endwertes.
	Test_t			Test;				///< Gibt Parameter fuer Testlauf an.
	float			eps;				///< Allgemeine Positioniergenauigkeit. (aus IBF_Data.ini)
	float			n_HW;				///< Konstante Soll-Drehzahl der Hauptwalze in der Walzphase. (aus IBF_Data.ini)
	float			offset_DW;			///< Soll-Abstand der Dornwalze zur berechneten RWS-Breite, um Kontakt mit Ring zu vermeiden. (aus IBF_Data.ini) 
	float			offset_ZEN;			///< Soll-Abstand der Zentrierrollen zum Ring bei geoeffneter Zentrierung. (aus IBF_Data.ini)
	float			offset_DrR_A;		///< Positionsabweichung der abhaengigen Druckrolle. Zur gezielten Ringverlagerung. (aus IBF_Data.ini)
	float			V_Soll_AS;			///< Konstante Zustellgeschwindigkeit des Axialschlittens in der Walzphase. (aus IBF_Data.ini)
	float			F_Soll_DrR;			///< Sollkraft Vorgabe fuer Druckrollen bei Kraftregelung. (aus IBF_Data.ini)
	float			F_Grenz_DrR;		///< Grenzkraft Vorgabe fuer Druckrollen bei Positionsregelung. (aus IBF_Data.ini)
};

static class IBF_Schuessel
{
 	public:
//-----------------------------------------------------------------------------
//
//
//
//		
        int Main(	struct Def_Ist_Inter			&Ist_Inter,
					struct Def_IBF_Allgemein_IST	&Ist_IBF,
					struct Def_Soll_Inter			&Soll_Inter,
					struct Def_IBF_Allgemein_SOLL	&Soll_IBF);																    	
					
		IBF_Schuessel(){};	// C´tor
		~IBF_Schuessel(){}; // D´tor

	private:
//-----------------------------------------------------------------------------
//
//
//
//	
		int Anfahren( struct Def_Ist_Inter			&Ist_Inter,
					  struct Def_IBF_Allgemein_IST	&Ist_IBF,
					  struct Def_Soll_Inter			&Soll_Inter,
					  struct Def_IBF_Allgemein_SOLL	&Soll_IBF);
//-----------------------------------------------------------------------------
//
//
//
//	
		int Anwalzen( struct Def_Ist_Inter			&Ist_Inter,
					  struct Def_IBF_Allgemein_IST	&Ist_IBF,
					  struct Def_Soll_Inter			&Soll_Inter,
					  struct Def_IBF_Allgemein_SOLL	&Soll_IBF);	
//-----------------------------------------------------------------------------
//
//
//
//	
		int Walzen(   struct Def_Ist_Inter			&Ist_Inter, 
					  struct Def_IBF_Allgemein_IST	&Ist_IBF,
					  struct Def_Soll_Inter			&Soll_Inter,
					  struct Def_IBF_Allgemein_SOLL	&Soll_IBF);	
//-----------------------------------------------------------------------------
//
//
//
//	
		int Rundung(  struct Def_Ist_Inter			&Ist_Inter, 
					  struct Def_IBF_Allgemein_IST	&Ist_IBF,
					  struct Def_Soll_Inter			&Soll_Inter,
					  struct Def_IBF_Allgemein_SOLL	&Soll_IBF);
//-----------------------------------------------------------------------------
//
//
//
//	
		int Initialisieren(	struct Def_Ist_Inter			&Ist_Inter, 
							struct Def_Soll_Inter			&Soll_Inter,
							struct Def_IBF_Allgemein_IST	&Ist_IBF,
							struct Def_IBF_Allgemein_SOLL	&Soll_IBF);

} schuesselWalzen;

/** @fn int RS_Regler(	const  Def_Ist_Inter&,
						const  Def_IBF_Allgemein_IST&,
						struct Def_Soll_Inter&,
						struct Def_IBF_Allgemein_SOLL&);
@brief	Sollwertfunktion fuer den Radialschlitten beim Schuesselwalzen. 
		Steuert waehrend der Walzphase die Position und Geschwindigkeit des Radialschlittens.
		Die Bestimmung der Sollwerte basiert auf den Walzformparametern die in der Funktion Schuessel_Form_IST()
		ermittelt wurden.
@return Fehlercode.
*/
int RS_Regler(	const  Def_Ist_Inter&,				///< [in]
				const  Def_IBF_Allgemein_IST&,		///< [in]
				struct Def_Soll_Inter&,				///< [out]
				struct Def_IBF_Allgemein_SOLL&		///< [out]
);

/** @fn int AG_Regler(	const  Def_Ist_Inter&,
						const  Def_IBF_Allgemein_IST&,
						struct Def_Soll_Inter&,
						struct Def_IBF_Allgemein_SOLL&);
@brief	Sollwertfunktion fuer das Axialgeruest beim Schuesselwalzen. 
		Steuert waehrend der Walzphase die Position und Geschwindigkeit des Axialgeruestes.
		Die Bestimmung der Sollwerte basiert auf den Walzformparametern die in der Funktion Schuessel_Form_IST()
		ermittelt wurden.
@return Fehlercode.
*/
int AG_Regler(	const  Def_Ist_Inter&,				///< [in]
				const  Def_IBF_Allgemein_IST&,		///< [in]
				struct Def_Soll_Inter&,				///< [out]
				struct Def_IBF_Allgemein_SOLL&		///< [out]
);

/** @fn int AS_Regler(	const  Def_Ist_Inter&,
						const  Def_IBF_Allgemein_IST&,
						struct Def_Soll_Inter&Soll_Inter,
						struct Def_IBF_Allgemein_SOLL&);
@brief	Sollwertfunktion fuer den Axialschlitten beim Schuesselwalzen. 
		Steuert waehrend der Walzphase die Geschwindigkeit des Axialschlittens.
		Die Vorgabe fuer die Zustellgeschwindigkeit wird in der Parameterdatei 'IBF_Data.ini' festgelegt.
@return Fehlercode.*/
int AS_Regler(	const  Def_Ist_Inter&,				///< [in]
				const  Def_IBF_Allgemein_IST&,		///< [in]
				struct Def_Soll_Inter&,				///< [out]
				struct Def_IBF_Allgemein_SOLL&		///< [out]
);

/** @fn int ZR_Regler(	const  Def_Ist_Inter&,
						const  Def_IBF_Allgemein_IST&,
						struct Def_Soll_Inter&,
						struct Def_IBF_Allgemein_SOLL&);
@brief	Sollwertfunktion fuer die Zentrierrollen beim Schuesselwalzen. 
		Steuert waehrend der Walzphase die Position und Geschwindigkeit der Zentrierrollen.
		Die Bestimmung der Sollwerte basiert auf den Walzformparametern die in der Funktion Schuessel_Form_IST()
		ermittelt wurden.
		Die Position wird dabei als 'Abstand zum Ring' definiert, d.h. Position '0' bedeutet 'in Kontakt mit dem Ring'.
		Die Umrechnung dieser auf den Ring bezogenen Sollwertdefinition in einen Sollwert fuer den Aktuator des
		Hebelgetriebes der Zentrierrollen erfolgt in der Funktion ZER_Reg_Soll().
@return Fehlercode.*/
int ZR_Regler(	const  Def_Ist_Inter&,				///< [in]
				const  Def_IBF_Allgemein_IST&,		///< [in]
				struct Def_Soll_Inter&,				///< [out]
				struct Def_IBF_Allgemein_SOLL&		///< [out]
);

/** @fn int DR_Regler(	const  Def_Ist_Inter&,
						const  Def_IBF_Allgemein_IST&,
						struct Def_Soll_Inter&,
						struct Def_IBF_Allgemein_SOLL&);
@brief	Sollwertfunktion fuer die Druckrollen beim Schuesselwalzen. 
		Steuert waehrend der Walzphase die Position und Geschwindigkeit der Druckrollen.
		Die Position wird dabei als 'Abstand zum Ring' definiert, d.h. Position '0' bedeutet 'in Kontakt mit dem Ring'.
		Die Umrechnung dieser auf den Ring bezogenen Sollwertdefinition in einen Sollwert fuer den Aktuator der
		Druckrolle erfolgt in der Funktion ZER_Reg_Soll().
@return Fehlercode.*/
int DR_Regler(	const  Def_Ist_Inter&,				///< [in]
				const  Def_IBF_Allgemein_IST&,		///< [in]
				struct Def_Soll_Inter&,				///< [out]
				struct Def_IBF_Allgemein_SOLL&		///< [out]
);

/** @fn int WA_Regler(	const  Def_Ist_Inter&,
						const  Def_IBF_Allgemein_IST&,
						struct Def_Soll_Inter&,
						struct Def_IBF_Allgemein_SOLL&);
@brief	Sollwertfunktion fuer das Axialgeruest beim Schuesselwalzen. 
		Steuert waehrend der Walzphase die Drehzahlen der Hauptwalze und der Axialwalzen.
@return Fehlercode.*/
int WA_Regler(	const  Def_Ist_Inter&,				///< [in]
				const  Def_IBF_Allgemein_IST&,		///< [in]
				struct Def_Soll_Inter&,				///< [out]
				struct Def_IBF_Allgemein_SOLL&		///< [out]
);

float sgn(float);

#endif // IBF_SCHUESSEL_HPP

