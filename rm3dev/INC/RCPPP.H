/*****************************************************************************/
/*                                                                           */
/*   Filename:  RCPPP.H                                                      */
/*                                                                           */
/*   Author:    J. Stephan           Department:      A&D SE E41             */
/*   Date:      19.01.1999                                                   */
/*                                                                           */
/*   Development Kit / Compiler :  C-Compiler Organon V6.x                   */
/*                                                                           */
/*   Copyright (C) Siemens AG 1999. All rights reserved.                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Description: Configuration Header for PPP-Driver.                       */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Modifications:                                                          */
/*                                                                           */
/*----------+-------------+-----+--------------------------------------------*/
/*  Date    |    Author   | Sign|                Description                 */
/*----------+-------------+-----+--------------------------------------------*/
/* 19.01.99 | J. Stephan  |     | original issue                             */
/*          |             |     |                                            */
/*          |             |     |                                            */
/*----------+-------------+-----+--------------------------------------------*/
/*          |             |     |                                            */
/*          |             |     |                                            */
/*          |             |     |                                            */
/*          |             |     |                                            */
/*          |             |     |                                            */
/*----------+-------------+-----+--------------------------------------------*/
/*                                                                           */
/*****************************************************************************/

#ifndef _RCPPP_H_
#define _RCPPP_H_

#include <rmconf.h>
#include <rmtypes.h>
#include <typedefs.h>

/* ------------------------------------------------------------------------- */
/* Definition of function prototypes                                         */
/* ------------------------------------------------------------------------- */

#ifdef _MSC_VER
#pragma pack(1)         /* set all to byte alignment */
#endif

#if defined (_ARCHITECTURE_)
#pragma fixedparams("pppdrv_task")
#endif

extern void _FAR _FIXED pppdrv_task(void);       

#if defined (_ARCHITECTURE_)
#pragma fixedparams("RcInitPPPenv")
#endif

extern int _FIXED _FAR RcInitPPPenv(uint  IOBaseAddr,
                                    uint  IRQ,       
                                    ulong Baudrate,  
                                    char  Parity,   
                                    uint  Databits,  
                                    uint  Stopbits,  
                                    uint  FIFO,     
                                    uint  ConsoleFlag);

#ifdef _MSC_VER
#pragma pack()          /* reset alignment to commandline specification */
#endif


/* ------------------------------------------------------------------------- */
/* Definition of catalog-names for systemresources (do not change)           */
/* ------------------------------------------------------------------------- */

#define PPPDRV_TASK     "PPPDRV_TASK"      /* name of driver-task            */
#define PPPDRV_QMBX     "PPPDRV_QMBX"      /* name of Startup-Mailbox        */

/* ------------------------------------------------------------------------- */
/* Misc. definitions for driver parts (may be changed)                       */
/* ------------------------------------------------------------------------- */

#define PPPDRV_TASK_PRI     255            /* priority of drivertask         */
#define PPPDRV_TASK_STACK   4000           /* stacksize drivertask           */

#endif /* _RCPPP_H_ */
