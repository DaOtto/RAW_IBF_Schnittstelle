/*****************************************************************************/
/*                                                                           */
/* Project:    #######  ######  ##   ##  ######  ######    ###               */
/*             ##         ##    ##   ##  #    #  ##       ####               */
/*             #######    ##    #######  ######  ######  ## ##               */
/*             ##         ##    ##   ##       #  ##  ##     ##               */
/*             #######    ##    ##   ##  ######  ######     ##               */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Filename:  RCETH961.H                                                   */
/*                                                                           */
/*   Author:    J. Stephan           Department:      AUT E741               */
/*   Date:      22.10.1997                                                   */
/*                                                                           */
/*   Development Kit / Compiler :  C-Compiler Organon V6.x                   */
/*                                                                           */
/*   Copyright (C) Siemens AG 1997. All rights reserved.                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Description: Configuration Header for SMP16-COM291 Ethernet-Driver      */
/*                for use with RMOS3 V3.20                                   */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Modifications:                                                          */
/*                                                                           */
/*----------+-------------+-----+--------------------------------------------*/
/*  Date    |    Author   | Sign|                Description                 */
/*----------+-------------+-----+--------------------------------------------*/
/* 22.10.97 | J. Stephan  |     | original issue                             */
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

#ifndef _RCETH961_H_
#define _RCETH961_H_

#include <rmconf.h>
#include <rmtypes.h>
#include <typedefs.h>

/* ------------------------------------------------------------------------- */
/* Definition of function prototypes                                         */
/* ------------------------------------------------------------------------- */

#if defined (_ARCHITECTURE_)
#pragma fixedparams("eth961_task")
#pragma fixedparams("eth961_init1401")
#endif

extern void _FAR _FIXED eth961_task(void);       
extern int  _FAR _FIXED eth961_init1401(char *IoAddr, char *DprBase, char *AtxIrq,
                                        char console_flag);

#if defined (_ARCHITECTURE_)
#pragma fixedparams("RcInitETH961env")
#endif

extern int _FIXED _FAR RcInitETH961env(int argc, char *argv[]);

/* ------------------------------------------------------------------------- */
/* Definition of catalog-names for systemresources (do not change)           */
/* ------------------------------------------------------------------------- */

#define ETH961_TASK     "ETH961_TASK"      /* name of driver-task            */
#define ETH961_QMBX     "ETH961_QMBX"      /* name of Startup-Mailbox        */

/* ------------------------------------------------------------------------- */
/* Misc. definitions for driver parts (may be changed)                       */
/* ------------------------------------------------------------------------- */

#define ETH961_TASK_PRI     206            /* priority of drivertask         */
#define ETH961_TASK_STACK   4000           /* stacksize drivertask           */

#endif /* _RCETH961_H_ */
