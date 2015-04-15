/*****************************************************************************/
/*                                                                           */
/* Project:    #######  ######  ##   ##  ######  ######  #   #               */
/*             ##         ##    ##   ##  #       #        # #                */
/*             #######    ##    #######  ######  #####     #                 */
/*             ##         ##    ##   ##       #      #    # #                */
/*             #######    ##    ##   ##  ######  #####   #   #               */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Filename:  RcEth55X.h                                                   */
/*                                                                           */
/*   Author:    D. Cotard           Department:      A&D SE RD44             */
/*   Date:      17.12.1997                                                   */
/*                                                                           */
/*   Development Kit / Compiler :											 */
/*		CAD-UL CC386 - ANSI C Cross Optimizing Compiler - Version: V701D     */
/*                                                                           */
/*   Copyright (C) Siemens AG 1901. All rights reserved.                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Description: Driver for KSP-COM294/CPU076                               */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Modifications:                                                          */
/*                                                                           */
/*----------+-------------+-----+--------------------------------------------*/
/*  Date    |    Author   | Sign|                Description                 */
/*----------+-------------+-----+--------------------------------------------*/
/* 17.12.01 | D. Cotard   |  DC | original issue                             */
/*----------+-------------+-----+--------------------------------------------*/
/*                                                                           */
/*****************************************************************************/
#ifndef _RcEth55X_H_
#define _RcEth55X_H_

#include <rmtypes.h>
#include <typedefs.h>

/* ------------------------------------------------------------------------- */
/* Definition of function prototypes                                         */
/* ------------------------------------------------------------------------- */

#if defined (_ARCHITECTURE_)
#pragma fixedparams("ETH55X_task")
#endif

extern void _FAR _FIXED ETH55X_task(void);       

#if defined (_ARCHITECTURE_)
#pragma fixedparams("RcInitETH55Xenv")
#endif

extern int _FIXED _FAR RcInitETH55Xenv(void);	

/* ------------------------------------------------------------------------- */
/* Definition of catalog-names for systemresources (do not change)           */
/* ------------------------------------------------------------------------- */

#define ETH55X_TASK     "ETH55X_TASK"      /* name of driver-task            */
#define ETH55X_QMBX     "ETH55X_QMBX"      /* name of Startup-Mailbox        */

/* ------------------------------------------------------------------------- */
/* Misc. definitions for driver parts (may be changed)                       */
/* ------------------------------------------------------------------------- */

#define ETH55X_TASK_PRI     206            /* priority of drivertask         */
#define ETH55X_TASK_STACK   4000           /* stacksize drivertask           */

#endif /* _RcEth55X_H_ */

