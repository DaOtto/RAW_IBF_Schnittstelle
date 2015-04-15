/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : ERRNO.H
;   version     : 0011
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file contains the  macro definitions
;                 for the valid values of the external variables
;                 "errno" and "errno2".  It also contains external
;                 declarations for the array of error messages and
;                 the number of error messages.
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0011  Modification for RMOS2/3 V3.1
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _ERRNO_H_
#define _ERRNO_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams("_xerrno", "_xerrno2" )
#pragma fixedparams("_xsys_errlist", "_xsys_nerr")
#endif  /* _ARCHITECTURE_ || CADUL */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int  *  _FIXED _FAR _xerrno       (void);
extern int  *  _FIXED _FAR _xerrno2      (void);
extern char ** _FIXED _FAR _xsys_errlist (void);
extern int  *  _FIXED _FAR _xsys_nerr    (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#define errno       (*_xerrno())
#define errno2      (*_xerrno2()) 
#define sys_errlist (_xsys_errlist())
#define sys_nerr    (*_xsys_nerr())


/*************************************************************************/
/*
 * Universal Errors may occur on all system calls.
 */

#define EAGAIN           1      /* temporary resource exhaustion - try again */
#define EBUSY            2      /* only one process per job can use interface; *
                                 * attempt to delete a non-empty directory */ 
#define EFAULT           3      /* fault in accessing call arguments */
#define EINSUBSYS        4      /* null subsystem id for procedure */
#define EINVAL           5      /* invalid argument */
#define ELIFETIME        6      /* local AD being copied to a global object */
#define ENATIVE          7      /* native exception - check message stack */
#define ENORES           8      /* resource exhausted - check message stack */
#define EPAGER           9      /* insufficient page rights */
#define EREPR           10      /* insufficient representation rights */
#define ETYPEMIS        11      /* type of object incorrect for operation */
#define ETYPER          12      /* insufficient type rights */
#define EXABORT         13      /* transaction has already been aborted */
#define EXNOACT         14      /* transaction is not active */
#define EXNOCOMM        15      /* transaction could not be committed */
#define EXTIMECONF      16      /* transaction time-stamp conflict */


/*
 * Operation-specific error codes. A gap is left between universal errors and
 * operation-specific errors to take care of future additions to universal
 * errors.
 */

#define E2BIG           26      /* exceeded operation/system-defined limit */
#define EACCES          27      /* insuff. rights or object does not exist */
#define EBADF           28      /* invalid open device descriptor */
#define ECHILD          29      /* no children to wait for */
#define EDEADLK         30      /* deadlock prevented */
#define EDOM            31      /* invalid argument for math function */
#define EEXIST          32      /* object already exists */
#define EFBIG           33      /* semaphore not in semaphore-array*/
#define EIDRM           34      /* IPC ID removed */
#define EINTR           35      /* signal or event caught during call */
#define EIO             36      /* physical IO error */
#define EMFILE          37      /* too many open device descriptors */
#define ENODEV          38      /* operation not supported */
#define ENOENT          39      /* IPC ID does not exist */
#define ENOEXEC         40      /* object has no EXECUTE property */
#define ENOLCK          41      /* no more file locks */
#define ENOMEM          42      /* insufficient memory */
#define ENOMSG          43      /* no such message on queue */
#define ENOSPC          44      /* insufficient space on device */
#define ENOTDIR         45      /* not a directory */
#define ENOTTY          46      /* not a tty */
#define ENXIO           47      /* device or request invalid */
#define EPERM           48      /* caller has insufficient rights */
#define ERANGE          49      /* result out of range */
#define ESRCH           50      /* no such job */
#define ENOTFOUND       51      /* object not found */

/*
 * The following errors have the same value as one of the above.
*/

#define EISDIR          ENODEV  /* Operation not supported for directories */
#define ESPIPE          ENODEV  /* Operation not supported for pipe (or fifo) */
#define EPIPE           ENXIO   /* Attempt to write to a pipe (or fifo) whose
                                 * read end is closed */

/*
 * The following error numbers are not raised.
 */

#define    ENOTBLK      255
#define    EXDEV        255
#define    ENFILE       255
#define    ETXTBSY      255
#define    EROFS        255
#define    EMLINK       255


#endif  /* _ERRNO_H_ */
