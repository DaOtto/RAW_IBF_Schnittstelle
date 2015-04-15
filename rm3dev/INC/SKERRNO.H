/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : SKERRNO.H
;   version     : 0002
;   contents    : Header file for RMOS socket library
;   author      : P.F.
;   date        : Jan 28, 1998
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file contains error definitions
;                 related to sockets
;
;   RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Jan 28, 1998  P.F.  0001  Original version
;   Feb 25, 1999  B.N.  0002  Added PPP support
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _SKERRNO_H_
#define _SKERRNO_H_

#define SLERRBASE       60              /* base value for socket errors     */
#define EWOULDBLOCK     (SLERRBASE+1)   /* I/O operation would block        */
#define EINPROGRESS     (SLERRBASE+2)   /* I/O operation now in progress    */
#define EALREADY        (SLERRBASE+3)   /* operation already in progress    */
#define EDESTADDRREQ    (SLERRBASE+4)   /* destination address required     */
#define EMSGSIZE        (SLERRBASE+5)   /* message too long                 */
#define EPROTOTYPE      (SLERRBASE+6)   /* protocol wrong type for socket   */
#define ENOPROTOOPT     (SLERRBASE+7)   /* bad protocol option              */
#define EPROTONOSUPPORT (SLERRBASE+8)   /* protocol not supported           */
#define ESOCKNOSUPPORT  (SLERRBASE+9)   /* socket type not supported        */
#define EOPNOTSUPP      (SLERRBASE+10)  /* operation not supported on socket*/
#define EPFNOSUPPORT    (SLERRBASE+11)  /* protocol family not supported    */
#define EAFNOSUPPORT    (SLERRBASE+12)  /* addr family not supp. by protocol*/
#define EADDRINUSE      (SLERRBASE+13)  /* address already in use           */
#define EADDRNOTAVAIL   (SLERRBASE+14)  /* can't assign requested address   */
#define ENETDOWN        (SLERRBASE+15)  /* network is down                  */
#define ENETUNREACH     (SLERRBASE+16)  /* network is unreachable           */
#define ENETRESET       (SLERRBASE+17)  /* network dropped conn. on reset   */
#define ECONNABORTED    (SLERRBASE+18)  /* software caused connection abort */
#define ECONNRESET      (SLERRBASE+19)  /* connection reset by peer         */
#define ENOBUFS         (SLERRBASE+20)  /* no buffer space available        */
#define EISCONN         (SLERRBASE+21)  /* socket is already connected      */
#define ENOTCONN        (SLERRBASE+22)  /* socket is not connected          */
#define ESHUTDOWN       (SLERRBASE+23)  /* can't send after socket shutdown */
#define ETOOMANYREFS    (SLERRBASE+24)  /* too many references              */
#define ETIMEDOUT       (SLERRBASE+25)  /* connection timed out             */
#define ECONNREFUSED    (SLERRBASE+26)  /* connection refused by target     */
#define EBUFTOOSMALL    (SLERRBASE+27)  /* mbuf too small for operation     */
#define ESMODEXISTS     (SLERRBASE+28)  /* socket module already attached   */
#define ENOTSOCK        (SLERRBASE+29)  /* path is not a socket             */
#define EDEADLOCK       (SLERRBASE+30)  /* Locking deadlock */
#define EHOSTDOWN       (SLERRBASE+31)
#define EHOSTUNREACH    (SLERRBASE+32)
#define ENOURGENTDATA   (SLERRBASE+33)
#define ENOOOBDATA      (SLERRBASE+34)
#define EMAYBEISO       (SLERRBASE+35)

#define EPPP_DEV_NOT_INIT      (SLERRBASE+61)/* dev. not initialized                       */
#define EPPP_DEV_DEV_TIMEOUT   (SLERRBASE+62)/* Timeout during link establishing           */
#define EPPP_DEV_ONLINE        (SLERRBASE+63)/* device is already online                   */
#define EPPP_DEV_OFFLINE       (SLERRBASE+64)/* device is offline                          */
#define EPPP_DEV_USR_LEN       (SLERRBASE+65)/* length of user name to long                */
#define EPPP_DEV_PWD_LEN       (SLERRBASE+66)/* length of password to long                 */
#define EPPP_DEV_NOHEAP        (SLERRBASE+67)/* no heap available                          */
#define EPPP_DEV_LCP_FAILED    (SLERRBASE+68)/* max failure or max configure are reached   */
#define EPPP_DEV_AUTH_FAILED   (SLERRBASE+69)/* Timeout during waiting for PAP AUTH REQ    */
#define EPPP_DEV_CHAP_FAILED   (SLERRBASE+70)/* max configure (challenge) is reached       */
#define EPPP_DEV_IPCP_FAILED   (SLERRBASE+71)/* max failure or max configure are reached   */
#define EPPP_DEV_IPCFG_FAILED  (SLERRBASE+72)/* invalid IP addresses for server mode       */
#define EPPP_DEV_BS_DROPPED    (SLERRBASE+73)/* char. dropped, missed prev. 0x7E           */
#define EPPP_DEV_BS_FCS_ERR    (SLERRBASE+74)/* FCS Error, packet dropped                  */
#define EPPP_DEV_BS_TOLONG     (SLERRBASE+75)/* Not enough room in m-buf - packet dropped  */
#define EPPP_DEV_SERIAL_FAILED (SLERRBASE+76)/* serial_updown reports an error             */
#define EPPP_DEV_TER_REQ       (SLERRBASE+77)/* terminate request received                 */
#define EPPP_DEV_SUSPICIOUS_ERR (SLERRBASE+78)/* suspicious error                           */
#define EPPP_DEV_CLOSE_CALL    (SLERRBASE+79)/* close user request (sk_PPPClose)           */

#endif /* _SKERRNO_H_ */
