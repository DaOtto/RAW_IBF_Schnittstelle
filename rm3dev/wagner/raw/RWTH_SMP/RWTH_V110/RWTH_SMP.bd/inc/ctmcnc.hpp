#ifndef _CTMCNC_HPP
   #define _CTMCNC_HPP

   #include <stdlib.h>
   #include <stdio.h>
   #include <math.h>

   #ifndef _MAX_PATH
      #define _MAX_PATH 1
   #endif

   #ifdef WIN32
      #include <windows.h>
   #endif   

   #include "teso.hpp"
   #include "errorbit.hpp"

   #include "ctmcncs.hpp"

   class CPP_T_EXPORT CPP_T_M_CNC
   {
      public:

      static unsigned long fehler1;

      //---------------------------------------------------------------------------
      // Methode: cot
      // Aufgabe:
      //---------------------------------------------------------------------------
      double cot(double cotangens, int *ok = NULL);

		// Bestimmt das kleinste Element des Feldes 
      int f_min(	int 		panz,
	   		      struct	Def_fxyz	pkoo[],
		   	      struct	Def_fxyz	*xmin);

		int f_min(	int		panz,
                  struct	Def_dxyz	pkoo[],
                  struct	Def_dxyz	*xmin);

      //---------------------------------------------------------------------
      // Methode:	CPP_T_M::Flaeche_Kreis
      // Aufgabe: Flaeche eines Kreises berechnen
      //---------------------------------------------------------------------
      int Flaeche_Kreis(float durchmesser,
					    	   float *flaeche);

      int Flaeche_Kreis(double durchmesser,
					    		double *flaeche);

      int Flaeche_Ring( float  durchmesser_aussen,
                        float  durchmesser_innen,
   							float  *flaeche);

      int Flaeche_Ring( double durchmesser_aussen,
                        double durchmesser_innen,
   							double *flaeche);

      //---------------------------------------------------------------------
      // Methode: CPP_T_M::Gerade_2_Werte
      // Aufgabe:
      //---------------------------------------------------------------------
      int Gerade_2_Werte(  float x1,
                           float y1,
                           float x2,
                           float y2,
                           float x,
                           float *y,
                           int   msg_flag = TRUE);
   
      //---------------------------------------------------------------------------
      // Methode CPP_T_M::p_abstand
      // Aufgabe:
      // Bestimme den Abstand zwischen 2 Punkten
      //---------------------------------------------------------------------------
      int p_abstand(  struct   Def_fxyz x1,
                      struct   Def_fxyz x2,
                      float    *abstand);

      int p_abstand(  struct   Def_dxyz x1,
                      struct   Def_dxyz x2,
                      double   *abstand);

      int p_abstand( float punkt1_x,
				         float punkt1_y,
				         float punkt2_x,
				         float punkt2_y,
				         float *abstand);

      int p_abstand( double punkt1_x,
						   double punkt1_y,
							double punkt2_x,
							double punkt2_y,
							double *abstand);

      int p_abstand( struct	Def_ixy x1,
						   struct	Def_ixy x2,
							int		*abstand);

		//Verschiebt Punkt1 um laenge in Richtung Punkt2
		int p_verschiebe	(	struct Def_fxyz x1,
	 								struct Def_fxyz x2,
	 								float  laenge,
	 								struct Def_fxyz *x3);

		int p_verschiebe	(	struct Def_dxyz x1,
	 								struct Def_dxyz x2,
	 								double laenge,
	 								struct Def_dxyz *x3);

      //---------------------------------------------------------------------
      // Methode: CPP_T_M::Msgbox
      // Aufgabe: Eine Messagebox ausgeben
      //---------------------------------------------------------------------
      int Msgbox( void  *obj, 
                  int   typ,
                  char  text[],
                  char  ueberschrift[],
                  int   bitmap);

      //---------------------------------------------------------------------------
      // Methode: CPP_T_M::nenner_ok
      // Aufgabe: Prueft, ob der Nenner != 0 ist
      //---------------------------------------------------------------------------
      int nenner_ok( float nenner,
                     char  variabel_name[],
                     char  funktions_name[],
                     int   msg_flag = TRUE);

		int nenner_ok	(	double nenner,									
								char	variabel_name[],						
								char  funktions_name[],						
								int	msg_flag = TRUE); 					

		int nenner_ok	(	int	nenner,									
								char	variabel_name[],						
								char	funktions_name[],						
								int	msg_flag = TRUE);						

		int nenner_ok	(	short nenner,									
								char  variabel_name[],						
								char  funktions_name[],						
								int	msg_flag = TRUE);						

      //---------------------------------------------------------------------------
      // Methode CPP_T_M::p_rotieren
      // Aufgabe:
      // Rotation eines Punktes auf einer Kreisbahn            
      //---------------------------------------------------------------------------
      int p_rotieren(struct   Def_fxyz x1,   /* Punkt auf Kreis          */
                     struct   Def_fxyz x2,   /* Mittelpunkt des Kreises  */
                     float    winkel,        /* Drehwinkel (Bogenmass)    */
                     struct   Def_fxyz *x3); /* Neue Koordinate Punkt x1 */

		int p_rotieren(struct 	Def_dxyz x1,	/* Punkt auf Kreis 			 */
							struct 	Def_dxyz x2,	/* Mittelpunkt des Kreises  */
							double	winkel, 			/* Drehwinkel (Bogenmass)    */
							struct 	Def_dxyz *x3);	/* Neue Koordinate Punkt x1 */

		//---------------------------------------------------------------------------
		// Methode CPP_T_M::pruefe_werte
		// Aufgabe:
		//---------------------------------------------------------------------------
		int pruefe_werte(	double *wert,	// zu pruefender Wert
								double min,		// Minimumabfrage
								double max);
		int pruefe_werte(	float *wert, 
								double min, 
								double max);
		int pruefe_werte(	int *wert, 
								int min, 
								int max);

      //---------------------------------------------------------------------------
      // Methode: CPP_T_M::tan_ok
      // Aufgabe: prueft,ob der tan fuer den uebergebenen Wert existiert 
      //            wenn ja -> return FALSE,Standard Bogenmass,wenn bogenmass_flag
      //            == False ->Ueberpruefung in Winkelmass
      //---------------------------------------------------------------------------
      int tan_ok( float argument,
                  char  variabel_name[],
                  char  funktions_name[],
                  int   bogenmass_flag = TRUE,
                  int   msg_flag = TRUE);

		// Bestimmt die Laenge eines Vektors
		int v_betrag	(	struct Def_fxyz vek,
								float  *vekbetrag);

		int v_betrag	(	struct Def_dxyz vek,
								double *vekbetrag);

		// Bestimmt den Einheitsvektor
		int v_einheit	(	struct Def_fxyz vek,
								struct Def_fxyz *vekein);

		int v_einheit	(	struct Def_dxyz vek,
								struct Def_dxyz *vekein);

		// Subtrahiert Vektor2 von Vektor1
		int v_minus	(	struct Def_fxyz vek1,
							struct Def_fxyz vek2,
							struct Def_fxyz *vekdif);


		int v_minus(struct Def_dxyz vek1,
						struct Def_dxyz vek2,
						struct Def_dxyz *vekdif);

      //---------------------------------------------------------------------------
      // Methode: CPP_T_M::Vektor_Initialisieren_Float
      // Aufgabe: Vektor mit Wert vorbelegen
      //---------------------------------------------------------------------------
      int Vektor_Initialisieren_Float(  int   laenge,
                                        float vek[],
                                        float wert);

      //---------------------------------------------------------------------------
      // Methode: CPP_T_M::Vektor_Initialisieren_Int
      // Aufgabe: Vektor mit Wert vorbelegen
      //---------------------------------------------------------------------------
      int Vektor_Initialisieren_Int( int   laenge,
                                     int   vek[],
                                     int   wert);

      //---------------------------------------------------------------------------
      // Methode: CPP_T_M::Vektor_Kopieren_Float
      // Aufgabe: Vektor Kopieren
      //---------------------------------------------------------------------------
      int Vektor_Kopieren_Float( int   laenge,
                                 float vek1[],
                                 float vek2[]);

      //---------------------------------------------------------------------------
      // Methode: CPP_T_M::Vektor_Sortieren_Float
      // Aufgabe:   
      //---------------------------------------------------------------------------
      int Vektor_Sortieren_Float(int   werte_anz,
                                 float werte[3],
                                 int   aufsteigend_flag);

		//---------------------------------------------------------------------------
		// Methode CPP_T_M::Verlauf_mit_exponent
		// Aufgabe:
		//---------------------------------------------------------------------------
      int Verlauf_mit_exponent(   double x_wert,
                                  double x_wert_0,
                                  double x_wert_1,
                                  double y_wert_0,
                                  double y_wert_1,
                                  double exponent,
                                  double *y_wert_mit_exponent,
                                  int	  msg_flag = TRUE);

		int Verlauf_mit_exponent(	float x_wert,
											float x_wert_0,
											float x_wert_1,
											float y_wert_0,
											float y_wert_1,
											float exponent,
                                 float *y_wert_mit_exponent,
											int	msg_flag = TRUE);

      int Verlauf_mit_exponent_alt(   double x_wert,
                                  double x_wert_0,
                                  double x_wert_1,
                                  double y_wert_0,
                                  double y_wert_1,
                                  double exponent,
                                  double *y_wert_mit_exponent,
                                  int	  msg_flag = TRUE);

		int Verlauf_mit_exponent_alt(	float x_wert,
											float x_wert_0,
											float x_wert_1,
											float y_wert_0,
											float y_wert_1,
											float exponent,
                                 float *y_wert_mit_exponent,
											int	msg_flag = TRUE);

      //---------------------------------------------------------------------
      // Methode:	CPP_T_M::Volumen_einer_Kontur
      // Aufgabe:
      //---------------------------------------------------------------------
      int Volumen_einer_Kontur(	int		panz_o,
									      struct	Def_fxyz punkte_o[],
									      int		panz_u,
									      struct	Def_fxyz punkte_u[],
									      struct	Def_Kontur_Volumen *kontur_volumen);

		int Volumen_einer_Kontur	(	int		panz_o,
												struct	Def_dxyz punkte_o[],
												int		panz_u,
												struct	Def_dxyz punkte_u[],
												struct	Def_Kontur_Volumen *kontur_volumen);

      int Volumen_unter_einer_Kurve(	int		panz,
			   									struct	Def_fxyz punkte[],
													float	   y_basis,
													double   *volumen);

      int Volumen_unter_einer_Kurve(	int		panz,
			   									struct	Def_dxyz punkte[],
													double	y_basis,
													double	*volumen);

      //---------------------------------------------------------------------------
      // Methode CPP_T_M::Differenz_groesser_Grenze
      //---------------------------------------------------------------------------
      int Differenz_groesser_Grenze(float    zahl_0,
                                    float    zahl_1,
                                    float    grenze,
                                    int      *genauigkeit_erreicht_flag);

      int Differenz_groesser_Grenze(double   zahl_0,
                                    double   zahl_1,
                                    double   grenze,
                                    int      *genauigkeit_erreicht_flag);

      //---------------------------------------------------------------------------
      // Methode CPP_T_M::Differenz_kleiner_Grenze
      //---------------------------------------------------------------------------
      int Differenz_kleiner_Grenze( float    zahl_0,
                                    float    zahl_1,
                                    float    grenze,
                                    int      *genauigkeit_erreicht_flag);

      int Differenz_kleiner_Grenze( double   zahl_0,
                                    double   zahl_1,
                                    double   grenze,
                                    int      *genauigkeit_erreicht_flag);

      //---------------------------------------------------------------------------
      // Methode CPP_T_M::Weitermachen_flag_aus_itermax_und_genauigkeit
      //---------------------------------------------------------------------------
      int Weitermachen_flag_aus_itermax_und_genauigkeit( float    wert_aktuell,
                                                         float    wert_vorher,
                                                         int      iter,
                                                         int      iter_max,
                                                         float    genauigkeit,
                                                         int      *weitermachen_flag);

      int Weitermachen_flag_aus_itermax_und_genauigkeit( double   wert_aktuell,
                                                         double   wert_vorher,
                                                         int      iter,
                                                         int      iter_max,
                                                         double   genauigkeit,
                                                         int      *weitermachen_flag);

      //---------------------------------------------------------------------------
      // Methode: CPP_T_M::wurzel_ok
      // Aufgabe: Prueft, ob der Radikant >= 0 ist.
      //---------------------------------------------------------------------------
      int wurzel_ok(  double radikant,
                      char   variabel_name[],
                      char   funktions_name[],
                      int    msg_flag = TRUE);

      int wurzel_ok(  float radikant,
                      char  variabel_name[],
                      char  funktions_name[],
                      int   msg_flag = TRUE);

		int wurzel_ok	(	short radikant,								/*die zu pruefende Variable																					*/
								char  variabel_name[],						/*Der Name der Variable (nicht der Wert!) als GwString											*/
								char  funktions_name[],						/*Der Name der aufrufenden Funktion als GwString													*/
								int   msg_flag = TRUE);						/*Optional! Gibt an,ob im Fehlerfall eine Msgbox ausgegeben wird,Default = FALSE			*/

      //---------------------------------------------------------------------------
      // Methode CPP_T_M::w_grbo
      // Aufgabe:                                                                   
      // Winkel von Grad in Bogenmass umrechnen                                   
      //---------------------------------------------------------------------------
      int w_grbo(  float winkelgr,
                   float *winkelbo);

      int w_grbo(  double winkelgr,
                   double *winkelbo);

      float  w_grbo(float  winkelgr);
      double w_grbo(double winkelgr);

		// Rechnet den uebergebenen Winkel vom Bogenmass in Grad um
		// Rueckgabe ueber Parameterleiste 
		int w_bogr	(	float winkelbo,
	 						float *winkelgr);

		int w_bogr	(	double winkelbo,
	 						double *winkelgr);

		// Rechnet den uebergebenen Winkel vom Bogenmass in Grad um.
		// Rueckgabe ueber return
		float		w_bogr	(	float		winkelbo	);
		double	w_bogr	(	double	winkelbo	);

      //---------------------------------------------------------------------------
      // Methode  CPP_T_M::zahlen_gleich
      // Aufgabe: Ueberprueft,ob die beiden uebergebenen Zahlen innerhalb der 
      //          optionalen Toleranz liegen.
      //          Wird nur Zahl1 uebergeben,wird ueberprueft,ob diese == 0 ist.
      //---------------------------------------------------------------------------
		int zahlen_gleich	(	float zahl1,
									float zahl2		= 0.0F,
									float toleranz = (float) EPSILON);

		int zahlen_gleich	(	double zahl1,
									double zahl2	 = 0.0,
									double toleranz = (double) EPSILON);
		
		int zahlen_gleich	(	short zahl1,
									short zahl2		= 0,
									short toleranz = (short) EPSILON);

		int zahlen_gleich	(	int zahl1,
									int zahl2		= 0,
									int toleranz	= (int) EPSILON);

      //--------------------------------------------------------------------------
      // Methode: CPP_T_M::z_max 
      // Aufgabe: Berechne die groesste Zahl
      //--------------------------------------------------------------------------
      float    z_max(   float zahl1,
                        float zahl2);

	  double   z_max(	double	zahl1,
						double	zahl2);

	  short    z_max(	short	zahl1,
						short	zahl2);

	  int     z_max(	int	    zahl1,
						int	    zahl2);

      //--------------------------------------------------------------------------
      // Methode: CPP_T_M::z_min 
      // Aufgabe: Berechne die kleinste Zahl
      //--------------------------------------------------------------------------
	  float		z_min(	float	zahl1,
						float	zahl2);

      double	z_min(	double	zahl1,
						double	zahl2);

	  short    z_min(	short	zahl1,
						short	zahl2);

	  int     z_min(	int	    zahl1,
						int	    zahl2);

      //--------------------------------------------------------------------------
      // Methode: CPP_T_M::z_runden 
      // Aufgabe: Zahl ohne Nachkommastelle runden
      //--------------------------------------------------------------------------
      float	z_runden(float zahl);

      //---------------------------------------------------------------------------
      // Methode: z_min_max_check
      // Aufgabe:
      //---------------------------------------------------------------------------
      int z_min_max_check( short zahl,
                           short z_min,
                           short z_max,
                           short *zahl_back);

      int z_min_max_check( int zahl,
                           int z_min,
                           int z_max,
                           int *zahl_back);

      int z_min_max_check( float zahl,
                           float z_min,
                           float z_max,
                           float *zahl_back);

      int z_min_max_check( double zahl,
                           double z_min,
                           double z_max,
                           double *zahl_back);

   };
#endif

