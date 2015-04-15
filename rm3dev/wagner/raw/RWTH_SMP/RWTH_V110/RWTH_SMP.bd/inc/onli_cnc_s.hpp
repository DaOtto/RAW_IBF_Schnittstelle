#ifndef _ONLI_CNC_S_HPP
   #define _ONLI_CNC_S_HPP

   #include "raw_t_cnc_s.hpp"


   #define S_PUNKT_ONLI_MAX   10.0F
   #define H_PUNKT_ONLI_MAX   10.0F

   #define T1_ONLI_DELTA_S    5.0F
   #define T1_ONLI_DHR        5.0F
   #define T1_ONLI_DELTA_H    5.0F
   #define T1_ONLI_DSA        5.0F


#if defined BECKHOFF || defined IBF_LINUX || defined SIMUFACT
   #pragma pack(1)
#endif


//---------------------------------------------------------------------------
// Struktur Def_Ein_Onli
//---------------------------------------------------------------------------
   struct Def_Ein_Onli
   {
#if defined(WIN32) && !defined(BECKHOFF)
      struct   Def_Maschine_Achse	rze_achse;	// Zentrierarm Einlaufseite
      struct   Def_Maschine_Achse	rza_achse;	// Zentrierarm Auslaufseite
#endif

      // Automatische Walzkurve fuer Walzstrategie Ringe und Flansche
      // Walzen bis Aufweiten Ende
      float    s_aufweiten_proz;               // Radiale Zustellung [%]
      float    kurv_faktor_aufweiten;          // Kurvenfaktor       [-]

      // Walzen bis Masse verteilt
      float    s_masse_verteilt_proz;          // Radiale Zustellung [%]
      float    dh_masse_verteilt;              // Axial Zustellung   [mm]
      float    kurv_faktor_masse_verteilt;     // Kurvenfaktor       [-]

      // Walzen bis EKV
      float    kurv_faktor_walzen;             // Kurvenfaktor       [-] 

      // Automatische Walzkurve fuer Titanwalzstrategie
      float    kurv_faktor_twst;               // Kurvenfaktor       [-] 
      float    faecherbreite_min_proz;          
      float    faecherbreite_max_proz;
      float    anteil_breitung_wegwalzen_proz;

      // Manuelle Walzekurve
      int      kurv_uebertragen_flag;
      int      stuetz_anz;
      float    h_stuetz[STUETZ_ANZ_MAX];
      float    s_stuetz[STUETZ_ANZ_MAX];
                                             
      // Prozessdynamik
      float    rwg_max;				               // Maximale Ringwachsgeschwindigkeit [mm/s]
      float    rwg_min_endphase;		            // Minimale Ringwachsgeschwindigkeit [mm/s]
      float    rwg_aufweiten;			            // Ringwachsgeschwindigkeit Aufweiten [mm/s]
      float    rwg_poti_wert;			            // Potiwert Ringwachsgeschwindigkeit [0<->2]
      float    rwg_regelgrenze;			         // Maximale moeglich Ringwachsgeschwindigkeit [mm/s]
      float    rwg_aps_bis_vk;                  // Ringwachsgeschwindigkeit bis Vollkontakt [mm/s]
      int      rwg_smooth_flag;                 // Wird von aussen vorgegeben 17.12.2012 Debye Koppers
      float    rwg_faktor_max;                  // Wird von aussen vorgegeben 17.12.2012 Debye Koppers
                                                // Standard 2.0  für Kobe 4.0

      float    deltad_rundier;                  // delta Durchmesser fuer Rundierung [mm]

      float    d_du_pro_1_mm_rwg;					//
      float    exponent_rwg_endphase;
      float    korrektur_deltad_endphase;       // Standardwert = 1.0;
      float    korrektur_endphase_poti_wert;	   // Potiwert Endphase [-1<->1]
      float    rwg_hochfahren_start;
      float    zeit_momente_hochfahren;
      int      aufwalzung_check_flag;

      int      endphase_delta_du_manu_flag;     // Schalter Manuelle Vorgabe der Endphase delta_du  
      float    endphase_delta_du_manu;          // Manuelle Vorgabe der Endphase delta_du

      // Maschinendaten
      float    da_walz_max;			            // Maxi. walzbarer Aussendurchmesser [mm]
      float    h_walz_max;			               // Maxi. walzbare  Hoehe [mm]
      struct   Def_rad_Achse rs_achse;		      // Radialschlitten
      struct   Def_axi_Achse as_achse;		      // Axialschlitten	

		// Zul. Spannung fuer Dornwalzenbiegung
      int      fr_max_dornwalze_manu_flag;      // Schalter fuer manuell gesetzte max. Kraft der Dornwalze [0,1]
      int      fr_max_dornwalze_grenze_flag;    // Schalter fuer Obergrenze Kraft Dornwalze gesetzt [0,1]
      float    fr_max_dornwalze_manu;           // Manuell gesetzte max. Kraft der Dornwalze [N]
      float    fr_max_dornwalze_grenze;         // Grenzkraft Dornwalze [N]
      float    dw_sigma_zul;                    // Biegespannung [N/mm^2]
      float    dw_sigma_verh;

      // Kollision
      float    dis_min_ag_dw;
      float    d_dw_pseudo_kolli_ag_dwlager;
      float    pos_rs_achse_min;                // min. Position des Radialschlittens aus Lagerkollisiom
		
      // AG-Position
      int      ws_agmodus;
      float    b_weg_ag_sl;
      float    ag_flex_move_exponent;
      float    dposag_start_vs;                 // Axialgeruestposition bei Walzenstart
      float    dposag_ende_vs;                  // Axialgeruestposition bei Walzenende


      // Automatische Ringverlagerung
      int      river_auto_flag;
      float    handrad_korrektur_river_auto;

      // Manuelle Ringverlagerung
      int      river_manu_flag;
      float    alpha_verl_manu_gr;

      // Ringzentrierung
      float    rz_achse_hebelverh;
      float    rz_kf_Wert_bezug;
#if defined SMP16 || defined BECKHOFF
      float    rz_f_kommi_nenn;
#endif
      float    rz_f_zul_handrad_korrektur;
      float    rz_f_zul_t1_glaettung_d;
      float    rz_f_zul_t1_glaettung_handrad_klein;
      float    rz_f_zul_t1_glaettung_handrad_gross;

#if defined SMP16 || defined BECKHOFF
      int      rz_f_lueften_axial_flag;
      int      rz_f_start_flag;
      int      rz_f_radial_5proz_erkannt;
      int      rz_f_radial_vorform_erreicht;
      int      rz_f_walzen_radial_u_axial;
      int      rz_f_betriebsart;
      int      rz_f_manu_flag;
      int      rz_f_IB_Walzen_radial_u_axial;
#endif

#if defined SMP16 || defined BECKHOFF
      //!! Achtung Aufloesung und Einheit geaendert!
      float    rz_f_manu_soll;            // [kN] manuelle Sollzentrierkraft
      float    rz_f_max;                  // [kN] druckabhaengige maximal zulaessige Zentrierkraft		
      float    rz_fz_eilgang;             // [kN] zulaessige Zentrierkraft im Eilgang
      float    rz_f_ist_zen_einl;         // [kN]
      float    rz_f_ist_zen_ausl;         // [kN]
#else // Modular4
      long     rz_f_manu_soll;
      long     rz_f_max;
      long     rz_fz_eilgang;
      long     rz_f_ist_zen_einl;
      long     rz_f_ist_zen_ausl;
#endif

      // Konstanten
      struct	Def_Iterstop  iterstop;

      // Axialprofilwalzen Walztischhoehenverstellung
      double    WT_dis_WP_Beladen; 
      double    WT_dis_WP_Entladen; 
      double    WT_Einlaufseite_dis_WP_Walzen; 
      double    WT_Auslaufseite_dis_WP_Walzen; 

      // Axialprofilwalzen Druckrolle
      double    dis_x_AW_Sp_theo_bis_AG_Achse_ref_AS;
      double    dis_x_AW_Sp_theo_bis_AG_Achse_ref_ES;

      double    alpha_ZR_zur_WW_Achse_gr_AS;
      double    alpha_ZR_zur_WW_Achse_gr_ES;

      double    dis_y_WW_Achse_bis_AG_Achse_ref_AS;
      double    dis_y_WW_Achse_bis_AG_Achse_ref_ES;

      double    dis_messanschlag_bis_SP_Achsen_AS;
      double    dis_messanschlag_bis_SP_Achsen_ES;

      double    dr_poti_wert;

      // Fliegender Dorn
      double    fr_max_dornwalze_fliegend;       // Maximale Radiale Kraft bei fliegendem Dorn [N]    
      double    dw_d_lager;                      // Lagerdurchmesser Dornwalze [mm]

#if defined SMP16 || defined BECKHOFF
      int       AG_Faehrt_Zum_Messzyklus_flag;   // Beim Axialprofilwalzen muss sichergestellt sein,
                                                 // dass die Scheibe zu Beginn des Messzyklus mit
                                                 // Hauptwalze und Druckrollen Kontakt hat.
                                                 // Hierbei werden die in CARWIN eingegeben Werte
                                                 // fuer die Vorform beruecksichtigt.
#endif
      Def_Ibf_actual    Ibf_actual;

      // Reserve
      double   river_fag_flag;                  // 0.0 oder 1.0
      double   river_delta_fag_TRE;             // TRE fag_ist_mf - fag_soll (maschdat.ini) N
      double   river_fag_dkorr_dt;              // mm pro Zyklus 

      short    delta_du_bis_aufweiten_start_manu_flag;
      short    delta_du_bis_rwg_max_manu_flag;
      short    delta_du_bis_aufweiten_ende_manu_flag;
      short    sdummy0;
      float    delta_du_bis_aufweiten_start_manu;
      float    delta_du_bis_aufweiten_ende_manu;
      float    delta_du_bis_rwg_max_manu;
      float    sp_soll_cnc; 
      float    sp_ist_cnc; 
      float    hp_soll_cnc; 
      float    hp_ist_cnc; 
      float    fdummy4; 
      float    fdummy5; 
      float    fdummy6; 
      float    fdummy7; 
      float    fdummy8;
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
		struct	Def_Endphase			         endphase;
		
		// Leistungsgrenzen
		struct	Def_Leistung_max		         nutz_leistungsgrenzen;

		float		fr_max_hydraulik;

#if defined(WIN32) && !defined(BECKHOFF)
      float    fr_max_hydraulik_nenn;

		float    pos_las_sl_u;
		float    dpos_ag_ist;
#endif

		float    pos_ag_soll;
		float    dpos_ag_soll;

		float		fr_max_dornwalze;

		float		fa_max_hydraulik;

#if defined(WIN32) && !defined(BECKHOFF)
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
   	struct   Def_Radien_Axial		radien_axial_nru;

      // Potiwert
      float    rwg_poti_wert_endphase_start;

      // Ringwachsgeschwindigkeit
      float    rwg_max_zul;
      float    rwg_max_zul_korr;    // 19.05.2009 Debye 

		// Automatische Ringverlagerung
		struct	Def_Verlagerung		verlagerung_auto;

		// Manuelle Ringverlagerung
		struct	Def_Verlagerung		verlagerung_manu;

		// Ringzentrierung
#if defined(WIN32) && !defined(BECKHOFF)
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
		float		h_aufweiten_ende;             // Hoehe, bei Aufweiten ende        [mm]
		float		s_aufweiten_ende;             // Wanddicke, bei Aufweiten ende   [mm]

		float		h_masse_verteilt;             // Flanschhoehe, bei der die Masse verteilt sein soll        [mm]
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
#if defined IBF_LINUX || defined SIMUFACT
      int32_t  Zaehler_check;
#else
      long     Zaehler_check;
#endif

#if defined SMP16 || defined BECKHOFF
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

      double   Frad_APS;

#if defined SMP16 || defined BECKHOFF

      // IBF Sollwerte
      struct   Def_Ibf_nominal Ibf_nominal;

#endif

      double    test1;
      double    test2;
      double    test3;
      double    test4;
      double    test5;

      // Reserve
      double   verl_soll_auto_in_mm_0_of;
      double   verl_soll_auto_in_mm_fag_dkorr_TRE;
      double   verl_soll_auto_in_mm_fag_korr_TRE_mf;
      double   verl_soll_auto_in_mm_of;
      double   rwg_max_zul_korr_0;
      double   rwg_max_zul_dkorr; 
      double   verl_soll_auto_in_mm_of_TRE;
      double   rwg_faktor_of; 
      double   rwg_faktor_mf; 
      double   dummy9;
	};

//---------------------------------------------------------------------------
// Struktur Def_Ein_Onli_V7
//---------------------------------------------------------------------------
   struct Def_Ein_Onli_V7
   {

#if defined(WIN32) && !defined(BECKHOFF)
      struct   Def_Maschine_Achse	rze_achse;	// Zentrierarm Einlaufseite
      struct   Def_Maschine_Achse	rza_achse;	// Zentrierarm Auslaufseite
#endif

      // Automatische Walzkurve fuer Walzstrategie Ringe und Flansche
      // Walzen bis Aufweiten Ende
      float    s_aufweiten_proz;               // Radiale Zustellung [%]
      float    kurv_faktor_aufweiten;          // Kurvenfaktor       [-]

      // Walzen bis Masse verteilt
      float    s_masse_verteilt_proz;          // Radiale Zustellung [%]
      float    dh_masse_verteilt;              // Axial Zustellung   [mm]
      float    kurv_faktor_masse_verteilt;     // Kurvenfaktor       [-]

      // Walzen bis EKV
      float    kurv_faktor_walzen;             // Kurvenfaktor       [-] 

      // Automatische Walzkurve fuer Titanwalzstrategie
      float    kurv_faktor_twst;               // Kurvenfaktor       [-] 
      float    faecherbreite_min_proz;          
      float    faecherbreite_max_proz;
      float    anteil_breitung_wegwalzen_proz;

      // Manuelle Walzekurve
      int      kurv_uebertragen_flag;
      int      stuetz_anz;
      float    h_stuetz[STUETZ_ANZ_MAX];
      float    s_stuetz[STUETZ_ANZ_MAX];
                                             
      // Prozessdynamik
      float    rwg_max;				               // Maximale Ringwachsgeschwindigkeit [mm/s]
      float    rwg_min_endphase;		            // Minimale Ringwachsgeschwindigkeit [mm/s]
      float    rwg_aufweiten;			            // Ringwachsgeschwindigkeit Aufweiten [mm/s]
      float    rwg_poti_wert;			            // Potiwert Ringwachsgeschwindigkeit [0<->2]
      float    rwg_regelgrenze;			         // Maximale moeglich Ringwachsgeschwindigkeit [mm/s]
      float    rwg_aps_bis_vk;                  // Ringwachsgeschwindigkeit bis Vollkontakt [mm/s]
      int      rwg_smooth_flag;                 // Wird von aussen vorgegeben 17.12.2012 Debye Koppers
      float    rwg_faktor_max;                  // Wird von aussen vorgegeben 17.12.2012 Debye Koppers
                                                // Standard 2.0  für Kobe 4.0

      float    deltad_rundier;                  // delta Durchmesser fuer Rundierung [mm]

      float    d_du_pro_1_mm_rwg;					//
      float    exponent_rwg_endphase;
      float    korrektur_deltad_endphase;       // Standardwert = 1.0;
      float    korrektur_endphase_poti_wert;	   // Potiwert Endphase [-1<->1]
      float    rwg_hochfahren_start;
      float    zeit_momente_hochfahren;
      int      aufwalzung_check_flag;

      int      endphase_delta_du_manu_flag;     // Schalter Manuelle Vorgabe der Endphase delta_du  
      float    endphase_delta_du_manu;          // Manuelle Vorgabe der Endphase delta_du

      // Maschinendaten
      float    da_walz_max;			            // Maxi. walzbarer Aussendurchmesser [mm]
      float    h_walz_max;			               // Maxi. walzbare  Hoehe [mm]
      struct   Def_rad_Achse rs_achse;		      // Radialschlitten
      struct   Def_axi_Achse as_achse;		      // Axialschlitten	

		// Zul. Spannung fuer Dornwalzenbiegung
      int      fr_max_dornwalze_manu_flag;      // Schalter fuer manuell gesetzte max. Kraft der Dornwalze [0,1]
      int      fr_max_dornwalze_grenze_flag;    // Schalter fuer Obergrenze Kraft Dornwalze gesetzt [0,1]
      float    fr_max_dornwalze_manu;           // Manuell gesetzte max. Kraft der Dornwalze [N]
      float    fr_max_dornwalze_grenze;         // Grenzkraft Dornwalze [N]
      float    dw_sigma_zul;                    // Biegespannung [N/mm^2]
      float    dw_sigma_verh;

      // Kollision
      float    dis_min_ag_dw;
      float    d_dw_pseudo_kolli_ag_dwlager;
      float    pos_rs_achse_min;                // min. Position des Radialschlittens aus Lagerkollisiom
		
      // AG-Position
      int      ws_agmodus;
      float    b_weg_ag_sl;
      float    ag_flex_move_exponent;
      float    dposag_start_vs;                 // Axialgeruestposition bei Walzenstart
      float    dposag_ende_vs;                  // Axialgeruestposition bei Walzenende


      // Automatische Ringverlagerung
      int      river_auto_flag;
      float    handrad_korrektur_river_auto;

      // Manuelle Ringverlagerung
      int      river_manu_flag;
      float    alpha_verl_manu_gr;

      // Ringzentrierung
      float    rz_achse_hebelverh;
      float    rz_kf_Wert_bezug;
#if defined SMP16 || defined BECKHOFF
      float    rz_f_kommi_nenn;
#endif
      float    rz_f_zul_handrad_korrektur;
      float    rz_f_zul_t1_glaettung_d;
      float    rz_f_zul_t1_glaettung_handrad_klein;
      float    rz_f_zul_t1_glaettung_handrad_gross;

#if defined SMP16 || defined BECKHOFF
      int      rz_f_lueften_axial_flag;
      int      rz_f_start_flag;
      int      rz_f_radial_5proz_erkannt;
      int      rz_f_radial_vorform_erreicht;
      int      rz_f_walzen_radial_u_axial;
      int      rz_f_betriebsart;
      int      rz_f_manu_flag;
      int      rz_f_IB_Walzen_radial_u_axial;
#endif

#if defined SMP16 || defined BECKHOFF
      //!! Achtung Aufloesung und Einheit geaendert!
      float    rz_f_manu_soll;            // [kN] manuelle Sollzentrierkraft
      float    rz_f_max;                  // [kN] druckabhaengige maximal zulaessige Zentrierkraft		
      float    rz_fz_eilgang;             // [kN] zulaessige Zentrierkraft im Eilgang
      float    rz_f_ist_zen_einl;         // [kN]
      float    rz_f_ist_zen_ausl;         // [kN]
#else // Modular4
      long     rz_f_manu_soll;
      long     rz_f_max;
      long     rz_fz_eilgang;
      long     rz_f_ist_zen_einl;
      long     rz_f_ist_zen_ausl;
#endif

      // Konstanten
      struct	Def_Iterstop  iterstop;

      // Axialprofilwalzen Walztischhoehenverstellung
      double    WT_dis_WP_Beladen; 
      double    WT_dis_WP_Entladen; 
      double    WT_Einlaufseite_dis_WP_Walzen; 
      double    WT_Auslaufseite_dis_WP_Walzen; 

      // Axialprofilwalzen Druckrolle
      double    dis_x_AW_Sp_theo_bis_AG_Achse_ref_AS;
      double    dis_x_AW_Sp_theo_bis_AG_Achse_ref_ES;

      double    alpha_ZR_zur_WW_Achse_gr_AS;
      double    alpha_ZR_zur_WW_Achse_gr_ES;

      double    dis_y_WW_Achse_bis_AG_Achse_ref_AS;
      double    dis_y_WW_Achse_bis_AG_Achse_ref_ES;

      double    dis_messanschlag_bis_SP_Achsen_AS;
      double    dis_messanschlag_bis_SP_Achsen_ES;

      double    dr_poti_wert;

      // Fliegender Dorn
      double    fr_max_dornwalze_fliegend;       // Maximale Radiale Kraft bei fliegendem Dorn [N]    
      double    dw_d_lager;                      // Lagerdurchmesser Dornwalze [mm]

#if defined SMP16 || defined BECKHOFF
      int       AG_Faehrt_Zum_Messzyklus_flag;   // Beim Axialprofilwalzen muss sichergestellt sein,
                                                 // dass die Scheibe zu Beginn des Messzyklus mit
                                                 // Hauptwalze und Druckrollen Kontakt hat.
                                                 // Hierbei werden die in CARWIN eingegeben Werte
                                                 // fuer die Vorform beruecksichtigt.
#endif
      Def_Ibf_actual    Ibf_actual;
    };

//---------------------------------------------------------------------------
// Struktur Def_Aus_Onli_V7
//---------------------------------------------------------------------------
	struct Def_Aus_Onli_V7
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
		struct	Def_Endphase			         endphase;
		
		// Leistungsgrenzen
		struct	Def_Leistung_max		         nutz_leistungsgrenzen;

		float		fr_max_hydraulik;

#if defined(WIN32) && !defined(BECKHOFF)
      float    fr_max_hydraulik_nenn;

		float    pos_las_sl_u;
		float    dpos_ag_ist;
#endif

		float    pos_ag_soll;
		float    dpos_ag_soll;

		float		fr_max_dornwalze;

		float		fa_max_hydraulik;

#if defined(WIN32) && !defined(BECKHOFF)
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
   	struct   Def_Radien_Axial		radien_axial_nru;

      // Potiwert
      float    rwg_poti_wert_endphase_start;

      // Ringwachsgeschwindigkeit
      float    rwg_max_zul;
      float    rwg_max_zul_korr;    // 19.05.2009 Debye 

		// Automatische Ringverlagerung
		struct	Def_Verlagerung		verlagerung_auto;

		// Manuelle Ringverlagerung
		struct	Def_Verlagerung		verlagerung_manu;

		// Ringzentrierung
#if defined(WIN32) && !defined(BECKHOFF)
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
		float		h_aufweiten_ende;             // Hoehe, bei Aufweiten ende        [mm]
		float		s_aufweiten_ende;             // Wanddicke, bei Aufweiten ende   [mm]

		float		h_masse_verteilt;             // Flanschhoehe, bei der die Masse verteilt sein soll        [mm]
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
#ifdef IBF_LINUX
      int32_t  Zaehler_check;
#else
      long     Zaehler_check;
#endif

#if defined SMP16 || defined BECKHOFF
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

      double   Frad_APS;

#if defined SMP16 || defined BECKHOFF

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

