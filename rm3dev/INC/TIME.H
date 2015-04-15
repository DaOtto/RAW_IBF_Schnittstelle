/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : TIME.H
;   version     : 0013
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file contains various macros and
;                 declarations used in the time routines (e.g.
;                 gmtime, localtime).
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0013  Modification for RMOS2/3 V3.1
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _TIME_H_
#define _TIME_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _STDDEF_H_
#include <stddef.h>
#endif  /* _STDDEF_H_ */


#define YEARBOT       1970                      /* The time routines return
                                                   the number of seconds elapsed
                                                   since 00:00:00 Jan. 1, 1970 
                                                   GMT, which is referred to in
                                                   the source as BOT (beginning
                                                   of time) */
#define SECSPERMIN    60L                       /* seconds in a minute */
#define SECSPERHR     (60L * SECSPERMIN)        /* seconds in an hour */
#define SECSPERDAY    (24L * SECSPERHR)         /* seconds in a day */
#define DAYSPERBLK    (365L + 365L + 366L + 365L)/* days in a block -- a block
                                                   is a set of 4 consecutive
                                                   years in which the 3rd is
                                                   a leap year (e.g. 1970, 1971,
                                                   1972, 1973) */
#define SECSPERBLK    (DAYSPERBLK * SECSPERDAY) /* seconds in a block */

#define DAYOFWKBOT    4                         /* BOT was on a Thursday */


#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams ("gmtime", "localtime", "ctime")
#pragma fixedparams ("asctime", "tzset", "difftime")
#pragma fixedparams ("mktime", "strftime", "x_cr_time")
#pragma fixedparams ("clock" ,"sleep")
#pragma fixedparams ("_xdaylight", "_xtimezone", "_xtzname" )
#pragma fixedparams ("x_cr_svc_time", "x_cr_svc_stime")
#if (_ARCHITECTURE_>=386) || defined (i386)
#pragma align (tm = 4)
#else
#pragma align (tm = 2)
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


/* The following structure is filled by the routines gmtime and localtime. */
struct tm {
  int tm_sec;   /* no. of seconds past the minute (0-59) */
  int tm_min;   /* no. of minutes past the hour (0-59) */
  int tm_hour;  /* the hour (0-23) */
  int tm_mday;  /* day of month (1-31) */
  int tm_mon;   /* month of year (0-11) */
  int tm_year;  /* current year - 1900 */
  int tm_wday;  /* day of week (0-6, Sunday = 0) */
  int tm_yday;  /* day of year (0-365) */
  int tm_isdst; /* daylight savings time flag (non-zero if daylight savings
                   time is currently in effect; 0 otherwise */
};

typedef long time_t;    /* type to represent number of seconds since BOT */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern char      * _FIXED _FAR asctime    (const struct tm *tm);
extern long        _FIXED _FAR clock      (void);
extern char      * _FIXED _FAR ctime      (time_t *sincebot);
extern double      _FIXED _FAR difftime   (time_t t1, time_t t0);
extern struct tm * _FIXED _FAR gmtime     (time_t *sincebot);
extern struct tm * _FIXED _FAR localtime  (time_t *sincebot);
extern time_t      _FIXED _FAR mktime     (struct tm *tm);
extern unsigned    _FIXED _FAR sleep      (unsigned secs);
extern size_t      _FIXED _FAR strftime   (char *s, size_t maxsize, char *fmtstr, struct tm *tm);
extern void        _FIXED _FAR tzset      (void);

extern time_t      _FIXED _FAR x_cr_time  (time_t *ptr);
extern int       * _FIXED _FAR _xdaylight (void);
extern long      * _FIXED _FAR _xtimezone (void);
extern char     ** _FIXED _FAR _xtzname   (void);

extern void        _FIXED _FAR x_cr_svc_time  (int fmt_type, void *timeInfo, unsigned int *sts);
extern void        _FIXED _FAR x_cr_svc_stime (int fmt_type, void *timeInfo, unsigned int *sts);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#define daylight ( *_xdaylight() )
#define timezone ( *_xtimezone() )
#define tzname   (  _xtzname()   )

#ifndef  _TIME_
#define _TIME_ 1
#define time    x_cr_time
#endif


#define CLK_TCK  100   /* number of clock ticks per second */


#if defined _MSC_VER
#pragma pack()
#endif

#if defined __BORLANDC__
#pragma option -a.
#endif


#endif  /* _TIME_H_ */
