/*--FILE HEADER---(set tabulator to 8)----------------------------------------
;
;   filename    : RC201.H
;   version     : 0004
;   contents    : Initialize Aspc2 driver and units for BSP-COM201
;   author      : G.H./T.V.
;   date        : Aug 23, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT---------------------------------------------
;
;   function    : Initialize Aspc2 driver and units for BSP-COM201
;
;   RMOS3
;
;---END OF FILE HEADER--------------------------------------------------------
;
;---MODIFICATION HEADER-------------------------------------------------------
;
;   Feb 22, 1996  G.H.  0001    Original issue
;   Apr 19, 1996  G.H.  0002    driver catalog string and port included
;   Jun 12, 1996  G.H.  0003    alternative library support added
;   Aug 23, 1996  G.H.  0004    RcCom201InitUnit(): parameter added
;
;---END OF MODIFICATION HEADER----------------------------------------------*/


#ifndef __RC201_H__
  #define __RC201_H__

  #ifndef _RMCOMP_H_
    #include <rmcomp.h>
  #endif
  #ifndef _TYPEDEFS_H_
    #include <typedefs.h>
  #endif

  #if (!defined(RM3)) || (!defined(PROT))
    #error"Invalid operating system, for RMOS3 only"
  #endif 

  #if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
    #pragma fixedparams("RcCom201Init", "RcCom201InitUnit")
    #pragma fixedparams("RcCom201Init1", "RcCom201InitUnit1")
    #pragma fixedparams("RcCom201Init2", "RcCom201InitUnit2")

    #pragma align(_Aspc2DrvPortStruct=1)
  #endif

  #if defined _MSC_VER
    #pragma pack(1)         /* set all to byte alignment */
  #endif

  #ifdef __BORLANDC__
    #pragma option -a-      /* set all to byte alignment */
  #endif

  /***** catalog string for RmIO driver ************************************/

  #define ASPC2DRV_CATSTR  "Dp"                         /* do not change ! */
  #define ASPC2DRV_CATSTR1 ASPC2DRV_CATSTR"1"             /* alternative 1 */
  #define ASPC2DRV_CATSTR2 ASPC2DRV_CATSTR"2"             /* alternative 2 */

  extern const char Aspc2DrvCatString[];                /* global resource */

  /***** UCD port **********************************************************/

  typedef struct _Aspc2DrvPortStruct {                  /* do not change ! */
    WORD32 PhysDPRAMStart;
    WORD32 PhysDPRAMLen;
    WORD32 PhysRegisterStart;
    WORD32 PhysRegisterLen;
    BYTE   Irq;
  } Aspc2DrvPortStruct;
  
  /***** interface *********************************************************/

  extern int _FIXED _FAR RcCom201Init(void);      
  extern int _FIXED _FAR RcCom201InitUnit(unsigned short Irq,
                                          unsigned long PhysMem, 
                                          unsigned long PhysReg); 
  extern int _FIXED _FAR RcCom201Init1(void);             /* alternative 1 */
  extern int _FIXED _FAR RcCom201InitUnit1(unsigned short Irq,
                                          unsigned long PhysMem, 
                                          unsigned long PhysReg); 
  extern int _FIXED _FAR RcCom201Init2(void);             /* alternative 2 */
  extern int _FIXED _FAR RcCom201InitUnit2(unsigned short Irq,
                                          unsigned long PhysMem, 
                                          unsigned long PhysReg); 

  #if defined _MSC_VER
    #pragma pack()         /* reset alignment to default */
  #endif

  #ifdef __BORLANDC__
    #pragma option -a.     /* reset alignment to default */
  #endif

#endif
