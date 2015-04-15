/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : DDE.H
;   version     : 0005
;   contents    : DDE library header file
;   author      : G.B.
;   date        : Mar 24, 1993
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : DDE library header file
;
;   RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Mar 24, 1993  G.B. 0001 Original issue
;   Mar 28, 1993  G.B. 0002 Adjustments during server implementation
;   Aug 24, 1993  G.B. 0003 Adjustments during warmstart implementation
;   May 19, 1994  G.B. 0004 Flat interface modifications
;   Jan 24, 1995  P.F. 0005 Modification for RMOS3-PC1/DOS V3.11
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _DDE_H_
#define _DDE_H_

#include <rmcomp.h>

/*****************************************************************************/
/*                                                                           */
/* Incode identification                                                     */
/*                                                                           */
/*****************************************************************************/

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
#ifndef _NOVERS
static const char idstr_dde_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"
        "\1"    "DDE.H"                 "\1"
        "\2"    "0005"                  "\2"
        "\3"    "P.F."                  "\3"
};
#endif
#endif  /* defined(_ARCHITECTURE_)  ||  defined(CADUL) */

/*****************************************************************************/
/*                                                                           */
/* Pragmadefinitions                                                         */
/*                                                                           */
/*****************************************************************************/

#if defined(_ARCHITECTURE_) || defined(CADUL)
/* ======= Intel iC386 or CAD-UL CC386 is used ======= */
#pragma fixedparams (x_dde_init,           x_clt_run_application)
#pragma fixedparams (x_clt_initiate,       x_clt_terminate      )
#pragma fixedparams (x_clt_poke,           x_clt_request        )
#pragma fixedparams (x_clt_execute,        x_clt_open_hot_link  )
#pragma fixedparams (x_clt_open_warm_link, x_clt_close_link     )
#pragma fixedparams (x_srv_register,       x_srv_unregister     )
#pragma fixedparams (x_srv_callback_aloc,  x_srv_update_link    )
#pragma fixedparams (x_srv_terminate,      x_srv_close_link     )
#endif  /* defined(_ARCHITECTURE_) || defined(CADUL) */

/*****************************************************************************/
/*                                                                           */
/* Typedefinitions                                                           */
/*                                                                           */
/*****************************************************************************/

/* DDE client: Conversation callback function */
/* ------------------------------------------ */
typedef void (_FIXED _FAR *CLT_CONVFUNCPTR)
                                            (char           *machine_name_p,
                                             char           *service_name_p, 
                                             char           *topic_name_p,
                                             unsigned short conversation_id);

/* DDE client: Warm/hot link callback function */
/* ------------------------------------------- */
typedef unsigned int (_FIXED _FAR *CLT_LINKFUNCPTR)
                                            (char           *machine_name_p,
                                             char           *service_name_p, 
                                             char           *topic_name_p,
                                             unsigned short conversation_id,
                                             char           *item_name_p, 
                                             char           *data_buf_p,
                                             unsigned int   data_buf_size,
                                             unsigned short data_format);

/* DDE server: Conversation callback function */
/* ------------------------------------------ */
typedef unsigned int (_FIXED _FAR *SRV_CONVFUNCPTR)
                                            (char           *machine_name_p,
                                             char           *service_name_p, 
                                             unsigned short server_id,
                                             char           *topic_name_p,
                                             unsigned short conversation_id,
                                             unsigned int   function_code);

/* DDE server: Data callback function */
/* ---------------------------------- */
typedef unsigned int (_FIXED _FAR *SRV_DATAFUNCPTR)
                                            (char           *machine_name_p,
                                             char           *service_name_p, 
                                             unsigned short server_id,
                                             char           *topic_name_p,
                                             unsigned short conversation_id,
                                             char           *item_name_p,
                                             char           *data_buf_p,
                                             unsigned int   data_buf_size,
                                             unsigned short data_format,
                                             unsigned int   function_code);

/* Configuration buffer */
/* -------------------- */
typedef struct dde_configbuf
{
    unsigned int  dummy;
} DDE_CONFIGBUF;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************/
/*                                                                           */
/* Initialization of DDE library                                             */
/*                                                                           */
/*****************************************************************************/

void _FIXED _FAR x_dde_init              (DDE_CONFIGBUF   *config_buf_p,
                                          unsigned int    *status_p);

/*****************************************************************************/
/*                                                                           */
/* DDE client functions                                                      */
/*                                                                           */
/*****************************************************************************/

unsigned short _FIXED _FAR x_clt_initiate(char            *machine_name_p,
                                          char            *service_name_p,
                                          char            *topic_name_p,
                                          CLT_CONVFUNCPTR conv_callback_p,
                                          CLT_LINKFUNCPTR link_callback_p,
                                          unsigned int    stack_size,
                                          unsigned char   priority,
                                          unsigned int    *status_p);
                            
void _FIXED _FAR x_clt_terminate         (unsigned short  conversation_id,
                                          unsigned int    *status_p);

void _FIXED _FAR x_clt_poke              (unsigned short  conversation_id,
                                          char            *item_name_p,
                                          char            *data_buf_p,
                                          unsigned int    data_buf_size,
                                          unsigned short  data_format,
                                          unsigned int    *status_p);

unsigned int  _FIXED _FAR x_clt_request  (unsigned short  conversation_id,
                                          char            *item_name_p,
                                          char            *data_buf_p,
                                          unsigned int    data_buf_size,
                                          unsigned short  data_format,
                                          unsigned int    *status_p);

void _FIXED _FAR x_clt_execute           (unsigned short  conversation_id,
                                          char            *data_buf_p,
                                          unsigned int    *status_p);

void _FIXED _FAR x_clt_open_hot_link     (unsigned short  conversation_id,
                                          char            *item_name_p,
                                          unsigned short  data_format,
                                          unsigned int    *status_p);

void _FIXED _FAR x_clt_open_warm_link    (unsigned short  conversation_id,
                                          char            *item_name_p,
                                          unsigned short  data_format,
                                          unsigned int    *status_p);

void _FIXED _FAR x_clt_close_link        (unsigned short  conversation_id,
                                          char            *item_name_p,
                                          unsigned short  data_format,
                                          unsigned int    *status_p);

void _FIXED _FAR x_clt_run_application   (char            *machine_name_p,
                                          char            *data_buf_p,
                                          unsigned int    flags,
                                          unsigned int    *status_p);

/*****************************************************************************/
/*                                                                           */
/* DDE server functions                                                      */
/*                                                                           */
/*****************************************************************************/

unsigned short _FIXED _FAR x_srv_register(char            *machine_name_p,
                                          char            *service_name_p,
                                          SRV_CONVFUNCPTR conv_callback_p,
                                          SRV_DATAFUNCPTR data_callback_p,
                                          unsigned int    stack_size,
                                          unsigned char   priority,
                                          unsigned int    *status_p);

void _FIXED _FAR x_srv_unregister        (unsigned short  server_id,
                                          unsigned int    *status_p);

char * _FIXED _FAR x_srv_callback_aloc   (unsigned short  server_id,
                                          unsigned int    data_buf_size,
                                          unsigned int    *status_p);

void _FIXED _FAR x_srv_update_link       (unsigned short  server_id,
                                          unsigned short  conversation_id,
                                          char            *item_name_p,
                                          char            *data_buf_p,
                                          unsigned int    data_buf_size,
                                          unsigned short  data_format,
                                          unsigned int    *status_p);

void _FIXED _FAR x_srv_terminate         (unsigned short  server_id,
                                          unsigned short  conversation_id,
                                          unsigned int    *status_p);

void _FIXED _FAR x_srv_close_link        (unsigned short  server_id,
                                          unsigned short  conversation_id,
                                          char            *item_name_p,
                                          unsigned short  data_format,
                                          unsigned int    *status_p);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*****************************************************************************/
/*                                                                           */
/* DDE data formats (same definition as the standard WINDOWS data formats).  */
/*                                                                           */
/*****************************************************************************/

#define CF_TEXT            (unsigned short) 1
#define CF_BITMAP          (unsigned short) 2
#define CF_METAFILEPICT    (unsigned short) 3
#define CF_SYLK            (unsigned short) 4
#define CF_DIF             (unsigned short) 5
#define CF_TIFF            (unsigned short) 6
#define CF_OEMTEXT         (unsigned short) 7
#define CF_DIB             (unsigned short) 8
#define CF_PALETTE         (unsigned short) 9
#define CF_PENDATA         (unsigned short) 10
#define CF_RIFF            (unsigned short) 11
#define CF_WAVE            (unsigned short) 12

#define CF_OWNERDISPLAY    (unsigned short) 0x0080
#define CF_DSPTEXT         (unsigned short) 0x0081
#define CF_DSPBITMAP       (unsigned short) 0x0082
#define CF_DSPMETAFILEPICT (unsigned short) 0x0083

#define CF_PRIVATEFIRST    (unsigned short) 0x0200
#define CF_PRIVATELAST     (unsigned short) 0x02FF

/*****************************************************************************/
/*                                                                           */
/* DDE protocol messages. Not seen by application.                           */
/* (Same definition as the standard WINDOWS DDE protocol messages.)          */
/*                                                                           */
/*****************************************************************************/

#define WM_DDE_FIRST       0x03E0
#define WM_DDE_INITIATE    (WM_DDE_FIRST)
#define WM_DDE_TERMINATE   (WM_DDE_FIRST+1)
#define WM_DDE_ADVISE      (WM_DDE_FIRST+2)
#define WM_DDE_UNADVISE    (WM_DDE_FIRST+3)
#define WM_DDE_ACK         (WM_DDE_FIRST+4)
#define WM_DDE_DATA        (WM_DDE_FIRST+5)
#define WM_DDE_REQUEST     (WM_DDE_FIRST+6)
#define WM_DDE_POKE        (WM_DDE_FIRST+7)
#define WM_DDE_EXECUTE     (WM_DDE_FIRST+8)
#define WM_DDE_LAST        (WM_DDE_FIRST+8)

/*****************************************************************************/
/*                                                                           */
/* Callback function codes.                                                  */
/*                                                                           */
/*****************************************************************************/

/* Conversation callback function codes */
/* ------------------------------------ */
#define DDE_INITIATE       (unsigned) WM_DDE_INITIATE
#define DDE_TERMINATE      (unsigned) WM_DDE_TERMINATE

/* Data callback function codes */
/* ---------------------------- */
#define DDE_HOT_LINK       (unsigned) WM_DDE_ADVISE
#define DDE_CLOSE_LINK     (unsigned) WM_DDE_UNADVISE
#define DDE_REQUEST        (unsigned) WM_DDE_REQUEST
#define DDE_POKE           (unsigned) WM_DDE_POKE
#define DDE_EXECUTE        (unsigned) WM_DDE_EXECUTE
#define DDE_WARM_LINK      (unsigned) (WM_DDE_LAST+2)

/* Callback function return status */
/* ------------------------------- */
#define DDE_CALLBACK_OK    (unsigned) 0   /* Callback request accepted      */
#define DDE_CALLBACK_NACK  (unsigned) -1  /* Callback request not accepted  */

/*****************************************************************************/
/*                                                                           */
/* Miscellaneous options                                                     */
/*                                                                           */
/*****************************************************************************/

#define DDE_NORMAL         (unsigned) 1   /* Window shown in normal   state */
#define DDE_MINIMIZED      (unsigned) 2   /* Window shown in minimize state */
#define DDE_MAXIMIZED      (unsigned) 3   /* Window shown in maximize state */

/*****************************************************************************/
/*                                                                           */
/* Status codes                                                              */
/*                                                                           */
/*****************************************************************************/

#define DDE_OK             (unsigned) 0        /* Function executed properly */
#define DDE_STOP           (unsigned) -1       /* DDE DISPATCHER not active  */

#define DDE_ACTIVE         (unsigned)(0x10000) /* DDE library already init.  */
#define DDE_NOT_ACTIVE     (unsigned)(0x10001) /* DDE library not init.      */
#define DDE_WRONG_NAME     (unsigned)(0x10002) /* Name (e.g. topic) not okay */
#define DDE_NO_CONV        (unsigned)(0x10003) /* No conversation available  */
#define DDE_NO_CHANNEL     (unsigned)(0x10004) /* No server channel available*/
#define DDE_WRONG_CONV     (unsigned)(0x10005) /* Wrong conversation id      */
#define DDE_WRONG_CHANNEL  (unsigned)(0x10006) /* Wrong channel id           */
#define DDE_WRONG_BUF      (unsigned)(0x10007) /* Buffer (ptr.or size) not ok*/
#define DDE_WRONG_CALLBACK (unsigned)(0x10008) /* Ptr. to callb. not ok      */
#define DDE_NO_LINKS       (unsigned)(0x10009) /* Warm/hot links not allowed */
#define DDE_CRRES_FAILED   (unsigned)(0x1000A) /* SVC (create ...) failed    */
#define DDE_TSF_FAILED     (unsigned)(0x1000B) /* SVC tsf failed             */
#define DDE_CAT_FAILED     (unsigned)(0x1000C) /* SVC catalog failed         */
#define DDE_RECV_FAILED    (unsigned)(0x1000D) /* SVC recv failed            */
#define DDE_GETSTAT_FAILED (unsigned)(0x1000E) /* SVC getstat failed         */
#define DDE_HALOC_FAILED   (unsigned)(0x1000F) /* SVC haloc failed           */
#define DDE_MAP_FAILED     (unsigned)(0x10010) /* Memory map function failed */
#define DDE_AT_FAILED      (unsigned)(0x10011) /* x_dos_at_warmstart failed  */
#define DDE_WRONG_PRIO     (unsigned)(0x10012) /* Wrong prio. of callb. func.*/

#define CLT_TIMEOUT         (unsigned) 1       /* Response timeout occured   */
#define CLT_TIMER_FAILED    (unsigned) 2       /* SetTimer      failed       */
#define CLT_ALLOC_FAILED    (unsigned) 3       /* GlobalAlloc   failed       */
#define CLT_LOCK_FAILED     (unsigned) 4       /* GlobalLock    failed       */
#define CLT_POST_FAILED     (unsigned) 5       /* PostMessage   failed       */
#define CLT_ATOM_FAILED     (unsigned) 6       /* GlobalAddAtom failed       */
#define CLT_NACK            (unsigned) 7       /* Neg. WM_DDE_ACK received   */
#define CLT_TERMINATE       (unsigned) 8       /* WM_DDE_TERMINATE received  */
#define CLT_WRONG_FORMAT    (unsigned) 9       /* Wrong data format received */
#define CLT_NO_REPLY        (unsigned) 10      /* No reply to WM_DDE_INITIATE*/
#define CLT_NO_DATA         (unsigned) 11      /* No data in WM_DDE_DATA     */
#define CLT_BUF_2SMALL      (unsigned) 12      /* Receive buffer too small   */
#define CLT_NAMES_2LONG     (unsigned) 13      /* Received names too long    */
#define CLT_CREATE_FAILED   (unsigned) 14      /* CreateWindow  failed       */

#define SRV_TIMEOUT         (unsigned) 1       /* Response timeout occured   */
#define SRV_TIMER_FAILED    (unsigned) 2       /* SetTimer      failed       */
#define SRV_ALLOC_FAILED    (unsigned) 3       /* GlobalAlloc   failed       */
#define SRV_LOCK_FAILED     (unsigned) 4       /* GlobalLock    failed       */
#define SRV_POST_FAILED     (unsigned) 5       /* PostMessage   failed       */
#define SRV_ATOM_FAILED     (unsigned) 6       /* GlobalAddAtom failed       */
#define SRV_NACK            (unsigned) 7       /* Neg. WM_DDE_ACK received   */
#define SRV_TERMINATE       (unsigned) 8       /* WM_DDE_TERMINATE received  */
#define SRV_WRONG_FORMAT    (unsigned) 9       /* Wrong data format          */
#define SRV_WRONG_CONV      (unsigned) 10      /* Wrong conversation id      */
#define SRV_WRONG_LINK      (unsigned) 11      /* Wrong warm/hot link        */
#define SRV_WRONG_DATA      (unsigned) 12      /* Wrong data length          */

#endif  /* _DDE_H_ */
