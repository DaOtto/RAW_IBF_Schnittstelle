/*--FILE HEADER-(set tabulator to 4)-------------------------------------------
;
;   filename    : DRV_COM.H  
;   version     : 0002
;   contents    : Definition of RMOS driver common parts
;   author      : W.S.
;   date        : Dec 04, 1992
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Definition of RMOS driver common parts for use in C
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 04, 1992  W.S.  0002  New Header added
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _DRV_COM_H_
#define _DRV_COM_H_

/*
**	DCD: (D)evice (C)ontrol (D)efinition block
*/

typedef struct dcd
{
	OFFSET		dcd_ucd;	/* Link to first unit UCD */
	BYTE		dcd_units;	/* Number of units */
	BYTE		dcd_shr;	/* Sharing device number (0ffh=none) */
	PTR_VOID	dcd_init;	/* Address of initialization routine */
	PTR_VOID	dcd_svc;	/* Address of SVC request handler */
	BYTE		dcd_flags;	/* Driver flags (see below) */
	BYTE		dcd_fmax;	/* Maximum function code for driver */
	WORD		dcd_res;	/* Expansion bytes (reserved) */
} DCD;

#define	DCD_SIZE	sizeof(DCD)	/* Size of DCD in bytes */	

/*
**	Flags for field "dcd_flags" of DCD
*/

#define DFL_PARA	1	/* Parallel driver */
#define DFL_TYPE2	2	/* Type II driver */
#define DFL_DORMANT	4	/* Driver dormant */

#if !RM3
#	define BLK_SIZE	128	/* Size of UCD/UCB/DCB block for RMOS2 */
#else
#	define BLK_SIZE	256	/* Size of UCD/UCB/DCB block for RMOS3 */
#endif	

/*
**	UCD: (U)nit (C)ontrol (D)efinition block
*/

typedef struct ucd_head
{
	BYTE		ucd_pid;	/* RESERVED */
	BYTE		ucd_intno;	/* Interrupt number */
	POINTER		ucd_intadr;	/* Interrupt vector address */
	WORD16		ucd_uns;	/* Unsolicited interrupt task number */
} UCD_HEAD;

typedef struct ucd_blk
{
	UCD_HEAD	ucd_header;	/* Common header for UCD */
	BYTE		ucd_port[BLK_SIZE-sizeof(UCD_HEAD)];/* Unit ROM par. */
} UCD_BLK;

#define	UCD_SIZE	sizeof(UCD_BLK)	/* Size of UCD in bytes */	

/*
**	DCB: (D)evice (C)ontrol dynamic (B)lock
*/

typedef struct dcb_head
{
	OFFSET		dcb_link;	/* Forward link or 0 */
	BYTE		dcb_id;		/* Device number */
	BYTE 		dcb_sts;	/* Driver status byte */
	OFFSET		dcb_qirb;	/* Link to driver IRB queue */
	OFFSET		dcb_cirb;	/* Link to driver current IRB */
	OFFSET		dcb_ucb;	/* Link to first unit UCB */
	OFFSET		dcb_dcd;	/* Link to driver DCD */
} DCB_HEAD;

typedef struct dcb_blk
{
	DCB_HEAD	dcb_header;	/* Common header for DCB */
	BYTE		dcb_gpr[BLK_SIZE-sizeof(DCB_HEAD)]; /* Driver param */
} DCB_BLK;

#define	DCB_SIZE	sizeof(DCB_BLK)	/* Size of DCB in bytes */	

/*
**	UCB: (U)nit (C)ontrol dynamic (B)lock
*/

typedef struct ucb_head
{
	OFFSET		ucb_link;	/* Forward link or 0 */
	BYTE		ucb_unit;	/* Unit number */
	BYTE		ucb_sts;	/* Unit status byte */
	OFFSET		ucb_qirb;	/* Link to unit IRB queue */
	OFFSET		ucb_cirb;	/* Link to unit current IRB */
	WORD16		ucb_seg;	/* segment of ucd */
	OFFSET		ucb_dcb;	/* Link to driver DCB */
	OFFSET		ucb_ucd;	/* Link to unit UCD */
	OFFSET		ucb_tcb;	/* Link to reservers TCB or 0 */
} UCB_HEAD;

typedef struct ucb_blk
{
	UCB_HEAD	ucb_header;	/* Common header for UCB */
	BYTE		ucb_gpr[BLK_SIZE-sizeof(UCB_HEAD)];/* Unit RAM param */
} UCB_BLK;

#define	UCB_SIZE	sizeof(UCB_BLK)	/* Size of UCB in bytes */	

/*
**	IRB: (I)/O (R)equest (B)lock
*/

typedef	struct irb
{
	OFFSET		irb_link;	/* Link to next IRB or 0 */
	WORD16		irb_pri;	/* Priority of current IRB */
	OFFSET		irb_tcb;	/* Link to current TCB */
	OFFSET		irb_ucb;	/* Link to current UCB */
	OFFSET		irb_tmb;	/* Link to current TMB */
	BYTE		irb_rio;	/* SVC operation code for RIO */
	BYTE		irb_funct;	/* RIO function code */
	BYTE		irb_device;	/* RIO device number */
	BYTE		irb_unit;	/* RIO unit number */
	BYTE		irb_grp;	/* RIO flag group ID */
	WORD		irb_flags;	/* RIO flag mask */
	POINTER		irb_status;	/* RIO pointer to status buffer */
	POINTER		irb_bufr;	/* RIO pointer to parameter list */ 
	WORD16		irb_seq;	/* IRB sequence number */
} IRB;

#define	IRB_SIZE	sizeof(IRB)	/* Size of IRB in bytes */	

/*
**	TMB: (T)imer (M)onitor Block
*/

typedef struct tmb
{
	OFFSET		tmb_link;	/* Forward link or 0 */
#if !RM3
	WORD16		tmb_mtime;	/* Absolute expiration time (middle) */
	WORD16		tmb_ltime;	/* Absolute expiration time (low) */
#else
	WORD32		tmb_ltime;	/* Absolute expiration time (low) */
	WORD32		tmb_htime;	/* Absolute expiration time (high) */
#endif
	BYTE		tmb_type;	/* TMB type (1 = driver timeout) */
	BYTE		tmb_space1;	/* TMB structure space (type 1) */
	OFFSET		tmb_ucb;	/* Link to driver unit UCB (type 1) */
	POINTER		tmb_sadr;	/* Address timeout routine (type 1) */
	WORD		tmb_space2;	/* TMB structure space (type 1) */
#if !RM3
	WORD16		tmb_htime;	/* Absolute expiration time (high) */
#endif
} TMB;	

#define	TMB_SIZE	sizeof(TMB)	/* Size of TMB in bytes */	

#endif /* _DRV_COM_H_ */

