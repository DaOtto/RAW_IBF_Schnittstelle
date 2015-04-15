/******************************************************************************
Name:		Win_RWTH_EXCH.cpp
Plattform:	WIN32

Funktion:	Testbetrieb des IBF-Technologiemoduls ohne Walzwerk

Autor:		Daniel Otto

Version:	26.10.2014	V1.0
******************************************************************************/

#include "Win_RWTH_EXCH.hpp"
#include "time.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <Windows.h>

//#define MICHL

int Win_RWTH_EXCH::init(void) {

///////////////////////////////////////////////////////////////////////////////
// Initialisierungsdaten aus Vorgängerversion. Sollte durch eine .ini-Datei
// ersetzt werden.
///////////////////////////////////////////////////////////////////////////////
	

	Ein_Puff->dt_zyklus = 0.1F;					//
	Ein_Puff->v_gl_fak_axi_p = 50.0F;			// Geschwindigkeitsfaktor 
	Ein_Puff->v_gl_fak_hw_p = 50.0F;			//

// Maschinendaten

	//--- Hauptwalze -------------------------
	Ein_Puff->hw1_motor.n_max = 1785.0F * MIN_FAK;			// Maximale Drehzahl          [1/s]
	Ein_Puff->hw1_motor.getriebe_untersetzung = 34.286F;	// Getriebeuntersetzung       [-]
	Ein_Puff->hw1_motor.i_nenn = 586.0F;					// Nennstrom                  [A]
	Ein_Puff->hw1_motor.p_nenn = 250.0F * MILL_FAK;			// Nennleistung               [Nmm/s]
	Ein_Puff->hw1_motor.eta_p = 95.0F;						// elektrischer Wirkungsgrad  [%]
	Ein_Puff->hw1_motor.n_nenn = 1400.0F * MIN_FAK;			// Nenndrehzahl               [1/s]
	Ein_Puff->hw1_motor.n_regelreserve_p = 0.0F;			// Regelreserve               [%]
	Ein_Puff->hw1_motor.ueberlastung_p = 20.0F;				// Motorüberlastung           [%]
	Ein_Puff->hw1_motor.n_vari_flag = TRUE;					// Flag variable Drehzahl     [-]

	Ein_Puff->hw1_i_of = Ein_Puff->hw1_motor.i_nenn;

	Ein_Puff->hw_geometrie.glatt_flag = TRUE;				// glatte Walze TRUE/FALSE    [-]
	Ein_Puff->hw_geometrie.d_nenn = 755.0F;					// Nenndurchmesser            [mm]
	Ein_Puff->hw_geometrie.d_min = 0.0F;					// minimaler Durchmesser      [mm]
	Ein_Puff->hw_geometrie.h_ges = 1000.0F;					// Hoehe der gesamten Walze   [mm]

	if (!Kaliber_HW) {
		Ein_Puff->hw_geometrie.h_kaliber = 0.0F;			// Hoehe Kaliber              [mm]
		Ein_Puff->hw_geometrie.t_kaliber = 0.0F;			// Tiefe Kaliber              [mm]
	}
	else {
		Ein_Puff->hw_geometrie.h_kaliber = 47.0F;			// Hoehe Kaliber              [mm]
		Ein_Puff->hw_geometrie.t_kaliber = 50.0F;			// Tiefe Kaliber              [mm]
	}

	Ein_Puff->hw_geometrie.h_lippe = 0.0F;					// Hoehe Lippe                [mm]
	Ein_Puff->hw_geometrie.t_lippe = 0.0F;					// Laenge Lippe               [mm]
	Ein_Puff->hw_geometrie.d_lager = 0.0F;					// nur für Grafiken: Lagerdurchmesser bei ZR und HW,bei DW ohne Bedeutung[mm]

	Ein_Puff->d_hw_dv0_carwin = Ein_Puff->hw_geometrie.d_nenn; // Geschwindigekitsfaktor über Carwin vorgegeben, bzw. berechnet in TRT

	//--- Dornwalze   --------------------------
	Ein_Puff->dw_geometrie.glatt_flag = TRUE;				// glatte Walze TRUE/FALSE           [-]
	Ein_Puff->dw_geometrie.d_nenn = 149.0F;					// Nenndurchmesser                   [mm]
	Ein_Puff->dw_geometrie.d_min = 0.0F;					// minimaler Durchmesser             [mm]
	Ein_Puff->dw_geometrie.h_ges = 1000.0F;					// Hoehe der gesamten Walze          [mm]

	if (!Kaliber_DW) {
		Ein_Puff->dw_geometrie.h_kaliber = 0.0F;			// Hoehe Kaliber                     [mm]
		Ein_Puff->dw_geometrie.t_kaliber = 0.0F;			// Tiefe Kaliber                     [mm]
	}
	else {
		Ein_Puff->dw_geometrie.h_kaliber = 10.0F;			// Hoehe Kaliber                      [mm]
		Ein_Puff->dw_geometrie.t_kaliber = 10.0F;			// Tiefe Kaliber                     [mm]
	}

	Ein_Puff->dw_geometrie.h_lippe = 0.0F;					// Hoehe Lippe                       [mm]
	Ein_Puff->dw_geometrie.t_lippe = 0.0F;					// Laenge Lippe                      [mm]
	Ein_Puff->dw_geometrie.d_lager = 0.0F;					// Lagerdurchmesser bei ZR und HW,bei DW ohne Bedeutung[mm]

	//---Axialwalze unten --------------------
	Ein_Puff->awu_motor.n_max = 2830.0F * MIN_FAK;			// Maximale Drehzahl                      [1/s]
	Ein_Puff->awu_motor.getriebe_untersetzung = 11.480F;	// Getriebübersetzung                     [-]
	Ein_Puff->awu_motor.i_nenn = 339.0F;					// Nennstrom                              [A]
	Ein_Puff->awu_motor.p_nenn = 124.0F * MILL_FAK;			// Nennleistung                           [Nmm/s]
	Ein_Puff->awu_motor.eta_p = 95.0F;						// elektrischer Wirkungsgrad              [%]
	Ein_Puff->awu_motor.n_nenn = 1400.0F * MIN_FAK;			// Nenndrehzahl                           [1/s]
	Ein_Puff->awu_motor.n_regelreserve_p = 5.0;				// Regelreserve                           [%]
	Ein_Puff->awu_motor.ueberlastung_p = 20.0F;				// Motorüberlastung                       [%]
	Ein_Puff->awu_motor.n_vari_flag = TRUE;					// Flag variable Drehzahl                 [-]
	Ein_Puff->awu_i_of = Ein_Puff->awu_motor.i_nenn;

	Ein_Puff->awu_geometrie.delta_w_konstr_gr = 0.0F;		// Delta Winkel oben                      [°] //wenn z.B. die obere Walze einen anderen Winkel als die untere Walze haben sollte kann hier die Differenz eingertagen werden
	Ein_Puff->awu_geometrie.l_fehlende_spitze = 75.0F;		// Länge der fehlenden Spitze             [mm]
	Ein_Puff->awu_geometrie.l_nutz = 670.0F;				// Nutzbare Mantellänge                   [mm]
	// Theor. Mantellänge - Länge fehlende Spitze
	Ein_Puff->awu_geometrie.l_zyl_ansatz = 0.0F;			// Länge des zylindrischen Ansatz         [mm]
	Ein_Puff->awu_geometrie.winkel_gr = 45.0F;				// Öffnungswinkel der unteren Axialwalze  [°]
	Ein_Puff->awu_geometrie.winkel_bo = 0.785398F;
	//--- Axialwalze oben --------------------
	Ein_Puff->awo_motor = Ein_Puff->awu_motor;
	Ein_Puff->awo_i_of = Ein_Puff->awo_motor.i_nenn;

	Ein_Puff->awo_geometrie = Ein_Puff->awu_geometrie;

	//----------------------------------------------------------------------
	//---------------------------------------------------
	//---------------------------

	// Prozessdaten
	Ein_Puff->abschalt_modus = AB_MOD_AUSSEN;
	Ist_IBF->Axial.Kr_geo.Del_Kr_AGR = 120;

#ifdef MICHL
    Ein_Puff->soll_walzform.da = 1304.83F;		// 1000.0F;
	Ein_Puff->soll_walzform.di = 1064.83F;		// 800.0F;
	Ein_Puff->soll_walzform.hm = 100.0F;
#endif
    Ein_Puff->soll_walzform.dm = (Ein_Puff->soll_walzform.da + Ein_Puff->soll_walzform.di) * 0.5F;
	Ein_Puff->soll_walzform.sm = (Ein_Puff->soll_walzform.da - Ein_Puff->soll_walzform.di) * 0.5F;

	//soll_walzform_volumen = PI * Ein_Puff->soll_walzform.dm * Ein_Puff->soll_walzform.sm * Ein_Puff->soll_walzform.hm;

#ifdef MICHL
    Ein_Puff->vorform.da = 600.0F,		// 500.0F;
	Ein_Puff->vorform.di = 192.0F;		// 130.0F;
	Ein_Puff->vorform.hm = 176.0F;		// 200.0F;
#endif
	Ein_Puff->vorform.dm = (Ein_Puff->vorform.da + Ein_Puff->vorform.di) * 0.5F;
	Ein_Puff->vorform.sm = (Ein_Puff->vorform.da - Ein_Puff->vorform.di) * 0.5F;

	Ein_Puff->form_mess_start.da = Ein_Puff->vorform.da;
	Ein_Puff->form_mess_start.di = Ein_Puff->vorform.di;
	Ein_Puff->form_mess_start.dis_aw = Ein_Puff->vorform.hm;
	Ein_Puff->form_mess_start.dm = Ein_Puff->vorform.dm;
	Ein_Puff->form_mess_start.dis_hw_dw = Ein_Puff->vorform.sm;

	Ein_Puff->deltad_ekv = 10.0F;						// Ende kombinierte Verwalzung 
	Ein_Puff->deltad_lf_nach_ekv = 5.0F;				// Lüften nach EKV
	Ein_Puff->lueftmass_auto_as = 30.0F;

	Ein_Puff->volvertverha = 0.0F;

	//--- Wahlsschalter ------------------
	Ein_Puff->endphase_flag = 0;						// Flag, Endphase [0,1]
	Ein_Puff->walzenstart_flag = TRUE;					// Flag, Walzenstart [0,1]
	Ein_Puff->sw_zuerst_fertig_flag = 0;				// Wanddicke zuerst fertig [0,1] 
	Ein_Puff->taster_aw_manu_gelueftet_flag = 0;        // Taster Axialwalze manuell gelueftet [0,1]
	Ein_Puff->ws_d_lauf_flag = TRUE;					// Modus Referenzdurchmesser [Aussen,Mitte,Innen]
	Ein_Puff->walz_modus = 0;							// Walzmodus [0 bis 5]
	Ein_Puff->stuetzstellen_anwenden_flag = 0;
	
	//Ein_Puff->volumenberechnung_flag;		    		// Nur CNC: Flag, mit Bererechnung Volumen [0,1]
	Ein_Puff->msg_flag = TRUE;							// Ausgabe einer Message-Box [0,1]
	Ein_Puff->cnc_flag = TRUE;							// Puffer fuer CNC [0,1]
	Ein_Puff->kw_testbetrieb_flag = TRUE;				// Flag, gesetzte Umformwiderstaende [0,1]
	Ein_Puff->test_walzen_ohne_ring_flag = FALSE;
	Ein_Puff->aufwalzen_bis_ekv_flag = FALSE;
	Ein_Puff->mit_breitung_flag = TRUE;
	Ein_Puff->power_taster_flag = 0;						// Flag, Powertaster gedrückt [0,1]   
	Ein_Puff->keine_verteilung_hoehe_neg_voldiff_flag = 0;	// Keine Verteilung in die Hoehe wenn Volumendifferenz negativ [0,1]
	Ein_Puff->aw_ueberdeckung_check_flag = 0;

	Ein_Puff->n_hw_motor_soll = Ein_Puff->hw1_motor.n_nenn; // Variable Solldrehzahl Hauptwalzenmotoren [1/s]
	Ein_Puff->n_hw_motor_soll_0 = Ein_Puff->n_hw_motor_soll;// Vorgabewert Handrad Solldrehzahl Hauptwalzenmotoren [1/s]
	Ein_Puff->n_hw_motor_ist = Ein_Puff->n_hw_motor_soll_0;
	Ein_Puff->n_awu_motor_ist = 1.0F;
	Ein_Puff->n_awo_motor_ist = 1.0F;

	//--- Messebenen Tastrolle--------------
	Ein_Puff->mess_ebene.du_DW_Laser_u = Ein_Puff->dw_geometrie.d_nenn;  //Abstand Tastrolle zu DW
	Ein_Puff->mess_ebene.du_HW_Laser_u = Ein_Puff->hw_geometrie.d_nenn;  //Abstand Tastrolle zu HW


	//---------------------------------------------------------------------------
	// Online Ein_Onli belegen
	//---------------------------------------------------------------------------

	// Maschinendaten
	//--- Radialschlitten ---------------
	Ein_Onli->rs_achse.p_system_hoch = 245.0F * BAR_FAK;					// Hochdruck [N/mm²]            
	Ein_Onli->rs_achse.p_system_nenn = Ein_Onli->rs_achse.p_system_hoch;	// Nenndruck [N/mm²]  

	Ein_Onli->rs_achse.d_kolben_o = 0.0F;								// Durchmesser Kolbenseite   oben                  [mm]
	Ein_Onli->rs_achse.d_kolben_u = 250.0F;								// Durchmesser Kolbenseite   unten                 [mm]
	Ein_Onli->rs_achse.d_kolbenstange_o = 0.0F;                          // Durchmesser Kolbenstange oben                   [mm]
	Ein_Onli->rs_achse.d_kolbenstange_u = 180.0F;                        // Durchmesser Kolbenstange unten                  [mm]
	Ein_Onli->rs_achse.f_regelreserve_p = 5.0F;                          // Regelreserve Kraft                              [%]
	Ein_Onli->rs_achse.f_max_manu = 0.0F;								// wird benutzt,wenn f nicht berechnet werden kann [N]
	Ein_Onli->rs_achse.f_kommi_hoch = 1000.0F * KILO_FAK;				// gesetzte kommissionierte Kraft bei Hochdruck    [N]
	Ein_Onli->rs_achse.f_kommi_nenn = Ein_Onli->rs_achse.f_kommi_hoch;	// gesetzte kommissionierte Kraft bei Nenndruck    [N]
	Ein_Onli->rs_achse.kraftniveau_ueber_BE = 0.0F;                      // Abstand über BE falls Zweischlittenmaschine gewählt
	Ein_Onli->rs_achse.kraftniveau_unter_BE = 0.0F;                      // Abstand unter BE falls Zweischlittenmaschine gewählt
	Ein_Onli->rs_achse.l_dw_unter_BE = 440.0F;							// Länge DW unter BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)
	Ein_Onli->rs_achse.l_dw_ueber_BE = 140.0F;							// Länge DW unter BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)

	// Absenkbares Dornlager
	Ein_Onli->rs_achse.l_max_dw_ueber_BE = 440.0F;				// Max.Länge DW ueber BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)
	Ein_Onli->rs_achse.l_min_dw_ueber_BE = 440.0F;				// Min.Länge DW ueber BE (je nach ws_dw_einspannung bis Lager oder Lagermitte)

	Ein_Onli->rs_achse.f_max_manu_flag = FALSE;					// Kraft direkt vorgeben (ohne Berechung mit Systemdruck)
	Ein_Onli->rs_achse.hoch_druck_flag = FALSE;					// Nenn- oder Hochdruckanwendung
	Ein_Onli->rs_achse.zwei_radialschlitten_flag = FALSE;		// Ein- oder Zweischlittenmaschine
	Ein_Onli->rs_achse.ws_dw_einspannung = 2;					// Schalter für Art der DW-Einspannung (FA, ESE, BSE)

	Ein_Puff->fr_kommi_nenn = Ein_Onli->rs_achse.f_kommi_nenn;
	Ein_Puff->fr_erkannt_p = 5.0F;								// Krafterkennung bei 5%
	Ein_Puff->p_system_r_of = Ein_Onli->rs_achse.p_system_nenn;

	Ein_Puff->fr_of = Ein_Puff->fr_kommi_nenn;

	Ein_Onli->dw_sigma_zul = 500.0F;
	Ein_Onli->d_dw_pseudo_kolli_ag_dwlager = Ein_Puff->dw_geometrie.d_nenn;

	// --- Axialschlitten -----------------
	Ein_Onli->as_achse.p_system_hoch = 245.0F * BAR_FAK;					// Hochdruck [N/mm²]
	Ein_Onli->as_achse.p_system_nenn = Ein_Onli->as_achse.p_system_hoch;	// Nenndruck [N/mm²]

	Ein_Onli->as_achse.d_kolben = 220.0F;						// Durchmesser Kolbenseite                           [mm]
	Ein_Onli->as_achse.d_kolbenstange = 160.0F;					// Durchmesser Kolbenstange                          [mm]
	Ein_Onli->as_achse.f_regelreserve_p = 5.0F;					// Regelreserve Kraft                                [%]
	Ein_Onli->as_achse.f_max_manu = FALSE;						// wird benutzt,wenn f nicht berechnet werden kann   [N]
	Ein_Onli->as_achse.f_kommi_hoch = 800.0F * KILO_FAK;			// gesetzte kommissionierte Kraft bei Hochdruck      [N]
	Ein_Onli->as_achse.f_kommi_nenn = Ein_Onli->as_achse.f_kommi_hoch;// gesetzte kommissionierte Kraft bei Nenndruck      [N]

	Ein_Onli->as_achse.anteil_bis_fa_nenn_proz = 30.0F;
	Ein_Onli->as_achse.anteil_bis_fa_hoch_proz = 30.0F;
	Ein_Onli->as_achse.f_reduz_vorne_proz = 100.0F;

	Ein_Puff->fa_kommi_nenn = Ein_Onli->as_achse.f_kommi_nenn;
	Ein_Puff->fa_erkannt_p = 5.0F;                               // Krafterkennung bei 5%
	Ein_Puff->p_system_a_of = Ein_Onli->as_achse.p_system_nenn;

	Ein_Puff->fa_of = Ein_Puff->fa_kommi_nenn;

	//--- Schlupfgeometrien -----------------
	Ein_Puff->schlupf_u.pos_laser_osp = Ein_Puff->awu_geometrie.l_nutz * 0.9F; // OSP = ohne Spitze
	Ein_Puff->schlupf_u.dis_sl = Ein_Puff->awu_geometrie.l_nutz - Ein_Puff->schlupf_u.pos_laser_osp; //Dis_sl= Distanz Schlupfposition  
	Ein_Puff->schlupf_u.pos_laser_msp = Ein_Puff->awu_geometrie.l_mantel_theo - Ein_Puff->schlupf_u.dis_sl;
	Ein_Puff->schlupf_u.b_weg_ag = 0.0F;

	//--- Zentrierarme --------------------
	// Prozessdynamik
	Ein_Onli->rwg_max = 10.0F;			// Maximale Ringwachsgeschwindigkeit [mm/s]
	Ein_Onli->rwg_min_endphase = 2.0F;	// Minimale Ringwachsgeschwindigkeit [mm/s]
	Ein_Onli->rwg_aufweiten = 0.0F;		// Ringwachsgeschwindigkeit Aufweiten [mm/s]
	Ein_Onli->rwg_poti_wert = 1.0F;		// Potiwert Ringwachsgeschwindigkeit [0<->2]
	Ein_Onli->rwg_regelgrenze = 20.0F;	// Maximale möglich Ringwachsgeschwindigkeit [mm/s]

	Ein_Onli->rwg_hochfahren_start = 5.0F;

	Ein_Onli->deltad_rundier = 10.0F;	// delta Durchmesser fuer Rundierung [mm]

	Ein_Onli->d_du_pro_1_mm_rwg;					
	Ein_Onli->exponent_rwg_endphase = 1.0F;
	Ein_Onli->korrektur_endphase_poti_wert = 0.0F;	// Potiwert Endphase [-1<->1]

	Ein_Onli->zeit_momente_hochfahren = 10.0F;
	Ein_Onli->aufwalzung_check_flag = FALSE;

	Ein_Onli->river_auto_flag = TRUE;
	Ein_Onli->handrad_korrektur_river_auto = 1.0F;

	Ein_Onli->s_aufweiten_proz = 10.0F;				// Aufweiten Prozent
	Ein_Onli->kurv_faktor_aufweiten = 0.0F;
	Ein_Onli->kurv_faktor_walzen = 1.0F;

	Ein_Onli->da_walz_max = 2200.0F;
	Ein_Onli->h_walz_max = 350.0F;

	//--- KW ------------------------------
	Ein_Puff->kw_fr_fa_mr_ma_test.kw_fa = 100.0F;
	Ein_Puff->kw_fr_fa_mr_ma_test.kw_fr = 100.0F;
	Ein_Puff->kw_fr_fa_mr_ma_test.kw_ma = 100.0F;
	Ein_Puff->kw_fr_fa_mr_ma_test.kw_mr = 100.0F;

	ExchPool.Ein_Puff_back = *Ein_Puff;
	ExchPool.Ein_Onli_back = *Ein_Onli;
	ExchPool.Ein_Puff_RWTH = *Ein_Puff;
	ExchPool.Ein_Onli_RWTH = *Ein_Onli;

	lRPW->sin_kw_winkel_halbe = (float)sin(Ein_Puff->awu_geometrie.winkel_bo * 0.5F);  /* Sinus halber Kegelwalzenwinkel */

	Ein_Puff->form_mess_of.dis_hw_dw	= 469.14F;    
	Ein_Puff->form_mess_of.dis_aw		= 273.37F;       
	Ein_Onli->Ibf_actual.Ist_AG	  		= 1515.44F;
	Ein_Puff->form_mess_of.da			= 1735.44F;
	Ein_Onli->Ibf_actual.Ist_ZEN_A		= 1846.14F;
	Ein_Onli->Ibf_actual.Ist_ZEN_E		= 1846.62F;
	Ein_Puff->n_hw_motor_ist			= 0.404F;
	Ein_Puff->n_awo_motor_ist			= 0.404F;
	Ein_Puff->pos_laser_u_of			= 220.00F;

	// Einlesen einiger Parameter aus der Maschdat.ini Datei
	// ToDo: Anpassen/erweitern der CIniFile-Klasse um syntax der Maschdat.ini Datei
	//CIniFile maschdatFile("MASCHDAT.INI");
	//if (!maschdatFile.ReadFile()) //Fehlerbehandlung
	//{
	//	return 0;
	//}

	return 0;
};

///////////////////////////////////////////////////////////////////////////////

int Win_RWTH_EXCH::run(void) {
	
	get_puff();
	Main_Control();
	put_puff();
	
	breakIter = iter_IBF; // dummy: eigentlich abbruchgrund

return breakIter;
};

///////////////////////////////////////////////////////////////////////////////

int Win_RWTH_EXCH::put_puff(void) {
	
	ExchPool.Ein_Puff_RWTH = *Ein_Puff;
	ExchPool.Ein_Onli_RWTH = *Ein_Onli;
	ExchPool.Aus_Puff_RWTH = *Aus_Puff;
	ExchPool.Aus_Onli_RWTH = *Aus_Onli;

	ExchPool.Ein_Puff_back = *Ein_Puff;
	ExchPool.Ein_Onli_back = *Ein_Onli;

	return 0;
};

///////////////////////////////////////////////////////////////////////////////

int Win_RWTH_EXCH::get_puff(void) {

	*Ein_Puff = ExchPool.Ein_Puff_back;
	*Ein_Onli = ExchPool.Ein_Onli_back;
	//Aus_Puff = aus_puff;
	//Aus_Onli = aus_onli;
	//Lokal_Puff = lokal_puff;

	return 0;
};

///////////////////////////////////////////////////////////////////////////////

int Win_RWTH_EXCH::Main_Control(void) {
	
	time_t start, end;
	ctime(&start);

	//jeweils zum Walzenstart (Walzenstartflag) müssen einige Variablen vordefiniert werden,
	//damit richtige CASE-Anweisungen im rpw.cpp (IBF-Modul) ausgeführt werden
	if (Ein_Puff->walzenstart_flag!=0) 
	{
		Ist_IBF->StartPos = 1;

		// Initialisierung der globalen IBF Strukturen
		iter_IBF	= 0;
		*Ist_Inter	= *pIst_Inter_Ini;
		*Soll_Inter	= *pSoll_Inter_Ini;
		*Soll_IBF	= *pSoll_IBF_Ini;
		*Ist_IBF	= *pIst_IBF_Ini;

		Soll_IBF->Axial.Pr_Num = 0;
		Soll_IBF->Flag.AG_Start_erreicht = 0;

		// Spezielle Anfahrroutine fuer Schuesselwalzen (11.1.2015 d.Otto)
		if (Ist_IBF->Flag.Axial_Radialwalzen == 3)
		{
			Soll_IBF->InitAchse = 's';
			Soll_IBF->Profilflag = -1;
		}

		// Achsenmodi initialisieren (9.1.2015 d.Otto)
		//Soll_Inter->RS_act	=	1;
		//Soll_Inter->AS_act	=	1;
		//Soll_Inter->zen_act	=	0;
		
		// Bissverhältnis
		Soll_IBF->Axial.Biss.Anzahl = 0;
		Soll_IBF->Axial.AGR_Pr[0] = Soll_IBF->Axial.Biss.AGR_Pr_Merker;
		Soll_IBF->Axial.Biss.AG_Pos_Erreicht = 0;
		Soll_IBF->Axial.Turbine.AG_Pos_Erreicht = 0;
		Soll_IBF->Axial.Turbine.Stufe_erreicht = 0;
		Soll_IBF->Axial.Turbine.zweite_Ebene_erreicht = 0;

		// IBF-Stuetzstelle 
		Soll_IBF->stuetz_var.skip_faktor = 1; // IBF-Stuetzstelle
		Soll_IBF->stuetz_var.merker = 0;	  // IBF-Stuetzstelle
		Soll_IBF->stuetz_var.crtimer = 0;	  // IBF-Stuetzstelle

		//Formenspektrum
		Soll_IBF->Formen.Profilflag = 1;
		
		// Walzprozess gestartet
		Ein_Puff->walzenstart_flag	= 0;
	}
	else 
	{
		iter_IBF++;
	}

	lRPW->Main_RAW(	iter_IBF,
					*Ein_Puff,
					*Lokal_Puff,
					*Aus_Puff,
					*Ein_Onli,
					*Aus_Onli,
					*Ist_Inter,
					*Soll_Inter,
					*Soll_IBF,
					*Ist_IBF );
	
	ctime(&end);
	
	// Zeitdifferenz berechnen. Angabe in Sekunden
	Ist_Inter->Systemzeit = difftime(end, start);
	
	// Zuweisungen für die Steuerung 
	
	/* zu setzende Flags mit denen IBF-Positionsvorgaben gültig werden */
	Aus_Onli->Ibf_nominal.RS_act	= Soll_Inter->RS_act;   // Flag Sollwerte Radialschlitten von Ibf auswertbar 1, nicht auswertbar 0
	Aus_Onli->Ibf_nominal.AS_act	= Soll_Inter->AS_act;   // Flag Sollwerte Axialschlitten von Ibf auswertbar
	Aus_Onli->Ibf_nominal.AG_act	= Soll_Inter->ag_act;   // Flag Sollwerte Axialgerüst von Ibf auswertbar
	Aus_Onli->Ibf_nominal.Zen_act	= Soll_Inter->zen_act;  // Flag Sollwerte Zentrierarme von Ibf auswertbar 1, nicht auswertbar 0
	
	/* Schalter Kraftregler */
	Aus_Onli->Ibf_nominal.RS_mode  = Soll_Inter->rs_mode;	// Betriebsart Vorschub (Bit0=0) oder Kraftregelung (Bit0=1)
	Aus_Onli->Ibf_nominal.AS_mode  = Soll_Inter->aso_mode;  // Betriebsart Vorschub (Bit0=0) oder Kraftregelung (Bit0=1)
	Aus_Onli->Ibf_nominal.AG_mode  = Soll_Inter->ag_mode;   // Betriebsart Vorschub (Bit0=0) oder Kraftregelung (Bit0=1)
	Aus_Onli->Ibf_nominal.Zen_mode = Soll_Inter->zen_mode;	// Betriebsart Vorschub (Bit0=0) oder Kraftregelung (Bit0=1) !!! Betriebsart für beide Arme !!! 
	
	/* Zustellgeschwindigkeiten */
	Aus_Onli->ds_dh_sp_hp.s_punkt = Soll_Inter->rs_v  * Ein_Onli->rwg_poti_wert;/*Radialschlitten      [mm/s]*/
	Aus_Onli->ds_dh_sp_hp.h_punkt = Soll_Inter->aso_v * Ein_Onli->rwg_poti_wert;/*Axialschlitten oben  [mm/s]*/
	Aus_Onli->Ibf_nominal.Soll_AG_V = Soll_Inter->ag_v;                         /* Axialgeruest        [mm/s]*/
	Aus_Onli->Ibf_nominal.Soll_ZA_V = Soll_Inter->zar_v;                        /* Zentrierarm links   [mm/s]*/
	Aus_Onli->Ibf_nominal.Soll_ZE_V = Soll_Inter->zal_v;                        /* Zentrierarm rechts  [mm/s]*/

	/* Sollpositionen */
	Aus_Onli->Ibf_nominal.Soll_RS_Pos = Soll_Inter->rs_pos;          /* Radialschlitten            [mm]*/
	Aus_Onli->Ibf_nominal.Soll_AS_Pos = Soll_Inter->aso_pos;         /* Axialschlitten oben        [mm]*/
	Aus_Onli->Ibf_nominal.Soll_AG_Pos = Soll_Inter->ag_pos;          /* Axialschlitten             [mm]*/
	Aus_Onli->Ibf_nominal.Soll_ZA_Pos = Soll_Inter->zar_pos;         /* Zentrierarm rechts Auslauf [mm]*/
	Aus_Onli->Ibf_nominal.Soll_ZE_Pos = Soll_Inter->zal_pos;         /* Zentrierarm links Einlauf  [mm]*/

	/* Drehzahlen */
	Aus_Puff->n_omega.n_hw_motor	 = Soll_Inter->hw_n;	/* Hauptwalze 			[1/min]*/
	Aus_Puff->n_omega.n_aw_motor_g_o = Soll_Inter->kwo_n;	//* MIN_FAK;  /* Kegelwalze oben      [1/min]*/
	Aus_Puff->n_omega.n_aw_motor_g_u = Soll_Inter->kwu_n;	//* MIN_FAK;  /* Kegelwalze unten     [1/min]*/

	/* Schrittnummer */
	// Soll_Inter->schritt_nr;			

	/* Sollkräfte */
	Aus_Onli->Ibf_nominal.Soll_FR  = Soll_Inter->rs_kraft;           /* Radialkraft [N] */
	Aus_Onli->Ibf_nominal.Soll_FA  = Soll_Inter->aso_kraft;          /* Axialkraft  [N] */
	Aus_Onli->Ibf_nominal.Soll_FAG = Soll_Inter->ag_kraft;           /* Axialgerüst [N] */
	Aus_Onli->Ibf_nominal.Soll_FZ  = Soll_Inter->zal_kraft;          /* Zentrierarme[N] */
	
	if (Ist_IBF->Flag.Axial_Radialwalzen ==	0) {
		/* !!! Darf nur aktiv sein, wenn Axialprofilieren angewählt wird und Kragenwalze verbaut ist !!! */
		Aus_Onli->fa_max_axialwalze = 400000.0F;
		/* Kraftgrenzenregler für Kragenwalze auf 40T, ansonsten wird Kraft anhand Kegelwalze auf mittlerer Wanddicke begrenzt */
	}

#ifdef DRR
	// Sollwertvorgaben für Druckrollen. 2.12.2012 D.O	
	Aus_Onli->Ibf_nominal.DRR_A_act		= Soll_Inter->DRR_Param.DrR_A.act;
	Aus_Onli->Ibf_nominal.DRR_E_act		= Soll_Inter->DRR_Param.DrR_E.act;
	Aus_Onli->Ibf_nominal.DRR_A_mode	= Soll_Inter->DRR_Param.DrR_A.mode;
	Aus_Onli->Ibf_nominal.DRR_E_mode	= Soll_Inter->DRR_Param.DrR_E.mode;
	Aus_Onli->Ibf_nominal.Soll_DRR_A_V		= Soll_Inter->DRR_Param.DrR_A.V;
	Aus_Onli->Ibf_nominal.Soll_DRR_E_V		= Soll_Inter->DRR_Param.DrR_E.V;
	Aus_Onli->Ibf_nominal.Soll_DRR_A_Pos	= Soll_Inter->DRR_Param.DrR_A.Pos;
	Aus_Onli->Ibf_nominal.Soll_DRR_E_Pos	= Soll_Inter->DRR_Param.DrR_E.Pos;
	Aus_Onli->Ibf_nominal.Soll_FDRR_A		= Soll_Inter->DRR_Param.DrR_A.Kraft;
	Aus_Onli->Ibf_nominal.Soll_FDRR_E		= Soll_Inter->DRR_Param.DrR_E.Kraft;
#endif // DRR
	
	return 0;
};

///////////////////////////////////////////////////////////////////////////////
// Aktuelle Ist-Werte berechnen
///////////////////////////////////////////////////////////////////////////////

int Win_RWTH_EXCH::genThread(LPVOID lpParameter)
{
	exchPool& Param = *(exchPool*)lpParameter;

	// RingDurchmesser
	Param.Ein_Puff_back.form_mess_of.da = Param.Aus_Puff_RWTH.form_ring.da = Param.Ein_Puff_back.vorform.da;

	// AG-Ist-Position berechnen
	switch (Param.Aus_Onli_RWTH.Ibf_nominal.AG_mode)
	{
	case 0x05:
	case 0x01:
		{
			Param.Ein_Onli_back.Ibf_actual.Ist_AG = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_AG_Pos,
																	Param.Ein_Onli_back.Ibf_actual.Ist_AG,
																	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_AG_V,
																	0,
																	1700,
																	Param.Ein_Puff_RWTH.dt_zyklus);
			//cout << "Achtung: Kraftsteuerung AG\r";
			break;
		}
	case 0x04:
	case 0x02:
	default:
		{
			Param.Ein_Onli_back.Ibf_actual.Ist_AG = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_AG_Pos,
																	Param.Ein_Onli_back.Ibf_actual.Ist_AG,
																	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_AG_V,
																	0,
																	1700,
																	Param.Ein_Puff_RWTH.dt_zyklus);
			break;
		}
	
	};

	// Tastrolle Position
	Param.Ein_Puff_back.pos_laser_u_of =  Param.Aus_Puff_RWTH.form_ring.da - Param.Ein_Onli_back.Ibf_actual.Ist_AG;

	// AS-Ist-Position berechnen
	switch (Param.Aus_Onli_RWTH.Ibf_nominal.AS_mode)
	{
	case 0:
		{
			Param.Ein_Puff_back.form_mess_of.dis_aw = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_AS_Pos,
																		Param.Ein_Puff_back.form_mess_of.dis_aw,
																		Param.Aus_Onli_RWTH.ds_dh_sp_hp.h_punkt,
																		0,
																		340,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			break;
		}
	case 1:
		{
			Param.Ein_Puff_back.form_mess_of.dis_aw = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_AS_Pos,
																		Param.Ein_Puff_back.form_mess_of.dis_aw,
																		Param.Aus_Onli_RWTH.ds_dh_sp_hp.h_punkt,
																		0,
																		340,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			//cout << "Achtung: Kraftsteuerung AS\r";
			Param.Aus_Puff_RWTH.fa_mf=Param.Aus_Onli_RWTH.Ibf_nominal.Soll_FA;
			break;
		}
	default:
		break;
	};

	// RS-Ist-Position berechnen
	switch (Param.Aus_Onli_RWTH.Ibf_nominal.RS_mode)
	{
	case 0: // Wegsteuerung
		{
			Param.Ein_Puff_back.form_mess_of.dis_hw_dw = IstPos_SollPos(Param.Aus_Onli_RWTH.Ibf_nominal.Soll_RS_Pos,
																		Param.Ein_Puff_back.form_mess_of.dis_hw_dw,
																		Param.Aus_Onli_RWTH.ds_dh_sp_hp.s_punkt,
																		0,
																		600,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			break;
		}
	case 1:  // ToDo Kraftsteuerung
		{
			Param.Ein_Puff_back.form_mess_of.dis_hw_dw = IstPos_SollPos(Param.Aus_Onli_RWTH.Ibf_nominal.Soll_RS_Pos,
																		Param.Ein_Puff_back.form_mess_of.dis_hw_dw,
																		Param.Aus_Onli_RWTH.ds_dh_sp_hp.s_punkt,
																		0,
																		600,
																		Param.Ein_Puff_RWTH.dt_zyklus);

			//cout << "Achtung: Kraftsteuerung RS\r";
			
			Param.Aus_Puff_RWTH.fr_mf=Param.Aus_Onli_RWTH.Ibf_nominal.Soll_FR;
			break;
		}
	default:
		break;
	};
	
	// Zentrierarme Position berechnen
	switch (Param.Aus_Onli_RWTH.Ibf_nominal.Zen_mode)
	{
	case 0+0+4: // Positionssteuerung
		{
			// Einlauf (Links)
			Param.Ein_Onli_back.Ibf_actual.Ist_ZEN_E = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_ZE_Pos,
																		Param.Ein_Onli_back.Ibf_actual.Ist_ZEN_E,
																		Param.Aus_Onli_RWTH.Ibf_nominal.Soll_ZE_V,
																		1470.0,
																		1850.0,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			// Auslauf (Rechts)
			Param.Ein_Onli_back.Ibf_actual.Ist_ZEN_A = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_ZA_Pos,
																		Param.Ein_Onli_back.Ibf_actual.Ist_ZEN_A,
																		Param.Aus_Onli_RWTH.Ibf_nominal.Soll_ZA_V,
																		1470.0,
																		1850.0,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			break;
		}
	case 1: // Kraftsteuerung
		{
			// Einlauf (Links)
			Param.Ein_Onli_back.Ibf_actual.Ist_ZEN_E = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_ZE_Pos,
																		Param.Ein_Onli_back.Ibf_actual.Ist_ZEN_E,
																		Param.Aus_Onli_RWTH.Ibf_nominal.Soll_ZE_V,
																		1470.0,
																		1850.0,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			// Auslauf (Rechts)
			Param.Ein_Onli_back.Ibf_actual.Ist_ZEN_A = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_ZA_Pos,
																		Param.Ein_Onli_back.Ibf_actual.Ist_ZEN_A,
																		Param.Aus_Onli_RWTH.Ibf_nominal.Soll_ZA_V,
																		1470.0,
																		1850.0,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			//cout << "Achtung: Kraftsteuerung ZR\r";
			break;
		}
	}

	// Druckrollen Positionen berechnen
	switch (Param.Aus_Onli_RWTH.Ibf_nominal.DRR_A_mode)
	{
	case 4: // Positionssteuerung
		{
			// Auslauf (Rechts)
			Param.Ein_Onli_back.Ibf_actual.Ist_DRR_A = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_DRR_A_Pos,
																		Param.Ein_Onli_back.Ibf_actual.Ist_DRR_A,
																		Param.Aus_Onli_RWTH.Ibf_nominal.Soll_DRR_A_V,
																		342.5F,
																		916.0F,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			break;
		}
	case 0: // Kraftsteuerung
		{
			// Auslauf (Rechts)
			Param.Ein_Onli_back.Ibf_actual.Ist_DRR_A = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_DRR_A_Pos,
																		Param.Ein_Onli_back.Ibf_actual.Ist_DRR_A,
																		Param.Aus_Onli_RWTH.Ibf_nominal.Soll_DRR_A_V,
																		345.9F,
																		916.0F,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			//cout << "Achtung: Kraftsteuerung DRA\r";
			break;
		}
	}
	switch (Param.Aus_Onli_RWTH.Ibf_nominal.DRR_E_mode)
	{
	case 4: // Positionssteuerung
		{
			// Einlauf (Links)
			Param.Ein_Onli_back.Ibf_actual.Ist_DRR_E = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_DRR_E_Pos,
																		Param.Ein_Onli_back.Ibf_actual.Ist_DRR_E,
																		Param.Aus_Onli_RWTH.Ibf_nominal.Soll_DRR_E_V,
																		342.5F,
																		916.0F,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			break;
		}
	case 0: // Kraftsteuerung
		{
			Param.Ein_Onli_back.Ibf_actual.Ist_DRR_E = IstPos_SollPos(	Param.Aus_Onli_RWTH.Ibf_nominal.Soll_DRR_E_Pos,
																		Param.Ein_Onli_back.Ibf_actual.Ist_DRR_E,
																		Param.Aus_Onli_RWTH.Ibf_nominal.Soll_DRR_E_V,
																		345.9F,
																		916.0F,
																		Param.Ein_Puff_RWTH.dt_zyklus);
			//cout << "Achtung: Kraftsteuerung DRE\r";
			break;
		}
	}

	//// Walzen

	/* Drehzahlen */
		Param.Ein_Puff_back.n_hw_motor_ist	= Param.Aus_Puff_RWTH.n_omega.n_hw_motor	 / (2.0F*PI);		// Hauptwalze
		Param.Ein_Puff_back.n_awo_motor_ist = Param.Aus_Puff_RWTH.n_omega.n_aw_motor_g_o / (2.0F*PI);	// Axialwalze oben
		Param.Ein_Puff_back.n_awu_motor_ist = Param.Aus_Puff_RWTH.n_omega.n_aw_motor_g_u / (2.0F*PI);	// Axialwalze unten

	return 0;
};

///////////////////////////////////////////////////////////////////////////////
// Funktion (float) Win_RWTH_EXCH::IstPos_SollPos(Soll,Ist,V,max,min)
//			Rückgabewert ist neue IstPos
///////////////////////////////////////////////////////////////////////////////

float Win_RWTH_EXCH::IstPos_SollPos(	float SP, 
								float IP, 
								float V , 
								float Pmin,
								float Pmax,
								float dt)
{
	float dir; // Bewegungsrichtung
	float Ptmp,SPtmp; // Temporaer neue Position
	
	// Minimalposition/Maximalposition eingehalten?
	SPtmp = max(min(SP,Pmax),Pmin);

	dir = sgn(SPtmp-IP);
	
	Ptmp = IP+fabs(V)*dir*dt;
	
	// Sollposition erreicht ?
	if (dir>0)
	{
		Ptmp = min(SPtmp,Ptmp);
	}
	else if (dir<0)
	{
		Ptmp = max(SPtmp,Ptmp);
	} 
		
	return Ptmp;
}
///////////////////////////////////////////////////////////////////////////////
// Konstruktor: Win_RWTH_EXCH
///////////////////////////////////////////////////////////////////////////////

Win_RWTH_EXCH::Win_RWTH_EXCH(RPW* aRPW, globData* initBuffer) {

	// lokale Referenzen auf globale Datenstrukturen
	Ein_Puff	= &(initBuffer->Ein_Puff);
	Aus_Puff	= &(initBuffer->Aus_Puff);
	Ein_Onli	= &(initBuffer->Ein_Onli);
	Aus_Onli	= &(initBuffer->Aus_Onli);
	Lokal_Puff	= &(initBuffer->Lokal_Puff);

	Ist_Inter	= &(initBuffer->Ist_Inter);
	Soll_Inter	= &(initBuffer->Soll_Inter);

	Ist_IBF		= &(initBuffer->Ist_IBF);
	Soll_IBF	= &(initBuffer->Soll_IBF);

	lRPW		= aRPW;
	
	// Initialisierung der IBF-Strukturen
	Def_Ist_Inter&			Ist_Inter_Ini	= *( pIst_Inter_Ini	= new Def_Ist_Inter()			);
	Def_Soll_Inter&			Soll_Inter_Ini	= *( pSoll_Inter_Ini= new Def_Soll_Inter()			);
	Def_IBF_Allgemein_IST&	Ist_IBF_Ini		= *( pIst_IBF_Ini	= new Def_IBF_Allgemein_IST()	);
	Def_IBF_Allgemein_SOLL&	Soll_IBF_Ini	= *( pSoll_IBF_Ini	= new Def_IBF_Allgemein_SOLL()	);

	Soll_IBF_Ini.Profilflag = -1;

	Soll_IBF_Ini.InitAchse = 'a';
	Soll_IBF_Ini.ExitAchse = 'a';
	Soll_IBF_Ini.Zeit.t_Halte = 20;    // Sollwartezeit beim Anfahren
	Soll_IBF_Ini.stuetz_var.skip_faktor = 1;	// IBF-Stuetzstelle
	Soll_IBF_Ini.stuetz_var.merker = 0;			// IBF-Stuetzstelle
	Soll_IBF_Ini.stuetz_var.crtimer = 0;		//IBF-Stuetzstelle

	Ist_IBF_Ini.Axial.Kr_geo.sin_kw_winkel_halbe = 0.3826834323650897717284599840304F;  // sin(22.5°)  
	
	//-----------------------------------------------------------------------------
	//----- Einlesen der IBF_Data.ini (entspricht der ipfpara auf dem MRAW)   -----
	//----- Datei liegt in dem smp16-Verzeichnis auf dem Windowsrechner       -----
	//----- und wird von der Sicomp-Einheit bei jedem Reset geladen.          -----
	//----- Ini-Datei darf nicht verändert werden, ohne dass diese Änderungen -----
	//----- hier im Quelltext übernommen werden!                              -----
	//-----------------------------------------------------------------------------
	cout << "Gleich soll IBF_Data geöffnet werden...." << endl;
	if (!lRPW->IBFPARA_auslesen(Ist_IBF_Ini, Soll_IBF_Ini, Ist_Inter_Ini))
	{
		cout << "konnte IBF_Data nicht öffnen" << endl;
	}
	else
	{
		cout << "konnte IBF_Data öffnen" << endl;
	}

	//	Ist_Inter_Ini.Systemzeit = difftime(end, start);    // Zeitdifferenz berechnen. Angabe in Sekunden

	// Funktionsaufrufe: hier IBF-Modul Flexibel axiales Profilieren (Funktionen stehen in der ibf_tool.cpp)

	lRPW->Kr_Geo_berechnen(Ist_IBF_Ini);
	lRPW->Kr_Geo_pruefen(Ist_IBF_Ini);

	// Funktionsaufrufe: Modus des Axialgerüstes
	lRPW->Modus_AG(Soll_Inter_Ini, Ist_IBF_Ini, Ist_IBF_Ini.Flag.Axial_Radialwalzen);


	if ((Ist_IBF_Ini.Flag.Axial_Radialwalzen == 1)||(Ist_IBF_Ini.Flag.Axial_Radialwalzen == 2))// Radialprof. od Formenspek.
	{
		Soll_IBF_Ini.min_RS_Pos  = 10.0F; // minimale Wanddickeposition, die erreicht werden darf. Wert ist von Carwin-Vorgabe unabhängig
		Soll_IBF_Ini.min_ASO_Pos = 85.0F; // min. Ringhöhe, wenn mit Tastrollenerhöhung gearbeitet wird  ||107.0F -> Radialprofieren Aufsatz 1
	}
	else
		Soll_IBF_Ini.min_ASO_Pos = 25.0F;

	Ist_IBF_Ini.Axial.Biss.Anzahl_zweite_Ebene = Ist_IBF_Ini.Axial.Biss.Anzahl + Ist_IBF_Ini.Axial.Biss.Anzahl;

	cout << "Allgemeine Information" << endl;
	cout << "System hat " << Ist_Inter_Ini.Systemzeit * 1000.0 << " Sekunden benötigt, um Datei einzulesen" << endl;
	cout << "Minimale IBF-Wandposition (kann von der CARWIN-Wanddicke abweichen) " << Soll_IBF_Ini.min_RS_Pos << endl;
	cout << "Minimale Ringhöhe                                                   " << Soll_IBF_Ini.min_ASO_Pos << endl;
	cout << endl;
	cout << endl;

	//Kontrolle der eingelesenen IBF-Werte in LoggerFile

	cout << "Folgende Werte wurden aus IBF_Data gelesen und wie folgt zugeordnet" << endl;
	cout << endl;


	cout << "Abschalten nach SMS (0) oder IBF (1)" << ":" << " " << Ist_IBF_Ini.Flag.IBF_Abschaltung << endl;
	cout << endl;
	cout << "Weg-Kraftschalter RS aktiv  [1=ja, 0=nein]" << ":" << " " << Ist_IBF_Ini.Flag.rs_kraftregler_aktiv <<	endl;
	cout << "Weg-Kraftschalter AS aktiv  [1=ja, 0=nein]" << ":" << " " << Ist_IBF_Ini.Flag.as_kraftregler_aktiv <<	endl;
	cout << "Weg-Kraftschalter AG aktiv  [1=ja, 0=nein]" << ":" << " " << Ist_IBF_Ini.Flag.ag_kraftregler_aktiv <<	endl;
	cout << "Weg-Kraftschalter ZAL aktiv [1=ja, 0=nein]" << ":" << " " << Ist_IBF_Ini.Flag.zal_kraftregler_aktiv << endl;
	cout << "Weg-Kraftschalter ZAR aktiv [1=ja, 0=nein]" << ":" << " " << Ist_IBF_Ini.Flag.zar_kraftregler_aktiv << endl;
	cout << endl;

	cout << "RS_Kraftvorgabe " << "= " << " " << Soll_IBF_Ini.RS_Kraft_Vorgabe << " N" << endl;
	cout << "AS_Kraftvorgabe " << "= " << " " << Soll_IBF_Ini.AS_Kraft_Vorgabe << " N" << endl;
	cout << "AG_Kraftvorgabe " << "= " << " " << Soll_IBF_Ini.AG_Kraft_Vorgabe << " N" << endl;
	cout << "ZAL_Kraftvorgabe" << "= " << " " << Soll_IBF_Ini.ZAL_Kraft_Vorgabe << " N" << endl;
	cout << "ZAR_Kraftvorgabe" << "= " << " " << Soll_IBF_Ini.ZAR_Kraft_Vorgabe << " N" << endl;
	cout << endl;
	cout << endl;

	cout << "Anwalzen in Kraft" << endl;

	// Schalter: Walzen mit Kraftsteuerung [1], Positionssteuereung [0]
	cout << "Dornwalze in Kraft beim Anwalzen [1=AN, 0=AUS]" << ":" << " " << Ist_IBF_Ini.Flag.rs_kraftanfahren_aktiv << endl;
	if (Ist_IBF_Ini.Flag.rs_kraftanfahren_aktiv == 0)
		cout << "Radiales Anwalzen in Kraft wurde nicht vorgewählt " << endl;
	else
		cout << "Radiales Anwalzen mit der Kraft FR" << "= " << " " << Soll_IBF_Ini.RS_Kraft_Anfahren << " vorgewählt" << endl;

	cout << endl;

	cout << "Kegelwalze in Kraft beim Anwalzen [1=AN, 0=AUS]" << ":" << " " << Ist_IBF_Ini.Flag.as_kraftanfahren_aktiv << endl;
	if (Ist_IBF_Ini.Flag.as_kraftanfahren_aktiv == 0)
		cout << "Axiales Anwalzen in Kraft wurde nicht vorgewählt" << endl;
	else
		cout << "Axiales Anwalzen mit der Kraft FA" << "= " << " " << Soll_IBF_Ini.AS_Kraft_Anfahren << " vorgewählt" << endl;

	cout << endl << endl << endl;
	
	cout << "Auswahl des IBF-Modul:";
	if (Ist_IBF_Ini.Flag.Axial_Radialwalzen != 0)
	{
		cout << "***IBF - Flexibel radial Profilieren***" << endl;

		cout << "Vorschubsart " << ": ";
		switch (Ist_IBF_Ini.Radial.Schalter_Kont_DisKo)
		{

		case 0:
			cout << "const. Vorschub (Schalterstellung = 0)" << endl;
			break;
		case 1:
			cout << "Epsilon/Weg (Schalterstellung = 1) " << endl;
			cout << "Vorgabe des Epsilon " << "= " << Soll_IBF_Ini.Radial.eps_Vorschub << endl;
			break;
		case 2:
			cout << "Walzspaltverhälnis (Schalterstellung = 2)" << endl;
			cout << "Für Cr wurde " << Soll_IBF_Ini.Radial.Walzspalt_Cr << " vorgegeben " << endl;
			break;
		}

		cout << endl;

		cout << "Profilierwerkzeugbreite       " << "= " << Ist_IBF_Ini.Radial.Werkzeugbreite << endl;
		cout << "const.Vorschubgeschwindigkeit " << "= " << Soll_IBF_Ini.Radial.Vorschubgeschw_Dw << endl;
		if (Soll_IBF_Ini.Radial.delta_s != 0.0F && Soll_IBF_Ini.Radial.Stegstaerke != 0.0F)
		{
			cout << endl;
			cout << "ACHTUNG !!!  Vorgabe von Soll-Stegstärke und Delta_s unzulässig! " <<	"=> Delta_s wurde Null gesetzt " << endl;
			Soll_IBF_Ini.Radial.delta_s = 0.0;

			cout << "Soll-Stegstärke               " << "= " << Soll_IBF_Ini.Radial.Stegstaerke << endl;
			cout << "Delta_s                       " << "= " << Soll_IBF_Ini.Radial.delta_s << endl;
			cout << endl;
		}

		else if (Soll_IBF_Ini.Radial.delta_s == 0.0F && Soll_IBF_Ini.Radial.Stegstaerke == 0.0F)
		{
			cout << endl;
			cout << "ACHTUNG !!!  Soll-Stegstärke und Delta_s beide NULL ist unzulässig! " << endl;
			Soll_IBF_Ini.Radial.delta_s = 0.0;
			Soll_IBF_Ini.Radial.Stegstaerke = 40.0F;

			cout << "Soll-Stegstärke (DEFAULT-Wert)" << "= " << Soll_IBF_Ini.Radial.Stegstaerke << endl;
			cout << "Delta_s                       " << "= " << Soll_IBF_Ini.Radial.delta_s << endl;
			cout << endl;
		}
		else
		{
			cout << "Soll-Stegstärke               " << "= " << Soll_IBF_Ini.Radial.Stegstaerke << endl;
			cout << "Delta_s                       " << "= " << Soll_IBF_Ini.Radial.delta_s << endl;
		}

		cout << endl;
		cout << endl;
		cout << "Anzahl der Umdrehungen in der Rundungsphase" << "= " << Soll_IBF_Ini.Radial.Umdrehungen << endl;
		cout << endl;
		cout << "Rohlingshöhe" << "= " << Soll_IBF_Ini.Radial.Rohlinghoehe << endl;
		cout << endl;
		cout << "Vorschubgeschwindigkeit Axialschlitten (nur im case 17)" << "= " << Soll_IBF_Ini.Radial.Vorschubgeschw_ASO << endl;
		cout << endl;
	} //endif (Ist_IBF_Ini.Flag.Axial_Radialwalzen != 0)

	else
	{
		cout << "***IBF - Flexibel axial Profilieren***" << endl;

		cout << " Kragenbreite                                " << "= " << Ist_IBF_Ini.Axial.Kr_geo.Kr_Br << endl;
		cout << " Kragendurchmesser vordere Kante             " << "= " << Ist_IBF_Ini.Axial.Kr_geo.Kr_d_nenn_vorne <<	endl;
		cout << " berechneter Nenndurchmesser Kragenmittelpkt." << "= " << Ist_IBF_Ini.Axial.Kr_geo.Kr_d_nenn_mitte <<	endl;
		cout << " Kragendurchmesser vordere Kante             " << "= " << Ist_IBF_Ini.Axial.Kr_geo.Kr_d_nenn_hinten << endl;
		cout << " berechneter Abstand Del_Kr_Br               " << "= " << Ist_IBF_Ini.Axial.Kr_geo.Del_Kr_AGR << endl;
		cout << " max. Profilierungstiefe                     " << "= " << Ist_IBF_Ini.Axial.Kr_geo.max_Pr_Tiefe << endl;
		cout << " Anfahrdurchmesser                           " << "= " << Ist_IBF_Ini.Axial.Anfahrdurchm << endl;
		cout << " Zustellgeschwindigkeit des Axialschlittens  " << "= " << Ist_IBF_Ini.Axial.Vorschub << " [mm/U]" << endl;

		cout << " Anzahl der Profile                          " << "= " << Ist_IBF_Ini.Axial.Profilanzahl << endl;
		for (int i = 0; i < Ist_IBF_Ini.Axial.Profilanzahl; i++)
		{
			cout << i + 1 << ". Profilierposition                   " << "= " << Ist_IBF_Ini.Axial.AGR_Pr[i] << endl;
			cout << i + 1 << ". Profiliertiefe                      " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[i] << endl;
		}
		cout << endl;
		cout << " Minimale Walzhöhe ist vorgegeben mit" << "= " << Soll_IBF_Ini.min_ASO_Pos << endl;
		cout << " Soll_Inter.ag_mode" << "= " << Soll_Inter_Ini.ag_mode << endl;
	}

	if (Ist_IBF_Ini.Axial.Turbine.Turbinenscheibe == 1)
	{
		cout << "Strategie Turbinenscheibe vorgewählt" << endl;
		cout << endl;
		if (Ist_IBF_Ini.Flag.Bissverhaeltnis == 1)
		{
			cout << "Pro Ebene werden " << Ist_IBF_Ini.Axial.Biss.Anzahl << " Bisse mit dem Versatz von je  " << Ist_IBF_Ini.Axial.Biss.Verhaeltnis << "  Prozent gemacht" << endl;
			cout << " Insgesamt werden " << Ist_IBF_Ini.Axial.Biss.Anzahl_zweite_Ebene << " Bisse gewalzt" << endl;
			cout << endl;
			cout << "1. Profiltiefe (1. Ebene 1. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[0] << endl;
			cout << "2. Profiltiefe (1. Ebene 2. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[1] << endl;
			cout << "3. Profiltiefe (1. Ebene 3. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[2] << endl;
			cout << endl;
			cout << "4. Profiliertiefe (2. Ebene 1. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[3] << endl;
			cout << "5. Profiliertiefe (2. Ebene 2. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[4] << endl;
			cout << "6. Profiliertiefe (2. Ebene 3. Profil)            " << "= " << Ist_IBF_Ini.Axial.Pr_Tiefe[5] << endl;
			cout << endl;
			cout << "1. Profilierposition 1. Ebene                      " << "= " << Ist_IBF_Ini.Axial.AGR_Pr[0] << " mm" << endl;
			cout << "1. Profilierposition 2. Ebene                      " << "= " << Ist_IBF_Ini.Axial.AGR_Pr[3] << " mm" << endl;
			cout << endl;
		}
		else
		{
			cout << "ACHTUNG !!! Biss nicht vorgewählt !!!" << endl;
		}
	}

	cout << endl;
	if (Ist_IBF_Ini.Flag.DA_Jenkouk_DW_Regelung == 1)
	{
		cout << "***!!! DA-Dornwalzenregelung vorgewählt !!!***" << endl;
		if (Ist_IBF_Ini.Flag.DA_Jenkouk_Messen_ohne_Fahren != 0)
		{
			cout << "Es wird gemessen und die Dornwalze (idealerweise) verfahren" << endl;
		}
		else
			cout << "Es wird NUR gemessen" << endl;
			cout << "Nachfolgende Werte wurden eingelsen" << endl;
			cout << "Abstand C :" << Ist_IBF_Ini.DW_Regelung.Abstand_C << endl;
			cout << "Nullpunkt :" << Ist_IBF_Ini.DW_Regelung.Messwert_Nullpunkt << endl;
			cout << "TR-Radius :" << Ist_IBF_Ini.DW_Regelung.Tastrollen_Radius << endl;
			cout << "Offset    :" << Ist_IBF_Ini.DW_Regelung.Offset << endl;
		}
	else
		cout << "Jenkouk Regler EIN(1) oder AUS(0) ? ->:" << Ist_IBF_Ini.Flag.DA_Jenkouk_DW_Regelung << endl << endl;
	
	if (Ist_IBF_Ini.Test.Flag == 1)
	{
		cout << "***IBF - Testwalzungen vorgewählt !!!***" << endl;
		cout << " Simulierter Ringdurchmesser                   " << "= " << Ist_IBF_Ini.Test.Ring_AD << endl;
	}
	
	/* Bissverhältnis*/
	if (Ist_IBF_Ini.Flag.Bissverhaeltnis == 1)
	{
		Soll_IBF_Ini.Axial.AGR_Pr[0] = Ist_IBF_Ini.Axial.AGR_Pr[0]; // Notwendig wenn mehrere Bisse gewalzt werden, damit die AG nach Positionierung per Biss nicht auf ersten Wert 'zurückfährt'
		Soll_IBF_Ini.Axial.Biss.AGR_Pr_Merker = Ist_IBF_Ini.Axial.AGR_Pr[0];
	}


	// Abbruchbedingung für Iteration
	breakIter	= 0;
	
};

///////////////////////////////////////////////////////////////////////////////
// Destruktor: Win_RWTH_EXCH
///////////////////////////////////////////////////////////////////////////////

Win_RWTH_EXCH::~Win_RWTH_EXCH(void) {
};

//////////////////////////////////////////////////////////////////////////////
//  Deklarationen class logChannel
//////////////////////////////////////////////////////////////////////////////

logChannel::logChannel(char* n, long& l)
{
	name = n;
	piData = &l;
	sym = false;
	Int = true;
	return;
};
logChannel::logChannel(char* n, int& i)
{
	name = n;
	piData = (long*)&i;
	sym = false;
	Int = true;
	return;
};
logChannel::logChannel(char* n, float& f)
{
	name = n;
	pfData = &f;
	sym = false;
	Int = false;
	return;
};
logChannel::logChannel(char* n, char& c)
{
	name = n;
	psData = &c;
	sym = true;
	Int = false;
	return;
};
int logChannel::snapShot()
{
	if (sym)
	{
		sdata.push_back(*psData);
		return 0;
	};
	Int ? idata.push_back(*piData) : fdata.push_back(*pfData);
	return 0;
}
size_t logChannel::size(void)
{
	if (sym)
		return (sdata.size());
	if (Int)
		return (idata.size());
	else
		return (fdata.size());
};
string logChannel::sGetValue(unsigned int num=0)
{
	string ret = "";
	if (sym)
		return (ret = sdata[num]);
	char buffer[20] = { 0 };
	if ((size_t)num < this->size())
		if (Int)
			sprintf_s(buffer, "%i", idata[num]);
		else
			sprintf_s(buffer, "%f", fdata[num]);
	if (buffer[0] != 0)
		ret = buffer;
	if (ret.find(".") != ret.npos)
		ret.replace(ret.find("."), (size_t)1, ",");
	return (ret);
};

logChannel::logChannel(void)
{
	return;
};

logChannel::~logChannel(void)
{
	return;
};

///////////////////////////////////////////////////////////////////////////////
// Deklaration class dataLog
///////////////////////////////////////////////////////////////////////////////

string dataLog::setName(string n)
{
	(n != "")? name = n : n = name;
	return n;
};
int dataLog::pushChannel(logChannel lC)
{
	ChannelSet.push_back(lC);
	return 0;
};
int dataLog::snapShot()
{
	for (size_t i = 0; i < ChannelSet.size(); i++)
		ChannelSet[i].snapShot();
	return 0;
};
int dataLog::writeCSV(string ofn)
{
	if (ofn == "")
		ofn = name;
	if (ofn == "")
		ofn = (name = "default");
	ofn += ".csv";
	ofstream os(ofn);

	for (size_t col = 0; col < ChannelSet.size(); col++)
	{
		os << ChannelSet[col].getName() << ";";
	}
	os << endl;
	for (size_t row = 0; row < ChannelSet[0].size(); row++)
	{
		for (size_t col = 0; col < ChannelSet.size(); col++)
		{
			os << ChannelSet[col].sGetValue(row) << ";";
		}
		os << endl;
	}
	os.close();
	return 0;
};
dataLog::dataLog(void)
{
	written = false;
	name = "dataLog";
	return;
};

dataLog::~dataLog(void)
{
	return;
};