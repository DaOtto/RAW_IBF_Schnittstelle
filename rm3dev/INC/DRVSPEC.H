/*--FILE HEADER---------------------------------------------------------------
;
;   filename    : DRVSPEC.H
;   version     : 0002
;   contents    : Structures for UCD control data blocks
;   author      : K.P.H.
;   date        : Feb 24, 1995
;
;---FUNCTION AND RMOS ENVIRONMENT---------------------------------------------
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER--------------------------------------------------------
;
;---MODIFICATION HEADER-------------------------------------------------------
;
;   Jan 12, 1995  K.P.H. 0001  Original issue
;   Feb 24, 1995  K.P.H. 0002  Additional Modification for RMOS2
;
;---END OF MODIFICATION HEADER----------------------------------------------*/

#ifndef _DRVSPEC_H_
#define _DRVSPEC_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _RMTYPES_H_
#include <rmtypes.h>
#endif  /* _RMTYPES_H_ */

#define UCDSIZE sizeof(RmUCDStruct)-sizeof(RmUCDHeadStruct) /* size of UCD specific data */

#if RM3
typedef void ( _NEAR _FIXED * _NEAR RM_FPTR_VOID)(void);
#else
typedef void ( _FAR  _FIXED * _FAR  RM_FPTR_VOID)(void);
#endif

/*---------------------------------------------------------------------*/
/* device driver specific parameter UCD block                          */
/*---------------------------------------------------------------------*/
 
/* --------------- */
/* ram-disk-unit   */
/* --------------- */
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_RAMDISK_PORT_TAG)
#endif
typedef struct UCD_RAMDISK_PORT_TAG
{
    void _FAR       *start;         /* startadr. of RAM-disk            */
    ushort          nblk;           /* number of blocks                 */
    ushort          blklen;         /* blocklength                      */
    uchar           ram_mode;       /* accessmode                       
                                       BIT 4: RAM start address 
                                              (0=off/seg, 1=physical)
                                    */
    uchar           ram_spec;       /* reserved ( 0 )                   */
} UCD_RAMDISK_PORT;

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_RAMDISK_TAG)
#endif
typedef struct UCD_RAMDISK_TAG {
    RmUCDHeadStruct   header;
    UCD_RAMDISK_PORT  spec;
    uchar             port[UCDSIZE-sizeof(UCD_RAMDISK_PORT)];
} UCD_RAMDISK;

/* --------------- */
/* FD0-UCD         */
/* --------------- */
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_FD0_PORT_TAG)
#endif
typedef struct UCD_FD0_PORT_TAG
{
    /* disk drive parameter */
    ushort          type;           /* disk type                        
                                        BIT 0: number of sides (=double, must be 1) 
                                        BIT 1: density track-0 (=double, must be 1)
                                        BIT 2: density track-N (=double , must be 1)
                                        BIT 3: drive type (0=standard, 1=mini)
                                        BIT 4,5: sector len track-0 (=512, must be 10 = 2)
                                        BIT 6,7: sector len track-N (=512, must be 10 = 2)
                                        BIT 8-13: reserved
                                        BIT 14: track-read buffer (0=disabled, 1=enabled)
                                        BIT 15: reserved
                                    */
    ushort          select;         /* disk select                  
                                        BIT 0-3: drive select
                                            0000=no drive
                                            0001=drive-0 selected
                                            0010=drive-1 selected
                                            0100=drive-2 selected
                                            1000=drive-3 selected
                                        BIT 4-15: reserved
                                    */
    ushort          control;        /* disk control mode
                                        BIT 0-13: reserved
                                        BIT 14: double step (0=disabled, 1=enabled)
                                        BIT 15:high density (0=disabled, 1=enabled)
                                    */
    ushort          max_track;      /* number of tracks per side        */
    ushort          max_sec_n;      /* number of sectors per track in track 1..N */
    ushort          max_sec_0;      /* number of sectors in track 0     */
    ushort          max_retry;      /* number of retries 
                                        (LSB=max. retries READ/WRITE
                                         MSB=max. retries SEEK/RECAL
                                         0=no retry)    */
    ushort          format;         /* format mode (LSB=fill byte, MSB=sector interleave */
    ushort          time_out;       /* time out                         */
    ushort          board;          /* board id (should be 0)           */
    
    /* next adapter-ID parameter optional if already defined */
    ushort          count_3;        /* head delay time    #msec, 0=default */
    ushort          count_4;        /* motor runtime      #msec, 0=default */
    ushort          count_5;        /* motor startup time #msec, 0=default */
    ushort          dma_page;       /* dma_page port address               */
    ushort          base_dma;       /* dma base port address               */
    ushort          base_fdc;       /* fdc base port address               */
    ushort          dma_id;         /* unit-ID of the DMA-channel (should be -1) */
    ushort          pool_id;        /* memorypool-ID                       */
    
} UCD_FD0_PORT;

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_FD0_TAG)
#endif
typedef struct UCD_FD0_TAG {
    RmUCDHeadStruct   header;
    UCD_FD0_PORT      spec;
    uchar             port[UCDSIZE-sizeof(UCD_FD0_PORT)];
} UCD_FD0;

/* --------------- */
/* HD0-UNIT        */
/* --------------- */
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_HD0_PORT_TAG)
#endif
typedef struct UCD_HD0_PORT_TAG
{
    /* disk drive parameter */
    uchar           type_mode;      /* disk type
                                        BIT 0-3: stepping rate
                                        BIT 4:   drive select
                                        BIT 5-6: reserved (should be 00)
                                        BIT 7:   track read buffer (0=disabled, 1=enabled)
                                    */
    uchar           type_id;        /* type identify ID
                                        0=not used
                                        -1=unknown
                                    */
    void _FAR       *hdparam;       /* hard-disk parameter address (0=not used)    */
    ushort          max_cyl;        /* number of cylinders/disk  (1..4096)         */
    uchar           max_sec;        /* number of sectors/track (0..64)             */
    uchar           max_head;       /* number of heads  (1..16)                    */
    ushort          pre_cyl;        /* start write precomp. cylinder (-1=not used) */
    ushort          pos_cyl;        /* landing zone cylinder number (-1=not used)  */
    uchar           control;        /* disk control mode
                                        BIT 0-2,4,5: reserved (should be 0)
                                        BIT 3: more than 8 heads (0=false, 1=true)
                                        BIT 6,7: disable retries (0=false, 1=true)
                                    */
                                        
    uchar           format;         /* interleave factor per track (0=factor 1)*/
    uchar           time_out;       /* time out rate for read/write (256 msec units) */
    uchar           max_retry;      /* max. retries read/write (0=no retry) */
    ushort          board;          /* adapter id (should be 0) */
    
    /* next adapter-ID parameter optional if already defined */
    ushort          count_rdy;      /* max. delay before rdy=1 (256 msec, 0=default) */
    ushort          count_drq;      /* max. delay before drq=1 (256 msec, 0=default) */
    ushort          disk_req;       /* fdc fixed-disk-register address (3F6H or 376H)*/
    
    ushort          dma_page;       /* dma_page port address            */
    ushort          base_dma;       /* dma base port address            */
    ushort          base_hdc;       /* hdc base port address            */
    ushort          dma_id;         /* unit-ID of the DMA-channel (should be -1) */
    ushort          pool_id;        /* memorypool-ID                    */
    
} UCD_HD0_PORT;

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_HD0_TAG)
#endif
typedef struct UCD_HD0_TAG {
    RmUCDHeadStruct   header;
    UCD_HD0_PORT      spec;
    uchar             port[UCDSIZE-sizeof(UCD_HD0_PORT)];
} UCD_HD0;

/* --------------- */
/* BYT-UNIT-HEADER */
/* --------------- */
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_BYT_HEAD_TAG)
#endif
typedef struct UCD_BYT_HEAD_TAG
{
    ushort          ucmode;         /* UCD_UCMODE: UNIT CONTROL MODE
                                        BIT 0:      I/O-MODE    (0= DIRECT, 1= MEMORY)
                                        BIT 1:      STATUS-CHECK (0= NO USE, 1= CHECK)
                                        BIT 2:      STATUS RET. (0= NO USE, 1= RETURN)
                                        BIT 3-4:    UNIT-TYPE:
                                            00= INPUT AND OUTPUT, 10= ONLY INPUT
                                            01= ONLY OUTPUT     , 11= RESERVED
                                        BIT 5:      OUTPUT-TRANS (0= NO USE, 1= TRANSLATE)
                                        BIT 6:      INPUT-TRANS. (0= NO USE, 1= TRANSLATE)
                                        BIT 7:      PARAM-RESTR. (0= NO USE, 1= RESTRICTED)
                                        BIT 8-11:   USART-TYPE:
                                            0000= SAB  8251     , 1000= EGA/KEYBOARD
                                            0001= RESERVED      , 1001= UART 8250
                                            0010= RESERVED      , 1010= RESERVED     
                                            0011= RESERVED      , 1011= RESERVED     
                                            0100= SCC  8530 COMN, 1100= RESERVED
                                            0101= PPI  8255 STRB, 1101= RESERVED
                                            0110= TIMER E18/E19 , 1110= RESERVED
                                            0111= RESERVED      , 1111= RESERVED
                                        BIT 12:     LINE-FEED   (0= DISABLED, 1= ENABLED)
                                        BIT 13:     HISTORY-POOL (0= DISABLED, 1= ENABLED)
                                        BIT 14:     RESERVED     (SHOULD BE 0)
                                        BIT 15:     DUPLEX-MODE  (0= DISABLED, 1= ENABLED)
                                    */
    ushort          prtseg;         /* MEMORY-MAPPED-I/O-SEGMENT (UNUSED IF DIRECT-I/O) */
    uint            prtdat;             
    uint            prtcmd;         /* PORT-INDEX = 1 */
    uint            port_2;         /* PORT-INDEX = 2 */
    uint            port_3;         /* PORT-INDEX = 3 */
    uint            prtsta;         /* PORT-INDEX = 4)*/
    ushort          stmode;
    ushort          staret;
    ushort          topchr;
    ushort          timout;
    void _FAR *     tabbuf;         /* ADDRESS UNIT TRANSLATION TABLE (0= NOT USED) */
    uchar           poolid;         /* HISTORY/EXTRA POOL-ID (-1= NOT USED)         */
    uchar           poolen;         /* LENGTH FOR EXTRA BUFFER (UNEXPECTED INPUT)   */
    uchar           unscr1;         /* UNSOLICITED START CHAR #1 (0= NOT USED)      */
    uchar           unscr2;         /* UNSOLICITED START CHAR #2 (0= NOT USED)      */
    uchar           recovr;         /* RESERVED (SHOULD BE 0)                       */
    uchar           modext;         /* UNIT CONTROL MODE EXTENSION
                                        BIT 0:  SPECIAL XPARENT READ/WRITE HANDLING (0= NORMAL, 1= SPECIAL)
                                        BIT 1:  SPECIAL XON/XOFF HANDLING (0= NORMAL, 1= SPECIAL) 
                                        BIT 2:  RESERVED (SHOULD BE 0)
                                        BIT 3:  RESERVED (SHOULD BE 0)
                                        BIT 4-5:UNIT CONTROL-TABLE FOR SPECIAL CHARACTERS:
                                            00= SPECIAL TABLE-0 (DS2)
                                            10= SPECIAL TABLE-2 (IBM PC/AT)
                                            01= SPECIAL TABLE-1 (DS3) 
                                            11= SPECIAL TABLE-3 (USER DEF)
                                        BIT 6:  RESERVED (SHOULD BE 0) 
                                        BIT 7:  RESERVED (SHOULD BE 0) 
                                    */
    ushort          icount;         /* INITIALIZATION LOOP-COUNTER OF INIT BYTES   */
} UCD_BYT_HEAD;

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_BYT_PORT_TAG)
#endif
typedef struct UCD_BYT_PORT_TAG
{
    UCD_BYT_HEAD    header;
    ushort          mobyte[(UCDSIZE-(sizeof(UCD_BYT_HEAD)))/2];
} UCD_BYT_PORT;

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_BYT_TAG)
#endif
typedef struct UCD_BYT_TAG
{
    RmUCDHeadStruct    header;
    UCD_BYT_PORT       byt;
} UCD_BYT;

/* ---------------- */
/* 3964-UNIT-HEADER */
/* ---------------- */
#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_3964_HEAD_TAG)
#endif
typedef struct UCD_3964_HEAD_TAG
{
    ushort          ucmode;         /* UCD_UCMODE: UNIT CONTROL MODE
                                        BIT 0:      I/O-MODE    (0= DIRECT, 1= MEMORY)
                                        BIT 1:      STATUS-CHECK (0= READ, 1= CHECK)
                                        BIT 2:      STATUS RET. (0= NO USE, 1= RETURN)
                                        BIT 3-4:    STATUS-MODE:
                                            00= NO STATUS,   10= STS ON WRITE
                                            01= STS ON READ, 11= STS ON READ&WRITE
                                        BIT 5-7:    RESERVED (SHOULD BE 0)
                                        BIT 8-11:   USART-TYPE:
                                            0000= SAB  8251     , 1000= RESERVED
                                            0001= RESERVED      , 1001= UART 8250
                                            0010= RESERVED      , 1010= RESERVED     
                                            0011= RESERVED      , 1011= RESERVED     
                                            0100= SCC  8530 COMN, 1100= RESERVED
                                            0101= RESERVED      , 1101= RESERVED
                                            0110= RESERVED      , 1110= RESERVED
                                            0111= RESERVED      , 1111= RESERVED
                                        BIT 12-15:  RESERVED (SHOULD BE 0)
                                    */
    ushort          prtseg;         /* MEMORY-MAPPED-I/O-SEGMENT (UNUSED IF DIRECT-I/O) */
    uint            prtdat;             
    uint            prtcmd;         /* PORT-INDEX = 1 */
    uint            port_2;         /* PORT-INDEX = 2 */
    uint            port_3;         /* PORT-INDEX = 3 */
    uint            prtsta;         /* PORT-INDEX = 4)*/
    ushort          stmode;
    ushort          staret;
    ushort          free_0;
    ushort          timout;
    ushort          recovr;         /*(LOW)  RECOVERY COUNTER FOR WAIT IF STAUS FAILED */
                                    /*(HIGH) RESERVED (SHOULD BE 0)                    */
    ushort          free_1;         /* RESERVED (SHOULD BE 0)                          */
    ushort          blklen;         /* BLOCK LENGTH                                    */
    ushort          pcmode;         /* PROCEDURE CONTROL MODE                          */
                                    /*
                                        BIT 0:      CONFLICT PRIORITY (0= LOW (SLAVE), 1= HIGH (MASTER))
                                        BIT 1:      BLOCK CHECK MODE  
                                            (0= DISABLE BCC SEND (3964 -MODE))
                                            (1= ENABLE  BCC SEND (3964R-MODE))
                                        BIT 2:      MONITORING TIME   
                                            (0: TQ= 2000 MSEC, TZ= 200 MSEC)
                                            (1: TQ=  550 MSEC, TZ= 100 MSEC)
                                        BIT 3:      WATCH ACKNOWLEDGE TQ-TIME (0= ENABLE, 1= DISABLE)
                                        BIT 4:      WATCH CHARACTER   TZ-TIME (0= ENABLE, 1= DISABLE)
                                        BIT 5:      WATCH READ ON STX RECEIVED(0= ENABLE, 1= DISABLE)
                                        BIT 6-7:    RESERVED (SHOULD BE 0)
                                        BIT 8:      RECEIVER CHARACTER SIZE    (0= 8-BIT, 1= 7-BIT)
                                        BIT 9-15:   RESERVED (SHOULD BE 0)
                                    */

    ushort          tq_val;         /* MONITORING TIME TQ-VALUE (<> 0 = 10 MSC UNITS) */
    ushort          tz_val;         /* MONITORING TIME TZ-VALUE (<> 0 = 10 MSC UNITS) */
    ushort          free_4;         /* RESERVED (SHOULD BE 0)                         */
    ushort          free_5;         /* RESERVED (SHOULD BE 0)                         */
    ushort          icount;         /* INITIALIZATION LOOP-COUNTER OF INIT BYTES      */
} UCD_3964_HEAD;

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_3964_PORT_TAG)
#endif
typedef struct UCD_3964_PORT_TAG
{
    UCD_3964_HEAD   header;
    ushort          mobyte[(UCDSIZE-(sizeof(UCD_3964_HEAD)))/2];
} UCD_3964_PORT;

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign(UCD_3964_TAG)
#endif
typedef struct UCD_3964_TAG
{
    RmUCDHeadStruct   header;
    UCD_3964_PORT     c3964;
} UCD_3964;

/* used to init const static UCD_BYT for EGA, which uses data at offset 0x60 in UCD */
#define TEN_NULLS 0,0,0,0,0,0,0,0,0,0
#if RM3
/* OFFSET 60H IS 40 NULL BYTES -> 20 NULL WORDS */
#define UCD_BYT_EGA_PAGE_CTRL TEN_NULLS, TEN_NULLS
#else
/* OFFSET 60H IS 54 NULL BYTES -> 27 NULL WORDS */
#define UCD_BYT_EGA_PAGE_CTRL   TEN_NULLS, TEN_NULLS, 0,0,0,0,0,0,0
#endif
#if RM3
#define EGA_PAGE_0 20
#define EGA_PAGE_1 23
#define EGA_PAGE_2 26
#define EGA_PAGE_3 29
#else                            
#define EGA_PAGE_0 27
#define EGA_PAGE_1 30
#define EGA_PAGE_2 33
#define EGA_PAGE_3 36
#endif

#endif /* _DRVSPEC_H_ */
