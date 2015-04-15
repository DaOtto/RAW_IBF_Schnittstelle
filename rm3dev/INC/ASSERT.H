/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : ASSERT.H
;   version     : 0010
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file supports the "assert" diagnostic.
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0010  Modification for RMOS2/3 V3.1
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _ASSERT_H_
#define _ASSERT_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#ifdef NDEBUG

/* Don't expand "assert" if user indicated "no debug" */
#define assert(EXPR)

#else

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
#pragma fixedparams("_fassrt")
#endif  /* _ARCHITECTURE_ || CADUL */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern void _FIXED _FAR _fassrt(char *expr, char *filename, int lineno);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#define assert(EXPR)  if (!(EXPR)) _fassrt(#EXPR,__FILE__,__LINE__)

#endif  /* NDEBUG */

#endif  /* _ASSERT_H_ */
