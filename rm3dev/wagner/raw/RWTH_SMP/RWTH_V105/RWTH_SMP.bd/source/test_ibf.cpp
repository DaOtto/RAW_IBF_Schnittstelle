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
        TestDat[2] = ein_onli.Ibf_actual.Ibf_Achse1; 
        TestDat[3] = ein_onli.Ibf_actual.Ibf_Achse2;    
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
        TestDat[2] = Ist_IBF.ASO_Pos  * 100; 
        TestDat[3] = Soll_IBF.ASO_V; 
        TestDat[4] = Ist_IBF.Rohling_h_angefahren;  
        TestDat[5] = Ist_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num];
        TestDat[6] = Ist_IBF.Axial.Pr_Num;
        TestDat[7] = Soll_IBF.AS_Kraft; 
        TestDat[8] = Ist_IBF.FA;
        TestDat[9] = Soll_Inter.aso_mode;
        break;


   default:
        sprintf(TestString, "Testcode %d wird nicht unterstützt!", (TestDat[0] & 0x0fff) + 10000);
        for (int i=0; i<10; i++)
           TestDat[i] = 0;
        break;
        
   } // end switch()

}
