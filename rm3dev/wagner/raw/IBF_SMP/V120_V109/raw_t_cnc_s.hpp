#ifndef _RAW_T_CNC_S_HPP
   #define _RAW_T_CNC_S_HPP

   #include <stdlib.h>

   #include "uftcncs.hpp"

   // Betriebssystem abh�ngige Setzungen
   #ifdef WIN32
      #define CHAR_ANZ_MAX _MAX_PATH
   #else
      #define Version "V110 Rev. 1"
   #endif

//---------------------------------------------------------------------------
// Setzungen
//---------------------------------------------------------------------------
   // Maximale Anzahl der Stuetzstellen
   #define STUETZ_ANZ_MAX 50

   // Abschaltmodi
   #define AB_MOD_AUSSEN 0             // Abschaltung auf Aussendurchmesser      
   #define AB_MOD_MITTE  1             // Abschaltung auf Mitteldurchmesser
   #define AB_MOD_INNEN  2             // Abschaltung auf Innendurchmesser
   #define AB_MOD_FS     3             // APW: Abschaltung auf oberen Fliessscheidendurchmesser

   // Abschaltmodi fuer WS_D_lauf
   #define D_LAUF_MOD_AUSSEN 0         // Abschaltung auf Aussendurchmesser fuer WS_D_lauf      
   #define D_LAUF_MOD_MITTE  1         // Abschaltung auf Mitteldurchmesser fuer WS_D_lauf
   #define D_LAUF_MOD_INNEN  2         // Abschaltung auf Innendurchmesser  fuer WS_D_lauf

   // Walzmodi
   #define WALZ_MOD_RING               0   // Walzmodus Ringe
   #define WALZ_MOD_FLANSCH            1   // Walzmodus Flansche
   #define WALZ_MOD_VOLLSCHEIBE        2   // Walzmodus Vollscheibe
   #define WALZ_MOD_TWST               3   // Walzmodus Titanwalzstrategie
   #define WALZ_MOD_APS                4   // Walzmodus Axialprofilwalzen 

#ifdef WIN32
   #define WALZ_MOD_FLANSCH_ALT        7  // Walzmodus Flansche
#endif

   // AG-Modi
   #define AG_MOD_FAEHRT               0   // fahrendes Axialgeruest  
   #define AG_MOD_STEHT                1   // stehendes Axialgeruest   
   #define AG_MOD_KOLLI                2   // Axialgeruest in Kollision
   #define AG_MOD_VS                   3   // Vollscheibenmodus
   #define AG_MOD_AXI_PROF_SCHEIBE     4   // Axialprofilwalzen

   #define T1_VERLAGERUNG              3.0F  // Zeitkonstante Ringverlagerung
   #define T1_VERLAGERUNG_TWST        40.0F  // Zeitkonstante Ringverlagerung TWST
   #define T1_VERLAGERUNG_VS           1.0F  // Zeitkonstante Ringverlagerung VS
   #define T1_ZR_DA_KRAFT_KORREKTUR    0.0F  // Durchmesserkorrektor Zentrierarme 

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
      float s;
      float h;
      float ra;
      float ri;
      float rm;
   };

//---------------------------------------------------------------------------
// Struktur Def_Maschine_Motor
//---------------------------------------------------------------------------
   struct Def_Maschine_Motor
   {
      // Eingangsgr�ssen
      float p_nenn;                 // Nennleistung               [Nmm/s]
      float i_nenn;                 // Nennstrom                  [A]
      float eta_p;                  // elektrischer Wirkungsgrad  [%]
      float n_nenn;                 // Nenndrehzahl               [1/s]
      float n_max;                  // Maximale Drehzahl          [1/s]
      float n_regelreserve_p;       // Regelreserve               [%]
      float ueberlastung_p;         // Motor�berlastung           [%]
      float getriebe_untersetzung;  // Getriebeuntersetzung       [-]
      
      int   n_vari_flag;            // Flag variable Drehzahl     [-]

      // resultierende Groessen
      float m_nenn;                 // Nenndrehmoment             [Nmm]
      float m_eff;                  // Effektives Drehmoment      [Nmm]
      float m_max;                  // Maximales Drehmoment       [Nmm]
   };                

   // Axiale Kraftachse
   struct Def_axi_Achse
   { 
      // Eingangsgr�ssen
      float p_system_hoch;             // Hochdruck                                       [N/mm�]            
      float p_system_nenn;             // Nenndruck                                       [N/mm�]            
      float d_kolben;                  // Durchmesser Kolbenseite                           [mm]
      float d_kolbenstange;            // Durchmesser Kolbenstange                        [mm]
      float f_regelreserve_p;          // Regelreserve Kraft                              [%]
      float f_max_manu;                // wird benutzt,wenn f nicht berechnet werden kann   [N]
      float f_kommi_hoch;              // gesetzte kommissionierte Kraft bei Hochdruck      [N]
      float f_kommi_nenn;              // gesetzte kommissionierte Kraft bei Nenndruck      [N]

      // Werte f�r feste Vorgabe der Belastungsbegrenzung
      float anteil_bis_fa_nenn_proz;   // Anteil an Mantell�nge f�r Fa_nenn               [%]
      float anteil_bis_fa_hoch_proz;   // Anteil an Mantell�nge f�r Fa_hoch               [%]
      float f_reduz_vorne_proz;        // reduzierte Kraft an AW-Spitze   (Proz.von fa_nenn)[%]

      // Werte f�r wanddickenabh�ngige Berechnung der Belastungsbegrenzung
      float dis_grund_bis_lagerung; // Abstand vom Grunddurchm.(ohne zyl.Ansatz)
                                    // bis zur Lagerung                          [mm]
      float durchmesser_welle;      // Durchmesser der Welle (vor Lagerung)      [mm]
      float sigma_b_max_zul_welle;  // Zul�ssige Biegespannung                   [N/mm�] (ehemals N/cm�)

      int   fa_max_begrenzung_neu_flag;// Neue, variable axiale Kraftbegrenzung (f(sam))
      int   f_max_manu_flag;           // Kraft direkt vorgeben (ohne Berechung mit Systemdruck)
      int   hoch_druck_flag;           // Nenn- oder Hochdruckanwendung

      // resultierende Gr�ssen
      float a_kolben;                  // Fl�che Kolbenseite                              [mm�]
      float a_ring;                    // Fl�che Ringseite                                 [mm�]
      float f_max_nutz_hoch;           // Maximale nutzbare Kraft   (Hochdruck,Regelreserve)[N]
      float f_max_nutz_nenn;           // Maximale nutzbare Kraft (Nenndruck,Regelreserve)[N]
   };


   // Radiale Kraftachse
   struct Def_rad_Achse
   { 
      // Eingangsgr�ssen
      float p_system_hoch;               // Hochdruck                                       [N/mm�]            
      float p_system_nenn;               // Nenndruck                                       [N/mm�]            
      float d_kolben_o;                  // Durchmesser Kolbenseite   oben                     [mm]
      float d_kolben_u;                  // Durchmesser Kolbenseite   unten                     [mm]
      float d_kolbenstange_o;            // Durchmesser Kolbenstange oben                     [mm]
      float d_kolbenstange_u;            // Durchmesser Kolbenstange unten                  [mm]
      float f_regelreserve_p;            // Regelreserve Kraft                              [%]
      float f_max_manu;                  // wird benutzt,wenn f nicht berechnet werden kann   [N]
      float f_kommi_hoch;                // gesetzte kommissionierte Kraft bei Hochdruck      [N]
      float f_kommi_nenn;                // gesetzte kommissionierte Kraft bei Nenndruck      [N]
      float kraftniveau_ueber_BE;        // Abstand �ber BE falls Zweischlittenmaschine gew�hlt
      float kraftniveau_unter_BE;        // Abstand unter BE falls Zweischlittenmaschine gew�hlt
      float l_dw_unter_BE;               // L�nge DW unter BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)
      float l_dw_ueber_BE;               // L�nge DW unter BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)
      
                                         // Absenkbares Dornlager
      float l_max_dw_ueber_BE;           // Max.L�nge DW ueber BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)
      float l_min_dw_ueber_BE;           // Min.L�nge DW ueber BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)
      
      int   f_max_manu_flag;            // Kraft direkt vorgeben (ohne Berechung mit Systemdruck)
      int   hoch_druck_flag;            // Nenn- oder Hochdruckanwendung
      int   zwei_radialschlitten_flag;   // Ein- oder Zweischlittenmaschine
      int   ws_dw_einspannung;         // Schalter f�r Art der DW-Einspannung (FA, ESE, BSE)

      // resultierende Gr�ssen
      float a_kolben_o;                  // Fl�che Kolbenseite oben            [mm�]
      float a_kolben_u;                  // Fl�che Kolbenseite unten         [mm�]
      float a_ring_o;                  // Fl�che Ringseite oben            [mm�]
      float a_ring_u;                  // Fl�che Ringseite unten            [mm�]
      float f_max_nutz_hoch;            // Max.nutzbare Kraft (Hochdruck, Regelreserve)         [N]
      float f_max_nutz_hoch_o;         // Max.nutzbare Kraft Zyl.oben(Hochdruck,Regelreserve)[N]
      float f_max_nutz_hoch_u;         // Max.nutzbare Kraft Zyl.unten (oder gesamt(1Schlitten))(Hochdruck,Regelreserve)[N]
      float f_max_nutz_nenn;            // Max.nutzbare Kraft (Nenndruck, Regelreserve)         [N]
      float f_max_nutz_nenn_o;         // Max.nutzbare Kraft Zyl.oben(Nenndruck,Regelreserve)[N]
      float f_max_nutz_nenn_u;         // Max.nutzbare Kraft Zyl.unten (oder gesamt(1Schlitten))(Nenndruck,Regelreserve)[N]
      float l_dw_gesamt;               // Gesamte Dornl�nge f(ws_dw_einspannung, l_dw_unter_BE, l_dw_ueber_BE)
   };

   struct Def_Maschine_Achse
   { 
      // Eingangsgr�ssen
      float p_system;                  // Systemdruck                                       [bar]            
      float d_kolben;                  // Durchmesser Kolbenseite                           [mm]
      float d_kolbenstange;            // Durchmesser Kolbenstange                        [mm]
      float f_regelreserve_p;            // Regelreserve Kraft                              [%]
      float f_nenn_gesetzt;            // wird benutzt,wenn f nicht berechnet werden kann   [kN]
      
      int   f_max_nutz_manu_flag;      // F_max_nutz direkt vorgeben (ohne Berechung mit Systemdruck)

      // resultierende Gr�ssen
      float a_kolben;                  // Fl�che Kolbenseite               [cm�]
      float a_ring;                     // Fl�che Ringseite                  [cm�]
      float f_max_system;               // Maximale Kraft System            [kN]
      float f_max_nutz;                  // Maximale nutzbare Kraft            [kN]
   };

   //---------------------------------------------------------------------------
   // Struktur Def_Walzprodukt
   //---------------------------------------------------------------------------
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
      float rwg_rad_soll_o;         // Soll Ringwachsgeschwindigkeit oben  [mm/s]
      float rwg_rad_soll_u;         // Soll Ringwachsgeschwindigkeit unten [mm/s]
      float d_rwg_ou_korr;          // Soll �nderung RWG oben zu unten     [mm/s]    

      float deltas_soll_o;          // Soll Abnahme oben                   [mm]
      float deltas_soll_u;          // Soll Abnahme unten                  [mm]
      float d_deltas_ou_soll;       // Soll �nderung oben zu unten         [mm]

      float dalpha_dreh_ou_soll_bo; // Soll Winkel�nderung Dornwalze [rad]
      float winkel_dw_soll_bo;      // Soll Winkel Dornwalze [rad]
      float winkel_dw_ist_bo;       // Ist Winkel Dornwalze [rad]

      float d_pos_rso_soll_0;         // Soll Position oberer Radialschlitten (nicht gecheckt) [mm]
      float d_pos_rso_soll;         // Soll Position oberer Radialschlitten [mm]
      float d_pos_rso_ist;          // Ist Dornneigung [mm]

      float dis_drehpunkte_dw_vert; // Vertikaler Abstand Drehpunkt oben bis unten [mm]

      float v_hw_mw;                // Walzengeschwindigkeit [mm/s]
      float v_rso_soll;               // Soll Geschwindigkeit RSO [mm/s]
      float t_korr;                 // Korrekturzeit [s]
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
   struct Def_h_3Segm
   {
      int    segment_nr;
      struct Def_fumo h_Segm_umo;
      struct Def_fumo h_Segm_fak_umo;
   };

//---------------------------------------------------------------------------
// Struktur Def_querschnitte_TWST: 
//---------------------------------------------------------------------------
   struct   Def_querschnitte_TWST
   {
      float h_m_bei_s_ist;
      float s_m_bei_h_ist;
   
      float h_l_bei_s_ist;
      float s_l_bei_h_ist;
   
      float h_r_bei_s_ist;
      float s_r_bei_h_ist;
   };

//---------------------------------------------------------------------------
// Struktur Def_Form_Mess: Definition der gemessen Groessen
//---------------------------------------------------------------------------
   struct Def_Form_Mess
   {
      float da;            // Aussendurchmesser                         [mm]
      float dm;            // Mittlerer Durchmesser                     [mm]
      float di;            // Innendurchmesser                          [mm]
      float dis_hw_dw;     // Abstand zwischen Hauptwalze - Dornwalze   [mm]
      float dis_aw;        // Abstand zwischen den Axialwalzen          [mm]

      double dFSWP;        // APW: Durchm Fliessscheide                 [mm]    
      struct Def_APW_Halbe_Form Halbe_Form_o;      
      struct Def_APW_Halbe_Form Halbe_Form_u;      
   };

//---------------------------------------------------------------------------
// Struktur Def_Dim_EKV
//---------------------------------------------------------------------------
   struct Def_Dim_EKV   // EKV -> Endpunkt Kombinierte Verwalzung
   {
      float du_ekv;  // laufender Durchmesser bei EKV    [mm]
      float da_ekv;  // Aussenurchmesser bei EKV         [mm]
      float dm_ekv;  // mittlerer Durchmesser bei EKV    [mm]
      float di_ekv;  // Innendurchmesser bei EKV         [mm]
      float h_ekv;   // Ringhoehe bei EKV                [mm]
      float s_ekv;   // Wanddicke bei EKV                [mm]
   };

//---------------------------------------------------------------------------
// Struktur Def_Walzen_Geo
//---------------------------------------------------------------------------
   struct Def_Walzen_Geo
   {
      // Eingabegroessen
      int glatt_flag;   //glatte Walze TRUE/FALSE           [-]
      
      float d_nenn;     //Nenndurchmesser                   [mm]
      float d_min;      //minimaler Durchmesser             [mm]
      float h_ges;      //Hoehe der gesamten Walze          [mm]
      float h_kaliber;  //Hoehe Kaliber                     [mm]
      float t_kaliber;  //Tiefe Kaliber                     [mm]
      float h_lippe;    //Hoehe Lippe                       [mm]
      float t_lippe;    //Laenge Lippe                      [mm]
      float d_lager;    //Lagerdurchmesser bei ZR und HW,bei DW ohne Bedeutung[mm]

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
      float r_nenn;        //Nennradius                  [mm]
      float r_min;         //minimaler Radius            [mm]
      float r_lager;       //Bedeutung je nach Objekt    [mm]
   };

//---------------------------------------------------------------------------
// Struktur Def_AW_Geo  - Axialwalzengeometrie (oben und unten getrennnt)
//---------------------------------------------------------------------------
   struct Def_AW_Geo
   {
      // Eingabegr�ssen
      float delta_w_konstr_gr;      // Delta Winkel oben                         [�]
      float l_fehlende_spitze;      // L�nge der fehlenden Spitze                [mm]
      float l_nutz;                 // Nutzbare Mantell�nge                      [mm]
                                    // Theor. Mantell�nge - L�nge fehlende Spitze
      float l_zyl_ansatz;           // L�nge des zylindrischen Ansatz            [mm]
      float winkel_gr;              // �ffnungswinkel der unteren Axialwalze     [�]

      // resultierende Gr�ssen
      float delta_w_konstr_bo;      // Delta Winkel oben   (Bogenma�)            [bog]
      float du_grund;               // Grunddurchmesser                          [mm]
      float du_spitze;              // Durchmesser Spitze                        [mm]
      float l_mantel_theo;          // Theor. Mantell�nge                        [mm]
      float winkel_bo;              // �ffnungswinkel der Axialwalze             [bog]

      float achsenlaenge_l_fehlende_spitze;  // L�nge der fehlenden Spitze bez.
                                             // auf Achse                        [mm]
      float achsenlaenge_l_nutz;    // Nutzbare L�nge bez. auf Achse             [mm]

#ifdef WIN32   // MSVC++ 6.0      
      char werkzeug_name[CHAR_ANZ_MAX];
#endif

   };

//---------------------------------------------------------------------------
// Struktur Def_Schlupf 
//---------------------------------------------------------------------------
   struct Def_Schlupf
   {
      float b_weg_ag;      // Beschleunigungsweg Axialger�st                        [mm]
      float dis_sl;         // Schlupfabstand der Messeinr.bez.auf AW-Kante hinten   [mm]
      float pos_laser_osp; // Schlupfposition des Lasers   ohne Spitze                  [mm]
      float pos_laser_msp; // Schlupfposition des Lasers   ohne Spitze                  [mm]
   };

//---------------------------------------------------------------------------
// Struktur Def_Walzphase
//---------------------------------------------------------------------------
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
      float ada;           // Gedrueckte Flaeche         [mm]
      float ba;            // Breitungsfaktor            [-]
      float ca;            // Walzspaltverhaeltnis       [-]
      float delta_h;       // Abnahme Hoehe              [mm]
      float dsa_mw;        // Mittelwert Breitung        [mm]
      float dsa_max;       // Maximale Breitung          [mm]
      float epsilon_h;     // Bezogene Hoehenabnahme     [-]
      float eqa;           // Querschnittsabnahme axial  [-]
      float h0a;           // Einlaufende Hoehe axial    [mm]
      float h1a;           // Auslaufende Hoehe axial    [mm]
      float sam;           // Mittlere Wand axial        [mm]
      float la;            // Gedrueckte Laenge          [mm]
      float phi_h;         // Umformgrad                 [-]
      float phi_qa;        // Umformgrad bezogen auf Querschnittsabnahme [-]
      float s0a;           // Einlaufende Wand axial     [mm]
      float s1a;           // Auslaufende Wand axial     [mm]

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
      float ram_o;               // Radius gedr�ckte L�nge oben                           [mm]
      float raa_o;                                                                        
      float rai_o;                                                                        
      float rawa_o;               // Radius Aussenumfang oben                              [mm]
      float rawi_o;               // Radius Innenumfang oben                                 [mm]
      float s_aw_kontakt_o;      // Wanddicke Kontaktbreite Axialwalze-Ring oben            [mm]
      float s_aw_kontakt_hori_o;   // hori. Wanddicke Kontaktbreite Axialwalze-Ring oben      [mm]
      float kontaktmitte_o; 

      // Unten
      float ram_u;               // Radius gedr�ckte L�nge unten                           [mm]      
      float raa_u;                                                                        
      float rai_u;                                                                        
      float rawa_u;               // Radius Aussenumfang unten                              [mm]
      float rawi_u;               // Radius Innnenumfang unten                              [mm]
      float s_aw_kontakt_u;      // Wanddicke Kontaktbreite Axialwalze-Ring unten         [mm]
      float s_aw_kontakt_hori_u;   // hori. Wanddicke Kontaktbreite Axialwalze-Ring unten   [mm]
      float kontaktmitte_u;   
   };

//---------------------------------------------------------------------------
// Struktur Def_Iterstop
//---------------------------------------------------------------------------
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
   struct Def_Endphase
   {
      float delta_du;
      float dm;
      float du_ref;
   };

//---------------------------------------------------------------------------
// Struktur Def_iter_anpass
//---------------------------------------------------------------------------
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
      float fa_max;   // maximale Kraft axial    [N]
      float fr_max;   // maximale Kraft radial   [N]
      float ma_max;   // maximales Moment axial  [Nmm]
      float ma_nenn;  // Nennmoment axial        [Nmm]
      float mr_max;   // maximales Moment radial [Nmm]
      float mr_nenn;  // Nennmoment radial       [Nmm]
   };

//---------------------------------------------------------------------------
// Struktur Def_rwg_ds_dh
//---------------------------------------------------------------------------
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
      float n_aw_motor_g_o;   // Grunddrehzahl Axialwalze oben           [1/s]
      float n_aw_motor_g_u;   // Grunddrehzahl Axialwalze unten          [1/s]
      float n_hw_motor;       // Drehzahl Hauptwalze                     [1/s]
      float n_wp_r;           // Drehzahl Ring radial                    [1/s]

      float omega_aw_g_o;     // Winkelgeschwindigkeit Axialwalze oben   [1/s]
      float omega_aw_g_u;     // Winkelgeschwindigkeit Axialwalze unten  [1/s]
      float omega_hw;         // Winkelgeschwindigkeit Hauptwalze        [1/s]
      float omega_wp_rad;     // Winkelgeschwindigkeit Ring radial       [1/s]
      float omega_wp_axi;     // Winkelgeschwindigkeit Ring axial        [1/s]

      float v_hw_dv0;
      float v_wp_dv0_hw; 
      float v_aw_dv0_u;
      float v_wp_dv0_aw_u;
      float v_aw_dv0_o;
      float v_wp_dv0_aw_o;

      float r_wp_dv0_hw;      // Radius des Ringes an der Hauptwalze mit dv0 = 0 [mm]

      float tu;               // zur�ckliegende Umlaufzeit [s]
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
      float axi;   //mittlere Ringwachsgeschwindigkeit axial   [mm/s]
      float rad;   //mittlere Ringwachsgeschwindigkeit radial  [mm/s]
      float ges;   //mittlere Ringwachsgeschwindigkeit gesamt  [mm/s]
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
      int   RS_act;         //Flag Sollwerte radial von Ibf auswertbar
      int   RS_mode;        //Betiebsart Vorschub (0) oder Kraftregelung (1)

      float Soll_RS_Pos;    //Sollposition Radialschlitten [mm]
      //float Soll_RS_V;    // = aus_onli.ds_dh_sp_hp.s_punkt
      float Soll_FR;        //Soll- bzw. Grenzkraft radial [N]
     
      // Axialschlitten
      int   AS_act;         //Flag Sollwerte axial von Ibf auswertbar
      int   AS_mode;        //Betiebsart Vorschub (0) oder Kraftregelung (1)

      float Soll_AS_Pos;    //Sollposition Axialschlitten [mm]
      //float Soll_AS_V;    // = aus_onli.ds_dh_sp_hp.h_punkt
      float Soll_FA;        //Soll- bzw. Grenzkraft axial [N]

      // Zentrierung
      int   Zen_act;        //Flag Sollwerte Zentrierung von Ibf auswertbar
      int   Zen_mode;       //Betiebsart Positionsreg. (0) oder Verdr�nger (1)

      float Soll_ZA_Pos;    //Sollposition Zentrierung Auslauf radial [mm]
      float Soll_ZE_Pos;    //Sollposition Zentrierung Einlauf radial [mm]
      float Soll_ZA_V;      //Sollgeschw. Zentrierung Auslauf radial [mm/s]
      float Soll_ZE_V;      //Sollgeschw. Zentrierung Einlauf radial [mm/s]
      float Soll_FZ;        //Soll- bzw. Grenzkraft Zentrierung [N]

      float Verlag_ZA;      //Verlagerungsanteil zur radialen Auslaufseite [mm]
      float Verlag_ZE;      //Verlagerungsanteil zur radialen Einlaufseite [mm]
      float Verlag_angle;   //Verlagerungswinkel [Grad]

      // Axialger�st
      int   AG_act;         //Flag Sollwerte Axialger�st von Ibf auswertbar
      int   AG_mode;        //Betiebsart Vorschub (0)( oder Kraftregelung (1))

      float Soll_AG_Pos;    //Sollposition Axialger�st [mm]
      float Soll_AG_V;      //Sollgeschwindigkeit Axialger�st [mm/s]
      float Soll_FAG;       //Soll- bzw. Grenzkraft Axialger�st [N]
   };

#endif
