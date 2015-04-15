/*--FILE HEADER---------------------------------------------------------------
;   filename       : RWTH_LOGGER.CPP
;   version        : V1.0
;   contents       : Loggerchannels
;   author         : K. Brauckmann, SMS Eumuco GmbH
;   date           : May, 2004
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   Loggerkanäle
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

//hier alle Klassen einbinden, die Loggerkanäle beinhalten!

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
// Tabelle ausfüllen und erweitern bis auf MAX_LOG_KANAELE_RWTH
// Bedeutung s. LOG_CHANNEL_DEF in RAW_T_POOL.HPP
//
// Die Kanäle müssen auch im WINDOWS-Logger definiert werden!
// Startkanal im WINDOWS-Logger: 1000
/*********************************************************************/

int LOGGER_RWTH::Kanalliste(void)
{
   #define L_MM_S_FAK 1000.0  // mm / s

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

   //Kanal 1004: Test -> Adresse einer globalen Variablen 
   TableLogRWTH[4].type     = 2;   
   TableLogRWTH[4].faktor   = 0.0;   
   TableLogRWTH[4].pAdresse = (void *)&TestCounter[2];

   //Kanal 1005:
   TableLogRWTH[5].type     = 0;   
   TableLogRWTH[5].faktor   = 0.0;   
   TableLogRWTH[5].pAdresse = NULL;

   //Kanal 1006:
   TableLogRWTH[6].type     = 0;   
   TableLogRWTH[6].faktor   = 0.0;   
   TableLogRWTH[6].pAdresse = NULL;

   //Kanal 1007:
   TableLogRWTH[7].type     = 0;   
   TableLogRWTH[7].faktor   = 0.0;   
   TableLogRWTH[7].pAdresse = NULL;

   //Kanal 1008:
   TableLogRWTH[8].type     = 0;   
   TableLogRWTH[8].faktor   = 0.0;   
   TableLogRWTH[8].pAdresse = NULL;

   //Kanal 1009:
   TableLogRWTH[9].type     = 0;   
   TableLogRWTH[9].faktor   = 0.0;   
   TableLogRWTH[9].pAdresse = NULL;

   //Kanal 1010:
   TableLogRWTH[10].type     = 3;   
   TableLogRWTH[10].faktor   =  L_MM_S_FAK;   
   TableLogRWTH[10].pAdresse = (void *) &aus_onli.ds_dh_sp_hp.s_punkt;

   return (TRUE);
}
