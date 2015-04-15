/*--FILE HEADER-(no tabs used)-----------------------------------------------
;
;   filename    : COM201.H
;   version     : 0003
;   contents    : Header file startup and shutdown interface
;   author      : G.H.
;   date        : May 10, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT--------------------------------------------
;
;   function    : The header file contains the declarations needed by an
;                 user of the startup and shutdown interface.
;                 The startup and shutdown interface is able to create and
;                 destroy DP instances. DP instances are logical connections
;                 between DP databases and units SMP16-COM201/CP5411(DP12-ISA).
;                  
;
;   RMOS3
;
;---END OF FILE HEADER-------------------------------------------------------
;
;---MODIFICATION HEADER------------------------------------------------------
;
;   Mar 29, 1996:        0001  Original issue
;   Apr  3, 1996:        0002  CP5411/DP12-ISA support added
;   May 10, 1996:        0003  DPS error codes added
;
;---END OF FILE HEADER-----------------------------------------------------*/

#ifndef __COM201_H__
  #define __COM201_H__

  /***** needed RMOS headers ***********************************************/

  #ifndef _RMCOMP_H_
    #include <rmcomp.h>
  #endif
  #ifndef _TYPEDEFS_H_
    #include <typedefs.h>
  #endif

  /***** alignment and calling convention **********************************/

  #if ((defined(_ARCHITECTURE_)) || (defined(CADUL)))
                      /* Intel C compiler iC386 or CAD-UL C compiler CC386 */
    #pragma fixedparams("Com201Start", "Com201Stop")
    #pragma fixedparams("Dp12IsaStart", "Dp12IsaStop")
  #endif

  #if defined _MSC_VER                             /* Microsoft C compiler */
    #pragma pack(1)
  #endif

  #ifdef __BORLANDC__                                /* Borland C compiler */
    #pragma option -a-
  #endif

  /***** return codes ******************************************************/

  typedef enum {
    ComNoErrLog=0,            /* debug reporter enabled */
    ComErrLog
  } ComErrLogFmt;
  
  typedef enum {
    ComDPSModeRepeat=0,
    ComDPSModeBuffered
  } ComDPSModeFmt;
  
  typedef enum {
    ComOk=0,                   /* OK */
    ComErrDriver,              /* error: driver not installed */
    ComErrReStart,             /* error: attempt to restart DP instance */ 
    ComErrReStop,              /* error: attempt to restop DP instance */ 
    ComErrUnit,                /* error: unknown unit selected */
    ComErrCfg,                 /* error: unit configuration */
    ComErrParam,               /* error: parameter error */
    ComErrL2Reset,             /* error: L2 reset */
    ComErrL2ResetNoConf,       /* error: L2 reset not direct confirmed */
    ComErrL2FillBpb,           /* error: L2 bus parameter */
    ComErrL2MemInit,           /* error: L2 init memory manager */
    ComErrL2MemAlloc,          /* error: L2 memory allocation */
    ComErrInitCbfSrv,          /* error: L2 init call back server */
    ComErrDataBase,            /* error: DP invalid data base */
    ComErrStationMode,         /* error: DP invalid station mode */
    ComErrDPMInit,             /* error: DPM init */
    ComErrDPMInitAck,          /* error: DPM init acknowledge */
    ComErrBoardId,             /* error: invalid board id */
    ComErrDAMInit,             /* error: DAM init */
    ComErrPAMInit,             /* error: PAM init */
    ComErrHardware,            /* error: hardware */
    ComErrPtrs,                /* error: no GTD entry available */
    ComErrFillSlcb,            /* error: DPM fill SLave Control Block */
    ComErrSetMaMo,             /* error: DPM set master mode */
    ComErrSetMaMoAck,          /* error: DPM set master mode acknowledge */
    ComErrAddSlv,              /* error: DPM add slave */
    ComErrWithdrawSlv,         /* error: DPM withdraw slave */
    ComErrDPMClose,            /* error: DPM close */
    ComErrDPSInit,             /* error: DPS init */
    ComErrDPSMemAlloc,         /* error: DPS memory allocation */
    ComErrDPSInBuf,            /* error: DPS get input buffer */
    ComErrDPSDiaBuf,           /* error: DPS get diag buffer */
    ComErrFatal                /* error: common fatal error */
  } ComEcodeFmt;

  /***** prototypes ********************************************************/

  ComEcodeFmt _FIXED _FAR Com201Start(unsigned       Unit, /* SMP16-COM201 */
                                      void _FAR     *pDataBase,
                                      unsigned long  LenDataBase,
                                      ComDPSModeFmt  DPSMode,
                                      ComErrLogFmt   ErrLog);

  ComEcodeFmt _FIXED _FAR Com201Stop (unsigned       Unit);

  ComEcodeFmt _FIXED _FAR Dp12IsaStart(unsigned       Unit,      /* CP5411 */
                                       void _FAR     *pDataBase,
                                       unsigned long  LenDataBase,
                                       ComDPSModeFmt  DPSMode,
                                       ComErrLogFmt   ErrLog);
  ComEcodeFmt _FIXED _FAR Dp12IsaStop (unsigned Unit);

  /*************************************************************************/

  #if defined _MSC_VER
    #pragma pack()         /* reset alignment to commandline specification */
  #endif

  #ifdef __BORLANDC__
    #pragma option -a.     /* reset alignment to commandline specification */
  #endif

#endif
