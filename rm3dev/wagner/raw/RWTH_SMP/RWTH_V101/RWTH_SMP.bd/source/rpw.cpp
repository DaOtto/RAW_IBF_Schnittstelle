#include "rpw.hpp"


//---------------------------------------------------------------------------
// Methode RWP::RPW
//---------------------------------------------------------------------------
RPW::RPW(void)
{

    hw_ir                = 0.0F; // Getriebeuntersetzung Hauptwalzenmotor
    kw_ia                = 0.0F; // Getriebeuntersetzung Kegelwalzenmotor
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
                  float  IBF_PARA[IBF_PARA_MAX],
                  struct Def_Ist_Inter           *Ist_Inter,
                  struct Def_Soll_Inter          *Soll_Inter,
                  struct Def_IBF_Allgemein_SOLL  *Soll_IBF,
                  struct Def_IBF_Allgemein_IST   *Ist_IBF   )
{
   // Defintion der lokalen Variabeln
   // struct Def_IBF_Allgemein *IBF_Allgemein;
   // Los gehts

   // Initilisieren
 /*
   if (Ein_Puff.walzenstart_flag)
   {
		Soll_Inter->rs_v = 0.0F;	
   }
   else
   {
      if (Ein_Onli.rwg_poti_wert > 0.05F)
      {
	     Soll_Inter->rs_v = 2.0F * Ein_Onli.rwg_poti_wert;
 	   }
      else
      {
        Soll_Inter->rs_v = 0.0F; 
      }

      Soll_Inter->aso_v = 0.0F;
   }
*/	
   // Istwerte aufbereiten
   Istwerte_RAW(  Ein_Puff,
                  Lokal_Puff,
                  Aus_Puff,
                  &*Ist_Inter);

   Soll_Inter->rs_v  = Aus_Onli.ds_dh_sp_hp.s_punkt;
   Soll_Inter->aso_v = Aus_Onli.ds_dh_sp_hp.h_punkt;

   // Hauptprogrammteil des IBF-Tasks
   Main(*Ist_Inter,
        IBF_PARA,
        &*Ist_IBF,
        &*Soll_Inter,
        &*Soll_IBF);

   return TRUE;
}

//---------------------------------------------------------------------------
// Methode RWP::Istwerte_RAW
//---------------------------------------------------------------------------
int RPW::Istwerte_RAW(  struct Def_Ein_Puff    Ein_Puff,
                        struct Def_Lokal_Puff  Lokal_Puff,
                        struct Def_Aus_Puff    Aus_Puff,
                        struct Def_Ist_Inter   *Ist_Inter)
{
  /* Ist_Inter->rs_pos    =    Ein_Puff.form_mess_of.dis_hw_dw 
                           + Ein_Puff.hw_geometrie.r_nenn
                           + Ein_Puff.dw_geometrie.r_nenn; */
   
    Ist_Inter->rs_pos    =    Ein_Puff.form_mess_of.dis_hw_dw;

    Ist_Inter->ag_pos    =   Ein_Puff.form_mess_of.da
                           - Ein_Puff.pos_laser_u_of
                           - Ein_Puff.awu_geometrie.l_fehlende_spitze
                           + Ein_Puff.hw_geometrie.r_nenn;
    Ist_Inter->aso_pos   =   Ein_Puff.form_mess_of.dis_aw;
    Ist_Inter->asu_pos   =   0.0F;
    Ist_Inter->tr_pos    =   Ein_Puff.pos_laser_u_of
                           + Ein_Puff.awu_geometrie.l_fehlende_spitze;
    Ist_Inter->rs_f      =   Ein_Puff.fr_of; 
    Ist_Inter->as_f      =   Ein_Puff.fa_of;	

    Ist_Inter->hw_n      =   Ein_Puff.n_hw_motor_ist / MIN_FAK;

    diam_hw              =   Ein_Puff.hw_geometrie.d_nenn;
    diam_dw              =   Ein_Puff.dw_geometrie.d_nenn; 

    hw_ir                =   Ein_Puff.hw1_motor.getriebe_untersetzung;              /* Getriebeuntersetzung Hauptwalzenmotor */
    kw_ia                =   Ein_Puff.awu_motor.getriebe_untersetzung;              /* Getriebeuntersetzung Kegelwalzenmotor */
    sin_kw_winkel_halbe  =   (float) sin(Ein_Puff.awu_geometrie.winkel_bo * 0.5F);  /* Sinus halber Kegelwalzenwinkel */

    Ist_Inter->da              = Aus_Puff.form_ring.da;      					/* Aeusserer Durchmesser        [mm]    */
	Ist_Inter->da_of           = Ein_Puff.form_mess_of.da;
  	Ist_Inter->di              = Aus_Puff.form_ring.di;      					/* Innerer   Durchmesser        [mm]    */
  	Ist_Inter->di_of           = Ein_Puff.form_mess_of.di;
  	Ist_Inter->dm              = Aus_Puff.form_ring.dm;      					/* Mittlerer Durchmesser        [mm]    */
  	Ist_Inter->dm_of           = Ein_Puff.form_mess_of.dm;    
  	Ist_Inter->fertig_ho_soll  = Aus_Puff.ist_walzform.hm;
  	Ist_Inter->fertig_wd_soll  = Aus_Puff.ist_walzform.sm;
  	Ist_Inter->h0a             = Aus_Puff.h0a;     					/* Ringhoehe axial  einlaufend  [mm]    */  		
  	Ist_Inter->h0r             = Aus_Puff.h0r;     					/* Ringhoehe radial einlaufend  [mm]    */
  	Ist_Inter->h1r             = Aus_Puff.h1r;     					/* Ringhoehe radial auslaufend  [mm]    */
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
    Ist_Inter->Vorform.sm      = Ein_Puff.vorform.sm;          /* Wandstärke Vorform aus Carwin            [mm] */
    Ist_Inter->Vorform.da      = Ein_Puff.vorform.da;          /* Durchmesser Vorform  aus Carwin          [mm] */
    Ist_Inter->Vorform.hm      = Ein_Puff.vorform.hm;          /* Rohlingshöhe Vorform aus Carwin          [mm] */

    Ist_Inter->rs_f            = Aus_Puff.fr_mf;               /* Radiale Kraft gefiltert                [N] */
    Ist_Inter->as_f            = Aus_Puff.fa_mf;               /* Axiale Kraft gefiltert                 [N] */
    // Ist_Inter->ag_f = ? ;                                   /* Axialgerüst                            [N] */        
                  
      
  

    return TRUE;
}


//---------------------------------------------------------------------------
// Methode RWP::MAIN
//---------------------------------------------------------------------------
int RPW::Main( struct Def_Ist_Inter          Ist_Inter,
               float  IBF_PARA[IBF_PARA_MAX],
               struct Def_IBF_Allgemein_IST  *Ist_IBF, 
               struct Def_Soll_Inter         *Soll_Inter,
               struct Def_IBF_Allgemein_SOLL *Soll_IBF)
{

   // Zuweisung Def_IBF_Allgemein_SOLL 

   // Übergeben der Parameter aus Soll_IBF/Ist_IBF Struktur
      
   Ist_IBF->Profilflag = Soll_IBF->Profilflag;
   Ist_IBF->InitAchse  = Soll_IBF->InitAchse;
   Ist_IBF->ExitAchse  = Soll_IBF->ExitAchse;
  
   Ist_IBF->RS_Pos_Null  = Soll_IBF->RS_Pos_Null; // bla_Null -> Initialisierung nach manueller Anfahrt / vor Profilieren 
   Ist_IBF->ASO_Pos_Null = Soll_IBF->ASO_Pos_Null;
   Ist_IBF->AG_Pos_Null  = Soll_IBF->AG_Pos_Null;           

   Ist_IBF->RS_Pos_Start = Soll_IBF->RS_Pos_Start; 	// Positionen in 'Walzen' vor Profilieren 
   Ist_IBF->AG_Pos_Start = Soll_IBF->AG_Pos_Start; 	
   Ist_IBF->ASO_Pos_Start= Soll_IBF->ASO_Pos_Start; 	       
   
   Ist_IBF->Vorring.Wandstaerke_Null    = Ist_Inter.Vorform.sm;  /* Übergabe der Rohlingswanddicke an IBF-Struktur */  
   Ist_IBF->Werkzeugdurchmesser = diam_dw;               /* Übergabe der Rohlingshöhe an IBF-Struktur | diam_dw in class rpw definiert */
   Ist_IBF->Vorring.D_Null      = Ist_Inter.Vorform.da;  /* Übergabe der Rohlingswanddicke an IBF-Struktur */ 
   Ist_IBF->Vorring.Start_Ringhoehe     = Ist_Inter.Vorform.hm;  /* Übergabe der Rohlingshöhe an IBF-Struktur */   
   
   Ist_IBF->FR                  = Ist_Inter.rs_f;        /* Übergabe der aktuellen RS-Kraft an IBF-Struktur */ 
   Ist_IBF->FA                  = Ist_Inter.as_f;        /* Übergabe der aktuellen AS-Kraft an IBF-Struktur */           

#if(MRAW)
   Ist_IBF->FA_f       = 0.1F;
   Ist_IBF->FR_f       = 0.1F;  // im Interfac gefilterte Kraft
   Ist_IBF->s_f        = 0.1F;
   
#else 
   Ist_IBF->FA_f       = 1.0F; //Aus_Puff.fa_mf; 
   Ist_IBF->FR_f       = 1.0F; //Aus_Puff.fr_mf;
   Ist_IBF->s_f        = 1.0F; //Aus_Puff.s1r;

#endif
//---------------------------------------------------------------------------
// Beginn AXPRO.H
//---------------------------------------------------------------------------
  
   
   //-----------------------------------------------------------------------------------------
   //-----------------------Definition für Kraftregler/Filterwerte u.ä.-----------------------
   //-----------------------------------------------------------------------------------------
   
   
   float s_f_alt = 0.0F; // 	gefilterte Wanddicke zum Zeitpunkt t-1 für Positionierung der oberen Kegelwalze
              
   
   
   float KP = 0.00191F;        //Radialkraft Prop
   
   	
   float uk_ASO = 0;   			//Hilfsvariable für Axialkraftregelung   MIC 040416
   float uk1_ASO = 0;          //Hilfsvariable für Axialkraftregelung  MIC 040416
   
   
   // Filter für Ringdurchmesser     
   float	 diam_f = 0;			// gefilterter Ringdurchmesser 
   float	 diam_f_alt = 0;	// letzter Wert Ringdurchmesser für Filter 
   
   
   
   float RS_Koll = 1.0F;      // Sicherheitsabstand RS-HW    (1 mm)
   float AG_Koll =  5.0F;     // Sicherheitsabstand AS-RS     (5 mm)
                                                                   
   float eps = 0.1F;          // Positioniergenauigkeit michl:-> war 0.1F
   
   float t_Halte = 50;        // Haltezeit in Vielfachen von 100ms               
   float t_warte = 0;         // Wartezeit in Vielfaches von 100ms   
   float t_warte_flag = 0;    // WarteFlag, damit t_warte bei der ersten Initialisierung gesetzt wird
                      
   //----------------------------------------------------------------------------------------------
   //--------------------------Variablen aus IBFPARA3.c--------------------------------------------
   //----------------------------------------------------------------------------------------------
   float Axialkraft;
   float Radialkraft;
   //-----------------------------------------------------------------------------------------------
   //------------------------------sonstige Hilfsvariablen------------------------------------------
   //----------------------------------------------------------------------------------------------- 
      
       
    
   //------------------------------------------------------------------------------------------------ 
   float zaehler=0.01F;   
   float n = 0.0f;    
   float s_ist =0.0f;         
   
   //-----------------------------------------------------------------------------------------------
   //------------------------- Variablen für die diskontinuierliche Funktion -----------------------
   //-----------------------------------------------------------------------------------------------
   
   
   float t_dis_h = 0; // Haltezeit für 1.5 Umdrehungen, bei denen der Dorn stehen bleiben soll (Diskontinuierliche Abwalzung)
   
   float delta_h = 0.0F;

//---------------------------------------------------------------------------
// Ende AXPRO.H
//---------------------------------------------------------------------------

   // Ring: Höhe und Wanddicke; Außendurchmesser 'diam' extern von interfac
   float h_a1;             // Ringhöhe nach Axialwalzspalt bzw. Entfernung Kr-K
   float s_r1;             // Wanddicke nach Radialwalzspalt bzw. Entfernung DW-HW
   float diam;             // Ringdurchmesser

   float Ta  = 0.1F;       // Filter 
   float Kpf = 1;
   float T1f = 1;     

   
   float Del_ASO_Pos;      // KORREKTUR ASO für axiale Walzkraftregelung MIC 040406

   float f_H;              // Drehfrequenz der HW in 1/s (_nicht_ 1/min!)
   
   float t_U;              // Zeit für eine Ringumdrehung   

   int RS_HW = 1;    // Kollisionsgefahr RS-HW
   int RS_AG = 1;    // Kollisionsgefahr RS_AG
   int AG_RS = 1;    // Kollisionsgefahr AG-RS
   int AS_AS = 1;    // Kollisionsgefahr oKrw-uKw 

   // Pi 
   #ifndef  PI
   #define  PI 3.14159265
   #endif 

   /* Daten von Oberflaeche an Task */                      
   struct Def_Steuerbyte Steuerbyte_Lese; // far Steuerbyte_Lese; 

//++++++++++ Zyklische Initialisierung und Aktualisierung der Messgrößen ++++++++++

   // schritt_nr = Soll_Inter->schritt_nr;	// lese aktuellen Programmstatus (Koppers) 
   
   // aktuelle Positionen im Walzwerk auslesen und berechnen:
   Ist_IBF->RS_Pos   = Ist_Inter.rs_pos;
//   Ist_IBF->RS_Pos   = Ist_Inter.rs_pos  - offset_rs;      // aktuelle Dornposition
   Ist_IBF->AG_Pos   = Ist_Inter.ag_pos  - offset_agr;     // aktuelle Axialgerüstposition
   Ist_IBF->ASO_Pos  = Ist_Inter.aso_pos - offset_aso;     // aktuelle Axialschlittenposition oben
#ifdef MRAW
   Ist_IBF->ASU_Pos  = Ist_Inter.asu_pos - offset_asu;     // aktuelle Axialschlittenposition unten
#endif
   Ist_IBF->TR_Pos   = Ist_Inter.tr_pos  - offset_tr;      // aktuelle Tastrollenposition
   Ist_IBF->FR       = Ist_Inter.rs_f;                     // aktuelle rad. Walzkraft     
   Ist_IBF->FA       = Ist_Inter.as_f;                     // aktuelle axiale Walzkraft    
   
   // Sollgeschwindigkeiten im Walzwerk (alle 0 wg. aut init startpos):
   Soll_IBF->RS_V = Soll_IBF->ASO_V = Soll_IBF->AG_V = 1.0F;      //  !!!
     
   
   // aktuelle Ringgeometrie
   h_a1 = Ist_IBF->ASO_Pos;                               // Ringhöhe
   s_r1 = Ist_IBF->RS_Pos - ((diam_hw + diam_dw) / 2.0F); // Wanddicke; Problem wegen Breitung!?!?
   diam = Ist_IBF->TR_Pos + Ist_IBF->AG_Pos - (diam_hw / 2.0F);   // momentaner Ringdurchmesser
                         
   // Filter für Ringdurchmesser, Bö, 020528
   diam_f     = (Kpf * diam + ((T1f / Ta) * diam_f_alt)) / ((T1f / Ta) + 1);
   diam_f_alt = diam_f;         
             
   // Sonstige Größen, Hilfsgrößen etc.
   f_H = Ist_Inter.hw_n/(hw_ir*60.0F);
   
   t_U = diam_f/(diam_hw*f_H); // Zeit für eine Ringumdrehung gemessen in s

//---------------------------------------------------------------------------------------------------
//------------------ Übergabe der Zahlenwerte aus IBFPARA-Fenster -----------------------------------
//---------------------------------------------------------------------------------------------------
  
   Axialkraft                    = 0.0F;   // Keine Vorgabe der Sollkraft  = zahl10;   //*!!!* 
   Radialkraft                   = 0.0F;   // Keine Vorgabe der Sollkraft  = zahl11;   //*!!!* 
   Ist_IBF->Del_Kr_AGR           = 1.0F;
   Ist_IBF->Pos_auf_Mantel       = 1.0F;   // 	
   
//----------------------------------------------------------------------------------------------------	


//++++++++++ Ende Initialisierung ++++++++++

//########## Hand- bzw. Automatiksteuerung ausgehend von Koppers Position bei Walzenstart ##########

   // Geschwindigkeiten sind in axpro.h vorbelegt
   // Startposition für jeweilige Ringgeometrie in axpro.h eintragen?

   if (! Ist_IBF->AUTO)		// AUTO = 0 heißt manuelle Steuerung
   {
#ifdef MRAW

      if (Ist_IBF->StartPos == 1)
      {
         // Bei manuell braucht keine Startposition eingenommen werden !?!
         // Sollposition auf Istposition zu Beginn:
         Soll_IBF->RS_Pos  = Ist_IBF->RS_Pos;
         Soll_IBF->ASO_Pos = Ist_IBF->ASO_Pos;
         Soll_IBF->AG_Pos  = Ist_IBF->AG_Pos;
         
         // Sollgeschwindigkeiten im Walzwerk:
         Soll_IBF->RS_V = 100000.0F;
         Soll_IBF->ASO_V = 1.0F;
         Soll_IBF->AG_V = 1.0F;
         
         
         Ist_IBF->StartPos = 0;
      };                                                           
      
      _settextposition(6,1);
      printf("Manuelle Steuerung: Beenden mit klein 'l': ");  
      printf("TEST fuer Pause die Taste 'p' druecken");

      if (kbhit()) Ist_IBF->ManAuswahl = getch();

      switch (Ist_IBF->ManAuswahl)
      {

         case 't': Soll_IBF->RS_Pos = Soll_IBF->RS_Pos - 0.2F;	break;	// Radialschlitten
         //case 'w': Soll_RS_Pos = Soll_RS_Pos - 0.1F;	break;
         case 'z': Soll_IBF->RS_Pos = Ist_IBF->RS_Pos; break;
         //case 'r': Soll_RS_Pos = Soll_RS_Pos + 0.1F;	break;
         case 'u': Soll_IBF->RS_Pos = Soll_IBF->RS_Pos + 0.2F; 	break;
         
         case 'd': Soll_IBF->AG_Pos = Soll_IBF->AG_Pos - 0.2F;	break;	//	Axialgerüst
         //case 's': Soll_AG_Pos = Soll_AG_Pos - 0.1F;	break;
         case 'f': Soll_IBF->AG_Pos = Ist_IBF->AG_Pos; break;
         //case 'f': Soll_AG_Pos = Soll_AG_Pos + 0.1F;	break;
         case 'g': Soll_IBF->AG_Pos = Soll_IBF->AG_Pos + 0.2F;	break;
         
         case 'y': Soll_IBF->ASO_Pos = Soll_IBF->ASO_Pos - 0.2F;	break;	//	Axialschlitten
         //case 'x': Soll_AS_Pos = Soll_AS_Pos - 0.1F;	break;
         case 'x': Soll_IBF->ASO_Pos = Ist_IBF->ASO_Pos; break;
         //case 'v': Soll_AS_Pos = Soll_AS_Pos + 0.1F;	break;
         case 'c': Soll_IBF->ASO_Pos = Soll_IBF->ASO_Pos + 0.2F;	break;
         
         default: break;
       }  // Klammer zu: switch (ManAuswahl) 
#endif         
   } // Klammer zu: if !AUTO then

   else  // von if !AUTO
   {     // automatische Steuerung:

         // Da Messwerte von Anlage und Mess-Schieber differieren (...), vor Beginn 
         // des Profilierens Aussenkontur (radial/axial) des Ringes von Hand anfahren ??
         // -> von Hand angefahrene Positionen beschreiben den Ausgangszustand ??

      switch (Ist_IBF->Profilflag)      // IBF_Allgemein.IBF_Allgemein.Profilflag in axpro.h definiert, bei Step 6 in interfac auf -1 gesetzt! 
      {
      
      case -1:    // --------------------------------------------------
                  //----- Startpositionen lesen, Sollwertvorgabe ------
                  //---------------------------------------------------						
                  //   Memoryflag=IBF_Allgemein.IBF_Allgemein.Profilflag;   //für Pausenfunktion

                  /* Geschwindigkeiten  */
                  Soll_IBF->RS_V  = 0.0F;
                  Soll_IBF->ASO_V = 0.0F; 
                  Soll_IBF->Soll_ASU_V = 0.0F;
                  Soll_IBF->AG_V  = 0.0F;
                  Soll_IBF->Soll_ZAL_V = 0.0F;
                  Soll_IBF->Soll_ZAR_V = 0.0F;

                  /* Kräfte */
                  Soll_IBF->RS_Kraft = Ist_IBF->Flag.rs_kraftregler_aktiv ? Ist_IBF->RS_Kraft_Vorgabe : 100000.0F ; 
                  Soll_IBF->AS_Kraft = Ist_IBF->Flag.as_kraftregler_aktiv ? Ist_IBF->AS_Kraft_Vorgabe :  80000.0F ; 
                  Soll_IBF->AG_Kraft = Ist_IBF->Flag.ag_kraftregler_aktiv ? Ist_IBF->AG_Kraft_Vorgabe :  10000.0F ; 
                  //Soll_IBF->ZAR_Kraft = Ist_IBF.Flag.zal_kraftregler_aktiv ? Ist_IBF->ZAL_Kraft_Vorgabe :  10000.0F ; 
                  //Soll_IBF->ZAL_Kraft = Ist_IBF.Flag.zar_kraftregler_aktiv ? Ist_IBF->ZAR_Kraft_Vorgabe :  10000.0F ; 
              
                
                  /* Drehzahl */
                  Soll_Inter->kwo_n    = kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);
                  Soll_Inter->kwu_n    = kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);               			
                 
                  /* Position */
                  Soll_IBF->RS_Pos_Start = Ist_IBF->RS_Pos;       // wird in case '3' -> hier Auffahren benötigt
                  
                  Soll_IBF->AG_Pos  = Soll_IBF->AG_Pos_Start = Ist_IBF->AG_Pos; // AG_Pos == auslesen der Werte aus PA-Karte inkl. Offset						
                  
                  
                  //---------------------------------------------------------------------------------
                  //------------Vorgabe für Startposition des Radialschlitten------------------------
                  //---------------------------------------------------------------------------------
                  
                  
                  //Soll_IBF->RS_Pos_Null = (diam_hw + Ist_IBF->Werkzeugdurchmesser)/2 + Ist_IBF->Wandstaerke_Null;  // Nullpunkt des Radialschlittens als Abstand zwischen Hauptwalzedurchmesser, Wandstärke und Dornwalzendurchmesser 
                  Soll_IBF->RS_Pos_Null = Ist_IBF->Vorring.Wandstaerke_Null;          /* Nullpkt. Radialschlitten entsprechend vorgegeber Wandstärke   [mm] */

                  Soll_IBF->RS_Pos = Soll_IBF->RS_Pos_Null; // definiert für RS_Pos in case 'a'  
                  
                  //---------------------------------------------------------------------------------
                  //------------Vorgabe für Startposition der Axialschlitten ------------------------
                  //---------------------------------------------------------------------------------
                  
                  Soll_IBF->AG_Pos_Null = Ist_IBF->AG_Pos; 
                  
                  						  
                  //--------------------------------------------------------------------------------
                  //------------Vorgaben für oberen Axialschlitten----------------------------------
                  //--------------------------------------------------------------------------------
                  
                  
                  Soll_IBF->ASO_Pos_Null = Ist_IBF->Vorring.Start_Ringhoehe + 15.0F; 	/* Vorgabe der Ringhöhe, die in CARWIN vorgegeben wird */
                  Soll_IBF->ASO_Pos_Start = Soll_IBF->ASO_Pos_Null;						
                  

                  #if (FALSE)
                  _settextposition(28,1);
                  printf("case -1");
                  #endif   
                  t_Halte= 50; //t_Halte = 10*2*diam_f/(diam_hw*f_H); // Haltezeit entspricht 1 Ringumdrehung, nötig als Kriterium bei Kraftanfahrposition 
                  Soll_IBF->Profilflag = 0;
               
                  break; //case -1
   
   
   case 0:     //----------------------------------------------------------------
               //----------------Routine für Startposition-----------------------
               //----------------------------------------------------------------
               //Memoryflag=IBF_Allgemein.IBF_Allgemein.Profilflag;						//für Pausefunktion
          
               switch (Ist_IBF->InitAchse) 
                  {
                  
                    // Programmexample for IFM 2006
                    //Spezieller Programmcode zur Verifikation einer Dornbewegung
                    // Ausgangswandicke entspricht der Carwinwanddicke, Diese soll um 100 mm reduziert werden mit v=2.0 mm/s und anschließend wieder zurücke auf Ausgangswanddicke                

                    //!!!ACHTUNG!!! in Datei rwth_task.cpp muss die Initialisierung wieder geändert werden, wenn richtig gewalzt werden soll

                case 'v':
                             Soll_IBF->RS_V = 2.0F;
                             Soll_IBF->AG_V  = 0.0F;
                             Soll_IBF->ASO_V = 2.0F; 
                             Soll_IBF->Soll_ASU_V = 0.0F;
                                
                             
                                                       
                             //Überprüfen, ob Dornposition erreicht ist Soll_IBF->RS_Pos_Null
                            if(Ist_IBF->RS_Pos <= Soll_IBF->RS_Pos + 1.0F) // Ab hier wird Radialschlitten positionieren
                               {
                                  Soll_IBF->RS_Pos = Ist_IBF->RS_Pos - 100.0f;                                 
                                  Soll_IBF->ASO_Pos = Soll_IBF->ASO_Pos_Null - 40.0F;                                  
                                  Soll_IBF->InitAchse = 'w';
                                  break;
                               }
                            break;

      
                  case 'w': 
                             Soll_IBF->RS_V         = 0.95F;
                             Soll_IBF->AG_V         = 0.0F;
                             Soll_IBF->ASO_V        = 0.75F; 
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                                
                             // test: Werte befinden sich jetz in den if-Anweisungen Soll_Inter->rs_v = Soll_RS_V;        
                           
                                                   
                             Soll_Inter->kwo_n = 0.5F*kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);
                             Soll_Inter->kwu_n = 0.5F*kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);               			
                            
                             if(Ist_IBF->RS_Pos <= Soll_IBF->RS_Pos) // Ab hier wird Radialschlitten positionieren
                               {
                                  Soll_IBF->RS_Pos = Soll_IBF->RS_Pos_Null;
                                 //Soll_IBF->Soll_RS_V = 0.5F;
                                 //     Soll_IBF->InitAchse = 'b1';
                                  break;
                               }
                                                    
  

                             break;



                    case 'a':  /* Positionieren des Radialschlittens */	
                              
                             if(FALSE)
                             {
                             #ifdef MRAW
                                 _settextposition(10,1); printf("MAPW: RS_Pos %8.1f  Soll_RS_Pos %8.1f RS_Pos_Null%8.1f, gefilterter %8.1f", Ist_IBF->RS_Pos, Soll_IBF->RS_Pos, Ist_IBF->RS_Pos_Null, diam_f);										
                                 _settextposition(13,1); printf("Dorn%8.1f, Hauptwalze%8.1f, t_Halte%8.1f",diam_dw, diam_hw, t_Halte);
                             #endif
                             }
             
                            
                            /* Geschwindigkeiten  */
                             //Soll_IBF->RS_V       = s. Klammer
                             Soll_IBF->ASO_V        = 5.0F; 
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 0.0F;
                             Soll_IBF->Soll_ZAL_V   = 0.0F;
                             Soll_IBF->Soll_ZAR_V   = 0.0F;

                             /* Kräfte */
                             //Soll_IBF->RS_Kraft = Ist_IBF->Flag.rs_kraftregler_aktiv ? Ist_IBF->RS_Kraft_Vorgabe : 100000.0F ; 
                             Soll_IBF->AS_Kraft = Ist_IBF->Flag.as_kraftregler_aktiv ? Ist_IBF->AS_Kraft_Vorgabe :  80000.0F ; 
                             Soll_IBF->AG_Kraft = Ist_IBF->Flag.ag_kraftregler_aktiv ? Ist_IBF->AG_Kraft_Vorgabe :  10000.0F ; 
                             //Soll_IBF->ZAR_Kraft = Ist_IBF.Flag.zal_kraftregler_aktiv ? Ist_IBF->ZAL_Kraft_Vorgabe :  10000.0F ; 
                             //Soll_IBF->ZAL_Kraft = Ist_IBF.Flag.zar_kraftregler_aktiv ? Ist_IBF->ZAR_Kraft_Vorgabe :  10000.0F ;
                                
                             /* Drehzahl */
                             Soll_Inter->kwo_n = 0.5F*kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);
                             Soll_Inter->kwu_n = 0.5F*kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);               			
                          
                              
                             //-------------------------------------------------------------------------
                             //---------Anfahrroutine Dorn per Kraftregelung---------------------------- 
                             //-------------------------------------------------------------------------
                            
                       if(Ist_IBF->Flag.rs_kraftanfahren_aktiv != 0) //Radialkraft!= 0.0F)	//aus IBF-Para(Radv01) vorgegeben               	  
                        {  	
                                /* Vorgaben: Kraft*/

                                Ist_IBF->Flag.rs_kraftregler_aktiv = Ist_IBF->Flag.rs_kraftanfahren_aktiv; /* Schalter: Walzen mit Kraftsteuerung 'AN' */
                                Soll_IBF->RS_Kraft = Ist_IBF->Flag.rs_kraftregler_aktiv ? Ist_IBF->RS_Kraft_Anfahren : 100000.0F ; 
                                
                                /* Vorgabe: Geschwindigkeit*/
                                Soll_IBF->RS_V  = 7.0F;                    /* Dorn, Radialschlitten */
                                                       
                                /* Vorgabe: Position */
                                //Soll_IBF->RS_Pos = aus case -1 
                                Soll_IBF->ASO_Pos = Ist_IBF->Vorring.Start_Ringhoehe + 1.5F; //da Ring gerne klettert, wird bereits hier ASO zugestellt
                             									
                                
                              //---------------------------------------------------------------------------------
                              //   Routine um Radialschlitten auf Kraft anzufahren      
                              //---------------------------------------------------------------------------------
                        
                                if ((Ist_IBF->FR) == (Ist_IBF->RS_Kraft_Vorgabe))
                                {
                                   Soll_IBF->RS_Pos = Ist_IBF->RS_Pos;
                                   Soll_IBF->InitAchse = 'b';
                                   zaehler=0.5F;
                                   t_Halte=100.0F;   //Zaehler für Kraftanfahrt des Axialschlittens
                                }

       

                        #ifdef MRAW
                               
                               if (Ist_IBF->RS_Pos <= (Ist_IBF->RS_Pos_Null + eps) && t_Halte >= 30)
                                { 
                                   Soll_IBF->RS_Pos = Ist_IBF->RS_Pos_Null - n;
                                   n= n + 0.01F;
                                }

                               if ((Ist_IBF->FR_f >= Radialkraft) && (Ist_IBF->RS_Pos <= Ist_IBF->RS_Pos_Null)) 
                               { 
                                     t_Halte--;
                                     if (t_Halte == 0)
                                     {
                                       Soll_IBF->RS_Pos = Ist_IBF->RS_Pos; // erreicht
                                       Soll_IBF->RS_V= 2.0F;
                         
                                       Soll_IBF->InitAchse = 'b';
                                       zaehler=0.5F;
                                       t_Halte=100.0F;   //zaehler für Kraftanfahrt des Axialschlittens
                                     } 
                                     else break;
                               } // end if(FR_f >=...)
                        #endif       
                               
                            else   break;   	
                                
                          }//end if(Radialkraft != NULL)
                                      
                                         
                         if(Ist_IBF->Flag.rs_kraftanfahren_aktiv == 0)	
                           { 		
                            
                            /*Vorgabe: Kraft*/    
                            Soll_IBF->RS_Kraft = Ist_IBF->Flag.rs_kraftregler_aktiv ? Ist_IBF->RS_Kraft_Vorgabe : 100000.0F ;        
                            Soll_IBF->RS_V  = 8.0F;            // Dorn, Radialschlitten
                                              
                                  Soll_IBF->RS_Pos = Soll_IBF->RS_Pos_Null;
                                  Soll_IBF->AG_Pos = Ist_IBF->Vorring.Start_Ringhoehe + 1.5F; //da Ring gerne klettert, wird bereits hier ASO zugestellt..
 
                               if(Ist_IBF->RS_Pos <= Soll_IBF->RS_Pos) // Ab hier wird Radialschlitten positionieren
                               {
                                  Soll_IBF->InitAchse = 'b';
                                  zaehler = 0.5F;                //zaehler für Kraftsteuerung des Axialschlitten
                               }

                           break;   
                          }// end if(Radial== NULL)  

 
                                    
                         
                      
                        break; // zu case 'a'

    
                  case 'b':   /*Positionsvorgabe:  Axialgerüst*/               				
                              
                             /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 0.0F;
                             Soll_IBF->ASO_V        = 5.0F; 
                             //Soll_IBF->Soll_ASU_V   = 0.0F;
                             //Soll_IBF->AG_V         = 10.0F;
                             //Soll_IBF->Soll_ZAL_V   = 0.0F;
                             //Soll_IBF->Soll_ZAR_V   = 0.0F;

                             /* Kräfte */
                             //Soll_IBF->RS_Kraft = Ist_IBF->Flag.rs_kraftregler_aktiv ? Ist_IBF->RS_Kraft_Vorgabe : 100000.0F ; 
                             Soll_IBF->AS_Kraft = Ist_IBF->Flag.as_kraftregler_aktiv ? Ist_IBF->AS_Kraft_Vorgabe :  80000.0F ; 
                             Soll_IBF->AG_Kraft = Ist_IBF->Flag.ag_kraftregler_aktiv ? Ist_IBF->AG_Kraft_Vorgabe :  10000.0F ; 
                             //Soll_IBF->ZAR_Kraft = Ist_IBF.Flag.zal_kraftregler_aktiv ? Ist_IBF->ZAL_Kraft_Vorgabe :  10000.0F ; 
                             //Soll_IBF->ZAL_Kraft = Ist_IBF.Flag.zar_kraftregler_aktiv ? Ist_IBF->ZAR_Kraft_Vorgabe :  10000.0F ;
                                
                             /* Drehzahl */
                             Soll_Inter->kwo_n = 0.5F*kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);
                             Soll_Inter->kwu_n = 0.5F*kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);               			
                          
                              /*Position*/                  
                              Soll_IBF->AG_Pos = Ist_IBF->Vorring.D_Null + diam_hw/2 - Ist_IBF->Pos_auf_Mantel - Ist_IBF->Del_Kr_AGR ;     // 10 steht für die Variable Pos_auf_Mantel
                              
                              
                              /*Zähler - Merker*/
                              n=0.1f;
                              Soll_IBF->InitAchse ='c';
                              
                              break; // zu case 'b'

                  case 'c':   /*Position Axialgerüst*/
                             
                              /* Geschwindigkeiten  */
                              Soll_IBF->RS_V         = 0.0F;
                              Soll_IBF->ASO_V        = 5.0F; 
                              //Soll_IBF->Soll_ASU_V   = 0.0F;
                              //Soll_IBF->AG_V         = 10.0F;
                              //Soll_IBF->Soll_ZAL_V   = 0.0F;
                              //Soll_IBF->Soll_ZAR_V   = 0.0F;

                              /* Kräfte */
                              //Soll_IBF->RS_Kraft = Ist_IBF->Flag.rs_kraftregler_aktiv ? Ist_IBF->RS_Kraft_Vorgabe : 100000.0F ; 
                              Soll_IBF->AS_Kraft = Ist_IBF->Flag.as_kraftregler_aktiv ? Ist_IBF->AS_Kraft_Vorgabe :  80000.0F ; 
                              Soll_IBF->AG_Kraft = Ist_IBF->Flag.ag_kraftregler_aktiv ? Ist_IBF->AG_Kraft_Vorgabe :  10000.0F ; 
                              //Soll_IBF->ZAR_Kraft = Ist_IBF.Flag.zal_kraftregler_aktiv ? Ist_IBF->ZAL_Kraft_Vorgabe :  10000.0F ; 
                              //Soll_IBF->ZAL_Kraft = Ist_IBF.Flag.zar_kraftregler_aktiv ? Ist_IBF->ZAR_Kraft_Vorgabe :  10000.0F ;
                                
                              /* Drehzahl */
                              Soll_Inter->kwo_n = 0.5F*kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);
                              Soll_Inter->kwu_n = 0.5F*kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);               			
                          
                              /*Position*/  
  
                              /*Zähler - Merker*/
                              t_Halte=500; // 200 ms = 2 sec abwarten
                              
                              #ifdef MRAW
                              if (Soll_IBF->AG_Pos < (Ist_IBF->AG_Pos_Start))
                              {
                                 if (Ist_IBF->AG_Pos <= (Soll_IBF->AG_Pos + eps)) 
                                 {
                                    Soll_IBF->InitAchse = 'd';
                                    break;
                                 }
                                 else 
                                 {
                                    #ifdef MRAW
                                       _settextposition(9,1);
                                       printf(" AG_Pos mit PLUS eps ");
                                    #endif
                                 }//end if
                              }//end if
                              else                                               
                              {
                                 if (Ist_IBF->AG_Pos >= (Soll_IBF->AG_Pos - eps)) 
                                 {
                                    Soll_IBF->InitAchse = 'd';
                                    break;
                                 }
                                 else 
                                 {
                                    #ifdef MRAW   
                                       _settextposition(9,1);
                                       printf(" AG_Pos mit MINUS eps");
                                    #endif
                                 }
                              }//end else
                              #endif
                              
                              Soll_IBF->InitAchse = 'd'; // AG wird noch nicht positioniert, deshalb direkt weiterleiten an nächste case-Anweisung                               break; // zu case 'c'
                  
                  case 'd':   /*Position Axialschlitten*/
                              
                              /* Geschwindigkeiten  */
                              Soll_IBF->RS_V         = 0.0F;
                              Soll_IBF->ASO_V        = 5.0F; 
                              //Soll_IBF->Soll_ASU_V   = 0.0F;
                              //Soll_IBF->AG_V         = 10.0F;
                              //Soll_IBF->Soll_ZAL_V   = 0.0F;
                              //Soll_IBF->Soll_ZAR_V   = 0.0F;

                              /* Kräfte */
                              //Soll_IBF->RS_Kraft = Ist_IBF->Flag.rs_kraftregler_aktiv ? Ist_IBF->RS_Kraft_Vorgabe : 100000.0F ; 
                              Soll_IBF->AS_Kraft = Ist_IBF->Flag.as_kraftregler_aktiv ? Ist_IBF->AS_Kraft_Vorgabe :  80000.0F ; 
                              Soll_IBF->AG_Kraft = Ist_IBF->Flag.ag_kraftregler_aktiv ? Ist_IBF->AG_Kraft_Vorgabe :  10000.0F ; 
                              //Soll_IBF->ZAR_Kraft = Ist_IBF.Flag.zal_kraftregler_aktiv ? Ist_IBF->ZAL_Kraft_Vorgabe :  10000.0F ; 
                              //Soll_IBF->ZAL_Kraft = Ist_IBF.Flag.zar_kraftregler_aktiv ? Ist_IBF->ZAR_Kraft_Vorgabe :  10000.0F ;
                                
                              /* Drehzahl */
                              Soll_Inter->kwo_n = 0.5F*kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);
                              Soll_Inter->kwu_n = 0.5F*kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);               			
                          
                              /*Position*/  
                              Soll_IBF->Soll_ASU_Pos = 0.0F; 

                              /*Zähler - Merker*/
                              Ist_IBF->Afpos_dw = Ist_IBF->RS_Pos;     // Variable in der aktuelle Dornposition definiert ist nachdem Dorn positioniert worden ist

                             
                              //--------------------------------------------------------------------------------------
                              //----------------Anfahren des Axialschlittens auf Kraft--------------------------------
                              //-------------------------------------------------------------------------------------- 
                              
                              if(Ist_IBF->Flag.as_kraftanfahren_aktiv != 0)  //wird nur durchlaufen, wenn Kraft angegeben
                              {
                                
                                /* Vorgaben: Kraft*/

                                Ist_IBF->Flag.as_kraftregler_aktiv = Ist_IBF->Flag.as_kraftanfahren_aktiv; /* Schalter: Walzen mit Kraftsteuerung 'AN' */
                                Soll_IBF->AS_Kraft = Ist_IBF->Flag.as_kraftregler_aktiv ? Ist_IBF->AS_Kraft_Anfahren : 100000.0F ; 
                                
                                /* Vorgabe: Geschwindigkeit*/
                                
                                /* Vorgabe: Position */
                                //Soll_IBF->RS_Pos = aus case -1 
                                Soll_IBF->ASO_Pos = Ist_IBF->Vorring.Start_Ringhoehe - 1.5F; //da Ring gerne klettert, wird bereits hier ASO zugestellt
                             									
                                
                              //---------------------------------------------------------------------------------
                              //   Routine um Radialschlitten auf Kraft anzufahren      
                              //---------------------------------------------------------------------------------
                        
                                if ((Ist_IBF->FR) == (Ist_IBF->RS_Kraft_Vorgabe))
                                {
                                   Soll_IBF->RS_Pos = Ist_IBF->RS_Pos;
                                   Soll_IBF->InitAchse = 'b';
                                   zaehler=0.5F;
                                   t_Halte=100.0F;   //Zaehler für Kraftanfahrt des Axialschlittens
                                }
                              
                              
                                #ifdef MRAW
                                    _settextposition(2,10);
                                    printf("ASO anhand Kraft");
                                 
                                 Soll_IBF->ASO_Pos = Ist_IBF->Vorring.Start_Ringhoehe - 10.0F;    //!!statt Zaehler wurde als Wert 10 (mm) eingesetzt;;;zaehler wurde in case'a' auf den Wert 0.5F gesetzt
                                 
                                 if (Ist_IBF->FA_f >= Axialkraft  || Ist_IBF->FA_f == Axialkraft /*|| t_Halte == 0*/) //JETZT MIT TEST TEST TEST....wirkende Axialkraft1 ist gemittelte AG-Kraft durch Eigengewicht !!
                                 {
                                    #ifdef MRAW
                                	 _settextposition(2,10);
                                     printf("ASO hat Position durch Kraft erreicht FA: %8.1f-eingabe-: %8.1f", Ist_IBF->FA, Axialkraft);
                                    #endif
                                    Soll_IBF->ASO_Pos = Ist_IBF->ASO_Pos;
                              
                                    Soll_IBF->ASO_V   = 1.0F;
                                    
                                    Soll_IBF->InitAchse    = ' ';
                                    Soll_IBF->Profilflag   = 1; 
                                 }// end if
                                #endif
                              }//end if(Axialkraft!=NULL) 
                              
                              
                              if(Ist_IBF->Flag.as_kraftanfahren_aktiv == 0) //wird durchlaufen, wenn ohne Kraftsteuerung angefahren wird
                              { 
                                 Soll_IBF->ASO_Pos = Ist_IBF->Vorring.Start_Ringhoehe;
                                 if (Ist_IBF->ASO_Pos <= (Soll_IBF->ASO_Pos + eps) || Ist_IBF->ASO_Pos <= (Soll_IBF->ASO_Pos - eps) ) 
                                 {Soll_IBF->InitAchse = ' '; Soll_IBF->Profilflag = 1; break;} // Hier IBF_Allgemein.IBF_Allgemein.IBF_Allgemein.Profilflag bestimmen wie es weiter geht 
                              }
                                                				
                              break;//break

                  case 'z':   // 2 Umdrehungen abwarten für gleichmäßiges Profil über Umfang 
                              t_Halte--;
                              if (t_Halte <= 0) {Soll_IBF->InitAchse = 'b';};
                              break;  // zu case 'z'
                                                
                  default:    
                              #ifdef MRAW
                                 _settextposition(9,1);
                                 printf(" InitAchse: %d - Warum default ?!? ", Ist_IBF->InitAchse);
                              #endif   
                              break;
                              
                  } //	Klammer zu: switch (InitAchse) von case0 
                  break;
   
   
         case 1:     //Vergleich der eingegebenen Wandstärke und der, per Kraftsteuerung angefahrenen Wandstärke
                     // Routine, ob Schalter gesetzt ist oder nicht -> Schalter (0,1,2)
                     
                     s_ist = Ist_IBF->Afpos_dw - ((186.9F + Ist_IBF->Werkzeugdurchmesser)/2.0F);
                     Soll_IBF->Soll_ASO_Pos_alt = Ist_IBF->ASO_Pos;     
                     s_f_alt = Ist_IBF->s_f; // dem Wert s_f_alt wird hier bereits der erste Wert vorgegeben, damit in case 11/12 keine Division durch NULL stattfindet.... 
                     #ifdef MRAW
                        _settextposition(6,10);
                        printf("s_ist %8.1f  s_gemessen %8.1f", s_ist, Ist_IBF->Wandstaerke_Null);
                     #endif
                     
                     if(Ist_IBF->Schalter_Kont_DisKo == 0)  // kontinuierlicher Vorschub
                     {Soll_IBF->Profilflag = 11; s_ist = 0; break;}
                     
                     if (Ist_IBF->Schalter_Kont_DisKo == 1) //diskontinuierlicher Vorschub (eps über Weg)
                     {Soll_IBF->Profilflag = 12; Soll_IBF->RS_Pos = Ist_IBF->RS_Pos - 0.5f; break;}
                     
                     if (Ist_IBF->Schalter_Kont_DisKo == 2) //diskontinuierlicher Vorschub (eps über Geschwindigkeit)
                     {
                        Soll_IBF->Profilflag =13; 
                        t_dis_h = 10*(Ist_IBF->Vorring.D_Null/(diam_hw*f_H)); //Zeit für x Umdrehungen bei denen der Dorn in den Ring vorfährt bis Schnabel-Formel greift
                        break;
                     }
                     
                     else
                     {
                        #ifdef MRAW
                           _settextposition(10,15);
                           printf("Fehler in Schalterstellung");
                        #endif
                     }
                     break;
                    
       
       case 11:      //Kontinuierlcher Walzungsroutine
                     Soll_Inter->kwo_n = kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);
                     Soll_Inter->kwu_n = kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);               			
                     
                     Soll_IBF->RS_V  = Soll_IBF->Vorschubgeschw_Dw;    // Dorn, Radialschlitten   
                     Soll_IBF->ASO_V = 100.0F;
                    
                     Soll_IBF->ASO_Pos = 143.0F;

                     if(Soll_IBF->Steg != 0)   // Abfrage ob Stegstärke angegeben
                     {
                     Soll_IBF->RS_Pos = (diam_hw + Ist_IBF->Werkzeugdurchmesser)/2 + Soll_IBF->Steg;
                    
                     }
                     else Soll_IBF->RS_Pos = Ist_IBF->Afpos_dw - Soll_IBF->delta_s;  //Afpos_dw wird in case 0 -> case 'a' gesetzt.....
                     
                     Soll_IBF->RS_Pos = Ist_IBF->RS_Pos;
                    
                     if(Ist_IBF->RS_Pos <= Soll_IBF->RS_Pos || Ist_IBF->RS_Pos <= (Soll_IBF->RS_Pos + eps) || Ist_IBF->RS_Pos <= (Soll_IBF->RS_Pos - eps))
                     {	
                        t_Halte= Soll_IBF->Umdrehungen*10*(Ist_IBF->Vorring.D_Null/(diam_hw*f_H));
                        //t_Halte=Umdrehungen*10*diam_f/(diam_hw*f_H); // n Umdrehungen, 10 * "100" ms Aufrufzyklus = 1000 ms = 1s;  
                        
                        Soll_IBF->Profilflag = 2; 
                        Soll_IBF->ASO_Pos = Ist_IBF->ASO_Pos; // damit kein Durck ausgeübt wird wenn Walzprozeß beendet ist muss hier noch eine Konstante eingefügt werden (z.B. 5)
                        break;
                        }                  
                     
                     //------------------------------------------------------------------------------------------------------
                    //--------------------------Kraftsteuerung des oberen Axialschlittens ----------------------------------
                    //------------------------------------------------------------------------------------------------------
                       
                    if(Axialkraft != NULL)
                    {
                                         
                      uk1_ASO = uk_ASO;
                      uk_ASO = (Ist_IBF->FA_f - Axialkraft);                 // gemittelte Axialkraft aus Interfac.
                      
                      Del_ASO_Pos = KP*(uk_ASO - uk1_ASO) + 1.0F*uk_ASO;    // PI-Regler nach Böhmer, jedoch mit KP=Böhmer;KI=1.0F hier noch Einstellen!!!!
                                            
                      Soll_IBF->ASO_Pos = Ist_IBF->ASO_Pos;
                       
                    }
                    
                       
                        //------------------------------------------------------------------------------------------------------
                        //----------------------- Positionssteuerung des oberen Axialschlittens --------------------------------
                        //------------------------------------------------------------------------------------------------------
                        
                        if(t_dis_h <=0)
                        {
                           
                           delta_h = 10*(diam_f*(s_f_alt - Ist_IBF->s_f)-(s_f_alt*s_f_alt) + (Ist_IBF->s_f*Ist_IBF->s_f))/(diam_f * s_f_alt - (s_f_alt*s_f_alt)); 
                           // Delta_h = 10 mm Werkzeugbreite *gef.Wanddicke (diam_f)*(Wanddicke[n]^2-Wanddicke[n-1]^2)+Wanddicke[n-1]^2-Wanddike[n]^2/(Klammerausdruck)
                           
                           Soll_IBF->ASO_Pos = Soll_IBF->Soll_ASO_Pos_alt + delta_h;
                           
                           Soll_IBF->Soll_ASO_Pos_alt = Soll_IBF->ASO_Pos;  
                           s_f_alt = Ist_IBF->s_f;   
                           t_dis_h = 10*(Ist_IBF->Vorring.D_Null/(diam_hw*f_H)); // 1 Umdrehungen (kein Wert vor der 10), 10*100 ms = 1000 ms = 1s
                        }        
                        
                        t_dis_h--;
                        
                        break;
                     
                     
        case 2:   //---------------------------------------------------------------------------------
                  //------- 2 Umdrehungen abwarten für gleichmäßiges Profil über Umfang -------------
                  //---------------------------------------------------------------------------------
                  
                  Soll_Inter->kwo_n = kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);
                  Soll_Inter->kwu_n = kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);               			
                  
                  Soll_IBF->ASO_V = 5.0F;
                                 
                    
                  t_Halte--;
                  t_warte_flag=0; //zurücksetzen der Bedingung (Diskonti...)
                  
                                    
                  if (t_Halte <= 0) 
                  {  
                      Soll_IBF->ExitAchse ='a';Soll_IBF->Profilflag = 3; break;   //hier befehle reinschreiben, wenn ein weiterer Schritt abgearbeitet werden soll.....
                  }
                  break;             
                  
      
       case 3:    //Memoryflag= Ist_IBF->Profilflag;
                  // RS und AS auffahren; danach manuell Entladeposition anfahren (Koppers 'e')     
                  switch (Ist_IBF->ExitAchse) 
                  {                         
                  
                     Steuerbyte_Lese.freigabe = 191;	// war 95
                     //Freigabe_MRAW_Senden();
                                 
                        case 'a': 	
                              Soll_IBF->RS_Pos=Ist_IBF->RS_Pos_Start+10.0F; //michl
                              Soll_IBF->RS_V = 5.0F;
                   
                              if (Ist_IBF->RS_Pos >= Soll_IBF->RS_Pos) Soll_IBF->ExitAchse = 'b';
                              break;
 
                        case 'b':
                   
                              Soll_IBF->AG_Pos = Ist_IBF->AG_Pos_Null  + 50; 
                              Soll_IBF->ASO_Pos= Ist_IBF->ASO_Pos_Null + 15; //michl
                              
                              Soll_IBF->ASO_V = 15.0F; 
                       
                              
                              Soll_IBF->AG_V = 8.0F;
                              Soll_IBF->Soll_ZAR_V = 0.0F;                   	
                              Soll_IBF->Soll_ZAL_V = 0.0F;                   	

                              if (Ist_IBF->AG_Pos >= Soll_IBF->AG_Pos) 
                              {
                                 Soll_IBF->ExitAchse = ' '; 
                                 Soll_IBF->Profilflag++;
                              }
                              
                              if (     (Ist_IBF->RS_Pos  >= Soll_IBF->RS_Pos)
                                    && (Ist_IBF->ASO_Pos >= Soll_IBF->ASO_Pos)
                                    #ifdef MRAW
                                       && (Ist_IBF->ASU_Pos >= Soll_IBF->Soll_ASU_Pos)
                                    #endif
                                 )
                              {
                                 Soll_IBF->ExitAchse = ' '; 
                                 Soll_IBF->Profilflag++;
                                 break;
                              }
                              //----------------------------------------------------------------------------------------------------
                              //------------------- Damit die Variabelwerte, die während einer vorgehenden Walzung------------------
                              //--------------------nicht im Speicher verbleiben, müssen diese zurückgesetzt werden-----------------
                              //----------------------------------------------------------------------------------------------------
                                 
                                 Ist_IBF->FR_f = 0; Ist_IBF->FA_f = 0;
                                	zaehler=0;  uk_ASO=0;
                                 uk1_ASO=0;	diam_f=0;   diam_f_alt=0;     t_Halte = 0;   t_warte = 0;	
                                 
                              break;                        
                              
                  default: 	break;
                  } // Klammer zu: switch(ExitAchse)                  
                  break;	
                 
    case 40:      //Routine die zur Pause gehört
                  break;

/*---------------------------------------------------------------------------------*/	
/*--------------------------------------ENDE ENDE ENDE ----------------------------*/		      
/*---------------------------------------------------------------------------------*/
   
}; // Klammer zu: switch (IBF_Allgemein.IBF_Allgemein.Profilflag) 
       
}; // Klammer zu: Ende von if !Auto else 
 
//########## Ende Hand- bzw. Automatiksteuerung ##########


    /* ------------------------------------------------------------------------ */
    /*                                                                          */
    /*  Übergabe der Sollwerte aus der IBF-Struktur an die 'Ist_Inter' Struktur */
    /*                                                                          */
    /* ------------------------------------------------------------------------ */
    
               /* Kraft [N]*/
                  Soll_Inter->rs_kraft  = Soll_IBF->RS_Kraft;
                  Soll_Inter->aso_kraft = Soll_IBF->AS_Kraft;
                  Soll_Inter->ag_kraft  = Soll_IBF->AG_Kraft;
                 //Soll_Inter->asu_kraft;
                 //Soll_Inter->ag_kraft;
                 //Soll_Inter->zal_kraft;
                 //Soll_Inter->zar_kraft;

               /* Flags für Kraftsteuerung */
                  Soll_Inter->rs_kraftregler_aktiv  =  Ist_IBF->Flag.rs_kraftregler_aktiv;   /* [0-1] */
                  Soll_Inter->aso_kraftregler_aktiv =  Ist_IBF->Flag.as_kraftregler_aktiv;
                   //Soll_Inter->asu_kraftregler_aktiv;   /* keine Kraftmessung des unter Axialschlittens an Banning*/
                   //Soll_Inter->ag_kraftregler_aktiv;
                   //Soll_Inter->zal_kraftregler_aktiv;
                   //Soll_Inter->ar_kraftregler_aktiv;

               /* Geschwindigkeit [mm/s] */
                  Soll_Inter->rs_v     = Soll_IBF->RS_V;         /* Übergebe Gechwindigkeit an Tabelle */
                  Soll_Inter->aso_v    = Soll_IBF->ASO_V;
                  Soll_Inter->asu_v    = Soll_IBF->Soll_ASU_V;
                  Soll_Inter->ag_v     = Soll_IBF->AG_V;       
                  Soll_Inter->zal_v    = Soll_IBF->Soll_ZAL_V;       
                  Soll_Inter->zar_v    = Soll_IBF->Soll_ZAR_V;

              /* Positionen [mm]*/
                  Soll_Inter->rs_pos = Soll_IBF->RS_Pos;
                  Soll_Inter->aso_pos = Soll_IBF->ASO_Pos;
                  //Soll_Inter->ag_pos = Soll_IBF->AG_Pos;
                  //Soll_Inter->zal_pos = Soll_IBF->ZAL_Pos;
                  //Soll_Inter->zar_pos = Soll_IBF->ZAR_Pos;

         
        
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



