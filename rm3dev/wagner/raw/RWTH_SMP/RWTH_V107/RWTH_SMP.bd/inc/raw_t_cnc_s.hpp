#ifndef _RAW_T_CNC_S_HPP
   #define _RAW_T_CNC_S_HPP

   #include <stdlib.h>

   #include "uftcncs.hpp"

   // Betriebssystem abhängige Setzungen
   #ifdef WIN32
      #define CHAR_ANZ_MAX _MAX_PATH
   #else
      #define Version "V117 Rev. 1"
   #endif

//---------------------------------------------------------------------------
// Setzungen
//---------------------------------------------------------------------------
   // Maximale Anzahl der Stuetzstellen
   #define STUETZ_ANZ_MAX 50

   // Abschaltmodi
   /** \def AB_MOD_AUSSEN
    * @brief Abschlatung auf Aussendurchmesser*/
   #define AB_MOD_AUSSEN 0
   /** \def AB_MOD_MITTE
    * @brief Abschlatung des Mitteldurchmesser*/
   #define AB_MOD_MITTE  1
   /** \def AB_MOD_INNEN
    * @brief Abschaltung auf Innendurchmesser*/
   #define AB_MOD_INNEN  2
   /** \def AB_MOD_FS
    * @brief APW: Abschaltung auf oberen Fliesscheindurchmesser*/
   #define AB_MOD_FS     3

   // Abschaltmodi fuer WS_D_lauf
   /** \def D_LAUF_MOD_AUSSEN
    * @brief Abschaltung auf Aussendurchmesser fuer WS_D_lauf*/
   #define D_LAUF_MOD_AUSSEN 0
   /** \def D_LAUF_MOD_MITTE
    * @brief Abschlatung auf Mitteldurchmesser fuer WS_D_lauf*/
   #define D_LAUF_MOD_MITTE  1
   /** \def D_LAUF_MOD_INNEN
    * @brief Abschaltung auf Innendurchmesser fuer WS_D_lauf*/
   #define D_LAUF_MOD_INNEN  2         // Abschaltung auf Innendurchmesser  fuer WS_D_lauf

   // Walzmodi
   /** \def WALZ_MOD_RING
    * @brief Walsmodus Ringe*/
   #define WALZ_MOD_RING               0
   /** \def WALZ_MOD_FLANSCH
    * @brief Walzmodus der Flansche*/
   #define WALZ_MOD_FLANSCH            1
   /** \def WALZ_MOD_VOLLSCHEIBE
    * @brief Walzmodus Vollscheibe*/
   #define WALZ_MOD_VOLLSCHEIBE        2
   /** \def WALZ_MOD_TWST
    * @brief Walzmodus Titanwalzstrategie*/
   #define WALZ_MOD_TWST               3
  /** \def WALZ_MOD_APS
   * @brief Walzmodus Axialprofilwalzen */
   #define WALZ_MOD_APS                4
   /** \def WALZ_MOD_AAW
    * @brief Walzmodus Axiales Aufweiten*/
   #define WALZ_MOD_AAW                5
 

#ifdef WIN32
   /** \def WALZ_MOD_FLANSCH_ALT
    * @brief Walzmodus Flansche*/
   #define WALZ_MOD_FLANSCH_ALT        7  // Walzmodus Flansche
#endif

   // AG-Modi
   /** \def AG_MOD_FAEHRT
    * @brief fahrendes Axialgeruest*/
   #define AG_MOD_FAEHRT               0
   /** \def AG_MOD_STEHT
    * @brief stehendes Axialgeruest*/
   #define AG_MOD_STEHT                1
   /** \def AG_MOD_KOLLI
    * @brief Axialgeruest in Kollision*/
   #define AG_MOD_KOLLI                2
   /** \def AG_MOD_VS
    * @brief Vollscheibenmodus*/
   #define AG_MOD_VS                   3
   /** \def AG_MOD_AXI_PROF_SCHEIBE
    * @brief Axialprofilwalzen*/
   #define AG_MOD_AXI_PROF_SCHEIBE     4
   /** \def AW-Verschleissminimierend fahrendes Axialgeruest*/
   #define AG_MOD_FLEX                 5
   /** \def T1_VERLAGERUNG
    * @brief Zeitkonstante Ringverlagerung*/
   #define T1_VERLAGERUNG              3.0F
   /** \def T1_VERLAGERUNG_TWST
    * @brief Zeitkonstante Ringverlagerung TWST*/
   #define T1_VERLAGERUNG_TWST        40.0F
   /** \def T1_VERLAGERUNG_VS
    * @brief Zeitkonstante Ringverlagerung VS*/
   #define T1_VERLAGERUNG_VS           1.0F
   /** \def T1_ZR_DA_KRAFT_KORREKTUR
    * @brief Durchmesserkorrektur Zentrierarme*/
   #define T1_ZR_DA_KRAFT_KORREKTUR    0.0F

   #define DW_EINGESPANNT_FA        0   
   #define DW_EINGESPANNT_ESE       1   
   #define DW_EINGESPANNT_BSE       2   
   #define DW_EINGESPANNT_FLIEGEND  3   

   #define FAKQ_MAX          300.0F
   #define MUE_DURCHZIEH_RAD   0.150F
   #define MUE_DURCHZIEH_AXI   0.150F

   // Scheibe/Huelse
   #define HUELSE                0
   #define SCHEIBE               1

   // Leistungsgrenzenregelung
   #define LIMIT_F           1
   #define LIMIT_M           2
   #define LIMIT_DZB         3

   // Grenzen Kurvenfaktoren 
   #define KURV_FAKTOR_AUFWEITEN_MIN         0.0F
   #define KURV_FAKTOR_AUFWEITEN_MAX         3.0F

   #define KURV_FAKTOR_WALZEN_RINGE_MIN      0.3F
   #define KURV_FAKTOR_WALZEN_RINGE_MAX      3.0F

   #define KURV_FAKTOR_WALZEN_FLANSCHE_MIN   KURV_FAKTOR_WALZEN_RINGE_MIN
   #define KURV_FAKTOR_WALZEN_FLANSCHE_MAX   5.0F


   struct Def_R_Form
   {  
	  /** @var s
	   * @brief Ringwanddicke*/
      float s;
      /** @var h
       * @brief Ringhoehe*/
      float h;
      float ra;
      float ri;
      /** @var rm
       * @brief Abstand zwischen Ringachse und Mitte des Walzkragens*/
      float rm;
   };

//---------------------------------------------------------------------------
// Struktur Def_Maschine_Motor
//---------------------------------------------------------------------------
   struct Def_Maschine_Motor
   {
      // Eingangsgrössen
	  /** @var p_nenn
	   * @brief Nennleistung des Motors in [Nmm/s]*/
      float p_nenn;
      /** @var i_nenn
       * @brief Nennstrom des Motors in [A]*/
      float i_nenn;
      /** @var eta_p
       * @brief Elektrischer Wirkungsgrad in [%]*/
      float eta_p;
      /** @var n_nenn
       * @brief Nenndrehzahl des Motors in [1/s]*/
      float n_nenn;
      /** @var n_max
       * @brief Maximale Drehzahl des Motors in [1/s]*/
      float n_max;
      /** @var n_regelreserve_p
       * @brief Regelreserve in [%]*/
      float n_regelreserve_p;
      /** @var ueberlastung_p
       * @brief Moterbelastung in [%]*/
      float ueberlastung_p;
      /** @brief Getriebeuntersetung in [-]*/
      float getriebe_untersetzung;
      
      /** @var n_vari_flag
       * @brief Flag variable Drehzahl in [-]*/
      int   n_vari_flag;


      // resultierende Groessen
      /** @var m_nenn
       * @brief Nennrehmoment des Motors in [Nmm]*/
      float m_nenn;
      /** @var m_eff
       * @brief Effektives Drehmoment in [Nmm]*/
      float m_eff;
      /** @var m_max
       * @brief maximales Drehmoment in [Nmm]*/
      float m_max;                  // Maximales Drehmoment       [Nmm]
   };                

   // Axiale Kraftachse
   struct Def_axi_Achse
   { 
      // Eingangsgrössen
	  /** @var p_system_hoch
	   * @brief Hochdruck in [N/mm²]*/
      float p_system_hoch;
      /** @var p_system_nenn
       * @brief Nenndruck in [N/mm²]*/
      float p_system_nenn;
      /** @var d_kolben
       * @brief Durchmesser Kolbenseite in [mm]*/
      float d_kolben;
      /** @var d_kolbenstange
       * @brief Durchmesser Kolpbenstange in [mµm*/
      float d_kolbenstange;
      /** @var f_regelreserve_p
       * @brief Regelreseve Kraft in [%]*/
      float f_regelreserve_p;
      /** @var f_max_manu
       * @brief wird benutzt, wenn f nicht berechnet werden kann [N]*/
      float f_max_manu;
      /** @var f_kommi_hoch
       * @brief gesetzte kommissionierte Kraft bei Hochdruck in [N]*/
      float f_kommi_hoch;
      /** @var f_kommi_nenn
       * @brief gesetzte kommionierte Kraft bei Nenndruck in [N]*/
      float f_kommi_nenn;


      // Werte für feste Vorgabe der Belastungsbegrenzung
      /** @var anteil_bis_fa_nenn_proz
       * @brief Anteil an Mantellaenge fuer Nennwert der Axialkraft in [%]*/
      float anteil_bis_fa_nenn_proz;
      /** @var anteil_bis_fa_hoch_proz
       * @brief Anteil der Mantellaenge fuer Fa_hoch in [%]*/
      float anteil_bis_fa_hoch_proz;
      /** @var f_reduz_vorne_proz
       * @brief Reduzierte Kraft an AW-Spitze (Proz. von fa_nenn) in [%]*/
      float f_reduz_vorne_proz;


      // Werte für wanddickenabhängige Berechnung der Belastungsbegrenzung
      /** @var dis_grund_bis_lagerung
       * @brief Abstand vom Grunddurchmessr (ohne zyl. Ansatz) bis zur Lagerung in [mm]*/
      float dis_grund_bis_lagerung;
      /** @var durchmesser_welle
       * @brief Durchmesser der Welle (vor Lagerung) in [mm]*/
      float durchmesser_welle;
      /** @var sigma_b_max_zul_welle
       * @brief Zulaessige Biegespannung in [N/mm²] (ehemals N/cm²)*/
      float sigma_b_max_zul_welle;


      /** @var fa_max_begrenzung_neu_flag
       * @brief Neue, variable axiale Kraftbegrenzung (f(sam))*/
      int   fa_max_begrenzung_neu_flag;// Neue, variable axiale Kraftbegrenzung (f(sam))
      /** @var f_max_manu_flag
       * @brief Kraft direkt vorgeben (ohne Berechung mit Systemdruck)*/
      int   f_max_manu_flag;
      /** @var hoch_druck_flag
       * @brief Nenn- oder Hochdruckanwendung*/
      int   hoch_druck_flag;           // Nenn- oder Hochdruckanwendung

      // resultierende Grössen
      /** @var a_kolben
       * @brief Flaeche Kolbenseite in [mm²]*/
      float a_kolben;
      /** @var a_ring
       * @brief Flaeche Ringseite in [mm²]*/
      float a_ring;
      /** @var f_max_nutz_hoch
       * @brief Maximal nutzbare Kraft (Hochdruck, Regelreseve) in [N]*/
      float f_max_nutz_hoch;
      /** @var f_max_nutz_nenn
       * @brief Maximal nutzbare Kraft (Nenndruck, Regelreserve) in [N]*/
      float f_max_nutz_nenn;
   };


   // Radiale Kraftachse
   struct Def_rad_Achse
   { 
      // Eingangsgrössen
	   /** @var p_system_hoch
	    * @brief Hochdruck in [N/mm²]*/
      float p_system_hoch;
      /** @var p_system_nenn
       * @brief Nenndruck in [N/mm²]*/
      float p_system_nenn;
      /** @var d_kolben_o
       * @brief Durchmesser Kolbenseite oben in [mm]*/
      float d_kolben_o;
      /** @var d_kolben_u
       * @brief Durchmesser Kolbenseite unten in [mm]*/
      float d_kolben_u;
      /** @var d_kolbenstange_o
       * @brief Durchmesser Kolbenstange oben*/
      float d_kolbenstange_o;
      /** @var d_kolbenstange_u
       * @brief Durchmesser Kolbenstange unten in [mm]*/
      float d_kolbenstange_u;
      /** @var f_regelreserve_p
       * @brief Regelreserve Kraft in [%]*/
      float f_regelreserve_p;
      /** @var f_max_manu
       * @brief wird benutz, wenn f nicht berechnet werden kann [N]*/
      float f_max_manu;
      /** @var f_kommi_hoch
       * @brief Gesetzte kommissionierte Kraft bei Hochdruck in [N]*/
      float f_kommi_hoch;
      /** @var f_kommi_nenn
       * @brief gesetzte kommissionierte Kraft bei Nenndruck in [N]*/
      float f_kommi_nenn;
      /** @var kraftniveau_ueber_BE
       * @brief Abstand ueber BE falls Zweischenschlittenmaschine gewaehlt*/
      float kraftniveau_ueber_BE;
      /** @var kraftniveau_unter_BE
       * @brief Abstand unter BE falls Zweischlittenmaschine gewaehlt*/
      float kraftniveau_unter_BE;
      /** @var l_dw_unter_BE
       * @brief Laenge der Dornwalze unter BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)*/
      float l_dw_unter_BE;
      /** @var l_dw_ueber_BE
       * @brief Laenge der Dornwalze unter BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)*/
      float l_dw_ueber_BE;

      
                                         // Absenkbares Dornlager
      /** @var l_max_dw_ueber_BE
       * @brief Maximale Laenge der Dornwalze ueber BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)*/
      float l_max_dw_ueber_BE;
      /** @var l_min_dw_ueber_BE
       * @brief Mindest Laenge der Dornwalze ueber BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)*/
      float l_min_dw_ueber_BE;


      /** @var f_max_manu_flag
       * @brief Kraft direkt vorgeben (ohne Berechnung mit Systemdruck)*/
      int   f_max_manu_flag;
      /** @var hoch_druck_flag
       * @brief Nenn- oder Hochdruckanwendung*/
      int   hoch_druck_flag;
      /** @var zwei_radialschlitten_flag
       * @brief Ein- oder Zweischlittenmaschine*/
      int   zwei_radialschlitten_flag;
      /** @var ws_dw_einspannung
       * @brief Schalter fuer Art der Dornwalze-Einspannung (FA, ESE, BSE)*/
      int   ws_dw_einspannung;
      

      // resultierende Grössen
      /** @var a_kolben_o
       * @brief Flaeche Kolbenseite oben in [mm²]*/
      float a_kolben_o;
      /** @var a_kolben_u
       * @brief Flaeche Kolbenseite unten [mm²]*/
      float a_kolben_u;
      /** @var a_ring_o
       * @brief Flaeche Ringeite oben in [mm²]*/
      float a_ring_o;
      /** @var a_ring_u
       * @brief Flaeche der Ringseite unten in [mm²]*/
      float a_ring_u;
      /** @var f_max_nutz_hoch
       * @brief Maximal nutzbare Kraft (Hochdruck, Regelreserve) in [N]*/
      float f_max_nutz_hoch;
      /** @var f_max_nutz_hoch_o
       * @brief Maximal nutzbare Kraft Zyl. oben (Hochdruck, Regelreserve) in [N]*/
      float f_max_nutz_hoch_o;
      /** @var f_max_nutz_hoch_u
       * @brief Maximal nutzbare Kraft Zyl. unten (oder gesamt (1 Schlitten)) (Hochdruck, Regelreserve) in [N]*/
      float f_max_nutz_hoch_u;
      /** @var f_max_nutz_nenn
       * @brief Maximal nutzbare Kraft (Nenndruck, Regelreserve) in [N]*/
      float f_max_nutz_nenn;
      /** @var f_max_nutz_nenn_o
       * @brief Maximal nutzbare Kraft Zyl. oben (Nenndruck, Regelreserve) in [N]*/
      float f_max_nutz_nenn_o;
      /** @var f_max_nutz_nenn_u
       * @brief Maximal nutzbare Kraft Zyl. unten (oder gesamt (1 Schlitten)) (Nenndruck, Regelreserve) in [N]*/
      float f_max_nutz_nenn_u;
      /** @var l_dw_gesamt
       * @brief Gesamte Dornlaenge f(ws_dw_einspannung, l_dw_unter_BE, l_dw_ueber_BE)*/
      float l_dw_gesamt;
   };

   struct Def_Maschine_Achse
   { 
      // Eingangsgrössen
	  /** @var p_system
	   * @brief Systemdruck in [bar]*/
      float p_system;
      /** @var d_kolben
       * @brief Durchmesser Kolbenseite in [mm]*/
      float d_kolben;
      /** @var d_kolbenstange
       * @brief Durchmesser Kolbenstang in [mm]*/
      float d_kolbenstange;
      /** @var f_regelreserve_p
       * @brief Regelreserve Kraft in [%]*/
      float f_regelreserve_p;
      /** @var f_nenn_gesetzt
       * @brief wird benutzt, wenn Kraft nicht brechnet werden kann in [kN]*/
      float f_nenn_gesetzt;

      /** @var f_max_nutz_manu_flag
       * @brief F_max_nutz direkt vorgeben (ohne Berechnung mit Systemdruck)*/
      int   f_max_nutz_manu_flag;


      // resultierende Grössen
      /** @var a_kolben
       * @brief Flaeche Kolbensetie in [cm²]*/
      float a_kolben;
      /** @var a_ring
       * @brief Flaeche Ringseite in [cm²]*/
      float a_ring;
      /** @var f_max_system
       * @brief Maximale Kraft System in [kN]*/
      float f_max_system;
      /** @var f_max_nutz
       * @brief Maximal nutzbare Kraft in [kN]*/
      float f_max_nutz;
   };

   //---------------------------------------------------------------------------
   // Struktur Def_Walzprodukt
   //---------------------------------------------------------------------------
   // TODO doygen comments
   struct Def_Walzprodukt
   {
      float s1r_o;
      float s1r_u;
      float ra_1r_o;
      float ra_1r_u;   
      float dra_1r_ou;
      float ri_1r_o;
      float ri_1r_u;
      float s1a_o;                              
      float s1a_u;                              
      float dra_1a_ou;
      float ra_1a_o;
      float ra_1a_u;
      float ri_1a_o;  
      float ri_1a_u;
   };

   //---------------------------------------------------------------------------
   // Struktur Def_dPos_Dorn_oben
   //---------------------------------------------------------------------------
   struct Def_dPos_Dorn_oben
   {
	   /** @var rwg_rad_soll_o
	    * @brief Soll-Ringwachsgeschwindigkeit oben in [mm/s]*/
      float rwg_rad_soll_o;
      /** @var rwg_rad_soll_u
       * @brief Soll-Ringwachsgeschwindigkeit unten in [mm/s]*/
      float rwg_rad_soll_u;
      /** @var d_rwg_ou_korr
       * @brief Soll-Aenderung der Ringwachsgeschwindigkeit von oben zu unten in [mm/s]*/
      float d_rwg_ou_korr;


      /** @var deltas_soll_o
       * @brief Soll-Abnahme oben in [mm]*/
      float deltas_soll_o;
      /** @var deltas_soll_u
       * @brief Soll-Abnahme untn in [mm]*/
      float deltas_soll_u;
      /** @var d_deltas_ou_soll
       * @brief Soll-Aenderung oben zu unten in [mm]*/
      float d_deltas_ou_soll;


      /** @var dalpha_dreh_ou_soll_bo
       * @brief Soll-Winkelaenderung Dornwalze in [rad]*/
      float dalpha_dreh_ou_soll_bo;
      /** @var winkel_dw_soll_bo
       * @brief Soll-Winkel der Dornwalze in [rad]*/
      float winkel_dw_soll_bo;
      /** @var winkel_dw_ist_bo
       * @brief Ist-Winkel der Dornwalze in [rad]*/
      float winkel_dw_ist_bo;       // Ist Winkel Dornwalze [rad]

      /** @var d_pos_rso_soll_0
       * @brief Soll-Position des oberen Radialschlittens (nicht gecheckt) in [mm]*/
      float d_pos_rso_soll_0;
      /** @var d_pos_rso_soll
       * @brief Soll-Position des oberen Radialschlittens in [mm]*/
      float d_pos_rso_soll;
      /** @var d_pos_rso_ist
       * @brief Ist-Dornneigung in [mm]*/
      float d_pos_rso_ist;

      /** @var dis_drehpunkte_dw_vert
       * @brief Vertikaler Abstand Drehpunkt oben bis unten in [mm]*/
      float dis_drehpunkte_dw_vert;

      /** @var v_hw_mw
       * @brief Walzengeschwindigkeit in [mm/s]*/
      float v_hw_mw;
      /** @var v_rso_soll
       * @brief Soll-Geschwindigkeit des Radialschlittens oben in [mm/s]*/
      float v_rso_soll;
      /** @var t_korr
       * @brief Korrekturzeit in [s]*/
      float t_korr;
   };

//---------------------------------------------------------------------------
// Struktur Def_fumo
//---------------------------------------------------------------------------
   struct Def_fumo
   {
      float u;   // unten
      float m;   // Mitte
      float o;   // oben
   };

//---------------------------------------------------------------------------
// Struktur Def_fumoM
//---------------------------------------------------------------------------
   struct Def_fumomw
   {
      float u;   // unten
      float m;   // Mitte
      float o;   // oben
      float mw;  // Mittelwert
   };

//---------------------------------------------------------------------------
// Struktur Def_Mess_Ebene
//---------------------------------------------------------------------------
   // TODO comments for doxygen
   struct Def_Mess_Ebene
   {
      // Laser unten
      float y_pos_Laser_u;

      // Laser oben
      float y_pos_Laser_o;

      // Hauptwalze
      float du_HW_Laser_u;

      // Dornwalze
      float du_DW_Laser_u;
   };

//---------------------------------------------------------------------------
// Struktur Def_WP_Mess_Ebene
//---------------------------------------------------------------------------
   // TODO comments for doxygen
   struct Def_WP_Mess_Ebene
   {
      // Laser unten
      float pos_Laser_osp_u;

      // Laser oben
      float pos_Laser_osp_o;

      // Axialgeruest
      float pos_AG_osp;
   };

//---------------------------------------------------------------------------
// Struktur Def_h_3Segm
//---------------------------------------------------------------------------
   // TODO comments for doxygen
   struct Def_h_3Segm
   {
      int    segment_nr;
      struct Def_fumo h_Segm_umo;
      struct Def_fumo h_Segm_fak_umo;
   };

//---------------------------------------------------------------------------
// Struktur Def_querschnitte_TWST: 
//---------------------------------------------------------------------------
   // TODO comments for doxygen
   struct   Def_querschnitte_TWST
   {
      float h_m_bei_s_ist;
      float s_m_bei_h_ist;
   
      float h_l_bei_s_ist;
      float s_l_bei_h_ist;
   
      float h_r_bei_s_ist;
      float s_r_bei_h_ist;

      float h_l_bei_s_m;
      float h_r_bei_s_m;
   };

//---------------------------------------------------------------------------
// Struktur Def_Form_Mess: Definition der gemessen Groessen
//---------------------------------------------------------------------------
   struct Def_Form_Mess
   {
	  /** @var da
	   * @brief Aussendruchmesser in [mm]*/
      float da;
      /** @var dm
       * @brief Mittlerer Durchmesser in [mm]*/
      float dm;
      /** @var di
       * @brief Innendurchmesser in [mm]*/
      float di;
      /** @var dis_hw_dw
       * @brief Abstand zwischen Hauptwalze - Dornwalze in [mm]*/
      float dis_hw_dw;
      /** @var dis_aw
       * @brief Abstand zwischen den Axialwalzen [mm]*/
      float dis_aw;

      /** @var dFSWP
       * @brief APW: Durchmesser Fliesscheide in [mm]*/
      double dFSWP;        // APW: Durchm Fliessscheide                 [mm]    
      struct Def_APW_Halbe_Form Halbe_Form_o;      
      struct Def_APW_Halbe_Form Halbe_Form_u;      
   };

//---------------------------------------------------------------------------
// Struktur Def_Dim_EKV
//---------------------------------------------------------------------------
   struct Def_Dim_EKV   // EKV -> Endpunkt Kombinierte Verwalzung
   {
	  /** @var du_ekv
	   * @brief laufender Durchmesser bei EKV in [mm]*/
      float du_ekv;
      /** @var da_ekv
       * @brief Aussendruchmesser bei EKV in [mm]*/
      float da_ekv;
      /** @var dm_ekv
       * @brief mittlerer Druchmesser bei EKV in [mm]*/
      float dm_ekv;
      /** @var di_ekv
       * @brief Innenduchmesser bei EKV*/
      float di_ekv;
      /** @var h_ekv
       * @brief Ringhoehe bei EKV in [mm]*/
      float h_ekv;
      /** @var s_ekv
       * @brief Wanddicke bei EKV in [mm]*/
      float s_ekv;
   };

//---------------------------------------------------------------------------
// Struktur Def_Walzen_Geo
//---------------------------------------------------------------------------
   struct Def_Walzen_Geo
   {
      // Eingabegroessen
	   /** @var glatt_flag
	    * @brief Gibt Aussage darueber, ob die Walze glatt(1) ist oder nicht (0)*/
      int glatt_flag;

      /** @var d_nenn
       * @brief Nennduchmesser der Walze in [mm]*/
      float d_nenn;
      /** @var d_min
       * @brief minmaler Durchmesser der Walze in [mm]*/
      float d_min;
      /** @var h_ges
       * @brief Hoehe der gesamten Walze in [mm]*/
      float h_ges;
      /** @var h_kaliber
       * @brief Hoehe Kaliber in [mm]*/
      float h_kaliber;
      /** @var t_kaliber
       * @brief Tiefe der Kaliber in [mm]*/
      float t_kaliber;
      /** @var h_lippe
       * @brief Hoehe der Lippe in [mm]*/
      float h_lippe;
      /** @var t_lippe
       * @brief Laenge der Lippe in [mm]*/
      float t_lippe;
      /** @var d_lager
       * @brief Lagerduchmesser bei Zentrierrollen und Hauptwalzen, bei Dornwalze ohne Bedeutung in [mm]*/
      float d_lager;
      
      // TODO Doxygen comments
      // Dummys,um Platz in der Struktur zu reservieren
      float du_max_profil;
      float du_max_gesamt;
#ifdef WIN32   // MSVC++ 6.0      
      float dummy_3;
      float dummy_4;
      float dummy_5;
      int   dummy_6;
      int   dummy_7;
      int   dummy_8;
      int   dummy_9;
      int   dummy_10;
      char   werkzeug_name[CHAR_ANZ_MAX];
#endif
   
      // resultierende Groessen
      /** @var r_nenn
       * @brief Nennradius in [mm]*/
      float r_nenn;
      /** @var r_min
       * @brief minimaler Radius in [mm]*/
      float r_min;
      /** @var r_lager
       * @brief Bedeutung je nach Objekt in [mm]*/
      float r_lager;       //Bedeutung je nach Objekt    [mm]
   };

//---------------------------------------------------------------------------
// Struktur Def_AW_Geo  - Axialwalzengeometrie (oben und unten getrennnt)
//---------------------------------------------------------------------------
   struct Def_AW_Geo
   {
      // Eingabegrössen
	   /** @var delta_w_konstr_gr
	    * @brief Delta Winkgel oben in [°]*/
      float delta_w_konstr_gr;
      /** @var l_fehlende_spitze
       * @brief Laenge der fehlenden Spitze in [mm]*/
      float l_fehlende_spitze;
      /** @var l_nutz
       * @brief Nutzbare Mangellaenge in [mm]
       * @brief Theorethische Mantellaenge - Laenge fehlende Spitze*/
      float l_nutz;

      /** @var l_zyl_ansatz
       * @brief Laenge des zylindrischen Ansatz [mm]*/
      float l_zyl_ansatz;
      /** @var winkel_gr
       * @brief Oeffnungswinkel der unteren Axialwalze in [°]*/
      float winkel_gr;


      // resultierende Grössen
      /** @var delta_w_konstr_bo
       * @brief Delta Winkel oben (Bogenmass) in [bog]*/
      float delta_w_konstr_bo;
      /** @var du_grund
       * @brief Grunddurchmesser in [mm]*/
      float du_grund;
      /** @var du_spitze
       * @brief Durchmesser Spitze [mm]*/
      float du_spitze;
      /** @var l_mantel_theo
       * @brief Theoretische Mantellaenge in [mm]*/
      float l_mantel_theo;
      /** @var winkel_bo
       * @brief Oeffnungswinkel der Axialwalze in [bog]*/
      float winkel_bo;

      /** @var achsenlaenge_l_fehlende_spitze
       * @brief Laenge der fehlenden Spitze bezogen auf Achse in [mm]*/
      float achsenlaenge_l_fehlende_spitze;
      /** @var achsenlaenge_l_nutz
       * @brief Nutzbare laenger bezogen auf Achse in [mm]*/
      float achsenlaenge_l_nutz;


#ifdef WIN32   // MSVC++ 6.0      
      char werkzeug_name[CHAR_ANZ_MAX];
#endif

   };

//---------------------------------------------------------------------------
// Struktur Def_Schlupf 
//---------------------------------------------------------------------------
   struct Def_Schlupf
   {
	   /** @var b_weg_ag
	    * @brief Beschleunigungsweg Axialgeruest in [mm]*/
      float b_weg_ag;
      /** @var dis_sl
       * @brief Schlupfstand der Messeinr bezogen auf Axialwalz-Kante hinten in [mm]*/
      float dis_sl;
      /** @var pos_laser_osp
       * @brief Schlupfposition des Lasers ohne Spitze in [mm]*/
      float pos_laser_osp;
      /** @var pos_laser_msp
       * @brief Schlupfposition des Lasers ohne Spitze in [mm]*/
      float pos_laser_msp;

   };

//---------------------------------------------------------------------------
// Struktur Def_Walzphase
//---------------------------------------------------------------------------
   // TODO Doxygen Comments
   struct   Def_Walzphase
   {
      int   aw_kontakt_flag;
      int   aw_teil_ueberdeckt_flag;
      int   aw_voll_ueberdeckt_flag;
      int   aw_vorformhoehe_erreicht_flag;
      int   aw_auto_gelueftet_flag;
      int   aw_manu_gelueftet_flag;
      int   aw_gelueftet_flag;
      int   ekv_erreicht_flag;
      int   fh_erreicht_flag;
      int   fa_erkannt_flag;      
      int   fr_erkannt_flag;
      int   hw_motor_hochgelaufen_flag;
      int   schlupfwalzen_flag;
      int   sw_erreicht_flag;
      int   um_ekv_10proz_flag;
      int   um_ekv_33proz_flag;
#ifdef WIN32
      int   di_vorhanden_flag;
#endif
   };

//---------------------------------------------------------------------------
// Struktur Def_Ufz_Rad
//---------------------------------------------------------------------------
   //TODO Doxygen Comments
   struct   Def_Ufz_Rad
   {
      float adr;
      float br;
      float cr;
      float delta_s;
      float dhr_mw;        // Mittelwert Breitung [mm] 
      float dhr_max;       // Maximale Breitung   [mm] 
      float epsilon_s;
      float eqr;
      float h0r;
      float h1r;
      float hrm;
      float lr;
      float phi_s;         // Umformgrad                 [-]
      float phi_qr;        // Umformgrad bezogen auf Querschnittsabnahme [-]
      float s0r;
      float s1r;
   };

//---------------------------------------------------------------------------
// Struktur Def_Ufz_Axi
//---------------------------------------------------------------------------
   struct   Def_Ufz_Axi
   {
	  /** @var ada
	   * @brief Gedreuckte Flaeche in [mm]*/
      float ada;
      /** @var ba
       * @brief Breitungsfaktor in [-]*/
      float ba;
      /** @var ca
       * @brief Walzspaltverhaeltnis in [-]*/
      float ca;
      /** @var delta_h
       * @brief Abnahme Hoehe in [mm]*/
      float delta_h;
      /** @var dsa_mw
       * @brief Mittelwert Breitung in [mm]*/
      float dsa_mw;
      /** @var dsa_max
       * @brief Maximale Breitung in [mm]*/
      float dsa_max;
      /** @var epsilon_h
       * @brief Bezogene Hoehenabnahme in [-]*/
      float epsilon_h;
      /** @var eqa
       * @brief Querschnittsabnahme axial in [-]*/
      float eqa;
      /** @var h0a
       * @brief Einlaufende Hoehe axial in [mm]*/
      float h0a;
      /** @var h1a
       * @brief Auslaufende Hoehe axial in [mm]*/
      float h1a;
      /** @var sam
       * @brief Mittlere Wand axial in [mm]*/
      float sam;
      /** @var la
       * @brief Gedrueckte Laenge in [mm]*/
      float la;
      /** @var phi_h
       * @brief Umformgrad in [-]*/
      float phi_h;
      /** @var phi_qa
       * @brief Umformgrad bezogen auf Queschnittsabnahme in [-]*/
      float phi_qa;
      /** @var s0a
       * @brief Einlaufende Wand axial in [mm]*/
      float s0a;
      /** @var s1a
       * @brief Auslaufende Wand axial in [mm]*/
      float s1a;

   };

//---------------------------------------------------------------------------
// Struktur Def_lueften_as
//---------------------------------------------------------------------------
   struct   Def_lueften_as
   {
      float deltad_lf;
      float dh_lf;
      float du_lf;
   };

//---------------------------------------------------------------------------
// Struktur Def_du_HW_DW_3Segm
//---------------------------------------------------------------------------
   struct   Def_du_HW_DW_3Segm
   {
      struct   Def_fumomw du_HW_werte;
      struct   Def_fumomw du_DW_werte;

      float    dr_HW_ou;
      float    dr_HW_mu;
      float    dr_DW_ou;
      float    dr_DW_mu;
   };

//---------------------------------------------------------------------------
// Struktur Def_kw_fr_fa_mr_ma
//---------------------------------------------------------------------------
   struct   Def_kw_fr_fa_mr_ma
   {
      float kw_fa;
      float kw_fr;
      float kw_ma;
      float kw_mr;
   };

//---------------------------------------------------------------------------
// Struktur Def_Radien_Axial
//---------------------------------------------------------------------------
   struct Def_Radien_Axial
   {
      // Oben
	   /** @var ram_o
	    * @brief Radius gedrueckte Laenge oben in [mm]*/
      float ram_o;
      // TODO At Doxygen Comments
      float raa_o;                                                                        
      float rai_o;
      /** @var rawa_o
       * @brief Radius Aussenumfang oben in [mm]*/
      float rawa_o;
      /** @var rawi_o
       * @brief Innenumfang oben in [mm]*/
      float rawi_o;
      /** @var s_aw_kontakt_o
       * @brief Wanddicke Kontaktbreite Axialwalze-Ring oben in [mm]*/
      float s_aw_kontakt_o;
      /** @var s_aw_kontakt_hori_o
       * @brief horizontale Wanddicke Kontaktbreite Axialwalze-Ring oben in [mm]*/
      float s_aw_kontakt_hori_o;
      // TODO At Doxygen Comments
      float kontaktmitte_o; 

      // Unten
      /** @var ram_u
       * @brief Raius gedrueckte Laenge unten in [mm]*/
      float ram_u;
      // TODO At Doxygen Comments
      float raa_u;                                                                        
      float rai_u;
      /** @var rawa_u
       * @brief Radius Aussen unten in [mm]*/
      float rawa_u;
      /** @var rawi_u
       * @brief Radius Innenumfang unten in [mm]*/
      float rawi_u;
      /** @var s_aw_kontakt_u
       * @brief Wanddicke Kontaktbreite Axialwalze-Ring unten [mm]*/
      float s_aw_kontakt_u;
      /** @var s_aw_kontakt_hori_u
       * @brief horizontale Wanddicke Kontaktbreite Axialwalze-Ring unten in [mm]*/
      float s_aw_kontakt_hori_u;
      // TODO At Doxygen Comments
      float kontaktmitte_u;   
   };

//---------------------------------------------------------------------------
// Struktur Def_Iterstop
//---------------------------------------------------------------------------
   // TODO At Doxygen Comments
   struct   Def_Iterstop
   {                   
      float genau_eps_abs;
      float genau_eps_rel;
      float genau_rwg_abs;
      float genau_rwg_rel;

      int   iter_abnahme_max;
      int   iter_rwg_max;
   };

//---------------------------------------------------------------------------
// Struktur Def_Verlagerung
//---------------------------------------------------------------------------
   // TODO At Doxygen Comments
   struct   Def_Verlagerung
   {
		float alpha_dm_bo;
		float alpha_hw_mp_bo;
		float dDa_Messfehler;
		float dv_rel_verl_mm_pro_s_summe;
		float dv_rel_verl_prozess_mm_pro_s;
		float soll;
   };

//---------------------------------------------------------------------------
// Struktur Def_Walzphase_Onli
//---------------------------------------------------------------------------
   // TODO At Doxygen Comments
   struct   Def_Walzphase_Onli
   {
      int   startphase_flag;
      int   hauptphase_flag;
      int   endphase_flag;
      int   aufweiten_ende_flag;

      int   limit_delh;
      int   limit_dels;
      int   limit_fm_max_axial_flag;
      int   limit_fm_max_radial_flag;
      int   limit_rwg_flag;

   };

//---------------------------------------------------------------------------
// Struktur Def_ds_dh_sp_hp
//---------------------------------------------------------------------------
   // TODO At Doxygen Comments
   struct   Def_ds_dh_sp_hp
   {
      float dh_zustellung;
      float ds_zustellung;
      float h_punkt;
      float s_punkt;
   };

//---------------------------------------------------------------------------
// Struktur Def_Endphase
//---------------------------------------------------------------------------
   // TODO At Doxygen Comments
   struct Def_Endphase
   {
      float delta_du;
      float dm;
      float du_ref;
   };

//---------------------------------------------------------------------------
// Struktur Def_iter_anpass
//---------------------------------------------------------------------------
   // TODO At Doxygen Comments
   struct   Def_iter_anpass
   {
      int prozess_am_limit;
      int fmmax_deltah;
      int fmmax_deltas;
      int rwgmax_deltah;
      int rwgmax_deltas;
      int start_end_deltah;
      int start_end_deltas;
   };

//---------------------------------------------------------------------------
// Struktur Def_Leistung_max
//---------------------------------------------------------------------------
   struct Def_Leistung_max
   {
	   /** @var fa_max
	    * @brief maximale Kraft axial in [N]*/
      float fa_max;
      /** @var fr_max
       * @brief maximale Kraft radial in [N]*/
      float fr_max;
      /** @var ma_max
       * @brief maximales Moment axial in [Nm]*/
      float ma_max;
      /** @var ma_nenn
       * @brief axiales Nennmoment in [Nm]*/
      float ma_nenn;
      /** @var mr_max
       * @brief maximales Moment radial in [Nm]*/
      float mr_max;
      /** @var mr_nenn
       * @brief Nennmoment radial in [Nm]*/
      float mr_nenn;
   };

//---------------------------------------------------------------------------
// Struktur Def_rwg_ds_dh
//---------------------------------------------------------------------------
   // TODO At Doxygen Comments
   struct Def_rwg_ds_dh_ufz
   {
      float  deltah_Fmax;
      float  deltah_Mmax;
      float  deltah_DZB;
      float  delta_h_fm_max;
      float  delta_h_fm_max_wst;
      float  dh_wst_bei_ds_fm_max;

      float  deltas_Fmax;
      float  deltas_Mmax;
      float  deltas_DZB;
      float  delta_s_fm_max;
      float  delta_s_fm_max_wst;
      float  ds_wst_bei_dh_fm_max;

      float  fakq0_of;
      float  fakq0_mf;
      float  fakq_out;
      float  fakq_out_kontrolle;

      float  rwg_axi;
      float  rwg_eta;
      float  rwg_fm_max;
      float  rwg_start_endphase;
      float  rwg_ges;
      float  rwg_rad;
      float  rwg_soll_aktu;

      struct Def_Ufz_Axi ufz_axi;
      struct Def_Ufz_Rad ufz_rad;
   };

//---------------------------------------------------------------------------
// Struktur Def_Fr_Fa_Mr_Ma
//---------------------------------------------------------------------------
   // TODO At Doxygen Comment
   struct Def_Fr_Fa_Mr_Ma
   {
      float fa_durch_fa_max;
      float fa_max;
      float fa_walz;
      float fr_durch_fr_max;
      float fr_max;
      float fr_walz;

      float ma_durch_ma_max;
      float ma_max;
      float ma_walz;
      float mr_durch_mr_max;
      float mr_max;
      float mr_walz;
   };

//---------------------------------------------------------------------------
// Struktur Def_n_omega
//---------------------------------------------------------------------------
   struct Def_n_omega
   {
	   /** @var n_aw_motor_g_o
	    * @brief Grunddrehzahl Axialwalze oben in [1/s]*/
      float n_aw_motor_g_o;
      /** @var n_aw_motor_g_u
       * @brief Grunddrehzahl Axialwalze unten in [1/s]*/
      float n_aw_motor_g_u;
      /** @var n_hw_motor
       * @brief Drehzahl der Hauptwalze unten in [1/s]*/
      float n_hw_motor;
      /** @var n_wp_r
       * @brief Drehzahl Ring radial in [1/s]*/
      float n_wp_r;


      /** @var omega_aw_g_o
       * @brief Winkelgeschwindigkeit Axialwalze oben in [1/s]*/
      float omega_aw_g_o;
      /** @var omega_aw_g_u
       * @brief Winkelgeschwindigkeit Axialwalze unten in [1/s]*/
      float omega_aw_g_u;
      /** @var omega_hw
       * @brief Winkelgeschwindigkeit der Hauptwalze in [1/s]*/
      float omega_hw;
      /** @var omega_wp_rad
       * @brief Winkelgeschwindigkeit des Ringes radial in [1/s]*/
      float omega_wp_rad;
      /** @var omega_wp_axi
       * @brief Winkelgeschwindigkeit des Ringes axial in [1/s]*/
      float omega_wp_axi;

      // TODO At Doxygen Comments
      float v_hw_dv0;
      float v_wp_dv0_hw; 
      float v_aw_dv0_u;
      float v_wp_dv0_aw_u;
      float v_aw_dv0_o;
      float v_wp_dv0_aw_o;

      float r_wp_dv0_hw;      // Radius des Ringes an der Hauptwalze mit dv0 = 0 [mm]

      float tu;               // zurückliegende Umlaufzeit [s]
   };

//---------------------------------------------------------------------------
// Struktur Def_tu_d_dd_nru
//---------------------------------------------------------------------------
   struct Def_tu_d_dd_nru
   {
      float tu;
      float durchmesser;
      float delta_durchmesser;
      float rwg_mw;
   };

//---------------------------------------------------------------------------
// Struktur Def_dmp
//---------------------------------------------------------------------------
   struct Def_dmp
   {
	   /** @var axi
	    * @brief mittlere Randachsengeschwindigkeit axial in [mm/s]*/
      float axi;
      /** @var rad
       * @brief mittlere Ringeschwindigkeit radial in [mm/s]*/
      float rad;
      /** @var ges
       * @brief mittlere Ringgeschwindigkeit gesamt in [mm/s]*/
      float ges;
   };

   struct Def_Fehler
   {
      unsigned long cpp_t_m;
      unsigned long uft_t; 
      unsigned long uft_m; 
      unsigned long raw_t1;
      unsigned long raw_t2;
      unsigned long raw_t3;
      unsigned long puff1;
      unsigned long puff2;
      unsigned long onli1;
      unsigned long onli2;
   }; 

//---------------------------------------------------------------------------
// Struktur Def_Ibf_nominal
//---------------------------------------------------------------------------
   struct Def_Ibf_nominal
   {
      // Radialschlitten
	   /** @var RS_act
	    * @brief Flag Sollwerte radial von IBF auswertbar*/
      int   RS_act;
      /** @var RS_mode
       * @brief Betriebsart des Radialschlittens (Vorschub = 0, Kraftregelung = 1)*/
      int   RS_mode;

      /** @var Soll_RS_Pos
       * @brief Sollposition Radialschlitten in [mm]*/
      float Soll_RS_Pos;
      //float Soll_RS_V;    // = aus_onli.ds_dh_sp_hp.s_punkt
      /** @var Soll_FR
       * @brief Soll- bzw. Grenzkraft radial in [N]*/
      float Soll_FR;
     
      // Axialschlitten
      /** @var AS_act
       * @brief Flag Sollwerte axial von IBF auswertbar*/
      int   AS_act;
      /** @var AS_mode
       * @brief Betriebsart des Axialschlittens (Vorschub = 0, Kraftregelung = 1)*/
      int   AS_mode;

      /** @var Soll_AS_Pos
       * @brief Sollposition Axialschlitten in [mmm]*/
      float Soll_AS_Pos;
      //float Soll_AS_V;    // = aus_onli.ds_dh_sp_hp.h_punkt
      /** @var Soll_FA
       * @brief Soll- bzw. Grenzkraft axial in [N]*/
      float Soll_FA;

      // Zentrierung
      /** @var Zen_act
       * @brief Flag Sollwerte Zentrierung von IBF auswertbar*/
      int   Zen_act;
      /** @var Zen_mode
       * Betriebsart der Zentrierrung (Positionsreg. = 0, Verdraengung = 1)*/
      int   Zen_mode;


      /** @var Soll_ZA_Pos
       * @brief Sollposition Zentrierung Auslauf radial in [mm]*/
      float Soll_ZA_Pos;
      /** @var Soll_ZE_Pos
       * @brief Sollposition Zentrierung Einlauf radial in [mm]*/
      float Soll_ZE_Pos;
      /** @var Soll_ZA_V
       * @brief Sollgeschwindigkeit Zentrierung Auslauf radial in [mm/s]*/
      float Soll_ZA_V;
      /** @var Soll_ZE_V
       * @brief Sollgeschwindigkeit Zentrierung Einlauf radial in [mm/s]*/
      float Soll_ZE_V;
      /** @var Soll_FR
       * @brief Soll- bzw. Grenzkraft Zentrierung in [N]*/
      float Soll_FZ;

      /** @var Verlag_ZA
       * @brief Verlagerungsanteil zur radialen Auslaufseite in [mm]*/
      float Verlag_ZA;
      /** @var Verlag_ZE
       * @brief Verlagerungsanteil zur radialen Einlaufseite in [mm]*/
      float Verlag_ZE;
      /** @var Verlag_angle
       * @brief Verlagerungswinkel in [Grad]*/
      float Verlag_angle;


      // Axialgerüst
      /** @var AG_act
       * @brief Flag Sollwerte Axialgeruest von IBF auswertbar*/
      int   AG_act;
      /** @var AG_mode
       * @brief Betriebsart des Axialgeruests (Vorschub = 0, Kraftregelung = 1)*/
      int   AG_mode;


      /** @var Soll_AG_Pos
       * @brief Sollposition Axialgeruest in [mm]*/
      float Soll_AG_Pos;
      /** @var Soll_AG_V
       * @brief Sollgeschwindigkeit Axialgeruest in [mm/s]*/
      float Soll_AG_V;
      /** @var Soll_FAG
       * @brief Soll- bzw Grenzkraft des Axialgeruests in [N]*/
      float Soll_FAG;

   };

//---------------------------------------------------------------------------
// Struktur Def_Ibf_actual
//---------------------------------------------------------------------------
   struct Def_Ibf_actual
   {
	   /** @var Ist_ZEN_A
	    * @brief Messachse (Kolbenhub) Zentrierung Auslauf in [mm]*/
      float Ist_ZEN_A;
      /** @var Ist_ZEN_E
       * @brief Messachse (Kolbenhub) Zentrierung Einlauf in [mm]*/
      float Ist_ZEN_E;
      /** @var Ist_AG
       * @brief Messachse Axialgeruest (HW-Aussen - Spitze AW) in [mm]*/
      float Ist_AG;


      /** @var Ibf_Achse1
       * @brief Messachse IBF 1 in [mm]*/
      float Ibf_Achse1;
      /** @var Ibf_Achse2
       * @brief Messachse IBF 2 in [mm]*/
      float Ibf_Achse2;
      /** @var Ibf_Achse3
       * @brief Messachse IBF 3 in [mm]*/
      float Ibf_Achse3;
      /** @var Ibf_Achse4
       * @brief Messachse IBF 4 in [mm]*/
      float Ibf_Achse4;     //Messachse IBF 4 [mm]
   };
#endif

