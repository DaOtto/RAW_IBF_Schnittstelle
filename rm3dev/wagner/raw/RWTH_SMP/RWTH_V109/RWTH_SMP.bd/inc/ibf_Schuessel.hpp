#include <time.h>
#include "rpw.hpp"
#include "IBF_struct.hpp"
#include <math.h>
#include <exception>
/*--FILE HEADER---------------------------------------------------------------
;   filename        : ibf_Schuessel.hpp
;   version         : V1.0
;   contents        : IBF-Variablen IBF software 
;   author          : Joachim Seitz, Jan Uthoff, IBF RWTH Aachen
;   date            : January, 2014
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   enthält alle Strukturen und Variablen, die für das Walzen in
;               zu einer Schuessel noetig sind
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

#ifndef _ibf_Schuessel_hpp

  #define _ibf_Schuessel_hpp
  

  
  
  /** \def T_KLETTERN_STARTEN
   * Zeit in [sec] nach der begonnen wird den Kletterprozess zu starten. */
  #define T_KLETTERN_STARTEN 5
  /** \def KLETTER_PUFFER 
   * Puffer bei der Berechnung, ob der Ring kletter oder nicht. Dieser
   * wird genutzt, damit nicht faelschlicherweise angenommen wird, dass der Ring
   * klettert, obwohl er es nicht tut.*/
  #define KLETTER_PUFFER 0

  /** \def ANZAHL_DURCHMESSER_MESSUNGEN
   * Entspricht der Anzahl der Messungen des Ringdurchmessers, die
   * verwendet werden um den Ringdurchmesser abzuschätzen.*/
  #define ANZAHL_DURCHMESSER_MESSUNGEN 5

  /** \def T_ZENTRIERROLLEN_KONTROLLE
   * Zeit nach der die Position der Zentrierrollen neu berechnet wird. */
  #define T_ZENTRIERROLLEN_KONTROLLE 3
 
  /** \def OEFFNEN
   * @brief Wert der Zentrierrollen, falls sie geöffnet sind, oder geöffnet
   * werden sollen*/
  #define OEFFNEN 1

  /** \def SCHLIESSEN
   * @brief Wert der Zentrierrollen, falls sie geschlossen sind, oder
   * geschlossen werden sollen.*/
  #define SCHLIESSEN 0

  /** \def LINKS
   * @brief Falls der linke Zentrierarm betrachtet wird*/
  #define LINKS 0
   /** \def RECHTS
   * @brief Falls der rechte Zentrierarm betrachtet wird*/
  #define RECHTS 1
  /** \def ZENTRIERROLLEN_OEFFNEN_OFFSET
   * Der Abstand den die Zentrierrollen vom Ring haben soll, wenn die Rollen
   * nicht geschlossen sind. */
  #define ZENTRIERROLLEN_OEFFNEN_OFFSET 100

  /** \def V_ZUSTELLUNG_AXIALSCHLITTEN_OBEN
   * @brief Geschwindigkeit mit der der Axialschlitten oben zugestellt werden
   * soll */
   #define V_ZUSTELLUNG_AXIALSCHLITTEN_OBEN 10

  /** \def RADIALER_PUFFER
   * Ein Puffer, der fuer die Berechung der Hauptwalzposition benoetigt wird */
  #define RADIALER_PUFFER 50

  /** \def AXIAL_PUFFER_GERUEST
   * Ein Puffer, der fuer die Berechung des Axialgeruestes benoetigt wird */
  #define AXIAL_PUFFER_GERUEST 20

 
  /** \def AXIAL_PUFFER_ASO
   * Ein Puffer, der fuer die Berechung des Axialschlittens benoetigt wird */
  #define AXIAL_PUFFER_ASO 10


  /** \def EXCEPTION_WRONG_ARGUMENT_1
   * Fehlercode falls der Methode \link ibf_Schuessel::berechneAlpha \endlink ein
   * falscher Parameter übergeben. Der Wert von 'armseite' war weder 
   * \link RECHTS \endlink noch \link LINKS \endlink*/
  #define EXCEPTION_WRONG_ARGUMENT_1 1
  /** \def EXCEPTION_WRONG_ARGUMENT_2
   * Fehlercode falls der Methode 
   * \link ibf_Schuessel::zentrierrollenPositionBerechnen \endlink
   * ein falscher Parameter übergeben. Der Wert von 'oeffnen' war weder
   * \link OEFFNEN \endlink noch \link SCHLIESSEN \endlink */
  #define EXCEPTION_WRONG_ARGUMENT_2 2
  /** \def EXCEPTION_WRONG_ARGUMENT_3
   * Fehlercode fallss der Methode \link ibf_Schuessel::berechneBeta4 \endlink
   * ein falscher Parameter übergeben. Der Wert von 'armseite' war weder 
   * \link RECHTS \endlink noch \link LINKS \endlink. */
  #define EXCEPTION_WRONG_ARGUMENT_3 3
  /** \def EXCEPTION_WRONG_ARGUMENT_4
   * @brief Fehlercode, falls der Methode 
   * \link ibf_Schuessel::berechneBeta1 \endlink ein
   * falscher Parameter übergeben wurde. Der betrachtete Parameter ist
   * 'armseite'. Dieser muss entweder \link RECHTS \endlink oder
   * \link RECHTS \endlink sein. */
  #define EXCEPTION_WRONG_ARGUMENT_4 4
  /** \def EXCEPTION_WRONG_ARGUMENT_5
   * Fehlercode, falls der Methode 
   * \link ibf_Schuessel::zentrierrollenPositionBerechnen \endlink
   * ein falscher Parameter
   * übergeben wurde. Der betrachtete Parameter ist 'armseite'. Dieser muss
   * entweder \link LINKS \endlink oder \link RECHTS \endlink sein */
  #define EXCEPTION_WRONG_ARGUMENT_5 5




  /** \struct Def_IBF_Schuessel
   * Struktur, die Informationen uber die Form der Schuessel enthaelt, so
   * wie den gegenwaertigen Zustand des Schuesselwalzprozesses.*/
  struct Def_IBF_Schuessel{
  
    /** @var ringKlettert
     * @brief Boolean Variable, die genau dann 1 ist, wenn der Ring klettert,
     * oder bereits geklettert ist. */
    int ringKlettert;

    /** @var abbruchRinghoehenDifferenz
     * @brief Die Ringhoehe, ab der der Axialschlitten oben nicht weiter
     * zustellen brauch, um das Klettern zu erzeugen. */
    int abbruchRinghoehenDifferenz;

	/** @var ringDurchmesserKlettern
     * @brief Ringdurchmesser der w�hrend des Kletterns nicht unterschritten werden 
	 * soll */
	int ringDurchmesserKlettern;
    
    /** @var zentrierrollenOffen
     * @brief Genau dann 1 wenn die Zentrierrollen geoeffnet sind */
    int zentrierrollenOffen;

	/** @var endWandhoehe_Schuessel
	 * Wandhoehe der Schuessel, die erreicht werden soll. */
	int endWandhoehe_Schuessel;

  };
  	



  class ibf_Schuessel
  {

      friend class Schuessel_Test;

      public:


        void static Main(
                  struct Def_IBF_Allgemein_IST Ist_IBF,
                  struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                  struct Def_Ist_Inter Ist_Inter,																	    	
                  struct Def_Soll_Inter *Soll_Inter);

  		private:


        static void radialSchlittenAnfahren(
                struct Def_IBF_Allgemein_IST Ist_IBF,
                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                struct Def_Ist_Inter Ist_Inter,
                struct Def_Soll_Inter *Soll_Inter);

        static void axialGeruestAnfahren(
                struct Def_IBF_Allgemein_IST Ist_IBF,
                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                struct Def_Ist_Inter Ist_Inter,
                struct Def_Soll_Inter *Soll_Inter);

        static void axialSchlittenAnfahren(	
								struct Def_IBF_Allgemein_IST Ist_IBF,
								struct Def_IBF_Allgemein_SOLL *Soll_IBF,
								struct Def_Ist_Inter Ist_Inter,
								struct Def_Soll_Inter *Soll_Inter);


    	  static int berechneRingdurchmesser(	
                struct Def_IBF_Allgemein_IST *Ist_IBF,
								struct Def_Ist_Inter Ist_Inter);

    		static void steuerungZentrierrollen( 
                struct Def_IBF_Allgemein_IST Ist_IBF,
                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                struct Def_Ist_Inter Ist_Inter,
                struct Def_Soll_Inter *Soll_Inter);

    		static void zentrierRollenOeffnen(
								struct Def_IBF_Allgemein_IST *Ist_IBF,
                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                struct Def_Ist_Inter Ist_Inter);


    		static void zentrierRollenSchliessen(  
								struct Def_IBF_Allgemein_IST *Ist_IBF,
                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                struct Def_Ist_Inter Ist_Inter);


    		static int zentrierrollenPositionBerechnen(
								struct Def_Ist_Inter Ist_Inter,
                int armseite,
                int offset,
                int oeffnen);

    		static int berechneAlpha(  
								struct Def_Ist_Inter,
                int offset,
                int armseite);

    		static int berechneBeta1(
								struct Def_Ist_Inter Ist_Inter, 
                int armseite);

    		static int berechneBeta2(  
								struct Def_Ist_Inter Ist_Inter,
                int offset,
                int armseite);

    		static int berechneBeta3(
								struct Def_Ist_Inter Ist_Inter,
								int offset,
                int armseite);

    		static int berechneBeta4(
								struct Def_Ist_Inter Ist_Inter,
                int armseite);

    		static int ringKlettert(
							struct Def_IBF_Allgemein_IST *Ist_IBF,
              struct Def_Ist_Inter Ist_Inter);
	
       					      
  };

#endif 
