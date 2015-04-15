/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : LOAD.H  
;   version     : 0009
;   contents    : Function, structure and error code definitions for the RMOS
;                 relocating task loader.
;   author      : W.K.
;   date        : Nov 11, 1990
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Function, structure and error code definitions for the RMOS
;                 relocating task loader.
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Nov 11, 1990  W.K.  0001  Original issue
;   Mar  4, 1991  W.K.  0002  Typedef inserted
;   Dec  4, 1992  W.S.  0003  New Header added
;   May 10, 1994  J.R.  0004  Error codes for PE format added.
;   Jul 14, 1994  P.F.  0005  Modification for flat memory model (RMOS3 only)
;   Dec 19, 1994  P.F.  0006  Include svc.h
;   Mar 01, 1996  J.R.  0007  Errorcode E_LD_TOO_MANY_OBJECTS for PE format
;                             added. This code means, that there are too many
;                             CODE, DATA and BSS sections; actually this limit
;                             is set to 10 and i haven't seen any working
;                             Borland programm with more than 3.
;   Mar 12, 1996  J.R.  0008  Dummy segments for ORGANON XDB added.
;                             Therefore reserved_word2 is used;
;                             reserved_word3 is used internally.
;                             The names of the structure members are not
;                             changed because a double definition in
;                             rcascii.c.
;   Feb 25, 1997  J.R.  0009  E_LD_OUT_OF_SEMAPHORES and
;                             E_LD_CATALOG_EXCEEDED added
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _LOAD_H_
#define _LOAD_H_

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
#ifndef _NOVERS
static const char       x_load_h_version_id [] =
{
        "\0"    "(C) SIEMENS AG 1994"   "\0"    /* In-code identification. */
        "\1"    "LOAD.H"                "\1"
        "\2"    "0009"                  "\2"
        "\3"    "W.K."                  "\3"
};
#endif
#endif


#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _SVC_H_
#include <svc.h>
#endif  /* _SVC_H_ */


#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
#pragma fixedparams ( stl_load, stl_free )
#pragma noalign ( loader_result )
#endif /* _ARCHITECTURE_ || CADUL */

#if defined _MSC_VER
#pragma pack(1)         /* set all to byte alignment */
#endif /* _MSC_VER */

#ifdef __BORLANDC__
#pragma option -a-      /* set all to byte alignment */
#endif /* __BORLANDC__ */
/* structure is double defined in rcascii.c */
struct loader_result { unsigned short    except_code ;
                       unsigned short    shareable ;
                       char              reserved_byte ;
                       unsigned short    reserved_word2 /* dummySegmentsForXDB */ ;
                       unsigned int      code_seg_offset ;
                       unsigned short    code_seg_base ;
                       unsigned int      stack_offset ;
                       unsigned short    stack_seg_base ;
                       unsigned int      stack_size ;
                       unsigned short    data_seg_base ;
                       char              num_more_slots ;
                       unsigned short    more_slots [1] ;
                       unsigned short    reserved_word3 ; /* used internally */
                       void _FAR         *reserved_pointer1 ;
                     } ;

typedef struct loader_result LOADER_RESULT;    

/* success */
#define E_LD_OK                    0

/* quasi success */
#define E_LD_NO_REG_INIT           0x8100
#define E_LD_NO_FIXUPS             0x8101

/* Errors which apply to all file formats */
#define E_LD_FILE_OPEN_FAIL        0x8110
#define E_LD_FILE_FORMAT           0x8111
#define E_LD_UNEXPECTED_EOF        0x8112
#define E_LD_DYNAMIC_MEMORY        0x8113
#define E_LD_ABSOLUTE              0x8114
#define E_LD_DALOC                 0x8115    /* stl_free() */
#define E_LD_NULL_POINTER          0x8116    /* stl_free() */
#define E_LD_OVERLAY               0x8117

#define E_LD_OUT_OF_SEMAPHORES     0x8158
#define E_LD_CATALOG_EXCEEDED      0x8159

/* Errors which apply only to the OMF86 LTL format. */
#define E_LD_RELOCATABLE           0x8120
#define E_LD_ILLEGAL_SEG           0x8121
#define E_LD_ILLEGAL_GRP           0x8122
#define E_LD_THREAD_FIXUP          0x8123
#define E_LD_SELF_REL_FIXUP        0x8124
#define E_LD_NON_SEG_FIXUP         0x8125
#define E_LD_EXTERNAL_FIXUP        0x8126
#define E_LD_NO_FRAME_FIXUP        0x8127
#define E_LD_REGISTER_FIXUP        0x8128

/* Errors which apply only to the OMF386 format. */
#define E_LD_PROCESSOR_TYPE        0x8130
#define E_LD_NON_EXECUTABLE        0x8131
#define E_LD_MULTI_LDT             0x8132
#define E_LD_GATES_PRESENT         0x8133
#define E_LD_NO_STACK_DESC         0x8134
#define E_LD_NULL_SEG_FIXUP        0x8135
#define E_LD_BAD_SEG_FIXUP         0x8136
#define E_LD_ACCESS_RIGHTS         0x8137
#define E_LD_ITERATE               0x8138

/* Errors which apply only to the OMF386 format. */
#define E_LD_FIXUP_FORMAT          0x8140
#define E_LD_USE16                 0x8141

/* Errors which apply only to the PE format. */
#define E_LD_SEEK                  0x8150
#define E_LD_DLL                   0x8151
#define E_LD_INVALID_DESCRIPTOR    0x8152
#define E_LD_TOO_MANY_OBJECTS      0x8153


int _FAR _FIXED stl_load ( char                 *file_name,
                           LOADER_RESULT _FAR   **lseg,
                           int                  poolid ) ;

int _FAR _FIXED stl_free ( LOADER_RESULT _FAR   **lseg ) ;


#if defined _MSC_VER
#pragma pack()          /* reset alignment to commandline specification */
#endif

#ifdef __BORLANDC__
#pragma option -a.      /* reset alignment to commandline specification */
#endif /* __BORLANDC__ */

#endif  /* _LOAD_H_ */
