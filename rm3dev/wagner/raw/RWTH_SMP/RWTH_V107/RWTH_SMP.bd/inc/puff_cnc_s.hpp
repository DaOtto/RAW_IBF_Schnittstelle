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
	  /** @var abschalt_modus
	   * @brief Abschaltmodus [Aussen, Mitte, Innen]*/
      int      abschalt_modus;
      /** @var endphase_flag
       * @brief Flag, Endphase [0,1]*/
      int      endphase_flag;                   // Flag, Endphase [0,1]
      /** @var walzenstart_flag
       * @brief Flag, Walzenstart*/
      int      walzenstart_flag;                // Flag, Walzenstart [0,1]
      /** @var sw_zuerst_fertig_flag
       * @brief Wanddicke zuerst fertig [0,1]*/
      int      sw_zuerst_fertig_flag;
      /** @var taster_aw_manu_gelueftet_flag
       * @brief Taster Axailwalze manuell gelueftet [0,1]*/
      int      taster_aw_manu_gelueftet_flag;
      /** @var ws_d_lauf_flag
       * @brief Modus Refernzdurchmesser [Aussen, Mitte, Innen]*/
      int      ws_d_lauf_flag;
      /** @var walz_modus
       * @brief Walzmodus [0,...,5]*/
      int      walz_modus;
      int      stuetzstellen_anwenden_flag;
      /** @var volumenberechnung_flag
       * @brief Nur CNC: Flag, mit Berechnung Volumen [0,1]*/
      int      volumenberechnung_flag;
      /** @var msg_flag
       * @brief Ausgabe einer Message-Box [0-1]*/
      int      msg_flag;
      /** @var cnc_flag
       * @brief Puffer fuer CNC [0,1]*/
      int      cnc_flag;
      /** @var kw_testbetrieb_flag
       * Flag, gesetzte Umformwiderstaende [0,1]*/

      //TODO doxygen comments
      int      kw_testbetrieb_flag;
      int      test_walzen_ohne_ring_flag;

      int      aufwalzen_bis_ekv_flag;

      int      mit_breitung_flag;


      /** @var power_taster_flag
       * @brief Flag, Powertaster gedrueckt [0,1]*/
      int      power_taster_flag;
      /** @var keine_verteilung_hoehe_neg_voldiff_flag
       * @brief keine Verteilung in den Hoehe wenn Volumendifferenz negativ [0,1]*/
      int      keine_verteilung_hoehe_neg_voldiff_flag;
      int      aw_ueberdeckung_check_flag;

      int      aw_geo_profiliert_1_walzung_drehzahl_flag;
      // Flag, Axialprofilwalzengeometrie fuer Drehzahlberechnung 1. Walzung verwenden [0,1]
      
      // Prozessdynamik
      /** @var dt_zyklus
       * @brief Nur CNC: Zeitinkrement [s]*/
      float    dt_zyklus;
      /** @var zeit_walzen
       * @brief Nur CNC: Walzzeit in [s]*/
      float    zeit_walzen;
      /** @var n_hw_motor_soll
       * @brief Solldrehzahl der Hauptwalzmotoren in [1/s]*/
      float    n_hw_motor_soll;
      /** @var n_hw_motor_soll_0
       * @brief Worgabewert handrad Solldrehzahl der Hauptwalzmotoren in [1/s]*/
      float    n_hw_motor_soll_0;
      /** @var n_hw_motor_ist
       * @brief Aktuelle Drehzahl der Hauptwalzmotoren in [1/s]*/
      float    n_hw_motor_ist;
      /** @var n_awo_motor_ist
       * @brief Aktuelle Drehzahl des Axailwalzmotors oben in [1/s]*/
      float    n_awo_motor_ist;
      /** @var n_awu_motor_ist
       * @brief Aktuelle Drehzahl des Axialwalzmotors unten in [1/s] */
      float    n_awu_motor_ist;
      float    v_gl_fak_hw_p;
      float    v_gl_fak_axi_p;
      /** @var d_hw_dv0_carwin
       * @brief Geschwindigkeitsdurchmesser von CARWIN*/
      float    d_hw_dv0_carwin;

      // Drehzahlen
      /** @var dv_Grundvertrim_ou_p
       * @brief Grundvertrimmung oben zu unden in [%]*/
      float    dv_Grundvertrim_ou_p;

      // Laserposition für Grunddrehzahl Axialwalzen
      float    t1_glaettung_vor_pos_laser_aw_n0;

      // TODO doxygen comments
      float    t1_glaettung_zurueck_pos_laser_aw_n0;

      // Messwerte Ringgeometrie
      struct   Def_Form_Mess   form_mess_of;
      // Aktuelle Messwerte ungefiltert
      struct   Def_Form_Mess   form_mess_start;
      // Messwerte bei Walzenstart
      struct   Def_Form_Mess   form_mess_mw_vol_of;
      // Aktuelle Messwerte Mittelwert Volumen ungefiltert
      float    da_id;
      /** @var pos_laser_u_of
       * @brief Position des Laser ungefiltert in [mm]*/
      float    pos_laser_u_of;

      // TODO doxygen comments
      float    pos_laser_id;

      // Messebene
      /** @var mess_ebene
       * @brief Strucktur vom Typ \link Def_Mess_Ebene \endlink Informationen ueber die Position
       * der Lasermessebene enthaelt*/
      struct   Def_Mess_Ebene mess_ebene;       // Messebene Laser

      // Geometrien
      /** @var vorform
       * @brief Struktur vom Typ \link Def_Form \endlink enhaelt Informationen ueber die
       * Soll-Ringgeormetrie der Vorform*/
      struct   Def_Form vorform;                // Soll Vorform
      /** @var soll_walzform
       * @brief Struktur vom Typ \link Def_Form \endlink enthaelt Informationen ueber die
       * Soll-Ringgeometrie der Walzform*/
      struct   Def_Form soll_walzform;          // Soll Walzform

      // Kraefte
      /** @var fa_of
       * @brief Nur CNC: Axiale Kraft ohne Filter in [N]*/
      float    fa_of;                           // Nur CNC: Axiale Kraft ohne Filter [N]
      /** @var fr_of
       * @brief Nur CNC: Radiale Kraft ohne Filter in [N]*/
      float    fr_of;                           // Nur CNC: Radiale Kraft ohne Filter [N]
      /** @var fag_of
       * @brief Nur CNC: Kraft Axialgeruest ohne Filter in [N]*/
      float    fag_of;                          // Nur CNC: Kraft Axialgeruest ohne Filter [N]

      /** @var fa_kommi_nenn
       * @brief Gesetzte kommisionierte axiale Kraft bei Nenndruck in [N]*/
      float    fa_kommi_nenn;                   // gesetzte kommissionierte axiale Kraft bei Nenndruck [N]
      /** @var fr_kommi_nenn
       * @brief gesetzte kommisionierte radiale Kraft bei Nenndruck in [N]*/
      float    fr_kommi_nenn;                   // gesetzte kommissionierte radiale Kraft bei Nenndruck [N]

      /** @var fr_erkannt_p
       * @brief Radiale Kraft erkannt in [%]*/
      float    fr_erkannt_p;                    // Radiale Kraft erkannt [%]
      /** fa_erkann
       * @brief Axiale Kraft erkannt in [%]*/
      float    fa_erkannt_p;                    // Axiale Kraft erkannt  [%]

      // Ist Systemdruecke
      /** @var p_system_a_of
       * @brief Ist-Systemdruck axial ohne Filter in [N/mm^2]*/
      float    p_system_a_of;
      /** @var p_system_r_of
       * @brief Ist-Systemdruck radial ohne Filter [N/mm^2]*/
      float    p_system_r_of;

      // Stroeme
      /** @var hw1_i_of
       * @brief Nur CNC: Strom am Hauptwalzmotor 1 ungefiltert in [A]*/
      float    hw1_i_of;
      /** @var hw2_i_of
       * @brief Nur CNC: Strom am Hauptwalzmotor 2 ungefiltert in [A]*/
      float    hw2_i_of;
      /** @var awo_i_of
       * @brief Nur CNC: Strom am Axialwalzmotor oben ungefiltert in [A]*/
      float    awo_i_of;
      /** @var awu_i_of
       * @brief Nur CNC: Strom Axialwalzmotor unten ungefiltert in [A]*/
      float    awu_i_of;


      // Umformwiderstaende
      /** @var kw_fr_fa_mr_ma_test
       * @brief Enhaelt Informationen ueber die Umformwiederstaende in [N/mm^2].
       * Struktur vom Typ \link Def_kw_fr_fa_mr_ma \endlink enthaelt Informatioenn ueber
       * die radial und axiale Kraft, sowie radiales als auch axiales Moment an der Kegelwalze*/
      struct   Def_kw_fr_fa_mr_ma kw_fr_fa_mr_ma_test;   // Umformwiderstaende Testbetrieb [N/mm2]


      // Werkzeuge

      /** @var hw_geometrie
       * @brief Struktur vom Typ \link Def_Walzen_Geo \endlink enthealt Informationen ueber
       * die Geometrie der verwendete Hauptwalze*/
      struct   Def_Walzen_Geo hw_geometrie;     // Hauptwalzengeometrie
      /** @var dw_geometrie
       * @brief Struktur vom Typ \link Def_Walzen_Geo \endlink enthealt Informationen ueber
       * die Geometrie der verwendeten Dornwalze*/
      struct   Def_Walzen_Geo dw_geometrie;     // Dornwalzengeometrie
      /** @var awo_geometrie
       * @brief Struktur vom Typ \link Def_AW_Geo \endlink enthealt Informationen ueber die
       * Geometrie der verwendeten Axialwalze oben*/
      struct   Def_AW_Geo     awo_geometrie;    // Axialwalzengeometrie unten
      /** @var awu_geometrie
       * @brief Struktur vom Typ \link Def_AW_Geo \endlink enthealt Informationen ueber die
       * Geometrie der verwendeten Axialwalze oben*/
      struct   Def_AW_Geo     awu_geometrie;    // Axialwalzengeometrie unten


      /** @var schlupf_u
       * @brief Struktur vom Typ \link Def_Schlupf \endlink enthealt Informationen ueber die
       * Schlupfgroessen*/
      struct   Def_Schlupf    schlupf_u;        // Schlupfgrößen

      /** @var deltad_ekv
       * @brief Durchmesser fuer EKV vor Fertigdurchmesser in [mm]*/
      float    deltad_ekv;                      // delta Durchmesser fuer EKV vor Fertigdurchmesser [mm]
      /** @var deltad_lf_nach_ekv
       * @brief delta Durchmesser fuer Lueften nach EKV in [mm]*/
      float    deltad_lf_nach_ekv;              // delta Durchmesser fuer Lueften nach EKV [mm]
      /** @var lueftmass_auto_as
       * @brief Lueftmass bei automatischem Lueften der Axialwalzen in [mm]*/
      float    lueftmass_auto_as;               // Lueftmass bei automatischem Lueften der Axialwalze [mm]


      // Volumenverteilung
      /** @var volvertverha
       * @brief Volumenverteilungsverhealtnis [0,10]*/
      float    volvertverha;                    // Volumenverteilungsverhaeltnis [0,10]


      // Motorendaten
      /** @var hw1_motor
       * @brief Struktur vom Typ \link Def_Maschine_Motor \endlink die Daten ueber
       * den Hauptwalzmotor 1 enthealt*/
      struct   Def_Maschine_Motor hw1_motor;
      /** @var hw2_motor
       * @brief Struktur vom Typ \link Def_Maschine_Motor \endlink die Daten ueber
       * den Hauptwalzmotor 2 enthealt*/
      struct   Def_Maschine_Motor hw2_motor;
      /** @var awo_motor
       * @brief Struktur vom Typ \link Def_Maschine_Motor \endlink die Daten uber
       * den Axialwalzmotor oben enthaelt*/
      struct   Def_Maschine_Motor awo_motor;
      /** @var awu_motor
       * @brief Struktur vom Typ \link Def_Maschine_Motor \endlink die Daten ueber
       * den Axialwalzmotor unten enthaelt*/
      struct   Def_Maschine_Motor awu_motor;


      // TODO doxygen comments
      // Online
      float    delta_durchmesser_nru;
      float    tu_nru;

      long     nummer;


      // Axialprofilwalzen
      /** @var Dorn_Messung_flag
       * @brief Dorn ist unten, Wanddicke gueltig [0,1]*/
      int      Dorn_Messung_flag;                 // Dorn ist unten, Wanddicke gültig [0,1]              

      /** @var dr_geometrie
       * @brief Struktur vom Typ \link Def_Walzen_Geo \endlink enthaelt Informationen ueber
       * die Druckrollengeometrie*/
      struct   Def_Walzen_Geo dr_geometrie;       // Druckrollengeometrie
      /** @var disy_dr_achsen_halbe
       * @brief Halber Abstand der Druckrollenmittelpunkte in [mm]*/
      double   disy_dr_achsen_halbe;


      /** @var awo_geo_profiliert
       * @brief Struktur vom Typ \link Def_AW_Geo_profiliert \endlink enthaelt Daten uber
       * die Geometrie der Axialwalze oben, die profiliert*/
      struct   Def_AW_Geo_profiliert awo_geo_profiliert;
      /** @var awu_geo_profiliert
       * @brief Struktur vom Typ \link Def_AW_Geo_profiliert \endlink enthaelt Daten uber
       * die Geometrie der Axialwalze unten, die profiliert*/
      struct   Def_AW_Geo_profiliert awu_geo_profiliert;

      // TODO doxygen comments
      double   y_be_basis;

      /** @var dif_Vorform
       * @brief Struktur vom Typ \link Def_APW_dif_Da_di_h \endlink die Informationen ueber
       * die Differenz der Ist- und Soll-Vorform enthealt*/
      struct   Def_APW_dif_Da_di_h   dif_Vorform;  // Unterschied Ist zu Soll Vorform
      /** @var dif_Vorform_merker
       * @brief Daten dif_Vorform erhalten*/
      int      dif_Vorform_merker;                 // Daten dif_Vorform erhalten

      double   y_awu_kante_mitte_aps;
      double   y_awu_kante_innen_aps;
      double   y_awu_kante_aussen_aps;
      double   y_awu_kante_max_aps;
      double   y_awu_kante_min_aps;

      struct   Def_APW_OUMIA   dy_awou_p;

      struct   Def_APW_OUMIA   dhWP_VS;

      struct   Def_dhzuds_Set dhzuds_set;

      // TODO doxygen comments
      // Vorform Soll
      struct   Def_Vol_WP              vorform_Vol_WP;
      struct   Def_APW_Iter_werte      vorform_Iter_VS;
      struct   Def_dh_luft_ou          vorform_dh_luft_ou;

      // TODO doxygen comments
      // Vorform Ist
      struct   Def_Form                ist_vorform;
      struct   Def_Vol_WP              istvorform_Vol_WP;
      struct   Def_dh_luft_ou          istvorform_dh_luft_ou;
      
      // TODO doxygen comments
      // Gemessene Form of Filter
      struct   Def_Vol_WP              form_mess_of_Vol_WP;
      struct   Def_dh_luft_ou          form_mess_of_dh_luft_ou;
      struct   Def_Zwischenform_Iter   form_mess_of_Iter_Z;     

      // TODO doxygen comments
      // Walzform Soll
      struct   Def_dh_luft_ou          soll_walzform_dh_luft_ou;
      struct   Def_Vol_WP              soll_walzform_Vol_WP;

      //double   dvol_WPa_korr_fak;

      double   du_FS_Pos_faktor_oben;
      double   du_FS_Pos_faktor_oben_min;
      double   du_FS_Pos_faktor_oben_max;
      double   ds_dh_iterfaktor;

      int      du_FS_nimmt_zu_mit_zwei_VK;
   };

//---------------------------------------------------------------------------
// Struktur Def_Aus_Puff
//---------------------------------------------------------------------------
   struct Def_Aus_Puff
   {
      float    pos_rs_achse;       
      float    pos_rs_achse_start; 
      float    pos_wp_achse;       
      float    pos_wp_achse_start; 

      // Schalter
      struct   Def_Walzphase   walzphase;       // Walzphasen

      // Ringgeometrien
      struct   Def_Form         ist_walzform;
      // Ringgeometrie Ist-Walzform
      struct   Def_Form         form_ring;
      // Aktuelle Ringgeometrie
      struct   Def_Form_Mess    form_mess_mf;
      // Aktuelle Messwerte gefiltert
      struct   Def_Form_Mess    form_mess_mw_vol_mf;
      // Aktuelle Messwerte Mittelwert Volumen gefiltert
      float    vorform_hoehe_variabel;
      // sich durch radiale Breitung ändernde Höhe
      int      di_vorhanden_flag;
      // Flag ob Innendurchmesser vorhanden

      /** @var ufz_rad_mf
       * @brief Struktur vom Typ \link Def_Ufz_Rad \endlink die die Groessen der Umformzone in radialer
       * Richtung enthaelt*/
      struct   Def_Ufz_Rad      ufz_rad_mf;     // Groessen Umformzone radial
      /** @var ufz_axi_mf
       * @brief Struktur vom Typ \link Def_Ufz_Axi \endlink die die Groessen der Umformzone in axialer
       * Richtung enthaelt*/
      struct   Def_Ufz_Axi      ufz_axi_mf;     // Groessen Umformzone axial


      /** @var pos_laser_u_mf
       * @brief Position des Laser gefiltert in [mm]*/
      float    pos_laser_u_mf;                  // Position Laser gefiltert               [mm]
      /** @var pos_laser_mit_spitze_u_mf
       * @brief Position mit Spitze des Lasers ungefiltert in [mm]*/
      float    pos_laser_mit_spitze_u_mf;       // Position mit Spitze Laser gefiltert    [mm]
      /** @var pos_laser_mit_spitze_u_of
       * @brief Position mit Spitze des Lasers ungefiltert in [mm]*/
      float    pos_laser_mit_spitze_u_of;       // Position mit Spitze Laser ungefiltert  [mm]
      /** @var pos_laser_mit_spitze_u_mf_start
       * @brief Position des Lasers mit Spitze gefiltert in [mm]*/
      float    pos_laser_mit_spitze_u_mf_start; // Position mit Spitze Laser gefiltert    [mm]

      /** @var h0r
       * @brief Einlaufende Hoehe radial in [mm]*/
      float    h0r;
      /** @var h1r
       * @brief Auslaufende Hoehe radial in [mm]*/
      float    h1r;
      /** @var h0a
       * @brief Einlaufende Hoehe axial in [mm]*/
      float    h0a;
      /** @var h1a
       * @brief Auslaufende Hoehe axial in [mm]*/
      float    h1a;

      /** @var s0r
       * @brief Einlaufende Wanddicke radial in [mm]*/
      float    s0r;
      /** @var s1r
       * @brief Auslaufende Wanddicke radial in [mm]*/
      float    s1r;
      /** @var s0a
       * @brief Einlaufende Wanddicke axial in [mm]*/
      float    s0a;
      /** @var s1a
       * @brief Auslaufende Wanddicke axial in [mm]*/
      float    s1a;


      /** @var h_ekv
       * @brief Ringhoehe bei EKV in [mm]*/
      float    h_ekv;
      /** @var s_ekv
       * @brief Wanddicke bei EKV in [mm]*/
      float    s_ekv;


      // TODO doxygen comments
      struct   Def_Walzprodukt wp;


      float    wp_pos_ra_1a_ms_hori_u;
      float    wp_aw_n_pos_ra_1a_ms_hori_u;

      // Lueften
      struct   Def_lueften_as   lueften_as;

      // TODO doxygen comments
      // Luft im Kaliber
      float    s_Luft_Kal_DW_o;
      float    s_Luft_Kal_DW_u;

      float    s_Luft_Kal_HW_o;
      float    s_Luft_Kal_HW_u;

      // Breitung, Abnahmen

      /** @var delta_h_mf
       * @brief Abnahme axialschlitten gefiltert in [mm]*/
      float    delta_h_mf;
      /** @var delta_s_mf
       * @brief Abnahme radial gefiltert in [mm]*/
      float    delta_s_mf;


      // Ringwachsgeschwindigkeiten

      /** @var dpa_mf
       * @brief Ringwachsgeschwindigkeit im Bezug auf den Aussenduchmesser in [mm/s]*/
      float    dpa_mf;
      /** @var dpi_mf
       * @brief Ringwachsgeschwindigkeit im Bezug auf den Innendurchmesser in [mm/s]*/
      float    dpi_mf;
      /** @var dpm_mf
       * @brief Ringwachsgeschwindigkeit im Bezug auf Dm in [mm/s]*/
      // TODO Dm nach schlagen !!!!
      float    dpm_mf;                          // Ringwachsgeschw. Bezug Dm              [mm/s]

      // TODO doxygen comments
      float    v1r_mw;
      float    v1a_mw;

      // Drehzahlen
      float    pos_laser_aw_n_mit_spitze_u_mf;
      struct   Def_n_omega            n_omega;

      float    hw_r_dv0_wp;
      // Geschwindigkeitsradius der Hauptwalze     [mm]
      float    wp_r_dv0_hw;
      float    aw_r_dv0_u;
      float    aw_r_dv0_o;
      float    wp_r_dv0_aw_u;
      float    wp_r_dv0_aw_o;

      // Werkzeuge
      struct   Def_du_HW_DW_3Segm   du_hw_dw_3segm;
      struct   Def_h_3Segm          h_3segm;

      // Umformwiderstaende
      struct   Def_kw_fr_fa_mr_ma kw_fr_fa_mr_ma_mf; // Umformwiderstaende gefiltert      [N/mm2]

      // Fiktive arbeitende Radien
      float    rr_mw;                           // Mittlerer arbeitender Radius radial    [mm]
      struct   Def_Radien_Axial   radien_axial;

      /** @var dvol_ring_proz
       * @brief Ringwalzvolumendifferenz in [%]*/
      float    dvol_ring_proz;
      /** @var vol_ring_mf
       * @brief Ringvolumen in [mm^3]*/
      float    vol_ring_mf;
      /** @var vol_ring_mf_anzeige
       * @brief Ringvolumenanzeige in [mm^3]*/
      float    vol_ring_mf_anzeige;
      /** @var symmetrie_faktor
       * @brief Symmetriefaktor Ringgeschwindigkeit in [-]*/
      float    symmetrie_faktor;


      // Kraefte
      /** @var fr_mf
       * @brief Radialkraft gefiltert in [N]*/
      float    fr_mf;
      /** @brief fa_mf
       * @brief Axiale Kraft gefiltert in [N]*/
      float    fa_mf;

      // Momente
      /** @var mr_nenn_gesamt
       * @brief ? Nenndrehmoment radial gesamt ?*/
      float    mr_nenn_gesamt; 
      /** @var ma_nenn_gesamt
       * @brief ? Nenndrehmoment axial gesamt ?*/
      float    ma_nenn_gesamt;
      /** @var mr_mf
       * @brief Radiales Moment gefiltert in [Nmm]*/
      float    mr_mf;
      /** @var ma_mf
       * @brief Axiales Moment gefiltert in [Nmm]*/
      float    ma_mf;


      // Ist Systemdruecke
      /** @var p_system_a_mf
       * @brief Ist Syst
       * emdruck axial mit Filter in [N/mm^2]*/
      float    p_system_a_mf;
      /** @var p_system_r_mf
       * @brief Ist-Systemdruck radial mit Filter in [N/mm^2]*/
      float    p_system_r_mf;


      // Breitung
      /** @var mit_breitung_rad_flag
       * @brief Flag, Berechnung mit Breitung [0,1]*/
      int      mit_breitung_rad_flag;
      /** @var mit_breitung_axi_flag
       * @brief Flag, Berechung mit axialer Breitung [0,1]*/
      int      mit_breitung_axi_flag;

#ifdef DAEMPFER
      struct   Def_Daempfer daempfer;
#endif

      /** @var istanz_ru
       * @brief Alle wieviel Zyklen wird ein Messwert aufgenommen (aktueller Wert)*/
      int      istanz_ru;                       // Alle wieviel Zyklen wird eine Messwert aufgenommen (aktueller Wert)


      // TODO doxygen comments
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

      double    test1;
      double    test2;
      double    test3;
      double    test4;
      double    test5;
   };

//---------------------------------------------------------------------------
// Struktur Def_Lokal_Puff
//---------------------------------------------------------------------------
   struct Def_Lokal_Puff
   {
      // Kraefte
	   /** @var fr_min
	    * @brief Minimale Radialkraft in [N]*/
      float    fr_min;                          // Minimum Kraft radial    [N]
      /** @var fr_of_kw
       * @brief Radiale Kraft ungefiltert fuer KW-Berechung in [N]*/
      float    fr_of_kw;                        // Radiale Kraft ungefiltert für KW-Berechnung [N]

      /** @var fa_min
       * @brief Minimale Axialkraft in [N]*/
      float    fa_min;                          // Minimum Kraft axial     [N]
      /** @var fa_of_kw
       * @brief Axiale Kraft ungefiltert fuer KW-Berechung in [N]*/
      float    fa_of_kw;                        // Axiale Kraft ungefiltert für KW-Berechnung [N]

      /** @var fag_mf
       * @brief Gefilterte Kraft des Axialgeruests in [N]*/
      float    fag_mf;                          // Kraft Axialgeruest gefiltert [N]


      // Momente
      /** @var mr_of
       * @brief Radiales Moment ungefiltert in [Nmm]*/
      float    mr_of;
      /** @var mr_min
       * brief Minimales radiales Moment in [Nmm]*/
      float    mr_min;
      /** @var mr_of_kw
       * @brief Radiales Moment ungefiltert fuer KW-Berechung in [Nmm]*/
      float    mr_of_kw;

      /** @var ma_of
       * @brief Axiales Moment ungefiltert in [Nmm]*/
      float    ma_of;
      /** @var ma_min
       * @brief Minimales Axiales Moment in [Nmm]*/
      float    ma_min;
      /** @var ma_of_kw
       * Axiales moment ungefiltert fuer KW-Berechung in [Nmm]*/
      float    ma_of_kw;


      // Ringgeometrie
      /** @var da_old
       * @brief Alter Aussendruchmesser in [mm]*/
      float      da_old;
      /** @var dm_old
       * @brief Alter mittl. Durchmesser in [mm]*/
      float      dm_old;
      /** @var di_old
       * @brief Alter Innendurchmesser in [mm]*/
      float      di_old;                        // Alter Innendurchmesser [mm]
      
      /** @var h1a0
       * @brief Auslaufende axiale Hoehe in [mm]*/
      float      h1a0;
      /** @var s1r0
       * @brief Auslaufende Wanddicke radial in [mm]*/
      float      s1r0;
      /** @var d_fertig
       * @brief Fertigdurchmesser f(Abschlatmodus) in [mm]*/
      float      d_fertig;
      /** @var vol_ref
       * @brief Volumen Sollwalzform in [mm^3]*/
      float      vol_ref;                       // Volumen Sollwalzform [mm^3]


      // Abgeleitete Groessen
      /** @var hw_strom_mf
       * @brief Strom aller Hauptwalzmotoren gefiltert in [A]*/
      float      hw_strom_mf;
      /** @var aw_strom_mf
       * @brief Strom aller Axialwalzmotoren gefiltert in [A]*/
      float      aw_strom_mf;


      // Prozessdynamik
      /** @var zeit_anwalzen
       * @brief Anwalzzeit in [s]*/
      float      zeit_anwalzen;
      /** @var tu
       * @brief Zeit fuer eine Ringumdrehung*/
      float      tu;                            // Zeit fuer eine Ringumdrehung [s]

      // Ringwachsgeschwindigkeiten
      /** @var dpa_of
       * @brief Ungefilterte Ringwachsgeschwindigkeit im Bezug auf den Aussenringdurchmesser in [mm/s]*/
      float      dpa_of;
      /** @var dpm_of
       * @brief Ungefilterte Ringwachsgeschwindigkeit im Bezug auf den mittl. Durchmesser in [mm/s]*/
      float      dpm_of;
      /** @var dpi_of
       * @brief Ungefilterte Ringwachsgeschwindigkeit im Bezug auf den innen Durchmesser in [mm/s]*/
      float      dpi_of;
      
      // Abnahmen
      /** @var delta_s_of
       * @brief Abname radial ungefiltert in [mm]*/
      float      delta_s_of;
      /** @var delta_h_of
       * @brief Abnahme axial ungefiltert in [mm]*/
      float      delta_h_of;


      // TODO doxygen comments
      // Breitungen
      float      deltahr0;
      float      deltasa0;
      float      deltahr_hilf;
      float      deltasa_hilf;

      // Umformwiderstaende
      /** kw_fr_fa_mr_ma_of
       * @brief Variable der Struktur \link Def_kw_fr_fa_mr_ma \endlink mit Daten ueber die ungefilterten Umformwiderstaende
       * in [N/mm2]*/
      struct   Def_kw_fr_fa_mr_ma kw_fr_fa_mr_ma_of;      // Umformwiderstaende ungefiltert  [N/mm2]

      /** @var kwa_ver
       * @brief Verhaeltnis der Umwiderformstaende in axialer Richtung in [-]*/
      float      kwa_ver;
      /** @var kwr_ver
       * @brief Verhaeltnis der Umformwiderstaende in radialer Richtung in [-]*/
      float      kwr_ver;

      /** @var kw_min
       * @brief Minimum Umformwiderstand [N/mm²]*/
      float      kw_min;
      /** @var kw_max
       * @brief Maximum Umformwiderstand in [N/mm²]*/
      float      kw_max;

      // Puffer intern
      /** @var it0
       * @brief Index auf momentanen Speicher*/
      unsigned   char it0;
      /** @var its
       * @brief Zeitzaehler bis Speicherung*/
      signed     char its;

      /** @var q_ru
       * @brief Interpolationsfaktor Ringumdrehung*/
      float      q_ru;
      /** @var q_ruh
       * interpolationsfaktor halbe Ringumdrehung*/
      float      q_ruh;                         // Interpolationsfaktor  halbe RU

      // TODO doxygen comments
      /** Dient zur Berechung der Ringumdrehungszeit */
      float      tim_rh0;
      float      tim_rh1;
      float      tim_r0;
      float      tim_r1;

      /** @var trr
       * @brief Ringumdrehungzeit*/
      float      trr;                           // Ringumdrehungszeit
      /** @var trrh
       * @brief Halbe Ringumdrehungzeit*/
      float      trrh;
      /** @var umf
       * @brief Momentaner Ringumfang*/
      float      umf;
      /** @var umf_sum
       * @brief Summer der aus dem Radialwalzspalt auslaufenden Laenge (Ringumfang) */
      float      umf_sum;
      /** @var umfh
       * @brief Momentaner halber Ringumfang*/
      float      umfh;

      // TODO doxygen comments
      float      umf_r0;
      float      umf_r1;
      float      umf_rh0;
      float      umf_rh1;

      /** @Ãar deltahr_val[NLIM]
       * @brief Speicher Breitung Hoehe Radialwalzspalt*/
      float      deltahr_val[NLIM];
      /** @var deltasa_val[NLIM]
       * @brief Speicher Breitung Wanddicke Axialwalzspalt*/
      float      deltasa_val[NLIM];
      /** @var h1a_val[NLIM]
       * @brief Speicher Ringhoehe*/
      float      h1a_val[NLIM];
      /** @var s1r_val[NLIM]
       * @brief Speicher Wanddicke*/
      float      s1r_val[NLIM];
      /** @var tim_val[NLIM]
       * @brief Speicher Zeitwerte*/
      float      tim_val[NLIM];
      /** @var umf_val[NLIM]
       * @brief Speicher Walzgeschwindigkeit*/
      float      umf_val[NLIM];

      int        i_pu;
      int        int_ip;
      int        istanz_ru_old;
      // Alle wieviel Zyklen wird eine Messwert aufgenommen (alter Wert)
   };

#endif

