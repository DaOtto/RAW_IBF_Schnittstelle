/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : RMOS.H  
;   version     : 0012
;   contents    : RMOS external definition
;   author      : W.S.
;   date        : Dec 04, 1992
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : RMOS external definition for use in C
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;                       0001  Original issue
;                       0002  Correct pointer declarations.
;                             Changed Table declarations from pointers to
;                             arrays of structures.
;                             Some const statements added.
;                       0003  xjmp_xover  included
;                       0004  x_srb_avail included
;                 W.S.  0005  xcatalog included
;                 W.S.  0006  xmonmod included
;                 W.S.  0007  x_init_ext, xhaloc, xhdaloc  included
;   Dec 04, 1992  W.S.  0008  New Header added
;   Jul 07, 1993  W.S.  0009  Avoid complications in case of multiple use
;   Mar 04, 1994  W.S.  0010  xphysadrp for RMOS3 DMA-Driver added 
;                             include prot.h
;   Jul 14, 1994  P.F.  0011  Corrected prototypes (added void)
;   Jan 10, 1995  P.F.  0012  Replaced far by _FAR
;                             Added conditional part to avoid conflicts with
;                             rmnuc.h
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _RMOS_H_
#define _RMOS_H_

#ifndef _PROT_H_
#include <prot.h>
#endif  /* _PROT_H_ */
#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

extern  const SEGMENT   xmtosds;        /* Data segment */
extern  const SEGMENT   xmtosgrom;      /* Global ROM segment */
extern  const WORD16    xversion;       /* Version of operating system */
extern  WORD16          xseq;           /* Sequence number for IRB's */
extern  void    _FAR *  xpointer;       /* Pointer for common purposes */
extern  OFFSET          xoffset;        /* General purpose offset of xpointer */
extern  SEGMENT         xsegment;       /* General purpose segment of xpointer */
extern  BYTE            xdevnum;        /* Current device number */
extern  BYTE            xdevunit;       /* Current device unit number */
extern  BYTE            xtunit;         /* Time interval unit code */
extern  BYTE            xtnum;          /* Number of time interval units */
extern  void    _FAR *  xerrmsg;        /* Error message transport address */
extern  BYTE            xpoolnum;       /* Pool number for block allocation */
extern  WORD            xblklen;        /* Length of block needed, bytes */
extern  WORD16          xtask;          /* Task-ID */
extern  BYTE            xpris;          /* Priority source options */
extern  BYTE            xpriv;          /* Priority to use */
extern  WORD            xp1;            /* Parameter 1 */
extern  WORD            xp2;            /* Parameter 2 */
extern  BYTE            xgrp;           /* Global event flag group ID */
extern  WORD            xflags;         /* Event flag mask  */
extern  BYTE            xbox;           /* Local mailbox ID */
extern  BYTE            xgenb;          /* General purpose BYTE */
extern  WORD16          xgenw;          /* General purpose WORD16 */
extern  WORD32          xgend;          /* General purpose WORD32 */
extern  SEGMENT         xseg;           /* Selector for S-STATE routines */
extern  WORD32          xseglim;        /* Segment limit for S-STATE routines */
extern  BYTE            xmonmod;        /* Debugger Monitor Mode Indicator*/
extern  WORD32          x_init_ext;     /* for initialization */
extern  WORD            x_srb_avail;    /* Available SRB's */

#ifndef _RM_DRIVER_FLAG_
#define _RM_DRIVER_FLAG_
extern  IRB     _FAR *  xcirb;          /* Driver interface current IRB */
extern  DCB     _FAR *  xdcb;           /* Driver interface actual DCB */
extern  UCB     _FAR *  xucb;           /* Driver interface actual UCB */
extern  STATUS          xstatus;        /* Status transport variable */
#endif /* _RM_DRIVER_FLAG_ */

extern  DCD     const   x_dcd_table[];  /* DCD table structure */
extern  UCD     const   x_ucd_table[];  /* UCD table structure */
extern  UCB             x_ucb_table[];  /* UCB table structure */
extern  DCB             x_dcb_table[];  /* DCB table structure */

extern  void    xhaloc(void);           /* Allocate memory from pool */
extern  void    xhdaloc(void);          /* Return memory to pool */
extern  void    xcatalog(void);         /* Catalog function */
extern  void    xsystem(void);          /* Switch from DI-State to S-State */
extern  void    xexsys(void);           /* Exit S-State */
extern  void    xaloc(void);            /* Allocate memory from pool */
extern  void    xdaloc(void);           /* Return memory to pool */
extern  void    xdeltmb(void);          /* Delete TMB */
extern  void    xdevdata(void);         /* Calculate offset of UCB and DCB */
extern  void    xdqtmb(void);           /* Remove TMB */
extern  void    xdword(void);           /* Calculate address from offset */
extern  void    xgetsmr(void);          /* Allocate System memory */ 
extern  void    xiodone(void);          /* Exit I/O request type I */
extern  void    xjmp_xover(void);       /* Exit I/O request type II from "c" */
extern  void    xover(void);            /* Exit I/O request type II */
extern  void    xputsmr(void);          /* Return system memory */
extern  void    xqsetuns(void);         /* Queue start task for unexpected intr */
extern  void    xqsirb(void);           /* Put actual IRB in serial queue */
extern  void    xqpirb(void);           /* Put actual IRB in parallel queue */
extern  void    xqstrt(void);           /* Queue start task request */
extern  void    xqtmb(void);            /* Put TMB in queue */
extern  void    xrecv(void);            /* Get message from mailbox */
extern  void    xref(void);             /* Reset global event flag */
extern  void    xsef(void);             /* Set global event flag */
extern  void    xsend(void);            /* Send message to mailbox */
extern  void    xsetuns(void);          /* Start task for unexpected interrupts */
extern  void    xtef(void);             /* Test global event flag */
extern  void    xtimeout(void);         /* Install timeout for device type II */
extern  void    xerrlog(void);          /* Pass error message */
extern  void    xphysadr(void);         /* calculate physical address */
#if RM3
extern  void    xphysadrp(void);        /* calculate physical address (paged system) */
#endif
extern  void    xcreatedesc(void);      /* Get new descriptor */
extern  void    xchangedesc(void);      /* Change descriptor */
extern  void    xdeldesc(void);         /* Delete descriptor */
extern  void    xchangedesaccess(void); /* Change descriptor access rigths */

#endif /* _RMOS_H_ */
