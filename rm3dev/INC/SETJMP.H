/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : SETJMP.H
;   version     : 0011a
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 06, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file supports the functions setjmp
;                 and longjmp
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0011  Modification for RMOS2/3 V3.1
;   Dec 06, 1996  P.F.  0011a Error corrected at alignment of jmp_buf
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _SETJMP_H_
#define _SETJMP_H_

#ifndef _PROT_H_
#include <prot.h>
#endif  /* _PROT_H_ */
#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams ( "setjmp", "longjmp")
#if (_ARCHITECTURE_>=386) || defined (i386)
#pragma align (_jmp_buf = 4)
#else
#pragma align (_jmp_buf = 2)
#endif
#endif  /* _ARCHITECTURE_ || CADUL */

#if defined _MSC_VER
           /* ============== Microsoft C is used ============== */
#pragma pack(2)
#endif  /* _MSC_VER */

#if defined __BORLANDC__
           /* =============== Borland C is used =============== */
#pragma option -a
#endif  /* __BORLANDC__ */


#if RM3
/* --- For use with RMOS3 --- */
typedef struct _jmp_buf {
    unsigned    esp;
    unsigned    ss;
    unsigned    eflag;
    unsigned    cs;
    unsigned    eip;
    unsigned    ebp;
#if RMFLAT
/* --- For use with flat RMOS3 --- */
    unsigned    fs;
    unsigned    gs;
#endif
    unsigned    edi;
    unsigned    es;
    unsigned    esi;
    unsigned    ds;
#if RMFLAT
/* --- For use with flat RMOS3 --- */
    unsigned    reserved[4];
#endif
}   jmp_buf[1];
#else
/* --- For use with RMOS2 --- */
typedef struct _jmp_buf {
    unsigned    sp;
    unsigned    ss;
    unsigned    flag;
    unsigned    cs;
    unsigned    ip;
    unsigned    bp;
    unsigned    di;
    unsigned    es;
    unsigned    si;
    unsigned    ds;
}   jmp_buf[1];
#endif


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern void _FIXED _FAR longjmp (jmp_buf env, int val);
extern int  _FIXED _FAR setjmp  (jmp_buf env);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#if defined _MSC_VER
#pragma pack()
#endif

#if defined __BORLANDC__
#pragma option -a.
#endif

#endif  /* _SETJMP_H_ */

