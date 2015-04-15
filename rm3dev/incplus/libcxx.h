/*
 * The information  contained  herein is a trade secret of CAD-UL GmbH,
 * Ulm, Germany, and is confidential information. It is provided  under
 * a license agreement, and may be  copied or disclosed  only under the
 * terms of  that  agreement.  Any  reproduction or disclosure  of this
 * material  without  the express written  authorization of CAD-UL GmbH
 * or persuant to the license agreement is unlawful.
 *
 * Copyright (c) 1999 CAD-UL GmbH
 * An unpublished work by CAD-UL GmbH, Germany
 * All rights reserved.
 */
#ifndef	LIBCXX_H
#define	LIBCXX_H

#include	<stddef.h>

#pragma noarguments_in_registers(push)

extern	"C" {

/* generic form predefined by the compiler. */
#define _PFX(x) __ ## x
#if i8086 /* >> 4719DE1 >> */
#pragma	align	(__user_cxxtls=2)
#else
#pragma	align	(__user_cxxtls=4)
#endif /* << 4719DE1 << */
struct	__user_cxxtls	{
	/* this type MUST BE compatible to 'a_region_number' of c++ compiler */
	long				_PFX(magic_number1);
	int				_PFX(eh_curr_region);
	int				_PFX(catch_clause_number);
	/* This type MUST BE compatible to 'an_eh_stack_entry_ptr'of c++ 
	 * compiler
	 */
	void	*			_PFX(curr_eh_stack_entry);	
	void	*			_PFX(caught_object_address);
	/*
	 * The rest of the CXXTLS is not accessed by the user code
	 * and therefore omitted.
	 */
	};
extern	__user_cxxtls	*	__cxxtls;

/* 1752DE1 __S12__ added */
#ifdef	i386
#ifdef	COMPACT
#if     defined(__WITH_SUBSYS__)	/* 2377DE1 */
#undef __FAR__
#define	__FAR__	far
#endif
#endif
#endif
#ifndef	__FAR__
#define	__FAR__
#endif

/*
 * Service funtions, required by the C++ runtime library for TLS
 * handling. 
 */
/*
 * Hooks are called by the runtime to get OS-specific services as
 * dynamic memory allocation
 */
extern	void __FAR__	__cxx_tls_free_hook(void *,bool);
extern	void *__FAR__	__cxx_tls_alloc_hook(size_t,bool);
extern	void __FAR__	__cxx_tls_delete_hook(void *);
extern	void __FAR__	__cxx_tls_delete_root_hook(void *);
extern	void __FAR__	__cxx_tls_set_hook(void *,int *);
extern	struct __user_cxxtls* __FAR__
			__cxx_tls_get_hook(void);
extern	int __FAR__	__cxx_tls_init_hook(void *);
extern	int __FAR__	__cxx_tls_exit_hook(void);

/*
 * Functions, which are used to manipulate the TLS
 */
extern	size_t __FAR__	__cxx_tls_size(void);
extern	void __FAR__	__cxx_tls_init(void *,void *,void *,void *);
extern	void* __FAR__	__cxx_tls_set(void *,int *);
extern	void __FAR__	__cxx_tls_delete(void);
extern	void* __FAR__	__cxx_tls_get_root(void);
extern	void __FAR__	__cxx_tls_free_hook(void *,bool);

/*
 * C++ TLS specific error codes
 */
#define	ECXX_TLS_NOTINIT	1	/* TLS not initialized */


/*
 * 2008DE1 
 * Lock/Unlock functions
 */
typedef	unsigned long	_IOS_SEM;	/* type to hold a semphore */
#define	NO_SEM		0		/* no semaphore assigned */
extern	"C"	void	__cadul_enter_critical_section(void *);
extern	"C"	void	__cadul_exit_critical_section(void *);
extern	"C"	void	__cadul_enable_critical_section_lock(void *);
extern	"C"	void	__cadul_disable_critical_section_lock(void *);
extern	"C"	void	__cadul_share_critical_section_lock(void *,void *);

}

#pragma arguments_in_registers(pop)

#endif

