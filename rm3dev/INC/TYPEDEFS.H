/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : TYPEDEFS.H
;   version     : 0006
;   contents    : Common type definitions 
;   author      : W.S.
;   date        : Dec 4, 1992
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Common type definitions for use in C
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec  4, 1992  W.S.  0003  New Header added
;   Jul  7, 1993  W.S.  0004  Avoid complications in case of multiple use
;   Oct 26, 1994  J.R.  0005  Adjusted to BORLAND C++ V4.0
;   Dec 19, 1994  P.F.  0006  Copied additional type definitions from SVC.H
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */


typedef unsigned char   BYTE;
typedef unsigned short  WORD16;
typedef unsigned int    WORD;
typedef unsigned long   WORD32;

typedef void _FAR *     POINTER;        /* Common pointer */
typedef unsigned int    OFFSET;
typedef unsigned short  SEGMENT;

#if RM3
typedef void *          PTR_VOID;
#else
typedef void _FAR *     PTR_VOID;
#endif


#endif /* _TYPEDEFS_H_ */
