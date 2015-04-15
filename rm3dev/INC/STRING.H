/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : STRING.H
;   version     : 0013
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file supports functions for string
;                 and memory manipulation
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0013  Modification for RMOS2/3 V3.1
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _STRING_H_
#define _STRING_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _STDDEF_H_
#include <stddef.h>
#endif  /* _STDDEF_H_ */


#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams("strcat", "strchr", "strcpy", "strncat", "strncpy")
#pragma fixedparams("strpbrk", "strrchr", "strtok", "strstr", "strerror")
#pragma fixedparams("strlen", "strcmp", "strncmp", "strspn", "strcspn")
#pragma fixedparams("strcoll")
#endif  /* _ARCHITECTURE_ || CADUL */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern char * _FIXED _FAR strcat   (char *s1, const char *s2);
extern char * _FIXED _FAR strchr   (const char *s, int c);
extern int    _FIXED _FAR strcmp   (const char *s1, const char *s2);
extern int    _FIXED _FAR strcoll  (const char *s1, const char *s2);
extern char * _FIXED _FAR strcpy   (char *s1, const char *s2);
extern size_t _FIXED _FAR strcspn  (const char *s1, const char *s2);
extern char * _FIXED _FAR strerror (int errnum);
extern size_t _FIXED _FAR strlen   (const char *s);
extern char * _FIXED _FAR strncat  (char *s1, const char *s2, size_t n);
extern int    _FIXED _FAR strncmp  (const char *s1, const char *s2, size_t n);
extern char * _FIXED _FAR strncpy  (char *s1, const char *s2, size_t n);
extern char * _FIXED _FAR strpbrk  (const char *s1, const char *s2);
extern char * _FIXED _FAR strrchr  (const char *s, int c);
extern size_t _FIXED _FAR strspn   (const char *s1, const char *s2);
extern char * _FIXED _FAR strstr   (const char *s1, const char *s2);
extern char * _FIXED _FAR strtok   (char *s1, const char *s2);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#ifndef _MEMORY_H_
#include <memory.h>
#endif /* _MEMORY_H_ */

/*****************************************************************************
 *                       Compiler built-in functions                         *
 *****************************************************************************/
#if defined _STRING_H_BUILTIN_
#if defined(_ARCHITECTURE_) && !defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
#pragma _builtin_("_strcpy_"==71)
char *_strcpy_(char*, const char*);
#define strcpy(x,y)  _strcpy_(x,y)

#endif  /* _ARCHITECTURE_ && !CADUL */
#endif  /* _STRING_H_BUILTIN_ */


#endif  /* _STRING_H_ */
