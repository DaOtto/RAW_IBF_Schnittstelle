/*--FILE HEADER---------------------------------------------------------------
;   filename        : ibf_struct.hpp
;   version         : V1.0
;   contents        : IBF-Variablen IBF software 
;   author          : D. Michl, IBF RWTH Aachen
;   date            : October, 2006
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
;   October , 10. 2006  0001  D.M.  original issue V1.0
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _IBF_struct_HPP
   #define _IBF_struct_HPP

//#define MRAW 0          // 0= Modellwalzwerk || 1=Banning Ringwalzwerk
#define RAW  0


/*-----------------------------------------------------------------------------------------*/
/*          Includedatein die für die IBF-Strukturen benötigt werden                       */
/*-----------------------------------------------------------------------------------------*/

	#include "ibf_tool.hpp"
    #include "IBF_radflex.hpp"
    #include "IBF_axproflex.hpp"
    #include "IBF_stuetz.hpp"
    #include "IBF_dw_regelung.hpp"
  	#include "IBF_formenspek.hpp"

	#include "IBF_Schuessel.hpp"

	#include "IBF_Schuessel_DR_pos.hpp"
	#include "IBF_Schuessel_ZR_pos.hpp"
	#include "IBF_Schuessel_Form.hpp"
	

// Definition von PI 
#ifndef  PI
#define  PI 3.14159265358979323846F          
#endif // PI

/*-----------------------------------------------------------------------------------------*/ 
/*                  Struktur Geometrie | IBF-Flags | Radial-Profilieren Module             */
/*-----------------------------------------------------------------------------------------*/
 
/** \struct IBF_Testfahrt
  * Enthält Informationen über die Art der Fahrt, ob Testfahrt oder nicht,
  * sowie den simulierten Ringdurchmesser, sollte es sich um eine Testfahrt handeln.
  */
struct IBF_Testfahrt
{
	int		Flag;				///< Testfahrt AN( 1 ) - AUS( 0 ) 
	float	Ring_AD;			///< Simulierter Ringdurchmesser für Testfahrt [mm]
};
 
struct Geometrie				///< Definiert Startgeometrie des Ringes. Notwendige Angabe bei Modellwalzwerk und Debug-Simulation.
{
  float D_Null;					///< Außendurchmesser des Ringes
  float Wandstaerke_Null;		///< Anfangswanddicke -> notwendig, da am Modellwalzwerk Daten nicht eingelesen werden koennen
  float Start_Ringhoehe;		///< Anfangsringhöhe
};
/** \struct IBF_Flag
  * @brief Enthält die wichtigsten Flags. Dies beinhaltet 
  *			*		die Flags für dieSteuerung der Schlitten,
  *			*		sowie Modi der einzelnen Schlitten,
  *			*		ob die Abschaltmasse erreicht sind,
  *			*		sowie Informationen für die Dornwalzregelung von V. Jenkouk.
  */
struct IBF_Flag
{
	int rs_kraftregler_aktiv;				///< Flag zum Arbeiten mit/ohne Radialschlitten Kraftregelung [0-1]
	int as_kraftregler_aktiv;				///< Flag zum Arbeiten mit/ohne Axialschlitten Kraftregelung [0-1]
	int ag_kraftregler_aktiv;				///< Flag zum Arbeiten mit/ohne Axialgerüst Kraftregelung [0-1]
	int zal_kraftregler_aktiv;				///< Flag zum Arbeiten mit/ohne Zentrierarm Kraftregelung links [0-1]
	int zar_kraftregler_aktiv;				///< Flag zum Arbeiten mit/ohne Zentrierarm Kraftregelung rechts [0-1]

	int rs_kraftanfahren_aktiv;				///< Flag zum Kraftanfahren RADIAL an Rohling [0-1]
	int as_kraftanfahren_aktiv;				///< Flag zum Kraftanfahren AXIAL an Rohling [0-1]

	int as_kraft_anfahren_erreicht;			///< Flag zeigt an, ob die Anfahrkraft des Axialschlittens erreicht wurde [0-1]
	int rs_kraft_anfahren_erreicht;			///< Flag zeigt an, ob die Anfahrkarft des Radialschlittens erreicht wurde [0-1]
	int DRA_kraft_anfahren_erreicht;		///< Flag zeigt an, ob die Anfahrkarft der Druckrolle(Auslauf) erreicht wurde [0-1]
	int DRE_kraft_anfahren_erreicht;		///< Flag zeigt an, ob die Anfahrkarft der Druckrolle(Einlauf) erreicht wurde [0-1]

/**
  * @var ag_mode
  * @brief Beschreibt den Modus des Axialgerüsts 
  */
	int ag_mode;                 ///< *		0 = Vorschubregelung, Abschaltmass nicht erreicht, AG schließt auf SMS-Position
	                             ///< *		1 = Kraftregelung, Abschaltmass nicht erreicht, AG schließt auf SMS-Position
	                             ///< *		2 = Vorschubregelung, Abschaltmass erreicht, AG schließt auf SMS-Position
	                             ///< *		3 = Kraftregelung, Abschaltmass  erreicht, AG schließt auf SMS-Position
	                             ///< *		4 = Vorschubregelung, Abschaltung nicht erreicht, IBF-Position
	                             ///< *		5 = Kraftregelung, Abschaltung nicht erreicht, IBF-Position
	                             ///< *		6 = Vorschubregelung, Abschaltung erreicht, IBF-Position
/**
  * @var ag_act
  * @todo Add DoxyGen Comment
  */
	int ag_act;
	int aso_mode;							///< Modus des Axialschlitten oben 
											///< *		0 = Verschubsteuerung
											///< *		1 = Kraftregelung
	int rs_mode;							///< Modus des Radialschlittens
											///< *		0 = Verschubsteuerung
											///< *		1 = Kraftregelung
	int Axial_Radialwalzen;					///< Auswahl Profilierungsmodus
											///< *		0 = Axialprofilieren 
											///< *		1 = Radialprofilieren
											///< *		2 = Formenspektrum
											///< *		3 = Schüssel
	int IBF_Abschaltung;					///< Flag zur Setzung der Abschaltung nach IBF-Vorgabe
	int AG_Start_erreicht;					///< = 1 wenn, Startposition für das Axialgerüst erreicht ist.

	int Bissverhaeltnis;					///< Auswahl Walzen mit oder ohne Bissverhältnis
											///< *		1 : mit Bissverhältnis walzen
											///< *		0 : ohne Bissverhältnis walzen
       
  
/** @var DA_Jenkouk_DW_Regelung
  * @brief Flag zum zuschalten/abschalten der Dorwalzregelung aus der DA 
  * Jenkouk 2008.
  * <p> Benötigt derzeit temporären Messaufbau (Stand 2008) 
  */
	int DA_Jenkouk_DW_Regelung;
  
/** @var DA_Jenkouk_Messen_ohne_Fahren
  * @brief Nur temporär für Einrichtebetrieb -> danach wieder löschen !!.
  */
	int DA_Jenkouk_Messen_ohne_Fahren; 
  
/** @var DA_Jenkouk_AG_Analyse
  * @brief Schalter für Regelanalyse des Axialgerüsts.
  */
	int DA_Jenkouk_AG_Analyse;
};

    struct Def_Zeit					///< Enthält Informationen über die Dauer der Ringumdrehungen
    {
        float Ringumdrehung;		///< Zeit für eine Ringumdrehung
        float Halbe_Ringumdrehung;	///< Zeit für 1/2 Ringumdrehung
        float t_Halte;				///< Haltezeit in [sec] (1sec = 1000ms)
									///< Zeit bis zum nächsten Walzfall in \link RPW::Main() \endlink
	};

/*----------------------------------------------------------------------------- */
/*                         IBF-IST Variablen                                    */
/*------------------------------------------------------------------------------*/

/** \struct Def_IBF_Allgemein_IST
  * @brief Enthält Informationen über die aktuellen Kräfte, Positionen und
  *       Geometrie, sowie Informationen über die den aktuellen Status
  *       des Radial- und Axialprofilieren.
  */
	struct Def_IBF_Allgemein_IST
	{

        /*---------------------------------------------------------------------------*/
        /*      Definition der allgemeinen Variabeln (ehemals axpro.h)               */
        /*                                                                           */
        /*       Variablen die zur Programmlaufzeit vorgegeben werden                */
        /*---------------------------------------------------------------------------*/

/*Wahlschalter 'intern' gesetzte*/ 

/** @var StartPos
  * @brief Bedingung fuer Anfahren der Startpostitionen (ersteProfilposition)
  * Info Modellwalzerk: wird in mapwonli zu Null und in interfac wieder 1 gesetzt
  */
		int		StartPos;
		int		Iter, K_Iter;
        char	ManAuswahl;				///< Auswahl von Aktionen bei manueller Steuerung
        int		Profilflag;				///< Einlesen des Profilflags, das in der Soll-Struktur geschrieben wird.
        char	InitAchse;				///< Flag zur Steuerung des Anfahrens an die Startposition.
										///< Mögliche Werte:
										///< *		'v'		: Interface Test.
										///< *		'w'		: Analyse Reglerverhalten Axialgerüst DA Jenkouk.
										///< *		'x'		: Axialgerüst auf Position 700mm + \link AG_Regelung::Sprunghoehe \endlink anfahren.
										///< *		'y'		: Axialgerüst auf Position 700mm anfahren.
										///< *		'a'		: Positionieren des Radialschlittens und Positionieren des Axialschlittens
										///<				  über Ringhöhe um ein Aufsetzen zu vermeiden.
										///< *		'b'		: Positionieren des Axialgerüsts an Startposition.
										///< *		'c'		: Position Axialgerüst: Profilierungsposition.
										///< *		'd'		: Position Axialschlitten.
										///< *		'z'		: 2 Umdrehungen abwarten für gleichmäßiges Profil über Umfang.
		short	InitAchse_gecastet;		///< Enthält Wert von Def_IBF_Allgemein_IST::InitAchse als Datentyp 'short'. Für Logger.
        char	ExitAchse;				///< Flag zur Steuerung des Auffahrens nach Prozessende.
    									///< Mögliche Werte:
										///< *		'a'		: Radialschlitten auf RS_Pos_Start zurückfahren.
										///< *		'b'		: Axialgerüst und Axialschlitten auf Startposition zurückfahren.
	
		float	FR;			///< Aktuelle radial Walzkraft (Banning gefiltert) in [N]
        float	FA;			///< Aktuelle axial Walzkraft (Banning gefiltert) in [N]
        float	FR_f;		///< Gefilterte Kraft Radial (MRAW) in [N], diese Variable ist nur beim Modellwalzwerk gültig.
        float	FA_f;		///< In Intefac gefilterte Kraft Axial (MRAW) in [N], diese Variable ist nur beim Modellwalzwerk gültig.
    
    /*Positionen aktuell*/
        float	RS_Pos;		///< Aktuelle Position de Dornwalze in [mm]
        float	AG_Pos;		///< Aktuelle Position des Axialgerüsts in [mm]
        float	ASO_Pos;	///< Aktuelle Position des Axialschlittens oben in [mm]
        float	TR_Pos;		///< Aktuelle Tastrollen-(Laser-) Position in [mm]
        float	ZAR_Pos;	///< Aktuelle Position des Zentrierarms rechts in [mm]
        float	ZAL_Pos;	///< Aktuelle Position des Zentrierarms links in [mm]
        
     
    #ifdef MRAW
        float ASU_Pos;		///< Aktuelle Position des Axialschlittens unten
    #endif

    /*Positionen Merker*/

        float RS_Pos_Null;		///< Vorformwanddicke aus Carwin [mm]
        float ASO_Pos_Null;		///< Vorformhöhe aus Carwin in [mm]
        float AG_Pos_Null;		///< Axial profilieren in [mm]
        float RS_Pos_Start;		///< Positionen in 'Walzen' vor profilieren in [mm]
        float AG_Pos_Start;		///< Positionen in 'Walzen' vor profilieren in [mm]
        float ASO_Pos_Start;	///< Positionen in 'Walzen' vor profilieren in [mm]
        
        /** @var ASO_Pos_Differenz
          * @brief Korrektur der Starthöhe aus Carwin (in IBF_ini definiert) in 
          * [mm]. Der Axialschlitten oben wird sonst auf Starthöhe gesetzt und
          * beim 'Positionierendes Axialgerüstes rutscht der Axialschlitten oben 
          * über.*/
        float ASO_Pos_Differenz;    

    
     /*Geometrie*/
       
        float Wanddicke_Ist;			///< Aktuelle Wanddicke, Auslausseite Radialschlitten
        float Rohling_h_angefahren;		///< Rohlingshöhe nach dem Anfahren in [mm]
        float Rohling_s_angefahren;		///< Rohlingswanddicke nach dem Anfahren [mm]
        float da;						///< Aktueller Außendurchmesser in [mm]
        float di;						///< aktueller Innendurchmesser in [mm]


/*---------------------------------------------------------------------------*/
/*  Variablen die vor Programmlaufzeit durch Benutzer vorgegeben werden      */
/*---------------------------------------------------------------------------*/

	    /*Wahlschalter 'extern' gesetzt*/
        struct IBF_Flag Flag;

		/*Kraft*/
		//	float RS_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
		//	float AS_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
		//	float AG_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
		//	float ZAR_Kraft_Vorgabe; /* Kraft [N] die in IBFPARA.ini definiert wird */
		//	float ZAL_Kraft_Vorgabe; /* Kraft [N] die in IBFPARA.ini definiert wird */
        
		//	float RS_Kraft_Anfahren; /* Anwalzkraft [N] aus IPFPARA.ini */
		//	float AS_Kraft_Anfahren; /* Anwalzkraft [N] aus IPFPARA.ini */
        
		/*Positionen*/
		float delta_tr;					///< Tastrollendifferenz zum Positionieren des Axialgerüstes beim Start in [mm]

		/*Geometrie*/
		struct Geometrie Vorring;		///< Struktur zur Geometrie des Vorrings

		/*Dynamik*/
		float eps_Vorschub;				///< Epsilon für diskontinuierlich
		struct Def_Zeit Zeit;			///< Struktur für die Zeit

		/* Strukturen zu IBF-Module "Flexibel Radial" und "Flexibel Axial" */

		/** @var Radial
		  * @brief Eine Struktur vom Typ \link Radial_Flex_Prof \endlink , die Informationen
		  * über das radiale Profilieren enthält.
		  */
		struct Radial_Flex_Prof Radial;
		/** @var Axial
		  * @brief Eine Struktur vom Typ \link Axial_Flex_Prof \endlink , die Informationen
		  * über das Axiale Profilieren enthält.*/
		struct Axial_Flex_Prof Axial;
		/** @var Formen
		  * @brief Eine Struktur vom Typ \link Formenspektrum \endlink
		  */
		struct Formenspektrum Formen;



/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  Strukturen und Variablen, die aus Studienarbeiten und Diplomarbeiten    */
/*  hervorgehen.                                                            */
/*--------------------------------------------------------------------------*/
    
		/** @var stuetz_var
		  * @brief Struktur zur Stützstellenberechnung
		  */
		struct stuetzstellen_var stuetz_var;
		/** @var DW_Regelung
		  * @brief Struktur für die Dornwalzregelung für das axiale Profilieren
		  * (DA Jenkouk April-Juli 2008)
		  */
		struct Def_DW_Regelung_DA_Jenkouk DW_Regelung;
		/** @var AG_Regelung
		  * @brief Struktur zur Axialgerüstregelung für das axiale Profilieren
		  * (DA Jenkouk April-Juli 2008)
		  */
		struct Axialgeruest_Regelung AG_Regelung;        
		/** @var Schuessel
		  * @brief Struktur vom Typ Def_IBF_Schuessel mit
		  * Informationen über den allgemeinen Status beim Schüsselwalzen und
		  * Formen der Schüssel.
		  */
		struct Def_IBF_Schuessel	Schuessel;
		struct IBF_Testfahrt		Test;

		struct Def_IBF_Ist_DRR		DRR_Param;
		struct Def_IBF_Ist_ZER		ZER_Param;
		
};

//--------------------------------------------------------------------------------------------------------------------------
//                  Allgemeine SOLL-Werte der IBF-Module
//--------------------------------------------------------------------------------------------------------------------------

/** \struct Def_IBF_Allgemein_SOLL
  * @brief Enthält Informationen über die Sollkräfte, -Positionen und
  *       -Geometrien, sowie Informationen über die den gewünschten Status
  *       des Radial- und Axialprofilieren.
  */
struct Def_IBF_Allgemein_SOLL
{

//---------------------------------------------------------------------------
// Definition der allgemeinen Variabeln
// ehemals Axpro.H
//---------------------------------------------------------------------------
   
/*Wahlschalter 'intern' gesetzte*/
    int		Profilflag;				///< Profilflag zur Steuerung des Prozessesablaufs.
									///< Mögliche Werte:
									///< *		-1		: Startpositionen lesen, Sollwertvorgaben. Anschließend Wechsel auf 0.
									///< *		0		: Startpositionen anfahren. Anschließend Wechsel auf 1.
									///< *		1		: Durch \link Axial_Radialwalzen \endlink vorgegebenes Walzstrategiemodul aufrufen.
									///< *		13		: IBF_Abschaltung()
									///< *		9		: Axialschlitten mit konstanter Geschwindigkeit zustellen, anschließend Wechsel in 11.
									///< *		11		: Rundungsphase, anschließend Wechsel in 12.
									///< *		12		: Hochfahren des Axialschlittens und Abfragen ob weitere Profilstufe gewalzt werden soll.
									///< *		2		: Rundungsphase. Wechselt nach Abschluss in 3
									///< *		3		: IBF_Abschaltung()
									///< *		345		: Radialschlitten und Axialschlitten auffahren.
	char	InitAchse;				///< Flags zur Steuerung des Anfahrens an die Startposition.
									///< Mögliche Werte:
									///< *		'v'		: Interface Test.
									///< *		'w'		: Analyse Reglerverhalten Axialgerüst DA Jenkouk.
									///< *		'x'		: Axialgerüst auf Position 700mm + \link AG_Regelung::Sprunghoehe \endlink anfahren.
									///< *		'y'		: Axialgerüst auf Position 700mm anfahren.
									///< *		'a'		: Positionieren des Radialschlittens und Positionieren des Axialschlittens
									///<				  über Ringhöhe um ein Aufsetzen zu vermeiden.
									///< *		'b'		: Positionieren des Axialgerüsts an Startposition.
									///< *		'c'		: Position Axialgerüst: Profilierungsposition.
									///< *		'd'		: Position Axialschlitten.
									///< *		'z'		: 2 Umdrehungen abwarten für gleichmäßiges Profil über Umfang.
    char ExitAchse;					///<
									///<
    
    /* Schalter Steuerung */
    int	RS_act;				///< Vorgaben von IBF auswertbar (1)
	int AS_act;				///< Vorgaben von IBF auswertbar (1)
    
    /* Sollkraefte */
    float RS_Kraft;			///< Kraft des Radialschlittens die an SMS Struktur übergeben wird in [N]
    float AS_Kraft;			///< Kraft des Axialschlittens die an SMS-Struktur übergeben wird in [N]
    float AG_Kraft;			///< Kraft des Axialgerüsts die an SMS-Struktur übergeben wird in [N]
    float ZAL_Kraft;		///< Kraft des Zentrierarms links die an SMS-Struktur übergeben wird in [N]
    float ZAR_Kraft;		///< Kraft des Zentrierarms rechts die an SMS-Struktur übergeben wird in [N]

    /*Positionen*/
    float RS_Pos;			///< Sollposition des Radialschlittens in [mm]
    float ASO_Pos;			///< Sollposition des Axialschlittens oben in [mm]
    float AG_Pos;			///< Sollposition des Axialgerüsts in [mm]
    
    float ZAR_Pos;			///< Sollposition Zentrierarm rechts in [mm]
    float ZAL_Pos;			///< Sollposition Zentrierarm links in [mm]

    float RS_Pos_end;		///< Soll-Endposition der Dornwalze, speziell wenn mehrer Soll-Positionen
							///< während der Laufzeit definiert werden in [mm]
								
    float min_RS_Pos;		///< minimale Dornwalzposition in [mm]
    float min_ASO_Pos;		///< minimale Axialwalzhöhe in [mm]
    float tr_pos;			///< Sollposition für Tastrolle beim Axialenprofilieren in [mm]
    float delta_tr;			///< Tastrollendifferenz zum Positionieren des Axialgerüstes beim Start in [mm]

    /*Geschwindigkeiten*/
    float RS_V;				///< Sollgeschwindigkeit des Radialschlittens
    float ASO_V;			///< Sollgeschwindigkeit des Axialschlittens oben
    float AG_V;				///< Sollgeschwindigkeit des Axialgeruestes
    float ZAR_V;			///< Sollgeschwindigkeit des Zentrierarms rechts
    float ZAL_V;			///< Sollgeschwindigkeit des Zentrierarm links

    /*Positionen Merker*/
    float RS_Pos_Null;		///< Inizitalisierung nach manueller Anfahrt / vor Profilieren
    float RS_Pos_Start;		///< Position in 'Walzen' vor Porilieren
    float Soll_RS_Pos_end;  ///< Soll-Endposition des Radialschlittens

    float Soll_ASO_Pos_alt;	///< Sollposition des oberen Axialschlitten Zum Zeitpunkt t-1 benoetigt in case 12/13
    float ASO_Pos_Null;		///<
    float ASO_Pos_Start;	///< Soll-Position des Axialschlittens oben zum Startzeitpunkt

    // TODO comments for doxygen
    float AG_Pos_Null;		///<
    float AG_Pos_Start;		///< Sart-Position des Axialgeruests

    /*Wartezeiten*/
    
    //float t_Halte;          // Haltezeit in sec (1sec = 1000 ms) 
    struct Def_Zeit Zeit;


    /*Geometrie*/

    float Rohling_h_angefahren;		///< Rohlingshoehe nach dem Anfahren in [mm]
    float Rohling_s_angefahren;		///< Rolingswanddicke nach dem Anfahren [mm]
    


    /*---------------------------------------------------------------------------*/
    /*  Variablen die vor Programmlaufzeit durch Benutzer vorgegeben werden      */
    /*---------------------------------------------------------------------------*/

    /*Wahlschalter 'extern' gesetzt*/
    struct IBF_Flag Flag;			///< IBF_Flag Struktur, die extern festleget wird

   /* Flexibel Radial Profliert */
    struct Radial_Flex_Prof Radial;	///< Radial_Flex_Prof Struktur für die Radiale Profilierung
    struct Axial_Flex_Prof Axial;	///< Axial_Flex_Prof Struktur zum Axialen Profilieren
    struct Formenspektrum Formen;
    struct stuetzstellen_var stuetz_var;   
    	

    
    /*Kraft*/
    float RS_Kraft_Vorgabe;		///< Kraft für den Radialschlitten die in IBFPARA.ini difiniert wird in [N]
    float AS_Kraft_Vorgabe;		///< Kraft für den Axialschlitten die in IBFPARA.ini definiert wird in [N]
    float AG_Kraft_Vorgabe;		///< Kraft des Axialgerüsts die in IBFPARA.ini definert wird in [N]
	float ZAR_Kraft_Vorgabe;		///< Kraft des Zentrierarms rechts die in IBFPARA.ini definiert wird in [N]
    float ZAL_Kraft_Vorgabe;		///< Kraft des Zentrierarms links die in IBFPARA.ini definiert wird in [N]
	float DRA_Kraft_Vorgabe;		///< Kraft der Druckrolle(Auslauf) die in IBFPARA.ini definiert wird in [N]
    float DRE_Kraft_Vorgabe;		///< Kraft der Druckrolle(Einlauf) die in IBFPARA.ini definiert wird in [N]
    float RS_Kraft_Anfahren;		///< Anwalzkraft des Radialschlittens die in IBFPARA.ini definiert wird in [N]
    float AS_Kraft_Anfahren;		///< Anwalzkraft des Axialschlittens die in IBFPARA.ini definiert wird in [N]
 
    
    
    /*Dynamik*/

    /*Geometrie*/
  
    //-----------------------------------------------------------------------------
   
    /* Axialschlitten unten  */
    #ifdef MRAW
    float ASU_Pos;
    #endif

	float Soll_ASU_Pos;		///< Soll-Position des Axialschlittens unten
    float Soll_ASU_V;		///< Soll-Geschwindigkeit des Axialschlittens unten
  

    /*--------------------------------------------------------------------------*/
    /*                                                                          */
    /*  Strukturen und Variablen, die aus Studienarbeiten und Diplomarbeiten    */
    /*  hervorgehen.                                                            */
    /*--------------------------------------------------------------------------*/
    /** @var DW_Regelung
      * @brief Struktur Dornwalzregelung für das axiale Profilieren (DA Jenkouk 
      * April-Juli 2008)*/ 
    struct Def_DW_Regelung_DA_Jenkouk DW_Regelung;
    /** @var AG_Regelung
      * @brief Struktur Axialgerüstregelung für das axiale Profilieren (DA Jenkouk
      * April-Juli 2008)*/
    struct Axialgeruest_Regelung AG_Regelung;

    /** @var IBF_Schuessel
     * @brief Struktur vom Typ Def_IBF_Schuessel mit
     * Informationen über den allgemeinen Status beim Schüsselwalzen und
     * Formen der Schüssel.*/
    struct Def_IBF_Schuessel	Schuessel;	///< Soll-Parameter der Schuesselwalzstrategie

	struct Def_IBF_Soll_DRR		DRR_Param;	///< Sollwerte fuer Druckrollenregelung
	struct Def_IBF_Soll_ZER		ZER_Param;  ///< Sollwerte fuer Zentrierrollenregelung
};

#endif // _IBF_struct_HPP
