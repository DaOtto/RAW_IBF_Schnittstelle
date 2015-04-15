/* Based on eth970.h  - see Readme.txt for credits! */
/*****************************************************************************/
/* Project:    ETH55X                                                         */
/*****************************************************************************/
/*                                                                           */
/*   Filename:  ETH970.H                                                     */
/*                                                                           */
/*   Author:    J. Stephan           Department:      A&D SE E41             */
/*   Date:      15.12.1997                                                   */
/*                                                                           */
/*   Development Kit / Compiler :  C-Compiler Organon V6.x                   */
/*                                                                           */
/*   Copyright (C) Siemens AG 1997. All rights reserved.                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Filename:  ETH55X.H                                                     */
/*                                                                           */
/*   Author:    Michael Busch        Department:      I&S IT PS KHE3         */
/*   Date:      03.07.2001                                                   */
/*                                                                           */
/*   Development Kit / Compiler :  Borland 5.01                              */
/*                                                                           */
/*   Copyright (C) Siemens AG 2001. All rights reserved.                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Description: Header file for Ethernetdriver for INTEL 82559ER           */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Modifications:                                                          */
/*                                                                           */
/*----------+-------------+-----+--------------------------------------------*/
/*  Date    |    Author   | Sign|                Description                 */
/*----------+-------------+-----+--------------------------------------------*/
/* 16.12.97 | J. Stephan  |     | original issue                             */
/*----------+-------------+-----+--------------------------------------------*/
/* 14.12.99 | S.R.        |     | add SVC ETH970_MBX_SET_FILTER              */
/*----------+-------------+-----+--------------------------------------------*/
/* 28.06.00 | J.S.        |     | add SVC ETH970_MBX_MULTICAST               */
/*----------+-------------+-----+--------------------------------------------*/
/* 03.07.01 | mmb         |     | ETH55X original issue                      */
/*----------+-------------+-----+--------------------------------------------*/
/* 17.12.01 | D. Cotard   |  DC | name of Mailbox changed to "ETH55X_MBX"    */
/*          |             |     |                                            */
/*          |             |     |                                            */
/*          |             |     |                                            */
/*----------+-------------+-----+--------------------------------------------*/
/*                                                                           */
/*****************************************************************************/

#ifndef _ETH55X_H_
#define _ETH55X_H_


/* Byte allignment */
#ifdef __BORLANDC__
#pragma option -a1
#endif


#ifndef NULL   
#define NULL ((void *) 0);       
#endif

/* ========================================================================= */
/*                                                                           */
/* General                                                                   */
/*                                                                           */
/* ========================================================================= */

#define ETH55X_MBX      "ETH55X_MBX"

#define ETH55X_IEEE_ADDR_LEN      6 /* length of Ethernet address in bytes   */
#define ETH55X_MAX_DATA_LEN    1514 /* length of Frame (netto)               */

/* ========================================================================= */
/*                                                                           */
/* Task-start-parameter (pointed to by EAX/EBX)                              */
/*                                                                           */
/* ========================================================================= */
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_PARAM_STRUCT)
#endif

typedef struct ETH55X_PARAM_STRUCT
{
  uint       MailboxID;        /* Mailbox quit-ID                        */
  uint       ConsoleFlag;      /* Console-Flag                           */
                               /* argc and argv not used yet.            */
  int        argc;             /* number of Strings in argv-array        */
  char     **argv;             /* Pointer to array of Pointer to Strings */
#ifdef __BORLANDC__
  short DummySegment;          /* make the pointer 6 byte long */
#endif
} ETH55X_PARAM_TYPE;

/*---------------------------------------------------------------------------*/
/* ConsoleFlag                                                               */
/*---------------------------------------------------------------------------*/

#define ETH55X_CONSOLE_OUT       1   /* Startupmessages on Stdio             */
#define ETH55X_CONSOLE_NO_OUT    0   /* No Startup-messages                  */

/* ========================================================================= */
/*                                                                           */
/* Quit-Mailbox (pMail points to)                                            */
/*                                                                           */
/* (Mailbox send from Drivertask after Startupinitialitiation to the Mailbox */
/*  MailboxID from Task Startup-Parameters)                                  */
/*                                                                           */
/* ========================================================================= */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_TASK_QUIT_MBX_STRUCT)
#endif

typedef struct ETH55X_TASK_QUIT_MBX_STRUCT
{
  int        stat;       /* state of initialization */
  uint       res1;
  uint       res2;
} ETH55X_TASK_QUIT_MBX_TYPE;

/*--------------------------------------------------------------------------*/
/* stat                                                                     */
/*--------------------------------------------------------------------------*/

#define ETH55X_INIT_OK                0  /* Driver Startup successful        */
#define ETH55X_INIT_ERR_EXIST        -1  /* Driver-Mailbox already exists    */
                                        /* (driver may be already loaded)   */
#define ETH55X_INIT_ERR_CREATE_MBX   -2  /* Error on Creating Driver MBX     */
                                        /* (other than already cataloged)   */
#define ETH55X_INIT_ERR_PARAM        -3  /* Driver-Parameter error           */
#define ETH55X_INIT_ERR_SET_HANDLER  -4  /* RMOS-Error on RmSetIntIS-Handler */
#define ETH55X_INIT_ERR_ALOC         -5  /* RMOS-Error on RmAlloc            */
#define ETH55X_INIT_ERR_GET_LINADDR  -6  /* RMOS-Error on RmGetLinAddress    */
#define ETH55X_INIT_ERR_CATALOG      -7  /* Could not find a free Catalog    */
                                        /* entry in the range ETHER_00..99  */
                                        /* or Catalog-Error                 */
#define ETH55X_INIT_ERR_NO_HW        -8  /* no HW found in System.           */

                                        /* The following Error occures if   */
                                        /* an error occured while sending   */
                                        /* the   quit - mail.   This error  */
                                        /* is fatal! It is not put into the */
                                        /* the quit-mail! The task continues*/

#define ETH55X_INIT_ERR_SEND_MAIL    -9  /* RMOS-Error on SendMail.          */

/* ========================================================================= */
/*                                                                           */
/* Timeout Mailbox                                                           */
/*                                                                           */
/*  (Send from Driver to his own Mailbox for Timeouthandling)                */
/*  (must not exceed 5 ushorts for RMOS3!)                                   */
/*                                                                           */
/* ========================================================================= */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_TOUT_STRUCT)
#endif

typedef struct ETH55X_MBX_TOUT_STRUCT
{
     ushort      UnitID;
     ushort      SyncCounter;      /* Counter to Sync Mail.                  */
                                   /* (there is a global counter which is    */
                                   /*  incremented after each INIT or RESET  */
                                   /*  so we see if this mail is valid or    */
                                   /*  an old one which can be ignored. )    */
     ushort      TimeoutType;      /* Timeout reason                         */
     ushort      reserved1;
     ushort      reserved2;
     ushort      reserved3;
} ETH55X_MBX_TOUT_TYPE;

#define ETH55X_TIMEOUT_INIT       0 /* timeout while waiting for INIT-DONE   */
#define ETH55X_TIMEOUT_SEND       1 /* timeout on transmit                   */


/* ========================================================================= */
/*                                                                           */
/* Interrupt Mailbox                                                         */
/*                                                                           */
/*  (Send from Interrupthandler to Drivertask)                               */
/*  (must not exceed 5 ushorts for RMOS3!)                                   */
/*                                                                           */
/* ========================================================================= */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_INT_STRUCT)
#endif

typedef struct ETH55X_MBX_INT_STRUCT
{
  ushort      UnitID;
  ushort      SyncCounter;         /* Counter to Sync Mail.                  */
                                   /* (there is a global counter which is    */
                                   /*  incremented after each INIT or RESET  */
                                   /*  so we see if this mail is valid or    */
                                   /*  an old one which can be ignored. )    */
  ushort      State;               /* Interrupt-State                        */
  ushort      reserved1;
  ushort      reserved2;
  ushort      reserved3;
} ETH55X_MBX_INT_TYPE;

/* ========================================================================= */
/*                                                                           */
/* SVC-Mailbox-Types (pMailParam points to)                                  */
/*                                                                           */
/* ========================================================================= */

#define ETH55X_MBX_INIT           0  /* Init of driver send/receive queues   */
#define ETH55X_MBX_READ           1  /* receive data frame                   */
#define ETH55X_MBX_WRITE          2  /* transmit data frame                  */
#define ETH55X_MBX_CANCEL         3  /* cancel current receive request       */
#define ETH55X_MBX_RESET          4  /* reset driver and controller          */
#define ETH55X_MBX_GET_PARAM      5  /* get driver/controller hw-params      */
#define ETH55X_MBX_GET_DRV_CFG    6  /* Driver-Configurations                */
#define ETH55X_MBX_GET_STATS      7  /* driver stats                         */
#define ETH55X_MBX_GET_UNIT_STR   8  /* get Unit-structure                   */
#define ETH55X_MBX_SET_FILTER     9  /* set filter on/off       SR 14.12.99  */
#define ETH55X_MBX_MULTICAST     10  /* Multicast MACs enable/disable        */  
#define ETH55X_MBX_SET_PHY_REG   11  /* Write Register to PHY interface      */
#define ETH55X_MBX_GET_PHY_REG   12  /* Read Register from PHY interface     */
#define ETH55X_MBX_DUMP_RESET_STATS  13  /* Dump and reset chip statistics   */
#define ETH55X_MBX_DUMP_STATS        14  /* Dump chip statistics             */
/* ========================================================================= */
/*                                                                           */
/* SVC Mailbox defs..                                                        */
/*                                                                           */
/* ========================================================================= */

/*---------------------------------------------------------------------------*/
/* General Mail-Params pointed by pMailParam.                                */
/*                                                                           */
/* ETH55X_MBX_TYPE  *pMailParam;                                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/


#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_SVC_STRUCT)
#endif

typedef struct ETH55X_MBX_SVC_STRUCT
{
  ushort      Type;      /* type of mail, see above */
  ushort      UnitID;
  uint        FlagID;
  uint        FlagMask;
  int   _FAR *pState;
#ifdef __BORLANDC__
  short DummySegment1;  /* make the pointer 6 byte long */
#endif
  void  _FAR *pParam;   /* pointer to typespecific parameter              */
#ifdef __BORLANDC__
  short DummySegment2;  /* make the pointer 6 byte long */
#endif
  void  _FAR *pQueue;   /* for driver internal queuing of requests        */                    
#ifdef __BORLANDC__
  short DummySegment3;  /* make the pointer 6 byte long */
#endif
} ETH55X_MBX_SVC_TYPE;

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_INIT                                                           */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_INIT_STRUCT)
#endif

typedef struct ETH55X_MBX_INIT_STRUCT
{
  uchar IEEEaddr[ETH55X_IEEE_ADDR_LEN];        /* IEEE-addr (6 uchar)     */
} ETH55X_MBX_INIT_TYPE;

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_READ                                                           */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_READ_STRUCT)
#endif

typedef struct ETH55X_MBX_READ_STRUCT
{
  void   _FAR   *pBuffer;       /* pointer to receivebuffer               */
#ifdef __BORLANDC__
  short DummySegment1;          /* make the pointer 6 byte long */
#endif
  ushort         Length;        /* Length of receivebuffer (min.1514 Byte)*/
  ushort _FAR   *pIOCount;      /* Number of bytes received               */
#ifdef __BORLANDC__
  short DummySegment2;          /* make the pointer 6 byte long */
#endif
     
} ETH55X_MBX_READ_TYPE;

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_WRITE                                                          */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_WRITE_STRUCT)
#endif

typedef struct ETH55X_MBX_WRITE_STRUCT
{
  void   _FAR *pBuffer;         /* pointer to writebuffer                 */
#ifdef __BORLANDC__
  short DummySegment;           /* make the pointer 6 byte long */
#endif
  ushort       Length;          /* Length of writebuffer   (max.1514 Byte)*/
} ETH55X_MBX_WRITE_TYPE;

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_CANCEL                                                         */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_RESET                                                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_GET_PARAM                                                      */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_GET_PARAM_STRUCT)
#endif

typedef struct ETH55X_MBX_GET_PARAM_STRUCT
{
     ushort      UnitCnt;          /* Number of total Units of driver        */
     ushort      State;            /* State of Unit .                        */
     uchar       OrgIEEEaddr[ETH55X_IEEE_ADDR_LEN];   /* IEEE-addr len     1)*/
     uchar       CurIEEEaddr[ETH55X_IEEE_ADDR_LEN];   /* IEEE-addr len     1)*/
  /* 1) only valid if State=ETH55X_STATE_OK */
} ETH55X_MBX_GET_PARAM_TYPE;

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_GET_DRV_CFG                                                    */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_DRV_CFG_STRUCT)
#endif

typedef struct ETH55X_MBX_GET_DRV_CFG_STRUCT
{
  ushort      ioAddr;           /* I/O-Base address of Controller         */
  ushort      IRQ;              /* IRQ                                    */
  ulong       DPRaddr;          /* Address of DPR                         */
  void  _FAR *pDPR;             /* Pointer to DPR used in driver          */
#ifdef __BORLANDC__
  short DummySegment;           /* make the pointer 6 byte long */
#endif
  ushort      DPRsize;          /* Size of DPR in KBytes (always 16)      */

} ETH55X_MBX_GET_DRV_CFG_TYPE; 

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_SET_FILTER			SR 14.12.99                              */
/*---------------------------------------------------------------------------*/
#define UDP_FILTER				1 

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_SET_FILTER_STRUCT)
#endif

typedef struct ETH55X_MBX_SET_FILTER_STRUCT
{
     ushort        FilterType;    /* Filter Type e.g. UDP_FILTER            */
     ushort	   Filter_On_Off; /* On = 1; Off = 0                        */
} ETH55X_MBX_SET_FILTER_TYPE;

/*---------------------------------------------------------------------------*/
/* Sate:                                                                     */
/*---------------------------------------------------------------------------*/

#define ETH55X_STATE_OK           0 /* Unit O.K.                             */
#define ETH55X_STATE_NO_HW        1 /* Hardware for Unit not Found.          */

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_GET_STATS                                                      */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_GET_STATS_STRUCT)
#endif

typedef struct ETH55X_MBX_GET_STATS_STRUCT
{
     ushort      Fatal;            /* Fatal errors occured                   */
                                   /* BABL, MERR                             */
     ulong       RxCnt;            /* Number of received Frames              */
     ulong       TxCnt;            /* Number of transmitted Frames           */
     ushort      RxFatal;          /* Number of fatal-Receive errors       1)*/
     ushort      RxMISS;           /* Number of missed receive Frames        */
     ushort      RxFRAM;           /* Number of Framing Errors               */
     ushort      RxOFLO;           /* Number of Overflow Errors              */
     ushort      RxCRC;            /* Number of CRC-Errors                   */
     ushort      RxBUFF;           /* Number of Buffer-Errors                */
     ushort      TxFatal;          /* Number of fatal-transmit errors      1)*/
     ushort      TxLCOL;           /* Number of Late Collisions              */
     ushort      TxLCAR;           /* Number of Loss of Carrier              */
     ushort      TxRTRY;           /* Number of Retrys                       */
     ushort      TxCERR;           /* Number of CERR  (Testfeature on Contr.)*/
     ushort      TxBUFF;           /* Number of BUFF errors                1)*/
     ushort      TxUFLO;           /* Number of UFLO errors                1)*/
     ushort      TxTOUT;           /* Number of Timeouts on transmit       2)*/
     ushort      Reinit;           /* Number of Reinits done (as a result    */
                                   /* from an fatal error)                   */
                                   /* 1) will result in an reinit attempt.   */
                                   /*    if this fails  Fatal will be set.   */
                                   /* 2) will result in an reinit attempt.   */


} ETH55X_MBX_GET_STATS_TYPE;


/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_SET_PHY_REG                                                     */
/* ETH55X_MBX_GET_PHY_REG                                                     */
/*---------------------------------------------------------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_PHY_REG_STRUCT)
#endif

typedef struct ETH55X_MBX_PHY_REG_STRUCT
{
  ushort      Reg;            /* IN: Register number to read or write */
  ushort      Value;          /* OUT: Active register value on read   */
                              /* IN:  Value to set on write  */
} ETH55X_MBX_PHY_REG_TYPE;

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_DUMP_STATS                                                      */
/* ETH55X_MBX_DUMP_RESET_STATS                                                */
/*---------------------------------------------------------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_DUMP_STATS_STRUCT)
#endif

typedef struct ETH55X_MBX_DUMP_STATS_STRUCT
{
	unsigned tx_good_frames;  
	unsigned tx_coll16_errs;  
	unsigned tx_late_colls;  
	unsigned tx_underruns;  
	unsigned tx_lost_carrier;  
	unsigned tx_deferred;  
	unsigned tx_one_colls;  
	unsigned tx_multi_colls;  
	unsigned tx_total_colls;  
	unsigned rx_good_frames;  
	unsigned rx_crc_errs;  
	unsigned rx_align_errs;  
	unsigned rx_resource_errs;  
	unsigned rx_overrun_errs;  
	unsigned rx_colls_errs;  
	unsigned rx_runt_errs;      
} ETH55X_MBX_DUMP_STATS_TYPE;



/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_UNIT_STR                                                       */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_GET_UNIT_STR_STRUCT)
#endif

typedef struct ETH55X_MBX_GET_UNIT_STR_STRUCT
{
  void        *pUnit;           /* Pointer to Unit-Structure of Type      */
                                /* ETH55X_UNIT_TYPE (for internal use)    */
                                /* (return-Parameter) */
#ifdef __BORLANDC__
  short DummySegment;// make the pointer 6 byte long
#endif
			      
} ETH55X_MBX_GET_UNIT_STR_TYPE;

/*---------------------------------------------------------------------------*/
/* ETH55X_MBX_MULTICAST                                                      */
/*---------------------------------------------------------------------------*/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_MULTICAST_STRUCT)
#endif

typedef struct ETH55X_MBX_MULTICAST_STRUCT {
     ushort Mode;                                  /* Mode                    */
     uchar  IEEEaddr[ETH55X_IEEE_ADDR_LEN];        /* IEEE-addr (6 uchar)     */
} ETH55X_MBX_MULTICAST_TYPE;

/* Modes: */

#define MULTICAST_ENABLE        0   /* enable  IEEEaddr for Multicast  */
#define MULTICAST_DISABLE       1   /* disable IEEEaddr for Multicast  */
#define MULTICAST_DISABLE_ALL   2   /* disable all Multicast addresses */

/* ========================================================================= */
/*                                                                           */
/* errorcodes (from SVCs)                                                    */
/*                                                                           */
/* ========================================================================= */

#define ETH55X_STS_OK            0  /* no error                              */
#define ETH55X_STS_ERR_PARAM    -1  /* parameter error                       */
#define ETH55X_STS_ERR_INIT     -2  /* Initialization error. (maybe HW-error)*/
#define ETH55X_STS_ERR_TIMEOUT  -3  /* Timeout-error (on INIT or Transmit)   */
#define ETH55X_STS_ERR_NOT_INIT -4  /* Controller not INIT. INIT first       */
#define ETH55X_STS_ERR_FATAL    -5  /* Fatal error. Reset-SVC and INIT-SVC   */
                                   /* needed to proceed!                    */
#define ETH55X_STS_ERR_CANCEL   -6  /* Request was canceld                   */
#define ETH55X_STS_ERR_FRAM    -10  /* Framing Error   (receive)             */
#define ETH55X_STS_ERR_OFLO    -11  /* Overflow Error  (receive)             */
#define ETH55X_STS_ERR_CRC     -12  /* Checksum  Error (receive)             */
#define ETH55X_STS_ERR_BUFF    -13  /* Buffer    Error (receive,transmit)    */
#define ETH55X_STS_ERR_LCOL    -14  /* Late Collision  (transmit)            */
#define ETH55X_STS_ERR_LCAR    -15  /* Loss of Carrier (transmit)            */
#define ETH55X_STS_ERR_RTRY    -16  /* Retry Error     (transmit)            */
#define ETH55X_STS_ERR_REINIT  -17  /* reinit of controller done to recover  */
                                   /* from fatal error (receive,transmit)   */
#define ETH55X_PHY_NOT_AVAIL   -20  /* PHY not available -> GET/SET_PHY_REG  */

/* ========================================================================= */
/*  Mailboxtypes to Driver-task                                              */
/* ========================================================================= */
/* pMail of Mailbox                                                          */
/*                                                                           */
/*             ETH55X_MBX_UNION                                              */
/*     pMail->  +------------+                                               */
/*              |  Mailtype  |                                               */
/*              +------------+                                               */
/*              | depends on |                                               */
/*              |  Mailtype  |                                               */
/*              +------------+                                               */
/*                                                                           */
/*  Mailtype:  ETH55X_MBX_TYPE_SVC  (Type for SVC's !)                       */
/*                                                                           */
/*             ETH55X_MBX_UNION                                              */
/*     pMail->  +------------+                                               */
/*              |  Mailtype  |      ETH_MBX_SVC_TYPE                         */
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
/*  Mailtype:  ETH55X_MBX_TYPE_INT  (driver internal use only!)              */
/*                                                                           */
/*             ETH55X_MBX_UNION                                              */
/*     pMail->  +------------+                                               */
/*              |  Mailtype  |                                               */
/*              +------------+                                               */
/*              | depends on |                                               */
/*              |  Mailtype  |                                               */
/*              +------------+                                               */
/*                                                                           */
/*                                                                           */
/*  Mailtype:  ETH55X_MBX_TYPE_TOUT (driver internal use only!)              */
/*                                                                           */
/*             ETH55X_MBX_UNION                                              */
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

#define ETH55X_MBX_TYPE_SVC           0  /* SVC-Handling                         */
#define ETH55X_MBX_TYPE_INT           1  /* from Interrupthandler                */
#define ETH55X_MBX_TYPE_TOUT          2  /* Timeoutmail                          */
#define ETH55X_MBX_TYPE_CHECK_RX_HANG 3  /* check for receiver hang bug          */ 
#define ETH55X_MBX_TYPE_PRINT_STATS   4  /* Print unit statistics to console     */

/* 3 uint of Mail (this are 6 ushort for RMOS3, we depend on this !)         */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (ETH55X_MBX_UNION_STRUCT)
#endif

typedef struct SegOffStruct
{  
  unsigned       Off;
  unsigned short Seg;
}SegOffType;

typedef struct ETH55X_MBX_UNION_STRUCT
{
  ushort     MBXType;                         /* type of mail, see above */
  union {
#ifdef __BORLANDC__
    SegOffType  Convert;                    /* Make the union six bytes long */
#endif
    ETH55X_MBX_SVC_TYPE _FAR *pMailParam;    /* 6 Bytes far ptr */
    ETH55X_MBX_INT_TYPE       interrupt;                
    ETH55X_MBX_TOUT_TYPE      tout;           
  } mail;
} ETH55X_MBX_UNION;



#endif  /* _ETH55X_H_ */
