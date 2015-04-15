#include "rpw.hpp"
#include "time.h"



//---------------------------------------------------------------------------
// Methode RPW::RPW
//---------------------------------------------------------------------------
RPW::RPW(void)
{

    //hw_ir                = 0.0F; // Getriebeuntersetzung Hauptwalzenmotor
    //kw_ia                = 0.0F; // Getriebeuntersetzung Kegelwalzenmotor
    sin_kw_winkel_halbe  = 0.0F; // Sinus halber Kegelwalzenwinkel
   
    offset_rs            = 0.0F; 
    offset_agr           = 0.0F;
    offset_aso           = 0.0F;
    offset_asu           = 0.0F;
    offset_tr            = 0.0F;	

         
}

//---------------------------------------------------------------------------
// Methode RWP::Main_RAW
//---------------------------------------------------------------------------
int RPW::Main_RAW(int    iter,
                  struct Def_Ein_Puff            Ein_Puff,
                  struct Def_Lokal_Puff          Lokal_Puff,
                  struct Def_Aus_Puff            Aus_Puff,
                  struct Def_Ein_Onli            Ein_Onli,
                  struct Def_Aus_Onli            Aus_Onli,
                  struct Def_Ist_Inter           *Ist_Inter,
                  struct Def_Soll_Inter          *Soll_Inter,
                  struct Def_IBF_Allgemein_SOLL  *Soll_IBF,
                  struct Def_IBF_Allgemein_IST   *Ist_IBF   )
{
   // Defintion der lokalen Variabeln
   // struct Def_IBF_Allgemein *IBF_Allgemein;
   // Los gehts
   Ist_Inter->Test.Flag    = Ist_IBF->Test.Flag; 
   Ist_Inter->Test.Ring_AD = Ist_IBF->Test.Ring_AD;


   // Istwerte aufbereiten
   Istwerte_RAW(  Ein_Onli,
                  Ein_Puff,
                  Lokal_Puff,
                  Aus_Puff,
                  &*Ist_Inter);
  

   
   // Spezielle Variablen an IST_IBF-Struktur �bergeben

   IstIBF_IstInter(*Ist_Inter,
                   &*Ist_IBF);

   IstIBF_SollIBF(*Soll_IBF,
                  &*Ist_IBF);


   Kr_Geo_berechnen(&*Ist_IBF);
   Kr_Geo_pruefen(&*Ist_IBF);


   Soll_Inter->rs_v  = Aus_Onli.ds_dh_sp_hp.s_punkt;
   Soll_Inter->aso_v = Aus_Onli.ds_dh_sp_hp.h_punkt;
   /* Flag setzen 5 prozent erreicht f�r Test Zentrierung */
   // Ein_Onli.rz_f_radial_5proz_erkannt = 1;


   // Hauptprogrammteil des IBF-Tasks
   Main(*Ist_Inter,
        *Ist_IBF,
        &*Soll_Inter,
        &*Soll_IBF);

   return TRUE;
}

//---------------------------------------------------------------------------
// Methode RWP::Istwerte_RAW
//---------------------------------------------------------------------------
int RPW::Istwerte_RAW(  struct Def_Ein_Onli    Ein_Onli,
                        struct Def_Ein_Puff    Ein_Puff,
                        struct Def_Lokal_Puff  Lokal_Puff,
                        struct Def_Aus_Puff    Aus_Puff,
                        struct Def_Ist_Inter   *Ist_Inter
                        )
{

  /* Ist-Achsenpositionen  */ 

    Ist_Inter->rs_pos    =   Ein_Puff.form_mess_of.dis_hw_dw;           /* Aktuelle Radialschlittenposition       [mm]*/

    Ist_Inter->ag_pos    =   Ein_Puff.form_mess_of.da
                            - Ein_Puff.pos_laser_u_of;                  /* Axialger�stposition (hergeleitet)      [mm]*/   
                          // !!!! PR�FEN, WELCHE AG_Pos-Definition besser f�r Axialprofilieren ist !!!!!

    Ist_Inter->ag_pos_real = Ein_Onli.Ibf_actual.Ist_AG;                /* Aktuelle Axialger�stposition           [mm]*/

    Ist_Inter->aso_pos   =   Ein_Puff.form_mess_of.dis_aw;              /* Aktuelle Axialschlittenposition        [mm]*/          
    Ist_Inter->asu_pos   =   0.0F;
    Ist_Inter->tr_pos    =   Ein_Puff.pos_laser_u_of
                           + Ein_Puff.awu_geometrie.l_fehlende_spitze;  /*Aktuelle Tastrollenposition             [mm]*/

    Ist_Inter->zar_pos   = Ein_Onli.Ibf_actual.Ist_ZEN_A;                /* Aktuelle Zentrierarmposition 'Auslauf' [mm]*/
    Ist_Inter->zal_pos   = Ein_Onli.Ibf_actual.Ist_ZEN_E;                /* Aktuelle Zentrierarmposition 'Einlauf' [mm]*/

    /*--- Geometrie ---*/

    /* Maschinengeometrie */
    Ist_Inter->Werkzeug.Durchmesser_HW              =   Ein_Puff.hw_geometrie.d_nenn;
    Ist_Inter->Werkzeug.Durchmesser_DW              =   Ein_Puff.dw_geometrie.d_nenn; 
    Ist_Inter->Werkzeug.l_fehlende_spitze           =   Ein_Puff.awu_geometrie.l_fehlende_spitze;

    Ist_Inter->hw_ir     =   Ein_Puff.hw1_motor.getriebe_untersetzung;              /* Getriebeuntersetzung Hauptwalzenmotor  i= n_Antrieb/n_Abtrieb (i>1 ist Untersetzung) */
    Ist_Inter->kw_ia     =   Ein_Puff.awu_motor.getriebe_untersetzung;              /* Getriebeuntersetzung Kegelwalzenmotor */
    sin_kw_winkel_halbe  =   (float) sin(Ein_Puff.awu_geometrie.winkel_bo * 0.5F);  /* Sinus halber Kegelwalzenwinkel */
  

    /* Ringgeometrie */
    if(Ist_Inter->Test.Flag == 0) /* Testmodus erm�glicht die Simulation des IBF-Walzzyklus ohne Ring, besonders wenn die Tastrollesimulation in CARWIn nicht erw�ncht wird */
    {
    Ist_Inter->da              = Aus_Puff.form_ring.da;      		/* Aeusserer Durchmesser        [mm]    */
	Ist_Inter->da_of           = Ein_Puff.form_mess_of.da;
  	
    Ist_Inter->di              = Aus_Puff.form_ring.di;   			/* Innerer   Durchmesser        [mm]    */
  	Ist_Inter->di_of           = Ein_Puff.form_mess_of.di;
  	
    Ist_Inter->dm              = Aus_Puff.form_ring.dm;   			/* Mittlerer Durchmesser        [mm]    */
  	Ist_Inter->dm_of           = Ein_Puff.form_mess_of.dm;    
    }
    else 
        {
         
         Ist_Inter->da              = Ist_Inter->Test.Ring_AD;      /* Aeusserer Durchmesser        [mm]    */
	     Ist_Inter->da_of           = Ist_Inter->Test.Ring_AD;
  	
                                                                    /* Innerer   Durchmesser        [mm]    */
         Ist_Inter->di              = Ist_Inter->Test.Ring_AD - 2*Aus_Puff.s1r;   			
  	     Ist_Inter->di_of           = Ist_Inter->Test.Ring_AD - 2*Aus_Puff.s1r;
  	
                                                                    /* Mittlerer Durchmesser        [mm]    */
         Ist_Inter->dm              = (Ist_Inter->da + Ist_Inter->di)/2;   			
  	     Ist_Inter->dm_of           = Ein_Puff.form_mess_of.dm;    
        }
  	
    Ist_Inter->fertig_ho_soll  = Aus_Puff.ist_walzform.hm;
  	Ist_Inter->fertig_wd_soll  = Aus_Puff.ist_walzform.sm;
  	
  	Ist_Inter->h0r             = Aus_Puff.h0r;     					/* Ringhoehe radial einlaufend  [mm]    */
  	Ist_Inter->h1r             = Aus_Puff.h1r;     					/* Ringhoehe radial auslaufend  [mm]    */
  	Ist_Inter->h0a             = Aus_Puff.h0a;     					/* Ringhoehe axial  einlaufend  [mm]    */  		
    Ist_Inter->h1a             = Aus_Puff.h1a;     					/* Ringhoehe axial  auslaufend  [mm]    */
  	Ist_Inter->h1a_of          = Ein_Puff.form_mess_of.dis_aw;
  	
    Ist_Inter->s0a             = Aus_Puff.s0a;     					/* Wanddicke axial  einlaufend  [mm]    */
  	Ist_Inter->s0r             = Aus_Puff.s0r;     					/* Wanddicke radial einlaufend  [mm]    */
  	Ist_Inter->s1a             = Aus_Puff.s1a;     					/* Wanddicke axial  auslaufend  [mm]    */
  	Ist_Inter->s1r             = Aus_Puff.s1r;     					/* Wanddicke radial auslaufend  [mm]    */
  	Ist_Inter->s1r_of          = Ein_Puff.form_mess_of.dis_hw_dw;
	Ist_Inter->sfh             = Aus_Puff.s_ekv;					/* Wanddicke bei Fertighoehe    [mm]    */
  	
    Ist_Inter->skw             = 0.0F;                    
  	Ist_Inter->skw_of          = 0.0F;                      		
  	Ist_Inter->wa_dvol         = Aus_Puff.dvol_ring_proz;      /* Berechnete Volumendifferenz [%]       */
    
    Ist_Inter->Vorform.sm      = Ein_Puff.vorform.sm;          /* Wandst�rke Vorform aus Carwin            [mm] */
    Ist_Inter->Vorform.da      = Ein_Puff.vorform.da;          /* Durchmesser Vorform  aus Carwin          [mm] */
    Ist_Inter->Vorform.hm      = Ein_Puff.vorform.hm;          /* Rohlingsh�he Vorform aus Carwin          [mm] */


    /* Ist-Prozessdynamik */
    //Ist_Inter->hw_n      =   (Ein_Puff.n_hw_motor_ist  / MIN_FAK) / hw_ir ;    /* Istdrehzahl Hauptwalze          gew�nscht war [1/s]  mit dem Faktor Min_Fak= 1/60 erh�lt man jedoch [1/min]*/
    //Ist_Inter->kwo_n     =   (Ein_Puff.n_awo_motor_ist / MIN_FAK) / kw_ia ;    /* Istdrehzahl Axialwalzen oben    gew�nscht war [1/s]  mit dem Faktor Min_Fak= 1/60 erh�lt man jedoch [1/min] */        
    //Ist_Inter->kwu_n     =   (Ein_Puff.n_awu_motor_ist / MIN_FAK) / kw_ia;     /* Istdrehzahl Axialwalzen unten Debye->[1/s]_ohne_  /MIN_FAK || MRAW->[1/min]*/

    if(Ist_Inter->Test.Flag == 0) /* Testmodus erm�glicht die Simulation des IBF-Walzzyklus ohne Ring und ohne eingeschaltete Antriebe */
    {
       Ist_Inter->hw_n      =   Ein_Puff.n_hw_motor_ist  / Ist_Inter->hw_ir ;      /* Istdrehzahl Hauptwalze              [1/s]  */
       Ist_Inter->kwo_n     =   Ein_Puff.n_awo_motor_ist / Ist_Inter->kw_ia ;      /* Istdrehzahl Axialwalzen oben        [1/s] */        
       Ist_Inter->kwu_n     =   Ein_Puff.n_awu_motor_ist / Ist_Inter->kw_ia ;      /* Istdrehzahl Axialwalzen unten Debye->[1/s]_ohne_  /MIN_FAK || MRAW->[1/min]*/
    }
    else if(Ist_Inter->Test.Flag == 1)
        {
        Ist_Inter->hw_n      =   20.0F ;      /* Istdrehzahl Hauptwalze              [1/s]  */
        Ist_Inter->kwo_n     =   16.0F ;      /* Istdrehzahl Axialwalzen oben        [1/s] */        
        Ist_Inter->kwu_n     =   16.0F ;      /* Istdrehzahl Axialwalzen unten Debye->[1/s]_ohne_  /MIN_FAK || MRAW->[1/min]*/
        }

    Ist_Inter->Werkzeug.Drehzahl_HW             = Ist_Inter->hw_n;                                      /* Drehzahl (grad) der Hauptwalze [1/s]*/
    Ist_Inter->Werkzeug.Winkelgeschw_omega_HW   = Ist_Inter->hw_n * (2 * PI);                           /* Winkelgeschwindigkeit (rad) der HW  [1/sec] //(omega=2*PI*n)*/
    Ist_Inter->Werkzeug.Winkel_grad_tU_HW       = Ist_Inter->Werkzeug.Winkelgeschw_omega_HW * 180/PI;   /* Aktueller Winkel  [�] */
    Ist_Inter->Werkzeug.tU_HW                   = 1 / Ist_Inter->hw_n;                                  /* Zeit(Periode) f�r 1 Umdrehung der HW  [s]*/
    Ist_Inter->Werkzeug.U_v_HW                  = Ist_Inter->Werkzeug.Winkelgeschw_omega_HW
                                                  * Ist_Inter->Werkzeug.Durchmesser_HW / 2;              /* Umfangsgeschwindigkeit der HW [mm/s] */

    if(Ist_Inter->hw_n == 0) 
                    {Ist_Inter->Werkzeug.Ringumdrehung = 0.0F;}
    
    else Ist_Inter->Werkzeug.Ringumdrehung  = Ist_Inter->da /
                                            ( (Ist_Inter->Werkzeug.Durchmesser_HW * Ist_Inter->hw_n) );     /* Zeit f�r eine Ringumdrehung [s] */
    

    if(Ist_Inter->Werkzeug.Ringumdrehung > 500.0F) /*Abfangen unsinniger Werte*/
        Ist_Inter->Werkzeug.Ringumdrehung=0.0F;

    Ist_Inter->Werkzeug.omega_Ring          = Ist_Inter->Werkzeug.U_v_HW * 2 / Ist_Inter->da ;  /* Winkelgeschwindigkeit OMEGA Ring  [1/sec] //(omega=2*PI*n)*/
    Ist_Inter->Werkzeug.Winkel_grad_tU_Ring = Ist_Inter->Werkzeug.omega_Ring * 180/PI;          /* Aktueller Winkel  [�] */
        
    Ist_Inter->Werkzeug.Antrieb_ASO.ma_ist   = 0.0F;   


    /* f�r Loggerm�glichkeit der Antriebsdrehzahlen*/
    Ist_Inter->n_hw_motor_ist      =   Ein_Puff.n_hw_motor_ist;  /* HW-Motor                          [1/s]*/
    Ist_Inter->n_kwo_motor_ist     =   Ein_Puff.n_awo_motor_ist; /* KWO-Motor                         [1/s]*/
    Ist_Inter->n_kwu_motor_ist     =   Ein_Puff.n_awu_motor_ist; /* KWU-Motor                         [1/s]*/
      

    /* Kr�fte (gefiltert) */
    Ist_Inter->rs_f            = Aus_Puff.fr_mf;               /* Radiale Kraft gefiltert               [N] */
    Ist_Inter->as_f            = Aus_Puff.fa_mf;               /* Axiale Kraft gefiltert                [N] */
    Ist_Inter->ag_f            = Lokal_Puff.fag_mf;            /* Axialger�st                           [N] */   
    Ist_Inter->zar_f  = Ein_Onli.rz_f_ist_zen_einl;            /* Zentrierkraft Einlaufseite            [N] */
    Ist_Inter->zal_f  = Ein_Onli.rz_f_ist_zen_ausl;            /* Zentrierkraft Auslaufseite            [N] */
   
    /* Messwerte-IBF-Zusatzachsen */
        
    Ist_Inter->Ibf_Achse1 = Ein_Onli.Ibf_actual.Ibf_Achse1;     /* Messachse IBF 1 - Auslaufseite Sensor Tastrolle 'innen' [mm] */
    Ist_Inter->Ibf_Achse2 = Ein_Onli.Ibf_actual.Ibf_Achse2;     /* Messachse IBF 2 - Auslaufseite Sensor Tastrolle 'au�en' [mm] */
    Ist_Inter->Ibf_Achse3 = Ein_Onli.Ibf_actual.Ibf_Achse3;     /* Messachse IBF 3 [mm] */
    Ist_Inter->Ibf_Achse4 = Ein_Onli.Ibf_actual.Ibf_Achse4;     /* Messachse IBF 4 [mm] */
  

    return TRUE;
}



int RPW::IstIBF_IstInter(struct Def_Ist_Inter          Ist_Inter,
                         struct Def_IBF_Allgemein_IST  *Ist_IBF)

{
    // Funktion dient dem Austausch der IST-Werte zwischen der INTER-Struktur und IBF-Struktur
    // los geht�s


    /* �bergabe statischer Werte, die sich zur Laufzeit nicht �ndern */

    /* Geometrien */
    Ist_IBF->Vorring.D_Null                     = Ist_Inter.Vorform.da;  /* �bergabe der Rohlingswanddicke an IBF-Struktur */ 
    Ist_IBF->Vorring.Start_Ringhoehe            = Ist_Inter.Vorform.hm;  /* �bergabe der Rohlingsh�he an IBF-Struktur */   
    Ist_IBF->Vorring.Wandstaerke_Null           = Ist_Inter.Vorform.sm;  /* �bergabe der Rohlingswanddicke an IBF-Struktur */  
    Ist_IBF->Axial.Kr_geo.sin_kw_winkel_halbe   = sin_kw_winkel_halbe;   /* Sinus des halber Kegelwalzenwinkels*/
    Ist_IBF->Axial.Kr_geo.l_fehlende_spitze_ukw = Ist_Inter.Werkzeug.l_fehlende_spitze; /*L�nge theo. Spitze untere KW */

       

    /* �bergabe dynamischer Werte, die sich w�hrend Laufzeit �ndern */

    /* Allgemein */
    Ist_IBF->da       = Ist_Inter.da;                           // aktuelle Ringdurchmesser in mm
    Ist_IBF->di       = Ist_Inter.di;                           // aktueller Ringinnendurchmesser (aus Carwin)
    Ist_IBF->RS_Pos   = Ist_Inter.rs_pos;                       // aktuelle Dornschlittenposition in mm
    Ist_IBF->AG_Pos   = Ist_Inter.ag_pos_real;                  // aktuelle Axialger�stposition in mm
    //Ist_IBF->AG_Pos   = Ist_Inter.ag_pos;                     // aktuelle Axialger�stposition in mm
    Ist_IBF->ASO_Pos  = Ist_Inter.aso_pos;                      // aktuelle Axialschlittenposition oben in mm

    Ist_IBF->FR       = Ist_Inter.rs_f;                         // aktuelle Radialkraft in Newton
    Ist_IBF->FA       = Ist_Inter.as_f;                         // aktuelle Axialkraft in Newton     
   
    Ist_IBF->Wanddicke_Ist = Ist_Inter.s1r;                     // aktuelle Wandst�rke, Radialschlitten Auslaufseite [mm] 


    Ist_IBF->Zeit.Ringumdrehung = Ist_Inter.Werkzeug.Ringumdrehung; // aktuelle Zeit f�r eine Ringumdrehung [s]

    
    /* Modul: Radial */   
    
    // Filter der Radialschlittenposition   
    // KP=1, Filterzeit Tf=0.3/Abtastzeit Ta=0.1 || (Filterzeit Tf vorher =1)
    Ist_IBF->Radial.s_f_Filter.yF_neu = (1*Ist_Inter.rs_pos 
                                        + (0.3/0.1)*Ist_IBF->Radial.s_f_Filter.yF_alt) / ((0.3/0.1)+1); 
    Ist_IBF->Radial.s_f_Filter.yF_alt = Ist_IBF->Radial.s_f_Filter.yF_neu;
    Ist_IBF->Radial.s_f               = Ist_IBF->Radial.s_f_Filter.yF_neu; /* Aktuelle gefilterte Wandst�rke f�r das Radialprofilieren [mm] */


    /*------------------------------------------------------*/
    /* DA Jenkouk: April - Juli 2008                        */
    /*------------------------------------------------------*/

    Ist_IBF->DW_Regelung.Messwert_A     = Ist_Inter.Ibf_Achse1 - Ist_IBF->DW_Regelung.Messwert_Nullpunkt;     // vergl. Abb.' Kinematik und Geometrie' DA Jenkouk  [mm]
    Ist_IBF->DW_Regelung.Messwert_A_unten = abs(Ist_Inter.Ibf_Achse2 - Ist_IBF->DW_Regelung.Messwert_Nullpunkt_unten); //Betrag 
    Ist_IBF->DW_Regelung.U_v_HW         = Ist_Inter.Werkzeug.U_v_HW;                                         // Umfangsgeschwindigkeit an Hauptwalze 
    Ist_IBF->DW_Regelung.DW_Durchmesser = Ist_Inter.Werkzeug.Durchmesser_DW;                                 // Durchmesser der Dornwalze


   /* Projekt Formenspektrum*/
   Ist_IBF->Formen.t_U_Viola = Ist_Inter.Werkzeug.Ringumdrehung;
   //Ist_IBF->Formen.proz_s = 20;	//prozentuale Wanddickenabnahme, wird jetzt aus ibfpara.dat eingelesen!!!
   //Ist_IBF->Formen.Profilflag = 1;	//wird jetzt aus ibfpara.dat eingelesen.

    return TRUE;
}


int RPW::IstIBF_SollIBF(struct Def_IBF_Allgemein_SOLL  Soll_IBF,
                        struct Def_IBF_Allgemein_IST  *Ist_IBF )
{
   // Zuweisung Def_IBF_Allgemein_SOLL 

   // �bergeben der Parameter aus Soll_IBF/Ist_IBF Struktur
      
   Ist_IBF->Profilflag      = Soll_IBF.Profilflag;
   Ist_IBF->InitAchse       = Soll_IBF.InitAchse;
   Ist_IBF->ExitAchse       = Soll_IBF.ExitAchse;

   /*Casting von Initachse, damit diese char-Variable gelogget werden kann*/
   Ist_IBF->InitAchse_gecastet = (short) Soll_IBF.InitAchse;


   Ist_IBF->Axial.Profilflag  = Soll_IBF.Axial.Profilflag;
   Ist_IBF->Radial.Profilflag = Soll_IBF.Radial.Profilflag;
   
   Ist_IBF->RS_Pos_Null     = Soll_IBF.RS_Pos_Null; 
   Ist_IBF->ASO_Pos_Null    = Soll_IBF.ASO_Pos_Null;
   Ist_IBF->AG_Pos_Null     = Soll_IBF.AG_Pos_Null;           

   /* Startpositionen */
   Ist_IBF->RS_Pos_Start    = Soll_IBF.RS_Pos_Start; 	// Positionen in 'Walzen' vor Profilieren 
   Ist_IBF->AG_Pos_Start    = Soll_IBF.AG_Pos_Start; 	
   Ist_IBF->ASO_Pos_Start   = Soll_IBF.ASO_Pos_Start; 

   Ist_IBF->Rohling_s_angefahren = Soll_IBF.Rohling_s_angefahren; // Reelle Rohlingswanddicke nach dem Anfahren. Wichtig bei Anfahren in Kraft
   Ist_IBF->Rohling_h_angefahren = Soll_IBF.Rohling_h_angefahren; // Reelle Rohlingsh�he nach dem Anfahren. Wichtig bei Anfahren in Kraft

   /* Z�hler */
   Ist_IBF->Zeit.t_Halte     = Soll_IBF.Zeit.t_Halte;    // Allgemeiner Zeitz�hler
   Ist_IBF->Axial.Pr_Num     = Soll_IBF.Axial.Pr_Num;    // Aktuelle Profiliernummer
                              

   /* Flags/Schalter */
   Ist_IBF->Flag.as_kraft_anfahren_erreicht = Soll_IBF.Flag.as_kraft_anfahren_erreicht;
   Ist_IBF->Flag.rs_kraft_anfahren_erreicht = Soll_IBF.Flag.rs_kraft_anfahren_erreicht;

   Ist_IBF->Flag.AG_Start_erreicht = Soll_IBF.Flag.AG_Start_erreicht;

   /*Bissversatz*/
    if(Ist_IBF->Flag.Bissverhaeltnis == 1)
        {
        Ist_IBF->Axial.AGR_Pr[Ist_IBF->Axial.Pr_Num] = Soll_IBF.Axial.AGR_Pr[Ist_IBF->Axial.Pr_Num];
        Ist_IBF->Axial.Biss.AG_Pos_Erreicht = Soll_IBF.Axial.Biss.AG_Pos_Erreicht;
        }

   /* Turbinenscheibe*/ 
   Ist_IBF->Axial.Turbine.zweite_Ebene_erreicht = Soll_IBF.Axial.Turbine.zweite_Ebene_erreicht; // Bei Neustart muss sichergestellt werden, dass Wert geschrieben wird

	
   /*Projekt Formenspektrum*/
    Ist_IBF->Formen.Profilflag = Soll_IBF.Formen.Profilflag;



   return TRUE;

}

//---------------------------------------------------------------------------
// Methode RWP::MAIN
//---------------------------------------------------------------------------
int RPW::Main( struct Def_Ist_Inter          Ist_Inter,
               struct Def_IBF_Allgemein_IST  Ist_IBF, 
               struct Def_Soll_Inter         *Soll_Inter,
               struct Def_IBF_Allgemein_SOLL *Soll_IBF)
{

  //DA_Jenkouk_Regler(Ist_IBF, Soll_IBF);
     
  /*
   // Geometrie, gefiltert    
   
   //Ist_IBF.Radial.s_f_Filter.yF_neu = (1*Ist_Inter.s1r + (1/0.1)*Ist_IBF.Radial.s_f_Filter.yF_alt) / ((1/0.1)+1); //KP=1, Filterzeit Tf=1/Abtastzeit Ta=0.1 Filter von J�rgens s1r

   Ist_IBF.Radial.s_f_Filter.yF_neu = (1*Ist_Inter.rs_pos + (0.3/0.1)*Ist_IBF.Radial.s_f_Filter.yF_alt) / ((0.3/0.1)+1); //KP=1, Filterzeit Tf=1/Abtastzeit Ta=0.1 Filter der Radialschlittenposition
   Ist_IBF.Radial.s_f_Filter.yF_alt =  Ist_IBF.Radial.s_f_Filter.yF_neu;


   Ist_IBF.Radial.s_f          = Ist_IBF.Radial.s_f_Filter.yF_neu; // Aktuelle gefilterte Wandst�rke f�r das Radialprofilieren [mm] 

*/
  
 
//---------------------------------------------------------------------------
// Beginn AXPRO.H
//---------------------------------------------------------------------------
  
                                                                       
   float eps = 1.0F;          // Positioniergenauigkeit michl:-> war 0.1F
   
   

   
  

//++++++++++ Zyklische Initialisierung und Aktualisierung der Messgr��en ++++++++++

   // schritt_nr = Soll_Inter->schritt_nr;	// lese aktuellen Programmstatus (Koppers) 
   
   // aktuelle Positionen im Walzwerk auslesen und berechnen:
             
   // Sonstige Gr��en, Hilfsgr��en etc.
   
      
   
   

//---------------------------------------------------------------------------------------------------
//------------------ �bergabe der Zahlenwerte aus IBFPARA-Fenster -----------------------------------
//---------------------------------------------------------------------------------------------------
  
   //Axialkraft                    = 0.0F;   // Keine Vorgabe der Sollkraft  = zahl10;   //*!!!* 
   //Radialkraft                   = 0.0F;   // Keine Vorgabe der Sollkraft  = zahl11;   //*!!!* 
   //Ist_IBF.Del_Kr_AGR           = 1.0F;
   //Ist_IBF.Pos_auf_Mantel       = 1.0F;   // 	
   
//----------------------------------------------------------------------------------------------------	


//++++++++++ Ende Initialisierung ++++++++++

//########## Hand- bzw. Automatiksteuerung ausgehend von Koppers Position bei Walzenstart ##########

   // Geschwindigkeiten sind in axpro.h vorbelegt
   // Startposition f�r jeweilige Ringgeometrie in axpro.h eintragen?


         // Da Messwerte von Anlage und Mess-Schieber differieren (...), vor Beginn 
         // des Profilierens Aussenkontur (radial/axial) des Ringes von Hand anfahren ??
         // -> von Hand angefahrene Positionen beschreiben den Ausgangszustand ??

      switch (Ist_IBF.Profilflag)      // IBF_Allgemein.IBF_Allgemein.Profilflag in axpro.h definiert, bei Step 6 in interfac auf -1 gesetzt! 
      {
      
      case -1:    // --------------------------------------------------
                  //----- Startpositionen lesen, Sollwertvorgabe ------
                  //---------------------------------------------------						
                  //   Memoryflag=IBF_Allgemein.IBF_Allgemein.Profilflag;   //f�r Pausenfunktion

                  /* Geschwindigkeiten  */
                  Soll_IBF->RS_V       = 0.0F;
                  Soll_IBF->ASO_V      = 0.0F; 
                  Soll_IBF->Soll_ASU_V = 0.0F;
                  Soll_IBF->AG_V       = 0.0F;
                  Soll_IBF->ZAL_V      = 0.0F;
                  Soll_IBF->ZAR_V      = 0.0F;


                  /* Kr�fte */
                  Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf

                                  
                  /* Drehzahl */
                  Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                  Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                 
                 
                  /* Position */

                  
                  //---------------------------------------------------------------------------------
                  //------------Vorgabe f�r Startposition des Radialschlitten------------------------
                  //---------------------------------------------------------------------------------
                  
                  
                  //Soll_IBF->RS_Pos_Null = (diam_hw + Ist_IBF.Werkzeugdurchmesser)/2 + Ist_IBF.Wandstaerke_Null;  // Nullpunkt des Radialschlittens als Abstand zwischen Hauptwalzedurchmesser, Wandst�rke und Dornwalzendurchmesser 
                  Soll_IBF->RS_Pos_Null = Ist_IBF.Vorring.Wandstaerke_Null;          /* Nullpkt. Radialschlitten entsprechend vorgegeber Wandst�rke   [mm] */

                  Soll_IBF->RS_Pos = Soll_IBF->RS_Pos_Null; // definiert f�r RS_Pos in case 'a'  
                  Soll_IBF->RS_Pos_Start = Ist_IBF.Vorring.Wandstaerke_Null; //um Wands�rke von HW weg VJ Regleranalyse 
                  
                  //---------------------------------------------------------------------------------
                  //------------ Vorgabe f�r Startposition der Axialschlitten -----------------------
                  //------------    Es ist zu unterscheiden, ob Axial bzw.    ----------------------- 
                  //------------     Radial Profiliert werden soll            -----------------------
                  //---------------------------------------------------------------------------------
                  
                  if((Ist_IBF.Flag.Axial_Radialwalzen == 1)||(Ist_IBF.Flag.Axial_Radialwalzen == 2)) //Radialprofilieren oder Formenspektrum
                  {
                  Soll_IBF->AG_Pos_Start = Ist_IBF.AG_Pos; // AG_Pos == auslesen der Werte aus PA-Karte inkl. Offset
                  Soll_IBF->AG_Pos_Null  = Ist_IBF.AG_Pos; 
                  //Soll_IBF->AG_Pos       = Soll_IBF->AG_Pos;#
				  Soll_IBF->AG_Pos       = Ist_IBF.AG_Pos;
                  }
                  else // Axialprofilieren
                  {
                  //Berechnung mit anzugebenden Startdurchmesser
                  Soll_IBF->AG_Pos_Start = Ist_IBF.Axial.Anfahrdurchm - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR - Ist_IBF.Axial.Kr_geo.Kr_Br + Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw; //Bestimmen der Position
               
                  Soll_IBF->AG_Pos_Null  = Soll_IBF->AG_Pos_Start;
                    // Bereits hier muss Wert an Soll_IBF->AG_Pos �bergeben werden werden (->Ende der Funktion an Soll_Inter.ag_pos und in rwthexch.cpp)
                    // Ansonsten ist die Vorgabe f�r AG=0 beim Anfahren, dieser Wert kann nicht erreicht werden..und Ger�st w�rde entsprechend vorfahren... 
                  Soll_IBF->AG_Pos      = Soll_IBF->AG_Pos_Start; 
                  }
                                   
                  						  
                  //--------------------------------------------------------------------------------
                  //------------Vorgaben f�r oberen Axialschlitten----------------------------------
                  //--------------------------------------------------------------------------------
                  
                  
                  Soll_IBF->ASO_Pos_Null = Ist_IBF.Vorring.Start_Ringhoehe; 	/* Vorgabe der Ringh�he, die in CARWIN vorgegeben wird */
                  Soll_IBF->ASO_Pos_Start = Soll_IBF->ASO_Pos_Null;						
                  

                  #if (FALSE)
                  _settextposition(28,1);
                  printf("case -1");
                  #endif   

                  if (Ist_IBF.Zeit.t_Halte <= 0)
                  {  
                    if(Ist_IBF.Flag.rs_kraftregler_aktiv == 1) // F�r Anfahren des Dornes, wenn Kraftreglung aktiviert wurd, allerdings nicht in Kraft angewalzt werden soll
                     {
                     Soll_IBF->Zeit.t_Halte = 70;
                     }
                    else Soll_IBF->Zeit.t_Halte= 30; // 100 ms = 0,1 Sekunden //t_Halte = 10*2*diam_f/(diam_hw*f_H); // Haltezeit entspricht 1 Ringumdrehung, n�tig als Kriterium bei Kraftanfahrposition 
                    Soll_IBF->Profilflag = 0;
                  }
                    Soll_IBF->Zeit.t_Halte--;
                  break; //case -1
   
   
   case 0:     //----------------------------------------------------------------
               //----------------Routine f�r Startposition-----------------------
               //----------------------------------------------------------------
               //Memoryflag=IBF_Allgemein.IBF_Allgemein.Profilflag;						//f�r Pausefunktion
          
               switch (Ist_IBF.InitAchse) 
                  {
                  
                    // Programexample for interface-testing 
                    //Spezieller Programmcode zur Verifikation einer Dornbewegung, Axialger�st usw.
                    // Ausgangswandicke entspricht der Carwinwanddicke, Diese soll um 100 mm reduziert werden mit v=2.0 mm/s und anschlie�end wieder zur�cke auf Ausgangswanddicke                

                    //!!!ACHTUNG!!! in Datei rwth_task.cpp muss die Initialisierung wieder ge�ndert werden, wenn richtig gewalzt werden soll

					//initachse = a in rwth_exch!

                    //#ifdef Testcode
                    case 'v':   
                          
                         
                            
                            /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 5.0F;
                             Soll_IBF->ASO_V        = 0.0F; 
                             //Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 0.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F;

                             /* Kr�fte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF ); //Funktionsaufruf

                            
                            /* Positionen */
                            // Aufruf des Jenkouk-Funktionsblock
                            DA_Jenkouk_Regler(Ist_IBF, Soll_IBF);

                            if (Ist_IBF.RS_Pos >= (Soll_IBF->RS_Pos - 1.0F)|| Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos + 1.0F))
                             { 
                               // Soll_IBF->InitAchse = 'w';
                               // Soll_IBF->Zeit.t_Halte = 20;                                   
                             }
                             
                             if(Ist_IBF.Flag.DA_Jenkouk_AG_Analyse == 1)
                                 { 
                                 Soll_IBF->InitAchse = 'w';
                                 Soll_IBF->Zeit.t_Halte = 10;
                                 }
                               
                                break;

                    case 'w': /*Analyse Reglerverhalten Axialger�st DA Jenkouk */

                            /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 0.0F;
                             Soll_IBF->ASO_V        = 0.0F; 
                             //Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 100.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F;

                             /* Kr�fte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF ); //Funktionsaufruf

                             /* Betriebsart */
                             
                             
                             /* Positionen */
                             if(Ist_IBF.Zeit.t_Halte <= 0)
                             {
                             Soll_IBF->RS_Pos = Soll_IBF->RS_Pos_Start; //Dorn verfaehrt um 20 mm VJ 
                             Soll_IBF->AG_Pos = 700.0F;
                             Soll_IBF->ASO_Pos = 80.0F;
                             Soll_IBF->ZAL_Pos= 350.0F;
                             Soll_IBF->ZAR_Pos= 350.0F;


                                if (Ist_Inter.ag_pos <= Soll_IBF->AG_Pos || Ist_Inter.ag_pos == Soll_IBF->AG_Pos)
                                {
                                Soll_IBF->InitAchse = 'x';
                                Soll_IBF->Zeit.t_Halte = Ist_IBF.AG_Regelung.Haltezeit;                                   
                                 }
                             }

                             Soll_IBF->Zeit.t_Halte--;


                             


                            
                           /*  if(Ist_Inter.ag_pos >= Soll_IBF->AG_Pos - 1.0F)
                                {
                                 Soll_IBF->InitAchse = 'x';
                                 Soll_IBF->Zeit.t_Halte--;
                                }

                            if(Ist_IBF.Zeit.t_Halte == 0)
                                {
                                 //  Soll_IBF->Profilflag = 3;
                                }
                             
                                #ifdef MRAW                       
                             //�berpr�fen, ob Dornposition erreicht ist Soll_IBF->RS_Pos_Null
                            if(Ist_IBF.RS_Pos <= Soll_IBF->RS_Pos + 1.0F) // Ab hier wird Radialschlitten positionieren
                               {
                                  Soll_IBF->RS_Pos = Ist_IBF.RS_Pos - 100.0f;                                 
                                  Soll_IBF->ASO_Pos = Soll_IBF->ASO_Pos_Null - 40.0F;                                  
                                  Soll_IBF->InitAchse = 'x';
                                  break;
                               }
                               #endif
                              */
                            break;

                 case 'x':
                             /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 0.0F;
                             Soll_IBF->ASO_V        = 0.0F; 
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 100.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F;

                             /* Kr�fte */
                             Kraftsteuerung(Ist_IBF, Soll_IBF);  //Funktionsaufruf

                             if(Ist_IBF.Zeit.t_Halte <= 0)
                             {   
                             /* Positionen */
                             // Soll_IBF->RS_Pos  = Soll_IBF->RS_Pos_Start;
                            Soll_IBF->AG_Pos  = 700.0F + Ist_IBF.AG_Regelung.Sprunghoehe;
                           /*  Soll_IBF->ASO_Pos = 200.0F;
                             Soll_IBF->ZAL_Pos = 200.0F;
                             Soll_IBF->ZAR_Pos = 200.0F; 
                            */

                             if (Ist_Inter.ag_pos <= (Soll_IBF->AG_Pos - 1.0F))
                                 { 
                                     Soll_IBF->InitAchse = 'y';
                                     Soll_IBF->Zeit.t_Halte = Ist_IBF.AG_Regelung.Haltezeit;                                   
                                 }

                             }


                            Soll_IBF->Zeit.t_Halte--;
                      
        
                      /*
                            //if((Ist_Inter.ag_pos <= Soll_IBF->AG_Pos + 1.0F) || (Ist_Inter.ag_pos == Soll_IBF->AG_Pos) && (Soll_IBF->ZAL_Pos == Ist_Inter.zar_pos))
                              if(Ist_Inter.aso_pos >= Soll_IBF->ASO_Pos - 1.0F)
                                {
                                 Soll_IBF->InitAchse = 'y';
                                 Soll_IBF->Zeit.t_Halte--;

                                }
   
                             
                             #ifdef MRAW                          
                             //�berpr�fen, ob Dornposition erreicht ist Soll_IBF->RS_Pos_Null
                            if(Ist_IBF.RS_Pos <= Soll_IBF->RS_Pos + 1.0F) // Ab hier wird Radialschlitten positionieren
                               {
                                  Soll_IBF->RS_Pos = Ist_IBF.RS_Pos - 100.0f;                                 
                                  Soll_IBF->ASO_Pos = Soll_IBF->ASO_Pos_Null - 40.0F;                                  
                                  Soll_IBF->InitAchse = ' ';
                                  break;
                               }
                             #endif
                       */
                            break;


                  case 'y': 
                             
                             /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 0.0F;
                             Soll_IBF->ASO_V        = 0.0F; 
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 100.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F;

                             /* Kr�fte */
                             Kraftsteuerung(Ist_IBF, Soll_IBF);  //Funktionsaufruf

                             if(Ist_IBF.Zeit.t_Halte <= 0)
                             {   
                             /* Positionen */
                             // Soll_IBF->RS_Pos  = Soll_IBF->RS_Pos_Start;
                            Soll_IBF->AG_Pos  = 700.0F;
                           /*  Soll_IBF->ASO_Pos = 200.0F;
                             Soll_IBF->ZAL_Pos = 200.0F;
                             Soll_IBF->ZAR_Pos = 200.0F; 
                            */

                             if (Ist_Inter.ag_pos <= (Soll_IBF->AG_Pos + 1.0F))
                                 { 
                                     Soll_IBF->InitAchse = ' ';
                                 }

                             }


                            Soll_IBF->Zeit.t_Halte--;

                            break;
                  //#endif



                  case 'a':  /* Positionieren des Radialschlittens && Position des Axialschlittens �ber Ringh�he, um vorzeitiges Aufsetzen zu vermeiden */	
                              
                                                       
                            /* Geschwindigkeiten  */
                             //Soll_IBF->RS_V         = 0.0F; //vergleiche Eintr�ge in den Klammern
                             Soll_IBF->ASO_V        = 30.0F; 
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 0.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F;

                            /* Kr�fte */
                            Anwalzen_Radial(Ist_IBF , Soll_IBF); // Vorgabe der gefordeten Kr�fte, Spezialroutine f�r Kraftreglung Radialschlitten
                               
                            /* Drehzahl */
                            Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                            Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                 
                            /* Positionsvorgabe: Abh�ngig ob Kraft- oder Weggebunden */
                             //Soll_IBF->AG_Pos = Ist_IBF.Vorring.Start_Ringhoehe + 1.5F; //da Ring gerne klettert, wird bereits hier ASO zugestellt..
                            Soll_IBF->ASO_Pos = Soll_IBF->ASO_Pos_Start + 15.0F;
                            
                            /* Abfrage 'Kraft anfahren' */
                            if(Ist_IBF.Flag.rs_kraftanfahren_aktiv == 1) //aus IBF-Para(Radv01): in Kraft anwalzen 
                               {  	
                                  /* Vorgabe: Geschwindigkeit*/
                                  Soll_IBF->RS_V  = 7.0F;                  
                                  Soll_IBF->RS_Pos = Ist_IBF.RS_Pos - 10.0F;                     
                                  /* Bedingung */
                                    if( (Ist_IBF.FR) == (Soll_IBF->RS_Kraft_Anfahren) || Ist_IBF.Flag.rs_kraft_anfahren_erreicht == 1)
                                    {
                                        Soll_IBF->RS_Pos = Ist_IBF.RS_Pos;
                                        // Wenn Kraft zum ersten Mal erreicht wurde, wird Schalter gesetzt. 
                                        if(Ist_IBF.Flag.rs_kraft_anfahren_erreicht == 0) Soll_IBF->Flag.rs_kraft_anfahren_erreicht = 1;

                                        // Wenn Kraft erreicht und Axialschlitten hochgefahren ist, wird die Haltezeit t_Halte runtergez�hlt bevor der Prozess weiterl�uft
                                        if(Ist_IBF.ASO_Pos >= Ist_IBF.Vorring.Start_Ringhoehe) Soll_IBF->Zeit.t_Halte--; 
                                        

                                        if(Ist_IBF.Zeit.t_Halte <= 0)
                                            {
                                            Soll_IBF->RS_Pos  = Ist_IBF.RS_Pos;
                                            Soll_IBF->Rohling_s_angefahren = Ist_IBF.RS_Pos;    

                                            Soll_IBF->Zeit.t_Halte = 30.0F;   //Zaehler f�r n�chste CASE-Anweisung
                                            Ist_IBF.Flag.rs_kraftanfahren_aktiv = 0; //Nachdem DW auf Kraft angefahren ist, muss f�r weitern Verlauf Schalter 'Anfahren' ausgestellt werden
                                            Soll_IBF->InitAchse = 'b';
                                            } //endif(Haltezeit)
                                        break;
                                     }//endif(Abfrage, ob Kraft erreicht
                                    break;
                                }//endif->Schalter Kraftanfahren
                             else 
                               {
                                          
                                //Kraftregler aktiv, aber nicht Anwalzen in Kraft vorgew�hlt. Es kann vorkommen, dass vorgegebene Wanddicke nicht erreicht werden kann. 
                                //Deshalb wird if-Anweisung ben�tigt, um n�chstes Case zu erreichen !!!
                                if(Ist_IBF.Flag.rs_kraftregler_aktiv == 1) 
                                    {
                                        /* Vorgabe: Geschwindigkeit*/
                                        Soll_IBF->RS_V  = 7.0F;        

                                        // Radialschlitten an Startposition? Dann Haltezeit runterz�hlen
                                        if (Ist_IBF.RS_Pos <= Soll_IBF->RS_Pos) Soll_IBF->Zeit.t_Halte--;
                                        if(Ist_IBF.Zeit.t_Halte <= 0)
                                            {
                                            Soll_IBF->RS_Pos = Ist_IBF.RS_Pos;
                                            Soll_IBF->Rohling_s_angefahren = Ist_IBF.RS_Pos;
                                            // Axialschlitten hochgefahren? Dann ins n�chste 'Case'
                                            if(Ist_IBF.ASO_Pos >= Ist_IBF.Vorring.Start_Ringhoehe)
                                                {
                                                    Soll_IBF->Zeit.t_Halte = 30.0F;   //Zaehler f�r Kraftanfahrt des Axialschlittens
                                                    Soll_IBF->InitAchse = 'b';
                                                }
                                            }//endif(Haltezeit)
                                    }// endif(Kraftschalter

                               if(Ist_IBF.Flag.rs_kraftregler_aktiv == 0) 
                                    {
                                    /* Vorgabe: Geschwindigkeit*/
                                        Soll_IBF->RS_V  = 7.0F; 
                                
                                        // Radialschlitten an Startposition ?
                                        if(Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos_Null + eps)) 
                                          {
                                            // Axialschlitten hochgefahren? Dann Haltezeit t_Halte runterz�hlen
                                            if(Ist_IBF.ASO_Pos >= Ist_IBF.Vorring.Start_Ringhoehe) Soll_IBF->Zeit.t_Halte--; 
                                            
                                            if(Ist_IBF.Zeit.t_Halte <= 0)
                                                {
                                                    Soll_IBF->RS_Pos = Ist_IBF.RS_Pos;
                                                    Soll_IBF->Rohling_s_angefahren = Ist_IBF.RS_Pos;
                                                    Soll_IBF->Zeit.t_Halte = 40.0F;   //Zaehler f�r Kraftanfahrt des Axialschlittens
                                                    Soll_IBF->InitAchse = 'b';
                                                }//endif(Haltezeit)
                                            break;
                                           }// endif(RS_Pos)
                                    } //end if(Flag-Kraftregler
                               } // end else   
                             break; // zu case 'a'

    
                  case 'b':   /* Positionierung des Axialger�stes an Startposition */               				
                     
                              /* Geschwindigkeiten  */
                              Soll_IBF->RS_V         =  0.0F;
                              Soll_IBF->ASO_V        = 10.0F; 
                             //Soll_IBF->Soll_ASU_V  =  0.0F;
                              Soll_IBF->AG_V         = 15.0F;
                              Soll_IBF->ZAL_V        =  0.0F;
                              Soll_IBF->ZAR_V        =  0.0F;

                              /* Kr�fte */
                              Kraftsteuerung (Ist_IBF, Soll_IBF);   

                              /* Drehzahl */
                              Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                              Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

                              /*Z�hler - Merker*/
                              Ist_IBF.Radial.Anfangsposition_DW = Ist_IBF.Wanddicke_Ist;     // Variable in der aktuelle Dornposition definiert ist, nachdem Dorn positioniert wurde -> wichtig f�r const.Vorschub case 11ff
                          
                          
                              /*Position*/                  
                              Soll_IBF->AG_Pos = Ist_IBF.AG_Pos_Start;
                              

                              /* Vorgabe erf�llt */
                              if ( Ist_IBF.AG_Pos <= Ist_IBF.AG_Pos_Start) //Grobes Intervall
                              {
                                 if ( (Ist_IBF.AG_Pos <= (Ist_IBF.AG_Pos_Start + eps)) && !(Ist_IBF.AG_Pos <= (Ist_IBF.AG_Pos_Start - eps)) ) //Feineres Intervall
                                 {
                                    Soll_IBF->AG_Pos = Ist_IBF.AG_Pos;
									if(Ist_IBF.Flag.Axial_Radialwalzen == 0)	// Soll axial profiliert werden? 
										{
											Soll_IBF->InitAchse = 'c';			// Wenn JA, dann muss das case 'c' durchlaufen werden. Feinpositionieren des AGs auf Walzposition.
										}	
									else Soll_IBF->InitAchse = 'd';				// Sonst weiter mit Absenken des Axialschlittens
                                    /*Z�hler - Merker*/
                                    Soll_IBF->Zeit.t_Halte = 30; // Abtastrate = 100 ms./ -> Iterattionsschleife wird 10x pro Sekunde aufgerufen
                                    AGR_Soll_Pos_delta_Tr(Ist_Inter, Ist_IBF, Soll_IBF); // Berechne delta_tr_pos f�r n�chsten Schritt
                                    Soll_IBF->AG_Pos = Ist_IBF.AG_Pos + Soll_IBF->delta_tr;
                                    break;
                                 }
                                 else break;
                              }
                                                                                                                      
                              break; // zu case 'b'

                  case 'c':   /* Position Axialger�st: Profilierungsposition */
                             
                              /* Geschwindigkeiten  */
                              Soll_IBF->RS_V         = 0.0F;
                              Soll_IBF->ASO_V        = 0.0F; 
                              //Soll_IBF->Soll_ASU_V   = 0.0F;
                              Soll_IBF->AG_V         = 15.0F;
                              Soll_IBF->ZAL_V        = 0.0F;
                              Soll_IBF->ZAR_V        = 0.0F;

                              /* Kr�fte */
                              Kraftsteuerung (Ist_IBF, Soll_IBF);   
  
                              /* Drehzahl */
                              Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                              Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                          
                              /*Position*/  
                           //  Soll_IBF->AG_Pos = AGR_Soll_Pos(Ist_Inter,Ist_IBF, Soll_IBF);
                              
                           if(Soll_IBF->Zeit.t_Halte <=0 && Ist_IBF.Flag.AG_Start_erreicht == 0)
                              {
                               AGR_Soll_Pos_delta_Tr(Ist_Inter, Ist_IBF, Soll_IBF);
                               Soll_IBF->AG_Pos = Ist_IBF.AG_Pos + Soll_IBF->delta_tr;
                               Soll_IBF->Zeit.t_Halte=10;
                              }
                           if(Soll_IBF->tr_pos <= Ist_IBF.Axial.Kr_geo.Del_Kr_AGR)
                              {
                              Soll_IBF->AG_Pos = Ist_IBF.AG_Pos + Soll_IBF->delta_tr;

                              
                              }
                             Soll_IBF->Zeit.t_Halte--; 

                             if(Ist_Inter.Test.Flag == 1)
                             {
                             Soll_IBF->delta_tr=0;
                             }
                           
                              if(Soll_IBF->delta_tr >= -1.0F && Soll_IBF->delta_tr <= 1.0F)
                              {
                              Soll_IBF->Flag.AG_Start_erreicht = 1;
                              Soll_IBF->AG_Pos = Ist_IBF.AG_Pos;
                              }

                                                           
                            //  if (Ist_IBF.AG_Pos <= Soll_IBF->AG_Pos) // NUR NOTWENDIG wenn AGR_Soll_Pos(Ist_Inter,Ist_IBF,Soll_IBF) verwenden wird und nicht AGR_Soll_Pos_delta_Tr()
                              if (Ist_IBF.AG_Pos <= Soll_IBF->AG_Pos && Ist_IBF.Flag.AG_Start_erreicht == 1) 
                             {
                                    /*Z�hler - Merker*/
                                    Soll_IBF->Zeit.t_Halte--;

                                 if (   Ist_IBF.Zeit.t_Halte <= 0                         // Zeit abgelaufen und
                                        &&(   (Ist_IBF.AG_Pos <= (Soll_IBF->AG_Pos + eps))  // Ist-Position kleiner als Vorgabe
                                           && !(Ist_IBF.AG_Pos <= (Soll_IBF->AG_Pos - eps))  // aber nicht �ber das Ziel hinaus
                                          )
                                    )
                                 {
                                    Soll_IBF->AG_Pos = Ist_IBF.AG_Pos;

                                    /*Z�hler - Merker*/
                                    Soll_IBF->Zeit.t_Halte= 15; // 200 ms = 2 sec abwarten
                              
                                    Soll_IBF->InitAchse = 'd';

                                    break;
                                 }
                                 else break;
                              }
                              
                              
                              break; // zu case 'c'
                  
                  case 'd':   /*Position Axialschlitten*/
                              
                              /* Geschwindigkeiten  */
                              Soll_IBF->RS_V         = 0.0F;
                              //Soll_IBF->ASO_V        =  s.Klammer 
                              //Soll_IBF->Soll_ASU_V   = 0.0F;
                              Soll_IBF->AG_V         = 15.0F;
                              Soll_IBF->ZAL_V        = 0.0F;
                              Soll_IBF->ZAR_V        = 0.0F;

                              /* Kr�fte */
                              Anwalzen_Axial(Ist_IBF, Soll_IBF);   // // Vorgabe der gefordeten Kr�fte, Spezialroutine f�r Kraftreglung Axialschlitten
                              //Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf

                              /* Drehzahl */
                              Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                              Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

                              /*Position*/  
                              // auch Klammer beachten
                              // Soll_IBF->ASO_Pos = Soll_IBF->ASO_Pos_Start;
                              
                    //-------------------------------------
                    //------ Kraftanfahren ----------------
                              if(Ist_IBF.Flag.as_kraftanfahren_aktiv == 1) //In Kraft anwalzen aus: (RAW->IBFPara.ini in rwthexch.cpp || MRAW-> IBF-Para.cpp)                                
                                {  	
                                 /* Vorgabe: Geschwindigkeit*/
                                    Soll_IBF->ASO_V  = -10.0F;                  
                                    Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos - 5.0F;                    
                              
                                  // Abfragen, ob Kraft erreicht ist
                                    if( (Ist_IBF.FA) == (Soll_IBF->AS_Kraft_Anfahren) || Ist_IBF.Flag.as_kraft_anfahren_erreicht == 1)
                                    {   
                                        Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos;
                                        Soll_IBF->Rohling_h_angefahren= Ist_IBF.ASO_Pos;

                                        Soll_IBF->Zeit.t_Halte--; // Wenn Kraft erreicht ist soll die Zeit t ablaufen bevor der Prozess weiterl�uft
                                        if(Ist_IBF.Flag.as_kraft_anfahren_erreicht == 0) Soll_IBF->Flag.as_kraft_anfahren_erreicht = 1;
                                        
                                        if(Ist_IBF.Zeit.t_Halte <= 0)
                                        {
                                           Soll_IBF->Zeit.t_Halte    = 100.0F;   //Zaehler f�r Kraftanfahrt des Axialschlittens
                                           Soll_IBF->InitAchse  = ' '; // Soll_IBF->InitAchse  = 'z';
                                           
                                           Ist_IBF.Flag.as_kraftanfahren_aktiv = 0; //Nachdem ASO auf Kraft angefahren ist, muss f�r weitern Verlauf Schalter 'Anfahren' ausgestellt werden
                                           Soll_IBF->Profilflag = 1;
                                        } //endif(Haltezeit)
                                        
                                     }//endif(Abfrage, ob Kraft erreicht
                                    
                                }//endif->"Schalter Kraftanfahren"
                       
                       //--------------------------------------
                       //----- Anfahren in Position -----------
                       //--------------------------------------

                               else // Anfahren unter Vorgabe der Position
                               {
                                 /* Vorgabe: Geschwindigkeit*/
                                 Soll_IBF->ASO_V = -18.0F;
                                 Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos_Start - Ist_IBF.ASO_Pos_Differenz;    // Ist_IBF.ASO_Pos_Differenz = Korektur der Starth�he aus Carwin (in IBF_ini definiert)
                                                                                                            // ASO wird sonst auf Starth�he gesetzt und beim 'Positonieren des AG rutscht ASO �ber Strinseite

                                 
                                 if(Ist_IBF.ASO_Pos <= (Soll_IBF->ASO_Pos + eps)) 
                                  {
                                    Soll_IBF->Zeit.t_Halte--; // Wenn Position erreicht wurde, soll die Zeit t ablaufen bevor der Prozess weiterl�uft
                                    if(Ist_IBF.Zeit.t_Halte <= 0)
                                       {
                                          Soll_IBF->AG_Regelung.psi      = Ist_IBF.Axial.AGR_Pr[0]/ Ist_IBF.RS_Pos;
                                          Soll_IBF->ASO_Pos              = Ist_IBF.ASO_Pos;
                                          Soll_IBF->Rohling_h_angefahren = Ist_IBF.ASO_Pos;
                                                    
                                          Soll_IBF->Zeit.t_Halte    = 15.0F;   //Zaehler f�r Kraftanfahrt des Axialschlittens
                                          Soll_IBF->InitAchse  = ' '; // Soll_IBF->InitAchse  = 'z';
                                          
                                          Soll_IBF->Profilflag = 1;  
                                          
                                          Soll_IBF->Axial.Profilflag = 9;
                                          //Soll_IBF->Radial.Profilflag = 9;

                                          Soll_IBF->DW_Regelung.Startmesswert = Ist_IBF.DW_Regelung.Messwert_A;

                                        }//endif(Haltezeit)
                                    
                                  }//end if(ASO_Pos)
                                } //end else

                                                                  
                                                				
                              break;//break

                  case 'z':   // 2 Umdrehungen abwarten f�r gleichm��iges Profil �ber Umfang 
                              Soll_IBF->Zeit.t_Halte--;
                              if (Ist_IBF.Zeit.t_Halte <= 0) {
                                                                IBF_Abschaltung(Soll_Inter, Ist_IBF); 
                                                             };
                              break;  // zu case 'z'
                                                
                  default:    
                              #ifdef MRAW
                                 _settextposition(9,1);
                                 printf(" InitAchse: %d - Warum default ?!? ", Ist_IBF.InitAchse);
                              #endif   
                              break;
                              
                  } //	Klammer zu: switch (InitAchse) von case0 
                  break;
        
         case 1:     // Aufruf der jeweilgen IBF-Module IBF-flex.Radial, IBF-Flex.Axial, Formenspektrum
                     
                    
                     if(Ist_IBF.Flag.Axial_Radialwalzen == 0) // 0= Axialwalzen|1= Radialwalzen
                        {
                         
                         flexibel_Axial(Ist_Inter,
                                        Ist_IBF, 
                                        Soll_Inter,
                                        Soll_IBF); 
                        }
                     
                     else if(Ist_IBF.Flag.Axial_Radialwalzen == 1) // 0= Axialwalzen|1= Radialwalzen
                        {
                         
                         flexibel_Radial(Ist_Inter,
                                         Ist_IBF, 
                                         &*Soll_Inter,
                                         &*Soll_IBF); 
                        }
					 else if(Ist_IBF.Flag.Axial_Radialwalzen == 2) // 0= Axialwalzen|1= Radialwalzen, 2= Formernspektrum
                        {
                         
                         formenspektrum(Ist_Inter,
                                         Ist_IBF, 
                                         &*Soll_Inter,
                                         &*Soll_IBF); 
                        }

                     else Soll_IBF->Profilflag = 13;
                     
                     break;
            

                     

         case 13:   // Ende des Walzprozesses -> Auffahren der Anlage
                    IBF_Abschaltung(Soll_Inter, Ist_IBF); 
                    break;

 //----------------------------------------------------------------------------------------------------------------------------
        case 9:   /* -------------------------------------------------------------
                    ; Axialschlitten mit const. vorgegebener Geschwindigkeit zustellen
                    ; Axialger�st mit Funktion AGR_Soll_Pos() positionieren
                    ; Radialschlitten in Kraftsteuerung an Ring andr�cken, daf�r muss allerdings Kraftsteuerung vorgew�hlt sein -> 
                    ;--------------------------------------------------------------*/

                    /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 2.0F;
                             Soll_IBF->ASO_V        = 4.0F; //Ist_IBF.Axial.Vorschub/Ist_IBF.Zeit.Ringumdrehung; // [mm/U] / [s/U]
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 10.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F; 

                             /* Kr�fte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf
                               
                             /* Drehzahl */
                             Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                             Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                 
                             /* Positionsvorgabe: Abh�ngig ob Kraft- oder Weggebunden */
                             Soll_IBF->AG_Pos = AGR_Soll_Pos(Ist_Inter, Ist_IBF, Soll_IBF);
                             Soll_IBF->ASO_Pos = Ist_IBF.Rohling_h_angefahren - Ist_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num];
                             

                             if(Ist_IBF.ASO_Pos <= Soll_IBF->ASO_Pos) 
                                 {
                                   Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos;
                                   Soll_IBF->Zeit.t_Halte = 20; //Ist_Inter.Werkzeug.Ringumdrehung * Soll_IBF->Axial.Umdrehungen;   //Zeit berechnen f�r x-Ringumdrehungen
                                   Soll_IBF->Profilflag = 11;
                                 }
                     
                            break; 

          case 11:          /* -------------------------------------------------------------
                            ;  Rundungsphase
                            ;--------------------------------------------------------------*/

                            /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 2.0F; 
                             Soll_IBF->ASO_V        = 1.0F; //Axialschlitten soll in Rundungsphase nicht zustellen
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 10.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F; 

                             /* Kr�fte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf
                               
                             /* Drehzahl */
                             Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                             Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                 
                             /* Positionsvorgabe: Abh�ngig ob Kraft- oder Weggebunden */
                             Soll_IBF->AG_Pos = AGR_Soll_Pos(Ist_Inter,Ist_IBF,&*Soll_IBF);
                             
                             if(Ist_IBF.Zeit.t_Halte <= 0) 
                                 {
                                   Soll_IBF->Profilflag = 12;
                                 }
                             Soll_IBF->Zeit.t_Halte--; // Runterz�hlen der Zeit f�r Gl�ttungsrunde
                             break;

         case 12:           /* -------------------------------------------------------------
                            ; Hochfahren des Axialschlittens und Abfragen, ob weitere                             
                            ; Profilstufe gewalzt werden soll
                            ;--------------------------------------------------------------*/
                            
                            /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 2.0F; 
                             Soll_IBF->ASO_V        = 30.0F; 
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 10.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F; 

                             /* Kr�fte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf
                               
                             /* Drehzahl */
                             Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                             Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

                             /* Position */
                            Soll_IBF->ASO_Pos = Ist_IBF.Rohling_h_angefahren + 30.0F;

                             /* Abfrage ob weiteres Profil gewalzt werden soll / Schalter setzen*/
                             if(Ist_IBF.ASO_Pos >= Soll_IBF->ASO_Pos - 1.0F) 
                                 {
                                    Soll_IBF->Axial.Pr_Num = Soll_IBF->Axial.Pr_Num + 1;
                                    if(Soll_IBF->Axial.Pr_Num == Ist_IBF.Axial.Profilanzahl)
                                       {
                                       Soll_IBF->Profilflag = 13; // Prozessende
                                       }
                                    if(Soll_IBF->Axial.Pr_Num < Ist_IBF.Axial.Profilanzahl) 
                                       {
                                        Soll_IBF->AG_Pos_Start =  Ist_Inter.da 
                                                                - Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num] 
                                                                - Ist_IBF.Axial.Kr_geo.Kr_Br 
                                                                - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
                                                                + Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw;
                                       Soll_IBF->Profilflag = 0;    // Axialger�st neu positionieren
                                       Soll_IBF->InitAchse = 'b';   
                                       }
                                 }
                              break;
 //-----------------------------------------------------------------------------------


         /*
   
         case 1:     // Vergleich der eingegebenen Wandst�rke und der, per Kraftsteuerung angefahrenen Wandst�rke
                     // Routine, ob Schalter gesetzt ist oder nicht -> Schalter (0,1,2)
                     
                     Soll_IBF->Soll_ASO_Pos_alt = Ist_IBF.ASO_Pos;    // F�r Berechnung der neuen ASO-H�he w�hrend der Walzung . Derzeit in case 11 & case 12 (konti & diskonti Vorschub) verwendet.
 

                     Ist_IBF.Radial.s_f_alt = Ist_IBF.Radial.s_f;   // dem Wert s_f_alt wird hier bereits der erste Wert vorgegeben, damit in case 11/12 keine Division durch NULL stattfindet.... 
                     
                     
                     if(Ist_IBF.Radial.Schalter_Kont_DisKo == 0)  // kontinuierlicher Vorschub
                        {
                            Soll_IBF->Profilflag = 11; 
                             //Ist_IBF.Radial.s_ist = 0;
                            break;
                         }
                     
                     if(Ist_IBF.Radial.Schalter_Kont_DisKo == 1) //diskontinuierlicher Vorschub (eps �ber Weg)
                        {
                            Soll_IBF->Profilflag = 12; 
                            Soll_IBF->RS_Pos = Ist_IBF.RS_Pos - 0.5f;
                            break;
                        }
                     
                     if (Ist_IBF.Radial.Schalter_Kont_DisKo == 2) //f�r Ingos Cr-Vorschub
		   			   {
		   					Soll_IBF->Profilflag = 15; 
                            Soll_IBF->Radial.Cr.os_i = 0;    //erste Ringh�lfte 0, zweite 1

		   				   //Zeit f�r 2 Umdrehungen bei denen der Dorn in den Ring vorf�hrt bis Schnabel-Formel greift
                        	//Soll_IBF->Radial.t_dis_h = 2*(Ist_IBF.Vorring.D_Null/(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.Werkzeug.Drehzahl_HW)); 
                            Soll_IBF->Radial.t_dis_h = Ist_IBF.Zeit.Ringumdrehung * 10.0;
		   				
                        	Ist_IBF.Zeit.Halbe_Ringumdrehung = Ist_IBF.Zeit.Ringumdrehung / 2; 

		   					Soll_IBF->RS_Pos = Ist_IBF.RS_Pos - 10.0F;  
                            Soll_IBF->Zeit.t_Halte = 30; // 30*100 ms = 3000 ms -> 1s = 1000 ms
                            break;
                        } //Soll_RS_Pos damit er in case 15 einfach kontinuierlich(mit vorgegebener Geschw.) verf�hrt
		   					
                     
                     else
                     {
                        #ifdef MRAW
                           _settextposition(10,15);
                           printf("Fehler in Schalterstellung");
                        #endif
                     }
                     break;
                    
       
        case 11:      // Walzungsroutine: const. Vorschub 
                     
                     // Geschwindigkeiten  
                     Soll_IBF->RS_V         = Soll_IBF->Radial.Vorschubgeschw_Dw;   // Vorschubgeschwindigkeit Dornwalze;
                     Soll_IBF->ASO_V        = 10.0F; 
                     //Soll_IBF->Soll_ASU_V   = 0.0F;
                     Soll_IBF->AG_V         = 10.0F;
                     Soll_IBF->ZAL_V        = 0.0F;
                     Soll_IBF->ZAR_V        = 0.0F;

                     // Kr�fte 
                     Kraftsteuerung(Ist_IBF, Soll_IBF);   
  
                     // Drehzahl 
                     Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                     Soll_Inter->kwu_n = KW_Drehzahl_unten(Ist_Inter, &Ist_IBF);
                          
                     // Position
                     
                     if(Soll_IBF->Radial.Stegstaerke != 0)   // Abfrage ob Stegst�rke angegeben
                        {
                            //Soll_IBF->RS_Pos = (Ist_Inter.Werkzeug.Durchmeser_HW + Ist_Inter.Werkzeug.Durchmesser_DW)/2 + Soll_IBF->Radial.Stegstaerke;
                            Soll_IBF->RS_Pos = Soll_IBF->Radial.Stegstaerke;
                        }
                     else Soll_IBF->RS_Pos = Ist_IBF.Radial.Anfangsposition_DW - Soll_IBF->Radial.delta_s;  //Ist_IBF.Radial.Anfangsposition_DW wird in case 0 -> case 'a' gesetzt.....
                                                
                     

                     if(Ist_IBF.RS_Pos <= Soll_IBF->RS_Pos || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos + eps) || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos - eps))
                        {	
                            Soll_IBF->Zeit.t_Halte= Soll_IBF->Radial.Umdrehungen * 10 * (Ist_IBF.Vorring.D_Null/(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.hw_n)); // n Umdrehungen, 10 * "100" ms Aufrufzyklus = 1000 ms = 1s;  
                            
                            Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos; // damit kein Durck ausge�bt wird wenn Walzproze� beendet ist muss hier noch eine Konstante eingef�gt werden (z.B. 5)
                            
                            Soll_IBF->Profilflag = 2; 
                            break;
                        }                  
                     
                        //------------------------------------------------------------------------------------------------------
                        //----------------------- Positionssteuerung des oberen Axialschlittens --------------------------------
                        //------------------------------------------------------------------------------------------------------
                        
                        if(Soll_IBF->Radial.t_dis_h <=0)
                        {
                           // Berechnung der H�henabnahme f�r den n�chsten Zeitschritt nach der Formel:
                           // Delta_h = 10 mm Werkzeugbreite *gef.Wanddicke (diam_f)*(Wanddicke[n]^2-Wanddicke[n-1]^2)+Wanddicke[n-1]^2-Wanddike[n]^2/(Klammerausdruck)
                           Soll_IBF->Radial.delta_h = Ist_IBF.Radial.Werkzeugbreite *(Ist_Inter.da *   (Ist_IBF.Radial.s_f_alt - Ist_IBF.Radial.s_f)
                                                        - (Ist_IBF.Radial.s_f_alt*Ist_IBF.Radial.s_f_alt) 
                                                        + (Ist_IBF.Radial.s_f*Ist_IBF.Radial.s_f)
                                                        )/(Ist_Inter.da * Ist_IBF.Radial.s_f_alt - (Ist_IBF.Radial.s_f_alt*Ist_IBF.Radial.s_f_alt)); 
                           
                           
                           // Positionen 
                           Soll_IBF->ASO_Pos = Soll_IBF->Soll_ASO_Pos_alt + Soll_IBF->Radial.delta_h;
                           
                           Soll_IBF->Soll_ASO_Pos_alt = Soll_IBF->ASO_Pos; 
 
                           Ist_IBF.Radial.s_f_alt = Ist_IBF.Radial.s_f;   
                           // Zeit setzen 
                           Soll_IBF->Radial.t_dis_h = 10*(Ist_IBF.Vorring.D_Null/(Ist_Inter.Werkzeug.Durchmesser_HW*Ist_Inter.hw_n)); // 1 Umdrehungen (kein Wert vor der 10), 10*100 ms = 1000 ms = 1s
                        }        
                        
                        Soll_IBF->Radial.t_dis_h--;
                        
                        break;

           case 12:    // Walroutine: diskontinuierlicher Vorschub (bezogen Wanddicke Epsilon �ber Weg) 
	   				    
                       // Geschwindigkeiten  
                        Soll_IBF->RS_V         = Soll_IBF->Radial.Vorschubgeschw_Dw;   // Vorschubgeschwindigkeit Dornwalze;
                        Soll_IBF->ASO_V        = 5.0F; 
                        //Soll_IBF->Soll_ASU_V   = 0.0F;
                        Soll_IBF->AG_V         = 10.0F;
                        Soll_IBF->ZAL_V        = 0.0F;
                        Soll_IBF->ZAR_V        = 0.0F;

                       // Kr�fte 
                        Kraftsteuerung(Ist_IBF, Soll_IBF);   
  
                       // Drehzahl 
                        Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                        Soll_Inter->kwu_n = KW_Drehzahl_unten(Ist_Inter, &Ist_IBF);
                          
                       // Position  
		
                       if(Soll_IBF->Radial.Stegstaerke != 0)   // Abfrage ob Stegst�rke angegeben wurde
                        {
                            //Soll_IBF->RS_Pos = (Ist_Inter.Werkzeug.Durchmeser_HW + Ist_Inter.Werkzeug.Durchmesser_DW)/2 + Soll_IBF->Radial.Stegstaerke;
                            Soll_IBF->RS_Pos_end = Soll_IBF->Radial.Stegstaerke;
                        }
                       else Soll_IBF->RS_Pos_end = Ist_IBF.Radial.Anfangsposition_DW - Soll_IBF->Radial.delta_s;  //Ist_IBF.Radial.Anfangsposition_DW wird in case 0 -> case 'a' gesetzt.....
                   
                  	 
                  	  //------------------------------------------------------------------------------------------------------
                  	  //-------------Routine bei der die neue RS-Pos bestimmt wird, dies in Abh�ngigkeit von eps -------------
                  	  //------------------------------------------------------------------------------------------------------
                  	  
                  	  
                  	  if((Soll_IBF->Radial.t_dis_h <= 0) && (Ist_IBF.RS_Pos == Soll_IBF->RS_Pos || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos + 0.1))) // || RS_Pos >= (Soll_RS_Pos-0.01)))
                  	  { 
                  	   	
                  	   // DELTA S = abnahme_s ; s_f ist die gefilterte Wanddicke aus dem Interfac.h
                  	   Soll_IBF->Radial.abnahme_s = (Soll_IBF->Radial.eps_Vorschub/100) * Ist_IBF.Radial.s_f; // eps_Vorschub aus IBF_Data.ini
                  	                                            
                  	   Soll_IBF->RS_Pos = Ist_IBF.RS_Pos - Soll_IBF->Radial.abnahme_s;
                  	                     	 
                  	   // neue Zeit f�r n�chste Ringumdrehung. Bezieht sich allerdings auf den Anfangs-Ausgangsdurchmesser...
                  	   Soll_IBF->Radial.t_dis_h = 10*(Ist_IBF.Vorring.D_Null/(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.hw_n)); // 10*100 ms = 1000 ms = 1s
                  	   break;
                  	   }  
                  	                     	    
                  	   if(Ist_IBF.RS_Pos == Soll_IBF->RS_Pos || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos + 0.1)) //|| RS_Pos >= (Soll_RS_Pos-0.01)) 
                  	   {Soll_IBF->Radial.t_dis_h--;}

                       //------------------------------------------------------------------------------------------------------
                        //----------------------- Positionssteuerung des oberen Axialschlittens --------------------------------
                        //------------------------------------------------------------------------------------------------------
                        
                        if(Soll_IBF->Radial.t_dis_h <=0)
                        {
                           // Berechnung der H�henabnahme f�r den n�chsten Zeitschritt nach der Formel:
                           // Delta_h = 10 mm Werkzeugbreite *gef.Wanddicke (diam_f)*(Wanddicke[n]^2-Wanddicke[n-1]^2)+Wanddicke[n-1]^2-Wanddike[n]^2/(Klammerausdruck)
                           Soll_IBF->Radial.delta_h = Ist_IBF.Radial.Werkzeugbreite *(Ist_Inter.da *   (Ist_IBF.Radial.s_f_alt - Ist_IBF.Radial.s_f)
                                                        - (Ist_IBF.Radial.s_f_alt*Ist_IBF.Radial.s_f_alt) 
                                                        + (Ist_IBF.Radial.s_f*Ist_IBF.Radial.s_f)
                                                        )/(Ist_Inter.da * Ist_IBF.Radial.s_f_alt - (Ist_IBF.Radial.s_f_alt*Ist_IBF.Radial.s_f_alt)); 
                           
                           
                           Soll_IBF->ASO_Pos = Soll_IBF->Soll_ASO_Pos_alt + Soll_IBF->Radial.delta_h;
                           
                           Soll_IBF->Soll_ASO_Pos_alt = Soll_IBF->ASO_Pos;  
                           Ist_IBF.Radial.s_f_alt = Ist_IBF.Radial.s_f;   
                        }
                  	                     		
                  		//---------------------------------------------------------------------------------------------------
                  		//----------------------            Abbruchkriterium                           ----------------------
                  		//---------------------------------------------------------------------------------------------------
                  		      
                  				
						if(Ist_IBF.RS_Pos <= Soll_IBF->RS_Pos_end || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos_end + eps) || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos_end - eps))
                  		 {	
                  			Soll_IBF->Zeit.t_Halte= Soll_IBF->Radial.Umdrehungen * 10 * (Ist_IBF.Vorring.D_Null/(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.hw_n)); // n Umdrehungen, 10 * "100" ms Aufrufzyklus = 1000 ms = 1s;  

           				    Soll_IBF->Profilflag=2; 
                  	
           					break;
                         }                  				
		   							   							
						
											
                  break;   

        

        case 15:     // Walzroutine Cr-Vorschub. 1 Schritt Berechnung der Parameter f�r die erste Ringumdrehung, die in case 16 ben�tigt werden 
                          
        
                          Soll_IBF->Radial.Cr.a = Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.da;           // Hauptwalzendurch. * Au�endurchmesser
                          Soll_IBF->Radial.Cr.b = Ist_Inter.di * Ist_Inter.Werkzeug.Durchmesser_DW;           // Innendurchmesser(Durchmesser-2*Wandst�rke) * Dornwalze
	   				      Soll_IBF->Radial.Cr.c = Ist_Inter.Werkzeug.Durchmesser_HW + Ist_Inter.da;           // Hauptwalzemdurch. + Au�endurchmesser
	   				      Soll_IBF->Radial.Cr.d = Ist_Inter.di - Ist_Inter.Werkzeug.Durchmesser_DW;			  // Innendurchmesser - Dornwalze
	   				      Soll_IBF->Radial.Cr.e = pow(Soll_IBF->Radial.Walzspalt_Cr,2);                       // Cr * Cr
	   				    
	   				      Soll_IBF->Radial.Cr.o = (Soll_IBF->Radial.Cr.a/Soll_IBF->Radial.Cr.c) * (Soll_IBF->Radial.Cr.b/Soll_IBF->Radial.Cr.d);
	   				      Soll_IBF->Radial.Cr.u = (Soll_IBF->Radial.Cr.a/Soll_IBF->Radial.Cr.c) + (Soll_IBF->Radial.Cr.b/Soll_IBF->Radial.Cr.d); 
	   				    
	   				 		                  
		                  Soll_IBF->Radial.Cr.g = (Ist_IBF.Radial.s_f + 1/Soll_IBF->Radial.Cr.e * (Soll_IBF->Radial.Cr.o / Soll_IBF->Radial.Cr.u));     
		                  Soll_IBF->Radial.Cr.f = 2 * Soll_IBF->Radial.Cr.g;

		                  //abnahme_s = -2*g + ( sqrt( pow(f,2) - 4*pow(s_f,2)))
                          Soll_IBF->Radial.abnahme_s = -2*Soll_IBF->Radial.Cr.g + ( sqrt( pow(Soll_IBF->Radial.Cr.f,2) - 4*pow(Ist_IBF.Radial.s_f,2))); //Delta s mittels der momentanen Wanddicke berechnen
		                  
                          
                          if(Ist_IBF.Zeit.t_Halte <= 0)
                          {
		                  // Weil Zeitprobleme mit ausgestellter HW keine Vorschubgeschwi ergeben habenSoll_IBF->Radial.dw_vn = 2.0F; 
                          Soll_IBF->Radial.dw_vn = -1* Soll_IBF->Radial.abnahme_s /(Ist_IBF.Zeit.Ringumdrehung * 2);   //Dornvorschubgeschwindigkeit f�r case 15      
		                  Soll_IBF->Profilflag =  16;       
                          }
                          Soll_IBF->Zeit.t_Halte--;
		                  break;
        
        case 16:    // Walzroutine Cr-Vorschub: 2. Schritt: Dorn in der ersten Ringumdrehung positionieren und ben�tigte Werte aufnehmen 
                    
                    // Geschwindigkeiten  
                        Soll_IBF->RS_V         = Soll_IBF->Radial.dw_vn;   // Vorschubgeschw_DW erechnet in case 15 
                        Soll_IBF->ASO_V        = 5.0F; 
                        //Soll_IBF->Soll_ASU_V   = 0.0F;
                        Soll_IBF->AG_V         = 10.0F;
                        Soll_IBF->ZAL_V        = 0.0F;
                        Soll_IBF->ZAR_V        = 0.0F;

                       // Kr�fte 
                        Kraftsteuerung (Ist_IBF , Soll_IBF);   
  
                       // Drehzahl 
                        Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                        Soll_Inter->kwu_n = KW_Drehzahl_unten(Ist_Inter, &Ist_IBF);
                          
                       
     		                
		                		                 
		                //Wanddicke f�r 2 St�tzpunkte �ber Umfang aufzeichnen
		             
		                if ((Soll_IBF->Radial.Cr.os_i == 0) && (Soll_IBF->Radial.t_dis_h >= Ist_IBF.Zeit.Halbe_Ringumdrehung)) //Aufzeichnen des ersten St�tzpunkt, wenn erste St�tzstelle aufgezeichnet wird muss die Zeit gr�der als die halbe Umlaufzeit sein
		                  {
		                	 Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i] = Ist_IBF.Radial.s_f; // speicher die Wandst�rke im Feld [i]
		                			                	
		                	 if(Soll_IBF->Radial.Cr.os_i >= 1)      	   
		                	    {
                                 Soll_IBF->Radial.Cr.os_i = -1;
                                }
    
		                	 Soll_IBF->Radial.Cr.os_i = Soll_IBF->Radial.Cr.os_i + 1;
		                  }
		                	
		                else 
                        if((Soll_IBF->Radial.Cr.os_i ==1) && (Soll_IBF->Radial.t_dis_h <= Ist_IBF.Zeit.Halbe_Ringumdrehung)) //Aufzeichnen des zweiten St�tzpunktes
		                  {
		                	Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i] = Ist_IBF.Radial.s_f; // speicher die Wandst�rke im Feld [i]
		                	
                            if(Soll_IBF->Radial.Cr.os_i >=1)      //bei Array[2]	          
                              {
                               Soll_IBF->Radial.Cr.os_i = -1;
                              }  
  
		                	Soll_IBF->Radial.Cr.os_i= Soll_IBF->Radial.Cr.os_i + 1;
		                  }

                        // Position  
		                           	   
                  	    if(Soll_IBF->Radial.t_dis_h <=0 )  //Zeit wird in case 1 definiert
                  	     { 
                  	        Soll_IBF->Profilflag = 17; 
                            Soll_IBF->Radial.Cr.os_i = 0;
                            Soll_IBF->Radial.t_dis_h = 0;
                            Ist_IBF.Zeit.Halbe_Ringumdrehung = Ist_IBF.Zeit.Ringumdrehung / 2;
                  	
	                        if(Soll_IBF->Radial.Stegstaerke != 0)   // Abfrage ob Stegst�rke angegeben wurde
                              {
                               Soll_IBF->RS_Pos_end = Soll_IBF->Radial.Stegstaerke;
                              }
                            else 
                            Soll_IBF->RS_Pos_end = Ist_IBF.Radial.Anfangsposition_DW - Soll_IBF->Radial.delta_s;  //Ist_IBF.Radial.Anfangsposition_DW wird in case 0 -> case 'a' gesetzt.....
                                                      	
                  	        break;
                        } 
                  	
                  	    Soll_IBF->Radial.t_dis_h--; // runterz�hlen der Zeit, die bei case 1 gesetzt wurde
                  	    break;

        case 17:    // Walzroutine Cr-Vorschub: 3. Schritt: Dornposition f�r jede halbe Ringumdrehung neu vorgeben  
                        
                        // Geschwindigkeiten  
                        Soll_IBF->RS_V         = Soll_IBF->Radial.Vorschubgeschw_Dw;   // Vorschubgeschw_DW erechnet in case 15 
                        Soll_IBF->ASO_V        = Soll_IBF->Radial.Vorschubgeschw_ASO; 
                        //Soll_IBF->Soll_ASU_V   = 0.0F;
                        Soll_IBF->AG_V         = 10.0F;
                        Soll_IBF->ZAL_V        = 0.0F;
                        Soll_IBF->ZAR_V        = 0.0F;


                        // f�r �berpr�fung im Logger
                        //Soll_IBF->Radial.dw_vn = Soll_IBF->RS_V;

                       // Kr�fte 
                        Kraftsteuerung(Ist_IBF, Soll_IBF);   
  
                       // Drehzahl 
                        Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                        Soll_Inter->kwu_n = KW_Drehzahl_unten(Ist_Inter, &Ist_IBF);
                          
                       
	   				    //------------------------------------------------------------------------
	   				    //Delta_s anhand des const Walzspaltverh�ltnis cr
	   				    	   				    

	   				    if(Soll_IBF->Radial.t_dis_h <= Ist_IBF.Zeit.Halbe_Ringumdrehung) 
     	   				  {
	   				       
                           //Neue Zeiten f�r n�chsten Zyklus vorgeben....
		                   Ist_IBF.Zeit.Halbe_Ringumdrehung = Ist_IBF.Zeit.Ringumdrehung / 2;
                                                              
                           //Zahlenwert der Ringumdrehung in Sekunde vorgegeben. 
                           //Da Zyklus alle 100 ms aufgerufen wird, muss t_dis_h von vorhandenen Millisekunden auf Sekunde normiert werden. Faktor 10
                           //+1 f�r die ersten 100 ms, die sofort nach der Klammer subtrahiert werden
                           Soll_IBF->Radial.t_dis_h   = Ist_IBF.Zeit.Ringumdrehung * 10.0 + 1; 
 
                          
                           
                           // Variablen der Formel berechnen
    	   				   Soll_IBF->Radial.Cr.a = Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.da;           // Hauptwalzendurch. * Au�endurchmesser
                           Soll_IBF->Radial.Cr.b = Ist_Inter.di * Ist_Inter.Werkzeug.Durchmesser_DW;           // Innendurchmesser(Durchmesser-2*Wandst�rke) * Dornwalze
	   				       Soll_IBF->Radial.Cr.c = Ist_Inter.Werkzeug.Durchmesser_HW + Ist_Inter.da;           // Hauptwalzemdurch. + Au�endurchmesser
	   				       Soll_IBF->Radial.Cr.d = Ist_Inter.di - Ist_Inter.Werkzeug.Durchmesser_DW;		   // Au�endurchmesser - Dornwalze
	   				       //Soll_IBF->Radial.Cr.e = pow(Soll_IBF->Radial.Walzspalt_Cr,2);                       // Cr * Cr |-> bereits in 16 berechnet
	   				    
	   				       Soll_IBF->Radial.Cr.o = (Soll_IBF->Radial.Cr.a/Soll_IBF->Radial.Cr.c) * (Soll_IBF->Radial.Cr.b/Soll_IBF->Radial.Cr.d);
	   				       Soll_IBF->Radial.Cr.u = (Soll_IBF->Radial.Cr.a/Soll_IBF->Radial.Cr.c) + (Soll_IBF->Radial.Cr.b/Soll_IBF->Radial.Cr.d); 
	   				    
	   				        //-------------------------------------------------------------------------
	   				    
		                   Soll_IBF->Radial.Cr.g = (Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i] + 1/ Soll_IBF->Radial.Cr.e*(Soll_IBF->Radial.Cr.o / Soll_IBF->Radial.Cr.u));
		                   Soll_IBF->Radial.Cr.f = 2 * Soll_IBF->Radial.Cr.g;

                           Soll_IBF->Radial.abnahme_s = -2*Soll_IBF->Radial.Cr.g + ( sqrt( pow(Soll_IBF->Radial.Cr.f,2) - 4*pow(Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i],2)));

		                          //  l_r = sqrt( -1 * abnahme_s * ( o / u));                                     // Gedr�ckte L�nge
		                         //   s_m = Array[os_i] + ( abnahme_s /2);                                        // mittlere Wanddicke
		                         //   c_ri = l_r / s_m;                                                         // momentanes Walzspaltverh�ltnis
                           
		                  
		                	// neue Abnahme bestimmen 
                            //Radial
		                	Soll_IBF->Radial.Soll_Wanddicke = Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i] + Soll_IBF->Radial.abnahme_s;
		                	Soll_IBF->RS_Pos = Soll_IBF->Radial.Soll_Wanddicke; 
		                	

                            //Axial (bei Radialprof = H�henzunahme)
                            Hoehenzunahme(Ist_Inter, Ist_IBF, Soll_IBF);	 
                            Soll_IBF->ASO_Pos = Soll_IBF->Radial.Rohlinghoehe + Soll_IBF->Radial.Breitung.delta_h;
                           
                               
          	  

		                	 		                	
		                	//Aktuelle Wanddicke speichern
		                	Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i] = Ist_IBF.Radial.s_f;         	// Speichern der Wandst�rken im Feld [i]
		                  
		                    //Umstellen von os_i
		                  
		                    if(Soll_IBF->Radial.Cr.os_i == 1)
		                     {
                               Soll_IBF->Radial.Cr.os_i = 0;
                             }
		                    else Soll_IBF->Radial.Cr.os_i = 1;                            
		                  
		                   // if (os_i >=1)  //f�r Array [2]
		                   //	{os_i = -1;}
		                   // os_i= os_i+1;
		                   // Vorschub_v = ((s_f - position_ip1)/t_hU); // Geschwindigkeit f�r 2 Messungen per Zeiteinheit, t_hU Zeit f�r eine 1/2Umdrehung
        		         
                      }//endif


                     // Festhalten des Radialschlittens, wenn dieser die Position erreicht hat...
		                 
		           //  if( Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos + eps))     
                     //   {
                       //   Soll_IBF->RS_Pos = Ist_IBF.RS_Pos;
                        //}
		                
		               	                              		
                  		                     
                  	//-----------------------------------------------------------------------------
                  	//----------    Abbruchkriterium                        ----------------------
                  	//-----------------------------------------------------------------------------
                  		      
                  	 if( Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos_end + eps)) 
                  	  {	
                  		 Soll_IBF->Zeit.t_Halte= Soll_IBF->Radial.Umdrehungen * 10 * (Ist_Inter.da /(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.hw_n)); // n Umdrehungen, 10 * "100" ms Aufrufzyklus = 1000 ms = 1s;  
                         Soll_IBF->RS_Pos = Ist_IBF.RS_Pos;
                  		 Soll_IBF->Profilflag=2; 
  
                  		break;
                      }                  				

                     Soll_IBF->Radial.t_dis_h--;  
		                
		   				

																	
                  break;
*/		

                     
                     
        case 2:   //---------------------------------------------------------------------------------
                  //------- x Umdrehungen abwarten f�r gleichm��iges Profil �ber Umfang -------------
                  //---------------------------------------------------------------------------------
                  
                  /* Geschwindigkeiten  */
                   Soll_IBF->RS_V         = Soll_IBF->Radial.Vorschubgeschw_Dw;   /* Vorschubgeschw_DW erechnet in case 15 */
                   Soll_IBF->ASO_V        = 5.0F; 
                   //Soll_IBF->Soll_ASU_V   = 0.0F;
                   Soll_IBF->AG_V         = 10.0F;
                   Soll_IBF->ZAL_V        = 0.0F;
                   Soll_IBF->ZAR_V        = 0.0F;

                  /* Kr�fte */
                   Kraftsteuerung(Ist_IBF, Soll_IBF);   
  
                  /* Drehzahl */
                  // Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                  // Soll_Inter->kwu_n = KW_Drehzahl_unten(Ist_Inter, &Ist_IBF);
                  
                                 
                    
                  Soll_IBF->Zeit.t_Halte--;
                  Soll_IBF->Radial.t_warte_flag=0; //zur�cksetzen der Bedingung (Diskonti...)
                  
                                    
                  if (Ist_IBF.Zeit.t_Halte <= 0) 
                  {  
                      Soll_IBF->ExitAchse ='a';
                      Soll_IBF->Profilflag = 3;
                      break;   //hier Befehle reinschreiben, wenn ein weiterer Schritt abgearbeitet werden soll.....
                  }
                  break;          
   
       case 3:    // Abschaltmass erreicht Banning
                 
                  /* Funktionsaufruf */
                  IBF_Abschaltung(Soll_Inter, Ist_IBF);
                  break;
      
       case 345:  //Abschaltung MRAW -> Memoryflag= Ist_IBF.Profilflag;
                  // RS und AS auffahren; danach manuell Entladeposition anfahren (Koppers 'e')     
                  switch (Ist_IBF.ExitAchse) 
                  {                         
                    #ifdef MRAW
                     Steuerbyte_Lese.freigabe = 191;	// war 95
                     //Freigabe_MRAW_Senden();
                    #endif
                                 
                        case 'a': 	
                              Soll_IBF->RS_Pos=Ist_IBF.RS_Pos_Start+10.0F; //michl
                              Soll_IBF->RS_V = 5.0F;
                   
                              if (Ist_IBF.RS_Pos >= Soll_IBF->RS_Pos) Soll_IBF->ExitAchse = 'b';
                              break;
 
                        case 'b':
                   
                              Soll_IBF->AG_Pos = Ist_IBF.AG_Pos_Null  + 50; 
                              Soll_IBF->ASO_Pos= Ist_IBF.ASO_Pos_Null + 15; //michl
                              
                              Soll_IBF->ASO_V = 15.0F; 
                       
                              
                              Soll_IBF->AG_V = 8.0F;
                              Soll_IBF->ZAR_V = 0.0F;                   	
                              Soll_IBF->ZAL_V = 0.0F;                   	

                              if (Ist_IBF.AG_Pos >= Soll_IBF->AG_Pos) 
                              {
                                 Soll_IBF->ExitAchse = ' '; 
                                 Soll_IBF->Profilflag++;
                              }
                              
                              if (     (Ist_IBF.RS_Pos  >= Soll_IBF->RS_Pos)
                                    && (Ist_IBF.ASO_Pos >= Soll_IBF->ASO_Pos)
                                    #ifdef MRAW
                                    && (Ist_IBF.ASU_Pos >= Soll_IBF->Soll_ASU_Pos)
                                    #endif
                                 )
                              {
                                 Soll_IBF->ExitAchse = ' '; 
                                 Soll_IBF->Profilflag++;
                                 break;
                              }
                              //----------------------------------------------------------------------------------------------------
                              //------------------- Damit die Variabelwerte, die w�hrend einer vorgehenden Walzung------------------
                              //--------------------nicht im Speicher verbleiben, m�ssen diese zur�ckgesetzt werden-----------------
                              //----------------------------------------------------------------------------------------------------
                                 
                                 Ist_IBF.FR_f = 0; Ist_IBF.FA_f = 0;
                                //	zaehler=0;  uk_ASO=0;
                                // uk1_ASO=0;	diam_f=0;   diam_f_alt=0;     Soll_IBF->Zeit.t_Halte = 0;   Ist_IBF.Radial.t_warte = 0;	
                                 
                              break;                        
                              
                  default: 	break;
                  } // Klammer zu: switch(ExitAchse)                  
                  break;	
                 
   
/*---------------------------------------------------------------------------------*/	
/*--------------------------------------ENDE ENDE ENDE ----------------------------*/		      
/*---------------------------------------------------------------------------------*/
   
}; // Klammer zu: switch (IBF_Allgemein.IBF_Allgemein.Profilflag) 
       
 
//########## Ende Automatiksteuerung ##########


    /* ------------------------------------------------------------------------ */
    /*                                                                          */
    /*  �bergabe der Sollwerte aus der IBF-Struktur an die 'Ist_Inter' Struktur */
    /*                                                                          */
    /* ------------------------------------------------------------------------ */
    
               /* Kraft [N]*/
                  Soll_Inter->rs_kraft  = Soll_IBF->RS_Kraft;
                  Soll_Inter->aso_kraft = Soll_IBF->AS_Kraft;
                  Soll_Inter->ag_kraft  = Soll_IBF->AG_Kraft;
                  //Soll_Inter->asu_kraft;
                  Soll_Inter->zal_kraft = Soll_IBF->ZAR_Kraft;
                  Soll_Inter->zar_kraft = Soll_IBF->ZAL_Kraft;

               /* Flags f�r Kraftsteuerung */
                  Soll_Inter->rs_kraftregler_aktiv      = Ist_IBF.Flag.rs_kraftregler_aktiv;   /* [0-1] */
                  Soll_Inter->aso_kraftregler_aktiv     = Ist_IBF.Flag.as_kraftregler_aktiv;
                   //Soll_Inter->asu_kraftregler_aktiv;   /* keine Kraftmessung des unter Axialschlittens an Banning*/
                  Soll_Inter->ag_kraftregler_aktiv      = Ist_IBF.Flag.ag_kraftregler_aktiv;
                  Soll_Inter->zal_kraftregler_aktiv     = Ist_IBF.Flag.zar_kraftregler_aktiv;
                  Soll_Inter->zar_kraftregler_aktiv     = Ist_IBF.Flag.zal_kraftregler_aktiv;
                
                  Soll_Inter->rs_mode  =  Soll_IBF->Flag.rs_mode;
                  Soll_Inter->aso_mode =  Soll_IBF->Flag.aso_mode;

               /* Geschwindigkeit [mm/s] */
                  Soll_Inter->rs_v     = Soll_IBF->RS_V;         /* �bergebe Gechwindigkeit an Tabelle */
                  Soll_Inter->aso_v    = Soll_IBF->ASO_V;
                  //Soll_Inter->asu_v    = Soll_IBF->Soll_ASU_V;
                  Soll_Inter->ag_v     = Soll_IBF->AG_V;       
                  Soll_Inter->zal_v    = Soll_IBF->ZAL_V;       
                  Soll_Inter->zar_v    = Soll_IBF->ZAR_V;

              /* Positionen [mm]*/
                  if(Soll_IBF->RS_Pos < Soll_IBF->min_RS_Pos)
                    {
                     Soll_Inter->rs_pos  = Ist_Inter.rs_pos; /* Wert in rwth-exch.cpp initialisiert. Routine ini-Datei einlesen */
                    }
                  else Soll_Inter->rs_pos  = Soll_IBF->RS_Pos;

                  if(Soll_IBF->ASO_Pos < Soll_IBF->min_ASO_Pos) /* min_ASO_Pos Wert in rwth-exch.cpp initialisiert Routine ini-Datei einlesen */
                    {
                    Soll_Inter->aso_pos = Ist_Inter.aso_pos; 
                    }
                  else Soll_Inter->aso_pos = Soll_IBF->ASO_Pos;

                  Soll_Inter->ag_pos  = Soll_IBF->AG_Pos;
                  Soll_Inter->zal_pos = Soll_IBF->ZAL_Pos + 1550.0F; /* Wert 15550.0 ergibt sich aus Zylinderaufbau der Zentrierung. N�here Info s.a. technische Zeichnung       */
                  Soll_Inter->zar_pos = Soll_IBF->ZAR_Pos + 1550.0F;

                              
                
         
        
/*------------------------------------------------------------------------------------*/
/*------------- Anfang Kollisionscheck Modellringwalzwerk ----------------------------*/
/*------------------------------------------------------------------------------------*/

#ifdef MRAW
      RS_HW = 1;
      RS_AG = 1;
      AG_RS = 1;
      AS_AS = 1;
      
      if ((RS_HW != 0) && (RS_AG != 0))
      {  
        /* Soll_Inter->rs_pos = Soll_IBF->Soll_RS_Pos + offset_rs;*/
         #ifdef MRAW
            _settextposition(7,1);
            printf("                                     ");
         #endif
      }
      else
      {  if (RS_HW == 0)
         {
            #ifdef MRAW
               _settextposition(7,1);
               printf("    KOLLISIONSGEFAHR RS - HW   %i      ", RS_HW);
            #endif
         }
         else
         {
            #ifdef MRAW
               _settextposition(7,1);
               printf("    KOLLISIONSGEFAHR RS - AG   %i      ", RS_AG);
            #endif
         }
      }
      
      if (AG_RS != 0)
      {  
         Soll_Inter->ag_pos = Soll_IBF->AG_Pos + offset_agr;
         #ifdef MRAW
            _settextposition(7,1);
            printf("                                     ");
         #endif
      }
      else
      {
         #ifdef MRAW
            _settextposition(7,1);
            printf("    KOLLISIONSGEFAHR AG - RS   %i      ", AG_RS);
         #endif
      }
      
      if (AS_AS != 0)
      {  
         Soll_Inter->aso_pos = Soll_IBF->ASO_Pos + offset_aso;
         #ifdef MRAW
            Soll_Inter->asu_pos = Soll_IBF->Soll_ASU_Pos + offset_asu;  //michl rausgenommen
            _settextposition(7,1);
            printf("                                     ");
         #endif
      }
      else
      {  
         #ifdef MRAW
            _settextposition(7,1);
            printf("    KOLLISIONSGEFAHR oberer AS - AS   %i      ", AS_AS);
         #endif
      }
#endif
      
// ------------ Ende Kollisionscheck -----------

    return TRUE;
}



