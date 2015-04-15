/*--FILE HEADER----------------------------------------------------------------
;
;   filename        : RWTH_TASK.CPP
;   version         : V1.0
;   contents        : Task mangement for technology 
;   author          : K. Brauckmann, SMS Eumuco GmbH
;   date            : May, 2006
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Main-Task RWTH
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   May , 10. 2006  0001  K.B.  original issue
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

/****************************************************************************/
/*  includes                                                                */
/****************************************************************************/
/* includes from outside the project */
#include "../inc/rmos_inc.h"
#include <stdio.h>

const char far strgFlag[] = "RWTH_FLAG";
const char far strgRWTH_Task[] = "RWTH_TASK";

#define  MainModul  
#include "../inc/rwth_task.hpp"
#include "../inc/test_ibf.hpp"

#ifndef RWTH_Version
 #error Keine Versionsinformation in RWTH_TASK.HPP!
#endif

void _FAR RWTH_Task(void); 

void _FAR main (void)
{
    int Status;
    uint                CurrentFlag;
    uint                RWTH_tid;

    for(int i=0; i<20; i++)
        TestCounter[i] = 0;


	FILE* fp;
	fp = fopen("C:\\RWTH_LOG.txt","w");
	fprintf(fp,"lawl");
	fclose(fp);

    MyLogFile.open("RWTH_LOG1.TXT");
    MyLogFile << "RWTH-Task - Version: " << RWTH_Version << endl << endl;
    cout << "INIT RWTH_TASK" << endl;
    MyLogFile << "INIT RWTH_TASK" << endl;
    Status  = RmCreateFlagGrp(strgFlag, &FlagId);
    svc_sts (1001, "RmCreateFlagGrp RWTH", Status);

    Status=RmCreateTask(strgRWTH_Task,STACK_SIZE,PRIO_RWTH,(rmfarproc)RWTH_Task,&RWTH_tid);
    svc_sts(1010,"RmCreateTask RWTH",Status);
    cout << "RWTH_Task hat die Task-ID: " << hex <<  RWTH_tid << endl;
    MyLogFile << "RWTH_Task hat die Task-ID: " << hex <<  RWTH_tid << endl;

    Logger    = new LOGGER_RWTH;
    rwth_exch = new RWTH_EXCH;

    rpw       = new RPW;    //Initialisierung der Klasse RPW (Aufruf Konstruktor)
    

    for(int i = 0; i < 4; i++)
        tmode[i] = new TEST_IBF;

    if(rwth_exch->running_flag)
    {
      Logger->Kanalliste();             //Variablenadressen in Loggertabelle eintragen

      Status=RmStartTask(RM_WAIT_READY,RWTH_tid,PRIO_RWTH,0,0);
      svc_sts(1020,"RmStartTask RWTH",Status);
      cout << "RWTH_Task ist gestartet." << endl;
      MyLogFile << "RWTH_Task ist gestartet." << endl;
        
      cout << "INIT RWTH_TASK waits on Flaggroup " << hex << FlagId << endl << endl;
      MyLogFile << "INIT RWTH_TASK waits on Flaggroup " << hex << FlagId << endl << endl;

      MyLogFile.close();
      Status    = RmGetFlag(RM_WAIT, RM_TEST_ONE, FlagId, FLAG1, &CurrentFlag);
      svc_sts   (1002, "RmGetFlag RWTH", Status);
    }
    else
      MyLogFile.close();

    RmDeleteTask(RWTH_tid);     

    for(int i = 0; i < 4; i++)
        delete tmode[i];

    delete rwth_exch;
    delete Logger;

    delete rpw;      // Freigabe des Speichers (Destruktor)

    cout << "RWTH TASK has been deleted!" << endl << endl;

    Status  = RmDeleteFlagGrp(FlagId);
    svc_sts (1004, "RmDeleteFlagGrp RWTH", Status);

    exit(0);
}

/****************************************************************************/
//  function:    RWTH Task                                       
/****************************************************************************/
void _FAR RWTH_Task(void)
{
    //Laufzeittest auf high word von TeDa[0][0]
    //wird von 10ms Task abgefragt
    *(((short *) &rwth_exch->TeDat.TeDa[0][0])+1) = 1;

    rwth_exch->get_puff();
    rwth_exch->Main_Control();
    rwth_exch->put_puff();

    for(int i= 0; i < 4; i++)
       tmode[i]->WRITE_VALUES(&rwth_exch->TeDat.TeDa[i][0],
                              &rwth_exch->TeDat.Teststring[i][0],
                              sizeof(rwth_exch->TeDat.Teststring[0]));

    *(((short *) &rwth_exch->TeDat.TeDa[0][0])+1) = 0;

    if(rwth_exch->running_flag && !rwth_exch->finish_flag)
        RmRestartTask(RM_LAST_READY_TIME, RM_MILLISECOND(RWTH_Abtastzeit));
    else
    {
        RmSetFlag(FlagId, FLAG1);
        RmEndTask();
    }

} 


/****************************************************************************/
//  function:    error output
/****************************************************************************/
void svc_sts (unsigned int index, char *svc_txt, int status)
{
    char buf[RM_MAXDECODELEN];
    if (status >0)
        {
        printf  ("\nERROR: %s  INDEX: %i  CODE: %i", svc_txt, index, status);
        if (RmDecode(RM_SVCERROR, status, buf) == RM_OK)
            printf  (" = %s\n", buf);
        else
            printf  ("\n");
        }
}
