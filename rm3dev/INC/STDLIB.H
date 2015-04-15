/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : STDLIB.H
;   version     : 0014a
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 06, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file supports some different functions
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0014  Modification for RMOS2/3 V3.1
;   Dec 06, 1996  P.F.  0014a Error corrected at alignment of div_t and ldiv_t
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _STDLIB_H_
#define _STDLIB_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams("atof", "atoi", "atol", "strtod", "strtol")
#pragma fixedparams("strtoul", "rand", "srand", "abort", "atexit")
#pragma fixedparams("exit", "qsort", "x_abs", "div")
#pragma fixedparams("labs", "ldiv", "bsearch" )
#pragma fixedparams("putenv", "getenv")
#if (_ARCHITECTURE_>=386) || defined (i386)
#pragma align (_div_t  = 4)
#pragma align (_ldiv_t = 4)
#else
#pragma align (_div_t  = 2)
#pragma align (_ldiv_t = 2)
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


#ifndef _STDDEF_H_
#include <stddef.h>
#endif  /* _STDDEF_H_ */


#define MB_CUR_MAX    2		/* ==	sizeof(wchar_t) */
#define RAND_MAX        32767

#define EXIT_SUCCESS  0
#define EXIT_FAILURE  1


typedef struct _div_t  { int quot; /* quotient */
                         int rem;  /* remainder */
                       } div_t;
typedef struct _ldiv_t { long quot; /* quotient */
                         long rem;  /* remainder */
                       } ldiv_t;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern void          _FIXED _FAR abort   (void);
extern int           _FIXED _FAR atexit  (void (_FIXED _FAR * func) (void));
extern double        _FIXED _FAR atof    (const char *nptr);
extern int           _FIXED _FAR atoi    (const char *nptr);
extern long          _FIXED _FAR atol    (const char *nptr);
extern void *        _FIXED _FAR bsearch (const void *key, const void *base,
                                          size_t nel, size_t width,
                                          int (_FIXED _FAR *compar)
                                          (const void *p0, const void *p1));
#if defined _ARCHITECTURE_
extern div_t         _FIXED _FAR div     (int numer, int denom);
#else
extern div_t         _FIXED _FAR x_cr_div(int numer, int denom);
#define div     x_cr_div
#endif
extern void          _FIXED _FAR exit    (int status);
extern char *        _FIXED _FAR getenv  (const char *name);
extern long          _FIXED _FAR labs    (long j);
extern ldiv_t        _FIXED _FAR ldiv    (long numer, long denom);
extern int           _FIXED _FAR putenv  (const char *name);
extern void          _FIXED _FAR qsort   (void *base, size_t nel, size_t width,
                                          int (_FIXED _FAR *compar)
                                          (const void *p0, const void *p1));
extern int           _FIXED _FAR rand    (void);
extern void          _FIXED _FAR srand   (unsigned int seed);
extern double        _FIXED _FAR strtod  (const char *nptr, char **endptr);
extern long          _FIXED _FAR strtol  (const char *nptr, char **endptr, int base);
extern unsigned long _FIXED _FAR strtoul (const char *nptr, char **endptr, int base);
extern int           _FIXED _FAR x_abs   (int j);
#define abs     x_abs

#ifdef __cplusplus
}
#endif /* __cplusplus */



#if defined _MSC_VER
#pragma pack()
#endif

#if defined __BORLANDC__
#pragma option -a.
#endif

#ifndef _MALLOC_H_
#include <malloc.h>
#endif  /* _MALLOC_H_ */

#endif  /* _STDLIB_H_ */
