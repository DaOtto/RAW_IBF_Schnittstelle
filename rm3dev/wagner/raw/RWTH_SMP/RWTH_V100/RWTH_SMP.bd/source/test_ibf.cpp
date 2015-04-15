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
        TestDat[2] = 0;
        TestDat[3] = 0;
        TestDat[4] = 0;
        TestDat[5] = 0;  
        TestDat[6] = 0;
        TestDat[7] = 0;
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

   case 10: // 
        strncpy(TestString, "Radialschlitten IBF", SizeString);
        TestDat[1] = aus_onli.ds_dh_sp_hp.s_punkt * 1000; // [1/1000 mm/s]
        TestDat[2] = Soll_Inter.rs_pos            * 100;
        TestDat[3] = Soll_Inter.rs_kraftregler_aktiv;
        TestDat[4] = Soll_Inter.rs_kraft;
        TestDat[5] = Soll_IBF.Soll_RS_Pos         * 100;  
        TestDat[6] = Soll_IBF.RS_Pos_Start        * 100;
        TestDat[7] = Soll_IBF.RS_Pos_Null         * 100;
        TestDat[8] = 0;
        TestDat[9] = Ist_IBF.RS_Pos               * 100;
        break;

   case 11: // 
        strncpy(TestString, "Axialschlitten oben IBF", SizeString);
        TestDat[1] = aus_onli.ds_dh_sp_hp.h_punkt * 1000; // [1/1000 mm/s]
        TestDat[2] = Soll_Inter.aso_pos           * 100;
        TestDat[3] = Soll_Inter.aso_kraftregler_aktiv;
        TestDat[4] = Soll_Inter.aso_kraft;
        TestDat[5] = 0;  
        TestDat[6] = 0;
        TestDat[7] = 0;
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

   case 12: // 
        strncpy(TestString, "Axialgeruest IBF", SizeString);
        TestDat[1] = Soll_Inter.ag_v   * 1000;
        TestDat[2] = Soll_Inter.ag_pos * 100;
        TestDat[3] = Soll_Inter.ag_kraftregler_aktiv;
        TestDat[4] = Soll_Inter.ag_kraft;
        TestDat[5] = Soll_IBF.Soll_AG_Pos         *100;  
        TestDat[6] = Ist_IBF.AG_Pos_Start        *100;
        TestDat[7] = 0;
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

   case 13: // 
        strncpy(TestString, "Zentrierarm Einlaufseite IBF", SizeString);
        TestDat[1] = Soll_Inter.zar_v     * 1000;
        TestDat[2] = Soll_Inter.zar_pos   * 100;
        TestDat[3] = Soll_Inter.zar_kraftregler_aktiv;
        TestDat[4] = Soll_Inter.zar_kraft;
        TestDat[5] = 0;  
        TestDat[6] = 0;
        TestDat[7] = 0;
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

   case 14: // 
        strncpy(TestString, "Zentrierarm Auslaufseite IBF", SizeString);
        TestDat[1] = Soll_Inter.zal_v     * 1000;
        TestDat[2] = Soll_Inter.zal_pos   * 100;
        TestDat[3] = Soll_Inter.zal_kraftregler_aktiv;
        TestDat[4] = Soll_Inter.zal_kraft;
        TestDat[5] = 0;  
        TestDat[6] = 0;
        TestDat[7] = 0;
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

      /* Sollkräfte */
      // Soll_Inter.rs_kraft;               /* Kraft [N] */
      // Soll_Inter.aso_kraft;
      // Soll_Inter.ag_kraft;
      // Soll_Inter.zal_kraft;
      // Soll_Inter.zar_kraft;



   case 15: // 
        strncpy(TestString, "Motordrehzahlen IBF", SizeString);
        TestDat[1] = aus_puff.n_omega.n_hw_motor     * 1000;
        TestDat[2] = aus_puff.n_omega.n_aw_motor_g_o * 1000;
        TestDat[3] = aus_puff.n_omega.n_aw_motor_g_u * 1000;
        TestDat[4] = 0;
        TestDat[5] = 0;  
        TestDat[6] = 0;
        TestDat[7] = 0;
        TestDat[8] = 0;
        TestDat[9] = 0;
        break;

   case 16: // 
        strncpy(TestString, "Testkennung IBF", SizeString);
        TestDat[1] = (long) Ist_IBF.AUTO;
        TestDat[2] = (long) Ist_IBF.Profilflag;
        TestDat[3] = (long) Ist_IBF.InitAchse;
        TestDat[4] = (long) Ist_IBF.ExitAchse;
        TestDat[5] = (long) Soll_IBF.Profilflag;  
        TestDat[6] = (long) Soll_IBF.InitAchse;
        TestDat[7] = (long) Soll_IBF.ExitAchse;
        TestDat[8] = 0;
        TestDat[9] = ein_puff.walzenstart_flag;
        break;

   case 17: // 
        strncpy(TestString, "Motordrehzahlen AW oben IBF", SizeString);
        TestDat[1] = aus_puff.n_omega.n_aw_motor_g_o * 1000;
        TestDat[2] = Soll_Inter.kwo_n * MIN_FAK      * 1000; 
        TestDat[3] = rpw->kw_ia                      * 1000;
        TestDat[4] = rpw->hw_ir                      * 1000;  
        TestDat[5] = rpw->diam_hw                    * 100;
        TestDat[6] = Ist_Inter.hw_n * MIN_FAK        * 1000;
        TestDat[7] = Ist_IBF.Del_Kr_AGR              * 100;
        TestDat[8] = Ist_IBF.Pos_auf_Mantel          * 100;
        TestDat[9] = rpw->sin_kw_winkel_halbe        * 100000;
        break;


   default:
        sprintf(TestString, "Testcode %d wird nicht unterstützt!", (TestDat[0] & 0x0fff) + 10000);
        for (int i=0; i<10; i++)
           TestDat[i] = 0;
        break;
        
   } // end switch()

}
