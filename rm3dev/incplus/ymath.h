 /*(
 * The information  contained  herein is a trade secret of CAD-UL GmbH,
 * Ulm, Germany, and is confidential information. It is provided  under
 * a license agreement, and may be  copied or disclosed  only under the
 * terms of  that  agreement.  Any  reproduction or disclosure  of this
 * material  without  the express written  authorization of CAD-UL GmbH
 * or persuant to the license agreement is unlawful.
 *
 * Copyright (c) 1991-1998 CAD-UL GmbH
 * An unpublished work by CAD-UL GmbH, Germany
 * All rights reserved.
 *
 *
 * $Log: ymath.h,v $
 * Revision 1.2  2000/02/08 06:21:08  pla
 * LIBCXX V210
 *
 * Revision 1.1  1998/05/04 14:43:07  aki
 * Initial revision
 *
 */ 

/* ymath.h internal header */
#ifndef _YMATH
#define _YMATH

#pragma noarguments_in_registers(push)

#include <math.h>
#ifndef _YVALS
#include <yvals.h>
#endif
		/* MACROS */
#define _FINITE		-1
#define _INFCODE	1
#define _NANCODE	2
		/* TYPE DEFINITIONS */
typedef union {
	unsigned short _W[5];
	float _F;
	double _D;
	long double __L;
	} _Dconst;
_C_LIB_DECL
		/* double DECLARATIONS */
double _Cosh(double, double);
short _Dtest(double *);
short _Exp(double *, double, short);
double _Log(double, int);
double _Sin(double, unsigned int);
double _Sinh(double, double);
extern const _Dconst _Denorm, _Hugeval, _Inf,
	_Nan, _Snan;
		/* float DECLARATIONS */
float _FCosh(float, float);
short _FDtest(float *);
short _FExp(float *, float, short);
float _FLog(float, int);
float _FSin(float, unsigned int);
float _FSinh(float, float);
extern const _Dconst _FDenorm, _FInf, _FNan, _FSnan;
		/* float ADDITIONS TO math.h */
float (atan2f)(float, float);
float (cosf)(float);
float (expf)(float);
float (ldexpf)(float, int);
float (logf)(float);
float (powf)(float, float);
float (sinf)(float);
float (sqrtf)(float);
float (tanf)(float);
_END_C_LIB_DECL

#pragma arguments_in_registers(pop)

#endif /* _YMATH */

/*
 * Copyright (c) 1995 by P.J. Plauger.  ALL RIGHTS RESERVED. 
 * Consult your license regarding permissions and restrictions.
V2.2:0414 */
