/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : SOCKET.H
;   version     : 0002
;   contents    : Header file for RMOS socket library
;   author      : P.F.
;   date        : Feb 18, 1998
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file supports the RMOS socket library
;
;   RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Feb 18, 1998  P.F.  0001  Original version
;   Feb 25, 1999  B.N.  0002  Added interface for PPP
;
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _SOCKET_H_
#define _SOCKET_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#ifndef _ERRNO_H_
#include <errno.h>
#endif  /* _ERRNO_H_ */

#ifndef _SKERRNO_H_
#include <skerrno.h>
#endif  /* _SKERRNO_H_ */


#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
	   /* ======= Intel IC386 or Organon CC386 is used ======= */
#pragma fixedparams(x_sk_accept,        x_sk_bind,          x_sk_close          )
#pragma fixedparams(x_sk_connect,       x_sk_endnet,        x_sk_get_sockevent  )
#pragma fixedparams(x_sk_getpeername,   x_sk_getsockname,   x_sk_getsockopt     )
#pragma fixedparams(x_sk_ioctl,         x_sk_listen,        x_sk_nselect        )
#pragma fixedparams(x_sk_recv,          x_sk_recvfrom,      x_sk_send           )
#pragma fixedparams(x_sk_sendto,        x_sk_setsockopt,    x_sk_shutdown       )
#pragma fixedparams(x_sk_socket                                                 )

#pragma fixedparams(x_sk_sethostent,    x_sk_endhostent                         )
#pragma fixedparams(x_sk_gethostent,    x_sk_gethostbyname, x_sk_gethostbyaddr  )
#pragma fixedparams(x_sk_setservent,    x_sk_endservent                         )
#pragma fixedparams(x_sk_getservent,    x_sk_getservbyname, x_sk_getservbyport  )
#pragma fixedparams(x_sk_PPPConfig,     x_sk_PPPTimeCnt,    x_sk_PPPOpen        )
#pragma fixedparams(x_sk_PPPClose,      x_sk_PPPGetIP,      x_sk_PPPConfigClosedEvent)

#pragma fixedparams(x_sk_ip_add_multi, x_sk_ip_del_multi ,  x_sk_add_route , x_sk_del_route)

#pragma noalign (servent)
#pragma noalign (hostent)
#pragma noalign (sockaddr)
#pragma noalign (socksel)
#endif /* _ARCHITECTURE_ || CADUL */

#if defined __BORLANDC__
	   /* ======= Borland C++ is used ======= */
#pragma option -a-
#endif


/*
**  Definitions related to sockets: types, address families, options.
*/

/*
**  ---- Types ----
*/
#define SOCK_STREAM     1           /* stream socket                        */
#define SOCK_DGRAM      2           /* datagram socket                      */

/*
**  ---- Option flags per-socket ----
*/
#define SO_DEBUG        0x0001      /* turn on debugging info recording     */
#define SO_REUSEADDR    0x0004      /* allow local address reuse            */
#define SO_KEEPALIVE    0x0008      /* keep connections alive               */
#define SO_DONTROUTE    0x0010      /* just use interface addresses         */
#define SO_LINGER       0x0080      /* linger on close if data present      */
#define SO_THROUGHPUT   0x0100      /* large data transfer                  */
#define SO_EXPEDITE     0x0200      /* responsive data transfer             */
#define SO_OOBINLINE    0x0400      /* leave received OOB data in line      */
#define SO_TYPE         0x1008      /* get socket type (getsocket only)     */

#define IPL_IP           0x0000     /* IP_IP options for socket level        */
#define IPL_O_TOS        0x0001     /* IP_IP Type of Service                 */
#define IPL_RELIABLE     0x0004     /* IP_IP reliability                     */
#define IPL_THROUGHPUT  0x0008     /* IP_IP throughput                       */
#define IPL_DELAY        0x0010     /* IP_IP delay                           */


/*
**  ---- Level number for (get/set)sockopt() to apply to socket itself ----
*/
#define SOL_SOCKET      0xffff      /* options for socket level             */

/*
**  ---- Address family ----
*/
#define AF_INET         2           /* internetwork: UDP, TCP, etc.         */

/*
**  ---- Protocols ----
*/
#define IPPROTO_TCP     6           /* transmission control protocol        */
#define IPPROTO_UDP     17          /* user datagram protocol               */

/*
**  ---- Definitions for I/O control functions ----
*/
#define SLiocNBIO       0           /* Select blocking/nonblocking mode     */
#define SLiocSOID       2           /* Set socket id number                 */
#define SLiocRECVBYTES  10          /* Get number of bytes in receive queue */
/*
**  ---- Definitions for send/recv flags ----
*/
#define MSG_OOB         0x1         /* process out of band information      */
#define MSG_URGENT      0x0800      /* urgent data                          */
#define MSG_NONBLOCKING 0x4000      /* override any blocking state          */
#define MSG_BLOCKING    0x8000      /* override any nonblocking state       */
/*
** synchronous or asynchronous notification values (via nselect).
*/
#define READ_NOTIFY         ((unsigned short)0x1)   /* read data available */
#define WRITE_NOTIFY        ((unsigned short)0x2)   /* write data space available */
#define ACCEPT_NOTIFY       ((unsigned short)0x4)   /* connection request awaits */
#define CLOSE_NOTIFY        ((unsigned short)0x8)   /* close down completed */
#define CONNECT_NOTIFY      ((unsigned short)0x10)  /* connection completed */
#define EXCEPT_NOTIFY       ((unsigned short)0x20)  /* exception has occurred */
#define RSHUTDOWN_NOTIFY    ((unsigned short)0x40)  /* read direction shutdown by peer */
#define TIMEOUT_NOTIFY      ((unsigned short)0x80)  /* request has timed out */
#define WSHUTDOWN_NOTIFY    ((unsigned short)0x100) /* write direction shutdown by peer */
#define URGENT_NOTIFY       ((unsigned short)0x200) /* urgent data available */
#define SENDQFULL_NOTIFY    ((unsigned short)0x1000)
#define SENDQEMPTY_NOTIFY   ((unsigned short)0x2000)

/******************************************************************************/
/*                    PPP CONFIGURATION PART                                  */
/******************************************************************************/
#define PPP_RESTART                     3000 /* default value                             */
#define PPP_CONFIGURE         10 /* no. of cfg. req. - default value          */
#define PPP_TERMINATE          2 /* no. of ter. req. - default value          */
#define PPP_FAILURE                       10 /* no. of failure   - default value          */

#define MAX_PPP_USER              25 /* ML: defines max len of PPP user name.     */
#define MAX_PPP_PSWD          15 /* ML: defines max len of PPP user password. */
#define FNS_37                           NO /* use FNS version 3.7 ?                     */
#define PPP_GET_FEEDBACK     YES /* Enable/disable callback                   */
#define PSI_SERIF                        YES /* use PSI serial interface, descr. in man.  */

/*============================================================================*/
/* PPP FLAG SECTION                                                           */
/*============================================================================*/
/* API FLAGS */
#define P_F_DIALIN               0x0001 /* Is set by OpenPPPSrv                       */        
#define P_F_NOWAIT       0x0002 /* Don't wait for events                      */
#define P_F_WAITALL      0x0004 /* Wait for until event                       */
#define P_F_SRV          0x0008 /* Indicates server mode for updown           */
#define P_F_CLI          0x0010 /* Indicates client mode for updown           */
#define P_F_UP           0x0020 /* Indicates UP request in updown             */
#define P_F_DOWN         0x0040 /* Indicates DOWN request in updown           */
#define P_F_ONLINE               0x0080 /* INdicates local in psp dev. online         */
#define P_F_CLOSECALL    0x0100 /* API close is running -  callbacks          */
#define P_F_OPENCALL     0x0200 /* API open is running -  callbacks           */
#define P_F_TIMEOUT      0x0400 /* PPP API timer is expired                   */
#define P_F_LINK_IS_UP   0x0800 /* Link is established                        */
#define P_F_LINK_IS_DOWN 0x1000 /* Link was closed                            */
#define P_F_NO_CALLBACK  0x2000 /* API call pending or user request           */

/* FLAGS for ClosePPP() */
#define P_F_NO_TERREQ    0x0001 /* Do not send TER REQ, reset FSM immediately */

/* LCP Configuration option */
#define P_F_LCP_ZERO_ACCM       1   /* Start with ACCM=0, instead of -1 (synch.)  */
#define P_F_LCP_PFC_OFF         2   /* disable Protocol field compression (PFC)   */
#define P_F_LCP_ACFC_OFF        4   /* disable Addr. Ctrl. Field compr. (ACFC)    */

/* IPCP Configuration option */
#define P_F_IPCP_VJC_OFF    1   /* disable Van Jacobson TCP/IP-Header compr.  */
#define P_F_IPCP_NO_IPREG   2   /* do not configure establ. link at FUSION    */
#define P_F_IPCP_GATEW      4   /* do add RemoteIP as gateway/route           */

#define PPP_PAPTYPE     0xc023
#define PPP_CHAPTYPE    0xc223

/*
**  ---- Structure for internet address family ----
*/
typedef struct sockaddr
{
    short           sa_family;      /* address family       */
    short           sin_port;       /* internet port number */
    char            sin_addr[4];    /* internet address     */
} SOCKADDR;

/* linger option value structure */
typedef struct lingeroptx {
    int linger_on;    /* Linger option on or off */
	int     linger_time;  /* Linger timeout value in seconds */
} LINGEROPTX;

/*
**  ---- Structure for use with nselect ----
*/
typedef struct socksel
{
    unsigned short  se_inflags;
    unsigned short  se_outflags;
    int             se_fd;
    int             se_1reserved;
    unsigned long   se_user;
    unsigned long   se_2reserved;
} SOCKSEL;

/*
**  ---- Socket function prototypes ----
*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int  _FIXED _FAR x_sk_accept         (int so, SOCKADDR _FAR *name,
					     int _FAR *namelen);
extern int  _FIXED _FAR x_sk_bind           (int so, SOCKADDR _FAR *name,
					     int namelen);
extern int  _FIXED _FAR x_sk_close          (int so);
extern int  _FIXED _FAR x_sk_connect        (int so, SOCKADDR _FAR *name,
					     int namelen);
extern void _FIXED _FAR x_sk_endnet         (void);
extern int  _FIXED _FAR x_sk_get_sockevent  (void);
extern int  _FIXED _FAR x_sk_getpeername    (int so, SOCKADDR _FAR *name,
					     int _FAR *namelen);
extern int  _FIXED _FAR x_sk_getsockname    (int so, SOCKADDR _FAR *name,
					     int _FAR *namelen);
extern int  _FIXED _FAR x_sk_getsockopt     (int so, int level, int optname,
					     int _FAR *optval, int _FAR *optlen);
extern int  _FIXED _FAR x_sk_ioctl          (int so, int request, void _FAR *arg,
					     int arglen);
extern int  _FIXED _FAR x_sk_listen         (int so, int backlog);
extern int  _FIXED _FAR x_sk_nselect        (struct socksel _FAR *selp, int cnt,
					     unsigned long _FAR *waitp,
					     void _FAR *pfi, void _FAR *arg);
extern int  _FIXED _FAR x_sk_recv           (int so, void _FAR *msg, int len,
					     int flags);
extern int  _FIXED _FAR x_sk_recvfrom       (int so, void _FAR *msg, int len,
					     int flags, SOCKADDR _FAR *from,
					     int _FAR *fromlen);
extern int  _FIXED _FAR x_sk_send           (int so, void _FAR *msg, int len,
					     int flags);
extern int  _FIXED _FAR x_sk_sendto         (int so, void _FAR *msg, int len,
					     int flags, SOCKADDR _FAR *to,
					     int tolen);
extern int  _FIXED _FAR x_sk_setsockopt     (int so, int level, int optname,
					     int _FAR *optval, int optlen);
extern int  _FIXED _FAR x_sk_shutdown       (int so, int how);
extern int  _FIXED _FAR x_sk_socket         (int af, int type, int protocol);
extern int  _FIXED _FAR x_sk_PPPConfig      (unsigned long       LCPcfg,
					     unsigned long       ACCM,
					     unsigned long       Authentication,
					     unsigned long       IPCPcfg,
					     unsigned long       MyIP,
					     unsigned long       RemoteIP );
extern int  _FIXED _FAR x_sk_PPPTimeCnt     (unsigned long       Restart,
					     unsigned char       MaxFailure,
					     unsigned char       MaxTerminate,
					     unsigned char       MaxConfigure);
extern int  _FIXED _FAR x_sk_PPPOpen        (char _FAR           *pUserName,
					     char _FAR           *pPassword,
					     unsigned long       Flags,
					     unsigned long       Timeout);
extern int  _FIXED _FAR x_sk_PPPClose       (unsigned long       Flags);
extern int  _FIXED _FAR x_sk_PPPGetIP       (unsigned long _FAR  *pMyIP,
					     unsigned long _FAR  *pRemoteIP);
extern int  _FIXED _FAR x_sk_PPPConfigClosedEvent (unsigned int   FlagID,
						   unsigned int   FlagMask);

extern int  _FIXED _FAR x_sk_ip_add_multi   (char _FAR		*DeviceName,
                                             unsigned int   UnitID,
                                             char _FAR      *MC_IPAddr);
extern int  _FIXED _FAR x_sk_ip_del_multi   (char _FAR		*DeviceName,
                                             unsigned int   UnitID,
                                             char _FAR      *MC_IPAddr);
extern int  _FIXED _FAR x_sk_add_route      (char _FAR		*DeviceName,
                                             unsigned int   UnitID,
                                             unsigned long  gateway,
											 unsigned long  network,
											 unsigned long  subnet,
											 int            hops);
extern int  _FIXED _FAR x_sk_del_route      (char _FAR		*DeviceName,
                                             unsigned int   UnitID,
                                             unsigned long  gateway,
											 unsigned long  subnet);											 
#ifdef __cplusplus
}
#endif /* __cplusplus */

/*
**  Host database entry
*/
typedef struct hostent
{
    char          _FAR *h_name;     /* official name of host    */
    char    _FAR *_FAR *h_aliases;  /* alias list               */
    short              h_addrtype;  /* host address type        */
    short              h_length;    /* length of address        */
    char          _FAR *h_addr;     /* address                  */
} HOSTENT;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int                   _FIXED _FAR x_sk_sethostent    (int stayopen);
extern void                  _FIXED _FAR x_sk_endhostent    (void);
extern struct hostent _FAR * _FIXED _FAR x_sk_gethostent    (void);
extern struct hostent _FAR * _FIXED _FAR x_sk_gethostbyname (void _FAR *name);
extern struct hostent _FAR * _FIXED _FAR x_sk_gethostbyaddr (void _FAR *addr,
							     int len, int type);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*
**  Services database entry
*/
typedef struct servent
{
    char          _FAR *s_name;     /* official service name */
    char    _FAR *_FAR *s_aliases;  /* alias list */
    int                s_port;      /* port # */
    char          _FAR *s_proto;    /* protocol to use */
} SERVENT;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int                   _FIXED _FAR x_sk_setservent    (int stayopen);
extern void                  _FIXED _FAR x_sk_endservent    (void);
extern struct servent _FAR * _FIXED _FAR x_sk_getservent    (void);
extern struct servent _FAR * _FIXED _FAR x_sk_getservbyname (void _FAR *name,
							     void _FAR *proto);
extern struct servent _FAR * _FIXED _FAR x_sk_getservbyport (int port,
							     void _FAR *proto);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*
**  Initialization functions
*/
#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
	   /* ======= Intel IC386 or Organon CC386 is used ======= */
#pragma fixedparams(x_skrm_initialize)
#endif /* _ARCHITECTURE_ || CADUL */

extern int  _FIXED _FAR x_skrm_initialize   (void);



/*  **************************************************************************
**  Utility functions and macros
*/

#ifndef RM_HTON
#define RM_HTON

/* convert a short int from host to network order */
#define htons(x)        (short) ((((short)(x)&0x00FF)<<8) + (((short)(x)&0xFF00)>>8))

/* convert a short int from network to host order */
#define ntohs(x)        (short) ((((short)(x)&0x00FF)<<8) + (((short)(x)&0xFF00)>>8))

#endif /* RM_HTON */


#if defined __BORLANDC__
#pragma option -a.
#endif

#endif /* _SOCKET_H_ */
