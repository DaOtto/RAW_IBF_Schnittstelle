/*--FILE HEADER---------------------------------------------------------------
;
;   filename    : RCINC.H
;   version     : 0006
;   contents    : Include for configuration
;   author      : K.P.H.
;   date        : Dec 10, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT---------------------------------------------
;
;   function    : prototypes of configuration function and defines
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER--------------------------------------------------------
;
;---MODIFICATION HEADER-------------------------------------------------------
;
;   Jan 24, 1995  K.P.H. 0001  Original issue
;   Mar 15, 1995  K.P.H. 0002  Additional changes for RMOS2
;   May 10, 1995  K.P.H. 0003  Additional changes for BORLAND RMOS2 support
;   Oct 12, 1995  K.P.H. 0004  Modification for RMOS V3.12
;   Feb 14, 1996  K.P.H. 0005  Additional modification for RMOS V3.12
;   Dec 10, 1996  P.F.   0006  Changed comments
;
;---END OF MODIFICATION HEADER----------------------------------------------*/


#ifndef _RCINC_H_
#define _RCINC_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif

#ifndef _RMTYPES_H_
#include <rmtypes.h>
#endif

#ifndef _RMDEF_H_
#include <rmdef.h>
#endif

/* CMOS ADDRESSES and FUNCTIONS ---------------------------------------------*/
#define CMOS_REG (unsigned short) 0x070u     /* CMOS select register         */
#define CMOS_VAL (unsigned short) 0x071u     /* value of selected register   */

#define CMOS_DSB (unsigned short) 0x00Eu     /* CMOS Diagnostic Status Byte  */
                                             
#define MEMBAS_L (unsigned short) 0x015u     /* CMOS ramsize                 */
#define MEMBAS_H (unsigned short) 0x016u
#define MEMEXP_L (unsigned short) 0x017u
#define MEMEXP_H (unsigned short) 0x018u

#define CMTIME_SEC   (unsigned short) 0x00u  /* time and date                */
#define CMTIME_MIN   (unsigned short) 0x02u
#define CMTIME_HOUR  (unsigned short) 0x04u
#define CMTIME_WKDAY (unsigned short) 0x06u
#define CMTIME_DAY   (unsigned short) 0x07u
#define CMTIME_MONTH (unsigned short) 0x08u
#define CMTIME_YEAR  (unsigned short) 0x09u

#define CMOS_DDTB    (unsigned short) 0x10u /* diskette drive type byte     */
#define CMOS_HDTP    (unsigned short) 0x12u /* harddisk type byte           */
#define CMOS_EQUB    (unsigned short) 0x14u /* equipment byte               */

/* macros for reading CMOS values -------------------------------------------*/
#define read_cmos(r) (outbyte(CMOS_REG,(unsigned char) r), inbyte(CMOS_VAL))
#define write_cmos(r,v) outbyte(CMOS_REG,(unsigned char) r); outbyte(CMOS_VAL,(unsigned char) v)

/* PC-BASE ADDRESSES  -------------------------------------------------------*/
/* PC-I/O -------------------------------------------------------------------*/
#define PCCOM1BASE   0x3f8u
#define PCCOM2BASE   0x2f8u
/* PC-PROGRAMMABLE INTERRUPT CONTROLLER -------------------------------------*/
#define PCMPIC_BASE  0x20u
#define PCMPIC_MASK  0x21u   
#define PCSPIC_BASE  0xA0u
#define PCSPIC_MASK  0xA1u

/* PC-CMOS FLOPPY AND HARDDISK TYPES ----------------------------------------*/
#define PCFD0_144 0x40u
#define PCFD0_12  0x20u
#define PCMEMCARD0 0x50u
#define PCFD1_144 0x04u
#define PCFD1_12  0x02u
#define PCMEMCARD1 0x05u
#define PCHD0     0xF0u
#define PCHD1     0x0Fu

/* defines for system console configuration ---------------------------------*/
#define EGA         1
#define COM1        2
#define COM2        3

/* nuc startup mesagesheader */
#define NUCMSG "NUC: "

/* ascii configuration defines */
#define RM_ASCII_CONTINUE          0
#define RM_ASCII_BREAK_ON_ERROR    1
#define RM_ASCII_CONTINUE_WITH_MSG 2

/* maximum number of debugger's is 16 */
#define MAXDEBUGGER 16

/*---------------------------------------------------------------------------*/
/* driver functions                                                          */
/*---------------------------------------------------------------------------*/

/* byt com driver line control settings */
#define DATA_7      0x02u        /* seven data bit */
#define DATA_8      0x03u        /* eight data bit */
#define STOP_1      0x00u        /* one stopbit    */
#define STOP_2      0x04u        /* two stopbits   */
#define NOPARITY    0x00u        /* no parity      */
#define EVENPARITY  0x18u        /* even parity    */
#define ODDPARITY   0x08u        /* odd parity     */

/* keydefines for unsolicited task */
#define CTRL_A  0x01u
#define CTRL_B  0x02u
#define CTRL_C  0x03u
#define CTRL_D  0x04u            /* standard for debugger */
#define CTRL_E  0x05u
#define CTRL_F  0x06u
#define CTRL_G  0x07u
#define CTRL_H  0x08u
#define CTRL_I  0x09u
#define CTRL_J  0x0Au
#define CTRL_K  0x0Bu
#define CTRL_L  0x0Cu
#define CTRL_M  0x0Du
#define CTRL_N  0x0Eu
#define CTRL_O  0x0Fu
#define CTRL_P  0x10u
#define CTRL_Q  0x11u
#define CTRL_R  0x12u            /* standard for cli dispatcher */
#define CTRL_S  0x13u
#define CTRL_T  0x14u
#define CTRL_U  0x15u
#define CTRL_V  0x16u
#define CTRL_W  0x17u
#define CTRL_X  0x18u
#define CTRL_Y  0x19u
#define CTRL_Z  0x1Au

/* defines for ega colors */
#define FG_BLACK          0x00u
#define FG_BLUE           0x01u
#define FG_GREEN          0x02u
#define FG_CYAN           0x03u
#define FG_RED            0x04u
#define FG_MAGENTA        0x05u
#define FG_BROWN          0x06u
#define FG_GRAY           0x07u
#define FG_DARKGRAY       0x08u
#define FG_LIGHTBLUE      0x09u
#define FG_LIGHTGREEN     0x0Au
#define FG_LIGHTCYAN      0x0Bu
#define FG_LIGHTRED       0x0Cu
#define FG_LIGHTMAGENTA   0x0Du
#define FG_LIGHTYELLOW    0x0Eu
#define FG_WHITE          0x0Fu
                              
#define BG_BLACK          0x00u
#define BG_BLUE           0x10u
#define BG_GREEN          0x20u
#define BG_CYAN           0x30u
#define BG_RED            0x40u
#define BG_MAGENTA        0x50u
#define BG_YELLOW         0x60u
#define BG_WHITE          0x70u

/* defines for RcInitDebugger */
#define RM_DEB_SET_INHIBIT          1u
#define RM_DEB_RESERVE_UNIT         2u
#define RM_DEB_SET_INHIBIT_EXC      4u

/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*---------------------------*/
/* memory and CMOS functions */
/*---------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcScanRamSize","RcGetCMOSSize","RcGetCMOSDateTime")
#pragma fixedparams("RcSetCMOSDateTime","RcGetFloppyType","RcGetHardDiskType")
#pragma fixedparams("RcGetRm4WinRamSize")
#if !RM3
#pragma fixedparams("RcGetCMOSExtendedSize")
#endif
#endif

int _FIXED _FAR RcScanRamSize(          ulong           StartAddress,
                                        ulong           *Size );

int _FIXED _FAR RcGetCMOSSize(          ulong           *Size );

int _FIXED _FAR RcGetRm4WinRamSize(     ulong           *Size );

#if !RM3
int _FIXED _FAR RcGetCMOSExtendedSize(  ulong           *Size );
#endif

int _FIXED _FAR RcGetCMOSDateTime(      RmTimeStruct    *pTime );

int _FIXED _FAR RcSetCMOSDateTime(      RmTimeStruct    *pTime );

int _FIXED _NEAR RcGetFloppyType(       uint            *pFloppyType );

int _FIXED _NEAR RcSetFloppyType(       uint            FloppyType );

int _FIXED _NEAR RcGetHardDiskType(     uint            *pHardDiskType );

/*-----------------------------------------------*/
/* for systems without CMOS some dummy functions */
/*-----------------------------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcDummyGetClock","RcDummySetClock","RcDummySetPICMask")
#endif
int _FIXED _FAR RcDummyGetClock(        RmTimeStruct    *pTime );

int _FIXED _FAR RcDummySetClock(        RmTimeStruct    *pTime );

int _FIXED _FAR RcDummySetPICMask(      uint            IRQ );

/*---------------------------*/
/* timer functions for PC    */
/*---------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcInit8254","RcInitTimerPC")
#endif

int _FIXED _NEAR RcInit8254(            ulong           Clock,
                                        ulong           Rate,
                                        uint            DataPort, 
                                        uint            CommandPort);

void _FIXED _FAR RcInitTimerPC(         void );

/*--------------------------------------*/
/* interrupt controler functions for PC */
/*--------------------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcInit8259A","RcInitPICPC")
#pragma fixedparams("RcEOIProcPC","RcSetPICMaskPC")
#endif

int _FIXED _NEAR RcInit8259A(           uint            BasePort,
                                        uint            MaskPort,
                                        uint            StsICW3, 
                                        uint            BaseVectorNum,
                                        uint            IRQMask );

int _FIXED _NEAR RcInitPICPC(           uint            BaseVectorNumMaster,
                                        uint            IRQMaskMaster,
                                        uint            SlaveVectorNumMaster,
                                        uint            IRQMaskSlave );

void _FIXED RM_MODEL RcEOIProcPC(       void );
int _FIXED _FAR RcSetPICMaskPC(         uint            IRQ );

/*-------------------------------*/
/* timer functions for AMD-M36   */
/*-------------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcInitTimerM36")
#endif

void _FIXED _FAR RcInitTimerM36(        void );

/*--------------------------------------------*/
/* interrupt controller functions for AMS-M36 */
/*--------------------------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcInitPICM36")
#pragma fixedparams("RcEOIProcM36","RcSetPICMaskM36")
#endif

int _FIXED _NEAR RcInitPICM36 (         uint            BaseVectorNumA,
                                        uint            IRQMaskA,
                                        uint            BaseVectorNumB,
                                        uint            IRQMaskB,
                                        uint            BaseVectorNumC,
                                        uint            IRQMaskC );

void _FIXED RM_MODEL RcEOIProcM36 (     void );

int _FIXED _FAR RcSetPICMaskM36 (       uint            IRQ );

/*---------------------------*/
/* systemconsole functions   */
/*---------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcInitPasspointEga","RcPutcharEga","RcInitPasspoint8250")
#pragma fixedparams("RcInitPasspoint8251","RcPutchar8251")
#pragma fixedparams("RcInitPasspoint8530","RcPutchar8530")
#pragma fixedparams("RcPutchar8250COM1","RcPutchar8250COM2")
#endif

int _FIXED _NEAR RcInitPasspointEga(    void );

int _FIXED _FAR RcPutcharEga(           char            c ); 

int _FIXED _NEAR RcInitPasspoint8250(   uint            BaseAddress,
                                        ulong           Baudrate );

int _FIXED _FAR RcPutchar8250COM1(      char            c );

int _FIXED _FAR RcPutchar8250COM2(      char            c );

int _FIXED _NEAR RcInitPasspoint8251(   ulong           Baudrate );

int _FIXED _FAR RcPutchar8251(          char            c );

int _FIXED _NEAR RcInitPasspoint8530(   ulong           Baudrate );

int _FIXED _FAR RcPutchar8530(          char            c );

/*---------------------------*/
/* task init functions       */
/*---------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcInitErrorLogger","RcInitDebugger","x_start_debugger_task")
#pragma fixedparams("RcInitDEBDispatcher","RcInitCLIDispatcher","RcInitReporter")
#pragma fixedparams("RcInitReporterX","RcInitRemoteTask","RcInitDos")
#pragma fixedparams("RcInitExceptionHandler","RcInitUserTask")
#endif

int _FIXED _NEAR RcInitErrorLogger(     uint            TaskPriority);

int _FIXED _NEAR RcInitExceptionHandler(uint            TaskPriority);

int _FIXED _NEAR RcInitDebugger(        uint            DebuggerNum,
                                        uint            TaskPriority,
                                        uint            Mode );

void _FIXED _NEAR x_start_debugger_task(uint            Device,
                                        uint            Unit );

int _FIXED _NEAR RcInitDEBDispatcher(   uint            TaskPriority);

int _FIXED _NEAR RcInitCLIDispatcher(   uint            TaskPriority);

int _FIXED _NEAR RcInitReporter(        char            *pConsole, 
                                        ulong           TableSize, 
                                        uint            TaskPriority);

int _FIXED _NEAR RcInitReporterX(       char            *pConsole, 
                                        ulong           TableSize, 
                                        uint            TaskPriority);

int _FIXED _NEAR RcInitRemoteTask(      uint            TaskPriority);

int _FIXED _NEAR RcInitDos(             uint            TaskPriority);

int _FIXED _NEAR RcStartDos(            void );

int _FIXED _NEAR RcInitUserTask(        uint            EAX,
                                        uint            EBX, 
                                        uint            DataSize,
                                        uint            StackSize,
                                        rmfarproc       UserTaskEntry,
                                        uint            Flags,
                                        char            *pTaskName,
                                        uint            TaskPriority,
                                        uint            *pTaskID);

/*---------------------------*/
/* NPX init functions        */
/*---------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcInitNPX","RcInitEmul")
#endif
int _FIXED _NEAR RcInitNPX(             void );

int _FIXED _NEAR RcInitEmul(            void );

/*-----------------------------*/
/* ASCII init functions        */
/*-----------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcASCIIConfig","RcReadASCII","RcLinkASCIIDecode")
#endif
int _FIXED _FAR RcASCIIConfig(          int             ReturnOnError, 
                                        char            *pText,
                                        uint            *pErrorLine);

int _FIXED _FAR RcReadASCII(            int             ReturnOnError, 
                                        char            *pFileName, 
                                        uint            *pErrorLine);

int _FIXED _FAR RcLinkASCIIDecode(      char            *sec_name,
                                        int             (_FAR *fcp)(char *));

/*----------------------------*/
/* init functions             */
/*----------------------------*/
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("RcInitHsfs","RcInitSmallHsfs","RcInitFd0","RcInitHd0")
#pragma fixedparams("RcInitRamdisk","RcInitByt","RcInitBk1")
#pragma fixedparams("RcInitByt8250","RcInitBytCOM1","RcInitBytCOM2","RcInitBk1Ser")
#pragma fixedparams("RcInitBytEga","RcInitByt8530","RcInitByt8255")
#pragma fixedparams("RcInitBytLPT1","RcInitBytLPT2","RcInitBytLPT3")
#pragma fixedparams("RcInitCrt","RcInitCrt8250","RcInitCrtCOM1")
#pragma fixedparams("RcInitCrtCOM2","RcInit3964","RcInit3964r8250")
#pragma fixedparams("RcInit3964rCOM1","RcInit3964rCOM2","RcInit3964r8530")
#pragma fixedparams("RcInitVc","RcInitVcUnit","RcInitDfs")
#pragma fixedparams("RcInitASCIIDecodeDos","RcGetRm4WinBootpath")
#if !RM3
#pragma fixedparams("RcInitRamdisk32")
#endif
#endif
/*---------------------------*/
/* hsfs init function        */
/*---------------------------*/
int _FIXED _FAR RcInitHsfs(             uint            TaskPriority,
                                        uint            MaxNumChannels, 
                                        uint            MaxNumFiles,
                                        uint            NumBuffers,
                                        uint            BufferSize );

int _FIXED _FAR RcInitSmallHSFS(        uint            TaskPriority,
                                        uint            MaxNumChannels, 
                                        uint            MaxNumFiles,
                                        uint            NumBuffers,
                                        uint            BufferSize );

int _FIXED _FAR RcInitASCIIDecodeHsfs ( void );

/*---------------------------*/
/* fd0 init function         */
/*---------------------------*/
int _FIXED _NEAR RcInitFd0(             void );

/*---------------------------*/
/* hd0 init function         */
/*---------------------------*/
int _FIXED _NEAR RcInitHd0(             void );

/*---------------------------*/
/* ramdisk init function     */
/*---------------------------*/
int _FIXED _NEAR RcInitRamdisk(         ulong           Size );

#if !RM3
int _FIXED _NEAR RcInitRamdisk32(       ulong           Size );
#endif

/*---------------------------*/
/* byt driver init functions */
/*---------------------------*/
int _FIXED _NEAR RcInitByt(             void );      

int _FIXED _NEAR RcInitByt8250(         uint DataPortAddress,
                                        uint ModemCtrlAddress,
                                        uint LineCtrlAddress,
                                        uint IntEnableAddress,
                                        uint LineStatusAddress,
                                        ulong Baudrate,
                                        uint Mode,
                                        uint  Unsolicited1,
                                        uint  Unsolicited2,
                                        char *pUnsolicitedTaskName,
                                        char *pUnitName );

int _FIXED _NEAR RcInitBytCOM1(         ulong           BaudRate,
                                        uint            Mode, 
                                        uint            Unsolicited1,
                                        uint            Unsolicited2, 
                                        char            *pUnsolicitedTaskName );
    
int _FIXED _NEAR RcInitBytCOM2(         ulong           BaudRate,
                                        uint            Mode, 
                                        uint            Unsolicited1,
                                        uint            Unsolicited2, 
                                        char            *pUnsolicitedTaskName );

int _FIXED _NEAR RcInitBytEga(          uint            UnitNum, 
                                        uint            ColorAttr1, 
                                        uint            ColorAttr2,
                                        uint            ColorAttr3, 
                                        uint            ColorAttr4, 
                                        uint            Unsolicited1,
                                        uint            Unsolicited2, 
                                        char            *pUnsolicitedTaskName);

int _FIXED _NEAR RcInitByt8530(         uint            DataPortAddressA, 
                                        uint            CommandPortAddressA,
                                        ulong           BaudrateA, 
                                        uint            Unsolicited1A,
                                        uint            Unsolicited2A,
                                        uint            DataPortAddressB, 
                                        uint            CommandPortAddressB,
                                        ulong           BaudrateB, 
                                        uint            Unsolicited1B,
                                        uint            Unsolicited2B,
                                        uint            StatusPortAddress, 
                                        uint            IntVectNum,
                                        char            *pUnsolicitedTaskName);

int _FIXED _NEAR RcInitByt8255(         uint            DataPortAddress, 
                                        uint            CommandPortAddress,
                                        uint            StatusPortAddress,
                                        uint            StrobePortAddress, 
                                        char            *pUnitName);

int _FIXED _NEAR RcInitBytLPT1(         uint            Strobe );

int _FIXED _NEAR RcInitBytLPT2(         uint            Strobe );

int _FIXED _NEAR RcInitBytLPT3(         uint            Strobe );

/*---------------------------*/
/* bk1 driver init functions */
/*---------------------------*/
int _FIXED _NEAR RcInitBk1(             ulong           Address,
                                        ulong           Len,
                                        uint            UID,
                                        ulong           Addr0,
                                        ulong           Addr1,
                                        uint            IRQ );   
   
int _FIXED _NEAR RcInitBk1Ser(          void );

/*---------------------------*/
/* crt driver init functions */
/*---------------------------*/
int _FIXED _NEAR RcInitCrt(             void );

int _FIXED _NEAR RcInitCrt8250(         uint            DataPortAddress, 
                                        uint            ModemCtrlAddress,
                                        uint            LineCtrlAddress, 
                                        uint            IntEnableAddress,
                                        uint            LineStatusAddress, 
                                        ulong           Baudrate,
                                        uint            Mode, 
                                        uint            Unsolicited1, 
                                        uint            Unsolicited2,
                                        char            *pUnsolicitedTaskName, 
                                        char            *pUnitName);

int _FIXED _NEAR RcInitCrtCOM1(         ulong           Baudrate, 
                                        uint            Mode, 
                                        uint            Unsolicited1,
                                        uint            Unsolicited2,
                                        char            *pUnsolicitedTaskName);

int _FIXED _NEAR RcInitCrtCOM2(         ulong           Baudrate, 
                                        uint            Mode, 
                                        uint            Unsolicited1,
                                        uint            Unsolicited2,
                                        char            *pUnsolicitedTaskName);

/*---------------------------*/
/* 3964 driver init functions */
/*---------------------------*/
int _FIXED _NEAR RcInit3964(            void );      

int _FIXED _NEAR RcInit3964r8250(       uint            DataPortAddress, 
                                        uint            ModemCtrlAddress,
                                        uint            LineCtrlAddress, 
                                        uint            IntEnableAddress,
                                        uint            LineStatusAddress, 
                                        ulong           Baudrate,
                                        uint            Mode,
                                        uint            ProtCtrlMode, 
                                        uint            TimeoutAckn,
                                        uint            TimeoutChar, 
                                        char             *pUnitName);

int _FIXED _NEAR RcInit3964rCOM1(       ulong           Baudrate, 
                                        uint            Mode,
                                        uint            ProtCtrlMode, 
                                        uint            TimeoutAckn,
                                        uint            TimeoutChar);

int _FIXED _NEAR RcInit3964rCOM2(       ulong           Baudrate, 
                                        uint            Mode,
                                        uint            ProtCtrlMode, 
                                        uint            TimeoutAckn,
                                        uint            TimeoutChar);

int _FIXED _NEAR RcInit3964r8530(       uint            DataPortAddressA, 
                                        uint            CommandPortAddressA,
                                        ulong           BaudrateA,
                                        uint            DataPortAddressB, 
                                        uint            CommandPortAddressB,
                                        ulong           BaudrateB,
                                        uint            StatusPortAddress,
                                        uint            ProtCtrlMode, 
                                        uint            TimeoutAckn,
                                        uint            TimeoutChar);

/*--------------------------*/
/* VC driver init functions */
/*--------------------------*/
int _FIXED _NEAR RcInitVc(              void );

int _FIXED _NEAR RcInitVcUnit(          uint            VcUnitNum );

/*---------------------------------------*/
/* Dos File System driver init functions */
/*---------------------------------------*/
int _FIXED _NEAR RcInitDfs(             uint            TaskPrioriry,
                                        char            *pVolumeNames );

/*---------------------------------------*/
/* RMOS 4 WINDOS configuration functions */
/*---------------------------------------*/
int _FIXED _FAR RcInitASCIIDecodeDos(   void );

int _FIXED _FAR RcGetRm4WinBootpath(    void );

/*---------------------------------------*/
/* extended unexpected Interrupt handler */
/*---------------------------------------*/
int _FIXED _FAR RcInitExtDefHandler(    void );

/* --------------------------------- */
/* crun external function prototypes */
/* --------------------------------- */
#if defined (_ARCHITECTURE_)
#pragma fixedparams ("x_crun_entry",  "x_crun_entry_i", "x_socket_entry_i")
#pragma fixedparams ("x_cr_cfgio",    "x_cr_cfgmath")
#pragma fixedparams ("x_cr_cfgstdio", "x_cr_cfgtime")
#endif

void _FIXED _FAR x_cr_cfgio       ( void );
void _FIXED _FAR x_cr_cfgmath     ( void );
void _FIXED _FAR x_cr_cfgstdio    ( void );
void _FIXED _FAR x_cr_cfgtime     ( void );
void _FIXED _FAR x_crun_entry     ( void );
void _FIXED _FAR x_crun_entry_i   ( void );
void _FIXED _FAR x_socket_entry_i ( void );
void _FIXED _FAR x_cf_dec_bin     ( void );

/*----------------------------------------*/
/* functions and data for BORLAND support */
/*----------------------------------------*/
#ifdef __BORLANDC__
void _FAR x_init_bcc(void) ;
#if 0
void _FAR x_start_bcc(void) ;
#endif /* 0 */
extern int _FAR bcc_heap_segment ;
extern int _FAR bcc_heap_offset ;
#endif /* __BORLANDC__ */

#endif
/* end of RCINC.H */
