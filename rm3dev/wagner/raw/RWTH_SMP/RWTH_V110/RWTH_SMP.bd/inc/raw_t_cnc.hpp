#ifndef _RAW_T_CNC_HPP
   #define _RAW_T_CNC_HPP

   #include <math.h>
   #include <stdlib.h>

   #include "teso.hpp"
   #include "ctm.hpp"
   #include "ctp.hpp"
   #include "uft.hpp"
   #include "ufm.hpp"
   #include "raw_t_cnc_s.hpp"
   #include "koppers_filter.hpp"  

   #define DIF_MIN_CNC     0.5F     // Absprache mit K. Brauckmann
   #define DIF_MIN_WIN32   0.05F

   class RAW_T_EXPORT RAW_T_CNC : public UFM_T
   {
      private:
         static float float_dummy;

      public:

      static unsigned long fehler1;
      static unsigned long fehler2;
      static unsigned long fehler3;

      class  KOPPERS_FILTER kpf;

      RAW_T_CNC();
      ~RAW_T_CNC();


      //---------------------------------------------------------------------------
      // Methode: 
      // Aufgabe:
      //---------------------------------------------------------------------------
      struct Def_R_Form RForm_aus_DForm(struct Def_Form dform);


      //---------------------------------------------------------------------------
      // Methode: 
      // Aufgabe:
      //---------------------------------------------------------------------------
      struct Def_R_Form RForm_aus_DForm_Mess(struct Def_Form_Mess dform_mess);


      //---------------------------------------------------------------------
      // Methode:   RWW_T::Abnahme_aus_Durchziehbedingung
      // Aufgabe:
      //---------------------------------------------------------------------
      int Abnahme_aus_Durchziehbedingung( float  mue_ref,
                                          float  radius_wz_ref,
                                          float  *delta_max);

      //---------------------------------------------------------------------
      // Methode: RAW_T::AW_Geometrie_Du_Grund
      // Aufgabe:
      //---------------------------------------------------------------------
      int AW_Geometrie_Du_Grund( float winkel_gr,
                                 float l_mantel_theo,
                                 float *du_grund);

      //---------------------------------------------------------------------
      // Methode: RAW_T::AW_Geometrie_Du_Spitze
      // Aufgabe:
      //---------------------------------------------------------------------
      int AW_Geometrie_Du_Spitze( float winkel_gr,
                                  float l_fehl_spitze,
                                  float *du_spitze);

      //---------------------------------------------------------------------
      // Methode:RWW_T::abnahmen_bestimmung
      // Aufgabe:
      //---------------------------------------------------------------------
      int Filter_mit_Gewichtung( float delta_in,
                                 float delta_in_vorher,
                                 float gewichtung,
                                 float *delta_out);

      //---------------------------------------------------------------------------
      // Methode : RAW_T_CNC::AG_v_soll
      // Aufgabe : Sollgeschwindigkeit Axialgeruest
      //---------------------------------------------------------------------------
      int AG_v_soll_funktion( float dpm_mf,
                              int   schlupfwalzen_flag,
                              int   ag_modus,
                              float *ag_v_soll);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::aufweiten_ende
      // Aufgabe:
      //---------------------------------------------------------------------
      int aufweiten_ende(  float dis_dw_hw_u,
                           float s_aufw_ende,
                           int   walzenstart_flag,   
                           int   *aufweiten_ende_flag);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::aw_hat_auto_gelueftet
      // Aufgabe:   
      //---------------------------------------------------------------------
      int aw_hat_auto_gelueftet( float du_ref,
                                 float du_lf,
                                 int   cnc_flag,
                                 int   walzenstart_flag,
                                 int   *zaehler,
                                 int   *aw_auto_gelueftet_flag);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::aw_hat_kontakt
      // Aufgabe:
      //---------------------------------------------------------------------
      int aw_hat_kontakt(  int   aw_vorformhoehe_erreicht_flag,
                           int   aw_auto_gelueftet_flag,
                           int   aw_manu_gelueftet_flag,
                           int   kraft_axial_erreicht_flag,
                           int   walz_modus,
                           int   cnc_flag,
                           int   *aw_kontakt_flag);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::aw_manu_gelueftet
      // Aufgabe:   
      //---------------------------------------------------------------------
      int aw_hat_manu_gelueftet( int taster_aw_manu_gelueftet,
                                 int *aw_manu_gelueftet_flag);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::aw_hat_vorformhoehe_erreicht
      // Aufgabe:
      //---------------------------------------------------------------------
      int aw_hat_vorformhoehe_erreicht(float dis_aw,
                                       float h_vorform,
                                       int   aw_teil_ueberdeckt_flag,
                                       int   walzenstart_flag,
                                       int   *aw_vorformhoehe_erreicht_flag); // Ein und Aus

      //---------------------------------------------------------------------
      // Methode RAW_T::AW_Ueberdeckung_flag
      // Aufgabe: 
      //---------------------------------------------------------------------
      int AW_Ueberdeckung_flag(  int   walzenstart_flag,
                                 int   walzmodus,
                                 int   aw_ueberdeckung_check_flag,
                                 float da,
                                 float dis_hw_dw_u,
						               float las_pos_u_osp,
					                  int   *aw_teil_ueberdeckung_flag,
						               int   *aw_voll_ueberdeckung_flag);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Berechne_Def_HW_DW_Geo
      // Aufgabe:
      //---------------------------------------------------------------------------
      int Berechne_Def_HW_DW_Geo(struct   Def_Mess_Ebene ME,
                                 struct   Def_Walzen_Geo   *hw_geometrie,      // Hauptwalzengeometrie
                                 struct   Def_Walzen_Geo   *dw_geometrie);   // Dornwalzengeometrie

      //---------------------------------------------------------------------------
      // Methode:   RWW_T::Berechne_Def_Walzen_Geo
      // Aufgabe:
      // Fuer Hauptwalze, Dornwalze und Zentrierollen
      //---------------------------------------------------------------------------
      int Berechne_Def_Walzen_Geo(struct Def_Walzen_Geo *walze);

      //---------------------------------------------------------------------
      // Methode: RWW_T::Berechne_Def_AW_Geo
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Berechne_Def_AW_Geo (  struct  Def_AW_Geo *awo_geometrie,
                                 struct  Def_AW_Geo *awu_geometrie);

      //---------------------------------------------------------------------
      // Methode: RWW_T::Berechne_Def_AW_Geo_oben
      // Aufgabe: Berechne obere Axialwalze aus den Daten der unteren
      //---------------------------------------------------------------------
      int Berechne_Def_AW_Geo_oben( struct Def_AW_Geo awu_geometrie,
                                    struct Def_AW_Geo *awo_geometrie);

      //-------------------------------------------------------------------------------
      // Methode: RWW_T::Berechne_Def_axi_Achse
      // Aufgabe: Struktur Def_Maschine_axiale_Achse
      //-------------------------------------------------------------------------------
      int Berechne_Def_axi_Achse(struct   Def_axi_Achse *axi_achse,
                                 int      *keine_berechnung_moeglich);


      //-------------------------------------------------------------------------------
      // Methode: RWW_T::Berechne_Def_rad_Achse
      // Aufgabe: Struktur Def_Maschine_radiale_Achse
      //-------------------------------------------------------------------------------
      int Berechne_Def_rad_Achse(struct   Def_rad_Achse *rad_achse,
                                 float    h_max_maschine,
                                 int      *keine_berechnung_moeglich,
                                 int      msg_flag);

      //---------------------------------------------------------------------
      // Methode: RWW_T::Berechne_Def_Schlupf
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Berechne_Def_Schlupf(  float   t_kaliber_hw,
                                 struct  Def_AW_Geo      awu_geometrie,
                                 struct  Def_Schlupf     *schlupf_u);

      //---------------------------------------------------------------------
      // Methode:RWW_T::Berechne_Startwerte_TWST
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Berechne_Startwerte_TWST( float s_twst_start,
                                    float h_twst_start,
                                    float s_ekv,
                                    float h_ekv,
                                    float faecherbreite_min_proz,
                                    float faecherbreite_max_proz,
                                    float *s_twst_rechts,
                                    float *h_twst_rechts,
                                    float *s_twst_links,
                                    float *h_twst_links,
                                    float *faecherbreite_max,
                                    float *faecherbreite_min);

#ifdef debye
      //---------------------------------------------------------------------
      // Methode: RWW_T::Breitungsanteil_ba_neu
      // Aufgabe: wegen Otto Fuchs wieder deaktiviert
      //---------------------------------------------------------------------
      int Breitungsanteil_ba_neu(int   mit_breitung_axi_flag,
                                 float la,
                                 float srm,
                                 float ham,
                                 float *breitung);
#endif

      //---------------------------------------------------------------------
      // Methode: RWW_T::Breitungsanteil_ba
      // Aufgabe:
      //---------------------------------------------------------------------
      int Breitungsanteil_ba( int   mit_breitung_axi_flag,
                              float la,
                              float srm,
                              float ham,
                              float *breitung);

      //---------------------------------------------------------------------
      // Methode: RWW_T::Breitungsanteil_br
      // Aufgabe:
      //---------------------------------------------------------------------
      int Breitungsanteil_br( int   mit_breitung_rad_flag,
                              float lr,
                              float srm,
                              float ham,
                              float *breitung);

      //---------------------------------------------------------------------
      // Methode   RWW_T::Da_Rg_u_aus_Da_Mess_u
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Da_Rg_u_aus_Da_Mess_u(  float   Da_Mess_u,
                                        float   s_Luft_Kal_HW_u,
                                        float   *Da_Rg_u);

      //---------------------------------------------------------------------
      // Methode   RWW_T::Da_Rg_o_aus_Da_Rg_u
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Da_Rg_o_aus_Da_Rg_u( float    Da_Rg_u,
                               float    s_Profilabsatz_aussen,
                               float    *Da_Rg_o);

      //---------------------------------------------------------------------------
      // Methode : RAW_T_CNC::dDa_Messfehler_durch_Verlagerung
      // Aufgabe : Bestimme Messfehler Da durch Ringverlagerung
      //---------------------------------------------------------------------------
      int dDa_Messfehler_durch_Verlagerung(float ra_wp_1r_mw,
                                           float verlagerung_mm,
                                           float *dda_messfehler);

      //---------------------------------------------------------------------
      // Methode:	RAW_T_CNC::D_du_pro_1_mm_RWG
      // Aufgabe: 
      //---------------------------------------------------------------------
      int D_du_pro_1_mm_RWG(  struct  Def_Form walzform,
                              float   *d_du_pro_1_mm_rwg,
                              int     msg_flag = TRUE);

      //---------------------------------------------------------------------
      // Methode: RAW_T::Def_Form_nach_Def_Form_Mess
      // Aufgabe:
      //---------------------------------------------------------------------
      int Def_Form_nach_Def_Form_Mess(  struct Def_Form form,
                                        struct Def_Form_Mess *form_mess);

      //---------------------------------------------------------------------
      // Methode: RAW_T::Def_Form_Mess_nach_Def_Form
      // Aufgabe:
      //---------------------------------------------------------------------
      int Def_Form_Mess_nach_Def_Form(  struct Def_Form_Mess form_mess,
                                        struct Def_Form *form);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Delta_D_Zentrierkraft_Zulaessig
      // Aufgabe: Durchmesserkorrektur wegen zulaessiger Zentrierkraft
      //---------------------------------------------------------------------------
      int Delta_D_Zentrierkraft_Zulaessig(float FZ_Zyl_zulaessig_einzeln,  // Zulaessige Summen Zentrierkraft im Zylinder wegen aktueller Ringgeometrie [kN]
                                          float FZ_Zyl_Ist_e_of,           // Ist Zentrierkraft im Zylinder Einlaufseite ungefiltert [kN]
                                          float FZ_Zyl_Ist_a_of,           // Ist Zentrierkraft im Zylinder Auslaufseite ungefiltert [kN]
                                          float Verstaerkung_dD_pro_kN,    // Verstaerkung [mm/kN]
                                          float dt_zyklus,                 // Zykluszeit [s]
                                          float t1_glaettung_FZ_Zyl_Ist,   // Glaettungszeit Ist Zentrierkraft im Zylinder [s]
                                          float t1_glaettung_FZ_Zyl_Diff,  // Glaettungszeit Zentrierkraftdifferenz im Zylinder [s]
                                          int   start_flag,                // Start Schalter Initialsierung Glaettung   [0,1]
                                          float *FZ_Zyl_Ist_MW_mf,         // Ist Mittelwert Summe Zentrierkraft im Zylinder geglaettet [kN]
                                          float *FZ_Zyl_Diff_mf,           // Zentrierkraftdifferenz im Zylinder geglaettet [kN]
                                          float *ZR_da_kraft_korrektur_mf);// Durchmesser Korrektur der Zentrierarme aufgrund der zulaessigen Zentrierkraft [mm]

      //---------------------------------------------------------------------
      // Methode: RWW_T::deltad_endphase_auto
      // Aufgabe:
      //---------------------------------------------------------------------
      int deltad_endphase_auto(  float delta_du_ref_aufwalz,
                                 float dm_walzform,
                                 float rwg_endphase_start,
                                 float rwg_endphase_ende,
                                 float korrektur_deltad_endphase,
                                 float korrektur_endphase_poti_wert,
                                 float v1r,
                                 int   walz_modus,
                                 float *deltad_endphase);

      //---------------------------------------------------------------------
      // Methode:  RAW_T::deltah_bei_Famax
      //---------------------------------------------------------------------
      int deltah_bei_Famax(float Fa_max, 
                           float ra_mw, 
                           float s_AW_kontakt_mw, 
                           float kw_Fa, 
                           float *deltah_Famax);

      //---------------------------------------------------------------------
      // Methode:  RAW_T::deltah_bei_Mamax
      //---------------------------------------------------------------------
      int deltah_bei_Mamax(float Ma_max, 
                           float ra_mw, 
                           float s_AW_kontakt_mw, 
                           float kw_Fa, 
                           float *deltah_Mmax);

      //---------------------------------------------------------------------
      // Methode:RWW_T::deltah_deltas_WST
      // Aufgabe:
      //---------------------------------------------------------------------
      int deltah_deltas_WST(  float    delta_h_wst,
                              float    delta_h_wst_startwert,
                              float    delta_h_wst_zwi_startwert,
                              float    delta_s_wst,
                              float    delta_s_ohne_wst,
                              float    delta_s_wst_startwert,
                              float    delta_s_wst_zwi_startwert,
                              float    fakq,
                              float    ra,
                              float    du_hw_mw,
                              float    du_dw_mw,
                              float    anteil_breitung_wegwalzen_twst,
                              int      fh_erreicht_flag,
                              int      aw_gelueftet_flag,
                              int      aw_kontakt_flag,
                              int      radial_walzen_flag,
                              int      walz_modus,
                              int      modus_fakq_twst_flag,
                              int      mit_breitung_axi_flag,
                              int      mit_breitung_rad_flag,
                              int      f_axial_begrenzung_flag,
                              float    delta_h_wst_obergrenze,
                              float    delta_s_wst_obergrenze,
                              float    genauigkeit_abnahme_abs,
                              float    genauigkeit_abnahme_rel,
                              int      iter_abnahme_max,
                              //int      ws_sw_zuerst_fertig,
                              //int      um_ekv_10proz_flag,
                              struct   Def_R_Form   WP_RForm_m_nru,
                              int      *limit_fm_max_axial_flag,
                              int      *limit_fm_max_radial_flag,
                              int      *iter_delta_h,
                              int      *iter_delta_s,
                              float    *deltah_wst,
                              float    *deltas_wst,
                              float    *deltah_wst_zwi,
                              float    *deltas_wst_zwi,
                              struct   Def_Ufz_Axi *ufz_axi,
                              struct   Def_Ufz_Rad *ufz_rad,
                              int      *zuerst_deltas_wst_flag,
                              int      msg_flag);

      //---------------------------------------------------------------------
      // Methode:RWW_T::deltah_FMDZB_max_Berechnung
      // Stand: neu seit August 2010
      //---------------------------------------------------------------------
      int deltah_FMDZB_max_Berechnung( float    Fa_max, 
                                       float    Ma_max, 
                                       float    kw_fa,  
                                       float    kw_ma,  
                                       float    ra_mw, 
                                       float    s_AW_kontakt,
                                       float    mue_ref,
                                       float    *deltah_Fmax,
                                       float    *deltah_Mmax,
                                       float    *deltah_DZB,
                                       float    *deltah_FMDZB_max);

      //---------------------------------------------------------------------
      // Methode:RWW_T::deltah_FMDZB_max_Berechnung
      // Stand: neu seit August 2010
      //---------------------------------------------------------------------
      int ds_dh_FMDZB_max_mit_Ufz_Berechnung(int      mit_breitung_rad_flag,
                                          int      mit_breitung_axi_flag,
                                          int      walz_modus,
                                          struct   Def_Leistung_max     Leistungsgrenzen,
                                          struct   Def_kw_fr_fa_mr_ma   kw_fr_fa_mr_ma,
                                          struct   Def_R_Form           WP_RForm_mw,
                                          float    ra_mw,
                                          float    du_hw_mw,
                                          float    du_dw_mw,
                                          float    *deltas_Fr_max,
                                          float    *deltas_Mr_max,
                                          float    *deltas_DZB,
                                          float    *deltas_FMDZBmax,
                                          float    *deltah_Fa_max,
                                          float    *deltah_Ma_max,
                                          float    *deltah_DZB,
                                          float    *deltah_FMDZBmax,
                                          struct   Def_Ufz_Rad *ufz_rad,
                                          struct   Def_Ufz_Axi *ufz_axi,
                                          int      msg_flag);


      //---------------------------------------------------------------------
      // Methode:RWW_T::deltah_WST
      // Aufgabe:
      //---------------------------------------------------------------------
      int deltah_WST(float    delta_s_wst,
                     float    delta_h_wst_startwert,
                     float    fakq,
                     float    ra,
                     float    du_hw_mw,
                     float    du_dw_mw,
                     float    anteil_breitung_wegwalzen_twst,
                     int      fh_erreicht_flag,
                     int      aw_gelueftet_flag,
                     int      aw_kontakt_flag,
                     int      walz_modus,
                     int      modus_fakq_twst_flag,
                     int      mit_breitung_axi_flag,
                     int      mit_breitung_rad_flag,
                     float    genauigkeit_abnahme_abs,
                     float    genauigkeit_abnahme_rel,
                     int      iter_max,
                     struct   Def_R_Form WP_RForm_mw,
                     int      *iter_delta_h,
                     float    *delta_h_wst,
                     struct   Def_Ufz_Axi *ufz_axi,
                     struct   Def_Ufz_Rad *ufz_rad,
                     int      msg_flag);

      //---------------------------------------------------------------------
      // Methode: RWW_T::deltah_Walzstrategie
      // Aufgabe:
      //---------------------------------------------------------------------
      int deltah_Walzstrategie(  float delta_s,
                                 float fakq,
                                 float dhr,
                                 float dsa,
                                 float anteil_breitung_wegwalzen_twst,
                                 int   fh_erreicht_flag,
                                 int   aw_gelueftet_flag,
                                 int   aw_kontakt_flag,
                                 int   walz_modus,
                                 int   modus_fakq_twst_flag,
                                 float *delh);

      //---------------------------------------------------------------------------
      // Methode   : RWW_T::dels_aus_RWG_rad
      // Aufgabe   : 
      //---------------------------------------------------------------------------
      int dels_aus_RWG_rad(float RWG_Soll_rad,
                           float v_HW,
                           float Da,
                           float srm,
                           float ham,
                           float du_HW_M,
                           float du_DW_M,
                           int   mit_breitung_axi_flag,
                           int   mit_breitung_rad_flag,
                           float *dels,
                           float *RWG_rad,
                           int   msg_flag);

      //---------------------------------------------------------------------------
      // Methode   : RWW_T::dPos_Dorn_oben_Funktion
      // Aufgabe   : Bestimme Positiion obere Dornverschiebung wegen Dornschraege
      //---------------------------------------------------------------------------
      int dPos_Dorn_oben_Funktion(  float    rwg_mw_ist,            // Mittlere Ist Ringwachsgeschwindigkeit [mm/s]
                                    float    d_pos_rso_ist_0,
                                    float    dda_wp_ou_fehler,
                                    float    n_ru_korr,
                                    float    da_mw,
                                    float    s_wp_1r_mw,
                                    float    hoehe_wp,
                                    float    du_hw_mw,
                                    float    du_dw_mw,
                                    float    i_rad,               // Radiale Getriebeuntersetzung [-]
                                    float    n_hw_motor,            // Motordrehzahl Hauptwalze [1/min]
                                    float    d_pos_rso_max,
                                    float    dis_drehpunkte_dw_vert_0,
                                    float    dis_drehpunkte_dw_vert_max,
                                    float    dis_drehpunkte_dw_vert_min,
                                    int      mit_breitung_axi_flag,
                                    int      mit_breitung_rad_flag,
                                    struct   Def_dPos_Dorn_oben *dpdo,
                                    int      msg_flag);

      //-----------------------------------------------------------------------------------
      // Methode:   RAW_T_CNC::deltah_aus_DZB
      // Neu seit August 2010
      //-----------------------------------------------------------------------------------
      int deltah_aus_DZB(  float mue_ref,
                           float ra_mw_DZB,
                           float *deltah_DZB);

      //-----------------------------------------------------------------------------------
      // Methode:   RAW_T_CNC::deltas_aus_DZB
      // Neu seit August 2010
      //-----------------------------------------------------------------------------------
      int deltas_aus_DZB(  float mue_ref,
                           float du_hw_mw,
                           float du_dw_mw,
                           float *deltas_DZB);
      
      //-----------------------------------------------------------------------------------
      // Methode:   RAW_T_CNC::deltas_bei_Frmax
      // Aufgabe:
      //-----------------------------------------------------------------------------------
      int deltas_bei_Frmax(int      mit_breitung_rad_flag,
                           struct   Def_R_Form WP_RForm_mw,
                           float    Fr_max, 
                           float    du_hw_mw,
                           float    du_dw_mw,
                           float    kw_Fr, 
                           float    *deltas_Frmax,
                           int      msg_flag);

      //-----------------------------------------------------------------------------------
      // Methode:   RAW_T_CNC::deltas_bei_Mrmax
      // Aufgabe:
      //-----------------------------------------------------------------------------------
      int deltas_bei_Mrmax(int      mit_breitung_rad_flag,
                           struct   Def_R_Form WP_RForm_mw,
                           float    Mr_max, 
                           float    du_hw_mw,
                           float    du_dw_mw,
                           float    kw_Mr, 
                           float    *deltas_Mrmax,
                           int      msg_flag);

      //-----------------------------------------------------------------------------------
      // Methode:   RAW_T_CNC::deltas_FMDZB_max_Berechnung
      // Stand: neu seit August 2010
      //-----------------------------------------------------------------------------------
      int deltas_FMDZB_max_Berechnung( int     mit_breitung_rad_flag,
                                       int     walz_modus,
                                       float   fr_max,
                                       float   mr_max,
                                       float   kw_fr,
                                       float   kw_mr,
                                       float   du_HW_mw,
                                       float   du_DW_mw,
                                       struct  Def_R_Form WP_RForm_mw,
                                       float   *deltas_Fr_max,
                                       float   *deltas_Mr_max,
                                       float   *deltas_DZB,
                                       float   *deltas_FMDZB_max,
                                       int     msg_flag);

      //---------------------------------------------------------------------
      // Methode:RWW_T::deltas_WST
      // Aufgabe:
      //---------------------------------------------------------------------
      int deltas_WST(float    delta_h_wst,
                     float    delta_s_ohne_wst,
                     float    delta_s_wst_startwert,
                     float    fakq,
                     float    fakq_anpass_grenze,
                     float    ra,
                     float    du_hw_mw,
                     float    du_dw_mw,
                     float    anteil_breitung_wegwalzen_twst,
                     int      fh_erreicht_flag,
                     int      aw_kontakt_flag,
                     int      radial_walzen_flag,
                     int      walz_modus,
                     int      modus_fakq_twst_flag,
                     int      mit_breitung_axi_flag,
                     int      mit_breitung_rad_flag,
                     float    genauigkeit_abnahme_abs,
                     float    genauigkeit_abnahme_rel,
                     int      iter_max,
                     struct   Def_R_Form WP_RForm_mw,
                     int      *iter_delta_s,
                     float    *delta_s_wst,
                     struct   Def_Ufz_Axi *ufz_axi,
                     struct   Def_Ufz_Rad *ufz_rad,
                     int      msg_flag);

      //---------------------------------------------------------------------
      // Methode:RWW_T::deltas_Walzstrategie
      // Aufgabe:
      //---------------------------------------------------------------------
      int deltas_Walzstrategie(  float delta_h,
                                 float delta_s_owst,
                                 float fakq,
                                 float fakq_anpass_grenze,
                                 float dhr,
                                 float dsa,
                                 float anteil_breitung_wegwalzen_twst,
                                 int   fh_erreicht_flag,
                                 int   aw_kontakt_flag,
                                 int   radial_walzen_flag,
                                 int   walz_modus,
                                 int   modus_fakq_twst_flag,
                                 float *dels);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::dis_HWDW_3Segm
      // Aufgabe:
      //---------------------------------------------------------------------------
      int dis_HWDW_3Segm(  float    pos_RS,
                           struct   Def_fumomw du_HW_werte,
                           struct   Def_fumomw du_DW_werte,
                           struct   Def_fumomw *dis_HWDW_werte);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::dmp_Funktion
      // Aufgabe:
      // Bemerkung: !!!Westphal ueberarbeitet am 24.04.02
      //---------------------------------------------------------------------
      int dmp_Funktion( float    v_hw_dv0,
                        float    da_mw,
                        float    s_wp_1r_mw,
                        float    ham,
                        float    dels,
                        float    delh,
                        float    du_HW_m,
                        float    du_DW_m,
                        float    ra,
                        int      mit_breitung_axi_flag,
                        int      mit_breitung_rad_flag,
                        struct   Def_dmp *dmp,
                        int      msg_flag);

//#ifdef debye_kann_bald_weg
      //---------------------------------------------------------------------
      // Methode:   RAW_T_CNC::dmP_Funktion_neu
      //---------------------------------------------------------------------   
      int dmP_Funktion_neu(  float  v1r_mw, 
                             float  WP_s_mw, 
                             float  WP_h_mw, 
                             float  deltas_mw, 
                             float  deltah_mw, 
                             float  rr_mw, 
                             float  ra_mw,
                             int    mit_breitung_axi_flag,
                             int    mit_breitung_rad_flag, 
                             struct Def_dmp *dmp,
                             float  *eQr,
                             float  *eQa,
                             float  *sym_fak,
                             int    msg_flag);
//#endif

      //---------------------------------------------------------------------
      // Methode:   RWW_T::dmp_rad_Grundgleichung
      // Aufgabe:
      //---------------------------------------------------------------------
      int dmp_rad_Grundgleichung(   float  v1r_mw,
                                    float  ufz_rad_eqr,
                                    float  *dmp_rad);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::dmp_axi_Grundgleichung
      // Aufgabe:
      //---------------------------------------------------------------------
      int dmp_axi_Grundgleichung( float  v1a_mw,
                                  float  ufz_axi_eqa,
                                  float  *dmp_rad);   

      //---------------------------------------------------------------------
      // Methode:   RWW_T::dmp_Grundgleichung
      // Aufgabe:
      //---------------------------------------------------------------------
      int dmp_Grundgleichung( float    ufz_rad_eqr,
                              float    ufz_axi_eqa,
                              float    v1r_mw,
                              float    v1a_mw,
                              struct   Def_dmp *dmp);

      //---------------------------------------------------------------------
      // Methode:RWW_T::Dim_bei_EKV
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Dim_bei_EKV(  struct   Def_Form      walzform,
                        float    deltad_ekv,
                        int      ws_abschalt_modus,
                        int      ws_d_lauf,
                        int      ws_sw_zuerst_fertig,
                        int      walz_modus,
                        struct   Def_Dim_EKV   *dim_ekv,
                        int      msg_flag);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Dornneigung
      // Aufgabe: Bestimme Dornneigung zum Ausgleich eines Durchmesserfehlers
      //---------------------------------------------------------------------------
      int Dornneigung(  float    pos_laser_osp_u,              // Laserposition unten [mm]
                        float    pos_laser_osp_o,              // Laserposition oben  [mm]
                        float    pos_ag_osp,                   // Axialgeruestposition bezug Hauptwalzen Achse [mm]
                        float    pos_rsu,                      // Position Radialschlitten unten (bezug HW-Achse -> DW-Achse)
                        float    hoehe_wp,                     // Hoehe Walzprodukt [mm]
                        float    dDa_me_laser_ou_soll,         // Soll Durchmesser Unterschied Da_o - Da_u        [mm]
                        float    y_pos_laser_u,                // Messhoehe Laser unten (bezug untere Kegelwalze) [mm]
                        float    y_pos_laser_o,                // Messhoehe Laser oben (bezug untere Kegelwalze)  [mm]
                        float    du_hw_laser_u,                // Durchmesser Hauptwalze unten [mm]
                        float    h_kal_hw_u,                   // Hoehe Kaliber Hauptwalze [mm]
                        float    t_kal_hw_u,                   // Tiefe Kaliber Hauptwalze [mm]
                        float    du_dw_laser_u,                // Durchmesser Dornwalze unten [mm]
                        float    h_kal_dw_u,                   // Hoehe Kaliber Dornwalze [mm]
                        float    t_kal_dw_u,                   // Tiefe Kaliber Dornwalze [mm]
                        float    d_pos_rso_ist,                // Ist Abweichung oberer zur unteren Position Radialschlitten [mm]
                        float    rwg_mw_ist,                   // Ist mittlere Ringwachsgeschwindigkeit [mm/s]
                        float    n_ru_korr,                    // Anzahl Ringumdrehungen bis Soll Position erreicht [-]
                        float    n_hw_motor,                   // Soll Drehzahl Hauptwalze [1/min]

                        float    i_rad,                        // Radiale Getriebeuntersetung [-]
                        float    d_pos_rso_max,                // Maximale Abweichung oberer zur unteren Position Radialschlitten [mm]
                        float    dis_drehpunkte_dw_vert,       // Vertikaler Abstand der beiden DW Lagerdrehpunkte [mm]
                        float    dis_drehpunkte_dw_vert_min,   // Minimaler vertikaler Abstand der beiden DW Lagerdrehpunkte [mm]
                        float    dis_drehpunkte_dw_vert_max,   // Maximaler vertikaler Abstand der beiden DW Lagerdrehpunkte [mm]

                        int      mit_breitung_axi_flag, 
                        int      mit_breitung_rad_flag, 

                        struct   Def_dPos_Dorn_oben         *dpos_dorn_oben,
                        int      msg_flag);

      //---------------------------------------------------------------------
      // Methode:RWW_T::dpos_AG_Korr_Werte
      // Aufgabe:
      //---------------------------------------------------------------------
      int dpos_AG_Korr_Werte( int      WS_AGmodus,                                 /*Wahlschalter Axialgeruestmodus            [-]*/
                              float    WP_Achse_Start,                           /*Achse Walzprodukt bei Start               [mm]*/
                              float    pos_RS_Achse_Start,                        /*Position Radialschlitten bei Start      [mm]*/
                              float    dpos_AG_Start_0,                           /*delta Position Axialgeruest Start         [mm]*/
                              float    du_ref,                                    /*laufender Referenzdurchmesser            [mm]*/
                              float    du_ref_Start,                              /*Referenzdurchmesser Start               [mm]*/
                              float    du_ref_Ende,                              /*Referenzdurchmesser Ende                  [mm]*/
                              float    dis_aw,                                    /*mittlere Hoehe                           [mm]*/
                              float    dis_aw_Start,                              /*Hoehe bei Start                           [mm]*/
                              float    h_walzform,                                 /*Hoehe bei Ende                           [mm]*/
                              float    dis_min_AG_DW,                              /*Minimaler Abstand Axialgeruest Dornwalze   [mm]*/
                              float    d_dw_pseudo_kolli_ag_dwlager,
                              struct   Def_Walzen_Geo       dw_geometrie,
                              struct   Def_AW_Geo           awu_geometrie,   
                              float    dpos_AG_VS_Start,                           /*delta Position Axialgeruest Start Vollscheibenmodus   [mm] */
                              float    dpos_AG_VS_Ende,                           /*delta Position Axialgeruest Ende Vollscheibenmodus   [mm] */
                              float    *dpos_AG_Soll,                              /*Rueckgabe,delta Position Axialgeruest      [mm] */
                              float    *pos_AG_Start);

      //---------------------------------------------------------------------
      // Methode:RWW_T::Dh_zustellung_axial
      // Aufgabe:
      //---------------------------------------------------------------------
      int Dh_zustellung_axial(float delta_h,
                              float dhr,
                              float *dh_zu_axi);

      //---------------------------------------------------------------------
      // Methode:RWW_T::Ds_zustellung_radial
      // Aufgabe:
      //---------------------------------------------------------------------
      int Ds_zustellung_radial( float delta_s,
                                float dsa,
                                float *ds_zu_rad);

      //---------------------------------------------------------------------
      // Methode:RWW_T::ds_dh_DP_WST
      // Aufgabe:
      //---------------------------------------------------------------------
      int ds_dh_DP_WST( struct   Def_R_Form        WP_RForm_m,
                        struct   Def_Iterstop      i_stop,
                        struct   Def_Ufz_Rad       ufz_rad_startwerte,
                        struct   Def_Ufz_Axi       ufz_axi_startwerte,
                        float    rwg_max_zul,
                        float    fakq,
                        float    ra,
                        float    du_hw_mw,
                        float    du_dw_mw,
                        float    v1r,
                        float    v1a,
                        float    delta_h_obergrenze,
                        float    delta_s_obergrenze,
                        float    anteil_breitung_wegwalzen_twst,
                        int      fh_erreicht_flag,
                        int      aw_gelueftet_flag,
                        int      aw_kontakt_flag,
                        int      radial_walzen_flag,
                        int      walz_modus,
                        int      modus_fakq_twst_flag,
                        int      mit_breitung_axi_flag,
                        int      mit_breitung_rad_flag,
                        int      f_axial_begrenzung_flag,
                        int      *limit_fm_max_axial_flag,
                        int      *limit_fm_max_radial_flag,
                        int      *iter_zaehl,
                        int      *iter_delta_h,
                        int      *iter_delta_s,
                        struct   Def_rwg_ds_dh_ufz *ds_dh_DP_WST,
                        int      *zuerst_deltas_wst_flag,
                        int      msg_flag);

      //---------------------------------------------------------------------------
      // Methode:RWW_T::ds_dh_zustellung
      // Aufabe: 
      //---------------------------------------------------------------------------
      int ds_dh_zustellung(float delta_h,
                           float delta_s,
                           float dsa,
                           float dhr,
                           float fakq,
                           int   aw_kontakt_flag,
                           int   sw_erreicht_flag,
                           int   radial_walzen_flag,
                           //int   zuerst_deltas_wst_flag,   
                           float *dh_zustellung,
                           float *ds_zustellung);

      //---------------------------------------------------------------------
      // Methode:RWW_T::dsa_Breitung_axial
      // Aufgabe:
      //---------------------------------------------------------------------
      int dsa_Breitung_axial( float delta_h, 
                              float h1a, 
                              float s0a, 
                              float ba, 
                              float *dsa);

      //---------------------------------------------------------------------
      // Methode:RWW_T::dhr_Breitung_radial
      // Aufgabe:
      //---------------------------------------------------------------------
      int dhr_Breitung_radial(float delta_s, 
                              float s1r, 
                              float h0r, 
                              float br, 
                              float *dhr);

      //---------------------------------------------------------------------
      // Methode: RAW_T_CNC::du_DW_fiktiv_Funktion
      //---------------------------------------------------------------------   
      int du_DW_fiktiv_Funktion(  float ri_0r, 
                                      float du_DW, 
                                      float ds_DW, 
                                      float *du_DW_fiktiv, 
                                      int   msg_flag);

      //---------------------------------------------------------------------------
      // Methode : RAW_T_CNC::dv_rel_aus_Prozess_mm_pro_s
      // Aufgabe : Summe aller Relativgeschwindigkeiten aus dem Prozess
      //---------------------------------------------------------------------------
      int dv_rel_aus_Prozess_mm_pro_s( float rwg,
                                       float ag_v,
                                       float ufz_axial_la_mw,
                                       float rm_wp_1a_mw,
                                       float v1a_mw,             
                                       float radien_axi_kontaktmitte_mw,
                                       float *dv_rel_verl_prozess_mm_pro_s);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::h_3Segm
      // Aufgabe:
      //---------------------------------------------------------------------------
      int h_3Segm(float    H_Kal_HW_u, 
                  float    T_Kal_HW_u,
                  float    H_Kal_DW_u,
                  float    T_Kal_DW_u,
                  float    Hoehe_WP,
                  struct   Def_h_3Segm *h_3Segm_werte);

      //---------------------------------------------------------------------
      // Methode: RAW_T_CNC::du_HW_fiktiv_Funktion
      //---------------------------------------------------------------------
      int du_HW_fiktiv_Funktion( float Ra_0r, 
                                 float du_HW, 
                                 float *du_HW_fiktiv, 
                                 int   msg_flag);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::da_3Segm_Neu
      // Aufgabe:
      //---------------------------------------------------------------------------
      int da_3Segm_Neu( float    da_ME_Laser_u,
                        struct   Def_Mess_Ebene       ME,
                        struct   Def_du_HW_DW_3Segm   du_HW_DW_werte,
                        struct   Def_h_3Segm          h_3Segm_werte,
                        struct   Def_fumomw           *da_3Segm_werte);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::du_HW_DW_3Segm_Neu
      // Aufgabe:
      //---------------------------------------------------------------------------
      int du_HW_DW_3Segm_Neu( struct   Def_Mess_Ebene       ME,
                              float    T_Kal_HW_u,
                              float    H_Kal_HW_u,
                              float    T_Kal_DW_u,
                              float    H_Kal_DW_u,
                              float    Hoehe_WP,
                              struct   Def_du_HW_DW_3Segm   *du_HW_DW_werte,
                              struct   Def_h_3Segm          *h_3Segm_werte);

      //---------------------------------------------------------------------
      // Funktion RWW_T::du_max_DW_Kolli
      // Aufgabe:
      //---------------------------------------------------------------------
      int du_max_DW_Kolli( struct   Def_Walzen_Geo         dornwalze,
                           float    d_dw_pseudo_kolli_ag_dwlager,
                           float    *du_max_DW_Kolli_ohne_DW_Lager,
                           float    *du_max_DW_Kolli_mit_DW_Lager);

      //---------------------------------------------------------------------
      // Methode:du_max_WZ_Kolli
      // Aufgabe:
      //---------------------------------------------------------------------
      int du_max_WZ_Kolli( struct   Def_Walzen_Geo hauptwalze,
                           float    *du_max_kolli,
                           float    *du_max_profil = &float_dummy);

      //---------------------------------------------------------------------
      // Methode:RWW_T::du_ref_ekv_funktion
      // Aufgabe: 
      //---------------------------------------------------------------------
      int du_ref_ekv_funktion(float    deltad_ekv,   
                              float    da_walzform,
                              float    s_walzform,
                              int      abschalt_modus,
                              float    *du_ref_ekv);

      // ----------------------------------------------------------------------------
      // Methode RWW_T::du_DW_aus_MB_max
      // Aufgabe:
      // ----------------------------------------------------------------------------
      int du_DW_aus_MB_max(float mb_max,
                           float dw_sigma_zul,
                           float d_du_dw_aufrunden,
                           float *du_dw_mindest);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::dv0_Radien_AW_WP
      // Aufgabe:
      //---------------------------------------------------------------------
      int dv0_Radien_AW_WP(float    wp_ra_1a_u,
                           float    wp_dra_1a_ou,
                           float    wp_pos_ra_1a_ms_hori_u,
                           float    wp_s1a_u,    
                           float    wp_s1a_o,    
                           float    v_gl_fak_axi_p,
                           int      di_vorhanden_flag,
                           struct   Def_AW_Geo        awo_geometrie,
                           struct   Def_AW_Geo        awu_geometrie,
                           float    *r_AW_dv0_u,
                           float    *r_AW_dv0_o,
                           float    *r_WP_dv0_AW_u,
                           float    *r_WP_dv0_AW_o);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::dv0_Radien_HW_WP
      // Aufgabe:
      //---------------------------------------------------------------------
      int dv0_Radien_HW_WP(float hw_r_u,
                           float wp_ra_1r_u,
                           float hw_dr_ou,
                           float hw_sluftkal_u,
                           float hw_sluftkal_o,
                           float v_gl_fak_hw_p,
                           float *r_hw_dv0_wp,
                           float *r_wp_dv0_hw);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::r_WP_dv0_HW
      // Aufgabe:
      //---------------------------------------------------------------------
      int r_WP_dv0_HW(  float Ra_WP_1r_u,
                        float dr_HW_ou,
                        float sLuftKal_HW_u,
                        float sLuftKal_HW_o,
                        float v_gl_fak_HW_p,
                        float *r_WP_dv0_HW);

      //---------------------------------------------------------------------
      // Methode RWW_T::Walzphasen_flags
      // Aufgabe: 
      //---------------------------------------------------------------------
      int ekv_erreicht( float    dis_aw,    
                        float    dis_hw_dw_u,
                        float    h_ekv,
                        float    s_ekv,
                        int      walz_modus,
                        int      cnc_flag,
                        int      sw_zuerst_fertig_flag,
                        int      walzenstart_flag,   
                        int      aufwalzen_bis_ekv_flag,
                        int      aw_gelueftet_flag,
                        int      *h_ekv_erreicht_flag,
                        int      *s_ekv_erreicht_flag,
                        int      *ekv_erreicht_flag);

      //---------------------------------------------------------------------
      // Methode Fa_max_Bestimmung
      // Aufgabe: Berechung der max. axi. Kraft als f(pos_laser)
      //---------------------------------------------------------------------
      int Fa_max_Begrenzung_alt( float fa_kommi_nenn,
                                 float fa_kommi_hoch,
                                 float fa_max_nutz_nenn,
                                 float fa_max_nutz_hoch,
                                 float fa_reduz_vorne_proz,
                                 float pos_laser,
                                 float aw_anteil_bis_fa_nenn_proz,
                                 float aw_anteil_bis_fa_hoch_proz,
                                 float aw_ml_theo,
                                 float l_aw_sp_fehl,
                                 int   p_system_hoch_flag,
                                 int   fa_max_manu_flag,   
                                 float fa_max_manu,
                                 float *fa_begrenzung,
                                 int   msg_flag);

      //------------------------------------------------------------------------------------
      // Methode   rww_t_Fa_max_Begrenzung
      // Aufgabe: Berechung der max. axi. Kraft als f(pos_laser) (incl. Sigma zul der Welle)
      //------------------------------------------------------------------------------------
      int Fa_max_Begrenzung(  float fa_kommi_nenn,
                              float fa_kommi_hoch,
                              float fa_max_nutz_nenn,
                              float fa_max_nutz_hoch,
                              float aw_sigma_b_max_zul_welle,
                              float aw_durchmesser_welle,
                              float aw_dis_grund_bis_lagerung,
                              int   p_system_hoch_flag,
                              int   fa_max_manu_flag,
                              float fa_max_manu,
                              float aw_achsenlaenge_l_nutz,
                              float aw_achsenlaenge_l_fehlende_spitze,
                              float aw_winkel_bog,
                              float pos_laser_ohne_spitze,
                              float sam,
                              int   di_vorhanden_flag,
                              float *fa_begrenzung,
                              int   msg_flag);

      //---------------------------------------------------------------------
      // Methode: RWW_T::Filter_ohne_Zeitverzoegerung
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Filter_ohne_Zeitverzoegerung(float wert_of,          // Aktueller Wert (Eingangssignal)
                                       float dt_zyklus,        // Zykluszeit           [s]
                                       float t1,               // Glaettungszeit       [s]
                                       float kr,               // Verstaerkungsfaktor  [-]
                                       int   start_flag,       // Start Schalter zur Initialsierung   [0,1]
                                       int   anz_diff_filter,  // Anzahl Differenzfilterungen [-]
                                       float *wert_mf);        // Stellsignal

      //---------------------------------------------------------------------
      // Methode RWW_T::Fr_max_Bestimmung
      // Aufgabe: Berechung der max. radialen Kraft als f(dis_aw) (2-Schlitten)
      //---------------------------------------------------------------------
      int Fr_max_Begrenzung(  float fr_kommi_nenn,
                              float fr_kommi_hoch,
                              float fr_max_nutz_nenn_u,
                              float fr_max_nutz_nenn_o,
                              float fr_max_nutz_hoch_u,
                              float fr_max_nutz_hoch_o,
                              float kraftniveu_unter_BE,
                              float kraftniveu_ueber_BE,
                              float h_ring,
                              int   zwei_radialschlitten_flag,
                              int   p_system_hoch_flag,
                              int   fr_max_manu_flag,   
                              float fr_max_manu,
                              float *fr_begrenzung,
                              int   msg_flag);

      //---------------------------------------------------------------------
      // Methode: RWW_T::Zylinderflaechen
      // Aufgabe: Berechung der Kolbenflaeche und der Ringflaeche eines 
      //          Zylinders 
      //---------------------------------------------------------------------
      int Fr_max_nutz_2Schlitten(float fr_grenze,
                                 float fr_max_nutz_u,
                                 float fr_max_nutz_o,
                                 float kraftniveu_unter_BE,
                                 float kraftniveu_ueber_BE,
                                 float h_ring,
                                 float *fr_max_nutz,
                                 int   msg_flag);

      // ----------------------------------------------------------------------------
      // Methode RWW_T::fr_max_aus_du_DW
      // Aufgabe:
      // ----------------------------------------------------------------------------
      int fr_max_aus_du_DW(float fr_walz,
                           float h_ring,
                           float l_dw_gesamt,
                           float l_dw_unter_BE,
                           float dw_sigma_zul,
                           float dw_sigma_verh,
                           float du_dw,
                           int   ws_einspannung,
                           int   i_max,
                           float *fr_max,
                           int   msg_flag);

      //---------------------------------------------------------------------
      // Methode:RWW_T::fakq_Bestimmung
      // Aufgabe: 
      //---------------------------------------------------------------------
      int fakq_Bestimmung( float h_ist,
                           float s_ist,
                           float h_ziel,
                           float s_ziel,
                           float kurven_faktor,
                           float dif_s_min,
                           int   fh_erreicht_flag,
                           int   aw_gelueftet_flag,
                           int   aw_teil_ueberdeckt_flag,
                           int   aw_voll_ueberdeckt_flag,
                           int   ws_ds_negativ_flag,
                           float *fakq);

      //---------------------------------------------------------------------
      // Methode:RWW_T::fakq_Bestimmung_Flansch
      // Aufgabe: 
      //---------------------------------------------------------------------
      int fakq_Bestimmung_Flansch(  float dis_aw,
                                    float dis_hw_dw_u,
                                    float h_masse_verteilt,
                                    float s_masse_verteilt,
                                    float h_ekv,
                                    float s_ekv,
                                    float h_walzform,
                                    float s_walzform,
                                    float s_aufweiten_ende,
                                    float kurven_faktor_aufweiten,
                                    float kurven_faktor_abwalzen,
                                    float kurven_faktor_aufwalzen,
                                    float dif_s_min,
                                    int   aufw_ende_flag,
                                    int   aw_teil_ueberdeckt_flag,
                                    int   aw_voll_ueberdeckt_flag,
                                    int   aw_gelueftet_flag,
                                    int   fh_erreicht_flag,
                                    int   ws_sw_zuerst_fertig,
                                    int   sw_erreicht_flag,
                                    int   volumenberechnung_flag,
                                    int   cnc_flag,
                                    int   ekv_erreicht_flag,
                                    int   *abwalzen_bis_masse_verteilt_flag,
                                    int   *aufwalzen_bis_ekv_flag,
                                    float *fakq_flansch,
                                    float *h_ziel,
                                    float *s_ziel);

      //---------------------------------------------------------------------
      // Methode:RWW_T::fakq_Bestimmung_Ringe
      // Aufgabe: 
      // Bemerkung:
      //---------------------------------------------------------------------
      int fakq_Bestimmung_Ringe( float h_ist,
                                 float s_ist,
                                 float h_ekv,
                                 float s_ekv,
                                 float s_start,
                                 float s_aufw_ende,
                                 float h_walzform,
                                 float s_walzform,
                                 float dif_s_min,
                                 float kurv_fak_aufw,
                                 float kurv_fak_walz,
                                 int   aufw_ende_flag,
                                 int   fh_erreicht_flag,
                                 int   aw_teil_ueberdeckt_flag,                 
                                 int   aw_voll_ueberdeckt_flag,
                                 int   aw_gelueftet_flag,
                                 int   sw_zuerst_fertig_flag,
                                 int   sw_erreicht_flag,
                                 int   volumenberechnung_flag,
                                 int   cnc_flag,
                                 int   ekv_erreicht_flag,
                                 int   kurv_fak_smooth_flag,
                                 float *fakq_ringe,
                                 float *h_ziel,
                                 float *s_ziel);

      //---------------------------------------------------------------------
      // Methode:RWW_T::fakq_Bestimmung_Stuetzstellen
      // Aufgabe: 
      //---------------------------------------------------------------------
      int fakq_Bestimmung_Stuetzstellen(  float h_ist,
                                          float s_ist,
                                          float h_ekv,
                                          float s_ekv,
                                          float h_walzform,
                                          float s_walzform,
                                          float dif_s_min,
                                          float h_stuetz[],
                                          float s_stuetz[],
                                          int   stuetz_anz,
                                          int   fh_erreicht_flag,
                                          int   aw_gelueftet_flag,
                                          int   aw_teil_ueberdeckt_flag,
                                          int   aw_voll_ueberdeckt_flag,
                                          int   walzenstart_flag,
                                          int   walz_modus,
                                          int   power_taster_flag,
                                          float *fakq_stuetzstellen,
                                          int   *index_stuetz_ziel,
                                          float *h_ziel,
                                          float *s_ziel,
                                          int   *abwalzen_bis_masse_verteilt_flag,
                                          //int   *war_true_abw_b_mas_vert_flag,
                                          int   *aufwalzen_bis_ekv_flag,
                                          float *h_masse_verteilt,
                                          float *s_masse_verteilt);

      //---------------------------------------------------------------------
      // Methode:RWW_T::fakq_Kontrolle
      // Aufgabe:
      //---------------------------------------------------------------------
      int fakq_Kontrolle(  float delta_h,
                           float dsa_mw,   
                           float delta_s,
                           float dhr_mw,
                           float *fakq_kontrolle);

      //---------------------------------------------------------------------
      // Methode:RWW_T::fakq_Bestimmung_TWST
      // Aufgabe: 
      //---------------------------------------------------------------------
      int fakq_Bestimmung_TWST(  float delta_s,
                                 float delta_h,
                                 float dhr,
                                 float dsa,
                                 float anteil_breitung_wegwalzen_twst,
                                 int   aw_gelueftet_flag,
                                 int   aw_voll_ueberdeckt_flag,
                                 int   fh_erreicht_flag,
                                 int   radial_walzen_flag,
                                 float *fakq_twst);

      //---------------------------------------------------------------------
      // Methode:RWW_T::sh_TWST
      // Aufgabe: 
      //---------------------------------------------------------------------
      int fakq_TWST( float dis_aw,
                     float dis_hw_dw_u,
                     float s_mess_start,
                     float h_ekv,
                     float s_ekv,
                     float h_walzform,
                     float s_walzform,
                     float kurv_faktor_twst,
                     float kurv_faktor_aufw,
                     float delta_s,
                     float delta_h,
                     float dhr,
                     float dsa,
                     float anteil_breitung_wegwalzen_proz,
                     float faecherbreite_min_proz,
                     float faecherbreite_max_proz,
                     int   aufw_ende_flag,
                     int   aw_teil_ueberdeckt_flag,
                     int   aw_voll_ueberdeckt_flag,
                     int   aw_gelueftet_flag,
                     int   fh_erreicht_flag,
                     int   ws_sw_zuerst_fertig,
                     int   sw_erreicht_flag,
                     int   volumenberechnung_flag,
                     int   cnc_flag,
                     int   ekv_erreicht_flag,
                     int   *radial_walzen_flag,
                     int   *modus_fakq_twst_flag,
                     int   *twst_gestartet_flag,
                     float *h_twst_start_m,
                     float *s_twst_start_m,
                     float *h_twst_start_r,
                     float *s_twst_start_r,
                     float *h_twst_start_l,
                     float *s_twst_start_l,
                     float *faecherbreite_max,
                     float *faecherbreite_min,
                     float *fakq_twst,
                     float *h_ziel,
                     float *s_ziel,
                     struct Def_querschnitte_TWST *querschnitte_twst);


      //---------------------------------------------------------------------
      // Methode: RAW_T_CNC::Fr_Fa_Mr_Ma_mit_UFZ_Geo
      // Aufgabe: Berechnung mit vorherige Berechnung der Ufz-Geometrie
      //---------------------------------------------------------------------
      int Fr_Fa_Mr_Ma_mit_UFZ_Geo(  int      mit_breitung_axi_flag,
                                    int      mit_breitung_rad_flag,
                                    float    delta_s_mw,
                                    float    delta_h_mw,
                                    float    du_hw_mw,
                                    float    du_dw_mw,
                                    float    ra_mw,
                                    struct   Def_R_Form           WP_RForm_mw,
                                    struct   Def_kw_fr_fa_mr_ma   kw_fr_fa_mr_ma,
                                    struct   Def_Leistung_max     Leistungsgrenzen,
                                    struct   Def_Fr_Fa_Mr_Ma      *fr_fa_mr_ma,
                                    int      msg_flag);

      //---------------------------------------------------------------------
      // Methode: RAW_T_CNC::Fr_Mr_mit_UFZ_Geo
      // Aufgabe: Berechnung mit vorherige Berechnung der Ufz-Geometrie
      //---------------------------------------------------------------------
      int Fr_Mr_mit_UFZ_Geo(  int      mit_breitung_rad_flag,
                              float    delta_s_mw,
                              float    du_hw_mw,
                              float    du_dw_mw,
                              struct   Def_R_Form        WP_RForm_mw,
                              float    kw_fr,
                              float    kw_mr,
                              float    *fr,
                              float    *mr,
                              int      msg_flag);

      //---------------------------------------------------------------------
      // Methode: RAW_T_CNC::Fa_Ma_mit_UFZ_Geo
      // Aufgabe: Berechnung mit vorherige Berechnung der Ufz-Geometrie
      //---------------------------------------------------------------------
      int Fa_Ma_mit_UFZ_Geo(  int      mit_breitung_axi_flag,
                              float    delta_h_mw,
                              float    ra_mw,
                              float    s_mw,
                              float    h_mw,
                              float    kw_fa,
                              float    kw_ma,
                              float    *fa,
                              float    *ma,
                              int      msg_flag);

      //---------------------------------------------------------------------
      // Methode:RAW_T_CNC::hebelarm_verhaeltnis_radial
      //------------------------------------------------------------------
      int hebelarm_verhaeltnis_radial( float du_hw_mw,
                                       float du_dw_mw,
                                       float s1r,
                                       float *hav_radial,
                                       int   msg_flag);

      //---------------------------------------------------------------------
      // Methode:RAW_T_CNC::hebelarm_verhaeltnis_axial
      //------------------------------------------------------------------
      int hebelarm_verhaeltnis_axial(  float ram_o,
                                       float ram_u,
                                       float h1a,
                                       float *hav_axial,
                                       int   msg_flag);

      //---------------------------------------------------------------------
      // Methode:RAW_T_CNC::distanz_hw_dw_achsen
      //------------------------------------------------------------------
      int distanz_hw_dw_achsen(  float du_hw_mw,
                                 float du_dw_mw,
                                 float ds_luft_hw,
                                 float ds_luft_dw,
                                 float s1r,
                                 float *dis_hw_dw_achsen);

      //---------------------------------------------------------------------
      // Methode:RAW_T_CNC::distanz_awo_awu_achsen
      //------------------------------------------------------------------
      int distanz_awo_awu_achsen(float ram_o,
                                 float ram_u,
                                 float dh_luft_awo,
                                 float dh_luft_awu,
                                 float h1a,
                                 float *dis_awo_awu_achsen);

      //---------------------------------------------------------------------
      // Methode: RWW_T::fh_erreicht_mit_h
      // Aufgabe:   
      //---------------------------------------------------------------------
      int fh_erreicht_mit_h(  float dis_aw,
                              float h_walzform,
                              int   walzenstart_flag,
                              int   cnc_flag,
                              int   aufwalzen_bis_ekv_flag,
                              int   walz_modus,
                              int   *fh_erreicht_flag);

      //---------------------------------------------------------------------------
      // Methode: RAW_T_CNC::Genauigkeit_Abnahme_Absolut
      // Aufgabe: Genauigkeit Abnahme absolut in Abhaengigkeit von der 
      //          Walzengeometrie radial  
      //---------------------------------------------------------------------------
      int Genauigkeit_Abnahme_Absolut( float hw_d_nenn,
                                       float dw_d_nenn,
                                       float *genauigkeit_abnahme_abs);

      //---------------------------------------------------------------------
      // Methode:RWW_T::Geo_ring_aus_geo_mess
      // Aufgabe:
      //---------------------------------------------------------------------
      int Geo_ring_aus_geo_mess( int      walz_modus,
                                 struct   Def_Form_Mess form_mess,
                                 float    h_vorform,
                                 float    h_walzform,
                                 float    s_luft_kal_hw_u,    
                                 float    s_luft_kal_dw_u,   
                                 int      fh_erreicht_flag,
                                 int      aw_auto_gelueftet_flag,
                                 int      aw_vorformhoehe_erreicht_flag,
                                 int      ws_d_lauf_flag,
                                 float    *du_ref_ring,
                                 struct   Def_Form    *form_ring);

      //---------------------------------------------------------------------
      // Methode: RWW_T::h_ring_real
      // Aufgabe: Berechnet die Ringhoehe aus dem gemessen Axialwalzenabstand    
      //---------------------------------------------------------------------
      int h_ring_real(  float dis_aw,
                        float h_vorform,
                        float h_walzform,
                        int   fh_erreicht_flag,
                        int   aw_auto_gelueftet_flag,
                        int   aw_vorformhoehe_erreicht_flag,
                        float *h_ring);

      //---------------------------------------------------------------------
      // Methode:RAW_T_CNC::h_von_s_mit_expo_funktion
      // Aufgabe: 
      //---------------------------------------------------------------------
      int h_von_s_mit_expo_funktion(float h_start,
                                    float s_start,
                                    float h_ende,
                                    float s_ende,
                                    float s_lauf,
                                    float exponent,
                                    float *h_von_s_mit_expo);

      //---------------------------------------------------------------------
      // Methode:RAW_T_CNC::s_von_h_mit_expo_funktion
      // Aufgabe: 
      //---------------------------------------------------------------------
      int s_von_h_mit_expo_funktion(float h_start,
                                    float s_start,
                                    float h_ende,
                                    float s_ende,
                                    float h_lauf,
                                    float exponent,
                                    float *s_von_h_mit_expo);

   #if debye
      //---------------------------------------------------------------------------
      // Methode: RWW_T::h1a_3Segm
      //---------------------------------------------------------------------------
      int h1a_3Segm( float    h_kaliber_HW,
                           float    t_kaliber_HW,
                           float    h_kaliber_DW,
                           float    t_kaliber_DW,
                           float    dis_KW_mess,
                           struct   Def_h1a_3Segm *h1a_werte);
   #endif


      //---------------------------------------------------------------------------
      // Methode : RAW_T_CNC::Handrad_korrfaktor_verlagerung_auto
      // Aufgabe : Korrigiere ggf. den Eingangswert
      //---------------------------------------------------------------------------
      int Handrad_korrfaktor_verlagerung_auto(int   walz_modus,
                                              float *handrad_korrektur);

      //---------------------------------------------------------------------------
      // Methode : RAW_T_CNC::Handrad_korrfaktor_plus_Verstaerkung
      // Aufgabe : Korrigiere ggf. den Eingangswert (allgemein)
      //---------------------------------------------------------------------------
      int Handrad_korrfaktor_plus_Verstaerkung( float verstaerkung,
                                                float *handrad_korrektur);

      //---------------------------------------------------------------------------
      // Methode : RAW_T_CNC::Handrad_korrfaktor_verlagerung_plus_Verstaerkung
      // Aufgabe : Korrigiere ggf. den Eingangswert
      //---------------------------------------------------------------------------
      int Handrad_korrfaktor_verlagerung_plus_Verstaerkung( int   walz_modus,
                                                            float verstaerkung,
                                                            float *handrad_korrektur);

      //---------------------------------------------------------------------------
      // Methode: Handrad_Glaettung
      // Aufgabe: RWW_T::Glaettung bei Handrad Drehungen
      //---------------------------------------------------------------------------
      int Handrad_Glaettung(  float handrad_of,           // Ungefilterter Handradwert               [-1,1]
                              float dt_zyklus,            // Zykluszeit                              [s]
                              float t1_glaettung_klein,   // Glaettungszeit zu kleinen Werten         [s]
                              float t1_glaettung_gross,   // Glaettungszeit zu grossen Werten         [s]
                              int   start_flag,           // Start Schalter Initialsierung Glaettung   [0,1]
                              float *handrad_gegl);       // Geglaetteter Handradwert                   [-1,1] 

      //---------------------------------------------------------------------
      // Methode RWW_T::hw_motor_hochgelaufen
      // Aufgabe: 
      //---------------------------------------------------------------------
      int hw_motor_hochgelaufen( float n_hw_motor_soll,
                                 float n_hw_motor_soll_0,
                                 int   walzenstart_flag,
                                 int   walz_modus,
                                 int   *hw_motor_hochgelaufen_flag);

      //---------------------------------------------------------------------
      // Methode: RWW_T::delta_du_rwg_Hochfahren
      // Aufgabe:
      //---------------------------------------------------------------------
      int intervall_du_rwg_Hochfahren( float du_aufwalzung,
                                       float d_du_rwg_hochfahren_0,
                                       float *delta_du_rwg_hochfahren);

      //---------------------------------------------------------------------
      // Methode: RWW_T::delta_du_rwg_Hochfahren
      // Aufgabe:
      //---------------------------------------------------------------------
      int I_Regler(  int    start_flag,
                     int    i_regler_aktiv_flag_flag,
                     double delta_ist_minus_soll,
                     double delta_korr_pro_dt,
                     double *korr);

      //---------------------------------------------------------------------
      // Methode RWW_T::Kraft_erreicht
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Kraft_erreicht( float kraft,
                          float kraft_erreicht_p,  
                          float kraft_kommi_nenn,
                          int   walzenstart_flag,
                          int   *kraft_erreicht_flag);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Korrektur_Walzkurve
      // Aufgabe: 
      //---------------------------------------------------------------------------
      int Korrektur_Walzkurve(int   walz_modus,
                              int   stuetzstellen_anwenden_flag,
                              float s_ist,
                              float h_ist,
                              int   stuetz_anz,
                              float s_stuetz[],
                              float h_stuetz[]);

      //---------------------------------------------------------------------
      // Methode:RWW_T::Kurvfak_Funktion 
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Kurvfak_Funktion(float s_ist,
                           float s_start,
                           float s_aufw_ende,
                           float kurv_fak_walz,
                           float kurv_fak_aufw,
                           int   aw_deckt_flag,
                           int   aufw_ende_flag,
                           int   kurv_fak_smooth_flag,
                           float *kurv_faktor);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Laserwert_AW_Grunddrehzahl
      // Aufgabe: Gefilterte Laser Position fuer Axialwalzengrunddrehzahl
      //---------------------------------------------------------------------------
      int Laserwert_AW_Grunddrehzahl(  float laser_pos_of,        // Ungefilterte Laser Position               [mm]
                                       float dt_zyklus,           // Zykluszeit                                [s]
                                       float t1_glaettung_vor,    // Glaettungszeit vor                        [s]
                                       float t1_glaettung_zurueck,// Glaettungszeit zurueck                    [s]
                                       int   start_flag,          // Start Schalter Initialsierung Glaettung   [0,1]
                                       float *laser_pos_mf,       // Gefilterte Laser Position              [mm] 
                                       float *t1_glaettung,       // Aktuelle Glättungszeit
                                       float *laser_pos_of_alt);  // Alte Laserposition ungefiltert

      //---------------------------------------------------------------------
      // Methode: RWW_T::Lueften_as_groessen
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Lueften_as_groessen(   float    du_ekv,   
                                 float    deltad_ekv,
                                 float    deltad_lf_nach_ekv_0,
                                 float    dh_lf_0,
                                 int      ws_sw_zuerst_fertig,
                                 struct   Def_lueften_as      *lueften_as);

      //---------------------------------------------------------------------
      // Methode RWW_T::M_max_nutz_von_Drehzahl
      // Aufgabe: Berechung m_max_nutz als f(n_ist)
      //---------------------------------------------------------------------
      int M_max_nutz_von_Drehzahl(  float m_max_nutz_bei_n_nenn,
                                    float n_nenn,
                                    float n_ist,
                                    float *m_max_nutz);

      // ----------------------------------------------------------------------------
      // Methode RWW_T::Mb_aufl_u_o_BSE
      // Aufgabe: Berechne unteres und oberes Auflagermoment beidseitig eingespannt
      // ----------------------------------------------------------------------------
      int Mb_aufl_o_u_BSE( float fr_walz,
                           float h_ring,
                           float l_dw_gesamt,
                           float l_dw_unter_BE,
                           float *mb_aufl_o,
                           float *mb_aufl_u);

      // ----------------------------------------------------------------------------
      // Methode RWW_T::Mb_aufl_u_o_BSE
      // Aufgabe: Berechne unteres und oberes Auflagermoment beidseitig eingespannt
      // ----------------------------------------------------------------------------
      int Mb_aufl_o_u_ESE( float fr_walz,
                           float h_ring,
                           float l_dw_gesamt,
                           float l_dw_unter_BE,
                           float *mb_aufl_o,
                           float *mb_aufl_u);

      // ----------------------------------------------------------------------------
      // Methode RWW_T::Mb_max_DW_allgemein
      // Aufgabe:
      // ----------------------------------------------------------------------------
      int Mb_max_DW_allgemein(float fr_walz,
                              float h_ring,
                              float l_dw_gesamt,
                              float l_dw_unter_BE,
                              float mb_aufl_u,
                              float mb_aufl_o,
                              int   i_max,
                              float *mb_max_walzzone,
                              float *mb_max_einspg);

      // ----------------------------------------------------------------------------
      // Methode RWW_T::Mb_max_je_nach_Einspannung
      // Aufgabe:
      // ----------------------------------------------------------------------------
      int Mb_max_je_nach_Einspannung(  float fr_walz,
                                       float h_ring,
                                       float l_dw_gesamt,
                                       float l_dw_unter_BE,
                                       int   ws_einspannung,
                                       int   i_max,
                                       float *mb_max_walzzone,
                                       float *mb_max_einspg,
                                       int   msg_flag);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::Mittelwert_3Segm
      // Aufgabe:   
      //---------------------------------------------------------------------
      int Mittelwert_3Segm(float Wert_u,
                           float Wert_m,
                           float Wert_o,
                           float h1a_fak_u,
                           float h1a_fak_m,
                           float h1a_fak_o,
                           float *Wert_mw);
   
      //---------------------------------------------------------------------
      // Methode  RWW_T::Momente_pro_Motor
      // Aufgabe: Berechne Motor-Momente
      //---------------------------------------------------------------------
      int Momente_pro_Motor(struct  Def_Maschine_Motor *motor,
                            int     msg_flag);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::n_omega_HW_AW_WP
      // Aufgabe: 
      //---------------------------------------------------------------------
      int n_omega_HW_AW_WP(float    r_HW_dv0,                  // Geschwindigkeitsradius der Hauptwalze     [mm]
                           float    r_WP_dv0_HW,
                           float    r_AW_dv0_u,
                           float    r_AW_dv0_o,
                           float    r_WP_dv0_AW_u,
                           float    r_WP_dv0_AW_o,
                           float    i_rad,                     // Untersetzungsverhaeltnis axial             [-]
                           float    i_axi,               
                           float    n_HW_Motor_Soll,           // Solldrehzahl Hauptwalzenmotor             [1/s]
                           float    n_HW_Motor_max,            // Maximaldrehzahl Hauptwalzenmotor          [1/s]                     
                           float    n_AW_Motor_max,
                           float    dn_AW_reg_res_p,           // Regelreserve Axialwalzen                  [%]
                           float    dv_Grundvertrim_o_zu_u_p,  // Vertrimmung AW oben zu unten              [%]
                           float    sym_fak,                   // Faktor fuer Symmetriebedingung               [-]
                           int      WS_n_HW_Motor_vari,        // Flag Drehstrom/Gleichstrom HW-Motor         []
                           struct   Def_n_omega *n_omega,
                           int      msg_flag);

      //---------------------------------------------------------------------
      // Methode: RWW_T::Pos_AG_Kollision   
      // Aufgabe:  
      //---------------------------------------------------------------------
      int Pos_AG_Kollision(float    pos_RS_Achse,
                           float    d_dw_pseudo_kolli_ag_dwlager,
                           struct   Def_Walzen_Geo         dw_geometrie,
                           struct   Def_AW_Geo            aw_geometrie,
                           float    dis_min_AG_DW,        
                           float    *pos_AG_Kolli);

      //---------------------------------------------------------------------
      // Methode: RAW_T::Pos_AG_Laser_mit_WP_Achse
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Pos_AG_Laser_mit_WP_Achse(int      WS_AGmodus,
                                    int      walzenstart_flag,
                                    float    pos_RS_Achse,
                                    float    pos_RS_Achse_Start,
                                    float    Da_Mess_u,
                                    float    pos_WP_Achse,
                                    float    pos_WP_Achse_Start,
                                    float    dpos_AG_Start_0,
                                    float    dis_min_AG_DW,
                                    float    du_ref,
                                    float    du_ref_Start,
                                    float    du_ref_Ende,
                                    float    dis_aw,
                                    float    dis_aw_Start,
                                    float    h_walzform,
                                    float    dpos_AG_Start_VS,
                                    float    dpos_AG_Ende_VS,
                                    float    d_dw_pseudo_kolli_ag_dwlager,
                                    float    pos_laser_mit_spitze_u_mf_start,
                                    float    ag_flex_move_exponent,
                                    struct   Def_Walzen_Geo       hw_geometrie,
                                    struct   Def_Walzen_Geo       dw_geometrie,
                                    struct   Def_AW_Geo           awu_geometrie,
                                    struct   Def_Schlupf          schlupf_u,
                                    float    *pos_TR_Soll_u,
                                    float    *pos_AG_Soll,
                                    float    *pos_las_sl_u,
                                    float    *dpos_AG_Soll,
                                    float    *dpos_AG_Ist,
                                    int      msg_flag);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Pos_LAS_SL_unten
      // Aufgaba:
      //---------------------------------------------------------------------------
      int Pos_LAS_SL_unten(float aw_ml_theor,
                           float dis_sl,
                           float dr_HW_ou,
                           float *pos_las_sl_u);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::pos_r_AW_dv0_mS_hori
      // Aufgabe:
      //---------------------------------------------------------------------
      int pos_r_AW_dv0_mS_hori( float    pos_ra_wp_1a_ms_hori,
                                float    s_kontakt_aw_hori,
                                float    v_gl_fak_axi_p,
                                struct   Def_AW_Geo aw_geometrie,
                                float    *pos_r_aw_dv0_ms_hori);

      //---------------------------------------------------------------------------
      // Methode RWWT::pos_RS_und_WP_Achse_einfach
      // Aufabe: 
      //---------------------------------------------------------------------------
      int pos_RS_und_WP_Achse_einfach( float da_mess_u,
                                       float s_luft_kal_hw_u,
                                       float dis_hw_dw_u,
                                       float r_hw_u,
                                       float r_dw_u,
                                       float pos_rs_achse_min,
                                       int   walz_modus,
                                       float *pos_rs_achse,
                                       float *pos_wp_achse);

      //---------------------------------------------------------------------------
      // Methode:   RWW_T::PT_Glied_1_Ordnung
      // Aufgabe: PT_Glied mit Verzoegerung 1.Ordnung
      //
      //                        ________________
      //                       |                |
      //                       |         1      |
      //  wert_aktuell (e) -->-| kr * --------- |----->-- *wert_neu (ua)
      //                       |      1 + s*t1  |
      //                       |________________|
      //
      //---------------------------------------------------------------------------
      int PT_Glied_1_Ordnung( float ein_wert_aktuell, // Aktuelle Wert
                              float dt,               // Zykluszeit                          [s]
                              float t1,               // Glaettungszeit                      [s]
                              float kr,               // Verstaerkungsfaktor                 [-]
                              int   start_flag,       // Start Schalter zur Initialsierung   [0,1]
                              float *aus_wert_neu);   // Stellsignal

      //---------------------------------------------------------------------------
      // Methode: RWW_T::PPT_Glied
      // Aufgabe: LEAD-Glied, wenn t1 > t2, LAG-Glied, wenn t1 < t2
      //
      //                        ________________
      //                       |                |
      //                       |      1 + s*t1  |
      //  wert_aktuell (e) -->-| kr * --------- |----->-- *wert_neu (ua)
      //                       |      1 + s*t2  |
      //                       |________________|
      //
      //---------------------------------------------------------------------------
      int PPT_Glied( float ein_wert_aktuell, // Aktueller Wert (Eingangssignal)
                           float dt,               // Zykluszeit      [s]
                           float t1,               // Zeitkonstante 1 [s]
                           float t2,               // Zeitkonstante 2 [s]
                           float kr,               // Verstaerkungsfaktor [-]
                           float MaxWert,          // Maximales Stellsignal
                           float MinWert,          // Minimales Stellsignal
                           int   start_flag,       // Start Schalter zur Initialsierung [0,1]
                           float *ein_wert_alt,    // Eingangssignal vom letzten Durchlauf
                           float *aus_wert_neu);   // Stellsignal

      //---------------------------------------------------------------------
      // Methode:   RWW_T::r_HW_dv0_WP
      // Aufgabe:
      //---------------------------------------------------------------------
      int r_HW_dv0_WP(  float r_HW_u,
                        float dr_HW_ou,
                        float sLuftKal_HW_u,
                        float sLuftKal_HW_o,
                        float v_gl_fak_HW_p,
                        float *r_HW_dv0);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::Radien_AW
      // Aufgabe:
      //---------------------------------------------------------------------
      int Radien_AW( float    wp_s1a,
                     float    wp_pos_ra_1a_ms_hori,
                     float    aw_winkel_bo,
                     float    aw_delta_w_konstr_bo,
                     float    aw_l_fehlende_spitze,
                     int      di_vorhanden_flag,
                     int      oben_flag,
                     struct   Def_Radien_Axial   *radien,
                     int      msg_flag);

      //---------------------------------------------------------------------
      // Methode RWW_T::Radien_axial
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Radien_axial( float    wp_pos_ra_1a_ms_hori_u,
                        float    wp_dRa_1a_ou,   
                        float    wp_s1a_u,
                        float    wp_s1a_o,
                        int      di_vorhanden_flag,
                        struct   Def_AW_Geo        awo_geometrie,
                        struct   Def_AW_Geo        awu_geometrie,
                        struct   Def_Radien_Axial  *radien,
                        int      msg_flag);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::Radius_AW_dv0
      // Aufgabe:
      //---------------------------------------------------------------------
      int Radius_AW_dv0(float    pos_ra_wp_1a_ms_hori,
                        float    s_kontakt_aw_hori,
                        float    v_gl_fak_axi_p,
                        struct   Def_AW_Geo aw_geometrie,
                        float    *r_aw_dv0);

      //---------------------------------------------------------------------
      // Methode: RWW_T::r_WP_dv0_axi_Funktion
      // Aufgabe:
      //---------------------------------------------------------------------
      int r_WP_dv0_axi_Funktion( float wp_ra_1a,
                                 float wp_s_kontakt_aw_hori,   
                                 float v_gl_fak_axi_p,
                                 float *wp_r_dv0_aw);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Ringlageregler
      // Aufgabe: Bestimme Motordrehzahlaenderung aufgrund der Zentrierkraftdifferenz
      //---------------------------------------------------------------------------
      int Ringlageregler(  float fz_zyl_e_of,            // ungefilterte Zentrierkraft am Zylinder Einlaufseite Hauptwalze [kN]
                           float fz_zyl_a_of,            // ungefilterte Zentrierkraft am Zylinder Auslaufseite Hauptwalze [kN]
                           float dfz_zyl_max,            // Maximaler nutzbare Kraft im Zylinder                           [kN]
                           float n_aw_motor_g_o,         // Motorgrunddrehzahl Kegelwalze oben                             [1/min]
                           float n_aw_motor_g_u,         // Motorgrunddrehzahl Kegelwalze unten                            [1/min]
                           float dn_aw_verst_fak_prop,   // Empfindlichkeit Ringlageregler                                 [0-5]
                           float dn_aw_verst_fak_addi,   // Additive Empfindlichkeit Ringlageregler                        [-] 
                           float dt_zyklus,              // Zykluszeit                                                     [s]
                           float t1_glaettung,           // Glaettungszeit                                                  [s]
                           int   start_flag,             // Start Schalter Initialsierung Glaettung                         [0,1]
                           float *fz_zyl_e_mf,           // gefilterte Zentrierkraft am Zylinder Einlaufseite Hauptwalze   [kN]
                           float *fz_zyl_a_mf,           // gefilterte Zentrierkraft am Zylinder Auslaufseite Hauptwalze   [kN] 
                           float *dfz_zyl_mf,            // Zentrierkraft Differenz im Zylinder geglaettet                  [kN]
                           float *dn_aw_motor_g_o,       // Motordrehzahlaenderung Kegelwalze oben                          [1/min]
                           float *dn_aw_motor_g_u,       // Motordrehzahlaenderung Kegelwalze unten                         [1/min]
                           float *dn_aw_motor_o_prop_mf, // Motordrehzahlaenderung Kegelwalze oben proportionaler Anteil    [1/min]
                           float *dn_aw_motor_u_prop_mf, // Motordrehzahlaenderung Kegelwalze unten proportionaler Anteil   [1/min]
                           float *dn_aw_motor_o_addi_mf, // Motordrehzahlaenderung Kegelwalze oben additiver Anteil         [1/min]
                           float *dn_aw_motor_u_addi_mf);// Motordrehzahlaenderung Kegelwalze unten additiver Anteil        [1/min]

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Ringlageregler_dn_AW_verst_fak
      // Aufgabe: Bestimme Verstaeerkung Ringlageregler
      //---------------------------------------------------------------------------
      int Ringlageregler_dn_AW_verst_fak( float fz_soll,
                                          float fz_soll_min_verst_aendern,
                                          float fz_soll_grenz_verst_aendern,
                                          float verst_1_bei_fz_soll_min,
                                          float verst_0_bei_fz_soll_grenz, 
                                          float verst_ringlage_exponent,
                                          float *verst_ringlage);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Ringverlagerung
      // Aufgabe: Ringverlagerung automatisch und manuell
      //---------------------------------------------------------------------------
      int Ringverlagerung( struct   Def_Form          form_ring_u,   // Ringgeometrie
                           struct   Def_Form          ist_walzform,  // Istwalzform
                           struct   Def_AW_Geo        awu_geometrie, // Axialwalzengeometrie (unten)
                           float    hw_d_nenn,                       // Hauptwalzennenndurchmesser                [mm]
                           float    delta_h,                         // Ist axiale Hoehenabnahme aus Puffer        [mm]
                           float    pos_laser_mit_spitze_u_mf,       // Ist Laserposition aus Puffer              [mm]
                           float    schlupf_u_pos_laser_mit_spitze,
                           float    radien_axi_kontaktmitte_u,       // Kontaktmitte Axialwalze                   [mm]
                           float    ufz_axial_la,                    // Gedrueckte Laenge Axialwalze                [mm]
                           float    v1a,                             // mittlere axiale Austrittsgeschw.          [mm]
                           float    dpm_mf,                          // Ringwachsgeschwindigkeit aus Puffer       [mm/s]
                           float    alpha_verl_manu_gr,              // Manuelle Verlagerung                      [Grad]
                           float    handrad_korrektur,               // Wert Poti oder Handrad                    [von -2 bis +2]
                           float    dt_zyklus,                       // Zykluszeit                                [s]
                           float    n_omega_tu,
                           float    t1_verlagerung,                  // Glaettungszeit                             [s]
                           float    dv_rad_verlager_soll_0,          // Radiale relative Sollgeschwindigkeit      [mm/s]
                                                                     // im Axialwalzspalt ohne Poti   
                           int      ag_modus,                        // Schalter Axialgeruestmodus                 [AG_MOD_FAEHRT, AG_MOD_STEHT, ....]
                           int      aw_auto_gelueftet_flag,          // Axialwalzen Lueften aktiv                  [TRUE,FALSE]]
                           int      river_auto_flag,                 // Automatische Ringverlagerung aktiv        [TRUE,FALSE]]
                           int      river_manu_flag,                 // Manuelle Ringverlagerung aktiv            [TRUE,FALSE]]
                           int      schlupfwalzen_flag,              // Schalter Schlupfwalzen                    [TRUE,FALSE]
                           int      start_flag,                      // Start Schalter Initialsierung Glaettung    [0,1]
                           int      walz_modus,
                           int      cnc_flag,

                           double   river_fag_flag,                  // 0.0 oder 1.0
                           double   river_fag_delta_soll,            // N
                           double   river_fag_verstaerkung,          // mm / N 

                           int      *t1_verlagerung_null_flag,
                           struct   Def_Verlagerung   *verlagerung_auto,  // Structur fuer autom. Ringverlagerung
                           struct   Def_Verlagerung   *verlagerung_manu,  // Structur fuer manuelle Ringverlagerung
                           double   *verl_soll_auto_in_mm_0_of,           // Autom. Ringverlagerung ohne Filter Basis [mm]
                           double   *verl_soll_auto_in_mm_of,             // Autom. Ringverlagerung ohne Filter [mm] 
                           double   *verl_soll_auto_in_mm_fag_dkorr_TRE,
                           double   *verl_soll_auto_in_mm_fag_korr_TRE_of,
                           double   *verl_soll_auto_in_mm_fag_korr_TRE_mf,
                           double   *verl_soll_auto_in_mm_of_TRE,
                           struct   Def_Koppers_Filter_Werte *kpf_verlagerung_auto);        // Structur fuer manuelle Ringverlagerung

      //---------------------------------------------------------------------
      // Methode: RWW_T::RWG_nru_Mittelwert
      // Aufgabe:
      //---------------------------------------------------------------------
      int RWG_nru_Mittelwert( float rwg_soll_aktu,
                              float rwg_soll_nru,
                              float dm_mw,
                              float dm_mw_nru,
                              float dm_mw_endphase,
                              float *rwg_mw_nru);

      //---------------------------------------------------------------------
      // Methode: RWW_T::RWG_zul_Aufwalzung
      // Aufgabe:
      //---------------------------------------------------------------------
      int RWG_zul_Aufwalzung( int   aufwalzung_check_flag,
                              float du_aufwalzung,
                              float rwg_soll_0,
                              float rwg_max_eingabe,
                              float *rwg_max_zul);

      //---------------------------------------------------------------------
      // Methode: RWW_T::Prozess_am_Limit (ehemals RWG_ds_dh_ohne_StE!)
      // Aufgabe:
      //----------------------------------------------------------------------
      int Prozess_am_Limit(struct   Def_Leistung_max     Leistungsgrenzen,
                           struct   Def_Iterstop         iterstop,
                           struct   Def_Form             form_ring_m_nru,
                           struct   Def_kw_fr_fa_mr_ma   kw_fr_fa_mr_ma_puff,
                           struct   Def_Ufz_Rad          ufz_rad_startwerte,
                           struct   Def_Ufz_Axi          ufz_axi_startwerte,
                           float    v1r,
                           float    v1a,
                           float    du_hw_mw,
                           float    du_dw_mw,
                           float    ra_mw,
                           float    rwg_max_zul,
                           float    fakq0,
                           float    anteil_breitung_wegwalzen_twst,
                           int      radial_walzen_flag,
                           int      walz_modus,
                           int      modus_fakq_twst_flag,
                           int      mit_breitung_axi_flag,
                           int      mit_breitung_rad_flag,
                           //int      ws_sw_zuerst_fertig,
                           int      test_walzen_ohne_ring_flag,
                           int      f_axial_begrenzung_flag,
                           struct   Def_Walzphase        walzphase,
                           struct   Def_Walzphase_Onli   *walzphase_onli,
                           int      *power_taster_flag,
                           struct   Def_iter_anpass      *iter_anpass,
                           struct   Def_rwg_ds_dh_ufz    *rwg_ds_dh_res,
                           int      *zuerst_deltas_wst_flag,
                           int      msg_flag);

      //---------------------------------------------------------------------
      // Methode:RWW_T::RWG_max_zul_mit_Hochfahren
      // Aufgabe:
      //---------------------------------------------------------------------
      int RWG_max_zul_mit_Hochfahren(  int      aufwalzung_check_flag,
                                       int      walzen_start_flag,
                                       int      aufweiten_ende_flag,
                                       float    rwg_hochfahren_start,
                                       float    rwg_aufweiten,
                                       float    rwg_max,
                                       float    du_ref_ring_nru,
                                       float    du_ref_ring,
                                       float    du_ref_start,
                                       float    du_ref_ende,
                                       float    d_du_pro_1_mm_rwg,
                                       int      endphase_intern_flag,
                                       int      walz_modus,
                                       int      RWG_smooth_flag,
                                       float    deltad_rundier,
                                       float    exponent_rwg_endphase,
                                       float    rwg_poti_wert,
                                       float    rwg_poti_wert_endphase_start,
                                       float    rwg_start_endphase,
                                       float    rwg_min_endphase,
                                       struct   Def_Endphase endphase,
                                       int      delta_du_bis_aufweiten_start_manu_flag,
                                       double   delta_du_bis_aufweiten_start_manu,
                                       int      delta_du_bis_aufweiten_ende_manu_flag,
                                       double   delta_du_bis_aufweiten_ende_manu,
                                       int      delta_du_bis_rwg_max_manu_flag,
                                       double   delta_du_bis_rwg_max_manu,
                                       float    *rwg_max_zul,
                                       float    *rwg_soll_aktu,
                                       int      msg_flag);

      //---------------------------------------------------------------------
      // Methode: RAW_T_CNC::RWG_max_zul_mit_Rampe
      // Aufgabe:
      //---------------------------------------------------------------------
      int RWG_max_zul_mit_Rampe(float  rwg_max_zul_ohne_rampe,          
                                float  rwg_max_poti_wert,
                                float  wp_dm,
                                float  wp_dm_vorher,
                                int    endphase_flag,
                                float  d_du_pro_1_mm_rwg,
                                float  *rwg_max_zul_mit_rampe);

      //---------------------------------------------------------------------
      // Methode:RWW_T::s_aufweiten_ende_funktion
      // Aufgabe: 
      //---------------------------------------------------------------------
      int s_aufweiten_ende_funktion(float s_start,
                                    float s_ekv,
                                    float s_aufweiten_proz,
                                    float *s_aufweiten_ende);

      //---------------------------------------------------------------------
      // Methode:RWW_T::s1r_aus_disHWDW
      // Aufgabe: 
      //---------------------------------------------------------------------
      int s1r_aus_disHWDW(float   dis_hw_dw,
                                float  hw_s_luftkal,
                                float  dw_s_luftkal, 
                                float  *wp_s1r);

      //---------------------------------------------------------------------
      // Methode: RWW_T::s_AW_Kontakt
      // Aufgabe: Berechnet die Kontaktwanddicke an der Axialwalze
      //---------------------------------------------------------------------
      int s_AW_Kontakt( float wp_s1a,
                        float wp_pos_ra_1a_ms_hori,
                        float aw_l_fehlende_spitze,
                        float aw_delta_w_konstr_bo,
                        int   di_vorhanden_flag,
                        float *wp_s_kontakt_aw,
                        float *wp_s_kontakt_aw_hori);

      //---------------------------------------------------------------------
      // Methode:   RWW_T::s_Kontakt_WP_WZ_s_Profil_WP_ou
      // Aufgabe:
      //---------------------------------------------------------------------
      int s_Kontakt_WP_WZ_s_Profil_WP_ou( float dr_WZ_ou,
                                          float sLuftKal_WZ_u,
                                          float sLuftKal_WZ_o,
                                          float *s_Kontakt_WP_WZ_ou,
                                          float *s_Profil_WP_WZ_ou);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::s_mess_u_h_mess_1RU_weiter
      // Aufabe: 
      //---------------------------------------------------------------------------
      int s_mess_u_h_mess_1RU_weiter(  float dis_hw_dw_u_ist,
                                       float dis_aw_ist,
                                       float dh_zustellung_1RU,
                                       float ds_zustellung_1RU,
                                       float *dis_hw_dw_u_1RU,
                                       float *dis_aw_1RU);


      //---------------------------------------------------------------------
      // Methode:RWW_T::schlupfwalzen
      // Aufgabe:
      //---------------------------------------------------------------------
      int schlupfwalzen (  float aw_geometrie_pos_laser_sl,
                           float pos_laser_u,
                           int   walzenstart_flag,
                           int   *schlupfwalzen_flag);

      //---------------------------------------------------------------------
      // Methode:RWW_T::sh_mitte_links_rechts_TWST
      // Aufgabe: 
      //---------------------------------------------------------------------
      int sh_mitte_links_rechts_TWST(  float    h_ist,
                                       float    s_ist,
                                       float    h_start_m,
                                       float    s_start_m,
                                       float    h_start_r,
                                       float    s_start_r,
                                       float    h_start_l,
                                       float    s_start_l,
                                       float    h_ekv,
                                       float    s_ekv,
                                       float    kurv_faktor_twst,
                                       struct   Def_querschnitte_TWST *querschnitte_twst);

      //---------------------------------------------------------------------
      // Methode RWW_T::sp_hp_soll
      // Aufgabe: 
      //---------------------------------------------------------------------
      int sp_hp_soll(float    s_zustellung_1RU,
                     float    h_zustellung_1RU,
                     float    tu_1RU,
                     float    *sp_1RU,
                     float    *hp_1RU,
                     int      msg_flag);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Suche_Segm_in_ME_Laser_u
      // Aufgabe:
      //---------------------------------------------------------------------------
      int Suche_Segm_in_ME_Laser_u( float    y_pos_Laser,
                                    struct   Def_fumo h_Segm_umo,
                                    int      *Segm);

      //---------------------------------------------------------------------
      // Methode: RWW_T::sw_erreicht
      // Aufgabe:
      //---------------------------------------------------------------------
      int sw_erreicht(  float dis_hw_dw_u,
                        float s_walzform,
                        int   walzenstart_flag,
                        int   cnc_flag,
                        int   *sw_erreicht_flag);

      //---------------------------------------------------------------------
      // Methode: RWW_T::Symmetriefaktor
      // Aufgabe:
      //---------------------------------------------------------------------
      int Symmetriefaktor( float epsilon_Qr,
                           float epsilon_Qa,
                           float *sym_fak);

      //---------------------------------------------------------------------
      // Methode: RWW_T::tu_dm_nru
      // Aufgabe:
      //---------------------------------------------------------------------
      int tu_dm_nru( float    dm_mw_nru_vorher, 
                     float    dm_ist,
                     float    dm_mw_endphase,
                     float    v1r_ist,
                     float    v1r_nru,
                     float    rwg_soll_aktu,
                     float    rwg_soll_nru,
                     float    tu_ist,
                     int      hw_motor_hochgelaufen_flag,
                     struct   Def_tu_d_dd_nru *tu_d_dd_nru,
                     int      msg_flag);

      //---------------------------------------------------------------------
      // Methode: RAW_T_CNC::UFZ_axial
      // Aufgabe:
      //---------------------------------------------------------------------
      int UFZ_axial( int      mit_breitung_axi_flag,
                     float    delta_h,
                     float    ram,
                     float    srm,
                     float    ham,
                     struct   Def_Ufz_Axi *ufz_a,
                     int      msg_flag);

// -------------- N  E  U -----------------
      //---------------------------------------------------------------------
      // Methode: RAW_T::UFZ_radial
      // Aufgabe:
      //---------------------------------------------------------------------
      int UFZ_radial(int      mit_breitung_rad_flag,
                     struct   Def_R_Form WP_RForm_mw,
                     float    deltas_mw,
                     float    du_hw_mw,
                     float    du_dw_mw,
                     struct   Def_Ufz_Rad *ufz_rad,                           
                     int      msg_flag);

// -------------- N  E  U -----------------
      //---------------------------------------------------------------------
      // Methode: RAW_T::Funktion_verh_lhw_ldw_ohne_Verlagerung
      // Aufgabe:
      //---------------------------------------------------------------------
      int Funktion_verh_lhw_ldw_ohne_Verlagerung(  float du_dw_hw_verh,
                                                   float du_dw_hw_fiktiv_verh,
                                                   float *verh_lhw_ldw_oV);

// -------------- N  E  U -----------------
      //---------------------------------------------------------------------
      // Methode: RAW_T::Funktion_ds_hw_dw_mw_oV
      // Aufgabe:
      //---------------------------------------------------------------------
      int Funktion_ds_hw_dw_mw_oV(  float    deltas_mw,
                                    float    du_hw_mw,
                                    float    du_dw_mw,
                                    float    WP_RForm_mw_ra,
                                    float    WP_RForm_mw_ri,
                                    struct   Def_Ufz_Rad  *ufz_rad,
                                    int      msg_flag);


// -------------- N  E  U -----------------
      //---------------------------------------------------------------------
      // Methode: RAW_T::Funktion_ds_hw_dw_oV_aus_verh_lhw_ldw
      // Aufgabe:
      //---------------------------------------------------------------------
      int Funktion_ds_hw_dw_oV_aus_verh_lhw_ldw(float    deltas,
                                                float    Verh_lhw_ldw,
                                                float    du_dw_hw_fiktiv_verh,
                                                float    *ds_hw_dw,
                                                float    *ds_dw_mw,
                                                float    *ds_hw_mw);

// -------------- N  E  U -----------------
      //---------------------------------------------------------------------
      // Methode: RAW_T::Funktion_ds_hw_dw_ohne_Verlagerung_aus_verh_lhw_ldw
      // Aufgabe:
      //---------------------------------------------------------------------
      int Funktion_lr_mw_lhw_ldw_verh_lhw_ldw_rr_mw(  float ds_hw_mw_oV,
                                                      float du_hw_fiktiv_oV,
                                                      float ds_dw_mw_oV,
                                                      float du_dw_fiktiv_oV,
                                                      float du_hw_mw,
                                                      float du_dw_mw,
                                                      float *lr_mw_oV,
                                                      float *ld_dw_oV,
                                                      float *ld_hw_oV,
                                                      float *verh_lhw_ldw_oV,
                                                      float *rr_mw_oV);

// -------------- N  E  U -----------------
      //---------------------------------------------------------------------
      // Methode: RAW_T::Funktion_ld_hw_ld_dw_oV
      // Aufgabe:
      //---------------------------------------------------------------------
      int Funktion_ld_hw_ld_dw_oV(  float ds_hw,
                                    float ds_dw,
                                    float WP_RForm_mw_ra,
                                    float WP_RForm_mw_ri,
                                    float du_hw_mw,
                                    float du_dw_mw,
                                    float *lr_mw_oV,
                                    float *ld_hw_oV,
                                    float *ld_dw_oV,
                                    float *du_hw_fiktiv_oV,
                                    float *du_dw_fiktiv_oV,
                                    float *rr_mw_oV,
                                    int   msg_flag);


// -------------- N  E  U -----------------
      //---------------------------------------------------------------------
      // Methode: RAW_T::Funktion_rr_fiktiv
      // Aufgabe:
      //---------------------------------------------------------------------
      int Funktion_rr_fiktiv( float    du_hw_mw,
                              float    du_dw_mw,
                              float    deltas_mw,
                              float    WP_RForm_mw_ra,
                              float    WP_RForm_mw_ri,
                              float    *rr_mw,
                              int      msg_flag);

// -------------- N  E  U -----------------
      //---------------------------------------------------------------------
      // Methode: RAW_T::Funktion_rr_fiktiv_Basis
      // Aufgabe:
      //---------------------------------------------------------------------
      int Funktion_rr_fiktiv_Basis( float    du_hw,
                                    float    du_dw,
                                    float    *rr_fiktiv);


      //---------------------------------------------------------------------------
      // Methode: RWW_T::Um_ekv_flag
      // Aufgabe:
      //---------------------------------------------------------------------------
      int Um_ekv_flag(  int      walzenstart_flag,
                        int      walz_modus,
                        float    s_ekv,
                        float    h_ekv,
                        struct   Def_Form_Mess form_mess_start,
                        struct   Def_Form_Mess form_mess_mf,
                        float    verhaelt_grenze_proz,
                        int      *um_ekv_flag);

      //---------------------------------------------------------------------
      // Methode   RWW_T::v_HW_Grundgleichung
      // Aufgabe: 
      //---------------------------------------------------------------------
      int v_HW_Grundgleichung(float r_HW_dv0,
                              float i_rad,
                              float n_HW_Motor,
                              float *v_HW_dv0);

      //---------------------------------------------------------------------------
      // Methode : RAW_T_CNC::Verlagerung_auto
      // Aufgabe : Automatischer Ringverlagerungswert (Ringe und Flansche)
      //---------------------------------------------------------------------------
      int Verlagerung_auto(float rm_wp_1a_mw,
                           float dv_rel_verl_soll_bezogen,
                           float v1a_mw,
                           float dv_rel_verl_prozess_mm_pro_s,
                           float *verl_soll_auto_in_mm,
                           float *dv_rel_verl_auto_bezogen,
                           float *dv_rel_verl_auto_mm_pro_s);

      //---------------------------------------------------------------------------
      // Methode : RAW_T_CNC::Verlagerung_manu
      // Aufgabe : Automatischer Verlagerungssollwert (Manuelle Vorgabe(Simulation))
      //---------------------------------------------------------------------------
      int Verlagerung_manu(float rm_wp_1a_mw,
                           float v1a_mw,
                           float alpha_verl_manu_rm_gr,
                           float *verl_soll_manu_in_mm,
                           float *dv_rel_verl_manu_bezogen,
                           float *dv_rel_verl_manu_mm_pro_s);

      //---------------------------------------------------------------------------
      // Methode : RAW_T_CNC::Verlagerung_vollscheibe_auto
      // Aufgabe : Automatischer Ringverlagerungswert (Vollscheibe)
      //---------------------------------------------------------------------------
      int Verlagerung_vollscheibe_auto(float ra_wp_1r_mw,
                                       float rm_wp_1a_mw,
                                       float ra_ist_walzform,
                                       float hw_d_mw,
                                       float v1a_mw,
                                       float alpha_verl_vs_da_bo,
                                       float *verl_soll_auto_in_mm,
                                       float *dv_rel_verl_auto_bezogen,
                                       float *dv_rel_verl_auto_mm_pro_s);

      //---------------------------------------------------------------------
      // Methode:   RAW_T_CNC::Verlagerungswinkel
      // Aufgabe:
      //---------------------------------------------------------------------
      int Verlagerungswinkel( float verlagerung_mm,            // Verlagerungwert                         [mm]
                              float rm_wp_1r_mw,               // Auslauf. Radius Walzprodukt Mittelwert  [mm]                        
                              float s_wp_1r_mw,                // Auslauf. Wandd. Walzprodukt Mittelwert  [mm]
                              float hw_d_mw,                   // Hauptwalzedurchmesser Mittelwert        [mm]
                              float *verl_alpha_auto_rm_bo,    // Ringverlagerungswinkel bezogen auf rm   [Rad]
                              float *verl_alpha_auto_ra_bo,    // Ringverlagerungswinkel bezogen auf ra   [Rad]
                              float *verl_alpha_auto_hw_mp_bo);// Ringverlagerungswinkel bezogen auf hw_mp[Rad]
                                                               // Hauptwalzenmittelpunkt                     
      //---------------------------------------------------------------------------
      // Methode : RAW_T_CNC::Verlagerung_rm_in_mm
      // Aufgabe : Bestimme Verlagerung bezogen auf mittlerern Durchmesser
      //---------------------------------------------------------------------------
      int Verlagerung_rm_in_mm(  float alpha_verl_rm_gr,
                                 float rm_wp_1r_mw,
                                 float *verl_rm_in_mm);

      //---------------------------------------------------------------------
      // Methode: RWW_T::v1r_v1a
      // Aufgabe:
      //---------------------------------------------------------------------
      int v1r_v1a(float v_HW_dv0,
                  float r_WP_dv0,
                  float rm_WP_1r_mw,
                  float sym_fak,
                  float *v1r_mw,
                  float *v1a_mw,
                  int   msg_flag);

      //---------------------------------------------------------------------
      // Methode: RAW_T::v1r_v1a_neu
      // Aufgabe:
      //---------------------------------------------------------------------
      int v1r_v1a_neu(float wp_omega_rad,
                      float wp_rm_1r_mw,
                      float sym_fak,
                      float *v1r_mw,
                      float *v1a_mw);

      //---------------------------------------------------------------------
      // Methode: RWW_T::v_HW_dv0_Funktion
      // Aufgabe:
      //---------------------------------------------------------------------
      int v_HW_dv0_Funktion(  float hw_du_u,
                              float i_rad,
                              float hw_n_motor,
                              float hw_dr_ou,
                              float hw_s_luftkal_o,
                              float hw_s_luftkal_u,
                              float v_gl_fak_hw_p,
                              float *hw_v_dv0);

      //---------------------------------------------------------------------------
      // Methode: RAW_T_CNC::Vorform_Hoehe_Variabel
      // Aufgabe: Berechne Vorformhoehe aus radialer Breitung, wenn noch kein AW-Kontakt
      //---------------------------------------------------------------------------
      int Vorform_Hoehe_Variabel(struct   Def_Form		form_ring,
                                 float    n_omega_tu,
                                 float    zeit_walzen,
                                 float    form_mess_start_dis_hw_dw,
                                 float    form_mess_mf_dis_hw_dw,
                                 float    ufz_rad_mf_delta_s,
                                 float    hw_geometrie_d_nenn,
                                 float    dw_geometrie_d_nenn,
                                 float    vorform_hm,
                                 int      mit_breitung_rad_flag,
                                 float    *vorform_hoehe_variabel,
                                 int      msg_flag);

      //---------------------------------------------------------------------
      // Methode: RAW_T_CNC::Vorwalzen
      // Aufgabe:
      //---------------------------------------------------------------------
      int Vorwalzen(  int     walzen_start_flag,
                      int     maschine_mit_vorwalzen_flag,
                      float   maschine_anzahl_ringumdrehungen,
                      int     vorwalzen_ende_taster_flag,
                      float   rwg_max,
                      float   v_hw,  
                      float   vorform_da,  
                      float   walz_zeit,
                      int     *vorwalzen_ende_flag,
                      float   *rwg_max_vorwalzen,
                      float   *v_hw_vorwalzen);

      //---------------------------------------------------------------------
      // Methode RWW_T::Walzphasen_flags
      // Aufgabe: 
      //---------------------------------------------------------------------
      int Walzphasen_flags(float    du_ref,
                           struct   Def_Form_Mess form_mess,
                           struct   Def_Form_Mess form_mess_start,
                           float    h_ekv,
                           float    h_vorform,
                           float    h_walzform,
                           float    s_ekv,
                           float    s_walzform,
                           float    du_lf,
                           float    pos_laser_u,
                           float    schlupf_u_pos_laser_osp,
                           float    fr,
                           float    fr_kommi_nenn,
                           float    fr_erkannt_p,
                           float    fa,
                           float    fa_kommi_nenn,
                           float    fa_erkannt_p,
                           float    n_hw_motor_soll,
                           float    n_hw_motor_soll_0,
                           float    zeit_walzen,
                           int      walz_modus,
                           int      cnc_flag,
                           int      sw_zuerst_fertig_flag,
                           int      aufwalzen_bis_ekv_flag,
                           int      taster_aw_manu_gelueftet,
                           int      walzenstart_flag,
                           int      test_walzen_ohne_ring_flag,
                           int      aw_ueberdeckung_check_flag,
                           int      rpt_1_walzung_flag,              // Flag, 1. Walzung Radialprofil Walzen [0,1] 
                           int      rpt_2_walzung_flag,              // Flag, 2. Walzung Radialprofil Walzen [0,1] 
                           int      *zaehler_auto_gelueftet,
                           struct   Def_Walzphase  *walzphase,
                           int      *h_ekv_erreicht_flag,
                           int      *s_ekv_erreicht_flag);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::WP_Querschnitte
      // Aufgabe:
      //---------------------------------------------------------------------------
      int WP_Querschnitte( float  dr_HW_ou,  
                           float  dr_DW_ou,
                           float  s_Luft_Kal_HW_o,
                           float  s_Luft_Kal_HW_u,
                           float  s_Luft_Kal_DW_o,  
                           float  s_Luft_Kal_DW_u,  
                           struct Def_Form_Mess form_mess,
                           struct Def_Walzprodukt *wp);

      //---------------------------------------------------------------------------
      // Methode: RWW_T::Zentrierkraft_zulaessig
      // Aufgabe: Bestimmt zulaessig Zentrierkraft am Ring und im Zylinder;
      //---------------------------------------------------------------------------
      int Zentrierkraft_zulaessig(  float    za_f_zyl_max,                 // Maximale Zentrierkraft im Zylinder (100 %)   [N]
                                    float    za_f_regelreserve_proz,
                                    float    za_hebelverhaeltnis,          // Hebelverhaeltnis                              [-]
                                    struct   Def_Form  form_ring_u,
                                    float    handrad_korrektur,            // Wert Poti oder Handrad           [von -1 bis +1]
                                    float    dt_zyklus,                    // Zykluszeit   [s]
                                    float    t1_glaettung_d,               // Glaettungszeit   Durchmesser                  [s]
                                    float    t1_glaettung_handrad_klein,   // Glaettungszeit   Handrad zu kleinen Werte     [s]
                                    float    t1_glaettung_handrad_gross,   // Glaettungszeit   Handrad zu grossen Werte     [s]
                                    float    h_kal_hw_u,
                                    float    t_kal_hw_u,
                                    float    kf_Wert_bezug,
                                    int      lueften_axial_flag,           // Lueften Kegelwalzen aktiv                     [0,1]
                                    int      start_flag,                   // Start Schalter Initialsierung Glaettung       [0,1]
                                    int      walz_modus,
                                    float    *za_f_zyl_zulaessig_einzeln,  // Zulaessige Zentrierkraft im Zylinder einzeln  [N]
                                    float    *za_f_zyl_zulaessig_summe,    // Zulaessige Zentrierkraft im Zylinder Summe    [N]
                                    float    *za_f_ring_zulaessig,         // Zulaessige Zentrierkraft am Ring              [N]
                                    float    *za_f_zyl_max_nutz);

      //---------------------------------------------------------------------------
      // Methode: RAW_T_CNC::Zuerst_deltas_wst_funktion
      // Aufgabe: Bestimme Hauptanpassungswalzspalt
      //---------------------------------------------------------------------------
      int Zuerst_deltas_wst_funktion(  int   radial_walzen_flag,
                                       int   aw_kontakt_flag,
                                       //int   um_ekv_10proz_flag,
                                       //int   sw_zuerst_fertig_flag,
                                       int   f_axial_begrenzung_flag,
                                       float fakq,
                                       int   *zuerst_deltas_wst_flag);

/*
      //---------------------------------------------------------------------
      // Methode: RAW_T_CNC::R_Form_aus_D_Form
      // Aufgabe: 
      //---------------------------------------------------------------------
      int R_Form_aus_D_Form(  struct   Def_Form    form_ring,
                              struct   Def_R_Form  *WP_RForm);
*/

      class CPP_T_M cpp_t_m;
      class CPP_T_P cpp_t_p;
      class UFT_T   uft_t;
      class UFM_T   ufm_t;
   };

#endif

