/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : MACRO.H  
;   version     : 0007
;   contents    : Macro definitions
;   author      : W.S.
;   date        : Dec 04, 1992
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Macro definitions for use in C
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 04, 1992  W.S.  0002  New Header added
;   May 10, 1993  J.R.  0003  Modifications for use with BORLAND C++
;   Jul 14, 1994  P.F.  0004  Include the header file typedefs.h
;   Nov 21, 1994  P.F.  0005  Added brackets to FP_OFF and FP_SEG macros
;   Jan 10, 1995  P.F.  0006  Now we use standard types, typedefs.h removed
;   Jan 10, 1996  J.R.  0007  Avoid collisions with DOS.H regarding FP_OFF,
;                             FP_SEG and MK_FP.
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _MACRO_H_
#define _MACRO_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */


#if !RMFLAT

	 /* Macros for far pointer not available in flat memory model */

#ifndef __BORLANDC__

#ifndef FP_OFF
#define FP_OFF(p) (((unsigned int *) (&(p)))[0] )
#if RM3
#define FP_SEG(p) (((unsigned short *) (&(p)))[2] )
#else
#define FP_SEG(p) (((unsigned short *) (&(p)))[1] )
#endif
#endif /* FP_OFF */

#else  /* __BORLANDC__ */

#ifdef __cplusplus
#ifndef FP_OFF
	 inline unsigned FP_OFF(void _FAR *fptr)
	 {
		  return ((unsigned)(fptr)) ;
	 }
#endif /* !FP_OFF */
#ifndef FP_SEG
	 inline unsigned FP_SEG(void _FAR *fptr)
	 {
		  return ((unsigned)(void _seg *)(void _FAR *)(fptr)) ;
	 }
#endif /* !FP_SEG */
#ifndef MK_FP
	 inline void _FAR *MK_FP(unsigned seg, unsigned off)
	 {
		  return ((void _seg *)(seg) + (void _NEAR *)(off)) ;
	 }
#endif /* !MK_FP */
	 inline void _FAR *buildptr(unsigned seg, void _NEAR *off)
	 {
		  return (void _FAR *)((void _seg *)(seg) + (void _NEAR *)(off)) ;
	 }
#else /* !__cplusplus */
#ifndef FP_OFF
#define FP_OFF(fptr)            ((unsigned)(fptr))
#define FP_SEG(fptr)            ((unsigned)(void _seg *)(void _FAR *)(fptr))
#define MK_FP(seg, off)         ((void _seg *)(seg) + (void _NEAR *)(off))
#define buildptr(seg, off)      MK_FP(seg, off)
#endif /* FP_OFF */
#endif /* __cplusplus */

#endif /* __BORLANDC__ */

#endif /* !RMFLAT */


#define HIGH(x)   (((unsigned char *) (&(x)))[1])
#define LOW(x)    (((unsigned char *) (&(x)))[0])

#define W32HIG(x) (((unsigned short *) (&(x)))[1])
#define W32LOW(x) (((unsigned short *) (&(x)))[0])


#endif /* _MACRO_H_ */
