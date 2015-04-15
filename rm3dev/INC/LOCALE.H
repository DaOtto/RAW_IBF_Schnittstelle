/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : LOCALE.H
;   version     : 0011
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Some definitions for the function setlocale().
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0010  Modification for RMOS2/3 V3.1
;   Sep  4, 2001  B.N.  0011  Modification for C++
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _LOCALE_H_
#define _LOCALE_H_                         

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams ( "setlocale" )
#if (i8086)
#pragma noalign (lconv)
#else
#pragma align (lconv)
#endif
#endif  /* _ARCHITECTURE_ || CADUL */


#define LC_ALL        1
#define LC_COLLATE    2
#define LC_CTYPE      3
#define LC_NUMERIC    4
#define LC_TIME       5
#define LC_UPPERLIMIT 6  /* Not a category -- must be the last in this list */


#ifdef __cplusplus
#ifndef __STDC__
#define __STDC__ 1
#endif
extern "C" {
#endif

#ifndef     _T_LCONV
#define     _T_LCONV  1
struct lconv {
    char *decimal_point;        /* "." */
    char *thousands_sep;        /* "" */
    char *grouping;             /* "" */
    char *int_curr_symbol;      /* "" */
    char *currency_symbol;      /* "" */
    char *mon_decimal_point;    /* "" */
    char *mon_thousands_sep;    /* "" */
    char *mon_grouping;         /* "" */
    char *positive_sign;        /* "" */
    char *negative_sign;        /* "" */
    char int_frac_digits;       /* CHAR_MAX */
    char frac_digits;           /* CHAR_MAX */
    char p_cs_precedes;         /* CHAR_MAX */
    char p_sep_by_space;        /* CHAR_MAX */
    char n_cs_precedes;         /* CHAR_MAX */
    char n_sep_by_space;        /* CHAR_MAX */
    char p_sign_posn;           /* CHAR_MAX */
    char n_sign_posn;           /* CHAR_MAX */
};
#endif

#if 0 /* CADUL defines are different to RMOS defines */
#define LC_ALL              (LC_COLLATE|LC_CTYPE|LC_MONETARY|LC_NUMERIC|LC_TIME)
#define LC_COLLATE          (1<<0)
#define LC_CTYPE            (1<<1)
#define LC_MONETARY         (1<<2)
#define LC_NUMERIC          (1<<3)
#define LC_TIME             (1<<4)
#endif

#if	!m68000

#ifdef	__STDC__ 
#if	!__PLM__
#if	!i8086
#ifdef  __VARPARAMS__
#define __FIXEDPARAMS__  (!__VARPARAMS__)
#else
#define __FIXEDPARAMS__  1 
#endif
#endif	/* i8086 */
#endif	/* !__PLM__ */
#endif	/* __STDC__ */ 

#ifndef	__FIXEDPARAMS__
#define __FIXEDPARAMS__  0 
#endif

#if	__FIXEDPARAMS__
#pragma fixedparams(setlocale,localeconv)
#else
#pragma varparams(setlocale,localeconv)
#endif

#endif	/* m68000 */

#ifdef __STDC__
extern char * _FIXED _FAR setlocale (int category, const  char *locale);
struct lconv *localeconv (void); 
#else
char *setlocale ();
struct lconv *localeconv ();
#endif

#ifndef NULL
#ifdef	__cplusplus
#define	NULL	0
#else
#if     __STDC__
#define NULL    (void *)0
#else
#define NULL    (char *)0
#endif
#endif
#endif

#ifndef	size_t
#ifndef	_T_SIZE
#define	_T_SIZE 1
#if	_SIZE_T_32_
typedef	unsigned long size_t;
#else
typedef unsigned int size_t;		/* Lengths */
#endif
#endif
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* _LOCALE_H_ */
