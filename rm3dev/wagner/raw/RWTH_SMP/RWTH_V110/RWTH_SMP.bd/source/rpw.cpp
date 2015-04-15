#include "../inc/rpw.hpp"
#include "time.h"
#include <math.h>

//---------------------------------------------------------------------------
// Methode RPW::RPW
//---------------------------------------------------------------------------

RPW::RPW(void)
{
	sin_kw_winkel_halbe =sin(22.5F*PI/180.0F);  // Sinus halber Kegelwalzenwinkel
	
	/* Setzt alle Offset Variablen dieser Klasse auf 0. */
	offset_rs	= 0.0F;
	offset_agr	= 0.0F;
	offset_aso	= 0.0F;
	offset_asu	= 0.0F;
	offset_tr	= 0.0F;
	return;
}

int RPW::Main_RAW(			int						ITER,
					const	Def_Ein_Puff&			Ein_Puff,
					const	Def_Lokal_Puff&			Lokal_Puff,
					const	Def_Aus_Puff&			Aus_Puff,
					const	Def_Ein_Onli&			Ein_Onli,
					const	Def_Aus_Onli&			Aus_Onli,
							Def_Ist_Inter&			Ist_Inter,
							Def_Soll_Inter&			Soll_Inter,
							Def_IBF_Allgemein_SOLL&	Soll_IBF,
							Def_IBF_Allgemein_IST&	Ist_IBF )
{
	// Defintion der lokalen Variabeln
	// struct Def_IBF_Allgemein *IBF_Allgemein;
	// Los gehts
	Ist_IBF.Iter = ITER;
	Ist_Inter.Test.Flag		= Ist_IBF.Test.Flag;
	Ist_Inter.Test.Ring_AD	= Ist_IBF.Test.Ring_AD;

	// Istwerte aufbereiten
	Istwerte_RAW(Ein_Onli, Ein_Puff, Lokal_Puff, Aus_Puff, Ist_Inter );

	// Spezielle Variablen aus Ist_Inter an IST_IBF-Struktur uebergeben
	IstIBF_IstInter(Ist_Inter, Ist_IBF);

	// Spezielle Variablen aus Soll_IBF an IST_IBF-Struktur uebergeben
	IstIBF_SollIBF(Soll_IBF, Ist_IBF);

	Kr_Geo_berechnen(Ist_IBF);
	Kr_Geo_pruefen(Ist_IBF);

	if (Ist_IBF.Flag.Axial_Radialwalzen==3)	// Schuesselwalzen
	{
		// Walzformgeometrie beim Schuesselwalzen hier aktualisieren
		Schuessel_Form_IST( Ist_IBF , Ist_Inter );
	}
	else
	{
		Soll_Inter.rs_v  = Aus_Onli.ds_dh_sp_hp.s_punkt;
		Soll_Inter.aso_v = Aus_Onli.ds_dh_sp_hp.h_punkt;
	}
	/* Flag setzen 5 prozent erreicht fuer Test Zentrierung */
	// Ein_Onli.rz_f_radial_5proz_erkannt = 1;

	// Hauptprogrammteil des IBF-Tasks
	Main( Ist_Inter,
		  Ist_IBF,
		  Soll_Inter,
		  Soll_IBF );

	return TRUE;
}

int RPW::Istwerte_RAW(	const	Def_Ein_Onli	&Ein_Onli,
						const	Def_Ein_Puff	&Ein_Puff,
						const	Def_Lokal_Puff	&Lokal_Puff,
						const	Def_Aus_Puff	&Aus_Puff,
								Def_Ist_Inter	&Ist_Inter )
{
/* Ist-Achsenpositionen  */
	Ist_Inter.rs_pos		= Ein_Puff.form_mess_of.dis_hw_dw;						/* Aktuelle Radialschlittenposition   [mm]*/
	Ist_Inter.ag_pos		= Ein_Puff.form_mess_of.da	- Ein_Puff.pos_laser_u_of;	/* Axialgeruestposition (hergeleitet) [mm]*/
	Ist_Inter.ag_pos_real	= Ein_Onli.Ibf_actual.Ist_AG;							/* Aktuelle Axialgeruestposition      [mm]*/
	Ist_Inter.aso_pos		= Ein_Puff.form_mess_of.dis_aw;							/* Aktuelle Axialschlittenposition    [mm]*/
	Ist_Inter.asu_pos		= 0.0F;
	Ist_Inter.tr_pos		= Ein_Puff.pos_laser_u_of + Ein_Puff.awu_geometrie.l_fehlende_spitze;	/*Aktuelle Tastrollenposition  [mm]*/

/*--- Geometrie ---*/

/* Maschinengeometrie */
	Ist_Inter.Werkzeug.Durchmesser_HW		= Ein_Puff.hw_geometrie.d_nenn;
	Ist_Inter.Werkzeug.Durchmesser_DW		= Ein_Puff.dw_geometrie.d_nenn;
	Ist_Inter.Werkzeug.l_fehlende_spitze	= Ein_Puff.awu_geometrie.l_fehlende_spitze;

	Ist_Inter.hw_ir = Ein_Puff.hw1_motor.getriebe_untersetzung;				/* Getriebeuntersetzung Hauptwalzenmotor  i= n_Antrieb/n_Abtrieb (i>1 ist Untersetzung) */
	Ist_Inter.kw_ia = Ein_Puff.awu_motor.getriebe_untersetzung;				/* Getriebeuntersetzung Kegelwalzenmotor */

	sin_kw_winkel_halbe = (float)sin(Ein_Puff.awu_geometrie.winkel_bo * 0.5F);  /* Sinus halber Kegelwalzenwinkel */


/* Ringgeometrie */
	if (Ist_Inter.Test.Flag == 0)
	/* Testmodus ermöglicht die Simulation des IBF-Walzzyklus ohne Ring,
	   besonders wenn die Tastrollesimulation in CARWIN nicht erwünscht wird */
	{
		/* Äusserer Durchmesser [mm]    */
		Ist_Inter.da	= Aus_Puff.form_ring.da;
		Ist_Inter.da_of = Ein_Puff.form_mess_of.da;

		/* Innerer   Durchmesser [mm]    */
		Ist_Inter.di	= Aus_Puff.form_ring.di;
		Ist_Inter.di_of = Ein_Puff.form_mess_of.di;

		/* Mittlerer Durchmesser [mm]    */
		Ist_Inter.dm	= Aus_Puff.form_ring.dm;
		Ist_Inter.dm_of = Ein_Puff.form_mess_of.dm;
	}
	else // Testbetrieb
	{
		/* Äusserer Durchmesser [mm]    */
		Ist_Inter.da	= Ist_Inter.Test.Ring_AD;
		Ist_Inter.da_of = Ist_Inter.Test.Ring_AD;

		/* Innerer   Durchmesser [mm]    */
		Ist_Inter.di	= Ist_Inter.Test.Ring_AD - 2 * Aus_Puff.s1r;
		Ist_Inter.di_of = Ist_Inter.Test.Ring_AD - 2 * Aus_Puff.s1r;

		/* Mittlerer Durchmesser [mm]    */
		Ist_Inter.dm	= (Ist_Inter.da + Ist_Inter.di) / 2;
		Ist_Inter.dm_of = Ein_Puff.form_mess_of.dm;
	}

	Ist_Inter.fertig_ho_soll = Aus_Puff.ist_walzform.hm;
	Ist_Inter.fertig_wd_soll = Aus_Puff.ist_walzform.sm;

	Ist_Inter.h0r = Aus_Puff.h0r;     					/* Ringhoehe radial einlaufend  [mm]    */
	Ist_Inter.h1r = Aus_Puff.h1r;     					/* Ringhoehe radial auslaufend  [mm]    */
	Ist_Inter.h0a = Aus_Puff.h0a;     					/* Ringhoehe axial  einlaufend  [mm]    */
	Ist_Inter.h1a = Aus_Puff.h1a;     					/* Ringhoehe axial  auslaufend  [mm]    */
	Ist_Inter.h1a_of = Ein_Puff.form_mess_of.dis_aw;

	Ist_Inter.s0a = Aus_Puff.s0a;     					/* Wanddicke axial  einlaufend  [mm]    */
	Ist_Inter.s0r = Aus_Puff.s0r;     					/* Wanddicke radial einlaufend  [mm]    */
	Ist_Inter.s1a = Aus_Puff.s1a;     					/* Wanddicke axial  auslaufend  [mm]    */
	Ist_Inter.s1r = Aus_Puff.s1r;     					/* Wanddicke radial auslaufend  [mm]    */
	Ist_Inter.s1r_of = Ein_Puff.form_mess_of.dis_hw_dw;
	Ist_Inter.sfh = Aus_Puff.s_ekv;						/* Wanddicke bei Fertighoehe    [mm]    */

	Ist_Inter.skw = 0.0F;
	Ist_Inter.skw_of = 0.0F;
	Ist_Inter.wa_dvol = Aus_Puff.dvol_ring_proz;		/* Berechnete Volumendifferenz [%]       */

	Ist_Inter.Vorform.sm = Ein_Puff.vorform.sm;         /* Wandstärke Vorform aus Carwin [mm]    */
	Ist_Inter.Vorform.da = Ein_Puff.vorform.da;         /* Durchmesser Vorform  aus Carwin [mm]  */
	Ist_Inter.Vorform.hm = Ein_Puff.vorform.hm;         /* Rohlingshoehe Vorform aus Carwin [mm] */


	if (Ist_Inter.Test.Flag == 0)	  /* Testmodus ermöglicht die Simulation des IBF-Walzzyklus
									     ohne Ring und ohne eingeschaltete Antriebe */
	{
		Ist_Inter.hw_n  = Ein_Puff.n_hw_motor_ist  / Ist_Inter.hw_ir;		  /* Istdrehzahl Hauptwalze               [1/s] */
		Ist_Inter.kwo_n = Ein_Puff.n_awo_motor_ist / Ist_Inter.kw_ia;		  /* Istdrehzahl Axialwalzen oben         [1/s] */
		Ist_Inter.kwu_n = Ein_Puff.n_awu_motor_ist / Ist_Inter.kw_ia;		  /* Istdrehzahl Axialwalzen unten Debye->[1/s]_ohne_  /MIN_FAK || MRAW->[1/min]*/
	}
	else if (Ist_Inter.Test.Flag == 1)
	{
		Ist_Inter.hw_n	= 20.0F;      /* Istdrehzahl Hauptwalze              [1/s] */
		Ist_Inter.kwo_n = 16.0F;      /* Istdrehzahl Axialwalzen oben        [1/s] */
		Ist_Inter.kwu_n = 16.0F;      /* Istdrehzahl Axialwalzen unten Debye->[1/s]_ohne_  /MIN_FAK || MRAW->[1/min]*/
	}

	Ist_Inter.Werkzeug.Drehzahl_HW = Ist_Inter.hw_n;						/* Drehzahl (grad) der Hauptwalze [1/s]*/
	Ist_Inter.Werkzeug.Winkelgeschw_omega_HW = Ist_Inter.hw_n * (2 * PI);	/* Winkelgeschwindigkeit (rad) der HW  [1/sec] //(omega=2*PI*n)*/
	Ist_Inter.Werkzeug.Winkel_grad_tU_HW	 = Ist_Inter.hw_n * 360;		/* Winkelgeschwindigkeit (Grad) der HW  [°/sec] */
	Ist_Inter.Werkzeug.tU_HW = 1 / Ist_Inter.hw_n;							/* Zeit(Periode) für 1 Umdrehung der HW  [s]*/
	Ist_Inter.Werkzeug.U_v_HW = Ist_Inter.Werkzeug.Winkelgeschw_omega_HW
								* Ist_Inter.Werkzeug.Durchmesser_HW / 2;    /* Umfangsgeschwindigkeit der HW [mm/s] */

	if (Ist_Inter.hw_n == 0)
	{
		Ist_Inter.Werkzeug.Ringumdrehung = 0.0F;
	}
	else
	{
		Ist_Inter.Werkzeug.Ringumdrehung = Ist_Inter.da / (Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.hw_n);     /* Zeit fuer eine Ringumdrehung [s] */
	}
	/* Abfangen unsinniger Werte */
	if (Ist_Inter.Werkzeug.Ringumdrehung > 500.0F)
	{
		Ist_Inter.Werkzeug.Ringumdrehung = 0.0F;
	}

	Ist_Inter.Werkzeug.omega_Ring = Ist_Inter.Werkzeug.U_v_HW * 2 /	Ist_Inter.da;	  /* Winkelgeschwindigkeit OMEGA Ring  [1/sec] //(omega=2*PI*n)*/
	Ist_Inter.Werkzeug.Winkel_grad_tU_Ring = Ist_Inter.Werkzeug.omega_Ring * 180 /PI;	  /* Aktueller Winkel  [°] */
	Ist_Inter.Werkzeug.Antrieb_ASO.ma_ist = 0.0F;

	/* für Loggermöglichkeit der Antriebsdrehzahlen*/
	Ist_Inter.n_hw_motor_ist  = Ein_Puff.n_hw_motor_ist;  /* HW-Motor        [1/s]*/
	Ist_Inter.n_kwo_motor_ist = Ein_Puff.n_awo_motor_ist; /* KWO-Motor       [1/s]*/
	Ist_Inter.n_kwu_motor_ist = Ein_Puff.n_awu_motor_ist; /* KWU-Motor       [1/s]*/

	/* Kräfte (gefiltert) */
	Ist_Inter.rs_f = Aus_Puff.fr_mf;                /* Radiale Kraft gefiltert  [N] */
	Ist_Inter.as_f = Aus_Puff.fa_mf;                /* Axiale Kraft gefiltert   [N] */
	Ist_Inter.ag_f = Lokal_Puff.fag_mf;             /* Axialgerüst              [N] */

	/* Messwerte-IBF-Zusatzachsen */
	Ist_Inter.Ibf_Achse1 = Ein_Onli.Ibf_actual.Ibf_Achse1;     /* Messachse IBF 1 - Auslaufseite Sensor Tastrolle 'innen' [mm] */
	Ist_Inter.Ibf_Achse2 = Ein_Onli.Ibf_actual.Ibf_Achse2;     /* Messachse IBF 2 - Auslaufseite Sensor Tastrolle 'außen' [mm] */
	Ist_Inter.Ibf_Achse3 = Ein_Onli.Ibf_actual.Ibf_Achse3;     /* Messachse IBF 3 [mm] */
	Ist_Inter.Ibf_Achse4 = Ein_Onli.Ibf_actual.Ibf_Achse4;     /* Messachse IBF 4 [mm] */

	//Uebergabe der aktuellen Zentrierarmparameter an Ist_Inter
	Ist_Inter.zar_pos	= Ein_Onli.Ibf_actual.Ist_ZEN_A;    /* Aktuelle Zentrierarmposition 'Auslauf' [mm]*/
	Ist_Inter.zal_pos	= Ein_Onli.Ibf_actual.Ist_ZEN_E;    /* Aktuelle Zentrierarmposition 'Einlauf' [mm]*/
	Ist_Inter.zar_f		= Ein_Onli.rz_f_ist_zen_ausl;		/* Zentrierkraft Auslaufseite	[N] */
	Ist_Inter.zal_f		= Ein_Onli.rz_f_ist_zen_einl;		/* Zentrierkraft Einlaufseite	[N] */

	// Dez. 2014 : entstanden im Rahmen der 'Schuesselwalzstrategie'
	// Anmerkungen: Einlaufseite = links ; Auslaufseite = rechts
	//				Ein- bzw. Auslaufseite bezieht sich IMMER auf den Radial-WS
	//				Der Ring rotiert gegen den Uhrzeigersinn (von oben betrachtet)
	//Uebergabe der aktuellen Druckrollenparameter an Ist_Inter
	Ist_Inter.DRR_Param.DrR_A.Pos = Ein_Onli.Ibf_actual.Ist_DRR_A;	/*Aktuelle Druckrollenposition 'Auslauf' [mm]*/
	Ist_Inter.DRR_Param.DrR_E.Pos = Ein_Onli.Ibf_actual.Ist_DRR_E;	/*Aktuelle Druckrollenposition 'Einlauf' [mm]*/
	Ist_Inter.DRR_Param.DrR_A.Kraft	= Ein_Onli.Ibf_actual.F_DRR_A;	/*[N]*/
	Ist_Inter.DRR_Param.DrR_E.Kraft	= Ein_Onli.Ibf_actual.F_DRR_E;	/*[N]*/
	
	return TRUE;
}

int RPW::IstIBF_IstInter(	struct Def_Ist_Inter&			Ist_Inter,
							struct Def_IBF_Allgemein_IST&	Ist_IBF )
{
	// Funktion dient dem Austausch der IST-Werte zwischen der INTER-Struktur und IBF-Struktur
	// los gehts


	/* Übergabe statischer Werte, die sich zur Laufzeit nicht ändern */

	/* Geometrien */
	Ist_IBF.Vorring.D_Null = Ist_Inter.Vorform.da;					/* Übergabe der Rohlingswanddicke an IBF-Struktur */
	Ist_IBF.Vorring.Start_Ringhoehe = Ist_Inter.Vorform.hm;			/* Übergabe der Rohlingshoehe an IBF-Struktur */
	Ist_IBF.Vorring.Wandstaerke_Null = Ist_Inter.Vorform.sm;		/* Übergabe der Rohlingswanddicke an IBF-Struktur */
	Ist_IBF.Axial.Kr_geo.sin_kw_winkel_halbe = sin_kw_winkel_halbe; /* Sinus des halber Kegelwalzenwinkels*/
	Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw = Ist_Inter.Werkzeug.l_fehlende_spitze;	/* Länge theo. Spitze untere KW */

	/* Übergabe dynamischer Werte, die sich während Laufzeit aendern */

	/* Allgemein */
	Ist_IBF.da = Ist_Inter.da;                           // aktueller Ringdurchmesser in mm
	Ist_IBF.di = Ist_Inter.di;                           // aktueller Ringinnendurchmesser (aus Carwin)
	Ist_IBF.RS_Pos = Ist_Inter.rs_pos;                   // aktuelle Dornschlittenposition in mm
	Ist_IBF.AG_Pos = Ist_Inter.ag_pos_real;              // aktuelle Axialgerüstposition in mm
	//Ist_IBF.AG_Pos   = Ist_Inter.ag_pos;               // aktuelle Axialgerüstposition in mm
	Ist_IBF.ASO_Pos = Ist_Inter.aso_pos;                 // aktuelle Axialschlittenposition oben in mm

	Ist_IBF.FR = Ist_Inter.rs_f;                         // aktuelle Radialkraft in [N]
	Ist_IBF.FA = Ist_Inter.as_f;                         // aktuelle Axialkraft in [N]     

	Ist_IBF.Wanddicke_Ist = Ist_Inter.s1r;               // aktuelle Wandstärke, Radialschlitten Auslaufseite [mm] 

	Ist_IBF.Zeit.Ringumdrehung = Ist_Inter.Werkzeug.Ringumdrehung; // aktuelle Zeit für eine Ringumdrehung [s]

	/* Modul: Radial */

	// Filter der Radialschlittenposition   
	// KP=1, Filterzeit Tf=0.3/Abtastzeit Ta=0.1 || (Filterzeit Tf vorher =1)
//	Ist_IBF.Radial.s_f_Filter.yF_neu = (1.0 * Ist_Inter.rs_pos
//										+ (0.3 / 0.1) * Ist_IBF.Radial.s_f_Filter.yF_alt) / ((0.3 / 0.1) + 1.0);
	Ist_IBF.Radial.s_f_Filter.yF_neu = ( Ist_Inter.rs_pos + 0.75F * Ist_IBF.Radial.s_f_Filter.yF_alt);
	Ist_IBF.Radial.s_f_Filter.yF_alt = Ist_IBF.Radial.s_f_Filter.yF_neu;
	Ist_IBF.Radial.s_f = Ist_IBF.Radial.s_f_Filter.yF_neu; /* Aktuelle gefilterte Wandstärke für das Radialprofilieren [mm] */


/*------------------------------------------------------*/
/* DA Jenkouk: April - Juli 2008                        */
/*------------------------------------------------------*/

	Ist_IBF.DW_Regelung.Messwert_A = Ist_Inter.Ibf_Achse1 - Ist_IBF.DW_Regelung.Messwert_Nullpunkt;     // vergl. Abb.' Kinematik und Geometrie' DA Jenkouk  [mm]
	Ist_IBF.DW_Regelung.Messwert_A_unten = abs(Ist_Inter.Ibf_Achse2 - Ist_IBF.DW_Regelung.Messwert_Nullpunkt_unten); //Betrag 
	Ist_IBF.DW_Regelung.U_v_HW = Ist_Inter.Werkzeug.U_v_HW;												// Umfangsgeschwindigkeit an Hauptwalze 
	Ist_IBF.DW_Regelung.DW_Durchmesser = Ist_Inter.Werkzeug.Durchmesser_DW;                             // Durchmesser der Dornwalze


	/* Projekt Formenspektrum */
	Ist_IBF.Formen.t_U_Viola = Ist_Inter.Werkzeug.Ringumdrehung;
	//Ist_IBF.Formen.proz_s = 20;		//prozentuale Wanddickenabnahme, wird jetzt aus ibfpara.dat eingelesen!!!
	//Ist_IBF.Formen.Profilflag = 1;	//wird jetzt aus ibfpara.dat eingelesen.

/*------------------------------------------------------*/
/* DA Otto: Dezember 2014			                    */
/* Projekt: Schuesselwalzen			                    */
/*------------------------------------------------------*/

// Transformation und Uebergabe der IST-Werte der Druckrollenregelung (DRRE-DRRA)
	Ist_IBF.DRR_Param = DRR_trans_IST( Ist_Inter , Ist_IBF );

// Transformation und Uebergabe der IST-Werte der Zentrierrollenregelung (ZERE-ZERA)
	Ist_IBF.ZER_Param	= ZER_trans_IST( Ist_Inter , Ist_IBF );
	Ist_IBF.ZAR_Pos		= Ist_IBF.ZER_Param.ZRA.MTS;
	Ist_IBF.ZAL_Pos		= Ist_IBF.ZER_Param.ZRE.MTS;

	return TRUE;
}

int RPW::IstIBF_SollIBF(	struct Def_IBF_Allgemein_SOLL&	Soll_IBF,
							struct Def_IBF_Allgemein_IST&	Ist_IBF )
{
	// Zuweisung Def_IBF_Allgemein_SOLL 

	// Übergeben der Parameter aus Soll_IBF/Ist_IBF Struktur

	Ist_IBF.Profilflag = Soll_IBF.Profilflag;
	Ist_IBF.InitAchse = Soll_IBF.InitAchse;
	Ist_IBF.ExitAchse = Soll_IBF.ExitAchse;

	/* Casting von Initachse, damit diese char-Variable gelogget werden kann */
	Ist_IBF.InitAchse_gecastet = (short)Soll_IBF.InitAchse;

	Ist_IBF.Axial.Profilflag = Soll_IBF.Axial.Profilflag;
	Ist_IBF.Radial.Profilflag = Soll_IBF.Radial.Profilflag;

	Ist_IBF.RS_Pos_Null = Soll_IBF.RS_Pos_Null;
	Ist_IBF.ASO_Pos_Null = Soll_IBF.ASO_Pos_Null;
	Ist_IBF.AG_Pos_Null = Soll_IBF.AG_Pos_Null;

	/* Startpositionen */
	Ist_IBF.RS_Pos_Start = Soll_IBF.RS_Pos_Start; 	// Positionen in 'Walzen' vor Profilieren 
	Ist_IBF.AG_Pos_Start = Soll_IBF.AG_Pos_Start;
	Ist_IBF.ASO_Pos_Start = Soll_IBF.ASO_Pos_Start;

	Ist_IBF.Rohling_s_angefahren = Soll_IBF.Rohling_s_angefahren; // Reelle Rohlingswanddicke nach dem Anfahren. Wichtig bei Anfahren in Kraft
	Ist_IBF.Rohling_h_angefahren = Soll_IBF.Rohling_h_angefahren; // Reelle Rohlingshöhe nach dem Anfahren. Wichtig bei Anfahren in Kraft

	/* Zähler */
	Ist_IBF.Zeit.t_Halte = Soll_IBF.Zeit.t_Halte;    // Allgemeiner Zeitzähler
	Ist_IBF.Axial.Pr_Num = Soll_IBF.Axial.Pr_Num;    // Aktuelle Profiliernummer


	/* Flags/Schalter */
	Ist_IBF.Flag.as_kraft_anfahren_erreicht = Soll_IBF.Flag.as_kraft_anfahren_erreicht;
	Ist_IBF.Flag.rs_kraft_anfahren_erreicht = Soll_IBF.Flag.rs_kraft_anfahren_erreicht;

	Ist_IBF.Flag.AG_Start_erreicht = Soll_IBF.Flag.AG_Start_erreicht;

	/* Bissversatz */
	if (Ist_IBF.Flag.Bissverhaeltnis == 1)
	{
		Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num] = Soll_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num];
		Ist_IBF.Axial.Biss.AG_Pos_Erreicht = Soll_IBF.Axial.Biss.AG_Pos_Erreicht;
	}

	/* Turbinenscheibe */
	Ist_IBF.Axial.Turbine.zweite_Ebene_erreicht = Soll_IBF.Axial.Turbine.zweite_Ebene_erreicht; // Bei Neustart muss sichergestellt werden, dass Wert geschrieben wird

	/* Projekt Formenspektrum */
	Ist_IBF.Formen.Profilflag = Soll_IBF.Formen.Profilflag;

	return TRUE;
}

//---------------------------------------------------------------------------
// Methode RWP::MAIN
//---------------------------------------------------------------------------

int RPW::Main(	struct Def_Ist_Inter&			Ist_Inter,
				struct Def_IBF_Allgemein_IST&	Ist_IBF,
				struct Def_Soll_Inter&			Soll_Inter,
				struct Def_IBF_Allgemein_SOLL&	Soll_IBF )
{
	float eps = 1.0F;          // Positioniergenauigkeit michl:-> war 0.1F

	//########## Hand- bzw. Automatiksteuerung ausgehend von Koppers Position bei Walzenstart ##########

	// Geschwindigkeiten sind in axpro.h vorbelegt
	// Startposition für jeweilige Ringgeometrie in axpro.h eintragen?

	// Da Messwerte von Anlage und Mess-Schieber differieren (...), vor Beginn 
	// des Profilierens Aussenkontur (radial/axial) des Ringes von Hand anfahren ??
	// -> von Hand angefahrene Positionen beschreiben den Ausgangszustand ??

	switch (Ist_IBF.Profilflag)
	{
		/* IBF_Allgemein.IBF_Allgemein.Profilflag in axpro.h definiert,
		* bei Step 6 in interfac auf -1 gesetzt! */

	case -1:
		// --------------------------------------------------
		//----- Startpositionen lesen, Sollwertvorgabe ------
		//---------------------------------------------------						
		if (Ist_IBF.Flag.Axial_Radialwalzen == 3) // Schuesselwalzen
		{
			// Das Schuesselwalzen erfordert eine spezielle Anfahrroutine
			schuesselWalzen.Main(Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
			break;
		}

		/* Geschwindigkeiten  */
		Soll_IBF.RS_V		= 0.0F;
		Soll_IBF.ASO_V		= 0.0F;
		Soll_IBF.Soll_ASU_V = 0.0F;
		Soll_IBF.AG_V		= 0.0F;
		Soll_IBF.ZAL_V		= 0.0F;
		Soll_IBF.ZAR_V		= 0.0F;

		/* Kräfte */
		Kraftsteuerung(Ist_IBF, &Soll_IBF);

		/* Drehzahl */
		Soll_Inter.kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
		Soll_Inter.kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

		//-----------------------------------------------------------------------
		//------------Vorgabe für Startposition des Radialschlitten--------------
		//-----------------------------------------------------------------------

		/* Nullpkt. Radialschlitten entsprechend vorgegeber Wandstärke   [mm] */
		Soll_IBF.RS_Pos_Null = Ist_IBF.Vorring.Wandstaerke_Null;

		/* definiert für RS_Pos in case 'a'*/
		Soll_IBF.RS_Pos = Soll_IBF.RS_Pos_Null;

		/* um Wandstärke von HW weg VJ Regleranalyse */
		Soll_IBF.RS_Pos_Start = Ist_IBF.Vorring.Wandstaerke_Null;

		//-----------------------------------------------------------------------
		//------------ Vorgabe für Startposition der Axialschlitten -------------
		//------------    Es ist zu unterscheiden, ob Axial bzw.    ------------- 
		//------------     Radial Profiliert werden soll            -------------
		//-----------------------------------------------------------------------

		/* Radialprofilieren oder Formenspektrum */
		if (Ist_IBF.Flag.Axial_Radialwalzen != 0)
		{
			/* AG_Pos == auslesen der Werte aus PA-Karte inkl. Offset */
			Soll_IBF.AG_Pos_Start	= Ist_IBF.AG_Pos;
			Soll_IBF.AG_Pos_Null	= Ist_IBF.AG_Pos;
			Soll_IBF.AG_Pos			= Ist_IBF.AG_Pos;
		}
		else
		{
			//Berechnung mit anzugebenden Startdurchmesser
			Soll_IBF.AG_Pos_Start = Ist_IBF.Axial.Anfahrdurchm
				- Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
				- Ist_IBF.Axial.Kr_geo.Kr_Br
				+ Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw;

			Soll_IBF.AG_Pos_Null = Soll_IBF.AG_Pos_Start;
			/* Bereits hier muss Wert an Soll_IBF.AG_Pos übergeben werden werden 
			 * (->Ende der Funktion an Soll_Inter.ag_pos und in rwth_exch.cpp) */
			/* Ansonsten ist die Vorgabe für AG=0 beim Anfahren, dieser Wert kann 
			 * nicht erreicht werden..und Gerüst würde entsprechend vorfahren... */
			Soll_IBF.AG_Pos = Soll_IBF.AG_Pos_Start;
		}

		//--------------------------------------------------------------------------------
		//------------Vorgaben für oberen Axialschlitten----------------------------------
		//--------------------------------------------------------------------------------

		/* Vorgabe der Ringhöhe, die in CARWIN vorgegeben wird */
		Soll_IBF.ASO_Pos_Null = Ist_IBF.Vorring.Start_Ringhoehe;
		Soll_IBF.ASO_Pos_Start = Soll_IBF.ASO_Pos_Null;

#if (FALSE)
			  _settextposition(28,1);
			  printf("case -1");
#endif

		if (Ist_IBF.Zeit.t_Halte <= 0)
		{
			/* Für Anfahren des Dornes, wenn Kraftregelung aktiviert wurde,
			* allerdings nicht in Kraft angewalzt werden soll*/
			if (Ist_IBF.Flag.rs_kraftregler_aktiv == 1)
			{
				Soll_IBF.Zeit.t_Halte = 70;
			}
			else
			{
				/* 100 ms = 0,1 Sekunden 
				* t_Halte = 10*2*diam_f/(diam_hw*f_H); 
				* Haltezeit entspricht 1 Ringumdrehung,
				* nötig als Kriterium bei Kraftanfahrposition */
				Soll_IBF.Zeit.t_Halte = 30;
			}
			Soll_IBF.Profilflag = 0;
		}
		Soll_IBF.Zeit.t_Halte--;
		break; // case -1;

	case 0:
		//----------------------------------------------------------------
		//----------------Routine für Startposition-----------------------
		//----------------------------------------------------------------

		switch (Ist_IBF.InitAchse)
		{
			/* Programexample for interface-testing 
			 * Spezieller Programmcode zur Verifikation einer Dornbewegung, 
			 * Axialgerüst usw. 
			 * Ausgangswandicke entspricht der Carwinwanddicke. Diese soll 
			 * um 100 mm reduziert werden mit v=2.0 mm/s und anschließend 
			 * wieder zurücke auf Ausgangswanddicke 
			 *
			 *
			 * !!!ACHTUNG!!! in Datei rwth_task.cpp muss die Initialisierung 
			 * wieder geändert werden, wenn richtig gewalzt werden soll */

		case 'v':

			/* Geschwindigkeiten  */
			Soll_IBF.RS_V	= 5.0F;
			Soll_IBF.ASO_V	= 0.0F;
			Soll_IBF.AG_V	= 0.0F;
			Soll_IBF.ZAL_V	= 0.0F;
			Soll_IBF.ZAR_V	= 0.0F;

			/* Kräfte */
			Kraftsteuerung(Ist_IBF, &Soll_IBF);

			/* Positionen */
			// Aufruf des Jenkouk-Funktionsblock
			DA_Jenkouk_Regler(Ist_IBF, &Soll_IBF);

			if (Ist_IBF.RS_Pos >= (Soll_IBF.RS_Pos - 1.0F) || Ist_IBF.RS_Pos <= (Soll_IBF.RS_Pos + 1.0F))
			{
				// Soll_IBF.InitAchse = 'w';
				// Soll_IBF.Zeit.t_Halte = 20;                                   
			}

			if (Ist_IBF.Flag.DA_Jenkouk_AG_Analyse == 1)
			{
				Soll_IBF.InitAchse		= 'w';
				Soll_IBF.Zeit.t_Halte	= 10;
			}
			break;

		case 'w':
			/*Analyse Reglerverhalten Axialgerüst DA Jenkouk */

			/* Geschwindigkeiten  */
			Soll_IBF.RS_V	= 0.0F;
			Soll_IBF.ASO_V	= 0.0F;
			Soll_IBF.AG_V	= 100.0F;
			Soll_IBF.ZAL_V	= 0.0F;
			Soll_IBF.ZAR_V	= 0.0F;

			/* Kräfte */
			Kraftsteuerung(Ist_IBF, &Soll_IBF); //Funktionsaufruf

			/* Betriebsart */


			/* Positionen */
			if (Ist_IBF.Zeit.t_Halte <= 0)
			{

				/* Dorn verfährt um 20 mm VJ */
				Soll_IBF.RS_Pos		= Soll_IBF.RS_Pos_Start;
				Soll_IBF.AG_Pos		= 700.0F;
				Soll_IBF.ASO_Pos	= 80.0F;
				Soll_IBF.ZAL_Pos	= 350.0F;
				Soll_IBF.ZAR_Pos	= 350.0F;


				if (Ist_Inter.ag_pos <= Soll_IBF.AG_Pos || Ist_Inter.ag_pos == Soll_IBF.AG_Pos)
				{
					Soll_IBF.InitAchse = 'x';
					Soll_IBF.Zeit.t_Halte = Ist_IBF.AG_Regelung.Haltezeit;
				}
			}

			Soll_IBF.Zeit.t_Halte--;
			break;

		case 'x':
			/* Geschwindigkeiten  */
			Soll_IBF.RS_V		= 0.0F;
			Soll_IBF.ASO_V		= 0.0F;
			Soll_IBF.Soll_ASU_V = 0.0F;
			Soll_IBF.AG_V		= 100.0F;
			Soll_IBF.ZAL_V		= 0.0F;
			Soll_IBF.ZAR_V		= 0.0F;

			/* Kräfte */
			Kraftsteuerung(Ist_IBF, &Soll_IBF);  //Funktionsaufruf

			if (Ist_IBF.Zeit.t_Halte <= 0)
			{
				/* Positionen */
				Soll_IBF.AG_Pos = 700.0F + Ist_IBF.AG_Regelung.Sprunghoehe;

				if (Ist_Inter.ag_pos <= (Soll_IBF.AG_Pos - 1.0F))
				{
					Soll_IBF.InitAchse = 'y';
					Soll_IBF.Zeit.t_Halte = Ist_IBF.AG_Regelung.Haltezeit;
				}
			}
			Soll_IBF.Zeit.t_Halte--;
			break; // case x

		case 'y':
			/* Geschwindigkeiten  */
			Soll_IBF.RS_V = 0.0F;
			Soll_IBF.ASO_V = 0.0F;
			Soll_IBF.Soll_ASU_V = 0.0F;
			Soll_IBF.AG_V = 100.0F;
			Soll_IBF.ZAL_V = 0.0F;
			Soll_IBF.ZAR_V = 0.0F;

			/* Kräfte */
			Kraftsteuerung(Ist_IBF, &Soll_IBF);  //Funktionsaufruf

			if (Ist_IBF.Zeit.t_Halte <= 0)
			{
				/* Positionen */
				Soll_IBF.AG_Pos = 700.0F;

				if (Ist_Inter.ag_pos <= (Soll_IBF.AG_Pos + 1.0F))
				{
					Soll_IBF.InitAchse = ' ';
				}
			}
			Soll_IBF.Zeit.t_Halte--;
			break; // case y

		case 'a':
			/* Positionieren des Radialschlittens && Position 
			 * des Axialschlittens über Ringhöhe, 
			 * um vorzeitiges Aufsetzen zu vermeiden */

			/* Geschwindigkeiten  */
			Soll_IBF.ASO_V		= 30.0F;
			Soll_IBF.Soll_ASU_V = 0.0F;
			Soll_IBF.AG_V		= 0.0F;
			Soll_IBF.ZAL_V		= 0.0F;
			Soll_IBF.ZAR_V		= 0.0F;

			/* Kräfte */
			/* Vorgabe der gefordeten Kräfte, Spezialroutine für 
			 * Kraftreglung Radialschlitten */
			Anwalzen_Radial(Ist_IBF, &Soll_IBF);

			/* Drehzahl */
			Soll_Inter.kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
			Soll_Inter.kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

			/* Positionsvorgabe: Abhängig ob Kraft- oder Weggebunden */
			Soll_IBF.ASO_Pos = Soll_IBF.ASO_Pos_Start + 15.0F;

			/* Abfrage 'Kraft anfahren' */
			/* aus IBF-Para(Radv01): in Kraft anwalzen */
			if (Ist_IBF.Flag.rs_kraftanfahren_aktiv == 1)
			{
				/* Vorgabe: Geschwindigkeit*/
				Soll_IBF.RS_V	= 7.0F;
				Soll_IBF.RS_Pos = Ist_IBF.RS_Pos - 10.0F;

				if (((Ist_IBF.FR) == (Soll_IBF.RS_Kraft_Anfahren)) || (Ist_IBF.Flag.rs_kraft_anfahren_erreicht == 1))
				{
					Soll_IBF.RS_Pos = Ist_IBF.RS_Pos;

					/* Wenn Kraft zum ersten Mal erreicht wurde, 
					 * wird Schalter gesetzt */
					if (Ist_IBF.Flag.rs_kraft_anfahren_erreicht == 0)
					{
						Soll_IBF.Flag.rs_kraft_anfahren_erreicht = 1;
					}

					/* Wenn Kraft erreicht und Axialschlitten hochgefahren 
					 * ist, wird die Haltezeit t_Halte runtergezählt bevor 
					 * der Prozess weiterläuft */
					if (Ist_IBF.ASO_Pos >= Ist_IBF.Vorring.Start_Ringhoehe)
					{
						Soll_IBF.Zeit.t_Halte--;
					}

					if (Ist_IBF.Zeit.t_Halte <= 0)
					{
						Soll_IBF.RS_Pos = Ist_IBF.RS_Pos;
						Soll_IBF.Rohling_s_angefahren = Ist_IBF.RS_Pos;

						/* Zähler für naechste CASE-Anweisung */
						Soll_IBF.Zeit.t_Halte = 30.0F;

						/* nachdem DW auf Kraft angefahren ist, muss für weiteren Verlauf
						 * Schalter 'Anfahren' ausgestellt werden */
						Ist_IBF.Flag.rs_kraftanfahren_aktiv = 0;
						Soll_IBF.InitAchse = 'b';
					}
				}
				break; // case a
			}
			else
			{
				/* Kraftregler aktiv, aber nicht Anwalzen in Kraft vorgewählt. 
				 * Es kann vorkommen, dass vorgegebene Wanddicke nicht erreicht 
				 * werden kann. 
				 * Deshalb wird if-Anweisung benötigt, um nächstes Case zu erreichen !!! */

				if (Ist_IBF.Flag.rs_kraftregler_aktiv == 1)
				{
					/* Vorgabe: Geschwindigkeit*/
					Soll_IBF.RS_V = 7.0F;

					// Radialschlitten an Startposition? Dann Haltezeit runterzählen
					if (Ist_IBF.RS_Pos <= Soll_IBF.RS_Pos)
					{
						Soll_IBF.Zeit.t_Halte--;
					}

					if (Ist_IBF.Zeit.t_Halte <= 0)
					{
						Soll_IBF.RS_Pos = Ist_IBF.RS_Pos;
						Soll_IBF.Rohling_s_angefahren = Ist_IBF.RS_Pos;

						/* Axialschlitten hochgefahren? Dann ins nächste 'Case' */
						if (Ist_IBF.ASO_Pos >= Ist_IBF.Vorring.Start_Ringhoehe)
						{
							/* Zaehler fuer Kraftanfahren des Axialschlitten */
							Soll_IBF.Zeit.t_Halte = 30.0F;
							Soll_IBF.InitAchse = 'b';
						}
					}
				}

				if (Ist_IBF.Flag.rs_kraftregler_aktiv == 0)
				{
					/* Vorgabe: Geschwindigkeit*/
					Soll_IBF.RS_V = 7.0F;

					/* Radialschlitten an Startposition ? */
					if (Ist_IBF.RS_Pos <= (Soll_IBF.RS_Pos_Null + eps))
					{
						/* Axialschlitten hochgefahren? Dann Haltezeit t_Halte runterzählen */
						if (Ist_IBF.ASO_Pos >= Ist_IBF.Vorring.Start_Ringhoehe)
						{
							Soll_IBF.Zeit.t_Halte--;
						}

						/* Haltezeit abgelaufen ? */
						if (Ist_IBF.Zeit.t_Halte <= 0)
						{
							Soll_IBF.RS_Pos = Ist_IBF.RS_Pos;
							Soll_IBF.Rohling_s_angefahren = Ist_IBF.RS_Pos;

							/* Zaehler fuer Kraftanfahren des Axialschlittens */
							Soll_IBF.Zeit.t_Halte = 40.0F;
							Soll_IBF.InitAchse = 'b';
						}
						break;
					}
				}
			}
			break; // case a

		case 'b':
			/* Positionierung des Axialgerüstes an Startposition */

			/* Geschwindigkeiten */
			Soll_IBF.RS_V	= 0.0F;
			Soll_IBF.ASO_V	= 10.0F;
			Soll_IBF.AG_V	= 15.0F;
			Soll_IBF.ZAL_V	= 0.0F;
			Soll_IBF.ZAR_V	= 0.0F;

			/* Kräfte */
			Kraftsteuerung(Ist_IBF, &Soll_IBF);

			/* Drehzahl */
			Soll_Inter.kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
			Soll_Inter.kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

			/* Zähler - Merker */
			/* Variable in der aktuelle Dornposition definiert ist, nachdem 
			 * Dorn positioniert wurde -> wichtig für const.Vorschub case 11ff */
			Ist_IBF.Radial.Anfangsposition_DW = Ist_IBF.Wanddicke_Ist;

			/* Position */
			Soll_IBF.AG_Pos = Ist_IBF.AG_Pos_Start;

			/* Vorgabe erfüllt */
			/* Grobes Intervall */
			if (Ist_IBF.AG_Pos <= Ist_IBF.AG_Pos_Start)
			{
				/* Feineres Intervall */
				if ((Ist_IBF.AG_Pos <= (Ist_IBF.AG_Pos_Start + eps)) && !(Ist_IBF.AG_Pos <= (Ist_IBF.AG_Pos_Start - eps)))
				{
					Soll_IBF.AG_Pos = Ist_IBF.AG_Pos;

					/* Soll axial profiliert werden */
					if (Ist_IBF.Flag.Axial_Radialwalzen == 0)
					{
						/*  Wenn JA, dann muss das case 'c' durchlaufen werden.
						 *  Feinpositionieren des AGs auf Walzposition. */
						Soll_IBF.InitAchse = 'c';
					}
					else
					{
						/* Sonst weiter mit Absenken des Axialschlittens */
						Soll_IBF.InitAchse = 'd';
					}

					/* Zähler - Merker */
					/* Abtastrate = 100 ms -> Iterationsschliefe wird 10x pro Sekunde
					 * aufgerufen*/
					Soll_IBF.Zeit.t_Halte = 30;

					/* Berechne delta_tr_pos für den nächsten Schritt */
					AGR_Soll_Pos_delta_Tr(Ist_Inter, Ist_IBF, &Soll_IBF);
					Soll_IBF.AG_Pos = Ist_IBF.AG_Pos + Soll_IBF.delta_tr;
					break;
				}
			}
			break; // case b

		case 'c':
			/* Position Axialgerüst: Profilierungsposition */

			/* Geschwindigkeiten  */
			Soll_IBF.RS_V = 0.0F;
			Soll_IBF.ASO_V = 0.0F;
			Soll_IBF.AG_V = 15.0F;
			Soll_IBF.ZAL_V = 0.0F;
			Soll_IBF.ZAR_V = 0.0F;

			/* Kräfte */
			Kraftsteuerung(Ist_IBF, &Soll_IBF);

			/* Drehzahl */
			Soll_Inter.kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
			Soll_Inter.kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);


			if (Soll_IBF.Zeit.t_Halte <= 0
				&& Ist_IBF.Flag.AG_Start_erreicht == 0)
			{

				AGR_Soll_Pos_delta_Tr(Ist_Inter, Ist_IBF, &Soll_IBF);
				Soll_IBF.AG_Pos = Ist_IBF.AG_Pos + Soll_IBF.delta_tr;
				Soll_IBF.Zeit.t_Halte = 10;
			}

			if (Soll_IBF.tr_pos <= Ist_IBF.Axial.Kr_geo.Del_Kr_AGR)
			{
				Soll_IBF.AG_Pos = Ist_IBF.AG_Pos + Soll_IBF.delta_tr;
			}

			Soll_IBF.Zeit.t_Halte--;

			if (Ist_Inter.Test.Flag == 1)
			{
				Soll_IBF.delta_tr = 0;
			}

			if (Soll_IBF.delta_tr >= -1.0F && Soll_IBF.delta_tr <= 1.0F)
			{
				Soll_IBF.Flag.AG_Start_erreicht = 1;
				Soll_IBF.AG_Pos = Ist_IBF.AG_Pos;
			}

			if (Ist_IBF.AG_Pos <= Soll_IBF.AG_Pos && Ist_IBF.Flag.AG_Start_erreicht == 1)
			{
				/* Zähler - Merker */
				Soll_IBF.Zeit.t_Halte--;
				/* Ist-Position kleiner als Vorbage, 
				 * aber nicht über das Ziel hinaus*/
				if (Ist_IBF.Zeit.t_Halte <= 0
					&& (Ist_IBF.AG_Pos <= (Soll_IBF.AG_Pos + eps))
					&& !(Ist_IBF.AG_Pos <= (Soll_IBF.AG_Pos - eps)))
				{
					Soll_IBF.AG_Pos = Ist_IBF.AG_Pos;

					/*Zähler - Merker*/
					/* 200ms = 2sec abwarten */
					Soll_IBF.Zeit.t_Halte = 15;

					Soll_IBF.InitAchse = 'd';

					break;
				}
				else
					break;
			}
			break; // case c

		case 'd':
			/*Position Axialschlitten*/

			/* Geschwindigkeiten  */
			Soll_IBF.RS_V = 0.0F;
			Soll_IBF.AG_V = 15.0F;
			Soll_IBF.ZAL_V = 0.0F;
			Soll_IBF.ZAR_V = 0.0F;

			/* Kräfte */
			/* Vorgabe der geforderten Kraefte, Spezialroutine fuer 
			 * Kraftregelung Axialschlitten */
			Anwalzen_Axial(Ist_IBF, &Soll_IBF);    // Vorgabe der gefordeten Kräfte, Spezialroutine für Kraftreglung Axialschlitten
			//Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf

			/* Drehzahl */
			Soll_Inter.kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
			Soll_Inter.kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

			/*Position*/

			//-------------------------------------
			//------ Kraftanfahren ----------------

			/* In Kraft anwalzen aus: */
			/* (RAW->IBF_Para.ini in rwthexch.cpp || MRAW -> IBF_Para.cpp*/
			if (Ist_IBF.Flag.as_kraftanfahren_aktiv == 1)
			{

				/* Vorgabe: Geschwindigkeit*/
				Soll_IBF.ASO_V = -10.0F;
				Soll_IBF.ASO_Pos = Ist_IBF.ASO_Pos - 5.0F;

				// Abfragen, ob Kraft erreicht ist
				if (((Ist_IBF.FA) == (Soll_IBF.AS_Kraft_Anfahren))
					|| (Ist_IBF.Flag.as_kraft_anfahren_erreicht == 1))
				{
					Soll_IBF.ASO_Pos = Ist_IBF.ASO_Pos;
					Soll_IBF.Rohling_h_angefahren = Ist_IBF.ASO_Pos;

					/* Wenn Kraft erreicht ist soll die Zeit t ablaufen
					* bevor der Prozess weiterlaeuft */
					Soll_IBF.Zeit.t_Halte--;

					if (Ist_IBF.Flag.as_kraft_anfahren_erreicht == 0)
					{
						Soll_IBF.Flag.as_kraft_anfahren_erreicht = 1;
					}

					if (Ist_IBF.Zeit.t_Halte <= 0)
					{
						/* Zaehler für Kraftanfahren des Axialschlittens*/
						Soll_IBF.Zeit.t_Halte = 100.0F;

						Soll_IBF.InitAchse = ' ';

						/* Nachdem ASO auf Kraft angefahren ist, muss für
						 * den weiteren Verlauf Schalter 'Anfahren' aus gestellt
						 * werden */
						Ist_IBF.Flag.as_kraftanfahren_aktiv = 0;
						Soll_IBF.Profilflag = 1;
					}

				}

			}

				//--------------------------------------
				//----- Anfahren in Position -----------
				//--------------------------------------
				/* Anfahren unter Vorgabe der Position */
			else
			{

				/* Vorgabe: Geschwindigkeit*/
				Soll_IBF.ASO_V = -18.0F;

				/* Ist_IBF.ASO_Pos_Differenz = Korrektur der Starthoehe aus Carwin
				 * (in IBF_ini definiert)
				 * ASO wird sonst auf Starthoehe gesetzt und beim 'Positionieren des AG 
				 * rutscht ASO ueber Stirnseite */
				Soll_IBF.ASO_Pos = Ist_IBF.ASO_Pos_Start
					- Ist_IBF.ASO_Pos_Differenz;

				if (Ist_IBF.ASO_Pos <= (Soll_IBF.ASO_Pos + eps))
				{

					/* Wenn Position erreicht wurde,
					 * soll die Zeit t ablaufen bevor
					 * Prozess weiterläuft */
					Soll_IBF.Zeit.t_Halte--;

					if (Ist_IBF.Zeit.t_Halte <= 0)
					{

						Soll_IBF.AG_Regelung.psi = Ist_IBF.Axial.AGR_Pr[0]
							/ Ist_IBF.RS_Pos;

						Soll_IBF.ASO_Pos = Ist_IBF.ASO_Pos;

						Soll_IBF.Rohling_h_angefahren = Ist_IBF.ASO_Pos;

						/* Zähler für Kraftanfahrt des Axialschlittens */
						Soll_IBF.Zeit.t_Halte = 15.0F;

						Soll_IBF.InitAchse = ' ';

						Soll_IBF.Profilflag = 1;

						Soll_IBF.Axial.Profilflag = 9;

						Soll_IBF.DW_Regelung.Startmesswert = Ist_IBF.DW_Regelung.Messwert_A;

					}
				}
			}

			break; // case d

		case 'z':

			/* 2 Umdrehungen abwarten für gleichmäßiges Profil über Umfang  */
			Soll_IBF.Zeit.t_Halte--;
			if (Ist_IBF.Zeit.t_Halte <= 0)
			{
				IBF_Abschaltung(&Soll_Inter, Ist_IBF);
			};

			break;  // case 'z'

		case 's':
			// Anfahren der Startpositionen und anwalzen
			schuesselWalzen.Main(Ist_Inter,Ist_IBF,Soll_Inter,Soll_IBF);
			break; // case 's'

		default:
#ifdef MRAW
			_settextposition(9,1);
			printf(" InitAchse: %d - Warum default ?!? ", Ist_IBF.InitAchse);
#endif
			break;  // default
		}
		break; // case 0

	case 1:     // Aufruf der jeweilgen IBF-Module IBF-flex.Radial, IBF-Flex.Axial, Formenspektrum, Schuesselwalzen

		
		switch (Ist_IBF.Flag.Axial_Radialwalzen)
		{
		case 0: /* Axialwalzen */
			
			flexibel_Axial( Ist_Inter, Ist_IBF,	Soll_Inter,	Soll_IBF );
			break;

		case 1: /* Radialwalzen */
		
			flexibel_Radial(Ist_Inter, Ist_IBF,	Soll_Inter,	Soll_IBF );
			break;
		
		case 2: /* Formspektrum */

			formenspektrum( Ist_Inter, Ist_IBF,	Soll_Inter,	Soll_IBF );
			break;

		case 3: /* Schüssel walzen */
			{
			int err=0;
			err = schuesselWalzen.Main(Ist_Inter, Ist_IBF, Soll_Inter, Soll_IBF);
			if ((err==0x0100/*ERR_FERTIG_HM*/)+(err==0x0200/*ERR_FERTIG_KW*/)!=0)
			{
				Soll_IBF.Profilflag = 3;
				break;
			};
			break;
			};
		default: /* es wurde kein passendes Flag gesetzt  */
		
			Soll_IBF.Profilflag = 3;
			break;
		}
		break; // case 1

	case 13: /* Ende des Walzprozesses -> Auffahren der Anlage */
		IBF_Abschaltung(&Soll_Inter, Ist_IBF);
		break;

	case 9:
		/* Axialschlitten mit const. vorgegebener Geschwindigkeit zustellen
		 * Axialgerüst mit Funktion AGR_Soll_Pos() positionieren
		 * Radialschlitten in Kraftsteuerung an Ring andrücken, 
		 * dafür muss allerdings Kraftsteuerung vorgewählt sein ->  */

		/* Geschwindigkeiten  */
		Soll_IBF.RS_V		= 2.0F;
		Soll_IBF.ASO_V		= 4.0F; //Ist_IBF.Axial.Vorschub/Ist_IBF.Zeit.Ringumdrehung; // [mm/U] / [s/U]
		Soll_IBF.Soll_ASU_V = 0.0F;
		Soll_IBF.AG_V		= 10.0F;
		Soll_IBF.ZAL_V		= 0.0F;
		Soll_IBF.ZAR_V		= 0.0F;

		/* Kräfte */
		Kraftsteuerung(Ist_IBF, &Soll_IBF); //Funktionsaufruf

		/* Drehzahl */
		Soll_Inter.kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
		Soll_Inter.kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

		/* Positionsvorgabe: Abhängig ob Kraft- oder Weggebunden */
		Soll_IBF.AG_Pos = AGR_Soll_Pos(Ist_Inter, Ist_IBF, &Soll_IBF);
		Soll_IBF.ASO_Pos = Ist_IBF.Rohling_h_angefahren - Ist_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num];

		if (Ist_IBF.ASO_Pos <= Soll_IBF.ASO_Pos)
		{
			Soll_IBF.ASO_Pos = Ist_IBF.ASO_Pos;
			Soll_IBF.Zeit.t_Halte = 20; //Ist_Inter.Werkzeug.Ringumdrehung * Soll_IBF.Axial.Umdrehungen;   //Zeit berechnen für x-Ringumdrehungen
			Soll_IBF.Profilflag = 11;
		}
		break;

	case 11:
		/* Rundungsphase */

		/* Geschwindigkeiten  */
		Soll_IBF.RS_V		= 2.0F;
		Soll_IBF.ASO_V		= 1.0F; //Axialschlitten soll in Rundungsphase nicht zustellen
		Soll_IBF.Soll_ASU_V = 0.0F;
		Soll_IBF.AG_V		= 10.0F;
		Soll_IBF.ZAL_V		= 0.0F;
		Soll_IBF.ZAR_V		= 0.0F;

		/* Kräfte */
		Kraftsteuerung(Ist_IBF, &Soll_IBF); //Funktionsaufruf

		/* Drehzahl */
		Soll_Inter.kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
		Soll_Inter.kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

		/* Positionsvorgabe: Abhängig ob Kraft- oder Weggebunden */
		Soll_IBF.AG_Pos = AGR_Soll_Pos(Ist_Inter, Ist_IBF, &Soll_IBF);

		if (Ist_IBF.Zeit.t_Halte <= 0)
		{
			Soll_IBF.Profilflag = 12;
		}

		/* Runterzaehlen der Zeit fuer Glaettungsrunde*/
		Soll_IBF.Zeit.t_Halte--;
		break;

	case 12:
		/* Hochfahren des Axialschlittens und Abfragen,
		 * ob weitere Profilstufe gewalzt werden soll */

		/* Geschwindigkeiten  */
		Soll_IBF.RS_V		= 2.0F;
		Soll_IBF.ASO_V		= 30.0F;
		Soll_IBF.Soll_ASU_V = 0.0F;
		Soll_IBF.AG_V		= 10.0F;
		Soll_IBF.ZAL_V		= 0.0F;
		Soll_IBF.ZAR_V		= 0.0F;

		/* Kräfte */
		Kraftsteuerung(Ist_IBF, &Soll_IBF); //Funktionsaufruf

		/* Drehzahl */
		Soll_Inter.kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
		Soll_Inter.kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

		/* Position */
		Soll_IBF.ASO_Pos = Ist_IBF.Rohling_h_angefahren + 30.0F;

		/* Abfrage ob weiteres Profil gewalzt werden soll / Schalter setzen*/
		if (Ist_IBF.ASO_Pos >= Soll_IBF.ASO_Pos - 1.0F)
		{
			Soll_IBF.Axial.Pr_Num = Soll_IBF.Axial.Pr_Num + 1;

			if (Soll_IBF.Axial.Pr_Num == Ist_IBF.Axial.Profilanzahl)
			{
				Soll_IBF.Profilflag = 13; // Prozessende
			}

			if (Soll_IBF.Axial.Pr_Num < Ist_IBF.Axial.Profilanzahl)
			{
				Soll_IBF.AG_Pos_Start = Ist_Inter.da
					- Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num]
					- Ist_IBF.Axial.Kr_geo.Kr_Br
					- Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
					+ Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw;

				/* Axialgeruest neu positionieren */
				Soll_IBF.Profilflag = 0;
				Soll_IBF.InitAchse = 'b';
			}
		}
		break;

	case 2:
		/* x Umdrehungen abwarten fuer gleichmaessiges Profil ueber Umfang */

		/* Geschwindigkeiten  */
		Soll_IBF.RS_V = Soll_IBF.Radial.Vorschubgeschw_Dw;   /* Vorschubgeschw_DW erechnet in case 15 */
		Soll_IBF.ASO_V = 5.0F;
		Soll_IBF.AG_V = 10.0F;
		Soll_IBF.ZAL_V = 0.0F;
		Soll_IBF.ZAR_V = 0.0F;

		/* Kräfte */
		Kraftsteuerung(Ist_IBF, &Soll_IBF);

		Soll_IBF.Zeit.t_Halte--;
		Soll_IBF.Radial.t_warte_flag = 0; //zurücksetzen der Bedingung (Diskonti...)

		
		if (Ist_IBF.Zeit.t_Halte <= 0)
		{
			Soll_IBF.ExitAchse = 'a';
			Soll_IBF.Profilflag = 3;
			/* Hier Befehl reinschreiben,
			 * wenn weitere Schritte 
			 * abgearbeitet werden sollen*/
			break;   //hier Befehle reinschreiben, wenn ein weiterer Schritt abgearbeitet werden soll.....
		}
		break;

	case 3:
		/*  Abschaltmass erreicht Banning */

		/* Funktionsaufruf */
		IBF_Abschaltung(&Soll_Inter, Ist_IBF);
		break;

	case 345:
		/* Abschaltung MRAW -> Memoryflag= Ist_IBF.Profilflag;
		 * RS und AS auffahren; danach manuell Entladeposition anfahren (Koppers 'e')     */

		switch (Ist_IBF.ExitAchse)
		{
#ifdef MRAW
		Steuerbyte_Lese.freigabe = 191;	// war 95
		#endif

		case 'a':
			Soll_IBF.RS_Pos = Ist_IBF.RS_Pos_Start + 10.0F; //michl
			Soll_IBF.RS_V = 5.0F;

			if (Ist_IBF.RS_Pos >= Soll_IBF.RS_Pos)
			{
				Soll_IBF.ExitAchse = 'b';
			}
			break;

		case 'b':

			Soll_IBF.AG_Pos = Ist_IBF.AG_Pos_Null + 50;
			Soll_IBF.ASO_Pos = Ist_IBF.ASO_Pos_Null + 15; //michl

			Soll_IBF.ASO_V = 15.0F;

			Soll_IBF.AG_V = 8.0F;
			Soll_IBF.ZAR_V = 0.0F;
			Soll_IBF.ZAL_V = 0.0F;

			if (Ist_IBF.AG_Pos >= Soll_IBF.AG_Pos)
			{
				Soll_IBF.ExitAchse = ' ';
				Soll_IBF.Profilflag++;
			}

			if ((Ist_IBF.RS_Pos >= Soll_IBF.RS_Pos)
				&& (Ist_IBF.ASO_Pos >= Soll_IBF.ASO_Pos)
#ifdef MRAW
              && (Ist_IBF.ASU_Pos >= Soll_IBF.Soll_ASU_Pos)
#endif
)
			{
				Soll_IBF.ExitAchse = ' ';
				Soll_IBF.Profilflag++;
				break;
			}
			/* Damit die Variablenwerte, die waehrend einer
			 * Walzung nicht im Speicher verbleiben, muessen 
			 * diese zurueckgesetzt werden */

			Ist_IBF.FR_f = 0;
			Ist_IBF.FA_f = 0;

			break;

		default:
			break;
		} // Klammer zu: switch(ExitAchse)                  
		break;
	}; // Klammer zu: switch (IBF_Allgemein.IBF_Allgemein.Profilflag) 


//########## Ende Automatiksteuerung ##########


/* ------------------------------------------------------------------------ */
/*                                                                          */
/*  Übergabe der Sollwerte aus der IBF-Struktur an die 'Ist_Inter' Struktur */
/*                                                                          */
/* ------------------------------------------------------------------------ */

	/* Kraft [N]*/
	Soll_Inter.rs_kraft		= Soll_IBF.RS_Kraft;
	Soll_Inter.aso_kraft	= Soll_IBF.AS_Kraft;
	Soll_Inter.ag_kraft		= Soll_IBF.AG_Kraft;
	Soll_Inter.zal_kraft	= Soll_IBF.ZAL_Kraft;
	Soll_Inter.zar_kraft	= Soll_IBF.ZAR_Kraft;

	/* Flags für Kraftsteuerung */
	Soll_Inter.rs_kraftregler_aktiv		= Ist_IBF.Flag.rs_kraftregler_aktiv;   /* [0-1] */
	Soll_Inter.aso_kraftregler_aktiv	= Ist_IBF.Flag.as_kraftregler_aktiv;
	Soll_Inter.ag_kraftregler_aktiv		= Ist_IBF.Flag.ag_kraftregler_aktiv;
	Soll_Inter.zal_kraftregler_aktiv	= Ist_IBF.Flag.zal_kraftregler_aktiv;
	Soll_Inter.zar_kraftregler_aktiv	= Ist_IBF.Flag.zar_kraftregler_aktiv;

	Soll_Inter.rs_mode	= Soll_IBF.Flag.rs_mode;
	Soll_Inter.aso_mode = Soll_IBF.Flag.aso_mode;

	// Kontrolle der Achsen | Neu: dez 2014
	Soll_Inter.RS_act = Soll_IBF.RS_act;
	Soll_Inter.AS_act = Soll_IBF.AS_act;
	Soll_Inter.ag_act = Soll_IBF.Flag.ag_act;

	// Flags fuer Zentrierrollen
	Soll_Inter.zen_mode = Soll_IBF.ZER_Param.mode;  // neu: dez 2014 d.Otto
	Soll_Inter.zen_act  = Soll_IBF.ZER_Param.act;   // neu: dez 2014 d.Otto

	/* Geschwindigkeit [mm/s] */
	Soll_Inter.rs_v		= Soll_IBF.RS_V;         /* Übergebe Gechwindigkeit an Tabelle */
	Soll_Inter.aso_v	= Soll_IBF.ASO_V;
	Soll_Inter.ag_v		= Soll_IBF.AG_V;
	//Soll_Inter.zal_v	= Soll_IBF.ZAL_V;
	//Soll_Inter.zar_v	= Soll_IBF.ZAR_V;

	/* Positionen [mm]*/
	if (Soll_IBF.RS_Pos < Soll_IBF.min_RS_Pos)
	{
		/* Wert in rwth-exch.cpp initialiert. Routine ini-Datei einlesen */
		Soll_Inter.rs_pos = Ist_Inter.rs_pos;
	}
	else
	{
		Soll_Inter.rs_pos = Soll_IBF.RS_Pos;
	}

	/* min_ASO_pos Wert in rwth-exch.cpp initialisiert Routine ini-Datei einlesen */
	if (Soll_IBF.ASO_Pos < Soll_IBF.min_ASO_Pos)
	{
		Soll_Inter.aso_pos = Ist_Inter.aso_pos;
	}
	else
	{
		Soll_Inter.aso_pos = Soll_IBF.ASO_Pos;
	}
	
	/* Axialgeruest positionieren */

	Soll_Inter.ag_pos = Soll_IBF.AG_Pos;

	
/*------------------------------------------------------*/
/* DA Otto: Dezember 2014			                    */
/* Projekt: Schuesselwalzen			                    */
/*------------------------------------------------------*/

//#ifdef DRR
// Transformation und Uebergabe der SOLL-Werte der Druckrollenregelung (DRRE-DRRA)
	Soll_Inter.DRR_Param = DRR_trans_Soll(Ist_IBF , Soll_IBF);
//#endif

// Sollwertvorgaben für die Zentrierarme konvertieren und an Soll-Inter übergeben
	ZER_trans_Soll(/*out*/Soll_Inter, Soll_IBF, Ist_IBF);

/*------------------------------------------------------------------------------------*/
/*------------- Anfang Kollisionscheck Modellringwalzwerk ----------------------------*/
/*------------------------------------------------------------------------------------*/

#ifdef MRAW
  RS_HW = 1;
  RS_AG = 1;
  AG_RS = 1;
  AS_AS = 1;

  if ((RS_HW != 0) && (RS_AG != 0)) {
#ifdef MRAW
    _settextposition(7,1);
    printf("                                     ");
#endif
  }
  else{
    if (RS_HW == 0) {
#ifdef MRAW
      _settextposition(7,1);
      printf("    KOLLISIONSGEFAHR RS - HW   %i      ", RS_HW);
#endif
    }
    else {
#ifdef MRAW
      _settextposition(7,1);
      printf("    KOLLISIONSGEFAHR RS - AG   %i      ", RS_AG);
#endif
    }
  }

  if (AG_RS != 0) {
    Soll_Inter.ag_pos = Soll_IBF.AG_Pos + offset_agr;
#ifdef MRAW
    _settextposition(7,1);
    printf("                                     ");
#endif
  }
  else {
#ifdef MRAW
    _settextposition(7,1);
    printf("    KOLLISIONSGEFAHR AG - RS   %i      ", AG_RS);
#endif
  }

  if (AS_AS != 0) {
    Soll_Inter.aso_pos = Soll_IBF.ASO_Pos + offset_aso;
#ifdef MRAW
    Soll_Inter.asu_pos = Soll_IBF.Soll_ASU_Pos + offset_asu;  //michl rausgenommen
    _settextposition(7,1);
    printf("                                     ");
#endif
  }
  else {
#ifdef MRAW
    _settextposition(7,1);
    printf("    KOLLISIONSGEFAHR oberer AS - AS   %i      ", AS_AS);
#endif
  }
#endif


	return TRUE;
}

int RPW::Modus_AG(struct Def_Soll_Inter& Soll_Inter, struct Def_IBF_Allgemein_IST& Ist_IBF, int Auswahl)
{
	// Funktion mit der die richtigen Bits des Axialgerüstmodus eingestellt werden 

	// Los geht´s

	//Setzen des SMS-Flag Sollwert/Abschaltung Axialgerüst
	if (Ist_IBF.Flag.IBF_Abschaltung == 1 && Ist_IBF.Flag.Axial_Radialwalzen == 0)
	{
		Soll_Inter.ag_act = 0x03; //3=0x03= 0000 0011 (Bit0=1 IBF übernimmt Regelung AG, Bit1=1 IBF übernimmt Abschaltung
	}
	else if (Ist_IBF.Flag.IBF_Abschaltung == 1 && Ist_IBF.Flag.Axial_Radialwalzen == 1)
	{
		Soll_Inter.ag_act = 0x02; // 0000 0010 (Bit0=0 SMS übernimmt Regelung AG, Bit1=1 IBF übernimmt Abschaltung
	}
	else
		Soll_Inter.ag_act = 0x00; // 0000 0000 (Bit0=0 SMS übernimmt Regelung AG, Bit1=0 SMS übernimmt Abschaltung

	//Setzen der Betriebsart des Axialgerüstes
	if (!Ist_IBF.Flag.ag_kraftregler_aktiv)  //Wenn FLAG = 0 ist -> Vorschubregelung gewählt (IBF_Para.ini, Defaultwert = 0)
		switch (Auswahl)
		{
		case 0: //Axialprofilieren : Vorschubregelung-IBF (Bit0=0), Abschaltung nicht erreicht (Bit1=0), beim Schließen/Anfahren wird die IBF-Position verwendet (Bit2=1) (allerdings ist bereits geschlossen, wenn Funktion aufgerufen wird)
			Soll_Inter.ag_mode = 0x04; // 0000 0100 
			break;
		case 1: //Radialprofilieren: Vorschubregelung-IBF (Bit0=0), Abschaltmaß nicht erreicht (Bit1=0), beim Schließen/Anfahren wird die SMS-Position verwendet (Bit2=0) (allerdings ist bereits geschlossen, wenn Funktion aufgerufen wird)
			Soll_Inter.ag_mode = 0x02; // 0000 0000
			break;

		default:
			break;
		}
	else
		switch (Auswahl)
		{

		case 0: //Axialprofilieren : Kraftregelung-IBF (Bit0=1), Abschaltung nicht erreicht (Bit1=0), beim Schließen/Anfahren wird die IBF-Position verwendet (Bit2=1)
			Soll_Inter.ag_mode = 0x05; // 0000 0101
			break;
		case 1: //Radialprofilieren: Kraftregelung-IBF (Bit0=1), Abschaltung nicht erreicht (Bit1=0), beim Schließen/Anfahren wird die SMS-Position verwendet (Bit2=0)
			Soll_Inter.ag_mode = 0x01; // 0000 0001 
			break;
		}

	return TRUE;

}

/*--------------------------------------------------------------------------------------*/
/*                                                                                      */
/*                  Funktionen für Programmmodul Axialprofilieren                       */
/*                                                                                      */
/*--------------------------------------------------------------------------------------*/


int RPW::Kr_Geo_berechnen(struct Def_IBF_Allgemein_IST& Ist_IBF)
{
	// Funktion zur Berechnung benötigter Kragenwalzengeometrien, Vorgegeben wird Vordere Durchmesser Kragenwalze, Kragenbreite

	// Los geht´s

	//Abstand Vorderkante Kragenwalze-theoretische Spitze
	Ist_IBF.Axial.Kr_geo.Del_Kr_AGR = Ist_IBF.Axial.Kr_geo.Kr_d_nenn_vorne / (Ist_IBF.Axial.Kr_geo.
																			  sin_kw_winkel_halbe * 2);

	//Kragendurchmesser an Kragenmittelpunkt
	Ist_IBF.Axial.Kr_geo.Kr_d_nenn_mitte = 2 * Ist_IBF.Axial.Kr_geo.sin_kw_winkel_halbe
		* (Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
		   + Ist_IBF.Axial.Kr_geo.Kr_Br / 2);
	return TRUE;
}


int RPW::Kr_Geo_pruefen(struct Def_IBF_Allgemein_IST& Ist_IBF)
{
	// Überprüfen der vorgegeben Kragengeometrie, Abstand zwischen reellen KW-Spitze und Ansatzpunkt des Kragens muss am RAW gemessen werden können

	// Los geht´s
	Ist_IBF.Axial.Kr_geo.l_mantel_ukw_o_fehlende_spitze = (Ist_IBF.Axial.Kr_geo.Kr_d_nenn_vorne / 2)
															/ Ist_IBF.Axial.Kr_geo.sin_kw_winkel_halbe
															- Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw;
	return TRUE;
}
