/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : FCNTL.H
;   version     : 0012
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Mar 04, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Constants for file I/O
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0011  Modification for RMOS2/3 V3.1
;   Mar 04, 1996  P.F.  0012  Added new mode O_CLOSEONEXIT for open
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _FCNTL_H_
#define _FCNTL_H_

/*
 * Flag values accessible to open(2) and fcntl(2)
 * (The first three values can only be set by open.)
 */
 
#define O_RDONLY    000         /* open for reading */
#define O_WRONLY    001         /* open for writing */
#define O_RDWR      002         /* open for read & write */
#define O_NDELAY    FNDELAY     /* non-blocking open */
                                /* really non-blocking I/O for fcntl */
#define O_APPEND    FAPPEND     /* append on each write */
#define O_CREAT     FCREAT      /* open with file create */
#define O_TRUNC     FTRUNC      /* open with truncation */
#define O_EXCL      FEXCL       /* error on create if file exists */

/* O_TEXT files have <cr><lf> sequences translated to <lf> on read()'s,
** and <lf> sequences translated to <cr><lf> on write()'s
*/

#define O_TEXT      04000       /* file mode is text (translated) */
#define O_BINARY    00000       /* file mode is binary (untranslated) */

/* O_CLOSEONEXIT files are close on task exit */
/* default is no close on task exit           */

#define O_CLOSEONEXIT       010000  /* close file on task exit       */
#define O_NOCLOSEONEXIT     000000  /* don't close file on task exit */


#ifndef F_DUPFD
/* fcntl(2) requests */
#define F_DUPFD 0   /* Duplicate fildes */
#define F_GETFD 1   /* Get fildes flags */
#define F_SETFD 2   /* Set fildes flags */
#define F_GETFL 3   /* Get file flags */
#define F_SETFL 4   /* Set file flags */
#define F_GETOWN 5  /* Get owner */
#define F_SETOWN 6  /* Set owner */
/* flags for F_GETFL, F_SETFL  */
#define FNDELAY     00004       /* non-blocking reads */
#define FAPPEND     00010       /* append on each write */
#define FASYNC      00100       /* signal pgrp when data ready */
#define FCREAT      00400       /* create if nonexistant */
#define FTRUNC      01000       /* truncate to zero length */
#define FEXCL       02000       /* error if already created */
#endif /* F_DUPFD */

#endif /* _FCNTL_H_ */
