/*--FILE HEADER---------------------------------------------------------------
;
;   filename    : RMNAMES.H
;   version     : 00044
;   contents    : Names of cataloged tasks, drivers and units
;   author      : K.P.H.
;   date        : Feb 14, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT---------------------------------------------
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER--------------------------------------------------------
;
;---MODIFICATION HEADER-------------------------------------------------------
;
;   Jan 12, 1995  K.P.H. 0001  Original issue
;   Mar 30, 1995  K.P.H. 0002  Additioinal changes for RMOS2
;   May 15, 1995  K.P.H. 0003  Corrected some names
;   Feb 14, 1996  K.P.H. 0004  Modification for RMOS V3.12
;
;---END OF MODIFICATION HEADER----------------------------------------------*/

#ifndef _RMNAMES_H_
#define _RMNAMES_H_

/*---------------------------------------------------------------------------*/
/* task, driver and unit names for catalog                                   */
/*---------------------------------------------------------------------------*/

/* name of tasks */
#define INITTASK "RMOSCONF"
#define CLIDPAT  "CLI_DPAT"
#define DEBDPAT  "DEB_DPAT"
#define ERRLOG   "ERRLOG"
#define EXCEPTION "EXCEPTION"
#define REPTASK  "REP"
#define REPXTASK "REPX"
#define RMTASK   "REMOTE"
#define DEBTASK  "DEB_"
#define DOSTASK  "DOS"
#define DFSTASK  "DOS_HSFS"

/* system device and unit */
#define SYSTEMCONSOLE "SYSCON"

/* FLOPPY DISK driver & unit name */
#define FD0DRV  "FD0"
#define FD0UNIT "FD0_"              /* drive name is completed with */
                                    /* driver number during init */

/* HARD DISK driver & unit name */
#define HD0DRV  "HD0"
#define HD0UNIT "HD0_"              /* drive name is completed with */
                                    /* driver number during init */

/* RAM DISK driver & unit name */
#define RAMDRV  "RAM"
#define RAMUNIT "RAM_0"
#define RAM32DRV  "RAM32"
#define RAM32UNIT "RAM32_0"

/* BYT driver & unit names */
#define BYTDRV  "BYT"
#define BYTEGA1 "BYT_EGA_0"
#define BYTEGA2 "BYT_EGA_1"
#define BYTEGA3 "BYT_EGA_2"
#define BYTEGA4 "BYT_EGA_3"
#define BYTCOM1 "BYT_COM1"
#define BYTCOM2 "BYT_COM2"
#define BYTLPT1 "BYT_LPT1"
#define BYTLPT2 "BYT_LPT2"
#define BYTLPT3 "BYT_LPT3"
#define BYT8530A "BYT_CHA"
#define BYT8530B "BYT_CHB"

/* CRT driver & unit names */
#define CRTDRV  "CRT"
#define CRTCOM1 "CRT_COM1"
#define CRTCOM2 "CRT_COM2"

/* 3964 driver & unit names */
#define COMDRV   "\x04""3964"
#define COMCOM1  "\x09""3964_COM1"
#define COMCOM2  "\x09""3964_COM2"
#define COM8530A "\x0A""3964_8530A"
#define COM8530B "\x0A""3964_8530B"

/* VC driver & unit names */
#define VCDRV  "VC"
#define VCUNIT "VC_"              /* name is completed with */
                                  /* unit number during init */

#endif /* _RMNAMES_H_ */

