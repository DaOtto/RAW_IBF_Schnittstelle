/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : STDDEF.H
;   version     : 0013
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Standard definitions
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0012  Modification for RMOS2/3 V3.1
;   Sep  4, 2001  B.N.  0013  Modifications for C++
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _STDDEF_H_
#define _STDDEF_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#ifdef __cplusplus
#ifndef __STDC__
#define __STDC__ 1
#endif
extern "C" {
#endif

/*
 * Mapping types.
 */
typedef	unsigned amap_t;		/* Auxiliary map */
typedef	unsigned aold_t;		/* Auxiliary map save */
typedef unsigned bmap_t;		/* Buffer map */
typedef unsigned bold_t;		/* Buffer map save */
typedef unsigned cmap_t;		/* Clist map */
typedef unsigned cold_t;		/* Clist map save */
typedef unsigned dmap_t;		/* Driver map */
typedef unsigned dold_t;		/* Driver map save */

/*
 * System types.
 */
typedef	unsigned comp_t;		/* Accounting */
typedef	long	 daddr_t;		/* Disk address */
typedef unsigned dev_t;			/* Device */
typedef unsigned ino_t;			/* Inode number */
typedef long	 paddr_t;		/* Physical memory address */
typedef unsigned saddr_t;		/* Segmenation address */
#if	__INT32__
typedef int 	 sig_t;			/* Signal bits */
#else
typedef long 	 sig_t;			/* Signal bits */
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

/* CR CC68-0116 */
#if	m68000
#if	_SIZE_T_32_ || CADUL_CXX
typedef unsigned long ptrdiff_t;
#else
typedef int	ptrdiff_t;
#endif
#else
/* --- */
typedef int	 ptrdiff_t;		/* Pointer diff. */
#endif

#ifndef     _T_WCHAR
typedef unsigned short    wchar_t; 	/* wide characters      */
#define _T_WCHAR
#endif


#if	__INT32__
typedef unsigned int vaddr_t;
typedef	unsigned int uaddr_t;		/* Universal memory address */
#else
typedef unsigned long vaddr_t;
typedef	unsigned long uaddr_t;		/* Universal memory address */
#endif

#ifndef __cplusplus
#define	offsetof(Type,Id)	(((char*)&(((Type*)NULL)->Id))-((char*)NULL))
#else
#define offsetof(t, memb) 	((size_t)__INTADDR__(&(((t *)0)->memb)))
#endif

/* A value guaranteed not to point to a valid object */
#ifndef NULL
#if defined __BORLANDC__
#  if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#    define NULL    0
#  else
#    define NULL    0L
#  endif
#else /* NOT __BORLANDC__ */
#ifndef __cplusplus
#define NULL    ((void *)0)
#else
#define NULL    0
#endif
#endif /* __BORLANDC__ */
#endif /* NULL */

#ifdef __cplusplus
}
#endif


#endif /* _STDDEF_H_ */
