/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : DIRECT.H
;   version     : 0015
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : May 10, 1995
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This is the header file for directory functions
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0014  Modification for RMOS2/3 V3.1
;   May 10, 1995  P.F.  0015  Error corrected at prototype for mkdir and rmdir
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _DIRECT_H_
#define _DIRECT_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams("chdir", "getcwd")
#pragma varparams  ("mkdir", "rmdir")
#endif  /* _ARCHITECTURE_ || CADUL */



#define CWD_MAX     128     /* Max. number of characters in the current */
                            /* working directory                        */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int    _FIXED _FAR chdir  (char *path);
extern char * _FIXED _FAR getcwd (char *buffer, int size);
extern int    _VAR   _FAR mkdir  (char *dirname);
extern int    _VAR   _FAR rmdir  (char *dirname);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* _DIRECT_H_ */
