/*--FILE HEADER---------------------------------------------------------------
;   filename        : test_ibf.cpp
;   version         : V1.0
;   contents        : Testwerte aufbereiten
;   author          : K. Brauckmann, SMS Eumuco GmbH
;   date            : May, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   Testwerte werden auf die CARWIN-Testfelder gelegt
;
;   RMOS3 Version 3.30
;
;   (c) 2006 SMS Eumuco GmbH Produktbereich Ringwalzen
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   May , 12. 2006  0001  K.B.  original issue
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
/****************************************************************************/
/*  includes                                                                */
/****************************************************************************/
/* includes from outside the project */

#include "rmos_inc.h"

/* includes from inside the project */

#include "test_ibf.hpp"
#include "rwth_task.hpp"
#include "rwth_exch.hpp"

//**************************************************************************
// Konstruktor
//**************************************************************************
TEST_IBF::TEST_IBF(void)
{
   CountTest = 0;
}

//**************************************************************************
// Test_Ausgaben bearbeiten
//
// Startcode unter Windows ist 10000 => entspricht case 0:
// Letzter möglicher Code  ist 10999 => entspricht case 999:
//**************************************************************************
void TEST_IBF::WRITE_VALUES(long * TestDat, char * TestString, int SizeString)
{
   switch (TestDat[0] & 0xffff) // high word ist Laufzeittest!
   {
    
   case 1: 
        strncpy(TestString, "Laufzeittest IBF count up", SizeString);
        TestDat[1] = CountTest++;
        TestDat[2] = 0;      
        TestDat[3] = 0;
        TestDat[4] = 0;
        TestDat[5] = 0;
        TestDat[6] = 0;
        TestDat[7] = 0;
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

   case 2: // 
        strncpy(TestString, "TestCounter 0...8 IBF", SizeString);
        TestDat[1] = TestCounter[0];
        TestDat[2] = TestCounter[1];
        TestDat[3] = TestCounter[2];
        TestDat[4] = TestCounter[3];
        TestDat[5] = TestCounter[4];  
        TestDat[6] = TestCounter[5];
        TestDat[7] = TestCounter[6];
        TestDat[8] = TestCounter[7];
        TestDat[9] = TestCounter[8];
        break;

   case 3: // 
        strncpy(TestString, "TestCounter 9...17 IBF", SizeString);
        TestDat[1] = TestCounter[9];
        TestDat[2] = TestCounter[10];
        TestDat[3] = TestCounter[11];
        TestDat[4] = TestCounter[12];
        TestDat[5] = TestCounter[13];  
        TestDat[6] = TestCounter[14];
        TestDat[7] = TestCounter[15];
        TestDat[8] = TestCounter[16];
        TestDat[9] = TestCounter[17];
        break;

   case 4: // 
        strncpy(TestString, "Test private IBF", SizeString);
        TestDat[1] = *rwth_exch->get_pCountBlinker();
        TestDat[2] = 0;
        TestDat[3] = 0;
        TestDat[4] = 0;
        TestDat[5] = 0;  
        TestDat[6] = 0;
        TestDat[7] = 0;
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

   case 5: // 
        strncpy(TestString, "Test private IBF", SizeString);
        {
         LOG_CHANNEL_DEF * TableLog = Logger->getLogPointer();
         TestDat[1] = *((long *)TableLog[0].pAdresse);
        }
        TestDat[2] = Ist_IBF.Zeit.Ringumdrehung * 1000;         // [1/1000 1/s]
        TestDat[3] = Ist_Inter.Werkzeug.Ringumdrehung * 1000 ;  // [1/1000 mm/s]
        TestDat[4] = Ist_IBF.Zeit.Halbe_Ringumdrehung * 1000;
        TestDat[5] = Ist_Inter.hw_n * 100;  //[1/100 1/s]
        TestDat[6] = Ist_Inter.Werkzeug.Drehzahl_HW * 100;
        TestDat[7] = Ist_Inter.Werkzeug.Durchmesser_HW;
        TestDat[8] = Ist_Inter.da;
        TestDat[9] = 0;
        break;
  
  // Allgemein
  case 10: //
        strncpy(TestString, "INI-Parameter IBF", SizeString);
        TestDat[1] = Ist_IBF.Flag.rs_kraftanfahren_aktiv;
        TestDat[2] = Soll_IBF.RS_Kraft_Vorgabe; 
        TestDat[3] = Ist_IBF.Vorring.Wandstaerke_Null;
        TestDat[4] = 0;  
        TestDat[5] = Soll_IBF.AS_Kraft_Anfahren;
        TestDat[6] = Soll_IBF.AS_Kraft;
        TestDat[7] = Ist_IBF.FA;
        TestDat[8] = 0;
        TestDat[9] =  Ist_Inter.Systemzeit;
        break;

  case 11: // 
        strncpy(TestString, "Testkennung IBF", SizeString);
        TestDat[1] = (long) Ist_IBF.Profilflag;
        TestDat[2] = 0;
        TestDat[3] = (long) Ist_IBF.InitAchse;
        TestDat[4] = (long) Ist_IBF.ExitAchse;
        TestDat[5] = (long) Soll_IBF.Profilflag;  
        TestDat[6] = (long) Soll_IBF.InitAchse;
        TestDat[7] = (long) Soll_IBF.ExitAchse;
        TestDat[8] = aus_onli.Ibf_nominal.RS_mode;
        TestDat[9] = ein_puff.walzenstart_flag;
        break;

   case 12: // 
        strncpy(TestString, "Motordrehzahlen IBF", SizeString);
        TestDat[1] = aus_puff.n_omega.n_hw_motor     * 1000;
        TestDat[2] = aus_puff.n_omega.n_aw_motor_g_o * 1000;
        TestDat[3] = aus_puff.n_omega.n_aw_motor_g_u * 1000;
        TestDat[4] = 0;
        TestDat[5] = Ist_Inter.hw_n *1000;  
        TestDat[6] = Ist_Inter.Werkzeug.Drehzahl_HW *1000;
        TestDat[7] = Ist_Inter.hw_n *1000 /60;
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

   case 13: // 
        strncpy(TestString, "Motordrehzahlen AW oben IBF", SizeString);
        TestDat[1] = aus_puff.n_omega.n_aw_motor_g_o * 1000;
        TestDat[2] = Soll_Inter.kwo_n * MIN_FAK      * 1000; 
        TestDat[3] = Ist_Inter.kw_ia                 * 1000;    //rpw->kw_ia                      * 1000;
        TestDat[4] = Ist_Inter.hw_ir                 * 1000;    //rpw->hw_ir                      * 1000;  
        TestDat[5] = Ist_Inter.Werkzeug.Durchmesser_HW;        //rpw->diam_hw                    * 100;
        TestDat[6] = Ist_Inter.hw_n * MIN_FAK        * 1000;
        TestDat[7] = 0;
        TestDat[8] = 0;
        TestDat[9] = rpw->sin_kw_winkel_halbe        * 100000;
        break;

    case 14: // 
        strncpy(TestString, "IBF-Messachsen", SizeString);
        TestDat[1] = 0;
        TestDat[2] = ein_onli.Ibf_actual.Ibf_Achse1 * 100; 
        TestDat[3] = ein_onli.Ibf_actual.Ibf_Achse2 * 100;    
        TestDat[4] = ein_onli.Ibf_actual.Ibf_Achse3;     
        TestDat[5] = ein_onli.Ibf_actual.Ibf_Achse4;       
        TestDat[6] = Ist_Inter.Ibf_Achse1;
        TestDat[7] = Ist_Inter.Ibf_Achse2;
        TestDat[8] = Ist_Inter.Ibf_Achse3;
        TestDat[9] = Ist_Inter.Ibf_Achse4;
        break;

  // Radialschlitten
   case 20: // 
        strncpy(TestString, "Radialschlitten IBF - Schalter ", SizeString);
        TestDat[1] = 0;       
        TestDat[2] = Soll_IBF.RS_Kraft;
        TestDat[3] = Soll_Inter.rs_kraft;
        TestDat[4] = Ist_IBF.FR;
        TestDat[5] = 0;             
        TestDat[6] = 0;
        TestDat[7] = Ist_IBF.Flag.rs_kraftanfahren_aktiv;    
        TestDat[8] = Ist_IBF.Flag.rs_kraft_anfahren_erreicht;
        TestDat[9] = Soll_IBF.Flag.rs_kraft_anfahren_erreicht;
        break;

   case 21: // 
        strncpy(TestString, "Radialschlitten IBF", SizeString);
        TestDat[1] = aus_onli.ds_dh_sp_hp.s_punkt       * 1000; // [1/1000 mm/s]
        TestDat[2] = Soll_Inter.rs_pos                  *  100; // [1/100 mm/s]
        TestDat[3] = Soll_IBF.RS_Pos                    *  100; // [1/100 mm/s]
        TestDat[4] = 0;
        TestDat[5] = 0;
        TestDat[6] = Soll_IBF.RS_Pos_Null               *  100; // [1/100 mm/s]
        TestDat[7] = aus_onli.Ibf_nominal.Soll_RS_Pos   *  100; // [1/100 mm/s]
        TestDat[8] = aus_onli.Ibf_nominal.RS_act;
        TestDat[9] = Ist_IBF.RS_Pos                     *  100; // [1/100 mm/s]
        break;

      
 // Axialschlitten 
   case 30: // 
        strncpy(TestString, "Axialschlitten oben IBF - Schalter", SizeString);
        TestDat[1] = Soll_IBF.Flag.aso_mode;        
        TestDat[2] = Soll_Inter.aso_mode;        
        TestDat[3] = aus_onli.Ibf_nominal.AS_mode;    
        TestDat[4] = 0;
        TestDat[5] = Ist_IBF.Flag.as_kraftregler_aktiv;
        TestDat[6] = 0;
        TestDat[7] = Ist_IBF.Flag.as_kraftanfahren_aktiv;
        TestDat[8] = Ist_IBF.Flag.as_kraft_anfahren_erreicht;
        TestDat[9] = Soll_IBF.Flag.as_kraft_anfahren_erreicht;
        break;   

    case 31: // 
        strncpy(TestString, "Axialschlitten oben IBF", SizeString);
        TestDat[1] = aus_onli.ds_dh_sp_hp.h_punkt * 1000;       // [1/1000 mm/s]
        TestDat[2] = Soll_Inter.aso_pos           * 100;        // [1/100 mm/s]
        TestDat[3] = aus_onli.Ibf_nominal.Soll_AS_Pos * 100;    // [1/100 mm/s]
        TestDat[4] = Ist_IBF.ASO_Pos;
        TestDat[5] = Soll_IBF.ASO_Pos;
        TestDat[6] = Soll_Inter.aso_kraft;
        TestDat[7] = Ist_IBF.FA;
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;   

	case 32: // 
        strncpy(TestString, "Startpositionen Debug", SizeString);
        TestDat[1] = ein_puff.form_mess_of.dis_hw_dw	* 100;       
        TestDat[2] = ein_puff.form_mess_of.dis_aw       * 100;        
        TestDat[3] = ein_onli.Ibf_actual.Ist_AG			* 100;    
        TestDat[4] = ein_puff.form_mess_of.da			* 100;
        TestDat[5] = ein_onli.Ibf_actual.Ist_ZEN_A		* 100;
        TestDat[6] = ein_onli.Ibf_actual.Ist_ZEN_E		* 100;
        TestDat[7] = ein_puff.n_hw_motor_ist			* 100;
        TestDat[8] = ein_puff.n_awo_motor_ist			* 100;
        TestDat[9] = ein_puff.pos_laser_u_of			* 100;
        break;   
	
	case 33: // 
        strncpy(TestString, "Debug DA Otto 2", SizeString);
        TestDat[1] = Ist_IBF.Schuessel.Walzform.hm				* 1;       
        TestDat[2] = Ist_IBF.Schuessel.Walzform.Kletterhoehe	* 1;        
        TestDat[3] = Ist_IBF.Schuessel.Walzform.Kletterwinkel	* 10;    
        TestDat[4] = aus_onli.Ibf_nominal.AG_mode;
        TestDat[5] = aus_onli.Ibf_nominal.Soll_ZA_Pos	* 100;
        TestDat[6] = aus_onli.Ibf_nominal.Soll_ZE_Pos	* 100;
        TestDat[7] = Soll_Inter.hw_n					* 100;
        TestDat[8] = Soll_Inter.kwo_n					* 100;
        TestDat[9] = Soll_Inter.kwu_n					* 100;
        break;  
   
		// Axialgerüst
   case 40: // 
        strncpy(TestString, "Axialgeruest IBF - Schalter / Kraft ", SizeString);
        TestDat[1] = Ist_IBF.Flag.Axial_Radialwalzen;
        TestDat[2] = Soll_Inter.ag_kraft;
        TestDat[3] = Soll_Inter.ag_v   * 1000;
        TestDat[4] = 0;
        TestDat[5] = Soll_Inter.ag_act;
        TestDat[6] = Soll_Inter.ag_mode;
        TestDat[7] = aus_onli.Ibf_nominal.AG_mode; 
        TestDat[8] = 0;
        TestDat[9] = Soll_Inter.ag_kraftregler_aktiv;
        break;

  
  case 41: //
        strncpy(TestString, "AG-Gerüst Ist_Inter/aus_onli.Ibf_nominal", SizeString);
        TestDat[1] = Ist_Inter.ag_pos;
        TestDat[2] = aus_onli.Ibf_nominal.Soll_AG_Pos; 
        TestDat[3] = aus_onli.Ibf_nominal.Soll_AG_V;
        TestDat[4] = 0;  
        TestDat[5] = aus_onli.Ibf_nominal.Soll_FAG;
        TestDat[6] = Soll_Inter.ag_kraft;
        TestDat[7] = Soll_IBF.AG_Kraft;
        TestDat[8] = Soll_Inter.ag_pos;
        TestDat[9] = Soll_IBF.Zeit.t_Halte;
        break;

   // Zentrierarme
   case 50: // 
        strncpy(TestString, "Zentrierarm Einlaufseite IBF", SizeString);
        TestDat[1] = Soll_Inter.zar_v     * 1000;
        TestDat[2] = Soll_Inter.zar_pos   * 100;
        TestDat[3] = aus_onli.Ibf_nominal.Soll_ZA_Pos;
        TestDat[4] = Ist_Inter.zar_pos;
        TestDat[5] = aus_onli.Ibf_nominal.Zen_mode;
        TestDat[6] = 0;  
        TestDat[7] = Soll_Inter.zar_kraftregler_aktiv;
        TestDat[8] = 0;
        TestDat[9] = Soll_Inter.zar_kraft;
        break;

   case 51: // 
        strncpy(TestString, "Zentrierarm Auslaufseite IBF", SizeString);
        TestDat[1] = Soll_Inter.zal_v     * 1000;
        TestDat[2] = Soll_Inter.zal_pos   * 100;
        TestDat[3] = aus_onli.Ibf_nominal.Soll_ZE_Pos;
        TestDat[4] = Ist_Inter.zal_pos;
        TestDat[5] = aus_onli.Ibf_nominal.Zen_mode;  
        TestDat[6] = 0;
        TestDat[7] = Soll_Inter.zal_kraftregler_aktiv;
        TestDat[8] = 0;
        TestDat[9] = Soll_Inter.zal_kraft;
        break;


   
   // Programm-Modul: Flexibles radiales Profilieren 
   case 60: //
        strncpy(TestString, "Berechnung der CR-Formel", SizeString);
        TestDat[1] = Soll_IBF.Radial.Cr.a;
        TestDat[2] = Soll_IBF.Radial.Cr.b; 
        TestDat[3] = Soll_IBF.Radial.Cr.c;
        TestDat[4] = Soll_IBF.Radial.Cr.d;  
        TestDat[5] = Soll_IBF.Radial.Cr.e;
        TestDat[6] = Soll_IBF.Radial.Cr.a * 1000;
        TestDat[7] = Soll_IBF.Radial.Cr.b * 1000;
        TestDat[8] = Soll_IBF.Radial.Cr.c * 1000;
        TestDat[9] = Soll_IBF.Radial.Cr.e * 1000;
        break;

   // Programm-Modul: Flexibles axiales Profilieren 
   case 70:    
        strncpy(TestString, "Axialprofilieren Allgemein", SizeString);
        TestDat[1] = Ist_IBF.Axial.Profilflag;
        TestDat[2] = Soll_IBF.Axial.Profilflag; 
        TestDat[3] = 0; 
        TestDat[4] = Soll_IBF.Axial.Wert;  
        TestDat[5] = 0;
        TestDat[6] = 0;
        TestDat[7] = 0; 
        TestDat[8] = 0;
        TestDat[9] = Soll_IBF.Zeit.t_Halte;
        break;

   case 71: //
        strncpy(TestString, "Axialprofilieren Kragengeo", SizeString);
        TestDat[1] = Ist_IBF.Axial.Kr_geo.Kr_Br;
        TestDat[2] = Ist_IBF.Axial.Kr_geo.Kr_d_nenn_vorne * 100; 
        TestDat[3] = Ist_IBF.Axial.Kr_geo.Kr_d_nenn_mitte;
        TestDat[4] = Ist_IBF.Axial.Kr_geo.Kr_d_nenn_hinten;  
        TestDat[5] = Ist_IBF.Axial.Kr_geo.Del_Kr_AGR;
        TestDat[6] = Ist_IBF.Axial.Kr_geo.sin_kw_winkel_halbe * 1000;
        TestDat[7] = Ist_IBF.Axial.Kr_geo.l_mantel_ukw_o_fehlende_spitze;
        TestDat[8] = Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw;
        TestDat[9] = Ist_IBF.Axial.Anfahrdurchm;  
        break;

    case 72: //
        strncpy(TestString, "Axialprofilieren Positionen SOll/IST", SizeString);
        TestDat[1] = Soll_IBF.AG_Pos   * 100;
        TestDat[2] = Soll_Inter.ag_pos * 100; 
        TestDat[3] = aus_onli.Ibf_nominal.Soll_AG_Pos; 
        TestDat[4] = Ist_IBF.AG_Pos;  
        TestDat[5] = Ist_Inter.ag_pos_real;
        TestDat[6] = ein_puff.form_mess_of.da; //Ist_AG-Pos bei Ein_Puff-Struktur ergibt sich durch Subtration von Außendurchmesser - Dornwalzenposition
        TestDat[7] = ein_puff.pos_laser_u_of; 
        TestDat[8] = Soll_IBF.AG_Pos_Start;
        TestDat[9] = Ist_IBF.AG_Pos_Start;
        break;

    case 73: //
        strncpy(TestString, "Axialprofilieren Positionen DEBEY", SizeString);
        TestDat[1] = ein_puff.awu_geometrie.achsenlaenge_l_fehlende_spitze;
        TestDat[2] = ein_puff.awu_geometrie.l_nutz; 
        TestDat[3] = ein_puff.awu_geometrie.l_fehlende_spitze; 
        TestDat[4] = ein_puff.awu_geometrie.l_zyl_ansatz;  
        TestDat[5] = ein_puff.awu_geometrie.winkel_gr;
        TestDat[6] = ein_puff.awu_geometrie.achsenlaenge_l_nutz; 
        TestDat[7] = ein_puff.awu_geometrie.du_grund; 
        TestDat[8] = ein_puff.awu_geometrie.du_spitze;
        TestDat[9] = ein_puff.awu_geometrie.l_mantel_theo;
        break;

    case 74: //
        strncpy(TestString, "Axialprofilieren Entscheider Nachführen", SizeString);
        TestDat[1] = Ist_IBF.Axial.Verh_pr_sf_proz_start;
        TestDat[2] = Ist_IBF.Axial.Verh_pr_sf_proz; 
        TestDat[3] = Soll_IBF.Axial.Wert; 
        TestDat[4] = 0;  
        TestDat[5] = Ist_IBF.Axial.Pr_Num;
        TestDat[6] = Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num];
        TestDat[7] = Ist_IBF.Axial.AGR_Pr[0]; 
        TestDat[8] = Ist_IBF.Axial.AGR_Pr[1];
        TestDat[9] = Ist_IBF.Axial.AGR_Pr[2];
        break;

    case 75:    
        strncpy(TestString, "Axialprofilieren Axialschlitten oben", SizeString);
        TestDat[1] = Soll_IBF.ASO_Pos * 100;
        TestDat[2] = Ist_IBF.ASO_Pos * 100; 
        TestDat[3] = Soll_IBF.ASO_V; 
        TestDat[4] = Ist_IBF.Rohling_h_angefahren;  
        TestDat[5] = Ist_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num];
        TestDat[6] = Ist_IBF.Axial.Pr_Num;
        TestDat[7] = Soll_IBF.AS_Kraft; 
        TestDat[8] = Ist_IBF.FA;
        TestDat[9] = Soll_Inter.aso_mode;
        break;

   case 76:    
        strncpy(TestString, "Axialprofilieren Axialgerüst-Startanfahren ", SizeString);
        TestDat[1] = Soll_IBF.delta_tr * 100;
        TestDat[2] = Soll_IBF.tr_pos   * 100; 
        TestDat[3] = Ist_Inter.tr_pos  * 100; 
        TestDat[4] = Soll_IBF.AG_Pos * 100;  
        TestDat[5] = Ist_IBF.AG_Pos * 100;
        TestDat[6] = Soll_IBF.ASO_Pos;
        TestDat[7] = Soll_IBF.ASO_Pos; 
        TestDat[8] = Soll_IBF.Zeit.t_Halte;
        TestDat[9] = Ist_IBF.Flag.AG_Start_erreicht;
        break;

        case 77:    
        strncpy(TestString, "Axialprofilieren Bissverhaeltnis ", SizeString);
        TestDat[1] = Ist_IBF.Axial.Biss.Verhaeltnis;
        TestDat[2] = Soll_IBF.Axial.Biss.AG_Pos_alt * 100; 
        TestDat[3] = Soll_IBF.AG_Pos  * 100; 
        TestDat[4] = 0;  
        TestDat[5] = Soll_IBF.Axial.Biss.Anzahl;
        TestDat[6] = Ist_IBF.Axial.Biss.Anzahl;
        TestDat[7] = Ist_IBF.Axial.Biss.AG_Pos_Erreicht; 
        TestDat[8] = Soll_IBF.Axial.AGR_Pr[0];
        TestDat[9] = Ist_IBF.Flag.Bissverhaeltnis;
        break;
        

        case 78:    
        strncpy(TestString, "Axialprofilieren Turbinenscheibe ", SizeString);
        TestDat[1] = Ist_IBF.Axial.Biss.Position;
        TestDat[2] = Soll_IBF.Axial.Biss.AG_Pos_Erreicht; 
        TestDat[3] = Ist_IBF.Axial.Biss.AG_Pos_Erreicht; 
        TestDat[4] = Ist_IBF.Axial.Biss.Anzahl;  
        TestDat[5] = Soll_IBF.Axial.Pr_Num;
        TestDat[6] = Ist_IBF.Axial.AGR_Pr[0];
        TestDat[7] = Soll_IBF.Axial.Biss.AG_Pos_alt; 
        TestDat[8] = Ist_IBF.AG_Pos;
        TestDat[9] = Soll_IBF.AG_Pos;
        break;

       case 90:    
        strncpy(TestString, "DA Jenkouk -> DW-Messsystem Test-Nr. 1", SizeString);
        TestDat[1] = Ist_IBF.Profilflag;
        TestDat[2] = Ist_IBF.InitAchse;    
        TestDat[3] = Soll_IBF.DW_Regelung.Alpha;   
        TestDat[4] = Soll_IBF.DW_Regelung.Gamma;  
        TestDat[5] = Soll_IBF.DW_Regelung.Beta;
        TestDat[6] = Soll_IBF.DW_Regelung.T_Einlauf;
        TestDat[7] = Soll_IBF.DW_Regelung.Messwert_A_mf * 100; 
        TestDat[8] = Soll_IBF.DW_Regelung.ri * 100;
        TestDat[9] = Soll_IBF.DW_Regelung.Wanddicke_berechnet * 100;
        break;

        case 91:    
        strncpy(TestString, "DA Jenkouk -> DW-Messsystem Test-Nr. 2", SizeString);
        TestDat[1] = Ist_IBF.Flag.DA_Jenkouk_Messen_ohne_Fahren;
        TestDat[2] = Ist_IBF.Flag.DA_Jenkouk_DW_Regelung;    
        TestDat[3] = Soll_IBF.DW_Regelung.Aufrufzeit_Regelzykl;    
        TestDat[4] = Soll_IBF.DW_Regelung.Anzahl_Zeitschritte;  
        TestDat[5] = Soll_IBF.RS_Pos;
        TestDat[6] = Ist_IBF.RS_Pos;
        TestDat[7] = Soll_IBF.DW_Regelung.DW_soll_Pos[0]; 
        TestDat[8] = Soll_IBF.DW_Regelung.TestOffset;
        TestDat[9] = Soll_IBF.DW_Regelung.Wanddicke_MS;
        break;

        case 92:    
        strncpy(TestString, "DA Jenkouk -> DW-Messsystem Test-Nr. 3", SizeString);
        TestDat[1] = Ist_IBF.DW_Regelung.Messwert_A * 100;
        TestDat[2] = Soll_IBF.DW_Regelung.Messwert_A_mf * 100;    
        TestDat[3] = 0;    
        TestDat[4] = Soll_IBF.DW_Regelung.ri_block1;  
        TestDat[5] = Soll_IBF.DW_Regelung.ri_block2;
        TestDat[6] = 0;
        TestDat[7] = Soll_IBF.DW_Regelung.Funktios_Iter; 
        TestDat[8] = Ist_IBF.da;
        TestDat[9] = Ist_IBF.di;
        break;

       case 93:    
        strncpy(TestString, "DA Jenkouk -> AG-Analyse", SizeString);
        TestDat[1] = Ist_IBF.Profilflag;
        TestDat[2] = Ist_IBF.InitAchse;    
        TestDat[3] = Soll_IBF.Zeit.t_Halte;    
        TestDat[4] = 0;  
        TestDat[5] = Ist_IBF.Flag.Axial_Radialwalzen;
        TestDat[6] = 0;
        TestDat[7] = Ist_IBF.Flag.DA_Jenkouk_AG_Analyse; 
        TestDat[8] = Ist_IBF.AG_Regelung.Haltezeit;
        TestDat[9] = Ist_IBF.AG_Regelung.Sprunghoehe;
        break;


    case 100:    
        strncpy(TestString, "IBF-Stuetzstellenberechnung", SizeString);
        TestDat[1] = Soll_IBF.stuetz_var.merker;
        TestDat[2] = Soll_IBF.stuetz_var.stellen[0][Soll_IBF.stuetz_var.merker]*10;    //Radialwalzspalt
        TestDat[3] = Soll_IBF.stuetz_var.stellen[1][Soll_IBF.stuetz_var.merker]*10;    //Axialwalzspalt
        TestDat[4] = Soll_IBF.stuetz_var.crtimer;  
        TestDat[5] = 0;
        TestDat[6] = 0;
        TestDat[7] = Soll_IBF.stuetz_var.delta_h; 
        TestDat[8] = Soll_IBF.ASO_V;
        TestDat[9] = Ist_IBF.stuetz_var.ca;
        break;


		
    case 101:    
        strncpy(TestString, "IBF-Formenspektrum", SizeString);
        TestDat[1] = Ist_IBF.Formen.epsilon;  										   //konstantes Epsilon 
        TestDat[2] = Ist_IBF.Formen.t_U_Viola;    									   //Zeit Ringumdrehung
        TestDat[3] = 0;													   				
        TestDat[4] = Soll_IBF.RS_V;  												   //Soll-Geschw. Dorn
        TestDat[5] = Ist_IBF.Radial.s_f;											   //Ist-Geschw. Dorn
        TestDat[6] = 0;
        TestDat[7] = 0; 
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

    case 102:    
        strncpy(TestString, "IBF-SchuesselWalzen", SizeString);
        TestDat[1] = 0;  										   //konstantes Epsilon 
        TestDat[2] = Ist_IBF.Formen.t_U_Viola;    									   //Zeit Ringumdrehung
        TestDat[3] = 0;													   				
        TestDat[4] = Soll_IBF.RS_V;  												   //Soll-Geschw. Dorn
        TestDat[5] = Ist_IBF.Radial.s_f;											   //Ist-Geschw. Dorn
        TestDat[6] = 0;
        TestDat[7] = Ist_IBF.Profilflag; 
        TestDat[8] = Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag;
        TestDat[9] = Ist_IBF.Schuessel.InitFlag;
        break;

	case 103:
		strncpy(TestString, "IBF Vorring-Geometrie/Werkzeug", SizeString);
        TestDat[1] = Ist_Inter.Vorform.sm;  
        TestDat[2] = Ist_Inter.Vorform.hm;    
        TestDat[3] = Ist_Inter.Vorform.da;													   				
        TestDat[4] = Ist_Inter.Werkzeug.Durchmesser_HW;  	
        TestDat[5] = Ist_Inter.Werkzeug.Durchmesser_DW;	
        TestDat[6] = Ist_IBF.Schuessel.StartPos.AG_startPos ;
        TestDat[7] = Ist_IBF.Profilflag; 
        TestDat[8] = Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag;
        TestDat[9] = Ist_IBF.Schuessel.InitFlag;
        break;

	case 104:
	    strncpy(TestString, "IBF-Achsenpostionen", SizeString);
        TestDat[1] = Ist_IBF.RS_Pos;
  	    TestDat[2] = Soll_IBF.RS_Pos;
        TestDat[3] = Ist_Inter.aso_pos;
  	    TestDat[4] = Soll_Inter.aso_pos;
        TestDat[5] = Ist_Inter.ag_pos;
		TestDat[6] = Soll_Inter.ag_pos;											   				
        TestDat[7] = Ist_Inter.zal_pos;
  	    TestDat[8] = Soll_Inter.zal_pos;  
        TestDat[9] = Ist_Inter.zar_pos;
        break;

	case 105:
		strncpy(TestString, "Test Puff-Struktur", SizeString);
        TestDat[1] = Ist_Inter.Werkzeug.Durchmesser_DW ;  
        TestDat[2] = ein_puff.soll_walzform.hm;    
        TestDat[3] = ein_puff.soll_walzform.sm;													   				
        TestDat[4] = ein_puff.vorform.hm;
        TestDat[5] = ein_puff.vorform.sm;	
        TestDat[6] = ein_puff.disy_dr_achsen_halbe;
        TestDat[7] = 0; 
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

	case 107:
		strncpy(TestString, "AG-DEBUG", SizeString);
        TestDat[1] = Soll_IBF.AG_Pos ;  
        TestDat[2] = Ist_IBF.AG_Pos ;    
        TestDat[3] = Soll_IBF.Flag.ag_act;													   				
        TestDat[4] = Soll_IBF.Flag.ag_mode;
        TestDat[5] = Soll_IBF.AG_V;
        TestDat[6] = Ist_IBF.Schuessel.StartPos.AG_startPos ;
        TestDat[7] = Ist_IBF.Profilflag; 
        TestDat[8] = Ist_IBF.Schuessel.AblaufFlags.AnfahrFlag;
        TestDat[9] = Ist_IBF.Schuessel.InitFlag;
        break;

	case 108:
		strncpy(TestString, "ZEN-DEBUG", SizeString);
        TestDat[1] = Ist_IBF.ZER_Param.ZRA.F_x;  
        TestDat[2] = Ist_IBF.ZER_Param.ZRA.F_y;   
        TestDat[3] = Ist_IBF.ZER_Param.ZRE.F_x;													   				
        TestDat[4] = Ist_IBF.Schuessel.Walzform.dw_min_Pos;
        TestDat[5] = Ist_IBF.ZER_Param.delta_ZRA_ZRE;
        TestDat[6] = Ist_IBF.ZER_Param.ZRA.MTS;
        TestDat[7] = Soll_IBF.ZER_Param.ZRA.delta_Ring; 
        TestDat[8] = Ist_IBF.ZER_Param.ZRE.MTS;
        TestDat[9] = Soll_IBF.ZER_Param.ZRE.delta_Ring;
        break;

	case 109:
		strncpy(TestString, "Drehzahl-DEBUG", SizeString);
        TestDat[1] = Ist_Inter.hw_n					* 100;  
        TestDat[2] = Ist_Inter.kwo_n				* 100;   
        TestDat[3] = Ist_Inter.kwu_n				* 100;													   				
        TestDat[4] = 0;
        TestDat[5] = Ist_IBF.K_Iter;
        TestDat[6] = 0;
        TestDat[7] = Soll_Inter.hw_n				* 100; 
        TestDat[8] = Soll_Inter.kwo_n				* 100;
        TestDat[9] = Soll_Inter.kwu_n				* 100;
        break;

	case 110:
		strncpy(TestString, "Druckrolle-DEBUG", SizeString);
        TestDat[1] = aus_onli.dr_auslauf_mp_no_korr.x;  
        TestDat[2] = aus_onli.dr_auslauf_mp_no_korr.y;   
        TestDat[3] = aus_onli.dr_auslauf_mp_no_korr.z;													   				
        TestDat[4] = aus_onli.dr_auslauf_pos_zyl_no_korr;
        TestDat[5] = aus_onli.dr_auslauf_pos_zyl;
        TestDat[6] = aus_onli.dr_pos_zyl_korr;
        TestDat[7] = aus_onli.dr_auslauf_mp.x; 
        TestDat[8] = aus_onli.dr_auslauf_mp.y;
        TestDat[9] = aus_onli.dr_auslauf_mp.z;
        break;

   default:
        sprintf(TestString, "Testcode %d wird nicht unterstützt!", (TestDat[0] & 0x0fff) + 10000);
        for (int i=0; i<10; i++)
           TestDat[i] = 0;
        break;
        
   } // end switch()

}
