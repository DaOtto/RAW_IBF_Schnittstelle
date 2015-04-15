/*--FILE HEADER-(set tabulator to 8)-------------------------------------------
;
;   filename    : RM3DOS.H
;   version     : 0021
;   contents    : Include file for RMOS3 MS-DOS interface.
;   author      : P.J./G.B.
;   date        : Oct 1, 1993
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   RMOS3 with VM86
;
;---MODIFICATIONS--------------------------------------------------------------
;
;   03.12.91    P.J.    0012    - Return value of x_dos_cpyin() changed
;                                 from (int) to (char far *)
;                               - dta_addr parameter to x_dos_intx_dta()
;                                 changed from (int) to (char near *).
;                               - addr parameter to x_dos_cpyout()
;                                 changed from (int) to (char near *).
;
;   16.01.92    P.J.    0013    - dta_addr parameter to x_dos_intx_dta()
;                                 changed to (char far *).
;                               - addr parameter to x_dos_cpyout()
;                                 changed to (char far *).
;
;   08.03.93    P.J.    0014    - x_vm_win_seg_base() added
;
;   29.04.93    P.J.    0015    - x_dos_map_selector() and
;                                 x_dos_map_selector() added
;
;   09.05.93    P.J.    0016    - x_dos_intx_dta() returns int
;
;   04.08.93    P.J.    0017    - x_dos_unmap_pointer()
;                                 x_dos_at_warmstart()
;                                 x_dos_rm_warmstart()
;                                 added
;
;   13.08.93    G.B.    0018    - Prototypes adjusted to documentation
;
;   18.08.93    G.B.    0019    - x_dos_do_reboot() added
;
;   01.10.93    G.B.    0020    - Pragmadefinitions introduced
;   01.09.95	W.K.	0021	- Flat definitions added
;
;---END OF FILE HEADER-------------------------------------------------------*/

#ifndef _RM3DOS_H_
#define _RM3DOS_H_
#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _STDDEF_H_
#include <stddef.h>
#endif  /* _STDDEF_H_ */

/*****************************************************************************/
/*                                                                           */
/* Inline identification                                                     */
/*                                                                           */
/*****************************************************************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
#ifndef _NOVERS
const static char idstr_rm3dos_h [] =
      "\000" "(C) SIEMENS AG 1995" "\000"
      "\001" "RM3DOS.H"            "\001"
      "\002" "0021"                "\002"
      "\003" "W.K."                "\003";
#endif
#endif  /* defined(_ARCHITECTURE_) || defined(CADUL) */

/*****************************************************************************/
/*                                                                           */
/* Pragmadefinitions                                                         */
/*                                                                           */
/*****************************************************************************/
#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
#pragma fixedparams ( x_vm_win_seg_base,  x_vm_wincond_start   )
#pragma fixedparams ( x_dos_cpyin,        x_dos_cpyout         )
#pragma fixedparams ( x_dos_map_selector, x_dos_unmap_selector )
#pragma fixedparams ( x_dos_map_pointer,  x_dos_unmap_pointer  )
#pragma fixedparams ( x_dos_intx_dta,     x_dos_test_warm_start)
#pragma fixedparams ( x_dos_at_warmstart, x_dos_rm_warmstart   )
#pragma fixedparams ( x_dos_do_reboot                          )
#pragma fixedparams ( x_dos_interrupt_rmos3,  x_dos_interrupt_dos       )
#pragma fixedparams ( x_dos_interrupt_status, x_dos_reserve_io          )
#pragma fixedparams ( x_dos_free_io,          x_dos_get_io_bitmap       )

#pragma align ( word_register_area = 1)
#pragma align ( byte_register_area = 1)
#endif  /* _ARCHITECTURE_ || CADUL */

#ifdef __BORLANDC__
#pragma option -a-      /* set all to byte alignment */
#endif

/*****************************************************************************/
/*                                                                           */
/* Structures                                                                */
/*                                                                           */
/*****************************************************************************/

struct word_register_area
{
  unsigned short ax ;
  unsigned short bx ;
  unsigned short cx ;
  unsigned short dx ;
  unsigned short si ;
  unsigned short di ;
  unsigned short bp ;
  unsigned short ds ;
  unsigned short es ;
  unsigned short flags ;
} ;

struct byte_register_area
{
  unsigned char al, ah ;
  unsigned char bl, bh ;
  unsigned char cl, ch ;
  unsigned char dl, dh ;
} ;

union REGS
{
  struct word_register_area x;
  struct byte_register_area h;
} ;

/*****************************************************************************/
/*                                                                           */
/* Prototypes                                                                */
/*                                                                           */
/*****************************************************************************/
#define x_dos_intx(int,inr,outr) x_dos_intx_dta ( int,  inr, outr, NULL )
#define x_dos_int(inr,outr)     x_dos_intx_dta ( 0x21, inr, outr, NULL )

#ifdef __cplusplus
extern "C" {
#endif
extern char  _FAR *_FIXED _FAR x_dos_cpyin   ( char _FAR *buffer,
                                              int       len ) ;

extern int _FIXED _FAR        x_dos_cpyout  ( char _FAR *addr,
                                              char _FAR *buffer,
                                              int        len ) ;

extern int _FIXED _FAR       x_dos_intx_dta ( int             intnum,
                                              union REGS _FAR *inregs,
                                              union REGS _FAR *outregs,
                                              char _FAR       *dta_addr ) ;

extern unsigned long _FIXED _FAR x_dos_map_pointer ( void _FAR    *r_ptr,
                                                     unsigned int   size ) ;
extern void _FIXED _FAR        x_dos_unmap_pointer ( unsigned long  w_ptr ) ;
#if !RMFLAT
extern int            far  x_dos_test_warm_start   ( unsigned *restart_ctr_u ) ;

extern void far *     far  x_vm_win_seg_base       ( unsigned short win_sel ) ;

extern unsigned short far  x_dos_map_selector      ( unsigned short r_sel ) ;
extern void           far  x_dos_unmap_selector    ( unsigned short w_sel ) ;

extern int            far  x_dos_at_warmstart      ( unsigned int task_id ) ;
extern void           far  x_dos_rm_warmstart      ( unsigned int task_id ) ;

extern void           far  x_dos_do_reboot         ( void );

extern void           far  x_vm_wincond_start      ( unsigned uNumberOfTasks,
                                                     unsigned uUnsolicitedTask ) ;

extern unsigned short far x_dos_map_physical_memory ( unsigned physical_start,
                                               unsigned physical_length,
                                               unsigned *linear_start_p ) ;

extern int            far x_dos_interrupt_rmos3     ( unsigned vector ) ;
extern int            far x_dos_interrupt_dos       ( unsigned vector ) ;
extern int            far x_dos_interrupt_status    ( unsigned vector ) ;
extern int            far x_dos_reserve_io          ( unsigned port,
                                               unsigned count ) ;
extern int            far x_dos_free_io             ( unsigned port,
                                               unsigned count ) ;
extern void           far x_dos_get_io_bitmap       ( void     *buffer,
                                                      unsigned *max_port ) ;
#endif /* end RMFLAT */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef __BORLANDC__
#pragma option -a.      /* reset alignment to commandline specification */
#endif

#endif /* _RM3DOS_H_ */
