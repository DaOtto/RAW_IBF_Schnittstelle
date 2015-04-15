#ifndef _ONLI_CNC_S_HPP
   #define _ONLI_CNC_S_HPP

   #include "raw_t_cnc_s.hpp"


   #define S_PUNKT_ONLI_MAX   10.0F
   #define H_PUNKT_ONLI_MAX   10.0F

   #define T1_ONLI_DELTA_S    5.0F
   #define T1_ONLI_DHR        5.0F
   #define T1_ONLI_DELTA_H    5.0F
   #define T1_ONLI_DSA        5.0F

//---------------------------------------------------------------------------
// Struktur Def_Ein_Onli
//---------------------------------------------------------------------------
   struct Def_Ein_Onli
   {

#ifdef WIN32
      struct   Def_Maschine_Achse	rze_achse;	// Zentrierarm Einlaufseite
      struct   Def_Maschine_Achse	rza_achse;	// Zentrierarm Auslaufseite
#endif

      // Automatische Walzkurve für Walzstrategie Ringe und Flansche
      // Walzen bis Aufweiten Ende
      /** @var s_aufweiten_proz
       * @brief Radial Zustellung in [%]*/
      float    s_aufweiten_proz;               // Radiale Zustellung [%]
      /** @var kurv_faktor_aufweiten
       * @brief Kurvenfaktor in [-] */
      float    kurv_faktor_aufweiten;          // Kurvenfaktor       [-]


      // Walzen bis Masse verteilt

      /** @var s_masse_verteilt_proz
       * @brief Verteilte masse in [%]*/
      float    s_masse_verteilt_proz;          // Radiale Zustellung [%]
      /** @var dh_masse_verteilt
       * @brief Axiale Zustellung in [mm]*/
      float    dh_masse_verteilt;              // Axial Zustellung   [mm]
      /** @var kurv_faktor_masse_verteilt
       * @brief Kurvenfaktor in [-] */
      float    kurv_faktor_masse_verteilt;     // Kurvenfaktor       [-]

      // Walzen bis EKV

      /** @var kurv_faktor_walzen
       * @brief Kurvenfaktor in [-]*/
      float    kurv_faktor_walzen;             // Kurvenfaktor       [-] 


      // Automatische Walzkurve für Titanwalzstrategie

      /** @var kurv_faktor_twst
       * @brief Kurvenfaktor [-]*/
      float    kurv_faktor_twst;
      // TODO add doxygen comments
      float    faecherbreite_min_proz;          
      float    faecherbreite_max_proz;
      float    anteil_breitung_wegwalzen_proz;

      // Manuelle Walzekurve
      int      kurv_uebertragen_flag;
      int      stuetz_anz;
      float    h_stuetz[STUETZ_ANZ_MAX];
      float    s_stuetz[STUETZ_ANZ_MAX];

      // Prozessdynamik
      /** @var rwg_max
       * @brief Maximale Ringwachsgeschwindigkeit in [mm/s]*/
      float    rwg_max;				// Maximale Ringwachsgeschwindigkeit [mm/s]
      /** @var rwg_min_endphase
       * @brief Minimale Ringwachsgeschwindigkeit in [mm/s]*/
      float    rwg_min_endphase;		// Minimale Ringwachsgeschwindigkeit [mm/s]
      /** @var rwg_aufweiten
       * @brief Ringwachsgeschwindigkeit beim Aufweiten in [mm/s]*/
      float    rwg_aufweiten;			// Ringwachsgeschwindigkeit Aufweiten [mm/s]
      /** @var rwg_poti_wert
       * @brief Potiwert Ringwachsgeschwindigkeit [0 <-> 2]*/
      float    rwg_poti_wert;			// Potiwert Ringwachsgeschwindigkeit [0<->2]
      /** @var rwg_regelgrenze
       * @brief Maximal moegliche Ringwachsgeschwindikeit in [mm/s]*/
      float    rwg_regelgrenze;			// Maximale möglich Ringwachsgeschwindigkeit [mm/s]

      /** @var deltad_rundier
       * @brief delta Durchmesser fuer Rundierung in [mm]*/
      float    deltad_rundier;                  // delta Durchmesser fuer Rundierung [mm]



      float    d_du_pro_1_mm_rwg;					//
      float    exponent_rwg_endphase;
      float    korrektur_deltad_endphase;       // Standardwert = 1.0;
      float    korrektur_endphase_poti_wert;	// Potiwert Endphase [-1<->1]
      float    rwg_hochfahren_start;
      float    zeit_momente_hochfahren;
      /** @var aufwalzung_check_flag
       * @brief Reguliert die Ringwachgeschwindigkeit, wenn gesetzt.
       * Die Regulierung hat zur Folge, dass der Ringwachsprozess nicht zu kurz ist.*/
      int      aufwalzung_check_flag;


      // Maschinendaten
      /** @var da_walz_max
       * @brief Maximal walzbarer Aussendurchmesserin [mm]*/
      float    da_walz_max;			// Maxi. walzbarer Aussendurchmesser [mm]
      /** @var h_walz_max
       * @brief Maximal walzbare Hoehe in [mm]*/
      float    h_walz_max;			// Maxi. walzbare  Höhe [mm]
      /** @var rs_achse
       * @brief Struktur, die detailierte Informationen ueber die Eingangs- und Resultierende
       * Groessen in Radialer Richtung enthaelt*/
      struct   Def_rad_Achse rs_achse;		// Radialschlitten
      /** @var as_achse
       * @brief Struktur, die detailierte Informationen ueber die Eingangs- und Resultierende
       * Groessen in Axialer Richtung enthaelt */
      struct   Def_axi_Achse as_achse;		// Axialschlitten	

		// Zul. Spannung für Dornwalzenbiegung

      /** @var fr_max_dornwalze_manu_flag
       * @brief Schalter fuer manuell gesetzte maximale Kraft der Dornwalze [0,1]*/
      int      fr_max_dornwalze_manu_flag;
      /** @var fr_max_dornwalze_grenze_flag
       * @brief Schlager fuer Obergrenze der Kraft der Dornwalze [0,1]*/
      int      fr_max_dornwalze_grenze_flag;
      /** @var fr_max_dornwalze_manu
       * @brief Manuell gesetzte maximale Kraft der Dornwalze in [N]*/
      float    fr_max_dornwalze_manu;           // Manuell gesetzte max. Kraft der Dornwalze [N]
      /** @var fr_max_dornwalze_grenze
       * @brief Grenzkraft der Dornwalze in [N]*/
      float    fr_max_dornwalze_grenze;
      /** @var dw_sigma_zul
       * @brief Beigespannung der Dornwalze in [N/mm^2]*/
      float    dw_sigma_zul;
      float    dw_sigma_verh;

      // Kollision
      float    dis_min_ag_dw;
      float    d_dw_pseudo_kolli_ag_dwlager;
      /** @var pos_rs_achse_min
       * @brief min. Position des Radialschlittens aus Lagerkollision*/
      float    pos_rs_achse_min;                // min. Position des Radialschlittens aus Lagerkollisiom
		
      // AG-Position
      int      ws_agmodus;
      float    b_weg_ag_sl;
      /** @var ag_flex_move_exponent
       * @brief Dient zum gleichmaessigen Verschliess der unteren Axialkegelwalze*/
      float    ag_flex_move_exponent;
      /** @var dposag_start_vs
       * @brief Axialgeruestposition bei Walzstart*/
      float    dposag_start_vs;                 // Axialgerüstposition bei Walzenstart
      /** var dposag_ende_vs
       * @brief Axialgeruestposition bei Walzende*/
      float    dposag_ende_vs;                  // Axialgerüstposition bei Walzenende


      // Automatische Ringverlagerung
      int      river_auto_flag;
      float    handrad_korrektur_river_auto;

      // Manuelle Ringverlagerung
      int      river_manu_flag;
      float    alpha_verl_manu_gr;

      // Ringzentrierung
      float    rz_achse_hebelverh;
#ifndef WIN32
      float    rz_f_kommi_nenn;
#endif
      float    rz_f_zul_handrad_korrektur;
      float    rz_f_zul_t1_glaettung_d;
      float    rz_f_zul_t1_glaettung_handrad_klein;
      float    rz_f_zul_t1_glaettung_handrad_gross;

#ifndef WIN32
      int      rz_f_lueften_axial_flag;
      int      rz_f_start_flag;
      int      rz_f_radial_5proz_erkannt;
      int      rz_f_radial_vorform_erreicht;
      int      rz_f_walzen_radial_u_axial;
      int      rz_f_betriebsart;
      int      rz_f_manu_flag;
      int      rz_f_IB_Walzen_radial_u_axial;

   #ifdef SMP16
      //!! Achtung Auflösung und Einheit geändert!
      /** @var rz_f_manu_soll
       * @brief Manuelle Sollzentrierkraft in [kN]*/
      float    rz_f_manu_soll;
      /** @var rz_f_max
       * @brief Druckabhaengige maximal zulaessige Zentrierkraft in [kN]*/
      float    rz_f_max;
      /** @var rz_fz_eilgang
       * @brief zulaessige Zentrierkraft im Eilgang in [kN]*/
      float    rz_fz_eilgang;
      float    rz_f_ist_zen_einl;         // [kN]
      float    rz_f_ist_zen_ausl;         // [kN]
   #else // Modular4
      long     rz_f_manu_soll;
      long     rz_f_max;
      long     rz_fz_eilgang;
      long     rz_f_ist_zen_einl;
      long     rz_f_ist_zen_ausl;
   #endif

#endif

      // Konstanten
      struct	Def_Iterstop  iterstop;

      // Axialprofilwalzen Walztischhoehenverstellung
      double    WT_dis_WP_Beladen; 
      double    WT_dis_WP_Entladen; 
      double    WT_Einlaufseite_dis_WP_Walzen; 
      double    WT_Auslaufseite_dis_WP_Walzen; 

      // Axialprofilwalzen Druckrolle
      double    alpha_ZR_zur_WW_Achse_gr;
      double    dis_x_AW_Sp_theo_bis_AG_Achse_ref;
      double    dis_y_WW_Achse_bis_AG_Achse_ref;
      double    dr_poti_wert;

      // Fliegender Dorn
      double    fr_max_dornwalze_fliegend;       // Maximale Radiale Kraft bei fliegendem Dorn [N]    
      double    dw_d_lager;                      // Lagerdurchmesser Dornwalze [mm]

#ifdef SMP16
      int       AG_Faehrt_Zum_Messzyklus_flag;   // Beim Axialprofilwalzen muss sichergestellt sein,
                                                 // dass die Scheibe zu Beginn des Messzyklus mit
                                                 // Hauptwalze und Druckrollen Kontakt hat.
                                                 // Hierbei werden die in CARWIN eingegeben Werte
                                                 // für die Vorform berücksichtigt.
#endif
      Def_Ibf_actual    Ibf_actual;
    };

//---------------------------------------------------------------------------
// Struktur Def_Aus_Onli
//---------------------------------------------------------------------------
	struct Def_Aus_Onli
	{
      // Fehlerbits 
      struct   Def_Fehler fehler;

      // Schalter
		int		walzspalt_kopplung_flag;

      // Aktueller Stuetzstellen-Index der Walzkurve 
      int      index_stuetz_ziel;
      float    h_ziel;
      float    s_ziel;

		// Sollabnahmen und -vorschuebe
		struct	Def_ds_dh_sp_hp		ds_dh_sp_hp;

		// Minimale Zustellgeschwindigkeiten
		float		s_punkt_min;			
		float		h_punkt_min;

		// Durchmesserwerte in Start- und Endphase
		struct	Def_Endphase			endphase;
		
		// Leistungsgrenzen
		struct	Def_Leistung_max		nutz_leistungsgrenzen;

		float		fr_max_hydraulik;

#ifdef WIN32
      float    fr_max_hydraulik_nenn;

		float    pos_las_sl_u;
		float    dpos_ag_ist;
#endif

		float    pos_ag_soll;
		float    dpos_ag_soll;

		float		fr_max_dornwalze;

		float		fa_max_hydraulik;

#ifdef WIN32
      float    fa_max_hydraulik_nenn;
#endif

		float		fa_max_axialwalze;

		// Soll Kraefte und Momente
		struct	Def_Fr_Fa_Mr_Ma		fr_fa_mr_ma;

      // Reduzierfaktoren
      float    red_fak_fr_of;
      float    red_fak_fa_of;
      float    red_fak_mr_of;
      float    red_fak_ma_of;
      float    red_fak_r_of; 
      float    red_fak_a_of; 
      float    red_fak_r_mf; 
      float    red_fak_a_mf; 

		// Walzphasen
		struct	Def_Walzphase_Onli   walzphase_onli;

		// Daten 1 Ringumdrehung im voraus
		float		du_ref_mess_nru;
      float		du_ref_ring_nru;
		struct	Def_rwg_ds_dh_ufz		rwg_ds_dh_ufz_anpass_nru;
		struct	Def_Form_Mess			form_mess_nru;
      struct   Def_Form				   form_ring_nru;
		float		rr_mw_nru;
   	struct   Def_Radien_Axial		radien_axial_nru;

      // Potiwert
      float    rwg_poti_wert_endphase_start;

      // Ringwachsgeschwindigkeit
      float    rwg_max_zul;

		// Automatische Ringverlagerung
		struct	Def_Verlagerung		verlagerung_auto;

		// Manuelle Ringverlagerung
		struct	Def_Verlagerung		verlagerung_manu;

		// Ringzentrierung
#ifdef WIN32
		float		rz_f_zulaessig_ring;
		float		rz_f_zulaessig_zyl_einzeln;
		float		rz_f_zulaessig_zyl_summe;
#endif

		// Umdrehungszeit
		struct	Def_tu_d_dd_nru		tu_d_dd_nru;

		// Iterationszaehler
		struct	Def_iter_anpass		iter_anpass;

      // Flanschewalzen
      int      abwalzen_bis_masse_verteilt_flag;    
      int      aufwalzen_bis_ekv_flag;
		float		h_aufweiten_ende;             // Höhe, bei Aufweiten ende        [mm]
		float		s_aufweiten_ende;             // Wanddicke, bei Aufweiten ende   [mm]

		float		h_masse_verteilt;             // Flanschhöhe, bei der die Masse verteilt sein soll        [mm]
		float		s_masse_verteilt;             // Flanschwanddicke, bei der die Masse verteilt sein soll   [mm]

      // Titanwalzstrategie
      float    h_twst_start_m;
      float    s_twst_start_m;
      float    s_start_rechts;
      float    h_start_rechts;
      float    s_start_links;
      float    h_start_links;
      float    faecherbreite_max;
      float    faecherbreite_min;

      int      modus_fakq_twst_flag;
      int      radial_walzen_flag;
      int      twst_gestartet_mkr;

      struct   Def_querschnitte_TWST qs_twst;

      float    za_f_zyl_zulaessig_einzeln;
      float    za_f_zyl_zulaessig_summe;
      float    za_f_ring_zulaessig;
      float    za_f_zyl_max_nutz;
      float    za_f_fz_zyl_ist_mw_mf;			 // Ausgabe in kN
      float    za_f_fz_zyl_diff_mf;				 // Ausgabe in kN
      float    za_f_zr_da_kraft_korrektur;
	   float	   za_f_zyl_zulaessig_auto_manu;	 //!! Sollkraft in kN
	   long     Zaehler_check;

#ifndef WIN32
      int      phase;
#endif

      // Axialprofilwalzen  Walztischhoehenverstellung
      double   WT_Beladen_soll_pos;             // Soll Position WT Beladen             [mm]
      double   WT_Entladen_soll_pos;            // Soll Position WT Entladen            [mm]
      double   WT_Einlaufseite_Walzen_soll_pos; // Soll Position WT Walzen Einlaufseite [mm]
      double   WT_Auslaufseite_Walzen_soll_pos; // Soll Position WT Walzen Auslaufseite [mm]

      struct   Def_dxyz dr_auslauf_mp_no_korr;
      struct   Def_dxyz dr_einlauf_mp_no_korr;

      struct   Def_dxyz dr_auslauf_mp;
      struct   Def_dxyz dr_einlauf_mp;

      double   dr_auslauf_pos_zyl_no_korr;
      double   dr_einlauf_pos_zyl_no_korr;

      double   dr_pos_zyl_korr;

      double   dr_auslauf_pos_zyl;
      double   dr_einlauf_pos_zyl;

      double   diff_vol_wp_i;

#ifdef SMP16

      // IBF Sollwerte
      struct   Def_Ibf_nominal Ibf_nominal;

#endif

      double    test1;
      double    test2;
      double    test3;
      double    test4;
      double    test5;
	};

#endif

