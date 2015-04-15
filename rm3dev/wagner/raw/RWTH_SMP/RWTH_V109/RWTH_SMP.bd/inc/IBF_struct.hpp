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

// Definition von PI 
#ifndef  PI
#define  PI 3.14159265358979323846            
#endif 


/*-----------------------------------------------------------------------------------------*/
/*          Includedatein die fuer die IBF-Strukturen benoetoigt werden                      */
/*-----------------------------------------------------------------------------------------*/
    #include "ibf_tool.hpp"
    #include "IBF_radflex.hpp"
    #include "IBF_axproflex.hpp"
    #include "IBF_stuetz.hpp"
    #include "IBF_dw_regelung.hpp"
  	#include "IBF_formenspek.hpp"
    #include "ibf_Schuessel.hpp"

    
/*-----------------------------------------------------------------------------------------*/ 
/*                  Strucktur Geometrie | IBF-Flags | Radial-Profilierenodule              */
/*-----------------------------------------------------------------------------------------*/
    /** \struct IBF_Testfahrt
      * @brief enthaelt Informationen, ob eine testfahrt gefahren wird,
      *       und mit welchem Aussendruchmesser
      */
    struct IBF_Testfahrt
    {
    	/** @var Flag
    	 * @brief Schalter fuer Testfahrt (0 = Aus , 1 = An)*/
      int Flag;
      /** @var Ring_AD
       * @brief simulierter Ringdurchmesser fuer Testfahrt in [mm]*/
      float Ring_AD;
    };
 
    /** \struct Geometrie
      * @brief Beinhaltet den Aussendurchmesser, Wandstaerke und Anfangshoehe des Rings
      */
    struct Geometrie
    {
      /** @var D_Null
       * @brief Aussendurchmesser des Ringes */
      float D_Null;              // Aussendurchmesser 
      /** @var Wandstaerke_Null
       * @brief Anfangswanddicke -> notwendig, da am Modelwalzwerk Daten nciht eingelesen werden koennen */
      float Wandstaerke_Null;    // Anfangswanddicke ->notwendig, da am Modellwalzwerk Daten nicht eingelesen werden koennen
      /** @var Start_Ringhoehe
       * @brief Anfangsringhoehe */
      float Start_Ringhoehe;     // Anfangsringhoehe
    };


    /** \struct IBF_Flag
      * @brief Enthaelt die wichtigsten Flags. Dies beinhaltet die Flags für die,
      *       sowie Modi der einzelnen Schlitten, ob die Abschaltmasse erreicht
      *       sind, sowie Informationen fuer die Dornwalzregelung von V. Jenkouk.
      */
    struct IBF_Flag
    {
    	/** @var rs_kraftregler_aktiv
    	 * @brief Flag zum Arbeien mit/ohne Radialschittenkraft [0-1]*/
      int rs_kraftregler_aktiv;
      /** @var as_kraftregler_aktiv
       * @brief Flag zum Arbeiten mit/ohne Axialschlittenkraft [0-1]*/
      int as_kraftregler_aktiv;

      /** @var ag_kraftregler_aktiv
       * @brief Flag zum Arbeiten mit/ohne Axialgeruestkraft [0-1]*/
      int ag_kraftregler_aktiv;
      /** @var zal_kraftregler_aktiv
       * @brief Flag zum Arbeiten mit/ohne Zentrierarmkraft links [0-1]*/
      int zal_kraftregler_aktiv;
      /** @var zar_kraftregler_aktiv
       * @brief Flag zum Arbeiten mit/ohne Zentrierarmkraft rechts [0-1]*/
      int zar_kraftregler_aktiv;

      /** @var rs_kraftanfahren_aktiv
       * @brief Flag zum Kraftanfahren RADIALl an Roling [0-1]*/
      int rs_kraftanfahren_aktiv;
      /** @ var as_kraftanfahren_aktiv
       * @brief Flag zum Kraftanfahren AXIAL an Roling [0-1]*/
      int as_kraftanfahren_aktiv;

      /** @var as_kraft_anfahren_erreicht
       * @brief Flag, dass anzeigt ob die Anfahrkraft des Axialschlittens erreicht wurde [0-1]*/
      int as_kraft_anfahren_erreicht;
      /** @var rs_kraft_anfahren_erreicht
       * @brief Flag, dass anzeigt ob die Anfahrkarft des Radialschlittens erreicht wurde [0-1]*/
      int rs_kraft_anfahren_erreicht; /* Flag, dass Anfahrkraft erreicht wurde */

      /** @var ag_mode
       * @brief Beschreibt den Modus des Axialgeruests */
      int ag_mode;                 /* 0 = Vorschubregelung, Abschaltmass nicht erreicht, AG schlie�t auf SMS-Position
                                      1 = Kraftregelung, Abschaltmass nicht erreicht, AG schlie�t auf SMS-Position
                                      2 = Vorschubregelung, Abschaltmass erreicht, AG schlie�t auf SMS-Position
                                      3 = Kraftregelung, Abschaltmass  erreicht, AG schlie�t auf SMS-Position
                                      4 = Vorschubregelung, Abschaltung nicht erreicht, IBF-Position
                                      5 = Kraftregelung, Abschaltung nicht erreicht, IBF-Position
                                      6 = Vorschubregelung, Abschaltung erreicht, IBF-Position
                                   */
      int ag_act;

      /** @var aso_mode
       * @brief Modus des Axialschlitten oben (0 = Verschubsteuerung, 1 = Kraftregelung)*/
      int aso_mode;

      /** @var rs_mode
       * @brief Modus des Radialschlittens (0 = Verschubsteuerung, 1 = Kraftregelung)*/
      int rs_mode;

      /** @var Axial_Radialwalzen
       * @brief Flag zur Profilierun (0 = Axialporfilieren, 1 = Radialporfilieren)*/
      int Axial_Radialwalzen;     /* Flag zur Auswahl Axialprofilieren (0) bzw. 
                                     Radialprofilieren (1)*/
      /** @var IBF_Abschaltung
       * @brief Flag zur Setzung der Abschaltung nach IBF-Vorgaben*/
      int IBF_Abschaltung;       /* Flag zur Setzung der Abschaltung nach IBF-Vorgabe */

      /** @var AG_Start_erreicht
        * @brief Genau dann 1 wenn, Startposition für das Axialgerüst erreicht ist.*/
      int AG_Start_erreicht;
      /** @var Bissverhaeltnis
        * @brief Flag, dass Informationen über das Walzen mit oder ohne Bissverhältnis
        *        enthält. 1 wenn mit Bissverhältnis gewalzt werden soll, sonst 0*/
      int Bissverhaeltnis;       
      
      /** @var DA_Jenkouk_DW_Regelung
        * @brief Flag zum zuschlaten/abschalten der Dorwalzregelung aus der DA 
        * Jenkoukg 2008.
        * <p> Benötigt derzeit temporären Messaufbau (Stand 2008) */
      int DA_Jenkouk_DW_Regelung;
      
      /** @var DA_Jenkouk_Messen_ohne_Fahren
        * @brief Nur temporär für Einrichtebetrieb.*/
      int DA_Jenkouk_Messen_ohne_Fahren; 
      /*nur temporär für Einrichtebetrieb -> danach wieder löschen !!!!!!!!*/
      
      /** @var DA_Jenkouk_AG_Analyse
        * @brief Schalter für Regelanalyse des Axialgerüsts*/
      int DA_Jenkouk_AG_Analyse;      /* Schalter für Regelanalyse des Axialgerüstes */

    };

    /** \struct Def_Zeit
     * @brief Enhaelt Informationen ueber Ringumdrehungen*/
    struct Def_Zeit
    {
    	/** @var Ringumdrehung
    	 * @brief Zeit fuer eine Ringumdrehung*/
        float Ringumdrehung;
        /**@var Halbe_Ringumdrehung
         * @brief Zeit fuer 1/2 Ringumdrehung*/
        float Halbe_Ringumdrehung;
        /** @var t_Halte
         * @brief Haltezeit in [sec] (1sec = 1000ms)
         * Zeit bis zum naechsten Walzfall in \link main \endlink */
        float t_Halte;
    };


 

/*----------------------------------------------------------------------------- */
/*                         IBF-IST Variablen                                    */
/*------------------------------------------------------------------------------*/

/** \struct Def_IBF_Allgemein_IST
  * @brief Enthaelt Informationen ueber die aktuellen Kraefte, Positionen und
  *       Geometrien, sowie Informationen ueber die den aktuellen Status
  *       des Radial- und Axialprofilieren.
  */
struct Def_IBF_Allgemein_IST
{

	/** @var debug_InnerSwitchCase
	  * @brief Eine Variable welche zum Debugen genutzt wird. Sie hat keinen Einfluss
	  * auf das Programm. */
	int debug_InnerSwitchCase;

        /*---------------------------------------------------------------------------*/
        /*      Definition der allgemeinen Variabeln (ehemals axpro.h)               */
        /*                                                                           */
        /*       Variablen die zur Programmlaufzeit vorgegeben werden                */
        /*---------------------------------------------------------------------------*/

        /** @var counter
		 * @brief Einzaehler der zum Debuggen in Version V109 verwendet wurde*/
		int counter;

		/** @var countDebug
		 * @brief Ein Zaehler der zum Debuggen in Version V109 verwendet wurde */
		int countDebug;
 
    /*Wahlschalter 'intern' gesetzte*/ 

    	/** @var StartPos
    	 * @brief Bedingung fuer Anfahren der Startpostitionen (ersteProfilposition)
    	 * 		Info Modellwalzerk: wird in mapwonli zu Null und in interfac wieder 1 gesetzt*/
        int StartPos;
        /** @var ManAuswahl
         * @brief Auswahl von Aktionen bei manueller Steuerung*/
        char ManAuswahl;

        /** @var Profilflag
         * @brief Einlesen des Profielflags, das in der Soll-Strukturg geschrieben wird*/
        int  Profilflag;
        /** @var InitAchse
         * @brief Einlesen des Flags fuer Anfahren der Startposition in Reihenfolge Radialschlitten, Axialgeruest, Axialschlitten*/
        char InitAchse;
        /** @var InitAchse_gecastet
         * @brief InitAchse in zu einer short Variable gecastet.
         * @brief Einlesen des Flags fuer Anfahren der Startposition in Reihenfolge Radialschlitten, Axialgeruest, Axialschlitten*/
        short InitAchse_gecastet;
        /** @var ExitAchse
         * @brief Flag fuer Lueften der Reihenfolge die in InitAchse festgelegt wurde*/
        char ExitAchse;
    
    /*Kraefte*/
        /** @var FR
         * @brief Aktuelle radial Walzkraft (Banning gefiltert) in [N]*/
        float FR;
        /** @var FA
         * @brief Aktuelle axial Walzkraft (Banning gefiltert) in [N]*/
        float FA;
        /** @var FR_f
         * @brief gefilterte Kraft Radial (MRAW) in [N], diese Variable ist nur beim Modellwalzwerk verwendbar*/
        float FR_f;
        /** @var FA_f
         * @brief in Intefac gefiltete Kraf Axial (MRAW) in [N], diese variable ist nur beim Modellwalzwerk verwendbar*/
        float FA_f;
    
    /*Positionen aktuell*/
        /** @var RS_Pos
         * @brief aktuelle Position de Dornwalze in [mm]*/
        float RS_Pos;
        /** @var AG_Pos
         * @brief Aktuelle Position des Axialgeruests in [mm]*/
        float AG_Pos;
        /** @var ASO_Pos
         * @brief Aktuelle Position des Axialschlittens oben in [mm]*/
        float ASO_Pos;
        /** @var TR_Pos
         * @brief Aktuelle Tastrollen-(Laser-) Position in [mm]*/
        float TR_Pos;
        /** @var ZAR_Pos
         * @brief Aktuelle Position des Zentrierarms rechts in [mm]*/
        float ZAR_Pos;
        /** @var ZAL_Pos
         * @brief Aktuelle Position des Zentrierarm links in [mm]*/
        float ZAL_Pos;
        
     
    #ifdef MRAW
        /** @var ASU_Pos
         * @brief Aktuelle Position des Axialschlittens unten*/
        float ASU_Pos;
    #endif

    /*Positionen Merker*/

        /** @var RS_Pos_Null
         * @brief Vorformwanddicke aus Carwin [mm]*/
        float RS_Pos_Null;
        /** @var ASO_Pos_Null
         * @brief Vorformhoehe aus Carwin in [mm]*/
        float ASO_Pos_Null;
        /** @var AG_Pos_Null
         * @brief Axial Profilieren in [mm]*/
        float AG_Pos_Null;
        /** @var RS_Pos_Start
         * @brief Positionen in 'Walzen' vor Profilieren [mm]*/
        float RS_Pos_Start;
        /** @var AG_Pos_Start
         * @brief Positionen in 'Walzen' vor Profilieren in [mm]*/
        float AG_Pos_Start;
        /** @var ASO_Pos_Start
         * @brief osition in 'Walzen' vor Porfilieren in [mm]*/
        float ASO_Pos_Start;
        
        /** @var ASO_Pos_Differenz
          * @brief Korrektur der Starthöhe aus Carwin (in IBF_ini definiert) in 
          * [mm]. Der Axialschlitten oben wird sonst auf Starthöhe gesetzt und
          * beim 'Positionierendes Axialgerüestes rutscht der Axialschlitten oben 
          * über.*/
        float ASO_Pos_Differenz;    

    
     /*Geometrie*/
       
        /** @var Wanddicke_Ist
         * @brief Aktuelle Wanddicke, Auslausseite Radialschlitten*/
       float Wanddicke_Ist;
       /** @var Rohling_h_angefahren
        * @brief Rohlingshoehe nach dem Anfahren in [mm]*/
       float Rohling_h_angefahren;
       /** @var Rohling_s_angefahren
        * @brief Rohlingswanddicke nach dem Anfahren [mm]*/
       float Rohling_s_angefahren;
       /** @var da
         * @brief Aktueller Außendurchmesser in [mm]*/ 
       float da;
       /** @var di
         * @brief aktueller Innendurchmesser in [mm]*/
       float di;


    /*---------------------------------------------------------------------------*/
    /*  Variablen die vor Programmlaufzeit durch Benutzer vorgegeben werden      */
    /*---------------------------------------------------------------------------*/

    /*Wahlschalter 'extern' gesetzt*/
        
     struct IBF_Flag Flag;

    /*Kraft*/
     //   float RS_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
     //   float AS_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
     //   float AG_Kraft_Vorgabe;  /* Kraft [N] die in IBFPARA.ini definiert wird */
     //   float ZAR_Kraft_Vorgabe; /* Kraft [N] die in IBFPARA.ini definiert wird */
     //   float ZAL_Kraft_Vorgabe; /* Kraft [N] die in IBFPARA.ini definiert wird */
        
     //   float RS_Kraft_Anfahren; /* Anwalzkraft [N] aus IPFPARA.ini */
     //   float AS_Kraft_Anfahren; /* Anwalzkraft [N] aus IPFPARA.ini */
    
    /*Positionen*/
    
    /** @var delta_tr
      * @brief Tastrollendifferenz zum Positionieren des Axialgerüstes beim Start
      * in [mm]*/ 
    float delta_tr;


    /*Geometrie*/
        /** @var Vorring
         * @brief Struktur zur Geometrie des Vorrings*/
        struct Geometrie Vorring;

    /*Dynamik*/
        /** @var eps_Vorschub
         * @brief Epsilon fuer diskontinuierlich*/
    float eps_Vorschub; // Epsilon fuer diskontinuierlich 
    
    
    /** @var Zeit
     * @brief Struktur fuer die Zeit*/
    struct Def_Zeit Zeit;

    /* Strukturen zu IBF-Module "Flexibel Radial" und "Flexibel Axial" */

    /** @var Radial
     * @brief Eine Struktur vom Typ \link Radial_Flex_Prof \endlink , die Informationen
     * ueber das radiale Profilieren enthaelt.*/
    struct Radial_Flex_Prof Radial;
    /** @var Axial
     * @brief Eine Struktur vom Typ \link Axial_Flex_Prof \endlink , die Informationen
     * ueber das Axiale Profilieren enthaelt.*/
    struct Axial_Flex_Prof Axial;
	  /** @var Formen
     * @brief Eine Struktur vom Typ \link Formenspektrum \endlink */
    struct Formenspektrum Formen;

    /*--------------------------------------------------------------------------*/
    /*                                                                          */
    /*  Strukturen und Variablen, die aus Studienarbeiten und Diplomarbeiten    */
    /*  hervorgehen.                                                            */
    /*--------------------------------------------------------------------------*/
    
    /** @var stuetz_var
     * @brief Struktur zur Stuetzstellenberechnung*/
    struct stuetzstellen_var stuetz_var;
    /** @var DW_Regelung
      * @brief Struktur für die Dornwalzregelung für das axiale Profilieren
      * (DA Jenkouk April-Juli 2008)*/
    struct Def_DW_Regelung_DA_Jenkouk DW_Regelung;
    /** @var AG_Regelung
      * @brief Struktur zur Axialgerüstregelung für das axiale Profilieren
      * (DA Jenkouk April-Juli 2008)*/
    struct Axialgeruest_Regelung AG_Regelung;        
   
    /** @var IBF_Schuessel
     * @brief Struktur vom Typ \link Def_IBF_Schuessel \endlink mit
     * Informationen ueber den allgemeinen Status beim Schuesselwalzen und
     * Formen der Schuessel */
    struct Def_IBF_Schuessel IBF_Schuessel;

    struct IBF_Testfahrt Test;


};



//--------------------------------------------------------------------------------------------------------------------------
//                  Allgemeine SOLL-Werte der IBF-Module
//--------------------------------------------------------------------------------------------------------------------------

/** \struct Def_IBF_Allgemein_SOLL
  * @brief Enthaelt Informationen ueber die Sollkraefte, -Positionen und
  *       -Geometrien, sowie Informationen ueber die den gewuenschten Status
  *       des Radial- und Axialprofilieren.
  */
struct Def_IBF_Allgemein_SOLL
{

//---------------------------------------------------------------------------
// Definition der allgemeinen Variabeln
// ehemals Axpro.H
//---------------------------------------------------------------------------
   
    		/*Wahlschalter 'intern' gesetzte*/
	/** @var Profilflag
	 * @brief Schreiben des Profilflags, das in der Ist-Struktur eingelesen wird*/
    int  Profilflag;
    /** @var InitAchse
     * @brief Schreiben des Flags fuer Anfahen der Startposition in der Reihenfolge Radialschlitten, Axialgeruest, Axialschlitten*/
    char InitAchse;
    /** @var ExitAchse
     * @brief Flat fuer Lueften in Reihenfolge wie in InitAchse*/
    char ExitAchse;

    
    /* Schalter Kraftregler */
    
    
    /* Sollkraefte */
    /** @var RS_Kraft
     * @brief Kraft des Radialschlittens die an SMS Struktur uebergeben wird in [N]*/
    float RS_Kraft;
    /** @var AS_Kraft
     * @brief Kraft des Axialschlittens die an SMS-Struktur uebergeben wird in [N]*/
    float AS_Kraft;
    /** @var AG_Kraft
     * @brief Kraft des Axialgeruests die an SMS-Struktur uebergeben wird in [N]*/
    float AG_Kraft;
    /** @var ZAL_Kraft
     * @brief Kraft des Zentrierarms links die an SMS-Struktur uebergeben wird in [N]*/
    float ZAL_Kraft;
    /** @var ZAR_Kraft
     * @brief Kraft des Zentrierarms rechts die an SMS-Struktur uebergeben wird in [N]*/
    float ZAR_Kraft;

    /*Positionen*/
    /** @var RS_Pos
     * @brief Sollposition des Radialschlittens in [mm]*/
    float RS_Pos;
    /** @var ASO_Pos
     * @brief Sollposition des Axialschlittens oben in [mm]*/
    float ASO_Pos;
    /** @var AG_Pos
     * @brief Sollposition des Axialgeruests in [mm]*/
    float AG_Pos;
    
    /** @var ZAR_Pos
     * @brief Soll-Position Zentrieramr rechts in [mm]*/
    float ZAR_Pos;
    /** @var ZAL_Pos
     * @brief Soll-Position Zentrierarm links in [mm]*/
    float ZAL_Pos;

    /** @var RS_Pos_end
     * @brief Soll-Endpositin der Dornwalze, speziell wenn mehrer Soll-Positionen waehren der Laufzeit definiert werden in [mm]*/
    float RS_Pos_end;

    /** @var min_RS_Pos
     * @brief minimale Dornwalzposition in [mm]*/
    float min_RS_Pos;
    /** @var min_ASO_Pos
     * @brief minimalse Axialwalzhoere in [mm]*/
    float min_ASO_Pos;
    /** @var tr_pos
      * @brief Sollposition für Tastrolle beim Axialenprofilieren in [mm]*/ 
    float tr_pos;
    /** @var delta_tr
      * @brief Tastrollendifferenz zum Positionieren des Axialgerüstes beim Start
      * in [mm]*/
    float delta_tr;

    /*Geschwindigkeiten*/
    /** @var RS_V
     * @brief Sollgeschwindigkeit des Radialschlittens*/
    float RS_V;
    /** @var ASO_V
     * @brief Sollgeschwindigkeit des Axialschlittens oben*/
    float ASO_V;
    /** @var AG_V
     * @brief Sollgeschwindigkeit des  Axialgeruestes*/
    float AG_V;
    /** @var ZAR_V
     * @brief Sollgeschwindigkeit des Zentrierarms rechts*/
    float ZAR_V;
    /** @var ZAR_V
     * @brief  Sollgeschwindigkeit des Zentrierarm links*/
    float ZAL_V;

    /*Positionen Merker*/
    /** @var RS_Pos_Null
     * @brief Inizitalisierung nach manueller Anfahrt / vor Profilieren*/
    float RS_Pos_Null;
    /** @var RS_Pos_Start
     * @brief Position in 'Walzen' vor Porilieren*/
    float RS_Pos_Start;
    /** @var Soll_RS_Pos_end
     * @brief Soll-Endposition des Radialschlittens*/
    float Soll_RS_Pos_end;  // Soll-Endposition

    /** @var Soll_ASO_Pos_alt
     * @brief Sollposition des oberen Axialschlitten Zum Zeitpunkt t-1 benoetigt in case 12/13*/
    float Soll_ASO_Pos_alt;
    /** @var ASO_Pos_Null
     * @brief */
    float ASO_Pos_Null;
    /** @var ASO_Pos_Start
     * @brief Soll-Position des Axialschlittens oben zum Startzeitpunk*/
    float ASO_Pos_Start;

    // TODO comments for doxygen
    float AG_Pos_Null;
    /** @var AG_Pos_Start
     * @brief Sart-Position des Axialgeruests*/
    float AG_Pos_Start;

    /*Wartezeiten*/
    
    //float t_Halte;          // Haltezeit in sec (1sec = 1000 ms) 
    /** @var Zeit
     * @brief Struktur einer Zeit*/
    struct Def_Zeit Zeit;


    /*Geometrie*/

    /** @var Rohling_h_angefahren
     * @brief Rohlingshoehe nach dem Anfahren in [mm]*/
    float Rohling_h_angefahren;
    /** @var Rohling_s_angefahren
     * @brief Rolingswanddicke nach dem Anfahren [mm]*/
    float Rohling_s_angefahren;
    


    /*---------------------------------------------------------------------------*/
    /*  Variablen die vor Programmlaufzeit durch Benutzer vorgegeben werden      */
    /*---------------------------------------------------------------------------*/

    /*Wahlschalter 'extern' gesetzt*/
    /** @var Flag
     * @brief IBF_Flag Strukutr, die etern festleget wird*/
    struct IBF_Flag Flag;

   /* Flexibel Radial Profliert */
    /** @var Radial
     * @brief Radial_Flex_Prof Struktur f�r die Radiale Profilierung*/
    struct Radial_Flex_Prof Radial;
    /** @var Axial
     * @brief Axial_Flex_Prof Struktur zum Axialen Profilieren*/
    struct Axial_Flex_Prof Axial;
    /** @var Formen
     * @brief Eine Struktur vom Typ \link Formenspektrum \endlink */
    struct Formenspektrum Formen;
    /** @var stuetz_var
     * @brief Eine Struktur vom Typ \link stuetzstellen_var \endlink */
    struct stuetzstellen_var stuetz_var;   
    	

    
    /*Kraft*/
    /** @var RS_Kraft_Vorgabe
     * @brief Kraft f�r den Radialschlitten die in IBFPARA.ini difiniert wird in [N]*/
     float RS_Kraft_Vorgabe;
     /** @var AS_Kraft_Vorgabe
      * @brief Kraf fuer den Axialschlitten die in IBFPARA.ini definiert wird in [N]*/
     float AS_Kraft_Vorgabe;
     /** @var AG_Kraft_Vorgabe
      * @brief Kraft des Axialgeruests die in IBFPARA.ini definert wird in [N]*/
     float AG_Kraft_Vorgabe;
     /** @var ZAR_Kraft_Vorgabe
      * @brief Kraft des Zentrierarms links die in IBFPARA.ini definiert wird in [N]*/
     float ZAR_Kraft_Vorgabe;
     /** @var ZAL_Kraft_Vorgabe
      * @brief Kraft des Zentrierarms rechts die in IBFPARA.ini definiert wird in [N]*/
     float ZAL_Kraft_Vorgabe;
     /** @var RS_Kraft_Anfahren
      * @brief Anzalzkraft des Radiaschlittens die in IBFPARA.ini definiert wird in [N]*/
     float RS_Kraft_Anfahren;
     /** @var AS_Kraft_Anfahren
      * @brief Anwalzkraft des Axialschlittens die in IBFPARA.ini definiert wird in [N]*/
     float AS_Kraft_Anfahren;
 
    
    
    /*Dynamik*/

    /*Geometrie*/
  
    //-----------------------------------------------------------------------------
   
    /* Axialschlitten unten  */
    #ifdef MRAW
     /** @var ASU_Pos
      * @brief aktuelle Axialsclhittenposition unten*/
    float ASU_Pos;
    #endif
    /** @var Soll_ASU_Pos
     * @brief Soll-Position des Axialschlitten unten*/
    float Soll_ASU_Pos;
    /** @var Soll_ASU_V
     * @brief Soll-Geschwindigkeit des Axialschlittens unten*/
    float Soll_ASU_V;
  

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
     * @brief Struktur vom Typ \link Def_IBF_Schuessel \endlink mit
     * Informationen ueber den allgemeinen Status beim Schuesselwalzen und
     * Formen der Schuessel */
    struct Def_IBF_Schuessel IBF_Schuessel;
};




#endif	
