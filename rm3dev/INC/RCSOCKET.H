/*****************************************************************************/
/*                                                                           */
/*   Filename:  RCSOCKET.H                                                   */
/*                                                                           */
/*   Author:    J. Stephan           Department:      A&D SE E41             */
/*   Date:      18.02.1998                                                   */
/*                                                                           */
/*   Development Kit / Compiler :  C-Compiler Organon V6.x                   */
/*                                                                           */
/*   Copyright (C) Siemens AG 1998. All rights reserved.                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Description: Configuration Header for RMOS3 TCP/IP Stack and Sockets.   */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Modifications:                                                          */
/*                                                                           */
/*----------+-------------+-----+--------------------------------------------*/
/*  Date    |    Author   | Sign|                Description                 */
/*----------+-------------+-----+--------------------------------------------*/
/* 18.02.98 | J. S.       |     | original issue                             */
/* 05.11.98 | R. S.       |     | added GetIEEEAddr                          */
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

#ifndef _RCSOCKET_H_
#define _RCSOCKET_H_

#include <rmconf.h>
#include <rmtypes.h>
#include <typedefs.h>

/***** alignment and calling convention **********************************/

  #if ((defined(_ARCHITECTURE_)) || (defined(CADUL)))
  /* Intel C compiler iC386 or CAD-UL C compiler CC386 */
    #pragma align(_IEEEADDR=1)
  #endif

  #ifdef __BORLANDC__                              /* Borland C compiler */
    #pragma option -a-
  #endif

/*
**  ---- Errorcodes for GetIEEEAddr ----
*/

#define IEEEADDR_NO_ERR                 0 /* no errors                       */
#define IEEEADDR_ERR_ETHDEV_NOT_FOUND  -1 /* Devicename of Ethernetdriver not*/
                                          /* found in catalog                */
#define IEEEADDR_ERR_TCPDRV_STATUS     -2 /* Internal TCP-Driver Error       */
#define IEEEADDR_INTERNAL_ERROR        -3 /* RMOS Internal Error             */

/*
**  ---- Structure for GetIEEEAddr ----
*/

typedef struct _IEEEADDR
{
        unsigned char OrgIEEEAddr[6];
        unsigned char CurIEEEAddr[6];
}IEEEAddrStruct;


/* ------------------------------------------------------------------------- */
/* Definition of function prototypes                                         */
/* ------------------------------------------------------------------------- */

#if defined (_ARCHITECTURE_)
#pragma fixedparams(RcInitTCPIPenv)
#pragma fixedparams(TCPIPConfigDriver)
#pragma fixedparams(GetIEEEAddr)
#pragma fixedparams(x_cr_cfgsocket)
#pragma fixedparams(x_socket2_entry, x_sk_socket)
#endif

extern void _FIXED _FAR x_socket2_entry(void);
extern int  _FIXED _FAR x_sk_socket   (int af, int type, int protocol);
extern void _FIXED _FAR x_cr_cfgsocket(void);
extern int  _FIXED _FAR RcInitTCPIPenv(void);
extern int  _FIXED _FAR TCPIPConfigDriver(char *DeviceName,
                                          uint UnitID,
                                          void *MACaddr,
                                          ulong IPaddr,
                                          ulong NetMask);

extern int _FIXED _FAR GetIEEEAddr(char            *DeviceName,
                                    unsigned int     UnitID,
                                    IEEEAddrStruct  *pIEEEAddr);

#endif /* _RCSOCKET_H_ */
