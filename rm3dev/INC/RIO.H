/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : RIO.H
;   version     : 0009
;   contents    : Include-File for RIO-Systemcalls in C
;   author      : P.F.
;   date        : Aug 08, 1995
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Include-file for RMOS-Systemcalls
;                 Official Defines for rio-systemcalls
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Sep 23, 1992  W.S.  0005  Modification header added
;   Dec  4, 1992  W.S.  0006  Modifications for use with BORLAND C
;   Jul  7, 1993  W.S.  0007  Allow multiple include of rio.h
;   Dec 19, 1994  P.F.  0008  Modifications for use with CADUL C
;   Aug 08, 1995  P.F.  0009  Added typedef RmBytParmStruct
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _RIO_H_
#define _RIO_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
#ifndef _NOVERS
static const
char idstr_rio_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"    /* In-code identification. */
        "\1"    "RIO.H"                 "\1"
        "\2"    "0009"                  "\2"
        "\3"    "P.F."                  "\3"
};
#endif
#endif  /* defined(_ARCHITECTURE_)  ||  defined(CADUL) */

#ifdef _ARCHITECTURE_  

/* This Part belongs to the Intel C-Compiler IC86/386 or CADUL CC86/386 */

/* These pragma's garantees that the rmos-data-structures conform with the
   compiler structures
*/   

#pragma noalign (byt_parm_struct)

#endif

#ifdef _MSC_VER     /* This belogs to Microsoft */
#pragma pack(1)     /* set all to allign on byte  */
#endif

#ifdef __BORLANDC__
#pragma option -a-  /* set all to byte alignment */
#endif /* __BORLANDC__ */

/*
;------------------------------------------------------------------------------
;   RIO-FUNCTION DEFINES FOR DEVICE DRIVERS
;------------------------------------------------------------------------------
*/


/************************************************************************
*   RIO FUNCTION DEFINES AND STRUCTURES FOR BYTE-DRIVER                 *
*************************************************************************/



/* Structure for the RIO system call: BYTEDRIVER                     */
struct byt_parm_struct
{
    char            *string;    /* Prompt string (address)           */
#if RMFLAT
    unsigned short  string_fill;/* fill word for flat model          */
#endif
    unsigned int    strlen;     /* Length of Prompt string           */
    char            *buffer;    /* Translation- or Buffer Address    */
#if RMFLAT
    unsigned short  buffer_fill;/* fill word for flat model          */
#endif
    unsigned int    timlen;     /* Timeout-Value / Buffer Length     */
    unsigned int    status;     /* Status->Look at Bytedriver-Manual */
};
typedef struct byt_parm_struct  RmBytParmStruct;
    

#define MAX_BYT_FUNC   (unsigned)         0x0E  /* MAX. FUNCTION CODE   */
#define BYT_IMMED_BIT  (unsigned)         0x80  /* EMERGENCY-OPTION     */
#define BYT_WAIT_BIT   (unsigned)         0x40  /* WAIT-OPTION          */
#define BYT_CANCEL_BIT (unsigned)         0x20  /* CANCEL-OPTION        */

/*      RIO-FUNCTION'S WITHOUT THE WAIT OPTION              */

#define BYT_RESERVE    (unsigned)         0x00  /* RESERVE UNIT         */
#define BYT_RELEASE    (unsigned)         0x01  /* RELEASE UNIT         */
#define BYT_READ       (unsigned)         0x02  /* NORMAL READ          */
#define BYT_WRITE      (unsigned)         0x03  /* NORMAL WRITE         */
#define BYT_XWRT       (unsigned)         0x04  /* EMERGENCY WRITE      */
#define BYT_ONE_XREAD  (unsigned)         0x05  /* ONE TRANSP. STS-READ */
#define BYT_WRT_XREAD  (unsigned)         0x06  /* WRITE & TRANSP. READ */
#define BYT_WRT_READ   (unsigned)         0x07  /* WRITE & NORMAL READ  */
#define BYT_SKIP_LINE  (unsigned)         0x08  /* SKIP LINE(S)         */
#define BYT_FORM_FEED  (unsigned)         0x09  /* ERASE SCREEN (FORM)  */
#define BYT_HSFS_XREAD (unsigned)         0x0A  /* ONE TRANSP. BUF-READ */
#define BYT_HSFS_WRT   (unsigned)         0x0B  /* ONE NORMAL BUF-WRITE */
#define BYT_POLL_XBUF  (unsigned)         0x0C  /* POLL EXTRA-BUFFER    */
#define BYT_CHECK_ABO  (unsigned)         0x0D  /* CHECK FOR ABORT-FLAG */
#define BYT_CREATE_NEW (unsigned)         0x0E  /* CREATE NEW UNIT      */

/*      RIO-FUNCTION'S WITH THE WAIT OPTION                 */

#define BYT_RESERVE_WAIT    (unsigned)    0x40  /* RESERVE UNIT         */
#define BYT_RELEASE_WAIT    (unsigned)    0x41  /* RELEASE UNIT         */
#define BYT_READ_WAIT       (unsigned)    0x42  /* NORMAL READ          */
#define BYT_WRITE_WAIT      (unsigned)    0x43  /* NORMAL WRITE         */
#define BYT_XWRT_WAIT       (unsigned)    0x44  /* EMERGENCY WRITE      */
#define BYT_ONE_XREAD_WAIT  (unsigned)    0x45  /* ONE TRANSP. STS-READ */
#define BYT_WRT_XREAD_WAIT  (unsigned)    0x46  /* WRITE & TRANSP. READ */
#define BYT_WRT_READ_WAIT   (unsigned)    0x47  /* WRITE & NORMAL READ  */
#define BYT_SKIP_LINE_WAIT  (unsigned)    0x48  /* SKIP LINE(S)         */
#define BYT_FORM_FEED_WAIT  (unsigned)    0x49  /* ERASE SCREEN (FORM)  */
#define BYT_HSFS_XREAD_WAIT (unsigned)    0x4A  /* ONE TRANSP. BUF-READ */
#define BYT_HSFS_WRT_WAIT   (unsigned)    0x4B  /* ONE NORMAL BUF-WRITE */
#define BYT_POLL_XBUF_WAIT  (unsigned)    0x4C  /* POLL EXTRA-BUFFER    */
#define BYT_CHECK_ABO_WAIT  (unsigned)    0x4D  /* CHECK FOR ABORT-FLAG */
#define BYT_CREATE_NEW_WAIT (unsigned)    0x4E  /* CREATE NEW UNIT      */

/************************************************************************
*                    RIO FUNCTION DEFINES FOR COM1-DRIVER               *
*************************************************************************/

    /*---------------------------------------------------
    |   ONLY VALID FOR RMOS2 AT THIS TIME!              |
    -----------------------------------------------------
    */

#define MAX_CM1_FUNC        (unsigned)   0x06  /* MAX. FUNCTION CODE   */
#define CM1_IMMED_BIT       (unsigned)   0x80  /* EMERGENCY-OPTION     */
#define CM1_WAIT_BIT        (unsigned)   0x40  /* WAIT-OPTION          */

/*      RIO FUNCTION'S WITHOUT THE WAIT OPTION              */

#define CM1_RESERVE         (unsigned)   0x00  /* RESERVE UNIT         */
#define CM1_RELEASE         (unsigned)   0x01  /* RELEASE UNIT         */
#define CM1_READ            (unsigned)   0x02  /* NORMAL READ          */
#define CM1_WRITE           (unsigned)   0x03  /* NORMAL WRITE         */
#define CM1_BREAK_ON        (unsigned)   0x04  /* FORCE BREAK ENABLE   */
#define CM1_BREAK_OFF       (unsigned)   0x05  /* FORCE BREAK DISABLE  */
#define CM1_CREATE_NEW      (unsigned)   0x06  /* CREATE NEW UNIT      */

/*      RIO FUNCTION'S WITH THE WAIT OPTION                 */

#define CM1_RESERVE_WAIT    (unsigned)   0x40  /* RESERVE UNIT         */
#define CM1_RELEASE_WAIT    (unsigned)   0x41  /* RELEASE UNIT         */
#define CM1_READ_WAIT       (unsigned)   0x42  /* NORMAL READ          */
#define CM1_WRITE_WAIT      (unsigned)   0x43  /* NORMAL WRITE         */
#define CM1_BREAK_ON_WAIT   (unsigned)   0x44  /* FORCE BREAK ENABLE   */
#define CM1_BREAK_OFF_WAIT  (unsigned)   0x45  /* FORCE BREAK DISABLE  */
#define CM1_CREATE_NEW_WAIT (unsigned)   0x46  /* CREATE NEW UNIT      */

/************************************************************************
*                   RIO FUNCTION DEFINES FOR CRT2-DRIVER                *
*************************************************************************/

#define MAX_CRT_FUNC        (unsigned)   0x0C  /* MAX. FUNCTION CODE   */
#define CRT_IMMED_BIT       (unsigned)   0x80  /* EMERGENCY-OPTION     */
#define CRT_WAIT_BIT        (unsigned)   0x40  /* WAIT-OPTION          */

/*      RIO FUNCTION'S WITHOUT THE WAIT OPTION              */

#define CRT_RESERVE         (unsigned)   0x00  /* RESERVE UNIT         */
#define CRT_RELEASE         (unsigned)   0x01  /* RELEASE UNIT         */
#define CRT_READ            (unsigned)   0x02  /* NORMAL READ          */
#define CRT_WRITE           (unsigned)   0x03  /* NORMAL WRITE         */
#define CRT_XWRT            (unsigned)   0x04  /* EMERGENCY WRITE      */
#define CRT_ONE_XREAD       (unsigned)   0x05  /* ONE TRANSP. STS-READ */
#define CRT_WRT_XREAD       (unsigned)   0x06  /* WRITE & TRANSP. READ */
#define CRT_WRT_READ        (unsigned)   0x07  /* WRITE & NORMAL READ  */
#define CRT_SKIP_LINE       (unsigned)   0x08  /* SKIP LINE(S)         */
#define CRT_FORM_FEED       (unsigned)   0x09  /* ERASE SCREEN (FORM)  */
#define CRT_HSFS_XREAD      (unsigned)   0x0A  /* ONE TRANSP. BUF-READ */
#define CRT_HSFS_WRT        (unsigned)   0x0B  /* ONE NORMAL BUF-WRITE */
#define CRT_CREATE_NEW      (unsigned)   0x0C  /* CREATE NEW UNIT      */

/*      RIO FUNCTION'S WITH THE WAIT OPTION                 */

#define CRT_RESERVE_WAIT    (unsigned)   0x40  /* RESERVE UNIT         */
#define CRT_RELEASE_WAIT    (unsigned)   0x41  /* RELEASE UNIT         */
#define CRT_READ_WAIT       (unsigned)   0x42  /* NORMAL READ          */
#define CRT_WRITE_WAIT      (unsigned)   0x43  /* NORMAL WRITE         */
#define CRT_XWRT_WAIT       (unsigned)   0x44  /* EMERGENCY WRITE      */
#define CRT_ONE_XREAD_WAIT  (unsigned)   0x45  /* ONE TRANSP. STS-READ */
#define CRT_WRT_XREAD_WAIT  (unsigned)   0x46  /* WRITE & TRANSP. READ */
#define CRT_WRT_READ_WAIT   (unsigned)   0x47  /* WRITE & NORMAL READ  */
#define CRT_SKIP_LINE_WAIT  (unsigned)   0x48  /* SKIP LINE(S)         */
#define CRT_FORM_FEED_WAIT  (unsigned)    0x49  /* ERASE SCREEN (FORM)  */
#define CRT_HSFS_XREAD_WAIT (unsigned)   0x4A  /* ONE TRANSP. BUF-READ */
#define CRT_HSFS_WRT_WAIT   (unsigned)   0x4B  /* ONE NORMAL BUF-WRITE */
#define CRT_CREATE_NEW_WAIT (unsigned)   0x4C  /* CREATE NEW UNIT      */

/*****************************************************************************
**                    RIO-FUNCTION DEFINES FOR DMA -DRIVER                  **
******************************************************************************/

    /*---------------------------------------------------
    |   ONLY VALID FOR RMOS2 AT THIS TIME!              |
    -----------------------------------------------------
    */

#define MAX_DMA_FUNC        (unsigned)   0x07  /* MAX. FUNCTION CODE   */
#define DMA_IMMED_BIT       (unsigned)   0x80  /* PREEMPTIVE OPTION    */
#define DMA_WAIT_BIT        (unsigned)   0x40  /* WAIT-OPTION          */
          
/*        RIO-FUNCTION'S WITHOUT THE WAIT OPTION            */

#define DMA_RESERVE         (unsigned)   0x00  /* RESERVE UNIT         */
#define DMA_RELEASE         (unsigned)   0x01  /* RELEASE UNIT         */
#define DMA_READ            (unsigned)   0x02  /* READ  (BUF --> DEV)  */
#define DMA_WRITE           (unsigned)   0x03  /* WRITE (DEV --> BUF)  */
#define DMA_ABORT           (unsigned)   0x04  /* ABORT DMA FUNCTION   */
#define DMA_CREATE          (unsigned)   0x05  /* CREATE/READ UNIT     */
#define DMA_DUMMY           (unsigned)   0x06  /* (RESERVED)           */
#define DMA_XCREATE         (unsigned)   0x07  /* OLD CREATE/READ UNIT */

/*      RIO-FUNCTION'S WITH THE WAIT OPTION                 */

#define DMA_RESERVE_WAIT    (unsigned)   0x40  /* RESERVE UNIT         */
#define DMA_RELEASE_WAIT    (unsigned)   0x41  /* RELEASE UNIT         */
#define DMA_READ_WAIT       (unsigned)   0x42  /* READ  (BUF --> DEV)  */
#define DMA_WRITE_WAIT      (unsigned)   0x43  /* WRITE (DEV --> BUF)  */
#define DMA_ABORT_WAIT      (unsigned)   0x44  /* ABORT DMA FUNCTION   */
#define DMA_CREATE_WAIT     (unsigned)   0x45  /* CREATE/READ UNIT     */
#define DMA_DUMMY_WAIT      (unsigned)   0x46  /* (RESERVED)           */
#define DMA_XCREATE_WAIT    (unsigned)   0x47  /* OLD CREATE/READ UNIT */

/*****************************************************************************
**                 RIO-FUNCTION DEFINES FOR FD2 -DRIVER                     **
******************************************************************************/

    /*---------------------------------------------------
    |   ONLY VALID FOR RMOS2  AT THIS TIME!             |
    -----------------------------------------------------
    */

#define MAX_FD2_FUNC        (unsigned)   0x0E  /* MAX. FUNCTION CODE   */
#define FD2_IMMED_BIT       (unsigned)   0x80  /* PREEMPTIVE OPTION    */
#define FD2_WAIT_BIT        (unsigned)   0x40  /* WAIT-OPTION          */
#define FD2_CANCEL_BIT      (unsigned)   0x20  /* CANCEL-OPTION        */

/*       RIO FUNCTION'S WITHOUT THE WAIT OPTION               */

#define  FD2_RESERVE        (unsigned)  0x00   /* RESERVE UNIT           */
#define  FD2_RELEASE        (unsigned)  0x01   /* RELEASE UNIT           */
#define  FD2_READ_1         (unsigned)  0x02   /* READ ONE BLOCK         */
#define  FD2_WRITE_1        (unsigned)  0x03   /* WRITE ONE BLOCK        */
#define  FD2_FORMAT         (unsigned)  0x04   /* FORMAT UNIT            */
#define  FD2_READ           (unsigned)  0x05   /* READ BLOCKS            */
#define  FD2_WRITE          (unsigned)  0x06   /* WRITE BLOCKS           */
#define  FD2_READ_ID        (unsigned)  0x07   /* READ ID-FIELD          */
#define  FD2_SEEK           (unsigned)  0x08   /* RECALIBRATE TO TRACK   */
#define  FD2_RECA           (unsigned)  0x09   /* RECALIBRATE TO TRACK 0x0 */
#define  FD2_UNIT_RDY       (unsigned)  0x0A   /* GET UNIT READY BLOCK   */
#define  FD2_DELETE         (unsigned)  0x0B   /* DELETE UNIT            */
#define  FD2_CREATE         (unsigned)  0x0C   /* CREATE UNIT            */
#define  FD2_FORM_TR        (unsigned)  0x0D   /* FORMAT TRACK           */
#define  FD2_READ_TR        (unsigned)  0x0E   /* READ TRACK-FORMAT      */

/*       RIO FUNCTION'S WITH THE WAIT OPTION                  */

#define  FD2_RESERVE_WAIT   (unsigned)  0x40   /* RESERVE UNIT           */
#define  FD2_RELEASE_WAIT   (unsigned)  0x41   /* RELEASE UNIT           */
#define  FD2_READ_1_WAIT    (unsigned)  0x42   /* READ ONE BLOCK         */
#define  FD2_WRITE_1_WAIT   (unsigned)  0x43   /* WRITE ONE BLOCK        */
#define  FD2_FORMAT_WAIT    (unsigned)  0x44   /* FORMAT UNIT            */
#define  FD2_READ_WAIT      (unsigned)  0x45   /* READ BLOCKS            */
#define  FD2_WRITE_WAIT     (unsigned)  0x46   /* WRITE BLOCKS           */
#define  FD2_READ_ID_WAIT   (unsigned)  0x47   /* READ ID-FIELD          */
#define  FD2_SEEK_WAIT      (unsigned)  0x48   /* RECALIBRATE TO TRACK   */
#define  FD2_RECA_WAIT      (unsigned)  0x49   /* RECALIBRATE TO TRACK 0 */
#define  FD2_UNIT_RDY_WAIT  (unsigned)  0x4A   /* GET UNIT READY BLOCK   */
#define  FD2_DELETE_WAIT    (unsigned)  0x4B   /* DELETE UNIT            */
#define  FD2_CREATE_WAIT    (unsigned)  0x4C   /* CREATE UNIT            */
#define  FD2_FORM_TR_WAIT   (unsigned)  0x4D   /* FORMAT TRACK           */
#define  FD2_READ_TR_WAIT   (unsigned)  0x4E   /* READ TRACK-FORMAT      */

/*****************************************************************************
**                   RIO-FUNCTION DEFINES FOR HD6 -DRIVER                   **
******************************************************************************/

    /*---------------------------------------------------
    |   ONLY VALID FOR RMOS2 AT THIS TIME!              |
    -----------------------------------------------------
    */

#define MAX_HD6_FUNC        (unsigned)   0x0F  /* MAX. FUNCTION CODE   */
#define HD6_IMMED_BIT       (unsigned)   0x80  /* PREEMPTIVE OPTION    */
#define HD6_WAIT_BIT        (unsigned)   0x40  /* WAIT-OPTION          */

/*        RIO-FUNCTION S WITHOUT THE WAIT OPTION            */

#define HD6_RESERVE         (unsigned)   0x00  /* RESERVE UNIT         */
#define HD6_RELEASE         (unsigned)   0x01  /* RELEASE UNIT         */
#define HD6_READ_1          (unsigned)   0x02  /* READ ONE BLOCK       */
#define HD6_WRITE_1         (unsigned)   0x03  /* WRITE ONE BLOCK      */
#define HD6_FILL            (unsigned)   0x04  /* FILL UNIT WITH DATA  */
#define HD6_READ            (unsigned)   0x05  /* READ BLOCKS          */
#define HD6_WRITE           (unsigned)   0x06  /* WRITE BLOCKS         */
#define HD6_CREATE          (unsigned)   0x07  /* CREATE UNIT          */
#define HD6_MULTI           (unsigned)   0x0F  /* MULTI FUNCTION       */

/*      RIO-FUNCTION S WITH THE WAIT OPTION                 */

#define HD6_RESERVE_WAIT    (unsigned)   0x40  /* RESERVE UNIT         */
#define HD6_RELEASE_WAIT    (unsigned)   0x41  /* RELEASE UNIT         */
#define HD6_READ_1_WAIT     (unsigned)   0x42  /* READ ONE BLOCK       */
#define HD6_WRITE_1_WAIT    (unsigned)   0x43  /* WRITE ONE BLOCK      */
#define HD6_FILL_WAIT       (unsigned)   0x44  /* FILL UNIT WITH DATA  */
#define HD6_READ_WAIT       (unsigned)   0x45  /* READ BLOCKS          */
#define HD6_WRITE_WAIT      (unsigned)   0x46  /* WRITE BLOCKS         */
#define HD6_CREATE_WAIT     (unsigned)   0x47  /* CREATE UNIT          */
#define HD6_MULTI_WAIT      (unsigned)   0x4F  /* MULTI FUNCTION       */

#ifdef _MSC_VER
#pragma pack()      /* reset to align set with commandline */
#endif

#ifdef __BORLANDC__
#pragma option -a.  /* reset alignment to commandline specification */
#endif /* __BORLANDC__ */

#endif /* _RIO_H_ */
