/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : MALLOC.H
;   version     : 0010
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file supports the memory allocation
;                 functions
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

#ifndef _MALLOC_H_
#define _MALLOC_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _STDDEF_H_
#include <stddef.h>
#endif  /* _STDDEF_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams("malloc", "realloc", "calloc", "free", "x_cr_lmalloc" )
#endif  /* _ARCHITECTURE_ || CADUL */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern void * _FIXED _FAR calloc       (size_t nmemb, size_t size);
extern void   _FIXED _FAR free         (void *ptr);
extern void * _FIXED _FAR malloc       (size_t size);
extern void * _FIXED _FAR realloc      (void *ptr, size_t size);

extern void * _FIXED _FAR x_cr_lmalloc (unsigned long size);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* _MALLOC_H_ */
