/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : MISC86.H
;   version     : 0007
;   contents    : I/O functions, address manipulations and interrupt handling
;   author      : J.R.
;   date        : May 10, 1993
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : I/O functions, address manipulations and interrupt handling
;                 for RMOS2.
;                 This header file should be included instead of i86.h/i386.h
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   May 10, 1993  J.R.  0001  Original issue after beta test
;   Jul 15, 1994  H.O.  0002  Added CADUL support
;   Oct 18, 1994  P.F.  0003  Added include of macro.h
;   Nov 21, 1994  P.F.  0004  Include i386.h, if IC386 is used
;                             Use builtin.h instead of ix86.h, if CADUL is used
;   Dec 19, 1994  P.F.  0005  Added typedef for 'selector', for not-Intel and
;                             not-CADUL C compiler
;   Oct 25, 1995  J.R.  0006  Don't define I/O commands when the according
;                             Borland includes are already included.
;                             (Borland includes define _PORT_DEFS).
;   Jan 10, 1996  J.R.  0007  Avoid collisions with Borland's DOS.H reagarding
;                             disable, _disable, enable and _enable.
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _MISC86_H_
#define _MISC86_H_

#ifndef _MACRO_H_
#include <macro.h>
#endif /* _MACRO_H_ */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#ifndef _NOVERS
static const
char idstr_misc86_h [] =
{
        "\0"    "(C) SIEMENS AG 1994"   "\0"    /* In-code identification. */
        "\1"    "MISC86.H"              "\1"
		  "\2"    "0007"                  "\2"
        "\3"    "J.R."                  "\3"
};
#endif
#endif  /* defined(_ARCHITECTURE_) || defined(CADUL) */


#if defined(_ARCHITECTURE_) && !defined(CADUL)
#if _ARCHITECTURE_ >= 386
#include <i386.h>
#else
#include <i86.h>
#endif
#endif /* _ARCHITECTURE_ && !CADUL */

#if defined (CADUL)
#include <builtin.h>
#endif /* CADUL */

#if !defined(_ARCHITECTURE_) && !defined(CADUL)
typedef unsigned short          selector;
#endif /* !_ARCHITECTURE_ && !CADUL */

#if defined (__BORLANDC__)

#ifdef __cplusplus
    extern "C"
    {
#endif /* __cplusplus */

    /* BORLAND intrinsic for generating an interrupt */
    void                cdecl   __int__(int int_no) ;
#ifndef _PORT_DEFS
    /* BORLAND intrinsic for reading a byte from a port */
    unsigned char       cdecl   __inportb__ ( unsigned adr) ;
    /* BORLAND intrinsic for reading a word from a port */
    unsigned            cdecl   __inportw__ ( unsigned adr) ;
    /* BORLAND intrinsic for writing a byte from a port */
	 unsigned char       cdecl   __outportb__( unsigned adr, unsigned char val) ;
    /* BORLAND intrinsic for writing a word from a port */
    unsigned            cdecl   __outportw__( unsigned adr, unsigned val) ;
#endif /* _PORT_DEFS */
    /* BORLAND intrinsic for inserting any byte code */
    void                __emit__(unsigned char __byte, ...) ;

#ifdef __cplusplus
    }
#endif /* __cplusplus */


/* generate/cause an interrupt */
/* --------------------------- */
#ifdef __cplusplus
    inline void geninterrupt(int interruptnum)          /* BORLAND */
    {
        __int__(interruptnum) ;
    }
	 inline void causeinterrupt(unsigned char interruptnum)      /* Intel */
    {
        geninterrupt(interruptnum) ;
    }
#else /* !__cplusplus */
#  define geninterrupt(interruptnum)    __int__(interruptnum)           /* BORLAND */
#  define causeinterrupt(interruptnum)  geninterrupt(interruptnum)      /* Intel */
#endif /* __cplusplus */

/* read a byte from a port */
/* ----------------------- */
#ifndef _PORT_DEFS
#ifdef __cplusplus
    inline unsigned char inportb(int port)              /* BORLAND */
    {
        return __inportb__(port) ;
    }
    inline int inp(unsigned port)                       /* BORLAND */
    {
		  return inportb(port) ;
    }
    inline unsigned char inbyte(unsigned short port)    /* INTEL */
    {
        return inportb(port) ;
    }
#else /* !__cplusplus */
#define inportb(adr)            __inportb__(adr)        /* BORLAND */
#define inp(adr)                inportb(adr)            /* BORLAND */
#define inbyte(adr)             inportb(adr)            /* INTEL */
#endif /* __cplusplus */

/* read a word from a port */
/* ----------------------- */
#ifdef __cplusplus
    inline int inport(int port)                         /* BORLAND */
    {
        return __inportw__(port) ;
    }
	 inline unsigned inpw(unsigned port)                 /* BORLAND */
    {
        return inport(port) ;
    }
    inline unsigned int inword(unsigned short port)     /* INTEL */
    {
        return inport(port) ;
    }
#else /* !__cplusplus */
#define inport(adr)             __inportw__(adr)        /* BORLAND */
#define inpw(adr)               inport(adr)             /* BORLAND */
#define inword(adr)             inport(adr)             /* INTEL */
#endif /* __cplusplus */

/* write a byte to a port */
/* ---------------------- */
#ifdef __cplusplus
    inline void outportb(int port, unsigned char val)   /* BORLAND */
    {
		  __outportb__(port, val) ;
    }
    inline int outp(unsigned port, int val)             /* BORLAND */
    {
        return __outportb__(port, (unsigned char) val) ;
    }
    inline void outbyte(unsigned short port, unsigned char val) /* INTEL */
    {
        outportb(port, val) ;
    }
#else /* !__cplusplus */
#define outportb(adr,val)       __outportb__(adr,val)   /* BORLAND */
#define outp(adr,val)           outportb(adr,val)       /* BORLAND */
#define outbyte(adr,val)        outportb(adr,val)       /* INTEL */
#endif /* __cplusplus */

/* write a word to a port */
/* ---------------------- */
#ifdef __cplusplus
	 inline void outport(int port, int val)              /* BORLAND */
    {
        __outportw__(port, val) ;
    }
    inline unsigned outpw(unsigned port, unsigned val)  /* BORLAND */
    {
        return __outportw__(port, val) ;
    }
    inline void outword(unsigned short port, unsigned int val)  /* INTEL */
    {
        outportb(port, (unsigned char) val) ;
    }
#else /* !__cplusplus */
#define outport(adr,val)        __outportw__(adr,val)   /* BORLAND */
#define outpw(adr,val)          outport(adr,val)        /* BORLAND */
#define outword(adr,val)        outport(adr,val)        /* INTEL */
#endif /* __cplusplus */
#endif /* _PORT_DEFS */

/* disable hardware interrupts (CLI) */
/* --------------------------------- */
#ifdef __cplusplus
#ifndef disable
	 inline void disable()                               /* BORLAND/INTEL */
	 {
		  __emit__((char)(0xFA)) ;        // inline assembler not allowed here
	 }
#endif /* !disable */
#ifndef _disable
	 inline void _disable()                              /* BORLAND */
	 {
		  disable() ;
	 }
#endif /* !_disable */
#else /* !__cplusplus */
#ifndef disable
#define disable()               __emit__((char)(0xFA))  /* BORLAND/INTEL */
#endif /* !disable */
#ifndef _disable
#define _disable()              disable()               /* BORLAND */
#endif /* !_disable */
#endif /* __cplusplus */

/* enable hardware interrupts (STI) */
/* -------------------------------- */
#ifdef __cplusplus
#ifndef enable
	 inline void enable()                                /* BORLAND/INTEL */
	 {
		  __emit__((char)(0xFB)) ;        // inline assembler not allowed here
	 }
#endif /* !enable */
#ifndef _enable
	 inline void _enable()                               /* BORLAND */
	 {
		  enable() ;
	 }
#endif /* !_enable */
#else /* !__cplusplus */
#ifndef enable
#define enable()                __emit__((char)(0xFB))  /* BORLAND/INTEL */
#endif /* !enable */
#ifndef _enable
#define _enable()               enable()                /* BORLAND */
#endif /* !_enable */
#endif /* __cplusplus */

#endif /* __BORLANDC__ */


#endif /* _MISC86_H_ */
