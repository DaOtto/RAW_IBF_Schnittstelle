/*--FILE HEADER---------------------------------------------------------------
;   filename       : RWTH_LOGGER.CPP
;   version        : V1.0
;   contents       : Loggerchannels
;   author         : K. Brauckmann, SMS Eumuco GmbH
;   date           : May, 2004
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   Loggerkan�le
;
;       RMOS3 Version 3.30
;
;---END OF   FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   May, 11. 2006  0001  K.B.  original issue
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
/****************************************************************************/
/*  includes                                                                */
/****************************************************************************/
/* includes from outside the project */
#include "rmos_inc.h"

/* declarations from inside the project */
#include "rwth_logger.hpp"
#include "rwth_task.hpp"

//hier alle Klassen einbinden, die Loggerkan�le beinhalten!

/*********************************************************************/
/* Konstruktor                                                     */
/*********************************************************************/
LOGGER_RWTH::LOGGER_RWTH(void)
{
    for(int i = 0; i < MAX_LOG_KANAELE_RWTH; i++)
    {
        TableLogRWTH[i].type = 0;
        TableLogRWTH[i].faktor = 0.0;
        TableLogRWTH[i].pAdresse = NULL;
    }
}

/*********************************************************************/
// Kanalliste initialisieren
//
// Tabelle ausf�llen und erweitern bis auf MAX_LOG_KANAELE_RWTH
// Bedeutung s. LOG_CHANNEL_DEF in RAW_T_POOL.HPP
//
// Die Kan�le m�ssen auch im WINDOWS-Logger definiert werden!
// Startkanal im WINDOWS-Logger: 1000
/*********************************************************************/

int LOGGER_RWTH::Kanalliste(void)
{
   #define L_MM_S_FAK 1000.0       // [1/1000 mm/s] Geschwindigkeitsfaktor in mm / s
   #define N_KN_FAK   1000.0       // [1/1000 N]    Kraft-/Momentenfaktor in N
   #define MM_FAK     100.0        // [1/100 mm]    Wegfaktor in mm
   #define MM2_FAK    100.0        // [1/100 mm2]   Formelfaktor f�r Einheit mm2 
   #define S_FAK      100.0        // [1/100 s]     Zeitfaktor in Sekunde, Datalogger 0,01 s
   #define f_FAK      1000.0       // [1/1000 ]     Formelfaktor
   
   

   //Kanal 1000: Test -> Adresse einer protected Variablen 
   TableLogRWTH[0].type     = 2;
   TableLogRWTH[0].faktor   = 0.0;
   TableLogRWTH[0].pAdresse = (void *)rwth_exch->get_pCountBlinker();

   //Kanal 1001: Test -> Adresse einer protected Variablen 
   TableLogRWTH[1].type     = 2;
   TableLogRWTH[1].faktor   = 0.0;
   TableLogRWTH[1].pAdresse = (void *)rwth_exch->get_pBlinker();

   //Kanal 1002: Test -> Adresse einer globalen Variablen 
   TableLogRWTH[2].type     = 2;   
   TableLogRWTH[2].faktor   = 0.0;   
   TableLogRWTH[2].pAdresse = (void *)&TestCounter[0];

   //Kanal 1003: Test -> Adresse einer globalen Variablen 
   TableLogRWTH[3].type     = 2;   
   TableLogRWTH[3].faktor   = 0.0;   
   TableLogRWTH[3].pAdresse = (void *)&TestCounter[1];

   //Kanal 1004: Test -> Adresse des iter_IBF 
   TableLogRWTH[4].type     = 1;   
   TableLogRWTH[4].faktor   = 0.0;   
   TableLogRWTH[4].pAdresse = (void *)&iter_IBF; 

   //Kanal 1005:
   TableLogRWTH[5].type     = 1;   
   TableLogRWTH[5].faktor   = 0.0;   
   TableLogRWTH[5].pAdresse = (void *)&Soll_IBF.Profilflag;

   //Kanal 1006:
   TableLogRWTH[6].type     = 1;   
   TableLogRWTH[6].faktor   = 0.0;   
   TableLogRWTH[6].pAdresse = (void *)&Ist_IBF.Profilflag;

   //Kanal 1007: gecastete char-Variable
   TableLogRWTH[7].type     = 1;   
   TableLogRWTH[7].faktor   = 0.0;   
   TableLogRWTH[7].pAdresse = (void *)&Ist_IBF.InitAchse_gecastet;

   //Kanal 1008:
   TableLogRWTH[8].type     = 1;   
   TableLogRWTH[8].faktor   = 0.0;   
   TableLogRWTH[8].pAdresse = (void *)&Ist_IBF.InitAchse;

   //Kanal 1009:
   TableLogRWTH[9].type     = 3;   
   TableLogRWTH[9].faktor   = N_KN_FAK;   
   TableLogRWTH[9].pAdresse = (void *)&Ist_IBF.FR;

   //Kanal 1010:
   TableLogRWTH[10].type     = 3;   
   TableLogRWTH[10].faktor   = L_MM_S_FAK;   
   TableLogRWTH[10].pAdresse = (void *) &aus_onli.ds_dh_sp_hp.s_punkt;
   
   //Kanal 1011:
   TableLogRWTH[11].type     = 3;   
   TableLogRWTH[11].faktor   = N_KN_FAK;   
   TableLogRWTH[11].pAdresse = (void *)&Soll_IBF.RS_Kraft;

   //Kanal 1012:
   TableLogRWTH[12].type     = 3;   
   TableLogRWTH[12].faktor   = N_KN_FAK;   
   TableLogRWTH[12].pAdresse = (void *)&Ist_IBF.FA;

   //Kanal 1013:
   TableLogRWTH[13].type     = 3;   
   TableLogRWTH[13].faktor   = N_KN_FAK;   
   TableLogRWTH[13].pAdresse = (void *)&Soll_IBF.AS_Kraft;

   //Kanal 1014:
   TableLogRWTH[14].type     = 3;   
   TableLogRWTH[14].faktor   = S_FAK;   
   TableLogRWTH[14].pAdresse = (void *)&Ist_IBF.Zeit.Ringumdrehung;

   //Kanal 1015:
   TableLogRWTH[15].type     = 3;   
   TableLogRWTH[15].faktor   = MM_FAK;   
   TableLogRWTH[15].pAdresse = (void *)&Soll_IBF.min_ASO_Pos;

   //Kanal 1016:
   TableLogRWTH[16].type     = 3;   
   TableLogRWTH[16].faktor   = L_MM_S_FAK;   
   TableLogRWTH[16].pAdresse = (void *)&Soll_IBF.RS_V;

   //Kanal 1017:
   TableLogRWTH[17].type     = 3;   
   TableLogRWTH[17].faktor   = L_MM_S_FAK;   
   TableLogRWTH[17].pAdresse = (void *)&Soll_IBF.ASO_V;

   //Kanal 1018:
   TableLogRWTH[18].type     = 3;   
   TableLogRWTH[18].faktor   = L_MM_S_FAK;   
   TableLogRWTH[18].pAdresse = (void *)&Soll_IBF.AG_V;

   //Kanal 1019:
   TableLogRWTH[19].type     = 3;   
   TableLogRWTH[19].faktor   = MM_FAK;   
   TableLogRWTH[19].pAdresse = (void *)&Soll_IBF.RS_Pos;

   //Kanal 1020:
   TableLogRWTH[20].type     = 3;   
   TableLogRWTH[20].faktor   = MM_FAK;   
   TableLogRWTH[20].pAdresse = (void *)&Soll_IBF.RS_Pos_end;

   //Kanal 1021:
   TableLogRWTH[21].type     = 3;   
   TableLogRWTH[21].faktor   = MM_FAK;   
   TableLogRWTH[21].pAdresse = (void *)&Ist_IBF.RS_Pos;

   //Kanal 1022:
   TableLogRWTH[22].type     = 3;   
   TableLogRWTH[22].faktor   = MM_FAK;   
   TableLogRWTH[22].pAdresse = (void *)&Soll_IBF.ASO_Pos;

   //Kanal 1023:
   TableLogRWTH[23].type     = 3;   
   TableLogRWTH[23].faktor   = MM_FAK;   
   TableLogRWTH[23].pAdresse = (void *)&Ist_IBF.ASO_Pos;

   //Kanal 1024:
   TableLogRWTH[24].type     = 3;   
   TableLogRWTH[24].faktor   = MM_FAK;   
   TableLogRWTH[24].pAdresse = (void *)&Soll_IBF.AG_Pos;

   //Kanal 1025:
   TableLogRWTH[25].type     = 3;   
   TableLogRWTH[25].faktor   = MM_FAK;   
   TableLogRWTH[25].pAdresse = (void *)&Ist_IBF.AG_Pos;

   //Kanal 1026:
   TableLogRWTH[26].type     = 3;   
   TableLogRWTH[26].faktor   = N_KN_FAK;   
   TableLogRWTH[26].pAdresse = (void *)&Soll_IBF.AG_Kraft;

   //Kanal 1027:
   TableLogRWTH[27].type     = 3;   
   TableLogRWTH[27].faktor   = N_KN_FAK;   
   TableLogRWTH[27].pAdresse = (void *)&Ist_Inter.ag_f;

   //Kanal 1028:
   TableLogRWTH[28].type     = 3;   
   TableLogRWTH[28].faktor   = L_MM_S_FAK;   
   TableLogRWTH[28].pAdresse = (void *)&aus_onli.ds_dh_sp_hp.h_punkt;
   
   //Kanal 1029:
   TableLogRWTH[29].type     = 3;   
   TableLogRWTH[29].faktor   = S_FAK;   
   TableLogRWTH[29].pAdresse = (void *)&Soll_IBF.Zeit.t_Halte;

   //Kanal 1030:
   TableLogRWTH[30].type     = 3;   
   TableLogRWTH[30].faktor   = MM_FAK;   
   TableLogRWTH[30].pAdresse = (void *)&Soll_IBF.Radial.delta_h;

   //Kanal 1031:
   TableLogRWTH[31].type     = 3;   
   TableLogRWTH[31].faktor   = MM_FAK;   
   TableLogRWTH[31].pAdresse = (void *)&Soll_IBF.Radial.delta_s;

   //Kanal 1032:
   TableLogRWTH[32].type     = 3;   
   TableLogRWTH[32].faktor   = MM_FAK;   
   TableLogRWTH[32].pAdresse = (void *)&Soll_IBF.Radial.abnahme_s;

   //Kanal 1033:
   TableLogRWTH[33].type     = 3;   
   TableLogRWTH[33].faktor   = MM_FAK;   
   TableLogRWTH[33].pAdresse = (void *)&Soll_IBF.Radial.Soll_Wanddicke;

   //Kanal 1034:
   TableLogRWTH[34].type     = 3;   
   TableLogRWTH[34].faktor   = MM_FAK;   
   TableLogRWTH[34].pAdresse = (void *)&Ist_IBF.Radial.s_f;

   //Kanal 1035:
   TableLogRWTH[35].type     = 3;   
   TableLogRWTH[35].faktor   = MM_FAK;   
   TableLogRWTH[35].pAdresse = (void *)&Ist_IBF.Radial.s_f_alt;

   //Kanal 1036:
   TableLogRWTH[36].type     = 3;   
   TableLogRWTH[36].faktor   = MM_FAK;   
   TableLogRWTH[36].pAdresse = (void *)&Ist_IBF.Radial.Anfangsposition_DW;

   //Kanal 1037:
   TableLogRWTH[37].type     = 3;   
   TableLogRWTH[37].faktor   = L_MM_S_FAK;   
   TableLogRWTH[37].pAdresse = (void *)&Soll_IBF.Radial.Vorschubgeschw_Dw;

   //Kanal 1038:
   TableLogRWTH[38].type     = 3;   
   TableLogRWTH[38].faktor   = L_MM_S_FAK;   
   TableLogRWTH[38].pAdresse = (void *)&Soll_IBF.Radial.dw_vn;
   
   //Kanal 1039:
   TableLogRWTH[39].type     = 3;   
   TableLogRWTH[39].faktor   = S_FAK;   
   TableLogRWTH[39].pAdresse = (void *)&Soll_IBF.Radial.t_dis_h;
   
   //Kanal 1040:
   TableLogRWTH[40].type     = 0;   
   TableLogRWTH[40].faktor   = 0.0;   
   TableLogRWTH[40].pAdresse = NULL;
   
   //Kanal 1041:
   TableLogRWTH[41].type     = 3;   
   TableLogRWTH[41].faktor   = S_FAK;   
   TableLogRWTH[41].pAdresse = (void *)&Ist_Inter.Werkzeug.Drehzahl_HW;
   
   //Kanal 1042:
   TableLogRWTH[42].type     = 3;   
   TableLogRWTH[42].faktor   = MM_FAK;   
   TableLogRWTH[42].pAdresse = (void *)&Ist_Inter.Werkzeug.Durchmesser_HW;
   
   //Kanal 1043:
   TableLogRWTH[43].type     = 1;   
   TableLogRWTH[43].faktor   = 0.0;   
   TableLogRWTH[43].pAdresse = (void *)&Soll_IBF.Flag.ag_act;
   
   //Kanal 1044:
   TableLogRWTH[44].type     = 1;   
   TableLogRWTH[44].faktor   = 0.0;   
   TableLogRWTH[44].pAdresse = (void*)&aus_onli.Ibf_nominal.AG_act;
   
   //Kanal 1045:
   TableLogRWTH[45].type     = 1;   
   TableLogRWTH[45].faktor   = 0.0;   
   TableLogRWTH[45].pAdresse = (void*)&Soll_IBF.Flag.ag_mode;
   
   //Kanal 1046 Wert:
   TableLogRWTH[46].type     = 1;   
   TableLogRWTH[46].faktor   = 0.0;   
   TableLogRWTH[46].pAdresse = (void*)&aus_onli.Ibf_nominal.AG_mode;
   
   //Kanal 1047 Bit:
   TableLogRWTH[47].type     = 1;   
   TableLogRWTH[47].faktor   = 0.0;   
   TableLogRWTH[47].pAdresse = (void*)&aus_onli.Ibf_nominal.AG_mode;
   
   //Kanal 1048:
   TableLogRWTH[48].type     = 3;   
   TableLogRWTH[48].faktor   = MM_FAK;   
   TableLogRWTH[48].pAdresse = (void *)&Soll_Inter.aso_pos;
   
   //Kanal 1049:
   TableLogRWTH[49].type     = 3;   
   TableLogRWTH[49].faktor   = MM_FAK;   
   TableLogRWTH[49].pAdresse = (void *)&Ist_Inter.aso_pos;
   
   //Kanal 1050:
   TableLogRWTH[50].type     = 3;   
   TableLogRWTH[50].faktor   = MM2_FAK;   
   TableLogRWTH[50].pAdresse = (void*)&Soll_IBF.Radial.Cr.a;
   
   //Kanal 1051:
   TableLogRWTH[51].type     = 3;   
   TableLogRWTH[51].faktor   = MM2_FAK;   
   TableLogRWTH[51].pAdresse = (void*)&Soll_IBF.Radial.Cr.b;
   
   //Kanal 1052:
   TableLogRWTH[52].type     = 3;   
   TableLogRWTH[52].faktor   = MM_FAK;   
   TableLogRWTH[52].pAdresse = (void*)&Soll_IBF.Radial.Cr.c;
   
   //Kanal 1053:
   TableLogRWTH[53].type     = 3;   
   TableLogRWTH[53].faktor   = MM_FAK;   
   TableLogRWTH[53].pAdresse = (void*)&Soll_IBF.Radial.Cr.d;
   
   //Kanal 1054:
   TableLogRWTH[54].type     = 3;   
   TableLogRWTH[54].faktor   = f_FAK;   
   TableLogRWTH[54].pAdresse = (void*)&Soll_IBF.Radial.Cr.e;
   
   //Kanal 1055:
   TableLogRWTH[55].type     = 3;   
   TableLogRWTH[55].faktor   = f_FAK;   
   TableLogRWTH[55].pAdresse = (void*)&Soll_IBF.Radial.Cr.o;
   
   //Kanal 1056:
   TableLogRWTH[56].type     = 3;   
   TableLogRWTH[56].faktor   = f_FAK;   
   TableLogRWTH[56].pAdresse = (void*)&Soll_IBF.Radial.Cr.u;
   
   //Kanal 1057:
   TableLogRWTH[57].type     = 3;   
   TableLogRWTH[57].faktor   = f_FAK;   
   TableLogRWTH[57].pAdresse = (void*)&Soll_IBF.Radial.Cr.g;
   
   //Kanal 1058:
   TableLogRWTH[58].type     = 3;   
   TableLogRWTH[58].faktor   = f_FAK;   
   TableLogRWTH[58].pAdresse = (void*)&Soll_IBF.Radial.Cr.f;
   
   //Kanal 1059:
   TableLogRWTH[59].type     = 1;   
   TableLogRWTH[59].faktor   = 0;   
   TableLogRWTH[59].pAdresse = (void*)&Soll_IBF.Radial.Cr.os_i;
   
   //Kanal 1060:
   TableLogRWTH[60].type     = 3;   
   TableLogRWTH[60].faktor   = MM_FAK;   
   TableLogRWTH[60].pAdresse = (void*)&Soll_IBF.Radial.Cr.Array[0];
   
   //Kanal 1061:
   TableLogRWTH[61].type     = 3;   
   TableLogRWTH[61].faktor   = MM_FAK;   
   TableLogRWTH[61].pAdresse = (void*)&Soll_IBF.Radial.Cr.Array[1];
   
   //Kanal 1062:
   TableLogRWTH[62].type     = 3;   
   TableLogRWTH[62].faktor   = MM_FAK;   
   TableLogRWTH[62].pAdresse = (void*)&Ist_IBF.ASO_Pos_Start;
   
   //Kanal 1063:
   TableLogRWTH[63].type     = 3;   
   TableLogRWTH[63].faktor   = MM_FAK;   
   TableLogRWTH[63].pAdresse = (void*)&Ist_IBF.Rohling_s_angefahren;
   
   //Kanal 1064:
   TableLogRWTH[64].type     = 3;   
   TableLogRWTH[64].faktor   = MM_FAK;   
   TableLogRWTH[64].pAdresse = (void*)&Ist_IBF.Rohling_h_angefahren;



   //Kanal 1065 bis 1069 freigehalten

   // Ringgeometrie
   //Kanal 1070
   TableLogRWTH[70].type     = 3;   
   TableLogRWTH[70].faktor   = f_FAK;   
   TableLogRWTH[70].pAdresse = (void*)&Ist_Inter.da;

   //Kanal 1071
   TableLogRWTH[71].type     = 3;   
   TableLogRWTH[71].faktor   = f_FAK;   
   TableLogRWTH[71].pAdresse = (void*)&Ist_Inter.di;
   
   //Kanal 1072
   TableLogRWTH[72].type     = 3;   
   TableLogRWTH[72].faktor   = f_FAK;   
   TableLogRWTH[72].pAdresse = (void*)&Ist_Inter.s1r;
   
   //Kanal 1073
   TableLogRWTH[73].type     = 3;   
   TableLogRWTH[73].faktor   = f_FAK;   
   TableLogRWTH[73].pAdresse = (void*)&Ist_Inter.h1a_of;
  
   //Kanal 1074 bis 1099 freigehalten   


   //Kanal 1100
   TableLogRWTH[100].type     = 3;   
   TableLogRWTH[100].faktor   = 1.0;   
   TableLogRWTH[100].pAdresse = (void*)&Ist_IBF.Axial.Verh_pr_sf_proz_start;

   //Kanal 1101
   TableLogRWTH[101].type     = 3;   
   TableLogRWTH[101].faktor   = 1.0;   
   TableLogRWTH[101].pAdresse = (void*)&Ist_IBF.Axial.Verh_pr_sf_proz;

   //Kanal 1102
   TableLogRWTH[102].type     = 2;   
   TableLogRWTH[102].faktor   = 0.0;   
   TableLogRWTH[102].pAdresse = (void*)&Ist_IBF.Axial.Pr_Num;

   //Kanal 1103
   TableLogRWTH[103].type     = 3;   
   TableLogRWTH[103].faktor   = S_FAK;   
   TableLogRWTH[103].pAdresse = (void*)&Soll_Inter.kwo_n;

   //Kanal 1104
   TableLogRWTH[104].type     = 3;   
   TableLogRWTH[104].faktor   = S_FAK;   
   TableLogRWTH[104].pAdresse = (void*)&Soll_Inter.kwu_n;

   //Kanal 1105
   TableLogRWTH[105].type     = 3;   
   TableLogRWTH[105].faktor   = S_FAK;   
   TableLogRWTH[105].pAdresse = (void*)&Ist_Inter.kwo_n;
   
   //Kanal 1106
   TableLogRWTH[106].type     = 3;   
   TableLogRWTH[106].faktor   = S_FAK;   
   TableLogRWTH[106].pAdresse = (void*)&Ist_Inter.kwu_n;

   //Kanal 1107 
   TableLogRWTH[107].type     = 2;   
   TableLogRWTH[107].faktor   = 0.0;   
   TableLogRWTH[107].pAdresse = (void*)&Ist_IBF.Axial.Profilflag;

   //Kanal 1108 ->
   TableLogRWTH[108].type     = 3;   
   TableLogRWTH[108].faktor   = MM_FAK;   
   TableLogRWTH[108].pAdresse = (void*)&Ist_IBF.Rohling_h_angefahren;

   //Kanal 1109
   TableLogRWTH[109].type     = 2;   
   TableLogRWTH[109].faktor   = 0.0;   
   TableLogRWTH[109].pAdresse = (void*)&Ist_IBF.Axial.Pr_Num;
  
   //Kanal 1110
   TableLogRWTH[110].type     = 3;   
   TableLogRWTH[110].faktor   = MM_FAK;   
   TableLogRWTH[110].pAdresse = (void*)&Ist_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num];

   //Kanal 1111
   TableLogRWTH[111].type     = 3;   
   TableLogRWTH[111].faktor   = MM_FAK;   
   TableLogRWTH[111].pAdresse = (void*)&Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num];
  
   //Kanal 1112
   TableLogRWTH[112].type     = 3;   
   TableLogRWTH[112].faktor   = L_MM_S_FAK;   
   TableLogRWTH[112].pAdresse = (void*)&Ist_IBF.Axial.Vorschub;
   
   //Kanal 1113
   TableLogRWTH[113].type     = 3;   
   TableLogRWTH[113].faktor   = f_FAK;   
   TableLogRWTH[113].pAdresse = (void*)&Ist_Inter.hw_n;

   //Kanal 1114 -> 1003
   TableLogRWTH[114].type     = 3;   
   TableLogRWTH[114].faktor   = f_FAK;   
   TableLogRWTH[114].pAdresse = (void*)&Ist_Inter.kwo_n;
   
   //Kanal 1115 -> 1004
   TableLogRWTH[115].type     = 3;   
   TableLogRWTH[115].faktor   = f_FAK;   
   TableLogRWTH[115].pAdresse = (void*)&Ist_Inter.kwu_n;
   
   //Kanal 1116 -> 1005
   TableLogRWTH[116].type     = 3;   
   TableLogRWTH[116].faktor   = f_FAK;   
   TableLogRWTH[116].pAdresse = (void*)&Soll_Inter.kwo_n;
   
   //Kanal 1117
   TableLogRWTH[117].type     = 3;   
   TableLogRWTH[117].faktor   = f_FAK;   
   TableLogRWTH[117].pAdresse = (void*)&Soll_Inter.kwu_n;

  //Kanal 1118
   TableLogRWTH[118].type     = 2;   
   TableLogRWTH[118].faktor   = 0.0;   
   TableLogRWTH[118].pAdresse = (void*)&Soll_IBF.Axial.Pr_Num;

   //Kanal 1119
   TableLogRWTH[119].type     = 3;   
   TableLogRWTH[119].faktor   = MM_FAK;   
   TableLogRWTH[119].pAdresse = (void*)&Soll_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num];

   //Kanal 1120
   TableLogRWTH[120].type     = 3;   
   TableLogRWTH[120].faktor   = MM_FAK;   
   TableLogRWTH[120].pAdresse = (void*)&Soll_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num];

   //Kanal 1200
   TableLogRWTH[200].type     = 3;   
   TableLogRWTH[200].faktor   = f_FAK;   
   TableLogRWTH[200].pAdresse = (void*)&Ist_Inter.hw_ir;

   //Kanal 1201
   TableLogRWTH[201].type     = 3;   
   TableLogRWTH[201].faktor   = f_FAK;   
   TableLogRWTH[201].pAdresse = (void*)&Ist_Inter.kw_ia;
   
   //Kanal 1210
   TableLogRWTH[210].type     = 3;   
   TableLogRWTH[210].faktor   = f_FAK;   
   TableLogRWTH[210].pAdresse = (void*)&Ist_Inter.n_hw_motor_ist; 
   
   //Kanal 1211
   TableLogRWTH[211].type     = 3;   
   TableLogRWTH[211].faktor   = f_FAK;   
   TableLogRWTH[211].pAdresse = (void*)&Ist_Inter.n_kwo_motor_ist;
   
   //Kanal 1212
   TableLogRWTH[212].type     = 3;   
   TableLogRWTH[212].faktor   = f_FAK;   
   TableLogRWTH[212].pAdresse = (void*)&Ist_Inter.n_kwu_motor_ist;

   // Ab hier in DATALOGGER EINBINDEN !!!!
   //Kanal 1213
   TableLogRWTH[213].type     = 3;   
   TableLogRWTH[213].faktor   = MM_FAK;   
   TableLogRWTH[213].pAdresse = (void*)&Ist_Inter.ag_pos_real;

   //Kanal 1214
   TableLogRWTH[214].type     = 3;   
   TableLogRWTH[214].faktor   = f_FAK;   
   TableLogRWTH[214].pAdresse = (void*)&Ist_Inter.Werkzeug.Winkelgeschw_omega_HW;

   //Kanal 1215
   TableLogRWTH[215].type     = 3;   
   TableLogRWTH[215].faktor   = f_FAK;   
   TableLogRWTH[215].pAdresse = (void*)&Ist_Inter.Werkzeug.Winkel_grad_tU_HW;

   //Kanal 1216
   TableLogRWTH[216].type     = 3;   
   TableLogRWTH[216].faktor   = f_FAK;   
   TableLogRWTH[216].pAdresse = (void*)&Ist_Inter.Werkzeug.tU_HW;

    //Kanal 1217
   TableLogRWTH[217].type     = 3;   
   TableLogRWTH[217].faktor   = f_FAK;   
   TableLogRWTH[217].pAdresse = (void*)&Ist_Inter.Werkzeug.U_v_HW;

    //Kanal 1218
   TableLogRWTH[218].type     = 3;   
   TableLogRWTH[218].faktor   = f_FAK;   
   TableLogRWTH[218].pAdresse = (void*)&Ist_Inter.Werkzeug.Ringumdrehung;

    //Kanal 1219
   TableLogRWTH[219].type     = 3;   
   TableLogRWTH[219].faktor   = f_FAK;   
   TableLogRWTH[219].pAdresse = (void*)&Ist_Inter.Werkzeug.omega_Ring;

    //Kanal 1220
   TableLogRWTH[220].type     = 3;   
   TableLogRWTH[220].faktor   = f_FAK;   
   TableLogRWTH[220].pAdresse = (void*)&Ist_Inter.Werkzeug.Winkel_grad_tU_Ring;
   
    //Kanal 1221
   TableLogRWTH[221].type     = 1;   
   TableLogRWTH[221].faktor   = 0.0;   
   TableLogRWTH[221].pAdresse = (void*)&Ist_IBF.Test.Flag;

    //Kanal 1222
   TableLogRWTH[222].type     = 3;   
   TableLogRWTH[222].faktor   = MM_FAK;   
   TableLogRWTH[222].pAdresse = (void*)&Ist_IBF.Test.Ring_AD;


      







   return (TRUE);
}