/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : RMDEF.H
;   version     : 0005
;   contents    : Include-File for RMOS API functions
;   author      : K.P.H.
;   date        : Dec 12, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Macro definitions for RMOS API functions
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Jan 19, 1995  P.F.   0001  Original issue
;   Apr 20, 1995  K.P.H. 0002  Additional changes for RMOS2
;   Aug 16, 1995  K.P.H. 0003  Modification for RMOS V3.12
;   Dec 15, 1995  K.P.H. 0004  Additional Modification
;   Dec 05, 1996  K.P.H. 0005  Added RM_IH_IDT
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _RMDEF_H_
#define _RMDEF_H_

#ifndef _PROT_H_
#include <prot.h>
#endif  /* _PROT_H_ */
#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */


#if defined(_ARCHITECTURE_) || defined(CADUL)
#ifndef _NOVERS
static const
char idstr_rmdef_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"    /* In-code identification. */
        "\1"    "RMDEF.H"               "\1"
        "\2"    "0004"                  "\2"
        "\3"    "K.P.H."                "\3"
};
#endif
#endif  /* defined(_ARCHITECTURE_) || defined(CADUL) */


  /**************************************************************************/
  /*                        General macro definitions                       */
  /**************************************************************************/

#ifndef FALSE
#define FALSE                           0
#endif

#ifndef TRUE
#define TRUE                            (~FALSE)
#endif

#define RM_TRUE                         -1
#define RM_FALSE                        0


  /**************************************************************************/
  /*                          RMOS API error codes                          */
  /**************************************************************************/

#define RM_OK                           0
                         /* SVC messages */
#define RM_ERROR_OUT_OF_RANGE           -265
#define RM_ENTRY_REMOVED                -263
#define RM_TASK_WAITING                 -262
#define RM_PRI_NOT_CHANGED              -261
#define RM_FLAG_RESET                   -260
#define RM_FLAG_SET                     -259
#define RM_FLAG_ALREADY_SET             -258
#define RM_TASK_RESUMED                 -256
                         /* SVC errors */
#define RM_SYSTEMERROR                  1
#define RM_PARAMETER_ERROR              2
#define RM_OUT_OF_MEMORY                3
#define RM_GOT_TIMEOUT                  4
#define RM_INVALID_DESCRIPTOR           5
#define RM_INVALID_SEGMENTLENGTH        6
#define RM_TASK_DORMANT                 7
#define RM_GDT_FULL                     9
#define RM_INVALID_NULLPOINTER          10
#define RM_OUT_OF_BYTEGROUPS            11
#define RM_OUT_OF_FLAGGROUPS            12
#define RM_OUT_OF_MEMORYPOOLS           13
#define RM_HEAP_NOT_REDEFINEABLE        14
#define RM_OUT_OF_MAILBOXES             15
#define RM_OUT_OF_SEMAPHORES            16
#define RM_INVALID_MEMORYBLOCK          17
#define RM_RESOURCE_BUSY                18
#define RM_TASK_NOT_DORMANT             20
#define RM_INVALID_SELECTOR             21
#define RM_INVALID_TASK_STATE           22
#define RM_RESOURCE_NOT_AVAILABLE       23
#define RM_MEMORY_ALREADY_USED          25
#define RM_TASK_NOT_PAUSED              26
#define RM_BOUND_REACHED                27
#define RM_BREAKPOINT_ID_ALREADY_USED   28
#define RM_BREAKPOINT_ALREADY_SET       29
#define RM_TASK_NOT_READY               30
#define RM_TASK_NOT_IN_BP_CONTEXT       31
#define RM_TASK_NOT_IN_RTE_HALT         32
#define RM_SVC_NOT_CONFIGURED           33
#define RM_INVALID_TYPE                 35
#define RM_INVALID_ID                   36
#define RM_INVALID_STRING               37
#define RM_INVALID_SIZE                 38
#define RM_INVALID_OFFSET               39
#define RM_INVALID_IRQ_NUMBER           41
#define RM_INVALID_POINTER              42
#define RM_NO_MESSAGE                   43
#define RM_INVALID_FUNCTION             44
#define RM_ALL_DEBUGREGISTERS_USED      45
#define RM_NOT_HALTABLE                 46
#define RM_IS_ALREADY_CATALOGED         47
#define RM_IS_NOT_CATALOGED             48
#define RM_TASK_KILLED                  49
#define RM_LINKTIMER_FULL               50
#define RM_INVALID_POOL_CFG             51
#define RM_INVALID_CFG_STATE            52
#define RM_NO_EOI                       53
#define RM_NO_INIT_TIMER                54
#define RM_SYNTAX_ERROR	                55
#define RM_INVALID_INTERRUPT_NUMBER     56
#define RM_TEST_NOT_OK                  57
#define RM_QUEUE_NOT_EXIST              58
#define RM_QUEUE_EXIST                  59
#define RM_INVALID_TASK_ENTRY           60
#define RM_LINE_TOO_LONG                61
#define RM_INVALID_SECTION_DECLARATION  62
#define RM_UNKNOWN_SECTION	        63
#define RM_STATEMENT_OUTSIDE_SECTION    64
#define RM_INVALID_SECTION_NAME	        65
#define RM_INVALID_DCD_SEGMENT	        66

#define RM_CATALOG_EXCEEDED             100


  
  /**************************************************************************/
  /*                  Constant names for RMOS API functions                 */
  /**************************************************************************/

                /* Constant values for misc API functions */

#define RM_MAXCATALOGLEN            15u
#define RM_MAXEXTCATALOGLEN         60u
#define RM_MAXDECODELEN             81


                     /* Constant values for messages */

#define RM_MSG_USER                 0x8000u
#define RM_MSG_MAX                  0xFFFFu


                  /* Constant values for priority types */

#define RM_TCDPRI                   (4u<<8u)
#define RM_CURPRI                   (3u<<8u)
#define RM_MAXPRI                   (1u<<8u)
#define RM_INCPRI                   (5u<<8u)
#define RM_DECPRI                   (6u<<8u)


                     /* Constant values for task ids */

#define RM_MAXTASKID                (uint) -2
#define RM_OWN_TASK                 (uint) -1


                      /* Constant values for timeout */

#define RM_CONTINUE                 0ul
#define RM_WAIT                     (ulong) -1
#define RM_MAXTIME                  0x7FFFFFFFul


                /* Constant values for timeout and RmPause */

#define RM_MILLISECOND(s)           ((ulong) (s))
#define RM_SECOND(s)                ((ulong) ((s) * 1000ul))
#define RM_MINUTE(s)                ((ulong) ((s) * 60000ul))
#define RM_HOUR(s)                  ((ulong) ((s) * 3600000ul))
/* RM_MICROSECOND is not combinable with above ones */
#define RM_MICROSECOND(s)           ((ulong) ((s) | 0x80000000ul))


                /* Constant values for RmTCDStruct.time */

#define RM_TCD_MSEC_1               (uchar) 0
#define RM_TCD_MSEC_10              (uchar) 1
#define RM_TCD_MSEC_100             (uchar) 2
#define RM_TCD_SEC                  (uchar) 3
#define RM_TCD_SEC_10               (uchar) 6
#define RM_TCD_MIN                  (uchar) 4
#define RM_TCD_MIN_10               (uchar) 7 
#define RM_TCD_HOUR                 (uchar) 5


                    /* Constant values for wait types */

#define RM_NO_WAIT                  0u
#define RM_WAIT_READY               1u
#define RM_WAIT_END                 2u


        /* Constant values for API functions RmAlloc and RmReAlloc */

#define RM_FLATALLOC                0x000Cu
#define RM_AUTOFREE                 0x0000u
#define RM_NOAUTOFREE               0x0002u


           /* Constant values for API functions RmMemPoolInfo */

#define RM_HEAP                     0u


               /* Constant values for catalog API functions */

#define RM_CATALOG_TASK             0u              /* catalog type task      */
#define RM_CATALOG_DEVICE           1u              /* catalog type device    */
#define RM_CATALOG_POOL             2u              /* catalog type mem pool  */
#define RM_CATALOG_SEMAPHORE        3u              /* catalog type semaphore */
#define RM_CATALOG_EVENTFLAG        4u              /* catalog type eventflag */
#define RM_CATALOG_CNTRL            5u              /* catalog type contr. pr.*/
#define RM_CATALOG_LOCALMAILBOX     6u              /* catalog type local mbox*/
#define RM_CATALOG_MISC             7u              /* catalog no spec. type  */
#define RM_CATALOG_USER             8u              /* catalog no spec. type  */
#define RM_CATALOG_DSCRTE           9u              /* catalog type disc. Byte*/
#define RM_CATALOG_UNIT             10u             /* catalog type unit      */
#define RM_CATALOG_MESSAGE          11u             /* catalog type message   */
#define RM_CATALOG_SYSTEM           12u             /* catalog type system    */
#define RM_CATALOG_ALL              0xFFu           /* catalog type all       */
#define RM_CATALOG_HIDDEN           0x80u
#define RM_CATALOG_EXTENDED         0x40u

               /* Constant values for API function RmDecode */

#define RM_SVCERROR                 0x01u
#define RM_SVCNAME                  0x02u
#define RM_OLDSVCNAME               0x04u

               /* Constant values for API function RmASCIIDecode */

#define RM_MAX_CFG_LINE_LENGTH		256
#define RM_MAX_SECTION_NAME_LENGTH	16

              /* Constant values for API function RmGetFlag */

#define RM_TEST_ALL                 0u              /* test for all bits      */
#define RM_TEST_ONE                 1u              /* test for just one bit  */


              /* Constant values for API function RmKillTask */

#define RM_TASK_END                 0u              /* end option             */
#define RM_TASK_DELETE              1u              /* delete option          */


            /* Constant values for API function RmRestartTask */

#define RM_LAST_READY_TIME          0u
#define RM_CURRENT_TIME             1u


               /* Constant values for API function RmSetOS */

#define RM_SVCEXC_ON                1u
#define RM_SVCEXC_OFF               0u
#define RM_SVCEXC_UNCHANGED         (uint) -1

#define RM_RR_OFF                   0u
#define RM_RR_TASK                  (uint) -1
#define RM_RR_UNCHANGED             (uint) -2


                      /* types of interrupt handler */

#define RM_IH_CUR                   0u           /* read old handler          */
#define RM_IH_DFT                   1u           /* take handler for unx. int.*/
#define RM_IH_DI                    2u           /* DI- handler               */
#define RM_IH_I                     3u           /* I - handler               */
#define RM_IH_S                     4u           /* S - handler               */
#define RM_IH_IS                    5u           /* I - handler and S-handler */
#define RM_IH_TSK                   6u           /* task start with int. hdler*/
#define RM_IH_MBOX                  7u           /* send message handler      */
#define RM_IH_IDT                   8u           /* direct handler            */
#define RM_IH_HW                    0u           /* Hardware Interrupt        */
#define RM_IH_SW                    0x80u        /* Software Interrupt        */


                  /* Constant values for IRQ definition */

#define RM_IRQ_TAG              0x8000u
#define IRQ(n)                  ( (((n)&0xF8u)<<5u) | (n&7u) | RM_IRQ_TAG )
#define IRQ0                    (0x0000u | RM_IRQ_TAG)
#define IRQ1                    (0x0001u | RM_IRQ_TAG)
#define IRQ2                    (0x0002u | RM_IRQ_TAG)
#define IRQ3                    (0x0003u | RM_IRQ_TAG)
#define IRQ4                    (0x0004u | RM_IRQ_TAG)
#define IRQ5                    (0x0005u | RM_IRQ_TAG)
#define IRQ6                    (0x0006u | RM_IRQ_TAG)
#define IRQ7                    (0x0007u | RM_IRQ_TAG)

#define IRQ8                    (0x0100u | RM_IRQ_TAG)
#define IRQ9                    (0x0101u | RM_IRQ_TAG)
#define IRQ10                   (0x0102u | RM_IRQ_TAG)
#define IRQ11                   (0x0103u | RM_IRQ_TAG)
#define IRQ12                   (0x0104u | RM_IRQ_TAG)
#define IRQ13                   (0x0105u | RM_IRQ_TAG)
#define IRQ14                   (0x0106u | RM_IRQ_TAG)
#define IRQ15                   (0x0107u | RM_IRQ_TAG)

#define IRQ16                   (0x0200u | RM_IRQ_TAG)
#define IRQ17                   (0x0201u | RM_IRQ_TAG)
#define IRQ18                   (0x0202u | RM_IRQ_TAG)
#define IRQ19                   (0x0203u | RM_IRQ_TAG)
#define IRQ20                   (0x0204u | RM_IRQ_TAG)
#define IRQ21                   (0x0205u | RM_IRQ_TAG)
#define IRQ22                   (0x0206u | RM_IRQ_TAG)
#define IRQ23                   (0x0207u | RM_IRQ_TAG)

#define IRQ24                   (0x0300u | RM_IRQ_TAG)
#define IRQ25                   (0x0301u | RM_IRQ_TAG)
#define IRQ26                   (0x0302u | RM_IRQ_TAG)
#define IRQ27                   (0x0303u | RM_IRQ_TAG)
#define IRQ28                   (0x0304u | RM_IRQ_TAG)
#define IRQ29                   (0x0305u | RM_IRQ_TAG)
#define IRQ30                   (0x0306u | RM_IRQ_TAG)
#define IRQ31                   (0x0307u | RM_IRQ_TAG)

#define IRQ32                   (0x0400u | RM_IRQ_TAG)
#define IRQ33                   (0x0401u | RM_IRQ_TAG)
#define IRQ34                   (0x0402u | RM_IRQ_TAG)
#define IRQ35                   (0x0403u | RM_IRQ_TAG)
#define IRQ36                   (0x0404u | RM_IRQ_TAG)
#define IRQ37                   (0x0405u | RM_IRQ_TAG)
#define IRQ38                   (0x0406u | RM_IRQ_TAG)
#define IRQ39                   (0x0407u | RM_IRQ_TAG)

#define IRQ40                   (0x0500u | RM_IRQ_TAG)
#define IRQ41                   (0x0501u | RM_IRQ_TAG)
#define IRQ42                   (0x0502u | RM_IRQ_TAG)
#define IRQ43                   (0x0503u | RM_IRQ_TAG)
#define IRQ44                   (0x0504u | RM_IRQ_TAG)
#define IRQ45                   (0x0505u | RM_IRQ_TAG)
#define IRQ46                   (0x0506u | RM_IRQ_TAG)
#define IRQ47                   (0x0507u | RM_IRQ_TAG)

#define IRQ48                   (0x0600u | RM_IRQ_TAG)
#define IRQ49                   (0x0601u | RM_IRQ_TAG)
#define IRQ50                   (0x0602u | RM_IRQ_TAG)
#define IRQ51                   (0x0603u | RM_IRQ_TAG)
#define IRQ52                   (0x0604u | RM_IRQ_TAG)
#define IRQ53                   (0x0605u | RM_IRQ_TAG)
#define IRQ54                   (0x0606u | RM_IRQ_TAG)
#define IRQ55                   (0x0607u | RM_IRQ_TAG)

#define IRQ56                   (0x0700u | RM_IRQ_TAG)
#define IRQ57                   (0x0701u | RM_IRQ_TAG)
#define IRQ58                   (0x0702u | RM_IRQ_TAG)
#define IRQ59                   (0x0703u | RM_IRQ_TAG)
#define IRQ60                   (0x0704u | RM_IRQ_TAG)
#define IRQ61                   (0x0705u | RM_IRQ_TAG)
#define IRQ62                   (0x0706u | RM_IRQ_TAG)
#define IRQ63                   (0x0707u | RM_IRQ_TAG)

                            /* task flag bits */

#define RM_TFL_NPX                  0x0001u         /* task uses npx                        */
#define RM_TFL_NOHLT                0x0004u         /* task may not be halted (a debugger)  */
#define RM_TFL_OVPRI                0x0008u         /* override priority after time expires */
#define RM_TFL_NEW_IF               0x0010u         /* svc call from new interface          */
#define RM_TFL_CHILD                0x0040u         /* task is child of creating task       */
                                                    /* CRUN inheritance is called           */
#define RM_TFL_ALLOC                0x0080u         /* tcd/tcb combination was allocated from */
                                                    /* the smr (dynamically created task)   */
#define RM_TFL_STK                  0x0100u         /* automatic stack segment allocation   */
                                                    /* length in dwords is in tcd_esp       */
#define RM_TFL_DS                   0x0200u         /* automatic data segment allocation    */
                                                    /* length is intcd_ds                   */


                    /* define the possible task states */

#define RM_READY                    1u              /* task in ready state    */
#define RM_DORMANT                  0u              /* task is dormant        */
#define RM_ACTIVE                   3u              /* task is active         */
#define RM_BLOCKED                  2u              /* task waits for I/O     */
#define RM_NOTEXISTENT              255u            /* task doesn't exist     */


                /* Additional information if task blocked */

#define RM_STA_EF               4                   /* event flag wait                 */
#define RM_STA_SEMA             (RM_STA_EF+4)       /* semaphore or control wait       */
#define RM_STA_LOAD             (RM_STA_SEMA+4)     /* reserved                        */
#define RM_STA_STRT             (RM_STA_LOAD+4)     /* wait for target to start        */
#define RM_STA_ENDT             (RM_STA_STRT+4)     /* wait for target to terminate    */
#define RM_STA_MSG              (RM_STA_ENDT+4)     /* wait to receive message         */
#define RM_STA_MSGRCVD          (RM_STA_MSG+4)      /* wait for own message to be received */
#define RM_STA_POOL             (RM_STA_MSGRCVD+4)  /* wait for allocatable memory     */
#define RM_STA_HLT              (RM_STA_POOL+4)     /* debugger halted, task suspended */
#define RM_STA_BREAK            (RM_STA_HLT+4)      /* debugger breakpointed           */
#define RM_STA_PAUSE            (RM_STA_BREAK+4)    /* in pause condition              */
#define RM_STA_TSKSTCK          (RM_STA_PAUSE+4)    /* invalid task stack selector     */
#define RM_STA_WAIT             (RM_STA_TSKSTCK+4)  /* awaiting i/o completion         */
#define RM_STA_ABORT            (RM_STA_WAIT+4)     /* reserved                        */
#define RM_STA_SVC              (RM_STA_ABORT+4)    /* reserved                        */
#define RM_STA_ENDR             (RM_STA_SVC+4)      /* awaiting timed "restart"        */
#define RM_STA_ERR0             (RM_STA_ENDR+4)     /* run time error, exception  0    */
#define RM_STA_ERR1             (RM_STA_ERR0+4)     /*  "   "     "    exception  1    */
#define RM_STA_ERR2             (RM_STA_ERR1+4)     /*  "   "     "    exception  3    */
#define RM_STA_ERR3             (RM_STA_ERR2+4)     /*  "   "     "    exception  4    */
#define RM_STA_ERR4             (RM_STA_ERR3+4)     /*  "   "     "    exception  5    */
#define RM_STA_ERR5             (RM_STA_ERR4+4)     /*  "   "     "    exception  6    */
#define RM_STA_ERR6             (RM_STA_ERR5+4)     /*  "   "     "    exception  7    */
#define RM_STA_ERR7             (RM_STA_ERR6+4)     /*  "   "     "    exception  8    */
#define RM_STA_ERR8             (RM_STA_ERR7+4)     /*  "   "     "    exception  9    */
#define RM_STA_ERR9             (RM_STA_ERR8+4)     /*  "   "     "    exception 13    */
#define RM_STA_ERR10            (RM_STA_ERR9+4)     /*  "   "     "    exception 16    */
#define RM_STA_ERR11            (RM_STA_ERR10+4)    /*  "   "     "    exception 10    */
#define RM_STA_ERR12            (RM_STA_ERR11+4)    /*  "   "     "    exception 11    */
#define RM_STA_ERR13            (RM_STA_ERR12+4)    /*  "   "     "    exception 12    */
#define RM_STA_ERR14            (RM_STA_ERR13+4)    /*  "   "     "    exception 14    */
#define RM_STA_ERR15            (RM_STA_ERR14+4)    /*  "   "     "    exception 17    */
#define RM_LAST_ERR             RM_STA_ERR15
#define RM_RES_ERR              (RM_STA_ERR0+(31<<2))/*reserve some run time errors    */
#define RM_STA_LOOK             (RM_RES_ERR+4)      /* wait for string to be cataloged */
#define RM_STA_KEND             (RM_STA_LOOK+4)     /* task killed with end option     */
#define RM_STA_KDEL             (RM_STA_KEND+4)     /* task killed with delete option  */


                /*  macros for specific RMOS3-systemcalls */

#ifndef ACS_ER
#define ACS_ER                      0x9Au
#define ACS_RW                      0x92u
#define ACS_RD                      0x96u
#define ACS_RWD                     0x96u
#endif /* ACS_ER */


                     /*  task flags when using create */

#define RM_TCD_NPX                  0x0001u         /* task uses npx                */
#define RM_TCD_NOHALT               0x0004u         /* task may not be halted       */
#define RM_TCD_OVERRIDE_PRIORITY    0x0008u         /* override priority            */
#define RM_TCD_NEW_INTERFACE        0x0010u         /* svc call from new interface  */
#define RM_TCD_ALLOC                0x0080u         /* tcd/tcb combination was      */
                                                    /* allocated from the smr (dynamically created task) */
#define RM_TCD_ALLOCATE_STACK       0x0100u         /* auto stack allocation        */
#define RM_TCD_ALLOCATE_DS          0x0200u         /* auto data segment allocation */


           /*  breakpoint type definitions when using db_sbreak */

#ifndef BP_HARD
#define BP_HARD                     0x00u    /* INT3 Hard-Breakpoint   */
#define BP_SOFT                     0x01u    /* INT3 Soft-Breakpoint   */
#define BP_EXEC                     0x80u    /* Execution-Breakpoint   */
#define BP_WRITE_BYTE               0x88u    /* Write Byte Breakpoint  */
#define BP_WRITE_WORD               0xA8u    /* Write Word Breakpoint  */
#define BP_WRITE_DWORD              0xE8u    /* Write Dword Breakpoint */
#define BP_MODIFY_BYTE              0x98u    /* Read or Write Byte Breakpoint */
#define BP_MODIFY_WORD              0xB8u    /* Read or Write Word Breakpoint */
#define BP_MODIFY_DWORD             0xF8u    /* Read or Write Dword Breakpoint*/
#endif /* BP_HARD */


                /* Flags for 'flags' field of RmDCDStruct */

#define RM_DFL_PARA                 (uchar) 1       /* parallel driver        */
#define RM_DFL_TYPE2                (uchar) 2       /* type 2 driver          */
#define RM_DFL_DORMANT              (uchar) 4       /* driver dormant         */

                /* Symbols used for dynamic resources */

#define	RM_IL_DYN                   0               /* "IN LIST"-IDENTIFIER.  */
#define	RM_NIL_DYN	            (uint) -1       /* "NOT IN LIST"-IDENTIFIER */
#define	RM_DEV_DORMANT	            (uint) -1       /* DEVICE DRIVER DORMANT. */

                 /* Flags for 'pid' field of RmUCDStruct */

#define RM_RIOBYTE                  (uchar) 0x40    /* RmIO byte unit type    */
#define RM_RIOBLOCK                 (uchar) 0x80    /* RmIO block unit type   */


                         /* Defines for busy task */

#define RM_BUSY_OK                  0
#define RM_BUSY_FAILED              -1


                         /* Defines for RmSysB */

#define RM_SYSTEM_RMOS2             2
#define RM_SYSTEM_RMOS3             3
#define RM_SYSTEM_R4WIN             4


                        /* miscellaneus defines */

#define RM_CR_INHERITANCE           0x1000u
#define RM_CR_REMOVE_INHERITANCE    0x2000u
#define RM_CR_ENDTASK               0x0001u
#define RM_CR_DELETETASK            0x0004u

#define RM_DEB_DB_CONT              0x4000u

#define RM_DEL_TASKHAND             0x0000u
#define RM_INS_TASKHAND             0x0001u

#define RM_BO_DEV                   -1u		/* BLOCK OWNER CODE DEVICE DRIVER */
#define RM_BO_TASK_STACK            -2u		/* BLOCK OWNER CODE TASK STACK */
#define RM_BO_TASK_DS               -3u		/* BLOCK OWNER CODE TASK DS */
#define RM_BO_NONE                  -4u		/* BLOCK OWNER CODE NO OWNER */

#define RM_SMR_SIZE                 sizeof(RmTCBStruct)
#define RM_USER_INT                 245u

#endif /* _RMDEF_H_ */

