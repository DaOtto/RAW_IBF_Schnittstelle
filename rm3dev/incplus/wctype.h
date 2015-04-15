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
 * $Log: wctype.h,v $
 * Revision 1.2  2000/02/08 06:21:07  pla
 * LIBCXX V210
 *
 * Revision 1.1  1998/05/04 14:43:06  aki
 * Initial revision
 *
 */ 

/* wctype.h standard header for CAD-UL */
#ifndef _WCTYPE
#define _WCTYPE

#pragma noarguments_in_registers(push)

#include <wchar.h>	/* for __L, NULL, size_t, wchar_t, wint_t */
#ifndef _YVALS
#include <yvals.h>
#endif
_STD_BEGIN
	/* type definitions */
typedef size_t wctrans_t;
typedef size_t wctype_t;
	/* ctype declarations */
_C_LIB_DECL
int _Iswctype(wint_t, wctype_t);
wint_t _Towctrans(wint_t, wctrans_t);
wctrans_t wctrans(const char *);
wctype_t wctype(const char *);
_END_C_LIB_DECL
#ifdef __cplusplus
		/* inlines, for C++ */
inline int iswalnum(wint_t _Wc)
	{return (_Iswctype(_Wc, 1)); }
inline int iswalpha(wint_t _Wc)
	{return (_Iswctype(_Wc, 2)); }
inline int iswcntrl(wint_t _Wc)
	{return (_Iswctype(_Wc, 3)); }
inline int iswctype(wint_t _Wc, wctype_t _Off)
	{return (_Iswctype(_Wc, _Off)); }
inline int iswdigit(wint_t _Wc)
	{return (_Iswctype(_Wc, 4)); }
inline int iswgraph(wint_t _Wc)
	{return (_Iswctype(_Wc, 5)); }
inline int iswlower(wint_t _Wc)
	{return (_Iswctype(_Wc, 6)); }
inline int iswprint(wint_t _Wc)
	{return (_Iswctype(_Wc, 7)); }
inline int iswpunct(wint_t _Wc)
	{return (_Iswctype(_Wc, 8)); }
inline int iswspace(wint_t _Wc)
	{return (_Iswctype(_Wc, 9)); }
inline int iswupper(wint_t _Wc)
	{return (_Iswctype(_Wc, 10)); }
inline int iswxdigit(wint_t _Wc)
	{return (_Iswctype(_Wc, 11)); }
inline wint_t towctrans(wint_t _Wc, wctrans_t _Off)
	{return (_Towctrans(_Wc, _Off)); }
inline wint_t towlower(wint_t _Wc)
	{return (_Towctrans(_Wc, 1)); }
inline wint_t towupper(wint_t _Wc)
	{return (_Towctrans(_Wc, 2)); }
#else
	/* declarations and macro overrides, for C */
int iswalnum(wint_t);
int iswalpha(wint_t);
int iswcntrl(wint_t);
int iswctype(wint_t, wctype_t);
int iswdigit(wint_t);
int iswgraph(wint_t);
int iswlower(wint_t);
int iswprint(wint_t);
int iswpunct(wint_t);
int iswspace(wint_t);
int iswupper(wint_t);
int iswxdigit(wint_t);
wint_t towctrans(wint_t, wctrans_t);
wint_t towlower(wint_t);
wint_t towupper(wint_t);
#define iswalnum(wc)	_Iswctype(wc, 1)
#define iswalpha(wc)	_Iswctype(wc, 2)
#define iswcntrl(wc)	_Iswctype(wc, 3)
#define iswctype(wc, off)	_Iswctype(wc, off)
#define iswdigit(wc)	_Iswctype(wc, 4)
#define iswgraph(wc)	_Iswctype(wc, 5)
#define iswlower(wc)	_Iswctype(wc, 6)
#define iswprint(wc)	_Iswctype(wc, 7)
#define iswpunct(wc)	_Iswctype(wc, 8)
#define iswspace(wc)	_Iswctype(wc, 9)
#define iswupper(wc)	_Iswctype(wc, 10)
#define iswxdigit(wc)	_Iswctype(wc, 11)
#define towctrans(wc, off)	_Towctrans(wc, off)
#define towlower(wc)	_Towctrans(wc, 1)
#define towupper(wc)	_Towctrans(wc, 2)
#endif /* __cplusplus */
_STD_END
#ifdef _STD_USING
using std::wint_t; using std::wctrans_t; using std::wctype_t;
using std::wctrans; using std::wctype; using std::iswalnum;
using std::iswalpha; using std::iswcntrl; using std::iswctype;
using std::iswdigit; using std::iswgraph; using std::iswlower;
using std::iswprint; using std::iswpunct; using std::iswspace;
using std::iswupper; using std::iswxdigit; using std::towctrans;
using std::towlower; using std::towupper;
#endif /* _STD_USING */

#pragma arguments_in_registers(pop)

#endif /* _WCTYPE */

/*
 * Copyright (c) 1994 by P.J. Plauger.  ALL RIGHTS RESERVED. 
 * Consult your license regarding permissions and restrictions.
V2.2:0414 */
