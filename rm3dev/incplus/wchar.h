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
 * $Log: wchar.h,v $
 * Revision 1.2  2000/02/08 06:21:07  pla
 * LIBCXX V210
 *
 * Revision 1.1  1998/05/04 14:43:06  aki
 * Initial revision
 *
 */ 

/* wchar.h standard header for CAD-UL */
#ifndef _WCHAR
#define _WCHAR

#pragma noarguments_in_registers(push)

#include <stddef.h>	/* for NULL, size_t, wchar_t */
#include <stdarg.h>	/* for va_list */
#ifndef _YVALS
#include <yvals.h>
#endif
_STD_BEGIN
	/* macros */
#define __L(x)	L##x
#define _Mbstinit(x)  mbstate_t x = {0}
#define WCHAR_MIN	0
#define WCHAR_MAX	65535
#define WEOF	((wint_t)(-1))
	/* type definitions */
typedef int mbstate_t;
struct tm;
struct _Filet;
typedef va_list _Va_list;
#ifndef _WINTT
#define _WINTT
typedef wchar_t wint_t;
#endif
	/* stdio declarations */
_C_LIB_DECL
wint_t fgetwc(struct _Filet *);
wchar_t *fgetws(wchar_t *, int, struct _Filet *);
wint_t fputwc(wchar_t, struct _Filet *);
int fputws(const wchar_t *, struct _Filet *);
int fwide(struct _Filet *, int);
int fwprintf(struct _Filet *, const wchar_t *, ...);
int fwscanf(struct _Filet *, const wchar_t *, ...);
wint_t getwc(struct _Filet *);
wint_t getwchar(void);
wint_t putwc(wchar_t, struct _Filet *);
wint_t putwchar(wchar_t);
int swprintf(wchar_t *, size_t, const wchar_t *, ...);
int swscanf(const wchar_t *, const wchar_t *, ...);
wint_t ungetwc(wint_t, struct _Filet *);
int vfwprintf(struct _Filet *, const wchar_t *, _Va_list);
int vswprintf(wchar_t *, size_t, const wchar_t *, _Va_list);
int vwprintf(const wchar_t *, _Va_list);
int wprintf(const wchar_t *, ...);
int wscanf(const wchar_t *, ...);
	/* stdlib declarations */
size_t mbrlen(const char *, size_t, mbstate_t *);
size_t mbrtowc(wchar_t *, const char *, size_t, mbstate_t *);
size_t mbsrtowcs(wchar_t *, const char **, size_t,
	mbstate_t *);
int mbsinit(const mbstate_t *);
size_t wcrtomb(char *, wchar_t, mbstate_t *);
size_t wcsrtombs(char *, const wchar_t **, size_t,
	mbstate_t *);
long wcstol(const wchar_t *, wchar_t **, int);
	/* string declarations */
wchar_t *wcscat(wchar_t *, const wchar_t *);
int wcscmp(const wchar_t *, const wchar_t *);
int wcscoll(const wchar_t *, const wchar_t *);
wchar_t *wcscpy(wchar_t *, const wchar_t *);
size_t wcscspn(const wchar_t *, const wchar_t *);
size_t wcslen(const wchar_t *);
wchar_t *wcsncat(wchar_t *, const wchar_t *, size_t);
int wcsncmp(const wchar_t *, const wchar_t *, size_t);
wchar_t *wcsncpy(wchar_t *, const wchar_t *, size_t);
size_t wcsspn(const wchar_t *, const wchar_t *);
wchar_t *wcstok(wchar_t *, const wchar_t *, wchar_t **);
size_t wcsxfrm(wchar_t *, const wchar_t *, size_t);
int wmemcmp(const wchar_t *, const wchar_t *, size_t);
wchar_t *wmemcpy(wchar_t *, const wchar_t *, size_t);
wchar_t *wmemmove(wchar_t *, const wchar_t *, size_t);
wchar_t *wmemset(wchar_t *, wchar_t, size_t);
	/* time declarations */
size_t wcsftime(wchar_t *, size_t, const wchar_t *,
	const struct tm *);
wint_t _Btowc(int);
int _Wctob(wint_t);
double _WStod(const wchar_t *, wchar_t **, long);
float _WStof(const wchar_t *, wchar_t **, long);
int _WStoflt(const wchar_t *, wchar_t **, long[], int);
long double _WStold(const wchar_t *, wchar_t **, long);
unsigned long _WStoul(const wchar_t *, wchar_t **, int);
_END_C_LIB_DECL
	/* inlines/macros */
#ifdef __cplusplus
		/* inlines and overloads, for C++ */
#define _WConst_return const
_C_LIB_DECL
const wchar_t *wmemchr(const wchar_t *, wchar_t, size_t);
const wchar_t *wcschr(const wchar_t *, wchar_t);
const wchar_t *wcspbrk(const wchar_t *, const wchar_t *);
const wchar_t *wcsrchr(const wchar_t *, wchar_t);
const wchar_t *wcsstr(const wchar_t *, const wchar_t *);
_END_C_LIB_DECL
inline wchar_t *wmemchr(wchar_t *__S, wchar_t __C, size_t __N)
	{return ((wchar_t *)wmemchr((const wchar_t *)__S, __C, __N)); }
inline wchar_t *wcschr(wchar_t *__S, wchar_t __C)
	{return ((wchar_t *)wcschr((const wchar_t *)__S, __C)); }
inline wchar_t *wcspbrk(wchar_t *__S, const wchar_t *__P)
	{return ((wchar_t *)wcspbrk((const wchar_t *)__S, __P)); }
inline wchar_t *wcsrchr(wchar_t *__S, wchar_t __C)
	{return ((wchar_t *)wcsrchr((const wchar_t *)__S, __C)); }
inline wchar_t *wcsstr(wchar_t *__S, const wchar_t *__P)
	{return ((wchar_t *)wcsstr((const wchar_t *)__S, __P)); }
inline wint_t btowc(int __C)
	{return (_Btowc(__C)); }
inline double wcstod(const wchar_t *__S, wchar_t **_Endptr)
	{return (_WStod(__S, _Endptr, 0)); }
inline unsigned long wcstoul(const wchar_t *__S, wchar_t **_Endptr,
	int _Base)
	{return (_WStoul(__S, _Endptr, _Base)); }
inline int wctob(wint_t _Wc)
	{return (_Wctob(_Wc)); }
#else
#define _WConst_return
wchar_t *wmemchr(const wchar_t *, wchar_t, size_t);
wchar_t *wcschr(const wchar_t *, wchar_t);
wchar_t *wcspbrk(const wchar_t *, const wchar_t *);
wchar_t *wcsrchr(const wchar_t *, wchar_t);
wchar_t *wcsstr(const wchar_t *, const wchar_t *);
wint_t btowc(int);
double wcstod(const wchar_t *, wchar_t **);
unsigned long wcstoul(const wchar_t *, wchar_t **, int);
int wctob(wint_t);
#define btowc(c)	_Btowc(c)
#define wcstod(s, endptr)	_WStod(s, endptr, 0)
#define wcstoul(s, endptr, base)	_WStoul(s, endptr, base)
#define wctob(wc)	_Wctob(wc)
#endif /* __cplusplus */
_STD_END
#if 0
#ifdef _STD_USING
using std::mbstate_t; using std::size_t; using std::wint_t;
using std::fgetwc; using std::fgetws; using std::fputwc;
using std::fputws; using std::fwide; using std::fwprintf;
using std::fwscanf; using std::getwc; using std::getwchar;
using std::putwc; using std::putwchar; using std::swprintf;
using std::swscanf; using std::ungetwc; using std::vfwprintf;
using std::vswprintf; using std::vwprintf; using std::wprintf;
using std::wscanf; using std::mbrlen; using std::mbrtowc;
using std::mbsrtowcs; using std::mbsinit; using std::wcrtomb;
using std::wcsrtombs; using std::wcstol; using std::wcscat;
using std::wcschr; using std::wcscmp; using std::wcscoll;
using std::wcscpy; using std::wcscspn; using std::wcslen;
using std::wcsncat; using std::wcsncmp; using std::wcsncpy;
using std::wcspbrk; using std::wcsrchr; using std::wcsspn;
using std::wcsstr; using std::wcstok; using std::wcsxfrm;
using std::wmemchr; using std::wmemcmp; using std::wmemcpy;
using std::wmemmove; using std::wmemset; using std::wcsftime;
#endif /* _STD_USING */
#endif

#ifdef _STD_USING
using std::mbstate_t; using std::wint_t;
using std::fgetwc; using std::fgetws; using std::fputwc;
using std::fputws; using std::fwide; using std::fwprintf;
using std::fwscanf; using std::getwc; using std::getwchar;
using std::putwc; using std::putwchar; using std::swprintf;
using std::swscanf; using std::ungetwc; using std::vfwprintf;
using std::vswprintf; using std::vwprintf; using std::wprintf;
using std::wscanf; using std::mbrlen; using std::mbrtowc;
using std::mbsrtowcs; using std::mbsinit; using std::wcrtomb;
using std::wcsrtombs; using std::wcstol; using std::wcscat;
using std::wcschr; using std::wcscmp; using std::wcscoll;
using std::wcscpy; using std::wcscspn; using std::wcslen;
using std::wcsncat; using std::wcsncmp; using std::wcsncpy;
using std::wcspbrk; using std::wcsrchr; using std::wcsspn;
using std::wcsstr; using std::wcstok; using std::wcsxfrm;
using std::wmemchr; using std::wmemcmp; using std::wmemcpy;
using std::wmemmove; using std::wmemset; using std::wcsftime;
#endif /* _STD_USING */

#pragma arguments_in_registers(pop)

#endif /* _WCHAR */

/*
 * Copyright (c) 1994 by P.J. Plauger.  ALL RIGHTS RESERVED. 
 * Consult your license regarding permissions and restrictions.
V2.2:0414 */
