/* Edison Design Group, 1995. */
/*
typeinfo.h -- Include file for type information (18.5.1)
*/
#ifndef _TYPEINFO_H
#define _TYPEINFO_H

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

 
#ifndef __EXCEPTIONS_ENABLED
#define THROW_NOTHING()
#else
#define THROW_NOTHING() throw()
#endif

/* The following pragma is used so that the compiler knows that this definition
   of type_info is the one that corresponds to the type returned by typeid. */
#pragma define_type_info
#if i8086 /* >> 4719DE1 >> */
#pragma	align(type_info=2)
#else
#pragma	align(type_info=4)		// 3055DE1 
#endif /* << 4719DE1 << */
  class type_info {
  public:
    virtual ~type_info();
    _bool __FAR__ operator==(const type_info&) const;
    _bool __FAR__ operator!=(const type_info&) const;
    _bool __FAR__ before(const type_info&) const;
    const char* __FAR__ name() const;
  private:
    type_info& __FAR__ operator=(const type_info&);  // Not actually defined
#if 0
#else /* 0 */
  protected:
    // Protected instead of private to suppress the "no accessible
    // constructor" warning
#endif /* 0 */
    type_info(const type_info&);  // Not actually defined
  };

#define	BAD_CAST	"bad cast"	// the default message
#if i8086 /* >> 4719DE1 >> */
#pragma	align(bad_cast=2)
#else
#pragma	align(bad_cast=4)		// 3055DE1  
#endif /* << 4719DE1 << */
  class bad_cast : public exception {
  public:
    bad_cast(const char *message = BAD_CAST) THROW_NOTHING();
    bad_cast(const bad_cast&) THROW_NOTHING();
    bad_cast& __FAR__ operator=(const bad_cast&) THROW_NOTHING();
    virtual ~bad_cast() THROW_NOTHING();
    virtual const char* __FAR__ what() const THROW_NOTHING();
  };

#define	BAD_TYPEID	"bad typeid"	// the default message
#if i8086 /* >> 4719DE1 >> */
#pragma	align(bad_typeid=2)
#else
#pragma	align(bad_typeid=4)		// 3055DE1 
#endif /* << 4719DE1 << */
  class bad_typeid : public exception {
  public:
    bad_typeid(const char *message = BAD_TYPEID) THROW_NOTHING();
    bad_typeid(const bad_typeid&) THROW_NOTHING();
    bad_typeid& __FAR__ operator=(const bad_typeid&) THROW_NOTHING();
    virtual ~bad_typeid() THROW_NOTHING();
    virtual const char* __FAR__ what() const THROW_NOTHING();
  };

#ifdef __RUNTIME_USES_NAMESPACES
}  /* namespace std */

#ifdef __IMPLICIT_USING_STD
/* Implicitly include a using directive for the STD namespace when this
   preprocessing flag is TRUE. */
using namespace std;
#endif /* ifdef __IMPLICIT_USING_STD */

#endif /* ifdef __RUNTIME_USES_NAMESPACES */

#pragma arguments_in_registers(pop)

#endif /* _TYPEINFO_H */
