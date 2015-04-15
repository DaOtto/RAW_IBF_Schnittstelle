/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : HSFS.H
;   version     : 0012
;   contents    : Header file for HSFS calls
;   author      : W.K.
;   date        : Oct 6, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Header file to use with HSFS calls in C
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   July 31, 1992   0009   Original issue after beta test
;   May  10, 1993   0010   Added Borland C/C++ Support
;   Sep  19, 1994   0011   corrected MS_BOOT_SEC to be really 512 Bytes
;   Oct  06, 1994   0012   Modifications for flat memory model
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _HSFS_H_
#define _HSFS_H_ 1

#include <rmcomp.h>

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
#ifndef _NOVERS
 static const char idstr_hsfssvc_h [] =
{
        "\0"    "(C) SIEMENS AG 1994"   "\0"    /* Incode identification. */
        "\1"    "HSFS.H"                "\1"
        "\2"    "0012"                  "\2"
        "\3"    "W.K."                  "\3"
};
#endif
#endif

#ifdef _ARCHITECTURE_
 #pragma align( _MS_BOOT_SEC = 1)
 #pragma align( _VOL_DATA = 1)
 #pragma align( _DEV_DATA_FIELD = 1)
 #pragma align( _DIR_ENTRY = 1)
 #pragma align( _MDR_RPB = 1)
 #pragma align( _OC_RPB = 1)
 #pragma align( _OCD_RPB = 1)
 #pragma align( _RW_RPB = 1)
 #pragma align( _SR_RPB = 1)
 #pragma align( _VS_RPB = 1)
 #pragma align( _CKP_RPB = 1)
 #pragma align( _CTV_RPB = 1)
 #pragma align( _CHV_RPB = 1)
#endif
#ifdef _MSC_VER
#pragma pack(1)     /* Align on byte  */
#endif

#ifdef __BORLANDC__
#pragma option -a-	/* set all to byte alignment */
#endif /* __BORLANDC__ */

/*
 * MS-DOS bootsector definition
 */

typedef struct _MS_BOOT_SEC
{
    char            boot_jmp[3];
    char            disk_name[8];
    unsigned short  bytes_per_sec;
    char            sec_per_clust;
    unsigned short  res_sec;
    char            no_of_fats;
    unsigned short  root_entries;
    unsigned short  partition_sec1;
    char            id_byte;
    unsigned short  sec_per_fat;
    unsigned short  sec_per_track;
    unsigned short  sides;
    long            hidden_sec;
    long            partition_sec2;
    char            fill_block[476];
} MS_BOOT_SEC;

/*
 * Volume identification block definition
 */

typedef struct _VOL_DATA
{
    char            vol_name[2];
    unsigned long   no_of_blocks;
    unsigned int    no_of_root_blocks;
    unsigned char   device_id;
    unsigned char   unit_id;
    unsigned int    flags;
    char            *fat_buf;
#if RMFLAT
    unsigned short  fbuf_fill;	/* Fill word, selector not used in flat model */
#endif
    unsigned long   start_block;
 /* MS_BOOT_SEC     *boot_sec;       for compatibility we use a void ptr */
    void            *boot_sec;
#if RMFLAT
    unsigned short  boot_fill;	/* Fill word, selector not used in flat model */
#endif
} VOL_DATA;

/*
 * Definitions for opening device files
 */

typedef struct _DEV_DATA_FIELD
{
    unsigned char   device_id;
    unsigned char   unit_id;
    unsigned char   read_code;
    unsigned char   write_code;
    unsigned char   is_block_dev;
    unsigned short  block_size;
} DEV_DATA_FIELD;

/*
 * Directory entry record definition
 */

typedef struct _DIR_ENTRY
{
    char            file_name[8];
    char            delim;
    char            file_ext[3];
    unsigned short  blocking;
    unsigned long   file_size;
    unsigned short  reserved1[3];
    char            attrib;
    unsigned char   reserved2;
    unsigned short  time;
    unsigned short  date;
    unsigned short  reserved3;
} DIR_ENTRY;

/*
 * Definitions for rpbs to mount, dismount, force dismount or remap a volume
 */

typedef struct _MDR_RPB
{
    char            vol_name[2];
    unsigned int    format;
} MDR_RPB;

/*
 * Definitions for rpbs to open or close a file
 */

typedef struct _OC_RPB
{
    char            *file_name;
    unsigned int    rec_size;
    unsigned long   rec_count;
    unsigned int    file_channel;
    char            file_attribs,
                    oc_options;
    unsigned int    dir_channel;
    unsigned short  wr_date;
    unsigned short  wr_time;
} OC_RPB;

/*
 * Definitions for rpbs to create a device file entry
 */

typedef struct _OCD_RPB
{
    char            *file_name;
    DEV_DATA_FIELD  *device_file;
#if RM3
    unsigned short  fillup;
#else
    unsigned long   fillup;
#endif
    unsigned int    file_channel;
    char            file_attribs,
                    oc_options;
    unsigned int    dir_channel;
    unsigned short  wr_date;
    unsigned short  wr_time;
} OCD_RPB;

/*
 * Definitions for rpbs to read or write records in a file
 */

typedef struct _RW_RPB
{
    unsigned int    file_channel;
    unsigned long   first_rec;
    unsigned int    nr_recs;
    char            *buffer_addr;
    unsigned int    recs_xferred;
    char            terminator,
                    rw_options;
} RW_RPB;

/*
 * Definitions for rpbs to search a directory for a file name
 */

typedef struct _SR_RPB
{
    char            *file_name;
    unsigned int    dir_channel,
                    first_rec;
    DIR_ENTRY       *found_name;
    unsigned int    found_rec,
                    padding;
 } SR_RPB;

/*
 * Definitions for rpbs to get volume status
 */

typedef struct _VS_RPB
{
    char            vol_name[2];
    VOL_DATA        *vol_vib;
    unsigned int    vol_flags;
    unsigned long   free_blocks;
    unsigned int    open_files,
                    write_errors;
} VS_RPB;

/*
 * Definitions for rpbs to execute checkpoints
 */

typedef struct _CKP_RPB
{
    unsigned int    file_channel;
} CKP_RPB;

/*
 * Definitions for rpbs to create a vib
 */

typedef struct _CTV_RPB
{
    VOL_DATA        *new_vib;
    char            pool_id;
} CTV_RPB;

/*
 * Definitions for rpbs to change a vib
 */

typedef struct _CHV_RPB
{
    char            vol_name[2];
    VOL_DATA        *vol_data;
} CHV_RPB;

/*
 * HSFS opcodes, with wait bit on
 */

#define H_OPEN                0x40
#define H_CLOSE               0x41
#define H_READ                0X42
#define H_WRITE               0x43
#define H_SEARCH              0x44
#define H_MOUNT               0x45
#define H_DISMT               0x46
#define H_REMAP               0x47
#define H_FDIS                0x48
#define H_CHKPT               0x49
#define H_VSTAT               0x4a
#define H_CVIB                0x4b
#define H_CTVIB               0x4c

/*
 * Subdescriptor bytes and file attributes
 */

#define OPT_CREATE            0x01
#define OPT_RENAME            0x01
#define OPT_AUTO              0x01
#define OPT_LOCK              0x02
#define OPT_DELETE            0x02
#define OPT_HALT              0x02
#define OPT_ATTR              0x04
#define OPT_REC_LOCK          0x08
#define OPT_AUTO_SEEK         0x10
#define OPT_DATE              0x80

/*
 * Directory entry attributes
 */

#define ATR_SYSTEM            0x01
#define ATR_HIDDEN            0x02
#define ATR_RDONLY            0x04
#define ATR_DIREC             0x08
#define ATR_LABEL             0x10
#define ATR_ARCH              0x20
#define ATR_DEVICE            0x80

/*
 * Volume flags
 */

#define VL_NO_WRITE_BUF       0x01
#define VL_NODATE             0x02
#define VL_WRITE_FLAG         0x04
#define VL_AUTO_DISMOUNT      0x08
#define VL_NO_IO_BUF          0x10
#define VL_NO_REMAP           0x20
#define VL_NO_MOUNTING        0x40
#define VL_NET                0x80
#define VL_REMOVABLE          0x100
#define VL_512                0x400
#define VL_MOUNTED            0x8000

/*
 * HSFS completion status
 */

#define H_END_OF_FILE           1
#define H_SUCCESS               0
#define H_PARAM_ERR           (-1)
#define H_READ_IO_ERR         (-2)
#define H_WRITE_IO_ERR        (-3)
#define H_INSUFFICIENT_SPACE  (-4)
#define H_FILE_LOCKED         (-5)
#define H_NO_SUCH_FILE        (-6)
#define H_NO_SUCH_RECORD      (-7)
#define H_NO_SUCH_VOLUME      (-8)
#define H_ATTRIBUTE_CLASH     (-9)
#define H_HSFS_SATURATED      (-10)
#define H_NO_SUCH_CHANNEL     (-11)
#define H_NOT_A_DIRECTORY     (-12)
#define H_RECORD_LOCKED       (-14)
#define H_MOUNT_FAILURE       (-15)
#define H_DIRECTORY_NEEDED    (-16)
#define H_RENAME_CLASH        (-17)
#define H_ILLEGAL_NAME        (-18)
#define H_RIO_SVC_ERROR       (-19)
#define H_ILLEGAL_FORMAT      (-20)
#define H_REMAP_PROTECTED     (-21)
#define H_NON_EMPTY_DIR       (-22)
#define H_VIB_EXISTS          (-23)
#define H_MEM_ALLOC_FAIL      (-24)
#define H_MAX_HSFS_ERRORCODE  (-25)

#ifdef _MSC_VER
#pragma pack()
#endif

#ifdef __BORLANDC__
#pragma option -a.	/* reset alignment to commandline specification */
#endif /* __BORLANDC__ */

#endif
