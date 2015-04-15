/* Edison Design Group, 1995. */
/*
stdexcept.h -- Include file for exception handling (see 19.1.1)
*/
#ifndef _STDEXCEPT_H
#define _STDEXCEPT_H

#pragma noarguments_in_registers(push)

/* This lets users disable the EDG supplied exception classes. */
#ifndef __NO_EXCEPTION_CLASSES

  /* PLA 22.5.98 LIBX-0006 
   * 1080DE1 __FAR__ added to methods 
   * 1752DE1 __S12__ added
   */
#ifdef	i386
#ifdef	COMPACT
#if     defined(__WITH_SUBSYS__)	/* 2377DE1 */
#undef __FAR__
#define	__FAR__	far
#endif
#endif
#endif
#ifndef	__FAR__
#define	__FAR__ /**/
#endif
#ifdef __RUNTIME_USES_NAMESPACES
namespace std {
#endif /* ifdef __RUNTIME_USES_NAMESPACES */

#include	"libcxx.h"
class	exception;
typedef void (__FAR__ * raise_hanlder)(const exception&);
#ifndef	__CXXTLS__
extern	raise_hanlder	_Raise_handler;
#endif

#ifndef	__EXCEPTIONS_ENABLED
#define	THROW_NOTHING()
#else
#define	THROW_NOTHING()	throw()
#endif

  #define	UNKNOWN	"unknown"	// the default message

#if i8086 /* >> 4719DE1 >> */
#pragma	align	(exception=2)
#else
#pragma	align	(exception=4)		// 3055DE1
#endif /* << 4719DE1 << */
  class exception {
  public:
    static raise_hanlder __FAR__ _Set_raise_handler(raise_hanlder);

    explicit exception(const char *message = UNKNOWN) THROW_NOTHING();

    exception(const exception& copyfrom) THROW_NOTHING();

    exception& __FAR__ operator=(const exception& copyfrom) THROW_NOTHING();

    virtual ~exception() THROW_NOTHING();

    virtual const char* __FAR__ what() const THROW_NOTHING();

    void __FAR__ _Raise(void) const;
  protected:
#ifndef	__EXCEPTIONS_EANBLED
    void _Doraise() const
                {}
#endif
    const char *_message;
  };
#ifdef __RUNTIME_USES_NAMESPACES
}  /* namespace std */

#ifdef __IMPLICIT_USING_STD
/* Implicitly include a using directive for the STD namespace when this
   preprocessing flag is TRUE. */
using namespace std;
#endif /* ifdef __IMPLICIT_USING_STD */

#endif /* ifdef __RUNTIME_USES_NAMESPACES */

#endif /* ifndef __NO_EXCEPTION_CLASSES */

#pragma arguments_in_registers(pop)

#endif /* _STDEXCEPT_H */

