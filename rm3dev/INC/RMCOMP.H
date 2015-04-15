/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : RMCOMP.H
;   version     : 0001
;   contents    : RMOS C/C++ compiler support header file
;   author      : P.F.
;   date        : Aug 08, 1995
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file contains macros to support
;                 different C/C++ compiler
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Aug 08, 1995  P.F.   0001  Original issue
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _RMCOMP_H_
#define _RMCOMP_H_


#if defined CADUL
           /* ======= CADUL C Compiler CC86/386 is used ====== */
#ifndef _ARCHITECTURE_
#if defined i386
#define _ARCHITECTURE_  386
#else
#define _ARCHITECTURE_  86
#endif  /* i386 */
#endif  /* _ARCHITECTURE_ */
#endif  /* CADUL */


#if defined _ARCHITECTURE_ || defined CADUL
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ====== */

#define RMFLAT  0       /* 16Bit/32Bit segmented code */

#ifndef _FIXED
#define _FIXED
#endif

#ifndef _VAR
#define _VAR
#endif

#ifndef _FAR
#if RMFLAT
#define _FAR
#else
#define _FAR    far
#endif
#endif

#ifndef _NEAR
#if RMFLAT
#define _NEAR
#else
#define _NEAR   near
#endif
#endif

#ifndef _DFAR
#define _DFAR
#endif

#ifndef _RMDS
#define _RMDS
#endif

#endif  /* _ARCHITECTURE_ || CADUL */


#if defined _MSC_VER
           /* ============ Microsoft C/C++ is used ============ */

#if defined _WIN32
#define RMFLAT  1       /* 32Bit       flat code      */
#else
#define RMFLAT  0       /* 16Bit/32Bit segmented code */
#endif

#ifndef _FIXED
#if RMFLAT
#define _FIXED  _stdcall
#else
#define _FIXED  _pascal
#endif
#endif

#ifndef _VAR
#define _VAR    _cdecl
#endif

#ifndef _FAR
#if RMFLAT
#define _FAR
#else
#define _FAR    _far
#endif
#endif

#ifndef _NEAR
#if RMFLAT
#define _NEAR
#else
#define _NEAR   _near
#endif
#endif

#ifndef _DFAR
#if RMFLAT
#define _DFAR
#else
#define _DFAR   _far
#endif
#endif

#ifndef _RMDS
#define _RMDS
#endif

#endif  /* _MSC_VER */


#if defined __BORLANDC__
           /* =============== Borland C is used =============== */

#if defined __FLAT__
#define RMFLAT  1       /* 32Bit       flat code      */
#else
#define RMFLAT  0       /* 16Bit/32Bit segmented code */
#endif

#ifndef _FIXED
#define _FIXED  pascal
#endif

#ifndef _VAR
#define _VAR    cdecl
#endif

#ifndef _FAR
#if RMFLAT
#define _FAR
#else
#define _FAR    far
#endif
#endif

#ifndef _NEAR
#if RMFLAT
#define _NEAR
#else
#define _NEAR   near
#endif
#endif

#ifndef _DFAR
#if RMFLAT
#define _DFAR
#else
#define _DFAR   far
#endif
#endif

#ifndef _RMDS
#define _RMDS   __loadds
#endif

#endif  /* __BORLANDC__ */


#endif  /* _RMCOMP_H_ */
