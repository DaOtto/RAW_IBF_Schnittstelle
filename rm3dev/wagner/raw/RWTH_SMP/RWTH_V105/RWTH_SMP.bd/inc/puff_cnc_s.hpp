#ifndef _PUFF_CNC_S_HPP
   #define _PUFF_CNC_S_HPP

   #include "uftcncs.hpp"
   #include "raw_t_cnc_s.hpp"
   #include "apwcncs.hpp"

   #define EPS_POS          0.1F     // Minimales Inkrement Position
   #define ISTANZ_RU_MAX    48       // Maximale Anzahl Speicherwerte
   #define NLIM             50       // Maximale Groesse Speicherbuffer

   #define MAX_WERTE_1RU         NLIM

   #define L_GEDRUECKT_MIN       10.0F

   #define T1_DA                 10.0F
   #define T1_LA                 10.0F

   #define T1_FA                 0.0F
   #define T1_FR                 0.0F
   #define T1_FAG                0.0F

   #define T1_HW_STROM           0.0F
   #define T1_AW_STROM           0.0F

   #define T1_MA                 0.0F
   #define T1_MR                 0.0F

   #define T1_DELTA_H            1.0F
   #define T1_DELTA_S            1.0F

   #define T1_KW_KRAFT           1.5F
   #define T1_KW_MOMENT          1.5F

   #define T1_DP                 2.0F

   #define T1_VOLUMEN            5.0F
   #define T1_VOLUMEN_FLANSCH    2.0F
   #define T1_VOLUMEN_VS         2.0F

   #define T1_SYSTEMDRUCK        2.0F

   #undef DAEMPFER
   //#define DAEMPFER

#ifdef DAEMPFER
   #include "rwwtdaem.h"
#endif

   //---------------------------------------------------------------------------
   // Struktur Def_Ein_Puff
   //---------------------------------------------------------------------------
   struct Def_Ein_Puff
   {
      // Wahlschalter
      int      abschalt_modus;                  // Abschaltmodus [Aussen,Mitte,Innen]
      int      endphase_flag;                   // Flag, Endphase [0,1]
      int      walzenstart_flag;                // Flag, Walzenstart [0,1]
      int      sw_zuerst_fertig_flag;           // Wanddicke zuerst fertig [0,1] 
      int      taster_aw_manu_gelueftet_flag;   // Taster Axialwalze manuell gelueftet [0,1]
      int      ws_d_lauf_flag;                  // Modus Referenzdurchmesser [Aussen,Mitte,Innen]
      int      walz_modus;                      // Walzmodus [0 bis 5]
      int      stuetzstellen_anwenden_flag;
      int      volumenberechnung_flag;          // Nur CNC: Flag, mit Bererechnung Volumen [0,1]
      int      msg_flag;                        // Ausgabe einer Message-Box [0,1]
      int      cnc_flag;                        // Puffer fuer CNC [0,1]
      int      kw_testbetrieb_flag;             // Flag, gesetzte Umformwiderstaende [0,1]
      int      test_walzen_ohne_ring_flag;
      int      aufwalzen_bis_ekv_flag;
      int      mit_breitung_flag;
      int      power_taster_flag;               // Flag, Powertaster gedrückt [0,1]   
      int      keine_verteilung_hoehe_neg_voldiff_flag; // Keine Verteilung in die Hoehe wenn Volumendifferenz negativ [0,1]
      int      aw_ueberdeckung_check_flag;
      
      // Prozessdynamik
      float    dt_zyklus;                       // Nur CNC: Zeitinkrement [s]
      float    zeit_walzen;                     // Nur CNC: Walzzeit [s]
      float    n_hw_motor_soll;                 // Variable Solldrehzahl Hauptwalzenmotoren [1/s]
      float    n_hw_motor_soll_0;               // Vorgabewert Handrad Solldrehzahl Hauptwalzenmotoren [1/s]
      float    n_hw_motor_ist;                  // Istdrehzahl Hauptwalzenmotoren [1/s]
      float    n_awo_motor_ist;                 // Istdrehzahl Axialwalzenmotoren oben [1/s]
      float    n_awu_motor_ist;                 // Istdrehzahl Axialwalzenmotoren unten [1/s]
      float    v_gl_fak_hw_p;
      float    v_gl_fak_axi_p;
      float    d_hw_dv0_carwin;                 // Geschwindigkeitsdurchmesser von CARWIN

      // Drehzahlen
      float    dv_Grundvertrim_ou_p;            // Grundvertrimmung oben zu unten [%]

      // Laserposition für Grunddrehzahl Axialwalzen
      float    t1_glaettung_vor_pos_laser_aw_n0;
      float    t1_glaettung_zurueck_pos_laser_aw_n0;

      // Messwerte Ringgeometrie
      struct   Def_Form_Mess   form_mess_of;    // Aktuelle Messwerte ungefiltert
      struct   Def_Form_Mess   form_mess_start; // Messwerte bei Walzenstart
      float    da_id;
      float    pos_laser_u_of;                  // Position Laser ungefiltert [mm]
      float    pos_laser_id;

      // Messebene
      struct   Def_Mess_Ebene mess_ebene;       // Messebene Laser

      // Geometrien
      struct   Def_Form vorform;                // Soll Vorform
      struct   Def_Form soll_walzform;          // Soll Walzform

      // Kraefte
      float    fa_of;                           // Nur CNC: Axiale Kraft ohne Filter [N]
      float    fr_of;                           // Nur CNC: Radiale Kraft ohne Filter [N]
      float    fag_of;                          // Nur CNC: Kraft Axialgeruest ohne Filter [N]

      float    fa_kommi_nenn;                   // gesetzte kommissionierte axiale Kraft bei Nenndruck [N]
      float    fr_kommi_nenn;                   // gesetzte kommissionierte radiale Kraft bei Nenndruck [N]

      float    fr_erkannt_p;                    // Radiale Kraft erkannt [%]
      float    fa_erkannt_p;                    // Axiale Kraft erkannt  [%]

      // Ist Systemdruecke
      float    p_system_a_of;                   // Ist Systemdruck axial ohne Filter  [N/mm^2]
      float    p_system_r_of;                   // Ist Systemdruck radial ohne Filter [N/mm^2]

      // Stroeme
      float    hw1_i_of;                        // Nur CNC: Strom Hauptwalzenmotor 1 ungefiltert [A]
      float    hw2_i_of;                        // Nur CNC: Strom Hauptwalzenmotor 2 ungefiltert [A]
      float    awo_i_of;                        // Nur CNC: Strom Axialwalzenmotor oben  ungefiltert [A]
      float    awu_i_of;                        // Nur CNC: Strom Axialwalzenmotor unten ungefiltert [A]

      // Umformwiderstaende
      struct   Def_kw_fr_fa_mr_ma kw_fr_fa_mr_ma_test;   // Umformwiderstaende Testbetrieb [N/mm2]

      // Werkzeuge
      struct   Def_Walzen_Geo hw_geometrie;     // Hauptwalzengeometrie
      struct   Def_Walzen_Geo dw_geometrie;     // Dornwalzengeometrie
      struct   Def_AW_Geo     awo_geometrie;    // Axialwalzengeometrie unten
      struct   Def_AW_Geo     awu_geometrie;    // Axialwalzengeometrie unten

      struct   Def_Schlupf    schlupf_u;        // Schlupfgrößen

      float    deltad_ekv;                      // delta Durchmesser fuer EKV vor Fertigdurchmesser [mm]
      float    deltad_lf_nach_ekv;              // delta Durchmesser fuer Lueften nach EKV [mm]
      float    lueftmass_auto_as;               // Lueftmass bei automatischem Lueften der Axialwalze [mm]

      // Volumenverteilung
      float    volvertverha;                    // Volumenverteilungsverhaeltnis [0,10]

      // Motorendaten
      struct   Def_Maschine_Motor hw1_motor;    // Hauptwalze 1 Motordaten
      struct   Def_Maschine_Motor hw2_motor;    // Hauptwalze 2 Motordaten
      struct   Def_Maschine_Motor awo_motor;    // Axialwalze oben Motordaten
      struct   Def_Maschine_Motor awu_motor;    // Axialwalze unten Motordaten

      // Online
      float    delta_durchmesser_nru;
      float    tu_nru;

      long     nummer;                            // 

      // Axialprofilwalzen
      int      Dorn_Messung_flag;                 // Dorn ist unten, Wanddicke gültig [0,1]              

      struct   Def_Walzen_Geo dr_geometrie;       // Druckrollengeometrie
      double   disy_dr_achsen_halbe;              // Halber Abstand der Druckrollenmittelpunkte [mm]

      struct   Def_AW_Geo_profiliert awo_geo_profiliert;
      struct   Def_AW_Geo_profiliert awu_geo_profiliert;

      double   y_be_basis;

      struct   Def_APW_dif_Da_di_h   dif_Vorform;  // Unterschied Ist zu Soll Vorform
      int      dif_Vorform_merker;                 // Daten dif_Vorform erhalten

      double   y_oberkante_awu_aps;
      struct   Def_APW_OUMIA   dy_awou_p;

      struct   Def_APW_OUMIA   dhWP_VS;

      struct   Def_dhzuds_Set dhzuds_set;

      // Vorform Soll
      struct   Def_Vol_WP              vorform_Vol_WP;
      struct   Def_APW_Iter_werte      vorform_Iter_VS;
      struct   Def_dh_luft_ou          vorform_dh_luft_ou;

      // Vorform Ist
      struct   Def_Form                ist_vorform;
      struct   Def_Vol_WP              istvorform_Vol_WP;
      struct   Def_dh_luft_ou          istvorform_dh_luft_ou;
      
      // Gemessene Form of Filter
      struct   Def_Vol_WP              form_mess_of_Vol_WP;
      struct   Def_dh_luft_ou          form_mess_of_dh_luft_ou;
      struct   Def_Zwischenform_Iter   form_mess_of_Iter_Z;     

      // Walzform Soll
      struct   Def_dh_luft_ou          soll_walzform_dh_luft_ou;
      struct   Def_Vol_WP              soll_walzform_Vol_WP;
   };

//---------------------------------------------------------------------------
// Struktur Def_Aus_Puff
//---------------------------------------------------------------------------
   struct Def_Aus_Puff
   {

#ifdef WIN32 // Wegen ONLI_CNC::Axialgerüst
      float    pos_rs_achse;       
      float    pos_rs_achse_start; 
      float    pos_wp_achse;       
      float    pos_wp_achse_start; 
#endif

      // Schalter
      struct   Def_Walzphase   walzphase;       // Walzphasen

      // Ringgeometrien
      struct   Def_Form         ist_walzform;   // Ringgeometrie Ist-Walzform
      struct   Def_Form         form_ring;      // Aktuelle Ringgeometrie
      struct   Def_Form_Mess    form_mess_mf;   // Aktuelle Messwerte gefiltert
      float    vorform_hoehe_variabel;          // sich durch radiale Breitung ändernde Höhe
      int      di_vorhanden_flag;               // Flag ob Innendurchmesser vorhanden

      struct   Def_Ufz_Rad      ufz_rad_mf;     // Groessen Umformzone radial
      struct   Def_Ufz_Axi      ufz_axi_mf;     // Groessen Umformzone axial

      float    pos_laser_u_mf;                  // Position Laser gefiltert               [mm]
      float    pos_laser_mit_spitze_u_mf;       // Position mit Spitze Laser gefiltert    [mm]
      float    pos_laser_mit_spitze_u_of;       // Position mit Spitze Laser ungefiltert  [mm]
      float    pos_laser_mit_spitze_u_mf_start; // Position mit Spitze Laser gefiltert    [mm]

      float    h0r;                             // Einlaufende Hoehe radial               [mm]
      float    h1r;                             // Auslaufende Hoehe radial               [mm]
      float    h0a;                             // Einlaufende Hoehe axial                [mm]
      float    h1a;                             // Auslaufende Hoehe axial                [mm]

      float    s0r;                             // Einlaufende Wanddicke radial           [mm]
      float    s1r;                             // Auslaufende Wanddicke radial           [mm]
      float    s0a;                             // Einlaufende Wanddicke axial            [mm]
      float    s1a;                             // Auslaufende Wanddicke axial            [mm]

      float    h_ekv;                           // Ringhoehe bei EKV                      [mm]
      float    s_ekv;                           // Wanddicke bei EKV                      [mm]

      struct   Def_Walzprodukt wp;

      float    wp_pos_ra_1a_ms_hori_u;
      float    wp_aw_n_pos_ra_1a_ms_hori_u;

      // Lueften
      struct   Def_lueften_as   lueften_as;

      
      // Luft im Kaliber
      float    s_Luft_Kal_DW_o;
      float    s_Luft_Kal_DW_u;

      float    s_Luft_Kal_HW_o;
      float    s_Luft_Kal_HW_u;

      // Breitung, Abnahmen
      float    delta_h_mf;                      // Abnahme axial gefiltert                [mm]
      float    delta_s_mf;                      // Abnahme radial gefiltert               [mm]

      // Ringwachsgeschwindigkeiten
      float    dpa_mf;                          // Ringwachsgeschw. Bezug Da              [mm/s]
      float    dpi_mf;                          // Ringwachsgeschw. Bezug Di              [mm/s]
      float    dpm_mf;                          // Ringwachsgeschw. Bezug Dm              [mm/s]

      float    v1r_mw;
      float    v1a_mw;

      // Drehzahlen
      float    pos_laser_aw_n_mit_spitze_u_mf;
      struct   Def_n_omega            n_omega;

      // Werkzeuge
      struct   Def_du_HW_DW_3Segm   du_hw_dw_3segm;
      struct   Def_h_3Segm          h_3segm;

      // Umformwiderstaende
      struct   Def_kw_fr_fa_mr_ma kw_fr_fa_mr_ma_mf; // Umformwiderstaende gefiltert      [N/mm2]

      // Fiktive arbeitende Radien
      float    rr_mw;                           // Mittlerer arbeitender Radius radial    [mm]
      struct   Def_Radien_Axial   radien_axial;

      float    dvol_ring_proz;                  // Ringvolumendifferenz                   [%]
      float    vol_ring_mf;                     // Ringvolumen                            [mm^3]
      float    vol_ring_mf_anzeige;             // Ringvolumen anzeige                    [mm^3]   
      float    symmetrie_faktor;                // Symmetriefaktor Ringgeschwindigkeit    [-]

      // Kraefte
      float    fr_mf;                           // Radiale Kraft gefiltert                [N]
      float    fa_mf;                           // Axiale Kraft gefiltert                 [N]

      // Momente
      float    mr_nenn_gesamt; 
      float    ma_nenn_gesamt;
      float    mr_mf;                           // Radiales Moment gefiltert              [Nmm]
      float    ma_mf;                           // Axiales Moment gefiltert               [Nmm]

      // Ist Systemdruecke
      float    p_system_a_mf;                   // Ist Systemdruck axial mit Filter       [N/mm^2]
      float    p_system_r_mf;                   // Ist Systemdruck radial mit Filter      [N/mm^2]

      // Breitung
      int      mit_breitung_rad_flag;           // Flag, Berechnung mit radialer Breitung [0,1]
      int      mit_breitung_axi_flag;           // Flag, Berechnung mit axialer Breitun   [0,1]

#ifdef DAEMPFER
      struct   Def_Daempfer daempfer;
#endif

      int      istanz_ru;                       // Alle wieviel Zyklen wird eine Messwert aufgenommen (aktueller Wert)

      // Axialprofilwalzen
      struct   Def_Form                opt_vorform;
      struct   Def_Vol_WP              opt_vorform_Vol_WP;
      struct   Def_dh_luft_ou          opt_vorform_dh_luft_ou;

      struct   Def_Form                opt_walzform;
      struct   Def_Vol_WP              opt_walzform_Vol_WP;
      struct   Def_dh_luft_ou          opt_walzform_dh_luft_ou;

      struct   Def_Vol_WP              form_mess_mf_Vol_WP;
      struct   Def_Zwischenform_Iter   form_mess_mf_Iter_Z;     
      struct   Def_dh_luft_ou          form_mess_mf_dh_luft_ou;

      struct   Def_Vol_WP              ist_walzform_Vol_WP;
      struct   Def_Walzform_real_Iter  ist_walzform_Iter_W;
      struct   Def_dh_luft_ou          ist_walzform_dh_luft_ou;

      double   dpos_AG_Start_Vopt;

      double   ram_dv0_APS_o;
      double   ram_APS_o;

      double   ram_dv0_APS_u;
      double   ram_APS_u;

#ifdef SMP16
      double    test1;
      double    test2;
      double    test3;
      double    test4;
      double    test5;
#endif

   };

//---------------------------------------------------------------------------
// Struktur Def_Lokal_Puff
//---------------------------------------------------------------------------
   struct Def_Lokal_Puff
   {
      // Kraefte
      float    fr_min;                          // Minimum Kraft radial    [N]
      float    fr_of_kw;                        // Radiale Kraft ungefiltert für KW-Berechnung [N]

      float    fa_min;                          // Minimum Kraft axial     [N]
      float    fa_of_kw;                        // Axiale Kraft ungefiltert für KW-Berechnung [N]

      float    fag_mf;                          // Kraft Axialgeruest gefiltert [N]


      // Momente
      float    mr_of;                           // Radiales Moment ungefiltert  [Nmm]
      float    mr_min;                          // Minimum Moment radial        [Nmm]
      float    mr_of_kw;                        // Radiales Moment ungefiltert für KW-Berechnung [Nmm]

      float    ma_of;                           // Axiales Moment ungefiltert   [Nmm]
      float    ma_min;                          // Minimum Moment axial         [Nmm]
      float    ma_of_kw;                        // Axiales Moment ungefiltert für KW-Berechnung [Nmm]

      // Ringgeometrie
      float      da_old;                        // Alter Aussendurchmesser [mm]
      float      dm_old;                        // Alter mittl. Durchmesser [mm]
      float      di_old;                        // Alter Innendurchmesser [mm]
      
      float      h1a0;                          // Auslaufende Hoehe axial [mm]
      float      s1r0;                          // Auslaufende Wanddicke radial [mm]
      float      d_fertig;                      // Fertigdurchmesser f(Abschaltmodus) [mm]
      float      vol_ref;                       // Volumen Sollwalzform [mm^3]

      // Abgeleitete Groessen
      float      hw_strom_mf;                   // Strom aller Hauptwalzenmotoren gefiltert [A]
      float      aw_strom_mf;                   // Strom aller Axialwalzenmotoren gefiltert [A]

      // Prozessdynamik
      float      zeit_anwalzen;                 // Anwalzzeit [s]
      float      tu;                            // Zeit fuer eine Ringumdrehung [s]

      // Ringwachsgeschwindigkeiten
      float      dpa_of;                        // Ringwachsgeschw. Bezug da            [mm/s]
      float      dpm_of;                        // Ringwachsgeschw. Bezug dm            [mm/s]
      float      dpi_of;                        // Ringwachsgeschw. Bezug di            [mm/s]
      
      // Abnahmen
      float      delta_s_of;                    // Abnahme radial ungefiltert           [mm]
      float      delta_h_of;                    // Abnahme axial ungefiltert            [mm]

      // Breitungen
      float      deltahr0;
      float      deltasa0;
      float      deltahr_hilf;
      float      deltasa_hilf;

      // Umformwiderstaende
      struct   Def_kw_fr_fa_mr_ma kw_fr_fa_mr_ma_of;      // Umformwiderstaende ungefiltert  [N/mm2]

      float      kwa_ver;                       // Verhaelt. Umformwiderstaende   axial      [-]
      float      kwr_ver;                       // Verhaelt. Umformwiderstaende   radial     [-]

      float      kw_min;                        // Minimum Umformwiderstand [N/mm²]
      float      kw_max;                        // Maximum Umformwiderstand [N/mm²]

      // Puffer intern
      unsigned   char it0;                      // Index auf momentanen Speicher
      signed     char its;                      // Zeitzaehler bis Speicherung

      float      q_ru;                          // Interpolationsfaktor  Ringumdrehung
      float      q_ruh;                         // Interpolationsfaktor  halbe RU

      float      tim_rh0;
      float      tim_rh1;
      float      tim_r0;
      float      tim_r1;

      float      trr;                           // Ringumdrehungszeit
      float      trrh;                          // Halbe Ringumdrehungszeit
      float      umf;                           // Momentaner Ringumfang
      float      umf_sum;                       // Summe der aus dem Radialwalzspalt
                                                // auslaufenden Laenge (Ringumfang)
      float      umfh;                          // Momentaner halber Ringumfang

      float      umf_r0;
      float      umf_r1;
      float      umf_rh0;
      float      umf_rh1;
                                                
      float      deltahr_val[NLIM];             // Speicher Breitung Hoehe Radialwalzspalt
      float      deltasa_val[NLIM];             // Speicher Breitung Wanddicke Axialwalzspalt
      float      h1a_val[NLIM];                 // Speicher Ringhoehe
      float      s1r_val[NLIM];                 // Speicher Wanddicke
      float      tim_val[NLIM];                 // Speicher Zeitwerte
      float      umf_val[NLIM];                 // Speicher Walzgeschwindigkeit

      int        i_pu;
      int        int_ip;
      int        istanz_ru_old;                 // Alle wieviel Zyklen wird eine Messwert aufgenommen (alter Wert)
   };

#endif

