#include "rpw.hpp"
#include "time.h"



//---------------------------------------------------------------------------
// Methode RPW::RPW
//---------------------------------------------------------------------------
/** Setzt alle Offset Variablen dieser Klasse auf 0. 
  */
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

/**
 * Initiiert die Ist_Inter als Struktur des Types \link Def_Ist_Inter \endlink.
 * Im Anschluss wird die interne Main gestartet.
 * @param[in] iter
 * @param[in] Ein_Puff eine Struktur vom Typ \link Def_Ein_Puff \endlink
 * @param[in] Lokal_Puff eine Struktur vom Typ \link Def_Lokal_Puff \endlink
 * @param[in] Aus_Puff eine Struktur vom Typ \link Def_Aus_Puff \endlink
 * @param[in] Ein_Onli eine Strktur vom Typ \link Def_Ein_Onli \endlink
 * @param[in] Aus_Onli eine Struktur vom Typen \link Def_Aus_Onli \endlink
 * @param[in] *Ist_Inter ein Zeiger auf eine Struktur vom Typen 
 * \link Def_Ist_Inter \endlink
 * @param[in] *Soll_Inter ein Zeiger auf eine Struktur vom Typen 
 * \link Def_Soll_Inter \endlink
 * @param[in] *Soll_IBF ein Zeiger auf eien Struktur vom Typen 
 * \link Def_IBF_Allgemein_SOLL \endlink
 * @param[in] *Ist_IBF ein Zeiger auf eine Struktur vom Typen 
 * \link Def_IBF_Allgemein_IST \endlink
 */
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

/**
 * Deklariert in der \link Def_Ist_Inter \endlink Struktur die Variablen die mit
 * den Positionen des aktuellen Status des Walzwerks,der Geometrien (Ring- und
 * Maschienengeometrie), den aktuellen Drehzahlen der Walzen und Motoren, den
 * Werkzeugen, den gefilterten Kraeften oder Messwerte der IBF-Zusatzachse zutun
 * haben.
 * @param Ein_Onli eine Struktur vom Typ \link Def_Ein_Onli \endlink
 * @param Ein_Puff eine Struktur vom Typ \link Def_Ein_Puff \endlink
 * @param Lokal_Puff eine Struktur vom Typ \link Def_Lokal_Puff \endlink
 * @param Aus_Puff eine Struktur vom Typ \link Def_Aus_Puff \endlink
 * @param *Ist_Inter ein Zeiger auf eien Struktur vom Typ 
 * \link Def_Ist_Inter \endlink
 */
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



/**
 * Schreibt Daten aus einer \link Def_Ist_Inter \endlink Struktur die das aktuelle 
 * Walzwerk beschreiben in eine \link Def_IBF_Allgemein_IST \endlink Struktur. Diese
 * Struktur ist vom IBF und auf dieser wird ueberwiegend gearbeitet. Die Daten
 * beziehen sich auf Geometrie des Ringes Position der Walzen und Filter des
 * Radialschlittens.
 *
 * @param Ist_Inter Struktur vom Typ \link Def_Ist_Inter \endlink aus der die
 * aktuellen Stati des Walzwerks ausgelesen werden.
 * @param *Ist_IBF Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink in die
 * einige Daten aus \link Def_Ist_Inter \endlink geschrieben werden
 * @return Der Rueckgabe wert der Funktion ist unabhaengig vom erfolgreichen
 * durchfuehren einzelner Operationen es wird stets TRUE (1) zuruckgegeben.
 */
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


/**
 * Aktualisiert die Werte in der Struktur \link Def_IBF_Allgemein_IST \endlink
 * mit den Werte aus \link Def_IBF_Allgemein_SOLL \endlink
 */
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
/** Verhalten des Ringwalzwerks in Abhaengigkeit von 
 * \link Def_IBF_Allgemein_IST.Profilflag \endlink .
 * <p>
 * Wenn \link Def_IBF_Allgemein_IST.Profilflag \endlink = -1 ist, werden die
 * Startpositionen  des Ringwalzwerks bestimmt. Es findet noch keine Zustellung
 * statt. Das heisst, das in diesem Fall auch noch nicht gewalzt wird, sondern die
 * Walzung nur vorbereitet wird. Sollte \link Def_IBF_Allgemein_IST.Profilflag \endlink
 * = 3 sein (es soll eine Schuessel gewalzt werden), so wird die Methode 
 * \link ibf_Schuessel::main \endlink aufgerufen.
 * </p>
 * <p>
 * Wenn \link Def_IBF_Allgemein_IST.Profilflag \endlink = 1 ist, befindet sich das
 * Walzwerk
 * in der Profilierphase. In diesem Fall wird \link flexibel_Axial \endlink
 * aufgerufen, sollte es sich um axiales Profilieren handeln
 * (\link IBF_Flag.Axial_Radialwalzen \endlink
 * = 0). Die gleiche Methode wird beim Radial Walzen aufgerufen. Sollte keine der
 * beiden
 * Profilierungen mehr vorgenommen werden, so wird das
 * \link Def_IBF_Allgemein_IST.Profilflag \endlink
 * auf 13 gesetzt, was gleich bedeutend ist mit, es wird abgeschaltet.
 * </p>
 * <p>
 * Wenn \link Def_IBF_Allgemein_IST.Profilflag \endlink = 2 ist, werden
 * Radialschlitten, Axialschlitten oben und Axialgeruest solange vorgefahren, bis
 * die Zeit \link Def_Zeit.t_Halte \endlink abgelaufen ist. Die Kraefte, die
 * waehrend der Zeit wirken werden mit Hilfe von \link Kraftsteuerung \endlink
 * berechnet. Wenn \link Def_Zeit.t_Halte \endlink abgelaufen ist, wird mit Fall
 * '3' fortgefahren.
 * </p>
 * <p>
 * </p>
 * Wenn \link Def_IBF_Allgemein_IST.Profilflag \endlink = 3 ist, ist das
 * Abschaltmass nach 'Banning' erreicht. Das Walzwerk wird wie in
 * \link IBF_Abschaltung \endlink abgeschaltet.
 * <p>
 * Wenn \link Def_IBF_Allgemein_IST.Profilflag \endlink = 9 ist, faehrt das
 * Walzwerk zu den vorher festgelegten Positionen vor. Auch hier wird noch nicht
 * gewalzt, das Walzwerk befindet sich noch in der Vorbereitung. Wenn das Walzwerk
 * komplett vorgefahren ist, so wird der
 * \link Def_IBF_Allgemein_IST.Profilflag \endlink auf 11 gesetzt.
 * </p>
 * <p>
 * Wenn \link Def_IBF_Allgemein_IST.Profilflag \endlink = 11 ist, befindet sich das
 * Walzwerk in der Rundungsphase.Die Walzen arbeiten mit konstanter
 * Geschwindigkeit. Die Kraft der Walzen wird bei jeder Iteration mit Hilfe von
 * \link Kraftsteuerung \endlink neu berechnet. Die Drehzahlen werden mit Hilfe von
 * \link KW_Drehzahl_axial \endlink berechnet. Die
 * \link Def_IBF_Allgemein_SOLL.AG_Pos \endlink wird durch
 * \link AGR_Soll_Pos \endlink berechnet. Wenn die Rundungsphase vorbei ist (
 * \link Def_Zeit.t_Halte \endlink  <= 0 ) wird die naechste Walzphase eingeleitet,
 * in dem \link Def_IBF_Allgemein_SOLL.Profilflag \endlink
 * auf 12 gesetzt wird.
 * </p>
 * <p>
 * Wenn \link Def_IBF_Allgemein_IST.Profilflag \endlink = 12 ist, befindet sich die
 * Walzung in einem Zwischenstadium. An dieser Stelle sind Verzweigungen moeglich.
 * Zunaechst faehrt der Axialschlitten hoch. Es folgt eine Abfrage, ob weitere
 * Profilierungen vorgenommen werden sollen. Sollte dies der Fall sein, so wird
 * \link Def_IBF_Allgemein_SOLL.Profilflag \endlink auf 0 gesetzt. Siehe oben
 * genannter Fall. Wenn keine weiteren Profilierungen mehr vollzogen werden sollen,
 * wird \link Def_IBF_Allgemein_SOLL.Profilflag \endlink auf 13 gesetzt.Siehe
 * naechster Fall.
 * </p>
 * <p>
 * Wenn \link Def_IBF_Allgemein_IST.Profilflag \endlink = 13 ist, befindet sich
 * das  Walzwerk am Ende der Walzung.Es wird nun mit Hilfe der Methode
 * \link IBF_Abschaltung \endlink abgeschlatet, und aufgefahren.
 * </p>
 *@param[in] Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 *@param[in] Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_SOLL \endlink
 *@param[in] *Soll_Inter Zeiger auf eine Struktur vom Typ
 *            \link Def_Soll_Inter \endlink
 *@param[in] *Soll_IBF Zeiger auf eine Struktur vom Typ
 *           \link Def_IBF_Allgemein_SOLL \endlink
 *@bug Fall 0 wurde noch nicht zu den Doxygen Kommentaren hinzugefuegt
 */
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



