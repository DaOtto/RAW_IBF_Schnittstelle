/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : STDARG.H
;   version     : 0008
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Macros and types for variable argument list to a
;                 function for use with RMOS-CRUN
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0008  Modification for RMOS2/3 V3.1
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _STDARG_H_
#define _STDARG_H_

#ifndef _PROT_H_
#include <prot.h>
#endif  /* _PROT_H_ */
#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#ifndef _va_list
#define _va_list
typedef char *va_list;
#endif

#if RM3
/* --- For use with RMOS3 --- */
#define _sizeof_param(type)  ((sizeof(type)+sizeof(int)-1) & (~(sizeof(int)-1)))
#define va_start(ap,paramn) (ap=((char *)&(paramn)+_sizeof_param(paramn)))
#define va_arg(ap,type)     (*((type *)((ap+=_sizeof_param(type))-_sizeof_param(type))))
#define va_end(ap)
#else
/* --- For use with RMOS2 --- */
#define va_start(ap, paramn) (ap=((char *)&(paramn)+sizeof(paramn)))
#define va_arg(ap, type)     (*((type *)(ap+=sizeof(type))-1)) 
#define va_end(ap)
#endif

#endif  /* _STDARG_H_ */
