/*--FILE HEADER---------------------------------------------------------------
;
;   filename    : RMNUC.H
;   version     : 0006
;   contents    : External nucleus variables definitions
;                 and function prototypes
;   author      : K.P.H.
;   date        : Dec 04, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT---------------------------------------------
;
;   function    : prototypes of nucleus functions and nucleus data
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER--------------------------------------------------------
;
;---MODIFICATION HEADER-------------------------------------------------------
;
;   Jan 18, 1995  K.P.H. 0001  Original issue
;   Feb 15, 1995  K.P.H. 0002  Additional Modification for RMOS2
;   Dec 15, 1995  K.P.H. 0003  Modification for RMOS V3.12
;   Feb 14, 1996  K.P.H. 0004  Additional modification for RMOS V3.12
;   Dec 04, 1996  K.P.H. 0005  Modification for RMOS V3.20
;   Jul 14, 2001  B.N.   0006  Modification for RMOS V3.21
;
;---END OF MODIFICATION HEADER----------------------------------------------*/

#ifndef _RMNUC_H_
#define _RMNUC_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _RMTYPES_H_
#include <rmtypes.h>
#endif  /* _RMTYPES_H_ */

#ifndef RMNUC_MODEL
#define RMNUC_MODEL
#endif

struct ptr_align         /* RMOS3: store a 48 bit sel:ofs ptr in a QWORD */
{                        /* RMOS2: store a 32 bit sel:ofs ptr in a DWORD */
    rmfarproc       ptr;
#if RM3    
    ushort  pad;
#endif
};

/****************************************************************************/
/*  nucleus data                                                            */
/****************************************************************************/
/* constant data in nucleus code segment */
extern  const ushort RMNUC_MODEL x_nucseg;             /* selector of nucleus */
extern  const ushort RMNUC_MODEL x_dataseg;            /* selector of nucleus data*/
extern  const ushort RMNUC_MODEL x_cfgseg;             /* selector of configuration */
extern  const ushort RMNUC_MODEL x_c_gef_dyn_num;      /* maximum number of event flags */
extern  const ushort RMNUC_MODEL x_c_mailbox_dyn_num;  /* maximum number of mailboxes   */
extern  const ushort RMNUC_MODEL x_c_mem_pool_dyn_num; /* maximum number of memory pools   */
extern  const ushort RMNUC_MODEL x_c_sema_dyn_num;     /* maximum number of semaphores  */
extern  const ushort RMNUC_MODEL x_c_system_data;
extern  const ushort RMNUC_MODEL x_c_hook_num;
extern  const ushort RMNUC_MODEL x_c_user_num_code;
extern  const ushort RMNUC_MODEL x_c_user_num_data;
extern  const ushort RMNUC_MODEL x_c_task_num;         /* maximum number of tasks   */
extern  const uchar  RMNUC_MODEL x_hook_table[]; 
extern  const uchar  RMNUC_MODEL x_user_table_code[]; 
extern  const ushort RMNUC_MODEL xmtosds;              /* Data segment */
extern  const ushort RMNUC_MODEL xmtosgrom;            /* Global ROM segment */
extern  const ushort RMNUC_MODEL xversion;             /* Version of operating system */

extern  uint         RMNUC_MODEL xoffset;        /* General purpose offset of xpointer */
extern  ushort       RMNUC_MODEL xsegment;       /* General purpose segment of xpointer */
extern  uchar        RMNUC_MODEL xdevnum;        /* Current device number */
extern  uchar        RMNUC_MODEL xdevunit;       /* Current device unit number */
extern  uchar        RMNUC_MODEL xtunit;         /* Time interval unit code */
extern  uchar        RMNUC_MODEL xtnum;          /* Number of time interval units */
extern  uchar        RMNUC_MODEL xpoolnum;       /* Pool number for block allocation */
extern  uint         RMNUC_MODEL xblklen;        /* Length of block needed, bytes */
extern  ushort       RMNUC_MODEL xtask;          /* Task-ID */
extern  uchar        RMNUC_MODEL xpris;          /* Priority source options */
extern  uchar        RMNUC_MODEL xpriv;          /* Priority to use */
extern  uint         RMNUC_MODEL xp1;            /* Parameter 1 */
extern  uint         RMNUC_MODEL xp2;            /* Parameter 2 */
extern  uchar        RMNUC_MODEL xgrp;           /* Global event flag group ID */
extern  uint         RMNUC_MODEL xflags;         /* Event flag mask  */
extern  uchar        RMNUC_MODEL xbox;           /* Local mailbox ID */
extern  uchar        RMNUC_MODEL xgenb;          /* General purpose uchar */
extern  ushort       RMNUC_MODEL xgenw;          /* General purpose ushort */
extern  ulong        RMNUC_MODEL xgend;          /* General purpose ulong */
extern  ushort       RMNUC_MODEL xseg;           /* Selector for S-STATE routines */
extern  ulong        RMNUC_MODEL xseglim;        /* Segment limit for S-STATE routines */
extern  uchar        RMNUC_MODEL xmonmod;        /* Debugger Monitor Mode Indicator*/
extern  ulong        RMNUC_MODEL x_init_ext;     /* for initialization */
extern  uint         RMNUC_MODEL x_srb_avail;    /* Available SRB's */
extern  ulong        RMNUC_MODEL x_timeout_value;/* timeout value for new SVCs */
extern  uchar        RMNUC_MODEL x_driver_dyn_num;
extern  uchar        RMNUC_MODEL x_unit_dyn_num;
extern  ushort       RMNUC_MODEL x_freeucd;
extern  ushort       RMNUC_MODEL x_freeucb;
extern  ushort       RMNUC_MODEL x_cfgstate;     /* Configuration state of rmos */
extern  ushort       RMNUC_MODEL x_errstate;     /* Configuration state of rmos */
extern  selector     RMNUC_MODEL x_flat_rw_sel;  /* Flat read/write selector */
extern  selector     RMNUC_MODEL x_flat_er_sel;  /* Flat read/write selector */
extern  ushort       RMNUC_MODEL x_csys_device;  /* System device (0 after init) */
extern  ushort       RMNUC_MODEL x_csys_unit;    /* System unit (0 after init) */
extern  uint         RMNUC_MODEL x_c_task_deb;   /* Debugger id for exception handler */
extern  ushort       RMNUC_MODEL x_c_task_excout;/* id of exception handler task */
extern  ushort       RMNUC_MODEL x_c_task_excout_pri;/* priority of exception handler task */
extern  uchar        RMNUC_MODEL x_exctype;      /* 0xFF = dont call svc exception handler */
extern  ushort       RMNUC_MODEL x_c_rep_device;
extern  ushort       RMNUC_MODEL x_c_rep_unit;
extern  uint         RMNUC_MODEL x_c_rep_table_size;
extern  uchar        RMNUC_MODEL x_ready_flag;   /* state variable for scheduler */
extern  ushort       RMNUC_MODEL x_rr_bound;     /* Round robin ticks */
extern  uchar        RMNUC_MODEL x_3964_device;
extern  RmSysB       RMNUC_MODEL x_sysb;         /* system control block */
extern  ulong        RMNUC_MODEL x_nuctrace;

extern  rmfarproc    RMNUC_MODEL x_proc_cr_inheritance;	/* crun handler */
extern  rmfarproc    RMNUC_MODEL x_proc_cr_remove_inheritance;	/* crun handler */
extern  rmfarproc    RMNUC_MODEL x_proc_cr_endtask;	/* crun handler */
extern  rmfarproc    RMNUC_MODEL x_proc_cr_deletetask;	/* crun handler */
extern  rmfarproc    RMNUC_MODEL x_proc_cr_killtask;	/* crun handler */
extern  rmfarproc    RMNUC_MODEL x_proc_cli_killtask;	/* cli handler */

extern  rmfarproc    RMNUC_MODEL x_proc_deb_db_cont;    /* continue task from */
														/* debugger breakpnt  */
														/* EBX=TCB            */

extern  void _FAR *  RMNUC_MODEL xpointer;       /* Pointer for common purposes */
extern  void _FAR *  RMNUC_MODEL xerrmsg;        /* Error message transport address */
extern  uchar        RMNUC_MODEL x_user_table_data[]; 
extern  uchar        RMNUC_MODEL x_savehwint[];
extern  uchar        RMNUC_MODEL x_system_table[]; 
extern  uchar        RMNUC_MODEL x_timestrct[];
extern  rmnearproc   RMNUC_MODEL x_dyn_jt[];

#ifndef _RM_DRIVER_FLAG_
#define _RM_DRIVER_FLAG_
extern  RmIRBStruct _FAR  * RMNUC_MODEL xcirb;   /* Driver interface current IRB */
extern  RmDCBStruct _NEAR * RMNUC_MODEL xdcb;
extern  RmUCBStruct _NEAR * RMNUC_MODEL xucb;
extern  RmIOStatusStruct    RMNUC_MODEL xstatus; /* Status transport variable */
#endif /* _RM_DRIVER_FLAG_ */

extern  RmDCBStruct _NEAR * RMNUC_MODEL x_dcb_q;
extern  RmUCDStruct _NEAR * RMNUC_MODEL x_freeucdptr;
extern  RmUCBStruct _NEAR * RMNUC_MODEL x_freeucbptr;
extern  struct ptr_align    RMNUC_MODEL x_pit_int_tab[];   /* Timer link table */

typedef struct
{
    uchar       b_day;
    uchar       b_month;
    ushort      b_year;
    uchar       b_hour;
    uchar       b_min;
    uchar       b_sec;
}   asctod_struc;       /* layout of binary system time */

extern  asctod_struc RMNUC_MODEL x_asctod;

extern  uint         _FAR        x_vm_task_dos;  /* ID of dos task  */

/* external definition for decode tables */
extern const char (* const RMNUC_MODEL x_svc_err_text[]);   /* table of SVC error messages */
extern const int  RMNUC_MODEL x_first_svc_err;
extern const int  RMNUC_MODEL x_last_svc_err;
extern const char (* const RMNUC_MODEL x_svc_name_text[]);  /* table of old SVC names */
extern const int  RMNUC_MODEL x_first_svc_name;
extern const int  RMNUC_MODEL x_last_svc_name;
extern const char (* const RMNUC_MODEL x_api_name_text[]);  /* table of SVC names */
extern const int  RMNUC_MODEL x_first_api_name;
extern const int  RMNUC_MODEL x_last_api_name;

extern const char (* const RMNUC_MODEL x_load_error_text[]);  /* table of loader errors */
extern const int  RMNUC_MODEL x_first_load_err;
extern const int  RMNUC_MODEL x_last_load_err;
int _FAR xc_decode_load_error(uint type, int number, char *text_buf);

/****************************************************************************/
/*  nucleus functions                                                       */
/****************************************************************************/
void  _NEAR xhaloc(void);           /* Allocate memory from pool */
void  _NEAR xhdaloc(void);          /* Return memory to pool */
void  _NEAR xcatalog(void);         /* Catalog function */
void  _NEAR xsystem(void);          /* Switch from DI-State to S-State */
void  _NEAR xexsys(void);           /* Exit S-State */
void  _NEAR xaloc(void);            /* Allocate memory from pool */
void  _NEAR xdaloc(void);           /* Return memory to pool */
void  _NEAR xdeltmb(void);          /* Delete TMB */
void  _NEAR xdevdata(void);         /* Calculate offset of UCB and DCB */
void  _NEAR xdqtmb(void);           /* Remove TMB */
void  _NEAR xdword(void);           /* Calculate address from offset */
void  _NEAR xgetsmr(void);          /* Allocate System memory */ 
void  _NEAR xiodone(void);          /* Exit I/O request type I */
void  _NEAR xjmp_xover(void);       /* Exit I/O request type II from "c" */
void  _NEAR xover(void);            /* Exit I/O request type II */
void  _NEAR xputsmr(void);          /* Return system memory */
void  _NEAR xqsetuns(void);         /* Queue start task for unexpected intr */
void  _NEAR xqsirb(void);           /* Put actual IRB in serial queue */
void  _NEAR xqpirb(void);           /* Put actual IRB in parallel queue */
void  _NEAR xqstrt(void);           /* Queue start task request */
void  _NEAR xqtmb(void);            /* Put TMB in queue */
void  _NEAR xrecv(void);            /* Get message from mailbox */
void  _NEAR xref(void);             /* Reset global event flag */
void  _NEAR xsef(void);             /* Set global event flag */
void  _NEAR xsend(void);            /* Send message to mailbox */
void  _NEAR xsetuns(void);          /* Start task for unexpected interrupts */
void  _NEAR xtef(void);             /* Test global event flag */
void  _NEAR xtimeout(void);         /* Install timeout for device type II */
void  _NEAR xerrlog(void);          /* Pass error message */
void  _NEAR xphysadr(void);         /* calculate physical address */
#if RM3
void  _NEAR xphysadrp(void);        /* calculate physical address (paged system) */
#endif
void  _NEAR xcreatedesc(void);      /* Get new descriptor */
void  _NEAR xchangedesc(void);      /* Change descriptor */
void  _NEAR xdeldesc(void);         /* Delete descriptor */
void  _NEAR xchangedesaccess(void); /* Change descriptor access rigths */

void _FAR x_3964_time_intr_up( void );

/* --------------- */
/* NUC C functions */
/* --------------- */
#if defined (_ARCHITECTURE_)
#pragma fixedparams("xc_catalog_gen","xc_look_gen","xc_list_gen")
#pragma fixedparams("xc_uncatalog_gen","xc_getname_gen")
#pragma fixedparams("xc_decode_time","xc_decode_gen")
#pragma fixedparams("xc_check_code_sel","xc_get_boot_path")
#pragma fixedparams("x_pit_int","x_pit_int_i","x_get_task_id_f")
#pragma fixedparams("xc_setclocks")
#pragma varparams  ("xc_devdata")
#ifdef RMNUC
#pragma interrupt  ("xc_sh_handler")
#endif
#endif

uint _FIXED _NEAR  xc_catalog_gen   ( char scatalog,
									  uchar kind,
									  ushort id,
                                      ulong  ide,
                                      char _FAR *strp );
uint _FIXED _NEAR  xc_look_gen      ( char slook, 
                                      RmEntryStruct _FAR *iptr,
                                      ulong time,
                                      char _FAR *strp );
uint _FIXED _NEAR  xc_list_gen      ( char slist, 
                                      uchar type, 
                                      ushort      count,
                                      uint _FAR  *ix_ptr,
                                      uint _FAR  *count_ptr,
                                      RmEntryStruct _FAR *info_ptr );
uint _FIXED _NEAR  xc_uncatalog_gen ( char unscatalog,
                                      char _FAR *strp );
uint _FIXED _NEAR  xc_getname_gen   ( uchar  kind,
                                      ushort id,
                                      ulong  ide,
                                      char *cp );
int  _FIXED _NEAR  xc_decode_gen    ( uint type, 
                                      int number,
									  char *text_buf );
char * _FIXED _NEAR xc_decode_time  ( char *buffer);
char * _FIXED _NEAR xc_get_boot_path( char *buffer );    /* get bootpath from x_sysb */
int    _FIXED _NEAR xc_check_code_sel(ushort sel );    /* check if sel is a valid code selector */
int    _FIXED _NEAR xc_setclocks    ( void _FAR * time );
uint   _FIXED _FAR  x_get_task_id_f ( RmTCBStruct _NEAR *ptcb);
void   _FIXED _FAR  x_socket_entry  ( void );
void   _FIXED _FAR  x_pit_int       ( void );
void   _FIXED _FAR  x_pit_int_i     ( void );

int    _VAR   _NEAR xc_devdata      (uint dev, uint unit, /* Calculate addr. */
									 RmDCBStruct _NEAR * _NEAR *dcb,
									 RmUCBStruct _NEAR * _NEAR *ucb);
void   _FAR         xc_sh_handler   ( void );

/* ---------------------*/
/* call C NUC functions */
/* ---------------------*/
#if defined (_ARCHITECTURE_)
#pragma varparams  ("x_nucprintf","x_nucsprintf","x_errprintf","errprintf")
#pragma varparams  ("xc_get_tcb_adr_f","xc_get_blockptr_f","xc_free_blockptr_f")
#if RM3
#pragma fixedparams("xc_set_interrupt_to_rmos","xc_reset_interrupt")
#pragma fixedparams("xc_task_function","xc_task_type","xc_task_remove")
#pragma fixedparams("xc_do_seqtask","xc_del_seqtaskto")
#endif
#endif

int          _VAR _FAR    x_nucprintf   (   const char *fmtstr,...);
int          _VAR _FAR    x_nucsprintf  (   char *bufr,
											const char *fmtstr,...);
int          _VAR _FAR    x_errprintf   (   const char *who,
											const char *fmtstr,...);
int          _VAR _FAR    errprintf     (   const char *who,
											const char *fmtstr,...);

RmTCBStruct _FAR * _VAR _FAR xc_get_tcb_adr_f(uint id );
void  _FAR * _VAR _FAR xc_get_blockptr_f(   uint mode,
											uint owner,
											uint poolid,
											ulong size );
int   _VAR _FAR        xc_free_blockptr_f ( uint poolid,
											void _FAR *blockptr );
#if RM3
int   _FIXED _FAR      xc_task_function (   uint type,
											rmfarproc handler );
int   _FIXED _FAR      xc_task_type     (   uint taskid,
											uint mode,
											uint type );
int   _FIXED _NEAR     xc_task_remove   (   RmTCBStruct _NEAR * ptcb );
int   _FIXED _NEAR     xc_set_interrupt_to_rmos ( uint irq );
int   _FIXED _NEAR     xc_reset_interrupt       ( uint irq );
void  _FIXED _NEAR     xc_do_seqtask    (   RmTCBStruct _NEAR * ptcb );
void  _FIXED _NEAR     xc_del_seqtaskto (   RmTCBStruct _NEAR * ptcb );
#endif

/* ------------------------- */
/* call NUC functions from C */
/* ------------------------- */
#if defined (_ARCHITECTURE_)
#pragma varparams ( "xc_set_vec", "x_asm_call", "x_start_init_task")
#pragma varparams ( "xc_put_smr", "xc_queue", "xc_dqueue", "xc_task_state" )
#pragma varparams ( "xc_set_ready", "xc_init_timeout", "xc_cancel_timeout" )
#pragma varparams ( "xc_get_smr0", "xc_cut_heap", "xc_get_tcb_adr" )
#pragma varparams ( "xc_set_time" )
#if RM3
#pragma varparams ( "xc_get_limit", "xc_get_cr0", "xc_get_cr2", "xc_get_cr3" )
#endif
#endif

void         _VAR _NEAR   xc_set_vec    ( uchar intno,
                                          void *intadr);
void         _VAR _NEAR   x_asm_call    ( void RM_MODEL *f ); /* call asm from C and save regs */
void _NEAR * _VAR _NEAR   xc_get_smr0   ( void );   /*  get system memory.          */
void         _VAR _NEAR   xc_put_smr    ( void _NEAR * smr );
void         _VAR _NEAR   xc_queue      ( void _NEAR * block,
                                          void _NEAR * queue_head );
int          _VAR _NEAR   xc_dqueue     ( void _NEAR * block, 
                                          void _NEAR * queue_head );
void         _VAR _NEAR   xc_task_state ( uint state, 
                                          void _NEAR * tcb );
void         _VAR _NEAR   xc_set_ready  ( void _NEAR * tcb );
void         _VAR _NEAR   xc_init_timeout(uint svc, 
                                          void _NEAR * block,
                                          void _NEAR * queue_head );
void         _VAR _NEAR   xc_cancel_timeout( uint svc,
                                          void _NEAR * tcb );
void _NEAR * _VAR _NEAR   xc_cut_heap   ( uint length );
void _NEAR * _VAR _NEAR   xc_get_tcb_adr( uint id );
int          _VAR _NEAR   xc_set_time   ( uint mode, void _FAR * time );

#if RM3
uint         _VAR _NEAR   xc_get_limit  ( uint sel );
uint         _VAR _NEAR   xc_get_cr0    ( void );
uint         _VAR _NEAR   xc_get_cr2    ( void );
uint         _VAR _NEAR   xc_get_cr3    ( void );
#endif

/* ------------------------- */
/* fast NUC memory functions */
/* ------------------------- */
#if defined (_ARCHITECTURE_)
#pragma fixedparams("xc_nmemcmp","xc_nfmemcmp","xc_fmemcmp")
#pragma fixedparams("xc_nmemset","xc_fmemset","xc_nmemchr","xc_fmemchr")
#pragma fixedparams("xc_nmemcpy","xc_fmemcpy","xc_cpyin","xc_cpyout")
#pragma fixedparams("xc_strcpyout","xc_fstrcpyout")
#endif

int    _FIXED  _NEAR xc_nmemcmp  (const void _NEAR *s1, const void _NEAR *s2, uint n);
int    _FIXED  _NEAR xc_nfmemcmp (const void _NEAR *s1, const void _FAR *s2, uint n);
int    _FIXED  _NEAR xc_fmemcmp  (const void _FAR *s1,  const void _FAR *s2,  uint n);
void   _FIXED  _NEAR xc_nmemcpy  (void _NEAR *s1, const void _NEAR *s2, uint n);
void   _FIXED  _NEAR xc_fmemcpy  (void _FAR *s1,  const void _FAR *s2,  uint n);
void   _FIXED  _NEAR xc_cpyin    (void _NEAR *s1, const void _FAR *s2,  uint n);
void   _FIXED  _NEAR xc_cpyout   (void _FAR *s1,  const void _NEAR *s2, uint n);
void   _FIXED  _NEAR xc_nmemset  (void _NEAR *s, int c, ushort n);
void   _FIXED  _NEAR xc_fmemset  (void _FAR *s,  int c, ushort n);
void _NEAR * _FIXED _NEAR xc_nmemchr (void _NEAR *s, int c, ushort n);
void _FAR  * _FIXED _NEAR xc_fmemchr (void _FAR *s,  int c, ushort n);
void   _FIXED  _NEAR xc_strcpyout    (void _FAR *s1, const void _NEAR *s2);
void   _FIXED  _NEAR xc_fstrcpy      (void _FAR *s1, const void _FAR *s2);

/* ----------------------------- */
/* SVC internal entry prototypes */
/* ----------------------------- */
typedef void _FAR _FIXED svc_xentry( void );
/*
#if RM3
typedef void svc_xentry( void );
#else
typedef void _FAR _FIXED svc_xentry( void );
#endif
*/
svc_xentry  x_dummy;
svc_xentry  x_set_svc;
svc_xentry  x_strt;
svc_xentry  x_qstrt;
svc_xentry  x_endt;
svc_xentry  x_endr;
svc_xentry  x_cpri;
svc_xentry  x_pause;
svc_xentry  x_resume;
svc_xentry  x_sef;
svc_xentry  x_ref;
svc_xentry  x_tef;
svc_xentry  x_sefet;
svc_xentry  x_wef;
svc_xentry  x_send;
svc_xentry  x_recv;
svc_xentry  x_time;
svc_xentry  x_stime;
svc_xentry  x_qcopy;
svc_xentry  x_rio;
svc_xentry  x_rsf;
svc_xentry  x_tsf;
svc_xentry  x_create;
svc_xentry  x_delete;
svc_xentry  x_deltsk;
svc_xentry  x_get_tables;
svc_xentry  x_hsfs;
svc_xentry  x_hsfsm;
svc_xentry  x_catalog;
svc_xentry  x_createdriv;
svc_xentry  x_createflag;
svc_xentry  x_creatembox;
svc_xentry  x_createsema;
svc_xentry  x_getstat;
svc_xentry  x_deletedriv;
svc_xentry  x_deleteflag;
svc_xentry  x_deletembox;
svc_xentry  x_deletepool;
svc_xentry  x_deletesema;
svc_xentry  x_getentry;
svc_xentry  x_getlinaddr;
svc_xentry  x_createdesc;
svc_xentry  x_chgdesc;
svc_xentry  x_deldesc;
svc_xentry  x_chgdescacs;
svc_xentry  x_link_timer_routine;
svc_xentry  x_unlink_timer_routine;
svc_xentry  x_list;
svc_xentry  x_uncatalog;
svc_xentry  x_enablescheduler;
svc_xentry  x_disablescheduler;
svc_xentry  x_timeout;
svc_xentry  x_createhpool;
svc_xentry  x_haloc;
svc_xentry  x_getsize;
svc_xentry  x_killtsk;
svc_xentry  x_resblk;
svc_xentry  x_hdaloc;
svc_xentry  x_timerstart;
svc_xentry  x_timercancel;
svc_xentry  x_bound;
svc_xentry  x_get_sysb;
svc_xentry  x_intrhand;
svc_xentry  x_getname;
svc_xentry  x_dbgsvc;
svc_xentry  x_repsvc;
svc_xentry  x_cntrl;
svc_xentry  x_aloc;
svc_xentry  x_daloc;
svc_xentry  x_createdsct;
svc_xentry  x_deletedsct;
svc_xentry  x_dscrte;
svc_xentry  x_setint;
svc_xentry  x_createpool;
svc_xentry  x_init_os;
svc_xentry  x_set_putchar;
svc_xentry  x_set_dev_handler;
svc_xentry  x_create_driver;
svc_xentry  x_create_unit;
svc_xentry  x_create_os;
svc_xentry  x_run_os;
svc_xentry  x_delete_driver;
svc_xentry  x_delete_unit;
svc_xentry  x_set_os;
svc_xentry  x_decode;
svc_xentry  x_decode_dummy;
svc_xentry  x_linkdecode;
svc_xentry  x_gettaskid;
svc_xentry  x_gettcbadr;
svc_xentry  x_gettaskpri;
svc_xentry  x_gettaskstate;
svc_xentry  x_activatetask;
svc_xentry  x_createsmall;
svc_xentry  x_createchild;
svc_xentry  x_suspend;
svc_xentry  x_lsef;
svc_xentry  x_lref;
svc_xentry  x_increasesmrbound;
svc_xentry  x_sethw;
svc_xentry  x_sethwclocktime;
svc_xentry  x_gethw;
svc_xentry  x_gethwclocktime;
svc_xentry  x_getabstime;
svc_xentry  x_getsystemperiod;
svc_xentry  x_getphysaddr;
svc_xentry  x_flattosegaddr;
svc_xentry  x_segtoflataddr;
svc_xentry  x_realloc;
svc_xentry  x_freeall;
svc_xentry  x_createmboxm;
svc_xentry  x_deletemboxm;
svc_xentry  x_sendm;
svc_xentry  x_recvm;
svc_xentry  x_boundm;
svc_xentry  x_deletepool;
svc_xentry  x_haloc_id;
svc_xentry  x_getmempoolinfo;
svc_xentry  x_setsystemperiod;
svc_xentry  x_setclocks;
svc_xentry  x_linklrs;
svc_xentry  x_mapmemory;
svc_xentry  x_sequencetask;
svc_xentry  x_statm;

#if ! RM3		/* SVC Vector entries for RMOS2 */
void _FAR x_svc_int ( void );
void _FAR x_svc_int1( void );
void _FAR x_svc_int2( void );
#endif /* ! RM3 */

/* --------------------------------- */
/* hsfs external function prototypes */
/* --------------------------------- */
#if defined (_ARCHITECTURE_)
#pragma fixedparams("x_hd_init","x_load_init","x_cli_entry")
#endif

int _FIXED _FAR x_hd_init (  int ConDeviceId_i,
                             int ConUnitId_i,
                             int HDDeviceId_i,
                             int HDUnitId_i,
                             int PoolId_i,
                             long MaxPoolSize_i,
                             uchar Mode_b,
                             char VolNameStart_cp[] ) ;
void _FIXED _FAR x_load_int( void );
void _FIXED _FAR x_cli_entry(void );

/* ------------------------------------- */
/* debugger external function prototypes */
/* ------------------------------------- */
#if defined (_ARCHITECTURE_)
#pragma fixedparams ("x_deb_config", "x_deb_cmd_hlldeb", "x_deb_cmd_monitor" )
#pragma fixedparams ("x_deb_cmd_disasm", "x_deb_cmd_float", "x_deb_cmd_report")
#pragma fixedparams ("x_deb_cmd_task",  "x_deb_cmd_misc")
#pragma fixedparams ("x_ss", "x_bpt")
#endif

void _FIXED _FAR x_deb_config     ( void );
void _FIXED _FAR x_deb_cmd_hlldeb ( void );
void _FIXED _FAR x_deb_cmd_monitor( void );
void _FIXED _FAR x_deb_cmd_disasm ( void );
void _FIXED _FAR x_deb_cmd_float  ( void );
void _FIXED _FAR x_deb_cmd_report ( void );
void _FIXED _FAR x_deb_cmd_task   ( void );
void _FIXED _FAR x_deb_cmd_misc   ( void );
void _FIXED _FAR x_ss             ( void );
void _FIXED _FAR x_bpt            ( void );

#endif /* _RMNUC_H_ */

