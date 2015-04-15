/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : _DEFS.H
;   version     : 0001
;   contents    : Some definitions for use with BORLAND C++ V4.0.
;   author      : J.R.
;   date        : Dec 20, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Common definitions for pointer size and calling conventions.
;
;   RMOS2/3 plus BORLAND C++ V4.0
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;  Dec 20, 1994   J.R.  0001  Original issue
;
;---END OF MODIFICATION HEADER-------------------------------------------------
;
;---NOTE(S) -------------------------------------------------------------------
;
;---END OF NOTE(S) ----------------------------------------------------------*/

#if !defined(__DEFS_H)
#define __DEFS_H

/************************************************************************/
/*									*/
/*		C A L L I N G   C O N V E N T I O N S			*/
/*		=====================================			*/
/*									*/
/************************************************************************/

/*----------------------------------------------------------------------*/
/*   _RTLENTRY	Specifies the calling convention used by the RTL	*/
/*----------------------------------------------------------------------*/
#define _RTLENTRY	__cdecl
#ifdef __WIN32__
#   define _EXPFUNC
#else	// NOT __WIN32__
#   define _EXPFUNC	__far
#endif	// __WIN32__


/************************************************************************/
/*									*/
/*	P R O T O T Y P E S   F O R   E R R O R H A N D L I N G		*/
/*	=======================================================		*/
/*									*/
/************************************************************************/

#ifdef __WIN32__
#ifdef __cplusplus
extern "C" {
#endif

// Prototype for configurable error message
void _ErrorMessage(const char * _message) ;

#ifdef __WIN32__
// Prototypes for init and free of C++ tasks
int rm_initcpp() ;
void rm_freecpp() ;
#endif // __WIN32__

#ifdef __cplusplus
}
#endif
#endif // __WIN32__


#endif  /* __DEFS_H */
