/* Edison Design Group, 1994. */
/*
exception.h -- Include file for exception handling (see 18.6)
*/
#ifndef _EXCEPTION_H
#define _EXCEPTION_H

/* This lets users disable the EDG supplied exception classes. */
#ifndef __NO_EXCEPTION_CLASSES



  /* PLA 22.5.98 LIBX-0006 
   * 1080DE1 __FAR__ added to methods 
   * 1752DE1 __S12__ added
   */
#ifdef	i386
#ifdef	COMPACT
#if	defined(__WITH_SUBSYS__)	/* 2377DE1 */
#undef __FAR__
#define	__FAR__	far
#endif
#endif
#endif
#ifndef	__FAR__
#define	__FAR__ /**/
#endif

#pragma noarguments_in_registers(push)

#include <stdexcept.h>

#ifdef __RUNTIME_USES_NAMESPACES
namespace std {
#endif /* ifdef __RUNTIME_USES_NAMESPACES */

  /*
  If bool is not supported, use a typedef for bool.
  */
  #ifdef _BOOL
  typedef bool _bool;
  #else /* ifndef _BOOL */
  typedef int _bool;
  #endif /* ifdef _BOOL */

  #define BAD_EXCEPTION	"bad exception"	// the default message 

#if i8086 /* >> 4719DE1 >> */
#pragma       align(bad_exception=2)
#else
#pragma       align(bad_exception=4)	// 3055DE1 
#endif /* << 4719DE1 << */
  class bad_exception : public exception {
  public:
    bad_exception(const char *message = BAD_EXCEPTION) THROW_NOTHING();
	
    bad_exception(const bad_exception& copyfrom) THROW_NOTHING();

    bad_exception& __FAR__ operator=(const bad_exception& copyfrom)
							THROW_NOTHING();
    virtual ~bad_exception() THROW_NOTHING();
    virtual const char* __FAR__ what() const THROW_NOTHING();
  };

  typedef void (__FAR__ *terminate_handler)();
  extern terminate_handler set_terminate(terminate_handler);

  typedef void (__FAR__ *unexpected_handler)();
  extern unexpected_handler set_unexpected(unexpected_handler);

  /* unexpected and terminate are in the WP definition of exception.h.
     It is not clear why. */
  void __FAR__ terminate();
  void __FAR__ unexpected();

  extern _bool uncaught_exception();

#ifdef __RUNTIME_USES_NAMESPACES
}  /* namespace */

#ifdef __IMPLICIT_USING_STD
/* Implicitly include a using directive for the STD namespace when this
   preprocessing flag is TRUE. */
using namespace std;
#endif /* ifdef __IMPLICIT_USING_STD */

#endif /* ifdef __RUNTIME_USES_NAMESPACES */

#else
#define	throw(x)	
#endif /* ifndef __NO_EXCEPTION_CLASSES */

#pragma arguments_in_registers(pop)

#endif /* _EXCEPTION_H */

