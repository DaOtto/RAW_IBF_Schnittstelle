/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : MATH.H
;   version     : 0010
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Function prototypes for floating point functions
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0009  Modification for RMOS2/3 V3.1
;   Sep 18, 2001  B.N.  0010  change exception to mathexception(for c++) 
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _MATH_H_
#define _MATH_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
           /* ======= CADUL C Compiler CC86/386 is used ======= */
#pragma fixedparams("acos", "asin", "atan", "atan2", "ceil", "cos", "cosh")
#pragma fixedparams("exp", "x_fabs", "floor", "fmod", "frexp", "ldexp", "log")
#pragma fixedparams("log10", "modf", "pow", "sin", "sinh", "sqrt", "tan")
#pragma fixedparams("tanh","matherr")
/* x_fabs is only used, if fast math is not selected */
#ifndef FMATH
#define fabs     x_fabs
#endif
#endif  /* _ARCHITECTURE_ || CADUL */

#if defined(_MSC_VER)
           /* ============== Microsoft C is used ============== */
#define acos    x_cf_msc_acos
#define asin    x_cf_msc_asin
#define atan    x_cf_msc_atan
#define atan2   x_cf_msc_atan2
#define ceil    x_cf_msc_ceil
#define cos     x_cf_msc_cos
#define cosh    x_cf_msc_cosh
#define exp     x_cf_msc_exp
#define fabs    x_cf_msc_fabs
#define floor   x_cf_msc_floor
#define fmod    x_cf_msc_fmod
#define frexp   x_cf_msc_frexp
#define ldexp   x_cf_msc_ldexp
#define log     x_cf_msc_log
#define log10   x_cf_msc_log10
#define modf    x_cf_msc_modf
#define pow     x_cf_msc_pow
#define sin     x_cf_msc_sin
#define sinh    x_cf_msc_sinh
#define sqrt    x_cf_msc_sqrt
#define tan     x_cf_msc_tan
#define tanh    x_cf_msc_tanh
#endif  /* _MSC_VER */

#if defined(__BORLANDC__)
           /* =============== Borland C is used =============== */
#define acos    x_cf_bc_acos
#define asin    x_cf_bc_asin
#define atan    x_cf_bc_atan
#define atan2   x_cf_bc_atan2
#define ceil    x_cf_bc_ceil
#define cos     x_cf_bc_cos
#define cosh    x_cf_bc_cosh
#define exp     x_cf_bc_exp
#define fabs    x_cf_bc_fabs
#define floor   x_cf_bc_floor
#define fmod    x_cf_bc_fmod
#define frexp   x_cf_bc_frexp
#define ldexp   x_cf_bc_ldexp
#define log     x_cf_bc_log
#define log10   x_cf_bc_log10
#define modf    x_cf_bc_modf
#define pow     x_cf_bc_pow
#define sin     x_cf_bc_sin
#define sinh    x_cf_bc_sinh
#define sqrt    x_cf_bc_sqrt
#define tan     x_cf_bc_tan
#define tanh    x_cf_bc_tanh
#endif  /* __BORLANDC__ */


#define HUGE_VAL 1.79769313486231571e308

#define DOMAIN      1  /* exception types used in matherr() */
#define SING        2
#define OVERFLOW    3
#define UNDERFLOW   4
#define TLOSS       5
#define PLOSS       6  /* PLOSS is not used in the numeric part of CRUN */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern double _FIXED _FAR acos   (double);
extern double _FIXED _FAR asin   (double);
extern double _FIXED _FAR atan   (double);
extern double _FIXED _FAR atan2  (double, double);
extern double _FIXED _FAR ceil   (double);
extern double _FIXED _FAR cos    (double);
extern double _FIXED _FAR cosh   (double);
extern double _FIXED _FAR exp    (double);
extern double _FIXED _FAR fabs   (double);
extern double _FIXED _FAR floor  (double);
extern double _FIXED _FAR fmod   (double, double);
extern double _FIXED _FAR frexp  (double, int *);
extern double _FIXED _FAR ldexp  (double, int);
extern double _FIXED _FAR log    (double);
extern double _FIXED _FAR log10  (double);
extern double _FIXED _FAR modf   (double, double *);
extern double _FIXED _FAR pow    (double, double);
extern double _FIXED _FAR sin    (double);
extern double _FIXED _FAR sinh   (double);
extern double _FIXED _FAR sqrt   (double);
extern double _FIXED _FAR tan    (double);
extern double _FIXED _FAR tanh   (double);

#ifdef __cplusplus
}
#endif /* __cplusplus */


/* Exception is the exception Structure used in matherr */
#if defined _ARCHITECTURE_
           /* ======= Intel C Compiler iC86/386 is used ======= */
#pragma noalign(mathexception)
#endif
struct mathexception {
  int type;
  char *name;
  double arg1, arg2, retval;
};
int _FIXED matherr(struct mathexception *); /* The library contains only a dummy */



/* ----------------------------------------------------------------- */
/* On 80387 and 486 under RMOS3 we can generate inline code for some */
/* numeric functions                                                 */
/* ----------------------------------------------------------------- */
   
#ifdef FMATH
#if _ARCHITECTURE_ >= 386

#pragma _builtin_("_sqrt_"==54)
double _sqrt_(double);
#define sqrt(x) _sqrt_(x)

#pragma _builtin_("_fabs_"==53)
double _fabs_(double);
#define fabs(x) _fabs_(x)

#pragma _builtin_("_acos_"==60)
double _acos_(double);
#define acos(x) _acos_(x)

#pragma _builtin_("_asin_"==61)
double _asin_(double);
#define asin(x) _asin_(x)

#pragma _builtin_("_atan_"==63)
double _atan_(double);
#define atan(x) _atan_(x)

#pragma _builtin_("_atan2_"==62)
double _atan2_(double,double);
#define atan2(x,y) _atan2_(x,y)

#pragma _builtin_("_cos_"==57)
double _cos_(double);
#define cos(x) _cos_(x)

#pragma _builtin_("_sin_"==58)
double _sin_(double);
#define sin(x) _sin_(x)

#pragma _builtin_("_tan_"==59)
double _tan_(double);
#define tan(x) _tan_(x)

#pragma _builtin_("_log_"==55)
double _log_(double);
#define log(x) _log_(x)

#pragma _builtin_("_log10_"==56)
double _log10_(double);
#define log10(x) _log10_(x)

#endif  /* _ARCHITECTURE_ >= 386 */
#endif  /* FMATH */


#endif /* _MATH_H_ */
