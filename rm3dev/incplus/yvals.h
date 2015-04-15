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
 * $Log: yvals.h,v $
 * Revision 1.2  2000/02/08 06:21:08  pla
 * LIBCXX V210
 *
 * Revision 1.1  1998/05/04 14:43:07  aki
 * Initial revision
 *
 */ 

/* yvals.h values header for CAD-UL C/C++ */
#ifndef _YVALS
#define _YVALS

#pragma noarguments_in_registers(push)


#ifndef _HAS_EXCEPTIONS
#ifdef	__EXCEPTIONS_ENABLED
 #define _HAS_EXCEPTIONS	1
#else
 #define _HAS_EXCEPTIONS	0
#endif
#endif

/* switched global */
#ifndef	_HAS_NAMESPACE
 #define _HAS_NAMESPACE	0
#endif

		/* NAMESPACE */
 #if _HAS_NAMESPACE
 #if defined(__cplusplus)
  #define _STD			std::
  #define _STD_BEGIN	namespace std {
  #define _STD_END		};
  #define _STD_USING
 #else
  #define _STD			::
  #define _STD_BEGIN
  #define _STD_END
 #endif /* __cplusplus */
 #else
  #define _STD			::
  #define _STD_BEGIN
  #define _STD_END
 #endif /* _HAS_NAMESPACE */
_STD_BEGIN
		/* TYPE bool */
 #if defined(__cplusplus)
typedef bool _Bool;
 #endif /* __cplusplus */
		/* INTEGER PROPERTIES */
#define _MAX_EXP_DIG	8	/* for parsing numerics */
#define _MAX_INT_DIG	32
#define _MAX_SIG_DIG	36
		/* STDIO PROPERTIES */
#define _Filet	FILE
#define _FPOSOFF(fp)	((long)(fp))
#define _IOBASE	io_base
#define _IOPTR	io_next
#define _IOCNT	io_left

		/* NAMING PROPERTIES */
 #if defined(__cplusplus)
  #define _C_LIB_DECL extern "C" {
  #define _END_C_LIB_DECL }
 #else
  #define _C_LIB_DECL
  #define _END_C_LIB_DECL
 #endif /* __cplusplus */
#define _CDECL
#define _CRTIMP
 #if defined(__cplusplus)
		// LOCK MACROS
#define _LOCK_LOCALE	0
#define _LOCK_MALLOC	1	/* 2008DE1 give them unique values */
#define _LOCK_STREAM	2
		// CLASS _Lockit
/*
 * 2008DE1
 * Thread safety for IO-Streams
 */
_STD_END
#include "libcxx.h"
_STD_BEGIN

#if	PSOS
/* For pSOS, we cannot store the FILE-pointers statically during cin,cout constructor
 * call. The symbolic pointers are replaced by the actual values during runtime
 */
#define	STDIN	(_Filet *)1
#define	STDOUT	(_Filet *)2
#define	STDERR	(_Filet *)3
#endif
/* 2008DE1 */

class _Lockit
	{	// lock while object in existence
public:
	explicit _Lockit(int kind ,_IOS_SEM *sem)
		{
		/*
		 * 2008DE1
		 * Lock the semaphore and stored it for unlock. Only 
		 * stream activities are monitored. Others are C-lib
		 * functionality, which is assumed to be thread safe.
		 */
		if(kind == _LOCK_STREAM) {
			if(sem != 0)
				_sem = *sem;
			else
				_sem = 0;
			__cadul_enter_critical_section((void *)sem);
			}
		}
	~_Lockit()
		{
		/*
		 * 2008DE1
		 * Free the semaphore
		 */
		__cadul_exit_critical_section((_sem != 0) ? ((void *)&_sem) : 0);
		}
private:
	_IOS_SEM	_sem;	/* The semaphore */
	};
 #endif /* __cplusplus */
		/* MISCELLANEOUS MACROS */
#define _ATEXIT_T	void
#define _Mbstinit(x)	mbstate_t x = {0}
#define _TEMPLATE_STAT
_STD_END

#ifdef	m68000
#define	__BIG_ENDIAN	1
#endif

#pragma arguments_in_registers(pop)

#endif /* _YVALS */

/*
 * Copyright (c) 1996 by P.J. Plauger.  ALL RIGHTS RESERVED. 
 * Consult your license regarding permissions and restrictions.
V2.2:0414 */
