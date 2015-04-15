/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : RMAPI.H
;   version     : 0010
;   contents    : Include-File for RMOS API functions
;   author      : K.P.H.
;   date        : Jun 23, 1999
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Function prototypes for RMOS API functions
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Feb 23, 1995  P.F.   0001  Original issue
;   Mar 22, 1995  K.P.H. 0002  Additional changes for RMOS2
;   May 22, 1995  K.P.H. 0003  Added more calls to FLAT HLI
;   May 30, 1995  K.P.H. 0004  Corrected RmSetSMRCount
;   Sep 13, 1995  K.P.H. 0005  Modification for RMOS V3.12
;   Sep 28, 1995  P.F.   0006  Error corrected for C++ (section "Interrupt")
;   Nov 21, 1995  K.P.H. 0007  Added _FAR for all data pointer
;   Dec 04, 1996  K.P.H. 0008  Added RmSetIntHandler
;   Jun 23, 1999  A.B.   0009  Adaptation to Visual C++
;   Jul 14, 2001  B.N.   0010  Added RmGetStatusMessageQueue
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _RMAPI_H_
#define _RMAPI_H_

#ifndef _PROT_H_
#include <prot.h>
#endif  /* _PROT_H_ */
#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _RMDEF_H_
#include <rmdef.h>
#endif  /* _RMDEF_H_ */
#ifndef _RMTYPES_H_
#include <rmtypes.h>
#endif  /* _RMTYPES_H_ */


#if defined(_ARCHITECTURE_) || defined(CADUL)
#ifndef _NOVERS
static const
char idstr_rmapi_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"    /* In-code identification. */
        "\1"    "RMAPI.H"               "\1"
        "\2"    "0010"                  "\2"
        "\3"    "B.N."                  "\3"
};
#endif
#endif  /* defined(_ARCHITECTURE_) || defined(CADUL) */

 /**************************************************************************/
 /*                    Prototypes for RMOS API functions                   */
 /**************************************************************************/

 /****************************/
 /*   System configuration   */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmResetOS,RmInitOS,RmCreateOS,RmSetOS,RmRunOS)
 #pragma fixedparams (RmSetPutcharProc,RmSetSVC,RmSetSMRCount)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if !RMFLAT

int _FIXED _FAR RmResetOS(              uint            NPXTestMode,
                                        ulong           SysBAddress,
                                        ulong           RAMEndAddress );
#endif /* end RMFLAT */

#ifdef _MSC_VER
#define RmInitOS(par1, par2, par3, par4, par5, par6)	\
        RmInitOS(par6, par5, par4, par3, par2, par1)  
#define RmCreateOS(par1, par2, par3)    RmCreateOS(par3, par2, par1)
#define RmSetOS(par1, par2, par3)       RmSetOS(par3, par2, par1)
#endif  /*  end _MSC_VER */
int _FIXED _FAR RmInitOS(               ulong           SystemPeriod,
                                        rmfarproc       InitTimerProc,
                                        rmproc          IssueEOIProc,
                                        int (_FIXED _FAR *SetPICMaskProc)(uint IRQ),
                                        int (_FIXED _FAR *SetClockProc)(RmTimeStruct *pDate),
                                        int (_FIXED _FAR *GetClockProc)(RmTimeStruct *pDate) );

int _FIXED _FAR RmCreateOS(             uint            SemaphoreNum,
                                        uint            FlagNum,
                                        uint            MailboxNum );

int _FIXED _FAR RmSetOS(                uint            RoundRobinCounter,
                                        uint            SVCExceptionType,
                                        const char _FAR *pUnitName );

#if !RMFLAT

int _FIXED _FAR RmRunOS(                const char _FAR *pTaskName );

int _FIXED _FAR RmSetPutcharProc(       int(_FIXED _FAR *PutcharProc)(char) );

int _FIXED _FAR RmSetSVC(               uint            SVCNumber,
                                        rmfarproc       SVCHandler );
#endif /* end RMFLAT */

int _FIXED _FAR RmSetSMRCount(          uint            SMRNumber );

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*          System          */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmDecode,RmLinkDecodeProc,RmLinkTimerProc)
 #pragma fixedparams (RmUnlinkTimerProc,RmGetSystemTables,RmGetSysB)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _MSC_VER
#define RmDecode(par1, par2, par3)      RmDecode(par3, par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmDecode(               uint            Type,
                                        int             Code,
                                        char       _FAR *pText );

int _FIXED _FAR RmLinkTimerProc(        rmfarproc       ProcEntry );

int _FIXED _FAR RmUnlinkTimerProc(      rmfarproc       ProcEntry );

int _FIXED _FAR RmGetSystemTables(      RmSystemTables _FAR *pSystemTables );

#if !RMFLAT

int _FIXED _FAR RmLinkDecodeProc(       rmfarproc       DecodeProc );

#endif /* end RMFLAT */

int _FIXED _FAR RmGetSysB(              RmSysB _FAR * _FAR *ppSysB );

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*        Descriptor        */
 /****************************/

#if RM3   /* only in RMOS 3 */
#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmCreateDescriptor,RmDeleteDescriptor,RmChangeDescriptor)
 #pragma fixedparams (RmChangeDescriptorAccess,RmGetLinAddress,RmMapMemory)
 #pragma fixedparams (RmGetPhysAddress,RmFlatToSegAddress,RmSegToFlatAddress)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if !RMFLAT

int _FIXED _FAR RmCreateDescriptor(       ulong         LinAddress,
                                          ulong         Limit,
                                          selector _FAR *pSel );

int _FIXED _FAR RmDeleteDescriptor(       selector      Sel );

int _FIXED _FAR RmChangeDescriptor(       selector      Sel,
                                          ulong         LinAddress,
                                          ulong         Limit );

int _FIXED _FAR RmChangeDescriptorAccess( selector      Sel,
                                          uint          Access );

#endif /* end !RMFLAT */

#ifdef _MSC_VER
#define RmGetLinAddress(par1, par2)       RmGetLinAddress(par2, par1)
#define RmGetPhysAddress(par1, par2)      RmGetPhysAddress(par2, par1)
#define RmMapMemory(par1, par2, par3)     RmMapMemory(par3, par2, par1)
#define RmFlatToSegAddress(par1, par2, par3)                       \
        RmFlatToSegAddress(par3, par2, par1)
#define RmSegToFlatAddress(par1, par2, par3)   RmSegToFlatAddress(par3, par2, par1)
#endif /* _MSC_VER */

int _FIXED _FAR RmGetLinAddress(          void     _FAR *pPointer,
                                          ulong    _FAR *pLinAddress );

int _FIXED _FAR RmGetPhysAddress(         void     _FAR *pPointer,
                                          ulong    _FAR *pPhysAddress );

int _FIXED _FAR RmMapMemory(              ulong         PhysAddress,
                                          ulong         Length,
                                          void _FAR * _FAR *pPointer );

int _FIXED _FAR RmFlatToSegAddress(       ulong         FlatAddress,
                                          ushort   _FAR *pSel,
                                          ulong    _FAR *pOffset);

int _FIXED _FAR RmSegToFlatAddress(       ushort        Sel,
                                          ulong         Offset,
                                          ulong    _FAR *pFlatAddress );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end RM3 */

 /****************************/
 /*          Memory          */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmAlloc,RmFree,RmReAlloc,RmFreeAll)
 #pragma fixedparams (RmExclude,RmGetSize)
 #pragma fixedparams (RmMemPoolAlloc,RmCreateMemPool,RmDeleteMemPool)
 #pragma fixedparams (RmGetMemPoolInfo)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _MSC_VER
#define RmAlloc(par1, par2, par3, par4)	RmAlloc(par4, par3, par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmAlloc(                ulong           TimeOutValue,
                                        uint            Mode,
                                        ulong           Size,
                                        void _FAR * _FAR *ppMemory );

int _FIXED _FAR RmFree(                 void       _FAR *pMemory );

#ifdef _MSC_VER
#define RmReAlloc(par1, par2, par3, par4) RmReAlloc(par4, par3, par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmReAlloc(              ulong           TimeOutValue,
                                        uint            Mode,
                                        ulong           NewSize,
                                        void _FAR * _FAR *ppMemory );

int _FIXED _FAR RmFreeAll(              uint            TaskID );

#ifdef _MSC_VER
#define RmExclude(par1, par2, par3)     RmExclude(par3, par2, par1)
#define RmGetSize(par1, par2)           RmGetSize(par2, par1)
#define RmMemPoolAlloc(par1, par2, par3, par4, par5)            \
        RmMemPoolAlloc(par5, par4, par3, par2, par1) 
#define RmGetMemPoolInfo(par1, par2)    RmGetMemPoolInfo(par2, par1)
#define RmCreateMemPool(par1, par2, par3, par4)                 \
        RmCreateMemPool(par4, par3, par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmExclude(              ulong           PhysAddress,
                                        ulong           Size,
                                        void _FAR * _FAR *ppMemory );

int _FIXED _FAR RmGetSize(              void       _FAR *pMemory,
                                        ulong      _FAR *pSize );

int _FIXED _FAR RmMemPoolAlloc(         ulong           TimeOutValue,
                                        uint            Mode,
                                        uint            PoolID,
                                        ulong           Size,
                                        void _FAR * _FAR *ppMemory );

int _FIXED _FAR RmGetMemPoolInfo(       uint            PoolID,
                                        RmMemPoolInfoStruct _FAR *Info);

int _FIXED _FAR RmCreateMemPool(        const char _FAR *pPoolName,
                                        void       _FAR *pPoolAddress,
                                        ulong           Size,
                                        uint       _FAR *pPoolID);

int _FIXED _FAR RmDeleteMemPool(        uint            PoolID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*         Resources        */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmCatalog,RmList,RmGetEntry,RmGetName,RmUncatalog)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _MSC_VER
#define RmCatalog(par1, par2, par3, par4)                    \
        RmCatalog(par4, par3, par2, par1)
#define RmList(par1, par2, par3, par4, par5)                 \
        RmList(par5, par4, par3, par2, par1)
#define RmGetEntry(par1, par2, par3)    RmGetEntry(par3, par2, par1)
#define RmGetName(par1, par2, par3, par4)                    \
        RmGetName(par4, par3, par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmCatalog(              uint            Type,
                                        uint            ID,
                                        ulong           IDEx,
                                        const char _FAR *pName );

int _FIXED _FAR RmList(                 uint            Type,
                                        uint            Count,
                                        uint       _FAR *pIndex,
                                        uint       _FAR *pNumEntries,
                                        RmEntryStruct _FAR *pEntry );

int _FIXED _FAR RmGetEntry(             ulong           TimeOutValue,
                                        const char _FAR *pName,
                                        RmEntryStruct _FAR *pEntry );

int _FIXED _FAR RmGetName(              uint            Type,
                                        uint            ID,
                                        ulong           IDEx,
                                        char       _FAR *pName );

int _FIXED _FAR RmUncatalog(            const char _FAR *pName );

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*           Task           */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmCreateTask,RmDeleteTask,RmStartTask,RmQueueStartTask)
 #pragma fixedparams (RmCreateChildTask,RmGetTCBAddress)
 #pragma fixedparams (RmEndTask,RmKillTask,RmRestartTask)
 #pragma fixedparams (RmResumeTask,RmSuspendTask,RmActivateTask,RmPauseTask)
 #pragma fixedparams (RmGetTaskID,RmGetTaskPriority,RmSetTaskPriority)
 #pragma fixedparams (RmGetTaskState,RmGetTaskInfo,RmEnableScheduler)
 #pragma fixedparams (RmDisableScheduler,RmCreateTaskEx)
#if RM3
 #pragma fixedparams (RmQCopy,RmLinkLRS,RmSequenceTask)
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _MSC_VER
#define RmCreateTask(par1, par2, par3, par4, par5)              \
        RmCreateTask(par5, par4, par3, par2, par1)
#define RmCreateChildTask(par1, par2, par3, par4, par5)         \
        RmCreateChildTask(par5, par4, par3, par2, par1)
#define RmCreateTaskEx(par1, par2, par3) RmCreateTaskEx(par3, par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmCreateTask(           const char _FAR *pTaskName,
                                        ulong           TaskStackSize,
                                        uint            Priority,
                                        rmfarproc       TaskEntry,
                                        uint       _FAR *pTaskID );

int _FIXED _FAR RmCreateChildTask(      const char _FAR *pTaskName,
                                        ulong           TaskStackSize,
                                        uint            Priority,
                                        rmfarproc       TaskEntry,
                                        uint       _FAR *pTaskID );

int _FIXED _FAR RmCreateTaskEx(         const char _FAR *pTaskName,
                                        RmTCDStruct _FAR *pTcd,
                                        uint       _FAR *pTaskID );

int _FIXED _FAR RmDeleteTask(           uint            TaskID );

#ifdef _MSC_VER
#define RmStartTask(par1, par2, par3, par4, par5)                \
        RmStartTask(par5, par4, par3, par2, par1)
#define RmQueueStartTask(par1, par2, par3, par4, par5)           \
        RmQueueStartTask(par5, par4, par3, par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmStartTask(            uint            Wait,
                                        uint            TaskID,
                                        uint            Priority,
                                        uint            RegVal1,
                                        uint            RegVal2 );

int _FIXED _FAR RmQueueStartTask(       uint            Wait,
                                        uint            TaskID,
                                        uint            Priority,
                                        uint            RegVal1,
                                        uint            RegVal2 );

int _FIXED _FAR RmEndTask(              void );

#ifdef _MSC_VER
#define RmKillTask(par1, par2)          RmKillTask(par2, par1)
#define RmRestartTask(par1, par2)       RmRestartTask(par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmKillTask(             uint            Mode,
                                        uint            TaskID );

int _FIXED _FAR RmRestartTask(          uint            Mode,
                                        ulong           TimeValue );

int _FIXED _FAR RmResumeTask(           uint            TaskID );

int _FIXED _FAR RmSuspendTask(          uint            TaskID );

int _FIXED _FAR RmActivateTask(         uint            TaskID );

int _FIXED _FAR RmPauseTask(            ulong           TimeValue );

#ifdef _MSC_VER
#define RmGetTaskID(par1, par2)         RmGetTaskID(par2, par1)
#define RmGetTCBAddress(par1, par2)     RmGetTCBAddress(par2, par1)
#define RmGetTaskPriority(par1, par2)   RmGetTaskPriority(par2, par1)
#define RmSetTaskPriority(par1, par2)   RmSetTaskPriority(par2, par1)
#define RmGetTaskState(par1, par2)      RmGetTaskState(par2, par1)
#define RmGetTaskInfo(par1, par2)       RmGetTaskInfo(par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmGetTaskID(            uint            Tcb,
                                        uint       _FAR *pTaskID );

int _FIXED _FAR RmGetTCBAddress(        uint            TaskID,
                                        void _FAR * _FAR *ppTcb );

int _FIXED _FAR RmGetTaskPriority(      uint            TaskID,
                                        uint       _FAR *pPriority );

int _FIXED _FAR RmSetTaskPriority(      uint            TaskID,
                                        uint            Priority );

int _FIXED _FAR RmGetTaskState(         uint            TaskID,
                                        uint       _FAR *pTaskState );

int _FIXED _FAR RmGetTaskInfo(          uint            TaskID,
                                        RmTaskInfoStruct _FAR *pTaskInfo );

int _FIXED _FAR RmEnableScheduler(      void );

int _FIXED _FAR RmDisableScheduler(     void );

#if RM3
int _FIXED _FAR RmQCopy(                RmRCBStruct _FAR *Rcb );

#ifdef _MSC_VER
#define RmLinkLRS(par1, par2)           RmLinkLRS(par2, par1)
#define RmSequenceTask(par1, par2, par3)                          \
        RmSequenceTask(par3, par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmLinkLRS(              uint            TaskID,
                                        void       _FAR *pLRS );

int _FIXED _FAR RmSequenceTask(         uint            Mode,
                                        uint            StartTaskID,
                                        uint            EndTaskID );
#endif
#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*          Driver          */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmCreateDriver,RmDeleteDriver,RmCreateUnit,RmDeleteUnit)
 #pragma fixedparams (RmResumeDriver,RmSuspendDriver,RmIO)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if !RMFLAT
int _FIXED _FAR RmCreateDriver(         uint            Mode,
                                        const char _FAR *pDeviceName,
                                        RmDCDStruct _FAR *pDcd,
                                        uint       _FAR *pDriverID );

int _FIXED _FAR RmDeleteDriver(         uint            DeviceID );

int _FIXED _FAR RmCreateUnit(           const char _FAR *pDeviceName,
                                        const char _FAR *pUnitName,
                                        RmUCDStruct _FAR *pUcd,
                                        uint       _FAR *pUnitID );

int _FIXED _FAR RmDeleteUnit(           uint            DeviceID,
                                        uint            UnitID );

int _FIXED _FAR RmResumeDriver(         uint            DeviceID );

int _FIXED _FAR RmSuspendDriver(        uint            DeviceID );

int _FIXED _FAR RmIO(                   uint            Function,
                                        uint            DeviceID,
                                        uint            UnitID,
                                        uint            FlagID,
                                        uint            FlagMask,
                                        RmIOStatusStruct _FAR *pState,
                                        void       _FAR *pParam );

#endif /* end !RMFLAT */

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*           Flag           */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmCreateFlagGrp,RmDeleteFlagGrp,RmSetFlag)
 #pragma fixedparams (RmSetFlagDelayed,RmGetFlag,RmResetFlag)
 #pragma fixedparams (RmSetLocalFlag,RmResetLocalFlag)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _MSC_VER
#define RmCreateFlagGrp(par1, par2)     RmCreateFlagGrp(par2, par1)
#endif /* end _MSC_VEr */

int _FIXED _FAR RmCreateFlagGrp(        const char _FAR *pFlagGrpName,
                                        uint       _FAR *pFlagGrpID );

int _FIXED _FAR RmDeleteFlagGrp(        uint            FlagGrpID );

#ifdef _MSC_VER
#define RmSetFlag(par1, par2)           RmSetFlag(par2, par1)
#define RmSetFlagDelayed(par1, par2, par3)                        \
        RmSetFlagDelayed(par3, par2, par1)
#define RmResetFlag(par1, par2)         RmResetFlag(par2, par1)
#define RmGetFlag(par1, par2, par3, par4, par5)                   \
        RmGetFlag(par5, par4, par3, par2, par1)
#define RmSetLocalFlag(par1, par2)      RmSetLocalFlag(par2, par1)
#define RmResetLocalFlag(par1, par2)    RmResetLocalFlag(par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmSetFlag(              uint            FlagGrpID,
                                        uint            FlagMask );

int _FIXED _FAR RmSetFlagDelayed(       ulong           TimeValue,
                                        uint            FlagGrpID,
                                        uint            FlagMask );

int _FIXED _FAR RmResetFlag(            uint            FlagGrpID,
                                        uint            FlagMask );

int _FIXED _FAR RmGetFlag(              ulong           TimeOutValue,
                                        uint            Type,
                                        uint            FlagGrpID,
                                        uint            TestMask,
                                        uint       _FAR *pFlagMask );

int _FIXED _FAR RmSetLocalFlag(         uint            TaskID,
                                        uint            FlagMask );

int _FIXED _FAR RmResetLocalFlag(       uint            TaskID,
                                        uint            FlagMask );

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*         Mailbox          */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmCreateMailbox,RmDeleteMailbox,RmSendMail)
 #pragma fixedparams (RmReceiveMail,RmSetMailboxSize,RmSendMailDelayed)
 #pragma fixedparams (RmSendMailCancel)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _MSC_VER
#define RmCreateMailbox(par1, par2)     RmCreateMailbox(par2, par1)
#endif /* end _MSC_VER */
int _FIXED _FAR RmCreateMailbox(        const char _FAR *pMailboxName,
                                        uint       _FAR *pMailboxID );

int _FIXED _FAR RmDeleteMailbox(        uint            MailboxID );

#ifdef _MSC_VER
#define RmSendMail(par1, par2, par3, par4)                        \
        RmSendMail(par4, par3, par2, par1)
#define RmReceiveMail(par1, par2, par3)                           \
        RmReceiveMail(par3, par2, par1)
#define RmSetMailboxSize(par1, par2)    RmSetMailboxSize(par2, par1)
#define RmSendMailDelayed(par1, par2, par3, par4, par5)           \
        RmSendMailDelayed(par5, par4, par3, par2, par1)
#define RmSendMailCancel(par1, par2)    RmSendMailCancel(par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmSendMail(             ulong           TimeOutValue,
                                        uint            Priority,
                                        uint            MailboxID,
                                        void       _FAR *pMail );

int _FIXED _FAR RmReceiveMail(          ulong           TimeOutValue,
                                        uint            MailboxID,
                                        void       _FAR *pMail );

int _FIXED _FAR RmSetMailboxSize(       uint            MailboxID,
                                        uint            Limit );

int _FIXED _FAR RmSendMailDelayed(      ulong           TimeValue,
                                        uint            Priority,
                                        uint            MailboxID,
                                        void       _FAR *pMail,
                                        RmMailIDStruct _FAR *pMailID );

int _FIXED _FAR RmSendMailCancel(       RmMailIDStruct _FAR *pMailID,
                                        void       _FAR *pMail );

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*         Message          */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmCreateMessageQueue,RmDeleteMessageQueue,RmSendMessage)
 #pragma fixedparams (RmReadMessage,RmSetMessageQueueSize,RmGetStatusMessageQueue)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _MSC_VER
#define RmCreateMessageQueue(par1, par2) RmCreateMessageQueue(par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmCreateMessageQueue(   char       _FAR *pMessageQueueName,
                                        uint            TaskID );

int _FIXED _FAR RmDeleteMessageQueue(   uint            TaskID );

#ifdef _MSC_VER
#define RmSendMessage(par1, par2, par3, par4, par5)                    \
        RmSendMessage(par5, par4, par3, par2, par1)
#define RmReadMessage(par1, par2, par3) RmReadMessage(par3, par2, par1)
#define RmSetMessageQueueSize(par1, par2) RmSetMessageQueueSize(par2,par1)
#define RmGetStatusMessageQueue(par1, par2) RmGetStatusMessageQueue(par2,par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmSendMessage(          ulong           TimeOutValue,
                                        uint            Priority,
                                        uint            TaskID,
                                        uint            Message,
                                        void       _FAR *pMessageParam );

int _FIXED _FAR RmReadMessage(          ulong           TimeOutValue,
                                        uint       _FAR *pMessage,
                                        void _FAR * _FAR *pMessageParam );

int _FIXED _FAR RmSetMessageQueueSize(  uint            TaskID,
                                        uint            Limit );

int _FIXED _FAR RmGetStatusMessageQueue(uint            TaskID,
                                        uint       _FAR *NumberOfMessages );

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*        Semaphore         */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmCreateBinSemaphore,RmDeleteBinSemaphore)
 #pragma fixedparams (RmReleaseBinSemaphore,RmGetBinSemaphore)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _MSC_VER
#define RmCreateBinSemaphore(par1, par2) RmCreateBinSemaphore(par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmCreateBinSemaphore(   const char _FAR *pSemaphoreName,
                                        uint       _FAR *pSemaphoreID );

int _FIXED _FAR RmDeleteBinSemaphore(   uint            SemaphoreID );

int _FIXED _FAR RmReleaseBinSemaphore(  uint            SemaphoreID );

#ifdef _MSC_VER
#define RmGetBinSemaphore(par1, par2)   RmGetBinSemaphore(par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmGetBinSemaphore(      ulong           TimeOutValue,
                                        uint            SemaphoreID );

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*           Time           */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmSetSystemTime,RmGetSystemTime,RmSetHWClockTime)
 #pragma fixedparams (RmGetHWClockTime,RmGetAbsTime,RmGetSystemPeriod)
 #pragma fixedparams (RmSetClocks,RmSetSystemPeriod)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int _FIXED _FAR RmSetSystemTime(        const RmAsciiTimeStruct _FAR *pTimeInfo );

int _FIXED _FAR RmGetSystemTime(        RmAsciiTimeStruct _FAR *pTimeInfo );

int _FIXED _FAR RmSetHWClockTime(       const RmAsciiTimeStruct _FAR *pTimeInfo );

int _FIXED _FAR RmGetHWClockTime(       RmAsciiTimeStruct _FAR *pTimeInfo );

int _FIXED _FAR RmSetClocks(            const RmAsciiTimeStruct _FAR *pTimeInfo );

int _FIXED _FAR RmGetAbsTime(           RmAbsTimeStruct   _FAR *pAbsTime );

int _FIXED _FAR RmGetSystemPeriod(      ulong             _FAR *pTime );

int _FIXED _FAR RmSetSystemPeriod(      ulong                   Time );

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /****************************/
 /*         Interrupt        */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmIntrhand,RmSetDeviceHandler)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _MSC_VER
#define RmIntrhand(par1, par2, par3, par4, par5, par6, par7)      \
        RmIntrhand(par7, par6, par5, par4, par3, par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmIntrhand(             uint            IntType,
                                        uint            IntNum,
                                        uint            ID,
                                        uint            IntPriv,
                                        rmfarproc       Entry0,
                                        rmfarproc       Entry1,
                                        rmfarproc  _FAR *pOldEntry );

/* RmGetIntHandler( uint IntNum, rmfarproc *pHandlerEntry ); */
#define RmGetIntHandler( IntNum, pHandlerEntry )                           \
    RmIntrhand( RM_IH_CUR | ((IntNum & RM_IRQ_TAG) ? RM_IH_HW : RM_IH_SW), \
                (uint) IntNum,                                             \
                0u,                                                        \
                0u,                                                        \
                (rmfarproc) 0,                                             \
                (rmfarproc) 0,                                             \
                (rmfarproc *) pHandlerEntry )

/* RmSetIntDefHandler( uint IntNum ); */
#define RmSetIntDefHandler( IntNum )                                       \
    RmIntrhand( RM_IH_DFT | ((IntNum & RM_IRQ_TAG) ? RM_IH_HW : RM_IH_SW), \
                (uint) IntNum,                                             \
                0u,                                                        \
                0u,                                                        \
                (rmfarproc) 0,                                             \
                (rmfarproc) 0,                                             \
                (rmfarproc *) 0 )

/* RmReserveInterrupt( uint IntNum ); */
#define RmReserveInterrupt( IntNum )                                      \
    RmIntrhand( RM_IH_DI | ((IntNum & RM_IRQ_TAG) ? RM_IH_HW : RM_IH_SW), \
                (uint) IntNum,                                            \
                0u,                                                       \
                0u,                                                       \
                (rmfarproc) 0,                                            \
                (rmfarproc) 0,                                            \
                (rmfarproc *) 0 )

/* RmSetIntDIHandler( uint IntNum, rmfarproc DIHandlerEntry ); */
#define RmSetIntDIHandler( IntNum, DIHandlerEntry )                       \
    RmIntrhand( RM_IH_DI | ((IntNum & RM_IRQ_TAG) ? RM_IH_HW : RM_IH_SW), \
                (uint) IntNum,                                            \
                0u,                                                       \
                0u,                                                       \
                (rmfarproc) DIHandlerEntry,                               \
                (rmfarproc) 0,                                            \
                (rmfarproc *) 0 )

/* RmSetIntISHandler( uint IntNum, rmfarproc IHandlerEntry, rmfarproc SHandlerEntry ); */
#define RmSetIntISHandler( IntNum, IHandlerEntry, SHandlerEntry)           \
    RmIntrhand( RM_IH_IS | ((IntNum & RM_IRQ_TAG) ? RM_IH_HW : RM_IH_SW),  \
                (uint) IntNum,                                             \
                0u,                                                        \
                0u,                                                        \
                (rmfarproc) IHandlerEntry,                                 \
                (rmfarproc) SHandlerEntry,                                 \
                (rmfarproc *) 0 )

/* RmSetIntTaskHandler( uint IntNum, uint TaskID ); */
#define RmSetIntTaskHandler( IntNum, TaskID )                              \
    RmIntrhand( RM_IH_TSK | ((IntNum & RM_IRQ_TAG) ? RM_IH_HW : RM_IH_SW), \
                (uint) IntNum,                                             \
                (uint) TaskID,                                             \
                0u,                                                        \
                (rmfarproc) 0,                                             \
                (rmfarproc) 0,                                             \
                (rmfarproc *) 0 )

/* RmSetIntMailboxHandler( uint IntNum, uint MailboxID ); */
#define RmSetIntMailboxHandler( IntNum, MailboxID,MailPriority )            \
    RmIntrhand( RM_IH_MBOX | ((IntNum & RM_IRQ_TAG) ? RM_IH_HW : RM_IH_SW), \
                (uint) IntNum,                                              \
                (uint) MailboxID,                                           \
                (uint) MailPriority,                                        \
                (rmfarproc) 0,                                              \
                (rmfarproc) 0,                                              \
                (rmfarproc *) 0 )

/* RmSetIntHandler( uint IntNum, rmfarproc HandlerEntry ); */
#define RmSetIntHandler( IntNum, HandlerEntry )                           \
    RmIntrhand( RM_IH_IDT,                                                \
                (uint) IntNum,                                            \
                0u,                                                       \
                0u,                                                       \
                (rmfarproc) HandlerEntry,                                 \
                (rmfarproc) 0,                                            \
                (rmfarproc *) 0 )

#ifdef _MSC_VER
#define RmSetDeviceHandler(par1, par2, par3, par4)                 \
        RmSetDeviceHandler(par4, par3, par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmSetDeviceHandler(     uint            IntNum,
                                        const char      *pDeviceName,
                                        const char      *pUnitName,
                                        rmfarproc       HandlerEntry );

#ifdef __cplusplus
}
#endif /* __cplusplus */


 /****************************/
 /*          Debug           */
 /****************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (RmSetBreakpoint,RmKillBreakpoint)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _MSC_VER
#define RmSetBreakpoint(par1, par2, par3, par4, par5, par6)       \
        RmSetBreakpoint(par6, par5, par4, par3, par2, par1)
#define RmKillBreakpoint(par1, par2)    RmKillBreakpoint(par2, par1)
#endif /* end _MSC_VER */

int _FIXED _FAR RmSetBreakpoint(        uint            CpuID,
                                        uint            BpID,
                                        uint            BpType,
                                        void       _FAR *BpAddress,
                                        uint            BpCount,
                                        void       _FAR *BpStruct );

int _FIXED _FAR RmKillBreakpoint(       uint            CpuID,
                                        uint            BpID );

 /****************************/
 /*      Usefull Macros      */
 /****************************/

/* define data for usage in RMOS macros */
#define RMDECL_MACROS     \
    int __rmerror__;  \
    union {           \
    void _FAR     *p; \
    RmEntryStruct cat;\
    } __rmvar__
    
#define RmCatalogPointer(name,ptr)                     \
    (__rmvar__.p=(void _FAR *) (ptr),                  \
    RmCatalog(  RM_CATALOG_SYSTEM | RM_CATALOG_HIDDEN, \
                (uint)  FP_SEG(__rmvar__.p),           \
                (ulong) FP_OFF(__rmvar__.p),           \
                name)                                  \
    )

#define RmGetPointerEntry(time,name,ptr)                 \
    (__rmerror__ = RmGetEntry(time,name,&__rmvar__.cat), \
    *(ptr)=buildptr((selector) __rmvar__.cat.id,         \
                (void _NEAR *) __rmvar__.cat.ide),       \
    __rmerror__                                          \
    )

#ifdef __cplusplus
}
#endif /* __cplusplus */

 /********************************/
 /* Task parameter ((E)AX,(E)BX) */
 /********************************/

#ifndef _RM_TASKPARAM_
#define _RM_TASKPARAM_

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (getparm, get2ndparm, getdword)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int *          _FIXED _FAR getparm(     void ); /* Startparameter as pointer */
unsigned int   _FIXED _FAR get2ndparm(  void ); /* 2nd start parameter (e)bx */
unsigned long  _FIXED _FAR getdword(    void ); /* Startparameter as long    */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RM_TASKPARAM_ */

 /****************************/
 /*         Busy task        */
 /****************************/

#ifndef _RM_BUSYTASK_
#define _RM_BUSYTASK_

#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma fixedparams (x_bu_get, x_bu_init)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int _FIXED _FAR x_bu_get(               char       _FAR *busy_ptr );
int _FIXED _FAR x_bu_init(              void );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RM_BUSYTASK_ */


#endif /* _RMAPI_H_ */

