#ifndef _APWCNCS_HPP
	#define _APWCNCS_HPP

   #include "ctmcncs.hpp"

   #define VOL_GENAUIGKEIT 0.0001
   #define DD_GENAUIGKEIT  0.5

   #define WP_ANBINDUNG_ANFANG_MAX 3
   #define WP_KONTUR_I_MAX         5
   #define WP_KONTUR_A_MAX         5
   #define WP_ANBINDUNG_ENDE_MAX   2

   #define ZWISCHENFORM_ITER_MAX    10
   #define VORFORM_IST_OPT_ITER_MAX 10
   #define VORFORM_SOLL_ITER_MAX    10
   #define WALZFORM_REAL_ITER_MAX   10

   struct Def_APW_MIA
   {
      double i;
      double m;
      double a;
   };

   struct Def_APW_INT_MIA
   {
      int i;
      int m;
      int a;
   };

   struct Def_APW_OUMIA
   {
      double o_i;
      double o_m;
      double o_a;
      double u_i;
      double u_m;
      double u_a;
   };

   struct Def_APW_INT_OUMIA
   {
      int o_i;
      int o_m;
      int o_a;
      int u_i;
      int u_m;
      int u_a;
   };

   struct Def_APW_Iter_werte
   {
      double iter;
      double dds_sWP_ges;
      double dds_sWP_i;
      double dds_sWP_a;
      double dif_Vol_WP;
      double dif_Vol_WPi;
      double dif_Vol_WPa;
   };

   struct Def_APW_dif_Da_di_h
   {
      double da;
      double di;
      double hm;
   };

   struct Def_dh_luft_ou
   {
      struct Def_APW_OUMIA     dh_luft_AW; 
      struct Def_APW_MIA       dh_luft_ges;
      struct Def_APW_INT_MIA   Merker_Vollkontakt;
      struct Def_APW_INT_OUMIA Merker_Kontakt;
      int    du_FS_nimmt_zu;
   };

   struct Def_AW_Geo_profiliert
   {
      double dx_Ecke_Profil_innen;
      double dx_Ecke_Profil_aussen;    // Resultierend
      double dx_Breite_Profil_max;
      double dx_Breite_Profil_min;     // Resultierend
      double alpha_Schraege_innen_bo;
      double alpha_Schraege_aussen_bo;
      double dy_Profil_innen;
      double dy_Profil_aussen;
      double dx_Schraege_innen;        // Resultierend
      double dx_Schraege_aussen;       // Resultierend
      double dy_BE_P;
      double l_fehl_spitze;            // Resultierend
      double l_mantel_theo;            // Resultierend
   };

   struct Def_Abgeleitete_Abmessungen
   {
      double hWPo_i;
      double hWPo_m;
      double hWPo_a;
      double sWP_ges;
      double hWPu_i;
      double hWPu_m;
      double hWPu_a;
      double sWPu_i;
      double sWPu_a;
      double sWPo_i;
      double sWPo_a;
      double dhWPo_i;
      double dhWPo_a;
      double dhWPu_i;
      double dhWPu_a;
   };

   struct Def_d_WP_ref_ou
   {
      double d_Fliessscheide_oben;
      double d_Fliessscheide_unten;

      struct Def_APW_OUMIA d_WP_ref;
   };

   struct Def_Da_di_WP
   {
      double Da_WPo;
      double Da_WPu;
      double di_WPo;
      double di_WPu;
   };

   struct Def_Vol_WP
   {
      double Vol_WP;
      double Vol_WP_i;
      double Vol_WP_a;
   };

   struct Def_Halber_Querschnitt_CNC
   {
      double Teil_vol_WP_Kontur_i[WP_KONTUR_I_MAX-2];
      double Teil_vol_WP_Kontur_a[WP_KONTUR_A_MAX-2];
      double Ges_vol_WP_Kontur_i;
      double Ges_vol_WP_Kontur_a;
      double Ges_vol_WP_Kontur;
      struct Def_dxyz Fliessscheide;
   };

   struct Def_Querschnitt_CNC
   {
      struct Def_Halber_Querschnitt_CNC WPo_werte;
      struct Def_Halber_Querschnitt_CNC WPu_werte;
      struct Def_Abgeleitete_Abmessungen Abgeleitete_Abmessungen;
      double y_pos_Unterkante;
      struct Def_Vol_WP Vol_WP;
      struct Def_Form Form;
   };

   struct Def_Walzform_real_Iter
   {
      double   dh_ges_dVol;
      double   ds_ges_W;
      double   ds_sWPa_W;
      double   ds_sWPi_W;
      double   ddh_ges_dVol;
      double   dds_sWPa_W;
      double   dds_sWPi_W;
      double   dh_zu_ds_dVol_iter;
      int      iter;
   };

   struct Def_Walzform_real_dif_Vol_werte
   {
      double   dif_dVol_vergleich;
      double   dif_Vol_WP_W;
      double   dif_Vol_WPi_W;
      double   dif_Vol_WPa_W;
   };

   struct Def_Simu_Messwerte
   {
      double pos_Laser_pseudo_mS;
      double x_pos_AW_Spitze;
      double pos_DR_Achsen_mS;
      double WP_Da;
      double WP_Ra;
      double xWP_Achse;
   };

   struct Def_Zwischenform_Iter
   {
      int      iter_Z;

      double   dds_sWPi_Z;
      double   dds_sWPa_Z;

      double   dif_Vol_WPi_Z;
      double   dif_Vol_WPa_Z;

      double   dif_Vol_WPi_Z_rel;
      double   dif_Vol_WPa_Z_rel;

      double   ddh_hWPo_i_Z;
      double   ddh_hWPu_i_Z;
      double   ddh_hWPo_a_Z;
      double   ddh_hWPu_a_Z;

      struct   Def_APW_OUMIA   delh_werte_Z;
      struct   Def_APW_OUMIA   dels_werte_Z;

      int      Vollkontakt_axial_flag;
      int      Form_Iterieren_flag;

      int      Merker_Vollkontakt_i_Z;
      int      Merker_Kontakt_o_i_Z;   
      int      Merker_Kontakt_u_i_Z; 

      int      Merker_Vollkontakt_a_Z; 
      int      Merker_Kontakt_o_a_Z;   
      int      Merker_Kontakt_u_a_Z;     

      double   hWP_m_Vollkontakt_i_Z;
      double   hWP_m_Vollkontakt_a_Z;
   };

   struct Def_dhzuds_Set
   {
      double Ohne_Kontakt;
      double Teilkontakt;
   };

#endif
