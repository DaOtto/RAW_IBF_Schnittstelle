/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : TASK.H
;   version     : 0020
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Aug 08, 1995
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file contains prototypes and macros for
;                 initialization functions.
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Jan 11, 1995  P.F.  0019  Modification for RMOS V3.11
;   Aug 08, 1995  P.F.  0020  Modification for RMOS V3.12
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _TASK_H_
#define _TASK_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma varparams   ("xinitc", "xinitt", "x_cr_killtsk")
#pragma fixedparams ("x_cr_gettaskid", "x_cr_gettaskparam")
#pragma fixedparams ("x_cr_initenv", "x_cr_setexit")
#if (_ARCHITECTURE_>=386) || defined (i386)
#pragma align (std_struct = 4)
#else
#pragma align (std_struct = 2)
#endif
#endif  /* _ARCHITECTURE_ || CADUL */

#if defined _MSC_VER
           /* ============== Microsoft C is used ============== */
#pragma pack(2)
#endif  /* _MSC_VER */

#if defined __BORLANDC__
           /* =============== Borland C is used =============== */
#pragma option -a
#endif  /* __BORLANDC__ */


struct std_struct
        {
        int             stdin_dev;
        int             stdin_unit;
        int             stdout_dev;
        int             stdout_unit;
        int             stderr_dev;
        int             stderr_unit;
        char            *stdin_fname;
#if RMFLAT
        unsigned short  stdin_fill;     /* Fill word, selector not used in flat model */
#endif
        char            *stdout_fname;
#if RMFLAT
        unsigned short  stdout_fill;    /* Fill word, selector not used in flat model */
#endif
        char            *stderr_fname;
#if RMFLAT
        unsigned short  stderr_fill;    /* Fill word, selector not used in flat model */
#endif
        char            *tmp_path;
#if RMFLAT
        unsigned short  tmp_fill;       /* Fill word, selector not used in flat model */
#endif
        };
       
typedef struct std_struct       STDSTRUCT;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int      _VAR   _FAR xinitc            (unsigned int PoolId,
                                               unsigned int Reserved1,
                                               int Reserved2, int Reserved3,
                                               char *TmpPath);
extern int      _VAR   _FAR xinitt            (int stdin_dev, int stdin_unit,
                                               int stdout_dev, int stdout_unit,
                                               int stderr_dev, int stderr_unit,
                                               char *TmpPath);
extern unsigned _FIXED _FAR x_cr_gettaskid    (void);
extern int      _FIXED _FAR x_cr_gettaskparam (unsigned TaskId,
                                               STDSTRUCT *StdData, char **Env);
extern int      _FIXED _FAR x_cr_initenv      (char *Env);
extern int      _VAR   _FAR x_cr_killtsk      (unsigned TaskId);
extern int      _FIXED _FAR x_cr_setexit      (void (_FIXED _FAR *exithandler)(int));

#ifdef __cplusplus
}
#endif /* __cplusplus */


#if defined _MSC_VER
#pragma pack()
#endif

#if defined __BORLANDC__
#pragma option -a.
#endif


/* For compatibility with old versions of RMOS-CRUN */
#define xinitC                  xinitc
#define xinitT                  xinitt
#define x_cr_GetTaskID          x_cr_gettaskid
#define x_cr_InitEnv            x_cr_initenv
#define x_cr_getTaskParam       x_cr_gettaskparam
#define x_cr_SetExit            x_cr_setexit


#endif  /* _TASK_H_ */
