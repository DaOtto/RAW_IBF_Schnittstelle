/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : RMOS320.H
;   version     : 0001
;   contents    : Header file for support of RMOS3 V3.20
;   author      : P.F.
;   date        : Nov 07, 1997
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Header file for support of RMOS3 V3.20
;
;   RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Nov 07, 1997  P.F.  0001  Original issue
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _RMOS320_H_
#define _RMOS320_H_

#define accept          x_sk_accept
#define bind            x_sk_bind
#define closesocket     x_sk_close
#define connect         x_sk_connect
#define endnet          x_sk_endnet
#define getsockevent    x_sk_get_sockevent  
#define getpeername     x_sk_getpeername
#define getsockname     x_sk_getsockname
#define getsockopt      x_sk_getsockopt
#define ioctlsocket     x_sk_ioctl
#define listen          x_sk_listen
#define nselect         x_sk_nselect
#define recv            x_sk_recv
#define recvfrom        x_sk_recvfrom
#define send            x_sk_send
#define sendto          x_sk_sendto
#define setsockopt      x_sk_setsockopt
#define shutdown        x_sk_shutdown
#define socket          x_sk_socket
#define sethostent      x_sk_sethostent
#define endhostent      x_sk_endhostent
#define gethostent      x_sk_gethostent
#define gethostbyname   x_sk_gethostbyname
#define gethostbyaddr   x_sk_gethostbyaddr
#define setservent      x_sk_setservent
#define endservent      x_sk_endservent
#define getservent      x_sk_getservent
#define getservbyname   x_sk_getservbyname
#define getservbyport   x_sk_getservbyport

#endif /* _RMOS320_H_ */

