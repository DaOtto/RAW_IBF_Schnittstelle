/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : FLOAT.H
;   version     : 0006a
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 06, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Numerical constants for floating point library
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0006  Modification for RMOS2/3 V3.1
;   Dec 06, 1996  P.F.  0006a Changed comments
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _FLOAT_H_
#define _FLOAT_H_


#define FLT_RADIX        2   /* radix of the floating point number e.g. a binary machine  */
#define FLT_ROUNDS       1   /* rounding to nearest is used */

/* Characteristics of float type */

#define FLT_DIG          6   /* maximum decimal digits of float precision */
#define FLT_EPSILON      5.96046e-8
#define FLT_MANT_DIG     24
#define FLT_MAX          3.40282e38
#define FLT_MAX_EXP      0x7F
#define FLT_MAX_10_EXP   38
#define FLT_MIN          1.17549e-38
#define FLT_MIN_EXP      -125
#define FLT_MIN_10_EXP   -37

/* Characteristics of double type */

#define DBL_DIG          15  /* maximum decimal digits of double precision */
#define DBL_EPSILON      1.110223024625156e-16
#define DBL_MANT_DIG     53
#define DBL_MAX          1.797693134862315e308
#define DBL_MAX_EXP      1023
#define DBL_MAX_10_EXP   308
#define DBL_MIN          2.225073858507202e-308
#define DBL_MIN_EXP      -1021
#define DBL_MIN_10_EXP   -307

/* Characteristics of long double type */

#define LDBL_DIG         15  /* max decimal digits of long double precisn */
#define LDBL_EPSILON     1.110223024625156e-16
#define LDBL_MANT_DIG    53
#define LDBL_MAX         1.797693134862315e308
#define LDBL_MAX_EXP     1023
#define LDBL_MAX_10_EXP  308
#define LDBL_MIN         2.225073858507202e-308
#define LDBL_MIN_EXP     -1021
#define LDBL_MIN_10_EXP  -307

#endif /* _FLOAT_H_ */

