/*****************************************************************************/
/*                                                                           */
/*   Filename:  PPPDRV.H                                                     */
/*                                                                           */
/*   Author:    J.S.                 Department:      A&D SE E41             */
/*   Date:      19.11.1998                                                   */
/*                                                                           */
/*   Development Kit / Compiler :  C-Compiler Organon V6.x                   */
/*                                                                           */
/*   Copyright (C) Siemens AG 1998. All rights reserved.                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Description: Header file for PPP-Driver                                 */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Modifications:                                                          */
/*                                                                           */
/*----------+-------------+-----+--------------------------------------------*/
/*  Date    |    Author   | Sign|                Description                 */
/*----------+-------------+-----+--------------------------------------------*/
/* 19.11.98 | J.S.        |     | original issue                             */
/*          |             |     |                                            */
/*          |             |     |                                            */
/*----------+-------------+-----+--------------------------------------------*/
/*          |             |     |                                            */
/*          |             |     |                                            */
/*          |             |     |                                            */
/*          |             |     |                                            */
/*          |             |     |                                            */
/*----------+-------------+-----+--------------------------------------------*/
/*                                                                           */
/*****************************************************************************/

#ifndef _PPPDRV_H_
#define _PPPDRV_H_

#ifndef NULL   
#define NULL ((void *) 0);       
#endif

/* ========================================================================= */
/*                                                                           */
/* General                                                                   */
/*                                                                           */
/* ========================================================================= */

#define PPPDRV_MBX      "PPPDRV_MBX"

/* ========================================================================= */
/*                                                                           */
/* Task-start-parameter (pointed to by EAX/EBX)                              */
/*                                                                           */
/* ========================================================================= */


#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPPDRV_PARAM_STRUCT)
#endif

typedef struct PPPDRV_PARAM_STRUCT {
    uint        MailboxID;        /* Mailbox quit-ID                        */
                                  /* the following are parameters from      */ 
                                  /* RcInitETHDPRenv                        */
    uint        IOBaseAddr;       /* I/O-BaseAddress of UART.               */
    uint        IRQ;              /* IRQ-Number                             */
    ulong       Baudrate;         /* Baudrate in bits/s                     */
    char        Parity;           /* Parity : 'N', 'E', 'O'                 */
    uint        Databits;         /* Number of databits (7 or 8)            */
    uint        Stopbits;         /* Number of Stopbits (1 or 2)            */
    uint        FIFO;             /* FIFO to be used if present             */
                                  /* 0: dont use, 1: use FIFO               */
    uint        ConsoleFlag;      /* Console-Flag                           */
} PPPDRV_PARAM_TYPE;

/*---------------------------------------------------------------------------*/
/* ConsoleFlag                                                               */
/*---------------------------------------------------------------------------*/

#define PPPDRV_CONSOLE_OUT       1   /* Startupmessages on Stdio             */
#define PPPDRV_CONSOLE_NO_OUT    0   /* No Startup-messages                  */

/*---------------------------------------------------------------------------*/
/* Baudrate                                                                  */
/*---------------------------------------------------------------------------*/

#define PPPDRV_BR_4800           4800  
#define PPPDRV_BR_9600           9600  
#define PPPDRV_BR_19200          19200 
#define PPPDRV_BR_38400          38400 
#define PPPDRV_BR_57600          57600 
#define PPPDRV_BR_115200         115200

/*---------------------------------------------------------------------------*/
/* PARITY                                                                    */
/*---------------------------------------------------------------------------*/

#define PPPDRV_PA_NO             'N'    
#define PPPDRV_PA_EVEN           'E'    
#define PPPDRV_PA_ODD            'O'    

/* ========================================================================= */
/*                                                                           */
/* Quit-Mailbox (pMail points to)                                            */
/*                                                                           */
/* (Mailbox send from Drivertask after Startupinitialitiation to the Mailbox */
/*  MailboxID from Task Startup-Parameters)                                  */
/*                                                                           */
/* ========================================================================= */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_TASK_QUIT_MBX_STRUCT)
#endif

typedef struct PPP_TASK_QUIT_MBX_STRUCT {
    int        error;      /* error occured in  initialization */
    uint       res1;  
    uint       res2;
} PPP_TASK_QUIT_MBX_TYPE;

/*---------------------------------------------------------------------------*/
/* error                                                                     */
/*---------------------------------------------------------------------------*/

#define PPPDRV_INIT_OK                 0 /* Driver Startup successful        */
#define PPPDRV_INIT_ERR_EXIST         -1 /* Driver-Mailbox already exists    */
                                         /* (driver may be already loaded)   */
#define PPPDRV_INIT_ERR_CREATE_MBX    -2 /* Error on Creating Driver MBX     */
                                         /* (other than already cataloged)   */
#define PPPDRV_INIT_ERR_PARAM         -3 /* Driver-Parameter error           */
#define PPPDRV_INIT_ERR_SET_HANDLER   -4 /* RMOS-Error on RmSetIntIS-Handler */
#define PPPDRV_INIT_ERR_ALOC          -5 /* RMOS-Error on RmAlloc            */
#define PPPDRV_INIT_ERR_CATALOG       -6 /* Could not find a free Catalog    */
                                         /* entry in the range PPP_00..PPP_99*/
                                         /* or Catalog-Error                 */
#define PPPDRV_INIT_ERR_HW_NOT_FOUND  -7 /* no UART found.                   */

                                         /* The following Error occures if   */
                                         /* an error occured while sending   */
                                         /* the   quit - mail.   This error  */
                                         /* is fatal! It is not put into the */
                                         /* the quit-mail! The task continues*/

#define PPPDRV_INIT_ERR_SEND_MAIL     -8 /* RMOS-Error on SendMail.          */


/* ========================================================================= */
/*                                                                           */
/* Timeout Mailbox                                                           */
/*                                                                           */
/*  (Send from Driver to his own Mailbox for Timeouthandling)                */
/*  (must not exceed 6 ushorts for RMOS3!)                                   */
/*                                                                           */
/* ========================================================================= */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPPDRV_MBX_TOUT_STRUCT)
#endif

typedef struct PPP_MBX_TOUT_STRUCT {
     ushort      UnitID;
     ushort      TimeoutType;      /* Timeout reason                         */
     ushort      reserved1;
     ushort      reserved2;
     ushort      reserved3;
     ushort      reserved4;
} PPP_MBX_TOUT_TYPE;

#define PPPDRV_TIMEOUT_SEND_CTS   0 /* timeout on transmit (waiting for CTS) */
#define PPPDRV_TIMEOUT_SEND       1 /* timeout on transmit (waiting for Int) */
#define PPPDRV_TIMEOUT_RECV       2 /* timeout on receive                    */

/* ========================================================================= */
/*                                                                           */
/* Interrupt Mailbox                                                         */
/*                                                                           */
/*  (Send from Interrupthandler to Drivertask)                               */
/*  (must not exceed 6 ushorts for RMOS3!)                                   */
/*                                                                           */
/* ========================================================================= */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_INT_STRUCT)
#endif

typedef struct PPP_MBX_INT_STRUCT {
     ushort      UnitID;                /* currently only one unit */
     ushort      IntIdent;              /* Interruptsource         */
     ushort      SyncCount;             /* Send: SyncCounter       */
                                        /* will be set to actual   */
                                        /* SendSyncCounter.        */
     uchar       Info1;                 /* Additional Info         */
     uchar       reserved1;
     ushort      reserved2;
     ushort      reserved3;
} PPP_MBX_INT_TYPE;

/*---------------------------------------------------------------------------*/
/* IntIdent                                                                  */
/*---------------------------------------------------------------------------*/

#define PPPDRV_INT_RECV          0   /* Receive. Data copied to receive-buff */
#define PPPDRV_INT_SEND          1   /* Transmit. Transmission completed     */
#define PPPDRV_INT_STATUS        2   /* Modem Status-register                */
#define PPPDRV_INT_CTS_WAIT      3   /* Wait for CTS have to initiated       */

/* ========================================================================= */
/*                                                                           */
/* SVC-Mailbox-Types (pMailParam points to)                                  */
/*                                                                           */
/* ========================================================================= */

#define PPP_MBX_READ              0x01 /* receive data frame (stack)         */
#define PPP_MBX_WRITE             0x02 /* transmit data frame (stack)        */
#define PPP_MBX_RESET             0x04 /* reset driver and controller (stack)*/

#define PPP_MBX_READ_USER         0x11 /* receive data frame (user)          */
#define PPP_MBX_WRITE_USER        0x12 /* transmit data frame (user)         */
#define PPP_MBX_RESET_USER        0x14 /* reset driver and controller (user) */

#define PPP_MBX_FLUSH             0x20 /* Flush receivebuffer of driver      */
#define PPP_MBX_SET_CHANNEL       0x21 /* Set Driver Channel                 */
#define PPP_MBX_CONFIG_EVENT      0x22 /* Config Eventflag                   */
#define PPP_MBX_GET_BUFFER_STATUS 0x23 /* Get receivebuffer status           */
#define PPP_MBX_GET_MODEM_STATUS  0x24 /* Get modem-status                   */

#define PPP_MBX_GET_DRV_CFG       0x30 /* get driver/controller hw-config    */
#define PPP_MBX_GET_STATS         0x31 /* driver stats                       */
#define PPP_MBX_GET_UNIT_STR      0x32 /* get Unit-structure                 */

/* ========================================================================= */
/*                                                                           */
/* SVC Mailbox defs..                                                        */
/*                                                                           */
/* ========================================================================= */

/*---------------------------------------------------------------------------*/
/* General Mail-Params pointed by pMailParam.                                */
/*                                                                           */
/* PPP_MBX_TYPE  *pMailParam;                                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_SVC_STRUCT)
#endif

typedef struct PPP_MBX_SVC_STRUCT {
    ushort      Type;      /* type of mail, see above */
    ushort      UnitID;
    uint        FlagID;
    uint        FlagMask;
    int   _FAR *pState;
    void  _FAR *pParam;   /* pointer to typespecific parameter              */
    void  _FAR *pQueue;   /* for driver internal queuing of requests        */
                          /* (no input param)                               */
} PPP_MBX_SVC_TYPE;


/*---------------------------------------------------------------------------*/
/* PPP_MBX_READ                                                              */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_READ_STRUCT)
#endif

typedef struct PPP_MBX_READ_STRUCT {
     void   _FAR   *pBuffer;       /* pointer to receivebuffer               */
     ushort         Length;        /* Length of receivebuffer                */
     ushort _FAR   *pIOCount;      /* Number of bytes received               */
} PPP_MBX_READ_TYPE;

/*---------------------------------------------------------------------------*/
/* PPP_MBX_WRITE                                                             */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_WRITE_STRUCT)
#endif

typedef struct PPP_MBX_WRITE_STRUCT {
     void   _FAR *pBuffer;         /* pointer to writebuffer                 */
     ushort       Length;          /* Length of writebuffer                  */
} PPP_MBX_WRITE_TYPE;

/*---------------------------------------------------------------------------*/
/* PPPDRV_MBX_RESET                                                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* PPP_MBX_READ_USER                                                         */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_READ_USER_STRUCT)
#endif

typedef struct PPP_MBX_READ_USER_STRUCT {
     void   _FAR   *pBuffer;       /* pointer to receivebuffer               */
     ushort         Length;        /* Length of receivebuffer                */
     ushort _FAR   *pIOCount;      /* Number of bytes received               */
     uchar          EndChar;       /* End Character (0=no)                   */
     ulong          Timeout;       /* Timeout in ms (0=no)                   */
} PPP_MBX_READ_USER_TYPE;

/*---------------------------------------------------------------------------*/
/* PPP_MBX_WRITE_USER                                                        */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_WRITE_USER_STRUCT)
#endif

typedef struct PPP_MBX_WRITE_USER_STRUCT {
     void   _FAR *pBuffer;         /* pointer to writebuffer                 */
     ushort       Length;          /* Length of writebuffer                  */
} PPP_MBX_WRITE_USER_TYPE;

/*---------------------------------------------------------------------------*/
/* PPPDRV_MBX_RESET_USER                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* PPP_MBX_FLUSH                                                             */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* PPP_MBX_SET_CHANNEL                                                       */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_SET_CHANNEL_STRUCT)
#endif

typedef struct PPP_MBX_SET_CHANNEL_STRUCT {
     ushort       Channel;         /* Channel (0 or 1)                       */
} PPP_MBX_SET_CHANNEL_TYPE;

/*---------------------------------------------------------------------------*/
/* PPP_MBX_CONFIG_EVENT                                                      */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_CONFIG_EVENT_STRUCT)
#endif

typedef struct PPP_MBX_CONFIG_EVENT_STRUCT {
     uint         FlagID;          /* FlagID                                 */
     uint         FlagMask;        /* FlagMask                               */
} PPP_MBX_CONFIG_EVENT_TYPE;

/*---------------------------------------------------------------------------*/
/* PPP_MBX_GET_BUFFER_STATUS                                                 */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_GET_BUFFER_STATUS_STRUCT)
#endif

typedef struct PPP_MBX_GET_BUFFER_STATUS_STRUCT {
     ushort          RecvCount;    /* Number of bytes in receivebuffer       */
} PPP_MBX_GET_BUFFER_STATUS_TYPE;

/*---------------------------------------------------------------------------*/
/* PPP_MBX_GET_MODEM_STATUS                                                  */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_GET_MODEM_STATUS_STRUCT)
#endif

typedef struct PPP_MBX_GET_MODEM_STATUS_STRUCT {
     ushort        Status;         /* Modem-Status                           */
} PPP_MBX_GET_MODEM_STATUS_TYPE;

#define PPP_MBX_MODSTAT_RI      0x1
#define PPP_MBX_MODSTAT_DCD     0x2
#define PPP_MBX_MODSTAT_CTS     0x4
#define PPP_MBX_MODSTAT_DSR     0x8

/*---------------------------------------------------------------------------*/
/* PPP_MBX_GET_DRV_CFG                                                       */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_GET_DRV_CFG_STRUCT)
#endif

typedef struct PPP_MBX_GET_DRV_CFG_STRUCT {
     uint        IOBaseAddr;     /* I/O-BaseAddress of UART.                 */
     uint        IRQ;            /* IRQ-Number                               */
     uint        Baudrate;       /* Baudrate in bits/s                       */
     uint        Parity;         /* Parity : 0 = No, 1=even, 2=odd           */
     uint        Databits;       /* Number of databits (7 or 8)              */
     uint        Stopbits;       /* Number of Stopbits (1 or 2)              */
     uint        FIFO;           /* FIFO to be used if present               */
     uint        UARTType;       /* UART-Type detected (0:none,1:8250,2:16550*/
} PPP_MBX_GET_DRV_CFG_TYPE;

/*---------------------------------------------------------------------------*/
/* Status:                                                                   */
/*---------------------------------------------------------------------------*/

#define PPP_MBX_STATE_OK              0 /* Unit O.K.                         */
#define PPP_MBX_STATE_NO_HW           1 /* Hardware for Unit not Found.      */

/*---------------------------------------------------------------------------*/
/* PPP_MBX_GET_STATS                                                         */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_GET_STATS_STRUCT)
#endif

typedef struct PPP_MBX_GET_STATS_STRUCT {
     ulong       RxCnt;            /* Number of successful RX-SVCs           */
     ulong       TxCnt;            /* Number of successful TX-SVCs           */
     ulong       IntCnt;           /* Number of Interrupts occured.          */
     ushort      RxFraming;        /* Number of Framing-errors on receive    */
     ushort      RxParity;         /* Number of Parity-errors  on receive    */
     ushort      RxOverflow;       /* Number of FIFO-Overflow  on receive    */
     ushort      RxBreak;          /* Number of Break-errors on receive      */
     ushort      RxBuffer;         /* Number of Driver-buffer overflow       */
     ushort      RxLSR;            /* Unexpected Line-Status interrupt       */
     ushort      RxTimeout;        /* Number of Receive-Timeouts occured.    */
     ushort      TxTimeout_CTS;    /* Transmission CTS not set               */
     ushort      TxTimeout;        /* Transmission interrupt missing?        */
     ushort      TxWaitForCTS;     /* Number of waits for CTS (no error)     */
     ushort      TxFatal;          /* Cannot send mail to Driver-task        */
     ushort      IntFatal;         /* Unexpected Interrupt.                  */
     ushort      IntCntOnce;       /* Number of pending ints > 1             */
} PPP_MBX_GET_STATS_TYPE;

/*---------------------------------------------------------------------------*/
/* PPP_MBX_UNIT_STR                                                          */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_GET_UNIT_STR_STRUCT)
#endif

typedef struct PPP_MBX_GET_UNIT_STR_STRUCT {
     void        *pUnit;           /* Pointer to Unit-Structure of Type      */
                                   /* PPPDRV_UNIT_TYPE (for internal use)    */
                                   /* (return-Parameter)                     */
} PPP_MBX_GET_UNIT_STR_TYPE;



/* ========================================================================= */
/*                                                                           */
/* errorcodes (from SVCs)                                                    */
/*                                                                           */
/* ========================================================================= */

#define PPP_STS_OK                    0  /* no error                         */
#define PPP_STS_ERR_PARAM            -1  /* parameter error                  */
/*                                   -2     reserved                         */
#define PPP_STS_ERR_TIMEOUT          -3  /* Timeout-error (on Transmit)      */
                                         /* CTS not present, or no response  */
                                         /* from UART (not interrupt)        */
/*                                   -4     reserved                         */
#define PPP_STS_ERR_FATAL            -5  /* Fatal error.                     */
#define PPP_STS_ERR_CANCEL           -6  /* Request was canceld              */
#define PPP_STS_ERR_CHANNEL          -7  /* Wrong channel for SVC selected.  */

/* ========================================================================= */
/*  Mailboxtypes to Driver-task                                              */
/* ========================================================================= */
/* pMail of Mailbox                                                          */
/*                                                                           */
/*               PPP_MBX_UNION                                               */
/*     pMail->  +------------+                                               */
/*              |  Mailtype  |                                               */
/*              +------------+                                               */
/*              | depends on |                                               */
/*              |  Mailtype  |                                               */
/*              +------------+                                               */
/*                                                                           */
/*  Mailtype:  PPP_MBX_TYPE_SVC     (Type for SVC's !)                       */
/*                                                                           */
/*               PPP_MBX_UNION                                               */
/*     pMail->  +------------+                                               */
/*              |  Mailtype  |      PPP_MBX_SVC_TYPE                         */
/*              +------------+      +-------------+                          */
/*              | pMailParam | ---->|             |                          */
/*              |            |      +-------------+                          */
/*              +------------+      |             |         Paramblock       */
/*              | reserved   |      +-------------+        +-----------+     */
/*              +------------+      |    pParam   | ------>|           |     */
/*                                  +-------------+        |           |     */
/*                                                         |           |     */
/*                                                         +-----------+     */
/*                                                                           */
/*  Mailtype:   PPP_MBX_TYPE_INT    (driver internal use only!)              */
/*                                                                           */
/*               PPP_MBX_UNION                                               */
/*     pMail->  +------------+                                               */
/*              |  Mailtype  |                                               */
/*              +------------+                                               */
/*              | depends on |                                               */
/*              |  Mailtype  |                                               */
/*              +------------+                                               */
/*                                                                           */
/*                                                                           */
/*  Mailtype:  PPP_MBX_TYPE_TOUT    (driver internal use only!)              */
/*                                                                           */
/*               PPP_MBX_UNION                                               */
/*     pMail->  +------------+                                               */
/*              |  Mailtype  |                                               */
/*              +------------+                                               */
/*              | depends on |                                               */
/*              |  Mailtype  |                                               */
/*              +------------+                                               */
/*                                                                           */
/* ========================================================================= */


/* ========================================================================= */
/*                                                                           */
/* Maiboxtypes (pMail points to)                                             */
/*                                                                           */
/* ========================================================================= */

#define PPP_MBX_TYPE_SVC       0     /* SVC-Handling                         */
#define PPP_MBX_TYPE_INT       1     /* from Interrupthandler                */
#define PPP_MBX_TYPE_TOUT      2     /* Timeoutmail                          */

/* 3 uint of Mail (this are 6 ushort for RMOS3, we depend on this !)         */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (PPP_MBX_UNION_STRUCT)
#endif

typedef struct PPP_MBX_UNION_STRUCT {
    ushort     MBXType;              /* type of mail, see above */
    union {
      PPP_MBX_SVC_TYPE _FAR *pMailParam;    /* 6 Bytes far ptr */
      PPP_MBX_INT_TYPE       interrupt;                
      PPP_MBX_TOUT_TYPE      tout;           
    } mail;
} PPP_MBX_UNION;


#endif  /* _PPPDRV_H_ */
