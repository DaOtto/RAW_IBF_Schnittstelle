/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : SVC.H
;   version     : 0040
;   contents    : Include-File for RMOS-Systemcalls in C
;   author      : P.F.
;   date        : Aug 08, 1995
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Include-file for RMOS-Systemcalls
;                 Official Defines for systemcalls
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Aug 08, 1995  P.F.   0040  Modification for RMOS V3.1
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _SVC_H_
#define _SVC_H_ 1

#ifndef _PROT_H_
#include <prot.h>
#endif  /* _PROT_H_ */
#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */


#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
#ifndef _NOVERS
static const
char idstr_svc_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"    /* In-code identification. */
        "\1"    "SVC.H"                 "\1"
        "\2"    "0040"                  "\2"
        "\3"    "P.F."                  "\3"
};
#endif  /* _NOVERS */
#endif  /* defined(_ARCHITECTURE_)  ||  defined(CADUL) */


#if defined _MSC_VER
#pragma pack(1)     /* set all to byte alignment */
#endif

#ifdef __BORLANDC__
#pragma option -a-  /* set all to byte alignment */
#endif


/***************************************************************
   RMOS SVC error macros
 ***************************************************************/

#define FLAG_CARRY      0x0001
#define FLAG_PARITY     0x0004
#define FLAG_AUXCARRY   0x0010
#define FLAG_ZERO       0x0040
#define FLAG_SIGN       0x0080
#define FLAG_TRAP       0x0100
#define FLAG_INTERRUPT  0x0200
#define FLAG_DIRECTION  0x0400
#define FLAG_OVERFLOW   0x0800
#if RM3
#define	FLAG__IOPL	0x00003000
#define	FLAG_NT		0x00004000
#define	FLAG_RF		0x00010000
#define	FLAG__VM	0x00020000
#endif /* RM3 */

#define SVCERR            FLAG_ZERO
#define SVCERRPAR       ( FLAG_ZERO | FLAG_SIGN )

#define svcok(sts)    (!((sts) & ZERO_SET))
#define SVCOK(sts)    (!((sts) & ZERO_SET))


#if defined(_ARCHITECTURE_) || defined(CADUL)

/*  This Part belongs to the Intel C-Compiler IC86/386 or CADUL CC86/386 */

/***************************************************************
   Function calling conventions
 ***************************************************************/

 #define PARAMS fixedparams

#if !RMFLAT
 #pragma PARAMS (aloc,bound,catalog,cntrl,cpri,cprix,create)
 #pragma PARAMS (createdriv,createdsct,createflag)
 #pragma PARAMS (creatembox,createhpool,createpool,createsema,daloc,delete)
 #pragma PARAMS (deleteme,deletedriv,deletedsct,deleteflag,deletembox)
 #pragma PARAMS (deletepool,deletesema)
 #pragma PARAMS (deltsk,dscrte,endt,endr,getsize,getstat,haloc)
 #pragma PARAMS (hdaloc,intrhand,killtsk,list,locks,look,pause,qcopy)
 #pragma PARAMS (qstrt,recv,ref,resblk,resume,rio)
 #pragma PARAMS (rsf,sef,sefet,send,setint)
 #pragma PARAMS (stime,strt,tef,timeout,timercancel,timerstart,tsf)
 #pragma PARAMS (uncatalog,wef,changedesc,changedescaccess,createdesc)
 #pragma PARAMS (deldesc,physadr,hsfs)
 #pragma PARAMS (db_sbreak,db_kbreak,db_halt,db_cont)
 #pragma PARAMS (db_tcbadr,db_taskid,db_lsef,db_lref,db_cont_rt)
 #pragma PARAMS (db_qbreak,db_rtrvp)
#endif /* !RMFLAT */

/***************************************************************
   RMOS structure alignment
 ***************************************************************/

/* These pragmas garantee that the rmos-data-structures conform with the
   compiler structures
*/   

 #pragma align( RM_MailboxStruct = 1)
 #pragma align( RM_TCDstruct = 1)
 #pragma align( RM_XTCDstruct = 1)
 #pragma align( RM_GetStatusStruct = 1)
 #pragma align( RM_ListStruct = 1)
 #pragma align( RM_CatalogStruct = 1)
 #pragma align( RM_RCBstruct = 1)
 #pragma align( RM_AsciiTimeStruct = 1)
 #pragma align( RM_BreakpointStruct = 1 )
 #pragma align( RM_RegisterStruct = 1 )
 #pragma align( RM_TimeStruct_Tag = 1)
 
#endif /*  defined(_ARCHITECTURE_) || defined(CADUL) */


/***************************************************************
   RMOS type definitions
 ***************************************************************/

#if RM3

typedef unsigned char byte;
typedef unsigned short word16;
typedef unsigned int word32;
typedef unsigned int word64[2];

#else

typedef unsigned char byte;
typedef unsigned int word16;
typedef unsigned long word32;
typedef unsigned long word64[2];

#endif /* RM3 */


/***************************************************************
   structures for RMOS-systemcalls    
 ***************************************************************/

/* Structure for the SEND and RECV systemcall
*/
struct  RM_MailboxStruct
{
    void *adr;              /* may be address of a mail                     */
#if RMFLAT
    word16 adr_res;         /* fill word for flat model                     */
#endif
#if RM3
    word16 pad;             /* pad pointer                                  */
#endif
    unsigned int len;       /* may be length of the mail                    */
};
#define mbox_struct    RM_MailboxStruct

  
/* Structure for the CREATE systemcall
*/
struct  RM_TCDstruct
{
    unsigned int ax;        /* register AX,BX,DS,ES                         */
    unsigned int bx;
    word16 ds;
    word16 es;
    char *stck;             /* pointer to task stack                        */
#if RMFLAT
    word16 stck_res;        /* fill word for flat model                     */
#endif
    void (_FAR *task)(void);/* pointer to task startaddress                 */
#if RMFLAT
    word16 task_res;        /* fill word for flat model                     */
#endif
    char *load;             /* address of the load descriptor string
                               for a loadable task, otherwise (char *) 0    */
#if RMFLAT
    word16 load_res;        /* fill word for flat model                     */
#endif
    char ovrd_tme_unit;     /* override time unit specifier                 */
    char ovrd_int_num;      /* number of units in override time interval    */
    char ovrd_prio_inc;     /* override priority increment                  */
    char ovrd_prio_bnd;     /* override priority boundary value             */
    char inherent_prio;     /* inherent priority                            */
    char cpu_id;            /* cpu number or 0ffh                           */
    word16 flags;           /* flags word                                   */
#if RM3
    char reserve[10];       /* reserved, 10 Bytes                           */
#else
    char reserve[4];        /* reserved, 4 Bytes                            */
#endif
};
#define tcd_struct  RM_TCDstruct


struct  RM_XTCDstruct
{
    unsigned int eax;       /* register EAX,EBX,DS,ES                       */
    unsigned int ebx;
    word16 ds;
    word16 es;
    char *stck;             /* pointer to task stack                        */
#if RMFLAT
    word16 stck_res;        /* fill word for flat model                     */
#endif
    void (_FAR *task)(void);/* pointer to task startaddress                 */
#if RMFLAT
    word16 task_res;        /* fill word for flat model                     */
#endif
    char *load;             /* address of the load-descriptor-string
                               for a loadable task, otherwise (char *) 0    */
#if RMFLAT
    word16 load_res;        /* fill word for flat model                     */
#endif
    char ovrd_tme_unit;     /* override time unit specifier                 */
    char ovrd_int_num;      /* number of units in override time interval    */
    char ovrd_prio_inc;     /* override priority increment                  */
    char ovrd_prio_bnd;     /* override priority boundary value             */
    char inherent_prio;     /* inherent priority                            */
    char cpu_id;            /* cpu number or 0ffh                           */
    word16 flags;           /* flags word                                   */
    word16 rr_ticks;        /* task specific round robin count              */
#if RM3
    char reserve[8];        /* reserved, 8 Bytes                            */
#else
    char reserve[4];        /* reserved, 4 Bytes                            */
#endif
};
#define xtcd_struct  RM_XTCDstruct


/* Structure for the GETSTAT-system-call. Look the nucleus-manual */
struct  RM_GetStatusStruct
{
    char pri;               /* priority of the task                         */
    char state;             /* state of the task                            */
    unsigned int *sp_ss;    /* current stack pointer address                */
#if RM3
#if RMFLAT
    word16 sp_ss_res;       /* fill word for flat model                     */
#endif
    word64 rdy_time;        /* time when task was first ready               */
#else
    unsigned int rdy_time[3];       /* time when task was first ready       */
#endif
    char    cpu_id;                 /* cpu-id                               */
    char    flg;                    /* task flags                           */
    struct RM_TCDstruct *tcd_ptr;   /* TCD pointer                          */
#if RMFLAT
    word16 tcd_ptr_res;     /* fill word for flat model                     */
#endif
};
#define getstat_struct RM_GetStatusStruct

    
/* structure for reading or setting CMOS-Time */
typedef struct RM_TimeStruct_Tag
{
  unsigned char  day;
  unsigned char  month;
  unsigned short year;
  unsigned char  hours;
  unsigned char  minutes;
  unsigned char  seconds;
} rm_time_struct;
#define RM_time_struct rm_time_struct


/* Structure for the LIST-Systemcall */
struct RM_ListStruct
{   char string[13];        /* string[0] contains the strlen                */
    char type;              /* Type of the OS-Ressource                     */
    word16 id;              /* Identification number of the type            */
};
#define list_struct  RM_ListStruct


/* Structure for the LOOK-Systemcall */
struct RM_CatalogStruct
{   char type;              /* Type of the ressource                        */
    word16 id;              /* ID-Number of the ressource                   */
};
#define cat_struct  RM_CatalogStruct


/* Structure for the QCOPY-Systemcall */
struct RM_RCBstruct
{   unsigned int rcb_link;  /* Forward link or NULL                         */
    char rcb_pri;           /* Request priority                             */
    char rcb_coord;         /* Task coordination                            */
    unsigned int rcb_wtcb;  /* Requesting task's tcb                        */
    unsigned int rcb_ax;    /* Start up AX                                  */
    unsigned int rcb_bx;    /* Start up BX                                  */
    unsigned int rcb_tcb;   /* Requested task's tcb                         */
    unsigned int res1[2];   /* reserved                                     */
    /* Start of the qcopy parameter region */
    unsigned short rcb_user; /* user defined parameter                      */
#if RM3
    unsigned short reserved[18]; /* reserved passing for TCB size           */
#else
    unsigned short reserved[7];  /* reserved                                */
#endif
};
#define rcb_struct  RM_RCBstruct


/* Structure for the STIME- and TIME-systemcall */
struct RM_AsciiTimeStruct
{   char day[2];            /* 01 ... 31 (ASCII)                            */
    char delim0;            /* '-'                                          */
    char month[3];          /* JAN ... DEC (ASCII)                          */
    char delim1;            /* '-'                                          */
    char year[4];           /* 0 ... 9999 (ASCII)                           */
    char blank;             /* ' '                                          */
    char hour[2];           /* 0 ... 23 (ASCII)                             */
    char colon0;            /* ':'                                          */
    char min[2];            /* 0 ... 59 (ASCII)                             */
    char colon1;            /* ':'                                          */
    char sec[2];            /* 0 ... 59 (ASCII)                             */
};
#define time_struct  RM_AsciiTimeStruct


/* Timer ID type for the systemcalls TIMERSTART and TIMERCANCEL */
typedef unsigned long RM_TimerId[2];
#define tid_t   RM_TimerId


/* Structures for the DB_SBREAK-systemcall */
#if RM3
struct RM_RegisterStruct    /* Definition of the breakpoint register structure */
{   word32  si;
    word32  di;
    word32  es;
    word32  ds;
    word32  bp;
    word32  fs;
    word32  gs;
    word32  x3;
    word32  ip;
    word32  cs;
    word32  fl;
    word32  sp;
    word32  ss;
    word32  dx;
    word32  cx;
    word32  bx;
    word32  ax;
    word32  save_sp;
    unsigned char ndp[108];
};
#else
struct RM_RegisterStruct
{   word16  si;
    word16  di;
    word16  es;
    word16  ds;
    word16  bp;
    word16  x1;
    word16  x2;
    word16  x3;
    word16  ip;
    word16  cs;
    word16  fl;
    word16  sp;
    word16  ss;
    word16  dx;
    word16  cx;
    word16  bx;
    word16  ax;
    word16  save_sp;
    unsigned char ndp[108];
};
#endif
#define regs_struct  RM_RegisterStruct


struct RM_BreakpointStruct      /* Definition for the db_sbreak systemcall  */
{   unsigned char   bp_id;             /* Breakpoint-ID                     */
    unsigned char   bp_typ;            /* Breakpoint-Type                   */
    unsigned char   curr_cpu_b;        /* CPU-ID = 0                        */
    word16          task_id_w16;       /* Task-ID                           */
    unsigned char   mon_flag;          /* 0 = Task-Breakpoint /             */
    unsigned char   reserve_0;         /* 1 = Monitor-Breakpoint            */
    unsigned char   reserve_1;
    word16          reserve_2;
    unsigned char   reserve_3;
    unsigned char   reserve_4;
    struct RM_RegisterStruct    regs;  /* Register-Structure                */
};
#define bp_struct  RM_BreakpointStruct


/* mbox structure for recv as send by intrhand
   ------------------------------------------- */
   
typedef struct
{
    unsigned int   int_no ;
    unsigned int   int_vec:8 ;
    unsigned int   int_kind:1 ;
    unsigned int   lost_int_overflow:1 ;
#if RM3
    unsigned int   dummy_2:22 ;
#else
    unsigned int   dummy_2:6 ;
#endif
    unsigned int   lost_int:8 ;
#if RM3
    unsigned int   dummy_3:24 ;
#else
    unsigned int   dummy_3:8 ;
#endif
} RM_IntrhandMailStruct ;
#define intrhand_mbox_struct  RM_IntrhandMailStruct


/***************************************************************
    Calling-Conventions for RMOS-systemcalls
 ***************************************************************/

#define FDCL    extern void _FIXED _FAR
#define FDCI    extern int  _FIXED _FAR
#define FCLO    extern long _FIXED _FAR
#define FCUC    extern unsigned char _FIXED _FAR
#define FDCP    extern int * _FIXED _FAR
#define FDUI    extern unsigned int  _FIXED _FAR

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if !RMFLAT 

FDCL aloc(       unsigned int wait_type,       /* wait till memory available */
                 unsigned int pool_id,         /* ID of reqested pool        */
                 unsigned int size,            /* so many bytes              */
                 void _DFAR * _DFAR *ptr,      /* there we put the pointer   */
                 unsigned int _DFAR *sts       /*  */
          );
FDCL haloc(      unsigned int wait_type,
                 unsigned int pool_id, 
                 word32 size,
                 void _DFAR * _DFAR *ptr,
                 unsigned int _DFAR *sts
          );
FDCL bound(      unsigned int type, 
                 unsigned int id,
                 unsigned int limit, 
                 unsigned int _DFAR *sts
          );
FDCL catalog(    unsigned int type, 
                 unsigned int type_id,
                 char _DFAR *ptr, 
                 unsigned int _DFAR *sts
            );
FDCL cntrl(      unsigned int type, 
                 unsigned int cntrl_id, 
                 unsigned int _DFAR *sts
          );
FDCL cpri(       unsigned int pri_type, 
                 unsigned int pri_val, 
                 unsigned int _DFAR *sts
         );
FDCL cprix(      unsigned int pri_type, 
                 unsigned int task_type,
                 unsigned int pri_val, 
                 unsigned int task_id,
                 unsigned int _DFAR *sts
          );
FDCL create(     unsigned int _DFAR *task_id_ptr, 
                 struct RM_TCDstruct _DFAR *tcd_ptr,
                 unsigned int _DFAR *sts
           );
FDCL createdriv( unsigned int dr_type, 
                 unsigned int dev_id, 
                 void _DFAR *dcd_ptr, 
                 void _DFAR *res_ptr, 
                 unsigned int _DFAR *sts
               );
FDCL createdsct( char _DFAR *dsct_addr, 
                 unsigned int _DFAR *dsct_id_ptr,
                 unsigned int _DFAR *sts
               );
FDCL createflag( unsigned int _DFAR *flag_id_ptr,
                 unsigned int _DFAR *sts
               );
FDCL creatembox( unsigned int _DFAR *mbox_id_ptr, 
                 unsigned int _DFAR *sts
               );
FDCL createpool( void _DFAR *pool_addr, 
                 unsigned int pool_size,
                 unsigned int _DFAR *pool_id_ptr, 
                 unsigned int _DFAR *sts
                );
FDCL createhpool(unsigned int mode, 
                 void _DFAR *pool_addr,
                 word32 pool_size, 
                 unsigned int _DFAR *pool_id_ptr,
                 unsigned int _DFAR *sts
                );
FDCL createsema( unsigned int _DFAR *sema_id_ptr, 
                 unsigned int _DFAR *sts
               );
FDCL daloc(      unsigned int size, 
                 void _DFAR * _DFAR *ptr, 
                 unsigned int _DFAR *sts
          );
FDCL hdaloc(     unsigned int mode, 
                 void _DFAR * _DFAR *ptr, 
                 unsigned int task_id,
                 unsigned int _DFAR *sts
           );
FDCL db_cont(    unsigned int task_id, 
                 unsigned int _DFAR *sts
            );
FDCL db_cont_rt( unsigned int task_id, 
                 unsigned int _DFAR *sts
               );
FDCL db_halt(    unsigned int task_id, 
                 unsigned int _DFAR *sts
            );
FDCL db_kbreak(  unsigned int cpu_id, 
                 unsigned int brk_id,
                 unsigned int _DFAR *sts
              );
FDCL db_lref(    unsigned int task_id, 
                 unsigned int flg_msk,
                 unsigned int _DFAR *sts
             );
FDCL db_lsef(    unsigned int task_id, 
                 unsigned int flg_msk,
                 unsigned int _DFAR *sts
             );
FDCL db_qbreak(  unsigned int cpu_id, 
                 unsigned int brk_id,
                 unsigned int count, 
                 unsigned int task_id,
                 unsigned int mon_spec, 
                 unsigned int _DFAR *sts
              );
FDCL db_rtrvp(   void _DFAR *bufr, 
                 unsigned int _DFAR *sts
             );
FDCL db_sbreak(  unsigned int cpu_id, 
                 unsigned int brk_id,
                 unsigned int brk_flg, 
                 void _DFAR *adr_,
                 unsigned int step_count, 
                 void _DFAR *bp_struc,
                 unsigned int _DFAR *sts
              );
FDCL db_taskid(  unsigned int tcb_ofs, 
                 unsigned int _DFAR *bufr,
                 unsigned int _DFAR *sts
              );
FDCL db_tcbadr(  unsigned int task_id, 
                 void _DFAR * _DFAR *bufr,
                 unsigned int _DFAR *sts
              );
#ifndef __cplusplus               /* only usable in C */
FDCL delete(     void
           );
#endif /* __cplusplus */
/* Synonym to delete, because in C++ delete is an operator */
FDCL deleteme(   void
             );
FDCL deletedriv( unsigned int dev_id, 
                 unsigned int _DFAR *sts
               );
FDCL deletedsct( unsigned int _DFAR *dsct_id_ptr, 
                 unsigned int _DFAR *sts
               );
FDCL deleteflag( unsigned int _DFAR *flag_id_ptr, 
                 unsigned int _DFAR *sts
               );
FDCL deletembox( unsigned int _DFAR *mbox_id_ptr, 
                 unsigned int _DFAR *sts
               );
FDCL deletepool( unsigned int _DFAR *pool_id_ptr, 
                 unsigned int _DFAR *sts
               );
FDCL deletesema( unsigned int _DFAR *sema_id_ptr, 
                 unsigned int _DFAR *sts
               );
FDCL deltsk(     unsigned int task_id, 
                 unsigned int _DFAR *sts
           );
FDCL dscrte(     unsigned int io_type, 
                 unsigned int test_typ, 
                 unsigned int dsct_typ, 
                 unsigned int dsct_mask, 
                 unsigned int _DFAR *sts
            );
FDCL endr(       unsigned int time_base,
                 unsigned int time_unit, 
                 unsigned int count
         );
FDCL endt(       void
         );
FDCL getsize(    void _DFAR * _DFAR *pool_ptr, 
                 word32 _DFAR *len_ptr,
                 unsigned int _DFAR *sts
             );
FDCL getstat(    unsigned int task_id, 
                 struct RM_GetStatusStruct _DFAR *info_ptr,
                 unsigned int _DFAR *sts
            );
FDCL intrhand(   unsigned int intr_type,
                 unsigned int intr_no,
                 unsigned int id, 
                 unsigned int intr_priv,
                 void _DFAR *entry0, 
                 void _DFAR *entry1, 
                 void _DFAR * _DFAR *old_entry,
                 unsigned int _DFAR *sts
             );
FDCL killtsk(    unsigned int mode, 
                 unsigned int task_id,
                 unsigned int _DFAR *sts
            );
FDCL list(       unsigned int count, 
                 unsigned int _DFAR *ix_ptr,
                 unsigned int type, 
                 unsigned int _DFAR *count_ptr,
                 struct RM_ListStruct _DFAR *info_ptr, 
                 unsigned int _DFAR *sts
         );
FDCL locks(      unsigned int type, 
                 unsigned int _DFAR *sts
          );
FDCL look(       unsigned int wait_type, 
                 char _DFAR *ptr,
                 struct RM_CatalogStruct _DFAR *info_ptr, 
                 unsigned int _DFAR *sts
          );
FDCL pause(      unsigned int time_unit, 
                 unsigned int count, 
                 unsigned int _DFAR *sts
          );
FDCL qcopy(      struct RM_RCBstruct _DFAR *info_ptr, 
                 unsigned int _DFAR *sts
          );
FDCL qstrt(      unsigned int wait_type, 
                 unsigned int task_id, 
                 unsigned int pri, 
                 unsigned int pri_val, 
                 unsigned int p1, 
                 unsigned int p2, 
                 unsigned int _DFAR *sts
          );
FDCL recv(       unsigned int wait_type, 
                 unsigned int mbox_id, 
                 void _DFAR *info_ptr, 
                 unsigned int _DFAR *sts
         );
FDCL ref(        unsigned int flg_id, 
                 unsigned int flg_mask, 
                 unsigned int _DFAR *sts
        );
FDCL resblk(     unsigned int mode, 
                 void _DFAR *rptr, 
                 word32 rphys,
                 word32 rlen, 
                 unsigned int _DFAR *sts
           );
FDCL resume(     unsigned int task_id, 
                 unsigned int _DFAR *sts
           );
FDCL rio(        unsigned int functn, 
                 unsigned int dev_id, 
                 unsigned int unit_id, 
                 unsigned int flg_id, 
                 unsigned int flg_mask, 
                 void _DFAR *status_ptr,
                 void _DFAR *parm_ptr, 
                 unsigned int _DFAR *sts 
        );
FDCL rsf(        unsigned int sema_id, 
                 unsigned int _DFAR *sts
        );
FDCL sef(        unsigned int flg_id, 
                 unsigned int flg_mask, 
                 unsigned int _DFAR *sts
        );
FDCL sefet(      unsigned int flg_id, 
                 unsigned int flg_mask, 
                 unsigned int time_unit, 
                 unsigned int count, 
                 unsigned int _DFAR *sts
          );
FDCL send(       unsigned int wait_type, 
                 unsigned int pri_type, 
                 unsigned int pri_val, 
                 unsigned int mbox_id, 
                 void _DFAR *ptr, 
                 unsigned int _DFAR *sts
         );
FDCL setint(     unsigned int cpu_id, 
                 unsigned int vector, 
                 void(_FAR _DFAR *ihand)(void), 
                 unsigned int _DFAR *sts
           );
FDCL stime(      unsigned int fmt_type, 
                 struct RM_AsciiTimeStruct _DFAR *info_ptr,
                 unsigned int _DFAR *sts
          );
FDCL strt(       unsigned int wait_type, 
                 unsigned int task_id, 
                 unsigned int pri, 
                 unsigned int pri_val, 
                 unsigned int p1, 
                 unsigned int p2, 
                 unsigned int _DFAR *sts
         );
FDCL tef(        unsigned int type, 
                 unsigned int flg_id, 
                 unsigned int flg_mask, 
                 unsigned int _DFAR *sts
        );

#ifndef  _TIME_
 #define _TIME_ 1
#ifdef _ARCHITECTURE_  
 #pragma PARAMS (time)
#endif
 FDCL time(      unsigned int fmt_type, 
                 void _DFAR *info_ptr,
                 unsigned int _DFAR *sts
          );
#endif

FDCL timeout(    unsigned int type, 
                 unsigned int time_unit, 
                 unsigned int count, 
                 unsigned int _DFAR *sts
            );
FDCL timercancel(tid_t timerid, 
                 void _DFAR *msg, 
                 unsigned int _DFAR *sts
                );
FDCL timerstart( unsigned int pri_type, 
                 unsigned int pri_val,
                 unsigned int ovf, 
                 unsigned int mbx, 
                 void _DFAR *msg,
                 unsigned int time_unit, 
                 unsigned int count,
                 tid_t timerid, 
                 unsigned int _DFAR *sts
               );
FDCL tsf(        unsigned int sema_id, 
                 unsigned int _DFAR *sts
        );
FDCL uncatalog(  char _DFAR *info_ptr, 
                 unsigned int _DFAR *sts
              );
FDCL wef(        unsigned int type, 
                 unsigned int flg_id, 
                 unsigned int flg_mask, 
                 unsigned int _DFAR *sts
         );


/*  highspeed-filesystem */

FDCL hsfs(       int h_opcode, 
                 unsigned int h_flagmask,
                 int _DFAR *h_status,
                 void _DFAR *h_rpb
         );

/* Systemcalls RMOS3 only:    */

FDCL changedesc( word16 select, 
                 word32 start, 
                 word32 limit, 
                 unsigned int _DFAR *sts
               );
FDCL changedescaccess(
                 word16 select, 
                 unsigned int access, 
                 unsigned int _DFAR *sts
                      );
FDCL createdesc( word32 start, 
                 word32 limit, 
                 word16 _DFAR *select_ptr, 
                 unsigned int _DFAR *sts
               );
FDCL deldesc(    word16 select, 
                 unsigned int _DFAR *sts
            );
FDCL physadr(    void _DFAR *poi, 
                 word32 _DFAR *addr, 
                 unsigned int _DFAR *sts
             );


/* Calls for the parameter-handling of tasks (HLI-Interface) */

#ifndef _RM_TASKPARAM_
#define _RM_TASKPARAM_
#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma PARAMS (getparm, get2ndparm, getdword, XSET_UNX_INT)
#endif

int *          _FIXED _FAR getparm      ( void ); /* Startparameter as pointer.   */
unsigned int   _FIXED _FAR get2ndparm   ( void ); /* 2nd start parameter (e)bx */
unsigned long  _FIXED _FAR getdword     ( void ); /* Startparameter as long.      */
void           _FIXED _FAR XSET_UNX_INT ( void ); /* unexpected interrupt handler */
#endif /* _RM_TASKPARAM_ */

#endif /* RMFLAT */


#ifdef __cplusplus
}
#endif /* __cplusplus */


/***************************************************************
    general purpose defines
 ***************************************************************/

#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    (~FALSE)
#endif


/***************************************************************
     constant-names in systemcalls
 ***************************************************************/

          /* wait types for aloc, recv, send, look, qstrt, strt */

#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define WAIT_RDY                    1u              /* qstrt, strt            */
#define WAIT_END                    2u              /* qstrt, strt            */
#define WT                          WAIT_RDY        /* aloc, recv, send, look */
#define CNT                         0u              /* aloc, recv, send, look,*/
                                                    /* qstrt, strt            */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_WaitType_old
{
    WT                          =   1,      /* wait til SVC finished or task ready */
    CNT                         =   0,      /* don't wait                          */
    WAIT_RDY                    =   WT,
    WAIT_END                    =   2       /* wait til task ended                 */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


              /* type for the different catalog entries */

#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define CTY_TASK                    0u              /* catalog type task      */
#define CTY_DEVICE                  1u              /* catalog type device    */
#define CTY_POOL                    2u              /* catalog type mem pool  */
#define CTY_SEMA                    3u              /* catalog type semaphore */
#define CTY_EVTFLAG                 4u              /* catalog type eventflag */
#define CTY_CNTRL                   5u              /* catalog type contr. pr.*/
#define CTY_LMBOX                   6u              /* catalog type local mbox*/
#define CTY_GMBOX                   7u              /* compatibility          */
#define CTY_MISC                    7u              /* catalog no spec. type  */
#define CTY_USER                    8u              /* catalog no spec. type  */
#define CTY_DSCRTE                  9u              /* catalog type disc. Byte*/
#define CTY_UNIT                    10u             /* catalog type unit      */
#define CTY_MESSAGE                 11u             /* catalog type message   */
#define CTY_ALL                     0xFFu           /* catalog type all, list */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_CatalogType_old
{
    CTY_TASK                    =   0,              /* catalog type task      */
    CTY_DEVICE                  =   1,              /* catalog type device    */
    CTY_POOL                    =   2,              /* catalog type mem pool  */
    CTY_SEMA                    =   3,              /* catalog type semaphore */
    CTY_EVTFLAG                 =   4,              /* catalog type eventflag */
    CTY_CNTRL                   =   5,              /* catalog type contr. pr.*/
    CTY_LMBOX                   =   6,              /* catalog type local mbox*/
    CTY_GMBOX                   =   7,              /* compatibility          */
    CTY_MISC                    =   7,              /* catalog no spec. type  */
    CTY_USER                    =   8,              /* catalog no spec. type  */
    CTY_DSCRTE                  =   9,              /* catalog type disc. Byte*/
    CTY_UNIT                    =   10,             /* catalog type unit      */
    CTY_MESSAGE                 =   11,             /* catalog type message   */
    CTY_ALL                     =   0xFF            /* catalog type all, list */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


#define CNTRL_START                 0u              /* cntrl                  */
#define CNTRL_END                   1u              /* cntrl                  */


#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define MAX_PRI                     0u              /* qstrt, strt            */
#define SET_PRI                     1u              /* qstrt, strt, send      */
#define CURR_PRI                    2u              /* qstrt, strt, send      */
#define TCD_PRI                     3u              /* qstrt, strt, send      */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_StartPriorityType_old
{
    MAX_PRI                     =   0,              /* qstrt, strt            */
    SET_PRI                     =   1,              /* qstrt, strt, send      */
    CURR_PRI                    =   2,              /* qstrt, strt, send      */
    TCD_PRI                     =   3               /* qstrt, strt, send      */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


                        /* priority types for cpri */

#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define PRI_SET                     0u
#define PRI_TCD                     1u
#define PRI_INC                     2u
#define PRI_DEC                     3u
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_ChangePriorityType_old
{
    PRI_SET                     =   0,              /* set new priority       */
    PRI_TCD                     =   1,              /* use priority from TCD  */
    PRI_INC                     =   2,              /* increment priority by 1*/
    PRI_DEC                     =   3               /* decrement priority by 1*/
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


                         /* task types for cprix */

#if defined(_ARCHITECTURE_)  ||  defined(_MSC_VER)
#define OWN                         0u
#define OTHER                       1u
#else /* any not-Intel and not-Microsoft compiler */
enum RM_ChangePriorityTaskTypes_old
{
    OWN                         =   0,              /* change priority for own task     */
    OTHER                       =   1               /* change priority for other task   */
};
#endif /* _ARCHITECTURE_ */


#define DSC_IN                      0u              /* dsctre                 */
#define DSC_OUT                     1u              /* dsctre                 */


#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define TEST_ALL                    0u              /* test for all bits      */
#define TEST_ONE                    1u              /* test for just one bit  */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_EventFlagTestType_old
{
    TEST_ALL                    =   0,              /* test for all bits      */
    TEST_ONE                    =   1               /* test for just one bit  */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


#define CLR_BITS                    0u              /* dsctre                 */
#define SET_BITS                    1u              /* dsctre                 */


#define S_TIME                      0u              /* endr                   */
#define C_TIME                      1u              /* endr                   */


                    /* units for endr, pause, timeout */

#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define MSEC_1                      0u
#define MSEC_10                     1u
#define MSEC_100                    2u
#define SEC                         3u
#define SEC_10                      6u
#define MIN                         4u
#define MIN_10                      7u
#define HOUR                        5u
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_TimeUnitType_old
{
    MSEC_1                      =   0,      /* time base is   1 millisecond   */
    MSEC_10                     =   1,      /* time base is  10 milliseconds  */
    MSEC_100                    =   2,      /* time base is 100 milliseconds  */
    SEC                         =   3,      /* time base is   1 second        */
    SEC_10                      =   6,      /* time base is  10 seconds       */
    MIN                         =   4,      /* time base is   1 minute        */
    MIN_10                      =   7,      /* time base is  10 minutes       */
    HOUR                        =   5       /* time base is   1 hour          */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define LOCKS_OFF                   0u              /* unlock scheduler       */
#define LOCKS_ON                    1u              /* lock scheduler         */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_SchedulerLockType_old
{
    LOCKS_OFF                   =   0,              /* unlock scheduler       */
    LOCKS_ON                    =   1               /* lock scheduler         */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define OVF_CLR                     0u              /* clear overflow bit     */
#define OVF_SET                     1u              /* set overflow bit       */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_MailboxOverflowType_old
{
    OVF_CLR                     =   0,              /* clear overflow bit     */
    OVF_SET                     =   1               /* set overflow bit       */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define MIN_FMT                     0u              /* stime, time            */
#define SEC_FMT                     1u              /* stime, time            */
#define GLSEC                       2u              /* stime, time            */
#define ABS_TIME                    3u              /* time                   */
#define LCSEC                       3u              /* stime                  */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_TimeType_old
{
    MIN_FMT                     =   0,              /* stime, time            */
    SEC_FMT                     =   1,              /* stime, time            */
    GLSEC                       =   2,              /* stime, time            */
    ABS_TIME                    =   3,              /* time                   */
    LCSEC                       =   3               /* stime                  */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define TB_ALOC                     0x1u            /* timeout for aloc       */
#define TB_CNTRL_TSF                0x2u            /* timeout for cntrl / tsf*/
#define TB_LOOK                     0x4u            /* timeout for look       */
#define TB_RECV                     0x8u            /* timeout for recv       */
#define TB_SEND                     0x10u           /* timeout for send       */
#define TB_WEF                      0x20u           /* timeout for wef        */
#define TB_ALL                      0xffu           /* timeout for all svcs   */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_TimeoutType_old
{
    TB_ALOC                     =   0x1,            /* timeout for aloc       */
    TB_CNTRL_TSF                =   0x2,            /* timeout for cntrl / tsf*/
    TB_LOOK                     =   0x4,            /* timeout for look       */
    TB_RECV                     =   0x8,            /* timeout for recv       */
    TB_SEND                     =   0x10,           /* timeout for send       */
    TB_WEF                      =   0x20,           /* timeout for wef        */
    TB_ALL                      =   0xFF            /* timeout for all svcs   */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


#define CPL_BLOCK                   (unsigned) -1   /* daloc complete block   */


#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define KL_END                      0u              /* killtsk end option     */
#define KL_DEL                      1u              /* killtsk delete option  */
#define KL_RDY                      2u              /* killtsk ready  option  */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_KillTaskOptions_old
{
    KL_END                      =   0,              /* killtsk end option     */
    KL_DEL                      =   1,              /* killtsk delete option  */
    KL_RDY                      =   2               /* killtsk ready  option  */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


#define CH_STD                      0u              /* createhpool standard pool*/
#define CH_HEAP                     1u              /* createhpool heap       */


#define RES_PTR                     0u              /* resblk passes pointer     */
#define RES_PHYS                    1u              /* resblk passes phys address*/
#define RES_RLS                     2u              /* resblk release reservation*/


#define HD_ONE                      0u              /* hdaloc free one block     */
#define HD_ALL                      1u              /* hdaloc free all owned bl. */


#define HA_OWN                      0u              /* haloc block for own task */
#define HA_NONE                     2u              /* haloc block for no task  */
#define RM_HALOC_FLAT_CODE          4u              /* haloc flat code          */
#define RM_HALOC_FLAT_DATA          12u             /* haloc flat data          */


#define OWN_TASK                    (unsigned) -1   /* indicate own task id   */


                          /* types of boundaries */

#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define BD_MBOX                     1u              /* bound limit for mailbox*/
#define BD_SMR                      2u              /* bound limit for smr    */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_BoundType_old
{
    BD_MBOX                     =   1,              /* bound limit for mailbox*/
    BD_SMR                      =   2               /* bound limit for smr    */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


                      /* types of interrupt handler */

#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define IH_CUR                      0u              /* read old handler          */
#define IH_DFT                      1u              /* take handler for unx. int.*/
#define IH_DI                       2u              /* DI- handler               */
#define IH_I                        3u              /* I - handler               */
#define IH_S                        4u              /* S - handler               */
#define IH_IS                       5u              /* I - handler and S-handler */
#define IH_TSK                      6u              /* task start with int. hdler*/
#define IH_MBOX                     7u              /* send message handler      */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_InterruptHandlerType_old
{
    IH_CUR                      =   0,              /* read old handler          */
    IH_DFT                      =   1,              /* take handler for unx. int.*/
    IH_DI                       =   2,              /* DI- handler               */
    IH_I                        =   3,              /* I - handler               */
    IH_S                        =   4,              /* S - handler               */
    IH_IS                       =   5,              /* I - handler and S-handler */
    IH_TSK                      =   6,              /* task start with int. hdler*/
    IH_MBOX                     =   7               /* send message handler      */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */

#define IH_FREE                     0u              /* free old handler       */
#define IH_HOLD                     0x40u           /* do not free old handler*/
  
#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define IH_HW                       0u              /* hardware interrupt     */
#define IH_SW                       0x80u           /* software interrupt     */
#else /* any not-Intel, not-CADUL and not-Microsoft compiler */
enum RM_IntType_old         /* interrupt kinds */
{
    IH_HW                       =   0,              /* hardware interrupt     */
    IH_SW                       =   0x80            /* software interrupt     */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


         /*  status macros for the check of the rmos-systemcalls */

#define CARRY_SET                   0x0001u
#define SIGN_SET                    0x0080u
#define ZERO_SET                    0x0040u
#define OVFL_SET                    0x0800u


                /*  macros for specific RMOS3-systemcalls */

#ifndef ACS_ER
#define ACS_ER                      0x9Au
#define ACS_RW                      0x92u
#define ACS_RD                      0x96u
#define ACS_RWD                     0x96u
#endif /* ACS_ER */


                     /*  task flags when using create */

#if defined(_ARCHITECTURE_) || defined(CADUL) || defined(_MSC_VER)
#define TFL_NPX                     0x0001u         /* task uses npx                */
#define TFL_NOHLT                   0x0004u         /* task may not be halted       */
#define TFL_OVPRI                   0x0008u         /* override priority            */
#define TFL_NEW_IF                  0x0010u         /* svc call from new interface  */
#define TFL_ALLOC                   0x0080u         /* tcd/tcb combination was      */
                                                    /* allocated from the smr (dynamically created task) */
#define TFL_STK                     0x0100u         /* auto stack allocation        */
#define TFL_DS                      0x0200u         /* auto data segment allocation */
#else /* any not-Intel and not-Microsoft compiler */
enum RM_TCD_Flags_old
{
    TFL_NPX                     =   0x0001,         /* task uses npx                */
    TFL_NOHLT                   =   0x0004,         /* task may not be halted       */
    TFL_OVPRI                   =   0x0008,         /* override priority            */
    TFL_NEW_INTERFACE           =   0x0010,         /* svc call from new interface  */
    TFL_TCD_ALLOC               =   0x0080,         /* tcd/tcb combination was      */
                                                    /* allocated from the smr (dynamically created task) */
    TFL_STK                     =   0x0100,         /* auto stack allocation        */
    TFL_DS                      =   0x0200          /* auto data segment allocation */
};
#endif /* _ARCHITECTURE_ || CADUL || _MSC_VER */


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


                         /* defines for busy task */

#define X_BU_OK                     0
#define X_BU_FAILED                 -1


/***************************************************************
 prototypes for busy task
 ***************************************************************/

#ifndef _RM_BUSYTASK_
#define _RM_BUSYTASK_

#ifdef _ARCHITECTURE_  
 #pragma PARAMS (x_bu_get, x_bu_init)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int  _FAR _FIXED    x_bu_get  (char *busy_ptr);
int  _FAR _FIXED    x_bu_init (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RM_BUSYTASK_ */


/***************************************************************
 Restore structure alignment to commandline specification
 ***************************************************************/

#if defined _MSC_VER
#pragma pack()
#endif

#ifdef __BORLANDC__
#pragma option -a.
#endif


#endif /* _SVC_H_ */
