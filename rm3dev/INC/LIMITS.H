/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : LIMITS.H
;   version     : 0010
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file contains some constants for
;                 different types
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

#ifndef _LIMITS_H_
#define _LIMITS_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */


#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#define CHAR_BIT    8
#define SCHAR_MIN   (-128)
#define SCHAR_MAX   127
#define UCHAR_MAX   255u
#if '\xFF' < 0
#define CHAR_MAX    SCHAR_MAX
#define CHAR_MIN    SCHAR_MIN
#else
#define CHAR_MAX    UCHAR_MAX
#define CHAR_MIN    0
#endif
#define SHRT_MIN    (-32768)
#define SHRT_MAX    32767
#define USHRT_MAX   65535u
#define LONG_MIN    (-2147483647l-1)
#define LONG_MAX    2147483647
#define ULONG_MAX   4294967295u

#if (_ARCHITECTURE_>=386) || defined (i386)
/* --- For use with RMOS3 --- */
#define INT_MIN     LONG_MIN
#define INT_MAX     LONG_MAX
#define UINT_MAX    ULONG_MAX
#else
/* --- For use with RMOS2 --- */
#define INT_MIN     SHRT_MIN
#define INT_MAX     SHRT_MAX
#define UINT_MAX    USHRT_MAX
#endif
#endif  /* _ARCHITECTURE_ || CADUL */


#if defined _MSC_VER
           /* ============== Microsoft C is used ============== */
#define CHAR_BIT          8             /* number of bits in a char */
#define SCHAR_MIN       (-127)          /* minimum signed char value */
#define SCHAR_MAX         127           /* maximum signed char value */
#define UCHAR_MAX         0xff          /* maximum unsigned char value */
#ifndef _CHAR_UNSIGNED
#define CHAR_MIN        SCHAR_MIN       /* mimimum char value */
#define CHAR_MAX        SCHAR_MAX       /* maximum char value */
#else
#define CHAR_MIN          0
#define CHAR_MAX        UCHAR_MAX
#endif
#define MB_LEN_MAX        1             /* max. # bytes in multibyte char */
#define SHRT_MIN        (-32767)        /* minimum (signed) short value */
#define SHRT_MAX          32767         /* maximum (signed) short value */
#define USHRT_MAX         0xffff        /* maximum unsigned short value */
#define INT_MIN         (-32767)        /* minimum (signed) int value */
#define INT_MAX           32767         /* maximum (signed) int value */
#define UINT_MAX          0xffff        /* maximum unsigned int value */
#define LONG_MIN        (-2147483647)   /* minimum (signed) long value */
#define LONG_MAX          2147483647    /* maximum (signed) long value */
#define ULONG_MAX         0xffffffff    /* maximum unsigned long value */
#endif  /* _MSC_VER */


#if defined __BORLANDC__
           /* =============== Borland C is used =============== */
#define CHAR_BIT        8               /* number of bits in a char */
#define MB_LEN_MAX      2               /* max. # bytes in multibyte char */

#define SCHAR_MIN     (-128)            /* minimum signed   char value */
#define SCHAR_MAX       127             /* maximum signed   char value */
#define UCHAR_MAX       255             /* maximum unsigned char value */

#if ('\x80' < 0)
#define CHAR_MIN        SCHAR_MIN       /* minimum char value */
#define CHAR_MAX        SCHAR_MAX       /* maximum char value */
#else
#define CHAR_MIN        0
#define CHAR_MAX        UCHAR_MAX
#endif

#define SHRT_MIN      (-32767-1)        /* minimum signed   short value */
#define SHRT_MAX        32767           /* maximum signed   short value */
#define USHRT_MAX       65535U          /* maximum unsigned short value */

#define LONG_MIN      (-2147483647L-1)  /* minimum signed   long value */
#define LONG_MAX        2147483647L     /* maximum signed   long value */
#define ULONG_MAX       4294967295UL    /* maximum unsigned long value */

#if !RMFLAT
#define INT_MIN         SHRT_MIN        /* minimum signed   int value */
#define INT_MAX         SHRT_MAX        /* maximum signed   int value */
#define UINT_MAX        USHRT_MAX       /* maximum unsigned int value */
#else
#define INT_MIN         LONG_MIN
#define INT_MAX         LONG_MAX
#define UINT_MAX        ULONG_MAX
#endif
#endif  /* __BORLANDC__ */

#define	MB_LEN_MAX	2	/* ==sizeof(wchar_t)	*/
				/* maximum number of bytes for */
				/* multibyte characters */


#endif  /* _LIMITS_H_ */
