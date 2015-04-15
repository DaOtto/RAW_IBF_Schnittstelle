/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : MEMORY.H
;   version     : 0004
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file supports functions memory manipulation
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0004  Modification for RMOS2/3 V3.1
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _MEMORY_H_
#define _MEMORY_H_


#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _STDDEF_H_
#include <stddef.h>
#endif  /* _STDDEF_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams("memcmp", "memset", "memchr", "memcpy", "memccpy")
#pragma fixedparams("memmove")
#endif  /* _ARCHITECTURE_ || CADUL */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern void * _FIXED _FAR memccpy (void *s1, const void *s2, int c, size_t n);
extern void * _FIXED _FAR memchr  (const void *s, int c, size_t n);
extern int    _FIXED _FAR memcmp  (const void *s1, const void *s2, size_t n);
extern void * _FIXED _FAR memcpy  (void *s1, const void *s2, size_t n);
extern void * _FIXED _FAR memmove (void *dest, const void *s2, size_t n);
extern void * _FIXED _FAR memset  (void *s, int c, size_t n);

#ifdef __cplusplus
}
#endif /* __cplusplus */


/*****************************************************************************
 *                       Compiler built-in functions                         *
 *****************************************************************************/
#if defined _MEMORY_H_BUILTIN_
#if defined(_ARCHITECTURE_) && !defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
#pragma _builtin_("_memcpy_"==64)
void *_memcpy_(void*, const void*, size_t);
#define memcpy(x,y,z) _memcpy_(x,y,z)

#pragma _builtin_("_memset_"==65)
void *_memset_(void*, int, size_t);
#define memset(x,y,z) _memset_(x,y,z)

#endif  /* _ARCHITECTURE_ && !CADUL */
#endif  /* _MEMORY_H_BUILTIN_ */


#endif  /* _MEMORY_H_ */
