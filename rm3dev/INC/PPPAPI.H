/*****************************************************************************/
/*                                                                           */
/*   Filename:  PPPAPI.H                                                     */
/*                                                                           */
/*   Author:    J.S.                 Department:      A&D SE E41             */
/*   Date:      19.01.1999                                                   */
/*                                                                           */
/*   Development Kit / Compiler :  C-Compiler Organon V6.x                   */
/*                                                                           */
/*   Copyright (C) Siemens AG 1999. All rights reserved.                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Description: Header file for PPP-Driver-API                             */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Modifications:                                                          */
/*                                                                           */
/*----------+-------------+-----+--------------------------------------------*/
/*  Date    |    Author   | Sign|                Description                 */
/*----------+-------------+-----+--------------------------------------------*/
/* 19.01.99 | J.S.        |     | original issue                             */
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

#ifndef _PPPAPI_H_
#define _PPPAPI_H_

#ifndef NULL   
#define NULL ((void *) 0);       
#endif

/* ========================================================================= */
/*                                                                           */
/* Errorcodes                                                                */
/*                                                                           */
/* ========================================================================= */

#define PPP_DRV_OK                    0  /* no error                         */
#define PPP_DRV_ERR_PARAM            -1  /* parameter error                  */
#define PPP_DRV_ERR_TIMEOUT          -2  /* timeout-error                    */
#define PPP_DRV_ERR_SYSTEM           -3  /* RMOS-System error                */
#define PPP_DRV_ERR_CANCEL           -4  /* Request canceld                  */
#define PPP_DRV_ERR_CHANNEL          -5  /* wrong active channel             */
#define PPP_DRV_ERR_NO_DRIVER        -6  /* general transmit error           */

/* ========================================================================= */
/*                                                                           */
/* Prototypes.                                                               */
/*                                                                           */
/* ========================================================================= */


#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma fixedparams("PPPDriverSetChannel")
#pragma fixedparams("PPPDriverGetModemStatus")
#pragma fixedparams("PPPDriverConfigEvent")
#pragma fixedparams("PPPDriverGetBufferStatus")
#pragma fixedparams("PPPDriverFlush")
#pragma fixedparams("PPPDriverReset")
#pragma fixedparams("PPPDriverRead")
#pragma fixedparams("PPPDriverWrite")
#endif

extern int _FIXED _FAR PPPDriverSetChannel(uint Channel);
extern int _FIXED _FAR PPPDriverGetModemStatus(ushort *pModemStatus);

#define MODEM_STATUS_DCTS  0x01
#define MODEM_STATUS_DDSR  0x02
#define MODEM_STATUS_TERI  0x04
#define MODEM_STATUS_DDCD  0x08
#define MODEM_STATUS_CTS   0x10
#define MODEM_STATUS_DSR   0x20
#define MODEM_STATUS_RI    0x40
#define MODEM_STATUS_DCD   0x80

extern int _FIXED _FAR PPPDriverConfigEvent(uint FlagsID,uint FlagMask);
extern int _FIXED _FAR PPPDriverGetBufferStatus(ushort *pRecvBufferCnt);
extern int _FIXED _FAR PPPDriverFlush(void);
extern int _FIXED _FAR PPPDriverReset(void);
extern int _FIXED _FAR PPPDriverRead(void    *pBuffer,
                                     ushort   Length,
                                     uchar    EndChar,
                                     ulong    Timeout,
                                     ushort  *pIOCount);

extern int _FIXED _FAR PPPDriverWrite(void    *pBuffer,
                                      ushort   Length);


#endif  /* _PPPAPI_H_ */
