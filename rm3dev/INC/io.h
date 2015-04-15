/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : IO.H
;   version     : 0014
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 07, 1995
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file supports some additional
;                 RMOS specific I/O functions
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0013  Modification for RMOS2/3 V3.1
;   Dec 07, 1995  P.F.  0014  Modification for RMOS3 V3.12
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _IO_H_
#define _IO_H_

#ifndef _RMCOMP_H_
#include "rmcomp.h"
#endif  /* _RMCOMP_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams ("read", "duread", "write", "access")
#pragma fixedparams ("duwrite", "unlink", "lseek", "close")
#pragma fixedparams ("mount", "dismount", "remap")
#pragma fixedparams ("x_cr_getskhandle", "x_cr_allocskhandle")
#pragma varparams ("open")
#pragma varparams ("search", "checkpoint", "getvolumestatus")
#pragma varparams ("createvib", "changevib", "efsuse", "efsstop")
#pragma varparams ("chmod")
#pragma varparams ("inhibitabort")
#endif  /* _ARCHITECTURE_ || CADUL */


#ifndef _STDDEF_H_
#include <stddef.h>
#endif  /* _STDDEF_H_ */
#ifndef _HSFS_H_
#include <hsfs.h>
#endif  /* _HSFS_H_ */
#ifndef _EFS_H_
#include <efs.h>
#endif  /* _EFS_H_ */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int    _FIXED _FAR access     (const char *filename, int amode);
extern int    _VAR   _FAR changevib  (char *volume, VOL_DATA *newvib);
extern int    _VAR   _FAR checkpoint (int handle);
extern int    _VAR   _FAR chmod      (const char *filename, int pmode);
extern int    _FIXED _FAR close      (int handle);
extern int    _VAR   _FAR createvib  (VOL_DATA *newvib, int poolid);
extern int    _FIXED _FAR dismount   (const char *volume_name);
extern size_t _FIXED _FAR duwrite    (int device, int unit, const void *buffer,
                                      size_t nbytes);
extern size_t _FIXED _FAR duread     (int device, int unit, void *buf,
                                      size_t nsize);
extern int    _VAR   _FAR efsstop    (char *volume);
extern int    _VAR   _FAR efsuse     (char *volume, char *rvolume,
                                      efs_addr *naddr, char *nname);
extern int    _VAR   _FAR getvolumestatus (char *volume, VOL_DATA *volvib,
                                           unsigned long *freeblocks,
                                           unsigned *openfiles,
                                           unsigned *writeerrors);
extern int    _VAR   _FAR inhibitabort    (int mode);
extern long   _FIXED _FAR lseek      (int handle, long offset, int ptofref);
extern int    _FIXED _FAR mount      (const char *volume_name, int format);
extern int    _VAR   _FAR open       (const char *pathname, int access, ... );
extern size_t _FIXED _FAR read       (int handle, void *buf, size_t nbytes);
extern int    _FIXED _FAR remap      (const char *volume_name, int format);
extern int    _VAR   _FAR search     (int *record, char *string,
                                      DIR_ENTRY *direntry);
extern int    _FIXED _FAR unlink     (const char *filename);
extern size_t _FIXED _FAR write      (int handle, const void *buffer,
                                      size_t nbytes);

extern int    _FIXED _FAR x_cr_getskhandle   (void);
extern int    _FIXED _FAR x_cr_allocskhandle (size_t scb_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#define S_IWRITE    0x1     /* open: permission to write */
#define S_IREAD     0x2     /* open: permission to read */

#ifndef _FCNTL_H_
#include <fcntl.h>
#endif  /* _FCNTL_H_ */


/* For compatibility with old versions of RMOS-CRUN */
#define x_cr_GetSKHandle        x_cr_getskhandle


#endif  /* _IO_H_ */

