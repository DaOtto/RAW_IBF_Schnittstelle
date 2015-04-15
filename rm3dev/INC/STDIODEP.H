/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : STDIODEP.H
;   version     : 0010a
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 06, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file should be included in STDIO.H.
;                 It contains host dependent data structures and parameters.
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0010  Modification for RMOS2/3 V3.1
;   Dec 06, 1996  P.F.  0010a Error corrected at alignment of fid_t
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _STDIODEP_H_
#define _STDIODEP_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#define EOF       (-1)  /* value returned to mean end-of -file */
#define OPEN_MAX    20  /* maximum number of streams allowed open per process */
#define BUFSIZ    1024  /* Default stream buffer size */
#define L_ctermid    9  /* Minimum length of buffer for the ctermid function */

/* This macro returns the file descriptor for a stream's underlying file */
#define fileno(p)       (p)->_fid.fildes

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
#if (_ARCHITECTURE_>=386) || defined (i386)
#pragma align (_fid_t  = 4)
#pragma align (_modetb = 4)
#else
#pragma align (_fid_t  = 2)
#pragma align (_modetb = 2)
#endif
#endif  /* _ARCHITECTURE_ || CADUL */

#if defined _MSC_VER
#pragma pack(2)
#endif  /* _MSC_VER */

#if defined __BORLANDC__
#pragma option -a
#endif

/* This typedef contains the system dependent file identification info. */
typedef struct _fid_t {
       int              fildes;     /* file descriptor returned from open system call */
       char             *fname;     /* ptr to name of file */
#if RMFLAT
       unsigned short fname_fill; /* Fill word, selector not used in flat model */
#endif
       } fid_t;

/* This table is used by the open routines to map user level
   open modes to os level open modes. */
struct _modetb {
       int              sysflag;   /* bit string of "system call" open flags */
       char             *usermode; /* ptr to open mode char string passed to fopen
                                      by user (e.g. "r", "w", "a", "r+", "w+", "a+") */
#if RMFLAT
       unsigned short   umode_fill; /* Fill word, selector not used in flat model */
#endif
       int              strmflag;  /* bit string of "stream" open flags kept in the
                                     _flag field of a FILE structure */
       };

#if defined _MSC_VER
#pragma pack()
#endif

#if defined __BORLANDC__
#pragma option -a.
#endif

/* This typedef is used to describe a file position.  In the current
   implementation (UNIX), we simply use a long int representing the byte
   offset from the start of the file. */
typedef long fpos_t;

#endif /* _STDIODEP_H_ */
