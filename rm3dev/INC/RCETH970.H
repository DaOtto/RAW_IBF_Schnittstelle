/*****************************************************************************/
/*                                                                           */
/* Project:    #######  ######  ##   ##  ######  ######  ######              */
/*             ##         ##    ##   ##  #    #      ##  ##  ##              */
/*             #######    ##    #######  ######      ##  ##  ##              */
/*             ##         ##    ##   ##       #      ##  ##  ##              */
/*             #######    ##    ##   ##  ######      ##  ######              */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Filename:  RCETH970.H                                                   */
/*                                                                           */
/*   Author:    J. Stephan           Department:      A&D SE E41             */
/*   Date:      18.12.1997                                                   */
/*                                                                           */
/*   Development Kit / Compiler :  C-Compiler Organon V6.x                   */
/*                                                                           */
/*   Copyright (C) Siemens AG 1997. All rights reserved.                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Description: Configuration Header for SMP16-COM292 Ethernet-Driver      */
/*                for use with RMOS3 V3.20                                   */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Modifications:                                                          */
/*                                                                           */
/*----------+-------------+-----+--------------------------------------------*/
/*  Date    |    Author   | Sign|                Description                 */
/*----------+-------------+-----+--------------------------------------------*/
/* 18.12.97 | J. Stephan  |     | original issue                             */
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

#ifndef _RCETH970_H_
#define _RCETH970_H_

#include <rmconf.h>
#include <rmtypes.h>
#include <typedefs.h>

/* ------------------------------------------------------------------------- */
/* Definition of function prototypes                                         */
/* ------------------------------------------------------------------------- */

#if defined (_ARCHITECTURE_)
#pragma fixedparams("eth970_task")
#endif

extern void _FAR _FIXED eth970_task(void);       

#if defined (_ARCHITECTURE_)
#pragma fixedparams("RcInitETH970env")
#endif

extern int _FIXED _FAR RcInitETH970env(void);

/* ------------------------------------------------------------------------- */
/* Definition of catalog-names for systemresources (do not change)           */
/* ------------------------------------------------------------------------- */

#define ETH970_TASK     "ETH970_TASK"      /* name of driver-task            */
#define ETH970_QMBX     "ETH970_QMBX"      /* name of Startup-Mailbox        */

/* ------------------------------------------------------------------------- */
/* Misc. definitions for driver parts (may be changed)                       */
/* ------------------------------------------------------------------------- */

#define ETH970_TASK_PRI     206            /* priority of drivertask         */
#define ETH970_TASK_STACK   4000           /* stacksize drivertask           */

#endif /* _RCETH970_H_ */
