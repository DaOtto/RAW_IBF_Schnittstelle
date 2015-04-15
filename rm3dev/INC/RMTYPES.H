/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : RMTYPES.H
;   version     : 0005
;   contents    : Include-File for RMOS API functions
;   author      : K.P.H.
;   date        : Sep 13, 1995
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Type definitions for RMOS API functions
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Jan 25, 1995  P.F.   0001  Original issue
;   Mar 09, 1995  K.P.H. 0002  Additional Modification for RMOS2
;   May 10, 1995  K.P.H. 0003  Removed unused structures
;   May 17, 1995  K.P.H. 0004  Added some FLAT support
;   Sep 13, 1995  K.P.H. 0005  Modification for RMOS V3.12
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _RMTYPES_H_
#define _RMTYPES_H_

#ifndef _PROT_H_
#include <prot.h>
#endif  /* _PROT_H_ */
#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _MISC86_H_
#include <misc86.h>
#endif  /* _MISC86_H_ */

#if ! RMFLAT
#define RMVOIDPTR(n)    void *n
#else
/* add fillword in pointer declaration for FLAT model                      */
#define RMVOIDPTR(n)    void    *n; \
                        ushort  n##_seg
#endif

#if defined(_ARCHITECTURE_) || defined(CADUL)
#ifndef _NOVERS
static const
char idstr_rmtypes_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"    /* In-code identification. */
        "\1"    "RMTYPES.H"             "\1"
        "\2"    "0005"                  "\2"
        "\3"    "K.P.H."                "\3"
};
#endif
#endif  /* defined(_ARCHITECTURE_) || defined(CADUL) */


  /**************************************************************************/
  /*                            Alignment control                           */
  /**************************************************************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma align (_RmMailboxStruct      = 1)
#pragma align (_RmMailIDStruct       = 1)
#pragma align (_RmTCDStruct          = 1)
#pragma align (_RmXTCDStruct         = 1)
#pragma align (_RmTCBStruct          = 1)
#pragma align (_RmSTKStruct          = 1)
#pragma align (_RmTaskInfoStruct     = 1)
#pragma align (_RmTimeStruct         = 1)
#pragma align (_RmEntryStruct        = 1)
#pragma align (_RmExtendedEntryStruct= 1)
#pragma align (_RmMemPoolInfoStruct  = 1)
#pragma align (_RmRCBStruct          = 1)
#pragma align (_RmAbsTimeStruct      = 1)
#pragma align (_RmAsciiTimeStruct    = 1)
#pragma align (_RmIntrhandMailStruct = 1)
#pragma align (_RmSysB               = 1)
#pragma align (_RmIOStatusStruct     = 1)
#pragma align (_RmDCDStruct          = 1)
#pragma align (_RmUCDHeadStruct      = 1)
#pragma align (_RmUCDStruct          = 1)
#pragma align (_RmDCBStruct          = 1)
#pragma align (_RmUCBStruct          = 1)
#pragma align (_RmIRBStruct          = 1)
#pragma align (_RmTMBStruct          = 1)
#pragma align (_RmSystemTables       = 1)
#endif  /* defined(_ARCHITECTURE_) || defined(CADUL) */

#if defined _MSC_VER
#pragma pack(1)         /* set all to byte alignment */
#endif

#ifdef __BORLANDC__
#pragma option -a-      /* set all to byte alignment */
#endif


  /**************************************************************************/
  /*                     Basic type definitions for RMOS                    */
  /**************************************************************************/

#if RM3
#define RM_MODEL _NEAR
#else
#define RM_MODEL _FAR
#endif

typedef unsigned long           longlong[2];

typedef unsigned char           uchar;
typedef unsigned short          ushort;
typedef unsigned int            uint;
typedef unsigned long           ulong;

typedef void (_FAR     _FIXED * rmfarproc) (void);
typedef void (_NEAR    _FIXED * rmnearproc)(void);
typedef void (RM_MODEL _FIXED * rmproc)    (void); /* RMOS2 far, RMOS3 near */ 

  /**************************************************************************/
  /*                 Type definitions for RMOS API functions                */
  /**************************************************************************/

/* Mailbox structure for the SEND and RECV system call */

typedef struct  _RmMailboxStruct
{
    void       *adr;            /* may be address of a mail                 */
#if RMFLAT
    ushort      adr_res;        /* fill word for flat model                 */
#endif
#if RM3
    ushort      pad;            /* pad pointer                              */
#endif
    uint        len;            /* may be length of the mail                */
} RmMailboxStruct;

typedef struct  _RmMailIDStruct
{
    ulong        low;          /* low ID of the mail                        */
    ulong        high;         /* high ID of the mail                       */
} RmMailIDStruct;                                                    


/* TCD structures for the CREATE system call */

typedef struct  _RmTCDStruct
{
    uint        eax;             /* register EAX,EBX,DS,ES                  */
    uint        ebx;
    ushort      ds;
    ushort      es;
    char       *stck;           /* pointer to task stack                    */
#if RMFLAT
    ushort      stck_res;       /* fill word for flat model                 */
#endif
    rmfarproc   task;           /* pointer to task startaddress             */
#if RMFLAT
    ushort      task_res;       /* fill word for flat model                 */
#endif

#if RM3
    char       *load;           /* address of the load descriptor string    */
                                /* for a loadable task, otherwise (char *) 0*/
#if RMFLAT
    ushort      load_res;       /* fill word for flat model                 */
#endif /* RMFLAT */
#else  /* RM3 if RMOS2*/
    uint        efg[2];         /* local eventflag group                    */
#endif /*RM3 */
    ushort      time;           /* override time unit specifier             */
    uchar       ovpri;          /* override priority increment              */
    uchar       bpri;           /* override priority boundary value         */
    uchar       inpri;          /* inherent priority                        */
    uchar       pid;            /* reserved                                 */
    ushort      flags;          /* flags word                               */
    ushort      rr_ticks;       /* task specific round robin count          */
                                /* if X_RR_BOUND is 0x0FFFF                 */
#if RM3
    uint        efg[2];         /* local eventflag group                    */
#endif

#if RM3
    uchar       reserve[4];     /* reserved, 4 Bytes                        */
    uint        seq;            /* sequenced task id to start when actual   */
                                /* task ends                                */
    uint    	seq_to;	        /* task is sequenced to task with id seq_to */
#else
    uchar       reserve[2];     /* reserved, 2 Bytes                        */
#endif
} RmTCDStruct;

typedef struct  _RmXTCDStruct
{
    uint        eax;            /* register EAX,EBX,DS,ES                   */
    uint        ebx;
    ushort      ds;
    ushort      es;
    char       *stck;           /* pointer to task stack                    */
#if RMFLAT
    ushort      stck_res;       /* fill word for flat model                 */
#endif
    rmfarproc   task;           /* pointer to task startaddress             */
#if RMFLAT
    ushort      task_res;       /* fill word for flat model                 */
#endif
    char       *load;           /* address of the load-descriptor-string    */
                                /* for a loadable task, otherwise (char *) 0*/
#if RMFLAT
    ushort      load_res;       /* fill word for flat model                 */
#endif
    char        ovrd_tme_unit;  /* override time unit specifier             */
    char        ovrd_int_num;   /* number of units in override time interval*/
    char        ovrd_prio_inc;  /* override priority increment              */
    char        ovrd_prio_bnd;  /* override priority boundary value         */
    char        inherent_prio;  /* inherent priority                        */
    char        cpu_id;         /* cpu number or 0ffh                       */
    ushort      flags;          /* flags word                               */
    ushort      rr_ticks;       /* task specific round robin count          */
#if RM3
    char        reserve[4];     /* reserved, 8 Bytes                        */
    uint        seq;            /* sequenced task id to start when actual   */
                                /* task ends                                */
    uint        seq_to;         /* task is sequenced to task with id seq_to */
#else
    char        reserve[4];     /* reserved, 4 Bytes                        */
#endif
} RmXTCDStruct;


/* Task (dynamic) control block (TCB) (ONLY FOR INTERNAL USE) */

typedef struct  _RmTCBStruct
{
    struct _RmTCBStruct _NEAR *link; /* forward link or 0                   */
    uchar       pri;            /* priority                                 */
    uchar       state;          /* current state: see below                 */
    uint        esp;            /* current stack offset                     */
    ushort      ss;             /* current stack selector                   */
#if RM3
    uchar       schdl[8];       /* last start time, absolute msec.          */
#else
    uchar       schdl[6];       /* last start time, absolute msec.          */
#endif
    struct _RmRCBStruct _NEAR *qrst;    /* rcb queue head                   */
    struct _RmRCBStruct _NEAR *crcb;    /* current rcb                      */
    struct _RmTMBStruct _NEAR *tmb;     /* tmb for priority override or endr*/
    uchar       pid;            /* reserved                                 */
    uchar       flags;          /* task flags: see below                    */
    uint        msg;            /* message queue                            */
    uint        stmb;           /* offset address of stb (timeout)          */
    struct _RmTCDStruct _FAR  *tcd;    /* tcd far address                   */
#if RMFLAT
    ushort      tcb_res0;       /* reserved                                 */
#endif
    ushort      sel;            /* control address                          */
#if RM3
    ushort      tcb_res1;       /* reserved                                 */
    void _FAR  *cr_tdp;         /* crun task data pointer                   */
    void _FAR  *cr_inhp;        /* crun inheritance pointer                 */
    ushort      tasktype;       /* type of task to call exit functions      */
    ushort      lseg;           /* loader result segment                    */
    void _NEAR *nextsmr;        /* smr chain                                */
#endif
} RmTCBStruct;

/* stack structure of an interrupted or suspended task */

typedef    struct _RmSTKStruct
{
    uint    ds;     /*                    */
#if RM3
    uint    gs;     /*                    */
    uint    fs;     /*                    */
#endif
    uint    es;     /*                    */
    uint    edi;    /*                    */
    uint    esi;    /*                    */
    uint    ebp;    /*                    */
    uint    esp;    /*                    */
    uint    ebx;    /*                    */
    uint    edx;    /*                    */
    uint    ecx;    /*                    */
    uint    eax;    /*                    */
    uint    eip;    /*  SAVED BY INTERRUPT OR SVC INTERFACE. */
    uint    cs;     /*    "                */
    uint    efl;    /*    "                */
} RmSTKStruct;      

/* Status structure for the RmGetTaskInfo system call. */

typedef struct  _RmTaskInfoStruct
{
    uchar       pri;            /* priority of the task                     */
    uchar       state;          /* state of the task                        */
    uint       *sp_ss;          /* current stack pointer address            */
#if RM3
#if RMFLAT
    ushort      sp_ss_res;      /* fill word for flat model                 */
#endif
    longlong    rdy_time;       /* time when task was first ready           */
#else
    uint        rdy_time[3];    /* time when task was first ready           */
#endif
    char        cpu_id;         /* cpu-id                                   */
    char        flg;            /* task flags                               */
    struct _RmTCDStruct *tcd_ptr; /* TCD pointer                            */
#if RMFLAT
    ushort      tcd_ptr_res;    /* fill word for flat model                 */
#endif
} RmTaskInfoStruct;


/* Structure for reading or setting hardware time */

typedef struct  _RmTimeStruct
{
    uchar       day;
    uchar       month;
    ushort      year;
    uchar       hours;
    uchar       minutes;
    uchar       seconds;
} RmTimeStruct;


/* Structure for the RmList and RmGetEntry system calls */

typedef struct _RmEntryStruct
{
    uchar       slen;           /* strlen of the following string           */
    char        string[16];     /* the string itself                        */
    uchar       type;           /* Type of the OS-Ressource                 */
    ulong       ide;            /* extended identification number of the type */
    ushort      id;             /* Identification number of the type        */
} RmEntryStruct;

typedef struct _RmExtendedEntryStruct
{
    uchar       slen;           /* strlen of the following string           */
    char        string[10];     /* the code string                          */
    char       *text;           /* pointer to the long string               */
    uchar       type;           /* Type of the OS-Ressource                 */
    ulong       ide;            /* extended identification number of the type */
    ushort      id;             /* Identification number of the type        */
} RmExtendedEntryStruct;
                     
                     
/* Structure for the RmMemPoolInfo system call */

typedef struct _RmMemPoolInfoStruct
{   
    ulong       pool_size;      /* total size of pool                       */
    ulong       avail_mem_size; /* available memory                         */
    ulong       max_block_size; /* size of biggest block                    */
    ulong       reserved[5];    /* reserved for later use                   */
} RmMemPoolInfoStruct;
                     
                     
/* Structure for the QCOPY system call */

typedef struct _RmRCBStruct
{
    struct _RmRCBStruct _NEAR *link; /* Forward link or NULL                */
    char        pri;            /* Request priority                         */
    char        cord;           /* Task coordination                        */
    struct _RmTCBStruct _NEAR *wtcb; /* Requesting task's tcb               */
    uint        eax;            /* Start up EAX                             */
    uint        ebx;            /* Start up EBX                             */
    struct _RmTCBStruct _NEAR *tcb;  /* Requested task's tcb                */
    uint        res1[2];        /* reserved                                 */
    /* Start of the qcopy parameter region */
    void       *ord_ptr;        /* pointer to the overlay-region-definition */
#if RMFLAT
    ushort      ord_ptr_res;    /* fill word for flat model                 */
#endif
    uchar      *tcd_load;       /* pointer to the task load-descriptor,     */
                                /* see the TCD-structure and the            */
                                /* configuration-manual for more information*/
#if RMFLAT
    ushort      tcd_load_res;   /* fill word for flat model                 */
#endif
    uint        reserved[4];    /* reserved                                 */
} RmRCBStruct;


/* structure for the RmAbsTime system call */

typedef struct _RmAbsTimeStruct
{
    ulong       lotime;         /* low 32-Bit time value                    */
    ulong       hitime;         /* high 32-Bit time value                   */
} RmAbsTimeStruct;

/* structure for the STIME  and TIME system call */

typedef struct _RmAsciiTimeStruct
{
    char        day[2];         /* 01 ... 31 (ASCII)                        */
    char        delim0;         /* '-'                                      */
    char        month[3];       /* JAN ... DEC (ASCII)                      */
    char        delim1;         /* '-'                                      */
    char        year[4];        /* 0 ... 9999 (ASCII)                       */
    char        blank;          /* ' '                                      */
    char        hour[2];        /* 0 ... 23 (ASCII)                         */
    char        colon0;         /* ':'                                      */
    char        min[2];         /* 0 ... 59 (ASCII)                         */
    char        colon1;         /* ':'                                      */
    char        sec[2];         /* 0 ... 59 (ASCII)                         */
} RmAsciiTimeStruct;


/* mbox structure for recv as send by intrhand */
   
typedef struct _RmIntrhandMailStruct
{
    uint        int_no;
    uint        int_vec             : 8;
    uint        int_kind            : 1;
    uint        lost_int_overflow   : 1;
#if RM3
    uint        dummy_2             : 22;
#else
    uint        dummy_2             : 6;
#endif
    ushort      lost_int;
#if RM3
    ushort      dummy_3;
#endif
} RmIntrhandMailStruct;


/* System control block */
   
typedef struct _RmSysB
{
    uchar       version[6];     /* rmos version number                      */
    ushort      proctype;       /* processor type                           */
                                /* proctype & 0x0F00 = cpu type             */
                                /* proctype & 0x00F0 = cpu model   (PENTIUM)*/
                                /* proctype & 0x000F = cpu stepping(PENTIUM)*/
                                /* proctype & 0x8000 = fpu attached         */
    ushort      systemtype;     /* RMOS type                                */
                                /* 2 = RMOS2                                */
                                /* 3 = RMOS3                                */
                                /* 4 = RMOS for Windows                     */
    ushort      res1;           /* reserved                                 */
    ulong       reserved;       /* reserved                                 */
                                /*                                          */    
    char        statname[16];   /* stationname                              */
    uchar       bootfname[128]; /* filespec of loaded system                */
    uchar       bootnode[6];    /* 6 bytes lan address of boot server       */
    uchar       bootdrive;      /* drive from which the system was loaded   */
                                /* 0 = Floppy Drive 0                       */
                                /* 1 = Hard Disk Drive 0                    */
                                /* 2 = Memory Card                          */
                                /* 3 = LAN                                  */
                                /* 4 = EPROM System                         */
                                /* 5 = bootfname has drivename of bootdrive */
                                /* -1= unknown bootdrive                    */
    uchar       res2;           /* reserved                                 */
                                /*                                          */    
    ulong       ram_size;       /* sizeof RAM                               */
    uint        smr_max;        /* maximum number of SMRs                   */
    uint        smr_used;       /* actual number of SMRs used               */
    uint        smr_avail;      /* available SMRs                           */
    uint        out_of_smr_count;/* number of bound reached                 */
#if RM3
    ushort      fl_er_sel;      /* flat selector for code                   */
    ushort      fl_rw_sel;      /* flat selector for data                   */
#endif
                                /*                                          */    
    ushort      rate_msec;      /* internal pitrate in milisecond           */
    ulong       rate_usec;      /* rmos systemclock in microsecond          */
    ulong       pit_count;      /* count of timerticks between two timerint */
    ushort      timer_int;      /* interrupt number for timer               */
                                /*                                          */    
    rmproc      issue_eoi_entry;/* address of issue_eoi function            */
    uchar       pic_count;      /* number of pics                           */
    uchar       pic_base[8];    /* lowest vector address assigned to        */
                                /* pic 1 to 8 (master=1)                    */
    uchar       pic_mask[8];    /* pic masks set for pics 1 to 8            */
                                /*                                          */    
#if RM3
    uchar       res3[3];        /* reserved                                 */
#else
    uchar       res3[1];        /* reserved                                 */
#endif    
    int (_FAR _FIXED * set_pic_mask)(uint irq);  /* address of function to  */
                                /* manipulate pic mask                      */
#if RM3
#if RMFLAT
    ushort      res4f;          /* reserved                                 */
#endif
    ushort      res4;           /* reserved                                 */
#endif
                                /* address of function to initialise timer  */
    int (_FAR _FIXED * init_pit)(void); 
#if RM3                         /*                                          */
#if RMFLAT                      /*                                          */
    ushort      res5f;          /* reserved                                 */
#endif                          /*                                          */
    ushort      res5;           /* reserved                                 */
#endif                          /*                                          */
                                /* address of set hardware clock            */
    int (_FAR _FIXED * set_rtc_entry)(RmTimeStruct *); 
#if RM3                         /*                                          */
#if RMFLAT                      /*                                          */
    ushort      res6f;          /* reserved                                 */
#endif                          /*                                          */
    ushort      res6;           /* reserved                                 */
#endif                          /*                                          */
                                /* address of get hardware clock            */
    int (_FAR _FIXED * get_rtc_entry)(RmTimeStruct *); 
#if RM3                         /*                                          */
#if RMFLAT                      /*                                          */
    ushort      res7f;          /* reserved                                 */
#endif                          /*                                          */
    ushort      res7;           /* reserved                                 */
#endif                          /*                                          */
                                /* address of putchar for nucprintf         */
    int (_FAR _FIXED * putchar_entry)(char);
#if RMFLAT                      /*                                          */
    ushort      res8f;          /* reserved                                 */
#endif                          /*                                          */

} RmSysB;


/* rio status structure */
   
typedef struct _RmIOStatusStruct
{
    char        primary;
    char        secondary;
    ushort      count;
#if RM3
    ushort      status3;
    ushort      status4;
#endif
} RmIOStatusStruct;

/* System tables */
   
typedef struct _RmSystemTables
{
    RMVOIDPTR(  tcb_table);
    uint        tcb_num;
    RMVOIDPTR(  gefd_table);
    uint        gefd_num;
    RMVOIDPTR(  scbd_table);
    uint        scbd_num;
    RMVOIDPTR(  mbxd_table);
    uint        mbxd_num;
    RMVOIDPTR(  mpdd_table);
    uint        mpdd_num;
    RMVOIDPTR(  mpbd_table);
    uint        mpbd_num;
    RMVOIDPTR(  system_table);
    uint        system_num;
    RMVOIDPTR(  hook_table);
    uint        hook_num;
    RMVOIDPTR(  user_table_code);
    uint        user_num_code;
    RMVOIDPTR(  user_table_data);
    uint        user_num_data;
} RmSystemTables;


/* Device control definition block*/

typedef struct _RmDCDStruct
{
    struct _RmUCDStruct _NEAR *ucd;  /* reserved                            */
    uchar       units;          /* reserved                                 */
    uchar       shr;            /* device nr. of sharing device             */
                                /* (0ffh = none).                           */
    rmproc      init;           /* address of initialization routine        */
    rmproc      svc;            /* address of irb input routine             */
                                /* (sometimes called svc rest handler)      */
    uchar       flags;          /* flags: see below                         */
                                /*  bit 0 = 1: parallel driver 
                                    bit 0 = 0: seriell driver
                                    bit 1 = 1: typ-II-driver
                                    bit 1 = 0: typ-I-driver
                                    bit 2 = 0: driver initialized
                                               and ready after systeminit
                                    bit 2 = 1: driver not initialized
                                               and suspended after systeminit
                                    */
    uchar       fmax;           /* maximum function code for driver         */
#if RM3
    uchar       res[4];         /* reserved space                           */
#else
    uchar       res[2];         /* reserved space                           */
#endif
} RmDCDStruct;


/* Unit control definition block */

typedef struct _RmUCDHeadStruct
{
    uchar       pid;            /* reserved                                 */
    uchar       intno;          /* interrupt number                         */
    rmfarproc   intadr;         /* interrupt vector address                 */
    ushort      uns;            /* unsolicited interrupt task number        */
} RmUCDHeadStruct;
        
typedef struct _RmUCDStruct
{
    uchar       pid;            /* reserved                                 */
    uchar       intno;          /* interrupt number                         */
    rmfarproc   intadr;         /* interrupt vector address                 */
    ushort      uns;            /* unsolicited interrupt task number        */
#if RM3
    uchar       port[256-10];   /* unit dependent parameters                */
#else
    uchar       port[128-8];    /* unit dependent parameters                */
#endif
} RmUCDStruct;


/* Device control (dynamic) block */

typedef struct _RmDCBStruct
{
    struct _RmDCBStruct _NEAR *link; /* forward link or 0                   */
    uchar       id;             /* device number                            */
    uchar       sts;            /* driver status byte                       */
    struct _RmIRBStruct _NEAR *qirb; /* driver irb queue                    */
    struct _RmIRBStruct _NEAR *cirb; /* driver current irb                  */
    struct _RmUCBStruct _NEAR *ucb;  /* address of unit 0 ucb               */
    struct _RmDCDStruct _NEAR *dcd;  /* offset of dcd                       */
#if RM3
    uchar       gpr[256-22];    /* driver general storage                   */
#else
    uchar       gpr[128-12];    /* driver general storage                   */
#endif
} RmDCBStruct;


/* Unit control (dynamic) block */

typedef struct _RmUCBStruct
{
    struct _RmUCBStruct _NEAR *link; /* forward link or 0                   */
    uchar       unit;           /* unit number                              */
    uchar       sts;            /* unit status byte                         */
    struct _RmIRBStruct _NEAR *qirb; /* unit irb queue                      */
    struct _RmIRBStruct _NEAR *cirb; /* unit current irb                    */
    ushort      seg;            /* segment of ucd                           */
    struct _RmDCBStruct _NEAR *dcb;  /* address of driver dcb               */
    struct _RmUCDStruct _NEAR *ucd;  /* offset of ucd                       */
    struct _RmTCBStruct _NEAR *tcb;  /* reserver's tcb address or 0         */
#if RM3                                                             
    uchar       gpr[256-28];    /* general unit storage                     */
#else
    uchar       gpr[128-16];    /* general unit storage                     */
#endif
} RmUCBStruct;


/* I/O request block */

typedef struct _RmIRBStruct
{
    struct _RmIRBStruct _NEAR *link; /* forward link or 0                   */
    ushort      pri;            /* priority                                 */
    struct _RmTCBStruct _NEAR *tcb;  /* tcb address of requestor            */
    struct _RmUCBStruct _NEAR *ucb;  /* ucb of requested unit               */
    struct _RmTMBStruct _NEAR *tmb;  /* address of tmb for this request     */
    uchar       rio;            /* start of sdb image                       */
    uchar       funct;          /* function code                            */
    uchar       device;         /* device number                            */
    uchar       unit;           /* unit number                              */
    uchar       grp;            /* flag group (always 0)                    */
    uint        flags;          /* flag mask                                */
    void       *status;         /* address of status buffer                 */
#if RMFLAT
    ushort      status_seg;     /* fillword for FLAT                        */
#endif    
    void       *bufr;           /* address of device dependent              */
                                /*   parameter list                         */
#if RMFLAT
    ushort      bufr_seg;       /* fillword for FLAT                        */
#endif    
    ushort      seq;            /* reserved                                 */
} RmIRBStruct;


/* Time monitor block */

typedef struct _RmTMBStruct
{
    /* *** Common part *** */
    struct _RmTMBStruct _NEAR *link; /* forward link or 0                   */
    uint        ltime;          /* low  dword, absolute expiration time     */
    uint        htime;          /* high dword, absolute expiration time     */
    uchar       type;           /* tmb type:                                */
                                /*  type 1 = driver or tod timeout          */
                                /*  type 2 = task pause expiration          */
                                /*  type 3 = event flag to be set           */
                                /*  type 4 = task restart timer             */
                                /*  type 5 = override-priority timer        */
                                /*  type 6 = reserved                       */
                                /*  type 7 = reserved                       */
                                /*  type 8 = svc timeout                    */
                                /*  type 9 = delayed messages               */
    union
    {
    /* *** Type 1 *** */
        struct
        {
            uchar   res;
            struct _RmUCBStruct _NEAR *ucb; /* ucb of unit                  */
            void   *sadr;           /* address of timeout routine           */
#if RMFLAT
            ushort sadr_seg;        /* fillword for FLAT                    */
#endif    

        } type_1;
    /* *** Type 2 *** */
        struct
        {
            uchar   res;
            struct _RmTCBStruct _NEAR *tcb; /* tcb of requestor             */
        } type_2;
    /* *** Type 3 *** */
        struct
        {
            uchar   efgrp;          /* event flag group                     */
            struct _RmTCBStruct _NEAR *tcb; /* tcb of requestor             */
            uint    efmsk;          /* event flag mask                      */
        } type_3;
    /* *** Type 4 *** */
        struct
        {
            uchar   res;
            struct _RmTCBStruct _NEAR *tcb; /* tcb of requestor             */
        } type_4;
    /* *** Type 5 *** */
        struct
        {
            uchar   res;
            struct _RmTCBStruct _NEAR *tcb; /* tcb of requestor             */
            uchar   ovpri;          /* priority override increment          */
            uchar   bpri;           /* override priority boundary           */
            uchar   ovtime;         /* override time interval, msec         */
        } type_5;
    /* *** Type 6 *** */
        struct
        {
            uchar   res;
            struct _RmTCBStruct _NEAR *tcb; /* tcb of requestor             */
            uint    swb;            /* swb address                          */
            uint    sem;            /* semaphore address                    */
        } type_6;
    /* *** Type 7 *** */
        struct
        {
            uchar   res;
            struct _RmIRBStruct _NEAR *irb; /* irb address                  */
        } type_7;
    /* *** Type 8 *** */
        struct
        {
            uchar   res;
            uint    tjt;        /* timeout jump table                       */
            ushort  svc;        /* bit coded svc                            */
            uint    qh;         /* specific queue header                    */
            uint    wb;         /* specific wait block                      */
        } type_8;
    /* *** Type 9 *** */
        struct
        {
            uchar   res[3];
            uint    alarm;      /* alarm routine, called on expiration      */
            uint    tib;        /* corresponding tib                        */
        } type_9;
    } utmb;
} RmTMBStruct;


  /**************************************************************************/
  /*                            Alignment control                           */
  /**************************************************************************/

#if defined _MSC_VER
#pragma pack()          /* reset alignment to commandline specification */
#endif

#ifdef __BORLANDC__
#pragma option -a.      /* reset alignment to commandline specification */
#endif


#endif /* _RMTYPES_H_ */

