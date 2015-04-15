/*****************************************************************************/
/*                                                                           */
/* Project:    ########  ########   ##    ##   #######   ##       #######    */
/*             ##        ##    ##   ##    ##   ##   ##   ##   ##  ##   ##    */
/*             ##        ########   ##    ##   ##   ##   #######  ##   ##    */
/*             ##        ##         ##    ##   ##   ##        ##  ##   ##    */
/*             ########  ##         ########   #######        ##  #######    */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Filename:  RD40.H                                                       */
/*                                                                           */
/*   Author:    J. Stephan           Department:      AUT E741               */
/*   Date:      01.04.1997                                                   */
/*                                                                           */
/*   Development Kit / Compiler :  C-Compiler Organon V6.x                   */
/*                                 Intel C-Compiler   V4.x                   */
/*                                 Borland C          V4.02                  */
/*                                                                           */
/*   Copyright (C) Siemens AG 1997. All rights reserved.                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Description: Header file for SMP16-CPU040 RAM/ROM-Disk-driver           */
/*                for use with RMOS3 V3.11                                   */
/*                                                                           */
/*                - UCD/UCB-definitions                                      */
/*                - RmIO   -definitions                                      */
/*                - Systemfunction-definitions                               */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*   Modifications:                                                          */
/*                                                                           */
/*----------+-------------+-----+--------------------------------------------*/
/*  Date    |    Author   | Sign|                Description                 */
/*----------+-------------+-----+--------------------------------------------*/
/* 01.04.97 | J. Stephan  |     | original issue                             */
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

#ifndef _RD40_H_
#define _RD40_H_

#include <rmconf.h>
#include <rmtypes.h>
#include <typedefs.h>
#include <drv_com.h>

/* ========================================================================= */
/*                                                                           */
/* Definition of DCD type  (use RmDCDStruct from RMOS)                       */
/*                                                                           */
/* ========================================================================= */

/* ========================================================================= */
/*                                                                           */
/* Definition of UCD type                                                    */
/*                                                                           */
/* ========================================================================= */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (UCD_RD40_COMMON_S)
#pragma noalign (UCD_RD40_TYPE_S)
#pragma noalign (UCD_RD40_S)
#endif

typedef struct UCD_RD40_COMMON_S{
         uint          srb_border;     /* SRB-Schwellenwert                  */
         uint          srb_time;       /* SRB-Time                           */
} UCD_RD40_COMMON;

typedef struct UCD_RD40_TYPE_S{
         ulong         start_adr;      /* Physical-Start-Address of Memory.  */
         ushort        size;           /* Size of Disk in KBytes.            */
                                       /* Note: This size is also used to    */
                                       /*       check the boundaries for     */
                                       /*       accessing the disk! So it    */
                                       /*       must confirm with the actual */
                                       /*       disk size.                   */
} UCD_RD40_TYPE;

typedef struct UCD_RD40_S {
         UCD_HEAD          head;       /* head of UCD                        */
         UCD_RD40_TYPE    type;        /* unit   CPU040-part of UCD          */
         UCD_RD40_COMMON  com;         /* common CPU040-part of UCD          */
} UCD_RD40;


/* ========================================================================= */
/*                                                                           */
/* Definition of DCB type                                                    */
/*                                                                           */
/* ========================================================================= */

typedef struct DCB_RD40_S{
         DCB_HEAD          head;       /* head of DCB                        */
         UCD_RD40_COMMON   ucd_com;    /* common-part of UCD                 */
         ushort            unit_cnt;   /* number of units of the device      */
} DCB_RD40;

/* ========================================================================= */
/*                                                                           */
/* Definition of UCB type                                                    */
/*                                                                           */
/* ========================================================================= */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (UCB_RD40_TYPE_S)
#pragma noalign (UCB_RD40_ADD_S)
#pragma noalign (UCB_RD40_S)
#endif

typedef struct UCB_RD40_TYPE_S{
         ulong         part_length;    /* Disk size in bytes (0 if not exist)*/
                                       /* This is the size spezified in UCD  */
                                       /* which is used to format a disk. If */
                                       /* the disk is already formatted, this*/
                                       /* value can differ from the real size*/
         uchar _FAR   *disk_start_adr; /* pointer to beginning of Diskspace  */
#if RMFLAT                                
         ushort        buf_fill_1_sel; /* space for flat segment             */
#endif /* RMFLAT */
         uchar _FAR   *buf_adr;        /* buffer (from RmIO-Call) for R/W    */
#if RMFLAT                                
         ushort        buf_fill_2_sel; /* space for flat segment             */
#endif /* RMFLAT */
         ulong         act_adr;        /* actual Disk R/W address            */
         ulong         end_adr;        /* Disk R/W end address               */
         uchar         (*rw_funct)();  /* pointer to R/W function            */
#if RMFLAT                                
         ushort        buf_fill_3_sel; /* space for flat segment             */
#endif /* RMFLAT */
} UCB_RD40_TYPE;   

typedef struct UCB_RD40_S{
         UCB_HEAD         head;        /* head of UCB                        */
         UCD_RD40_TYPE   ucd_type;     /* unit-part of UCD                   */
         UCB_RD40_TYPE   ucb_type;     /* common UCB data                    */
} UCB_RD40;


/* ========================================================================= */
/*                                                                           */
/* Definitions for RmIO-functioncalls                                        */
/*                                                                           */
/* --------------------------------------------------------------------------*/
/* use RmRD40IO for RmIO-Calls. i.e RmRD40IO( RD40_READ_ONE,....) instead    */
/* of RmIO() to get compilerindependance Code. RmRD40IO will be substituted  */
/* to the proper function (see below)                                        */
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/* For FLAT-memory-model define spezial RmIO-Function                        */
/* ------------------------------------------------------------------------- */

#if RMFLAT
int _FIXED _FAR FlatRD40_RmIO(            uint            Function,
                                          uint            DeviceID,
                                          uint            UnitID,
                                          uint            FlagID,
                                          uint            FlagMask,
                                          RmIOStatusStruct *pState,
                                          void            *pParam );

#define RmRD40IO      FlatRD40_RmIO
#else
#define RmRD40IO      RmIO
#endif /* RMFLAT */

/* ------------------------------------------------------------------------- */
/* Definition of RmIO-Functioncodes                                          */
/* ------------------------------------------------------------------------- */

#define RD40_RESERVE         0x0       /* reserve device                    */
#define RD40_FREE            0x1       /* free device                       */
#define RD40_READ_ONE        0x2       /* read one log. sector              */
#define RD40_WRITE_ONE       0x3       /* write one log. sector             */
#define RD40_FORMAT          0x4       /* format (not supported yet)        */
#define RD40_READ_MORE       0x5       /* read more log. sect.              */
#define RD40_WRITE_MORE      0x6       /* write more log. sect.             */
#define RD40_IOCTRL          0xe       /* io-control functions              */


#define RD40_RESERVE_WAIT    0x40      /* reserve device                    */
#define RD40_FREE_WAIT       0x41      /* free device                       */
#define RD40_READ_ONE_WAIT   0x42      /* read one log. sector              */
#define RD40_WRITE_ONE_WAIT  0x43      /* write one log. sector             */
#define RD40_FORMAT_WAIT     0x44      /* format (not supported yet)        */
#define RD40_READ_MORE_WAIT  0x45      /* read more log. sect.              */
#define RD40_WRITE_MORE_WAIT 0x46      /* write more log. sect.             */
#define RD40_IOCTRL_WAIT     0x4e      /* io-control functions              */

/* ------------------------------------------------------------------------- */
/* Definition of RmIO-Subfunctionscodes for IOCTRL                           */
/* ------------------------------------------------------------------------- */

#define RD40_GET_PARAM        0x0      /* get unit parameter                 */
#define RD40_IDENT            0x2      /* identify SRAM                      */

/* ------------------------------------------------------------------------- */
/* RmIO primary status                                                       */
/* ------------------------------------------------------------------------- */

#define RD40_STS_QUEUE             0   /* request queued                     */
#define RD40_STS_BUSY              1   /* driver busy                        */
#define RD40_STS_SUCCESS           2   /* RmIO successful                    */
#define RD40_STS_WRONG_PARAM      -1   /* wrong RmIO parameter               */
#define RD40_STS_BAD_RSRV         -2   /* driver reserve error               */
#define RD40_STS_PART_NOT_EXIST   -3   /* memorycard partition not exist     */
#define RD40_STS_READ_WRITE_ERROR -5   /* read or write error                */

/* ------------------------------------------------------------------------- */
/* RmIO functions return value                                               */
/* ------------------------------------------------------------------------- */

#define RD40_SVC_END               TRUE   /* request function finished       */
#define RD40_SVC_SLEEP             FALSE  /* request function not finished   */

/* ------------------------------------------------------------------------- */
/* Definitions for parameterblock of RmIO functioncalls                      */
/* ------------------------------------------------------------------------- */

#if defined(_ARCHITECTURE_) || defined(CADUL)
#pragma noalign (RD40_READ_WRITE_TYP_S)
#pragma noalign (RD40_READ_ONE_TYP_S)
#pragma noalign (RD40_WRITE_ONE_TYP_S)
#pragma noalign (RD40_READ_MORE_TYP_S)
#pragma noalign (RD40_WRITE_MORE_TYP_S)
#pragma noalign (RD40_IOCTRL_TYP_S)
#pragma noalign (RD40_IO_GET_PARAM_S)
#pragma noalign (RD40_IO_IDENT_S)
#endif

/* ----------------------------------------------------------------------- */
/* In flat-environments (i.e. Borland C) a pointer is 4 bytes long         */
/* (near-pointer). For RMOS we need a far-Pointer (6 bytes). In order to   */
/* add the selector to the pointer we let room for this selector (buf_fill)*/
/* witch is added within the Flat-RmIO-Function  FlatMC2_RmIO().           */
/* (the macro _FAR will be expanded to spaces in Flat evironment)          */
/* ----------------------------------------------------------------------- */

typedef struct RD40_READ_WRITE_TYP_S{
      ulong           lba;                /* logical block address         */
      void _FAR *     buf_adr;            /* buffer address                */
#if RMFLAT                                
      ushort          buf_fill_sel;       /* space for flat segment        */
#endif /* RMFLAT */
      ushort          num_blk;            /* block amount                  */ 
   } RD40_READ_WRITE_TYP;


typedef struct RD40_READ_ONE_TYP_S{
      ulong           lba;                /* logical block address         */
      void _FAR *     buf_adr;            /* buffer address                */
#if RMFLAT                                
      ushort          buf_fill_sel;       /* space for flat segment        */
#endif /* RMFLAT */
      ushort          reserve;
   } RD40_READ_ONE_TYP;


typedef struct RD40_WRITE_ONE_TYP_S{
      ulong           lba;                /* logical block address         */
      void _FAR *     buf_adr;            /* buffer address                */
#if RMFLAT
      ushort          buf_fill_sel;       /* space for flat segment        */
#endif /* RMFLAT */
      ushort          reserve;
   } RD40_WRITE_ONE_TYP;


typedef struct RD40_READ_MORE_TYP_S{
      ulong           lba;                /* logical block address         */
      void _FAR *     buf_adr;            /* buffer address                */
#if RMFLAT
      ushort          buf_fill_sel;       /* space for flat segment        */
#endif /* RMFLAT */
      ushort          num_blk;            /* block amount                  */
   } RD40_READ_MORE_TYP;


typedef struct RD40_WRITE_MORE_TYP_S{
      ulong           lba;                /* logical block address         */
      void _FAR *     buf_adr;            /* buffer address                */
#if RMFLAT
      ushort          buf_fill_sel;       /* space for flat segment        */
#endif /* RMFLAT */
      ushort          num_blk;            /* block amount                  */
   } RD40_WRITE_MORE_TYP;


typedef struct RD40_IOCTRL_TYP_S{
      ushort          sub_fct;            /* subfunction                   */
      ushort          byte_num;           /* subfunction specific parameter*/
      void _FAR *     buf_adr;            /* Pointer to subfct-parameterbl.*/
#if RMFLAT
      ushort          buf_fill_sel;       /* space for flat segment        */
#endif /* RMFLAT */
      ushort          reserve;
   } RD40_IOCTRL_TYP;

                /*-----------------------------------*/
                /* typedefs for IOCTRL subfct-blocks */
                /*-----------------------------------*/

typedef struct RD40_IO_GET_PARAM_S{
      ushort           unit_cnt;         /* number of units of the device */
      UCD_RD40_COMMON  ucd_com;          /* common parameter of UCD       */
      UCD_RD40_TYPE    ucd_type;         /* unit   parameter of UCD       */
      UCB_RD40_TYPE    ucb_type;         /* parameter from UCB            */
   } RD40_IO_GET_PARAM;


/* ========================================================================= */
/*                                                                           */
/* definitions for systemfct. x_rd40_init()                                  */
/*                                                                           */
/* ========================================================================= */

extern int _FAR _FIXED x_rd40_init(uint console_flag);

/* ------------------------------------------------------------------------- */
/* errorcodes                                                                */
/* ------------------------------------------------------------------------- */

#define RD40_NO_ERROR              0  /* success                            */
#define RD40_ERR_NO_MEM           -1  /* error on memoryrequest from heap   */
#define RD40_ERR_HSFS_CREATE      -2  /* error from function createvib()    */
#define RD40_ERR_NO_DEVICE_INST   -3  /* RD40-driver not installed         */
#define RD40_ERR_HSFS_CHANGE      -4  /* error from function changevib()    */
#define RD40_ERR_HSFS_STATUS      -5  /* error from function getvolumestatus*/
#define RD40_ERR_HSFS_VIB_EXIST   -6  /* VIB already exists (cannot create) */
#define RD40_ERR_RMIO             -7  /* general RmIO-SVC-error             */
#define RD40_ERR_DEVICE           -8  /* general device error               */
#define RD40_ERR_UNIT_CNT         -9  /* unit count wrong.                  */
#define RD40_ERR_HSFS_REMAP       -10 /* Disk format error                  */
#define RD40_ERR_PARAM            -11 /* parameter error (unit id wrong)    */

/* ------------------------------------------------------------------------- */
/* general params                                                            */
/* ------------------------------------------------------------------------- */

#define RD40_BLK_SIZE               (ushort) 512     /* sectorsize           */

#endif  /* _RD40_H_ */
