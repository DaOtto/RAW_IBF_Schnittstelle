/* Edison Design Group, 1992. */
/*
new.h -- Include file for C++ default operator new (see ARM 12.5).
*/


#ifndef __NEW_H
#define __NEW_H


#pragma noarguments_in_registers(push)

#ifndef __STDDEF_H
#include <stddef.h>
#endif
#ifndef _EXCEPTION_H
#include <exception.h>
	/* 499DE1
	 * Moved up, to have the THROW-macros, even of exception.h
	 * already included
	 */
#endif /* _EXCEPTION_H */
#ifdef	__EXCEPTIONS_ENABLED
#ifndef	THROW_NOTHING
#define	THROW_NOTHING()	throw()
#endif
#ifndef	THROW_1
#define	THROW_1(x)	throw(x)
#endif
#else
#ifndef	THROW_NOTHING
#define	THROW_NOTHING()
#endif
#ifndef	THROW_1
#define	THROW_1(x)
#endif
#endif

typedef unsigned int size_t;		/* Lengths */

#ifndef __STD_NAMESPACE
/* If not already defined, define a macro that expands to the namespace
   containing the standard library. */
#ifdef __RUNTIME_USES_NAMESPACES
#define __STD_NAMESPACE std
#else /* ifndef __RUNTIME_USES_NAMESPACES */
#define __STD_NAMESPACE /* nothing */
#endif /* ifdef __RUNTIME_USES_NAMESPACES */
#endif /* ifdef __STD_NAMESPACE */


#ifdef __RUNTIME_USES_NAMESPACES
namespace std {
#endif /* ifdef __RUNTIME_USES_NAMESPACES */

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

/* This lets users disable the EDG supplied exception classes. */
#ifndef __NO_EXCEPTION_CLASSES

#define	BAD_ALLOC	"bad_allocation" // the default message

#if i8086 /* >> 4719DE1 >> */
#pragma	align(bad_alloc=2)
#else
#pragma	align(bad_alloc=4)	// 3055DE1 
#endif /* << 4719DE1 << */
  class bad_alloc : public exception {
  public:
    bad_alloc(const char *message = BAD_ALLOC) THROW_NOTHING();

    bad_alloc(const bad_alloc& copyfrom) THROW_NOTHING();

    bad_alloc& __FAR__ operator=(const bad_alloc& copyfrom) THROW_NOTHING();

    virtual ~bad_alloc() THROW_NOTHING();

    virtual const char* __FAR__ what() const THROW_NOTHING();
  };

#endif /* ifndef __NO_EXCEPTION_CLASSES */

  typedef void (__FAR__ * new_handler)();
  new_handler set_new_handler(new_handler);
  struct nothrow_t { };
  // Declaration of object nothrow to permit the use of the placement new
  // syntax: new (nothrow) T;
  const nothrow_t nothrow = {};

#ifdef __RUNTIME_USES_NAMESPACES
}  /* namespace std */

#ifdef __IMPLICIT_USING_STD
/* Implicitly include a using directive for the STD namespace when this
   preprocessing flag is TRUE. */
using namespace std;
#endif /* ifdef __IMPLICIT_USING_STD */

#endif /* ifdef __RUNTIME_USES_NAMESPACES */

/*
Normal operator new routine.
*/
void *operator new(size_t) THROW_1(__STD_NAMESPACE::bad_alloc);

/*
Nothrow version of operator new.
*/
void *operator new(size_t, const __STD_NAMESPACE::nothrow_t&) THROW_NOTHING();

/*
Placement new.  This was not in the ARM, but it is now standard in
[lib.new.delete.placement].
*/
void *operator new(size_t, void*) THROW_NOTHING();

/*
Placement delete.
*/
#ifdef __PLACEMENT_DELETE
void operator delete(void*, void*);
#endif /* ifdef __PLACEMENT_DELETE */

#ifdef __ARRAY_OPERATORS
/*
Array new.
*/
void *operator new[](size_t) THROW_1(__STD_NAMESPACE::bad_alloc);

/*
Placement array new.
*/
void *operator new[](size_t, void*) THROW_NOTHING();

/*
Placement array delete.
*/
#ifdef __PLACEMENT_DELETE
void operator delete[](void*, void*);
#endif /* ifdef __PLACEMENT_DELETE */

/*
Nothrow version of array new.
*/
void *operator new[](size_t,
                     const __STD_NAMESPACE::nothrow_t&) THROW_NOTHING();
#endif /* __ARRAY_OPERATORS */

#pragma arguments_in_registers(pop)

#endif
