/*--FILE HEADER-(set tabulator to 4)-------------------------------------------
;
;   filename    : EFS.H
;   version     : 0003
;   contents    : Include-file for EFS-systemcalls in C
;   author      : A.J.
;   date        : Sep 26, 1991
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Include-file for RMOS-Systemcalls
;                 Official Defines for systemcalls
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Sep 26, 1991  A.J.  0001  Original issue
;   Oct 06, 1994  P.F.  0002  Modification for flat memory model (RMOS3 only)
;   Jan 16, 1995  A.J.  0003  Modification for RMOS V3.11
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _EFS_H_
#define _EFS_H_ 1

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */
#ifndef _RMTYPES_H_
#include <rmtypes.h>
#endif  /* _RMTYPES_H_ */
#ifndef _HSFS_H_
#include <hsfs.h>
#endif  /* _HSFS_H_ */


#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
#ifndef _NOVERS
static const
char idstr_efs_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"    /* In-code identification. */
        "\1"    "EFS.H"                 "\1"
        "\2"    "0003"                  "\2"
        "\3"    "A.J."                  "\3"
};
#endif
#endif	/* defined(_ARCHITECTURE_)  ||  defined(CADUL) */


#define	EFS_CVERSION		0x0031		/*	read as: version v3.1	*/

/******************************************************************************
 *   structures for the enhanced file system
 */

#ifdef _ARCHITECTURE_
 #pragma align( _EUSE_RPB  = 1)
 #pragma align( _ESTOP_RPB = 1)
 #pragma align( _ENOOP_RPB = 1)
 #pragma align( _ECTL_RPB  = 1)
 #pragma align( _ESYS_RPB  = 1)
 #pragma align( _EDG_RPB   = 1)
 #pragma align( _EVS_RPB   = 1)
 #pragma align( _ECHV_RPB  = 1)
 #pragma align( _ESTI_RPB  = 1)
 #pragma align(  efs_addr  = 1)
 #pragma align( _TS_DESC   = 1)
 #pragma align( _EFS_START_SERVER = 1)
#endif
#ifdef _MSC_VER
#pragma pack(1)     /* set all to byte alignment */
#endif
#ifdef __BORLANDC__
#pragma option -a-  /* set all to byte alignment */
#endif

/*
 *	structure declaration of the parameter block for efs use operation
 */

/*
 *	structure declaration of an efs internal address buffer
 */

#define	BK1	0
#define	SOC	1
#define	MPI	2
#define	SH1	3

typedef	struct	{
short	unsigned	 loctsapid;
short	unsigned	 remtsapid;
long	unsigned	 subnetid;
char	unsigned	 netaddress[6];
short	unsigned	 nsapid;
		char		 res1;
		char		 medium;
		char		 res2;
		char		 res3;
		} efs_addr;

typedef	struct _EUSE_RPB	{
		char		 vol_name [2];	/* 2 bytes volume name 					*/
		char		 rvol_name [2]; /* 2 bytes volume name ( the name on the
									   server )								*/
		efs_addr 	*netaddr;		/* pointer to a field containing the net
									   address of the server				*/
		char		*netname;		/* pointer to a field containing the name
									   of the server ( address )			*/
short	unsigned	 vol_flags;		/* flags for the desired unit			*/
		char		*rvol_namep;	/* pointer to rvol_name					*/
									/* ! only if rval_name[0] == 0			*/
		} EUSE_RPB;

#if RM3
#define	EFS_NETUNIT	0x800000
#define	EFS_DGUNIT	0x400000
#define	EFS_SERROR	0x200000
#define	EFS_SPEED	0x010000
#else
#define	EFS_NETUNIT	0x80
#define	EFS_DGUNIT	0x40
#define	EFS_SERROR	0x20
#define	EFS_SPEED	0x01
#endif
#define EFS_INUSE	0x8000
#define EFS_NOMAP	0x4000

/*
 *	structure declaration of the parameter block for efs stop operation
 */

typedef	struct _ESTOP_RPB	{
		char		 vol_name[2];	/* 2 bytes volume name 					*/
		} ESTOP_RPB;

/*
 *	structure declaration of the parameter block for efs noop operation
 */

typedef	struct _ENOOP_RPB	{
		char		 vol_name[2];	/* 2 bytes volume name 					*/
short	unsigned	 vol_flags;		/* flags for the desired unit			*/
		} ENOOP_RPB;

/*
 *	structure declaration of the parameter block for efs control operation
 */

typedef	struct _ECTL_RPB	{
		char		 vol_name[2];	/* 2 bytes volume name 					*/
short	unsigned	 vol_flags;		/* flags for the desired unit			*/
		} ECTL_RPB;

/*
 *	structure declaration of the parameter block for efs system operation
 */

typedef	struct _ESYS_RPB	{
		char		 vol_name[2];	/* 2 bytes volume name 					*/
short	unsigned	 task_id;		/* task id to be started by the server	*/
short	unsigned	 mess_len;		/* length of the parameter block to be
									   transmitted							*/
		char 		*mess_adr;		/* pointer to the parameter block itself*/
		} ESYS_RPB;
 
/*
 *	structure declaration of the parameter block for efs status operation
 */

typedef struct _EVS_RPB	{
		char		 vol_name[2];
		VOL_DATA	*vol_vib;
		unsigned	 vol_flags;
		long		 free_blocks;
		unsigned	 open_files,
					 write_errors;
		} EVS_RPB;

/*
 *	structure declaration of the parameter block for efs change vib operation
 */

typedef struct _ECHV_RPB {
		char		 vol_name[2];
		VOL_DATA	*vol_data;
		} ECHV_RPB;

/*
 *	structure declaration of the parameter block for efs systime operation
 */

typedef struct _ESTI_RPB {
		char		 vol_name[2];
		char		 date[8];
		char		 time[8];
		} ESTI_RPB;

/*
 *	structure declaration of the parameter block for efs datagram operation
 */

typedef	struct _EDG_RPB	{
		char		 vol_name [2];	/* 2 bytes volume name 					*/
		efs_addr 	*netaddr;		/* pointer to a field containing the net
		                               address 								*/
		char 		*buffer;		/* pointer to buffer					*/
short	unsigned	 length;		/* length of the buffer / received bytes*/
		} EDG_RPB;

/*****************************************************************************
     constant-names for the enhanced file system
******************************************************************************/

/*  symbols for the efs opcodes, with the auto-block bit on. */

#define	EFS_SYSTEM	0x54
#define	EFS_SYSTIME	0x55	/* get system time from server			*/
#define	EFS_SNDDG	0x57	/* send a datagram						*/
#define	EFS_RCVDG	0x58	/* receive a datagram					*/
#define	EFS_CTL		0x59	/* change modes							*/
#define	EFS_USE		0x5A	/* connect to a remote station			*/
#define	EFS_STAT	0x5B	/* get the status of a connection		*/
#define	EFS_VIB		0x5C	/* change volume identification block	*/
#define	EFS_STOP	0x5D	/* stop a connection 					*/
#define	EFS_NOOP	0x5E	/* no operation ( test connection )		*/
#define	EFS_SYSCALL	0x5F	/* remote system call					*/

/*
 *	structure declaration of the datagram message for internal control
 */

typedef	struct	{
		char		 access;
		char		 mode;
		char		 res[14];
		} ctl_datagram;

#define	CPU_STOP_INFO		0x00
#define	CPU_RUN_INFO		0x01

#define	REDIR_STOP_INFO		0x10
#define	REDIR_RUN_INFO		0x11

#define	SERVER_STOP_INFO	0x20
#define	SERVER_RUN_INFO		0x21

/*  symbols for the individual bits in subdescriptor bytes and in
    file attribute bytes: */

/*
    symbols for the various completion statuses:
*/

#define	EFS_SUCCESS						RM_OK

#define	EFS_USE_ERROR					(-126)
#define EFS_CEF_ERROR					(-127)
#define EFS_WEF_ERROR					(-127)
#define EFS_REF_ERROR					(-127)
#define EFS_TEF_ERROR					(-127)
#define EFS_SEF_ERROR					(-127)
#define	EFS_CREATE_ERROR				(-128)
#define	EFS_CPRI_ERROR					(-128)
#define	EFS_TIME_ERROR					(-128)
#define EFS_STRT_ERROR					(-129)
#define EFS_SEMA_ERROR					(-129)
#define EFS_SYS_ERROR					(-129)
#define EFS_ALOC_ERROR					(-130)
#define EFS_DALOC_ERROR					(-130)
#define EFS_ALREADY_STOPPED_ERROR		(-131)
#define EFS_VOLUME_STOPPED_ERROR		(-132)
#define EFS_ALREADY_IN_USE_ERROR		(-133)
#define EFS_CONNECTION_REFUSED_ERROR	(-134)
#define EFS_STOP_OPEN_FILES_ERROR		(-135)
#define EFS_ILLEGAL_COMMAND				(-136)
#define EFS_ABORT						(-137)
#define EFS_INTERNAL_ERR				(-138)
#define EFS_NO_TRANSPORT_LAYER			(-139)
#define EFS_BAD_TRANSPORT_LAYER			(-140)
#define EFS_ILLEGAL_VERSION				(-141)

#define EFS_INVALID_REQUEST				(-180)
#define EFS_ILLEGAL_REQUEST				(-181)
#define EFS_ILLEGAL_REQUEST_FORMAT		(-182)
#define EFS_ILLEGAL_ADDRESS				(-183)
#define EFS_ILLEGAL_BUFFER_LENGTH		(-184)
#define EFS_BUFFER_TOO_SHORT			(-185)
#define EFS_BUFFER_TOO_LONG				(-186)
#define EFS_MESSAGE_INCOMPLETE			(-187)
#define EFS_NO_RESOURCES_AVAILABLE		(-188)
#define EFS_TOO_MANY_CONNECTIONS		(-189)
#define EFS_TOO_MANY_COMMANDS			(-190)
#define EFS_INTERFACE_BUSY				(-191)
#define EFS_UNKNOWN_REFERENCE			(-192)
#define EFS_DUPLICATE_REQUEST			(-193)
#define EFS_REQUEST_TIMED_OUT			(-194)
#define EFS_CONNECTION_REFUSED			(-195)
#define EFS_CONNECTION_CLOSING			(-196)
#define EFS_CONNECTION_CLOSED			(-197)
#define EFS_REMOTE_ABORT				(-198)
#define EFS_ABNORMAL_END				(-199)
#define EFS_CMD_CANCELED				(-200)
#define EFS_CMD_NOT_VALID_TO_CANCEL		(-201)
#define EFS_CMD_COMPLETED_WHILE_CANCEL	(-202)
#define EFS_ADAPTER_MALFUNC				(-203)
#define EFS_NETWORK_STOPPED				(-204)
#define EFS_NETWORK_ERROR				(-205)
#define EFS_PROTOCOL_ERROR				(-206)
#define EFS_NO_REMOTE					(-207)
#define EFS_WOULD_BLOCK					(-208)
#define EFS_NOT_SPECIFIED				(-209)

/*
    macros to determine the kind of an error code
*/

#define HSFS_ERROR(c)	( ( (c) >= H_MEM_ALLOC_FAIL ) && ( (c) <= H_PARAM_ERR ) )
#define EFS_ERROR(c)	( ( (c) >= EFS_ILLEGAL_VERSION ) && ( (c) <= EFS_USE_ERROR ) )
#define NET_ERROR(c)	( ( (c) >= EFS_NOT_SPECIFIED ) && ( (c) <= EFS_INVALID_REQUEST ) )
#define ONET_ERROR(c)	( ( (c) >  H_END_OF_FILE ) && ( (c) < 0x1000 ) )

#define	EFS_ACCGENERAL		0x0400
#define	EFS_ACCSYSTEM		0x0200
#define	EFS_ACCMOUNT		0x0100
#define	EFS_ACCREAD			0x0002
#define	EFS_ACCWRITE		0x0001
#define EFS_ACCALL			(EFS_ACCGENERAL+EFS_ACCSYSTEM+EFS_ACCMOUNT+EFS_ACCREAD+EFS_ACCWRITE)

#define	EFSCLOSEFILES		0x0010
#define	EFSSPEEDCHANNEL		0x0080
#define	EFSSEROPEN			0x0800

#define	EFSERRCIRCLE		0x8000
#define	EFSERROPENEND		0x4000
#define	EFSERRTERMINATED	0x2000
#define	EFSERRINSUFFI		0x1000

#define	EFSERRCODE			( EFSERRCIRCLE | EFSERROPENEND | EFSERRTERMINATED | EFSERRINSUFFI )

/*
 *	server flag masks
 */

#ifdef RM3
#define	SERFLMASKSTOP		0x80000000
#define	SERFLMASKRUN		0x40000000
#define	SERFLMASKERR		0x20000000
#define	SERFLMASKCONT		0x10000000
#else
#define	SERFLMASKSTOP		0x8000
#define	SERFLMASKRUN		0x4000
#define	SERFLMASKERR		0x2000
#define	SERFLMASKCONT		0x1000
#endif

/*
 *	the special start block for the EFS server
 */

typedef	struct _TS_DESC	{
		efs_addr 	 netaddr;		/* field containing the net address 	*/
short   unsigned     scount;        /* maximum count of server tasks        */
short   unsigned     ncount;        /* count of normal channels to be left  */
		} TS_DESC;

typedef	struct _EFS_START_SERVER	{
		char		 version;		/*	*/
		char		 ts_count;		/* 	*/
		TS_DESC		*ts_desc[16];	/*  */
		} EFS_START_SERVER;

#if 0
/*
 *	the special EFS svc for the server
 */

#define	SACC_SET	0
#define	SACC_GET	1
#define	SACC_DEL	2
#define	SACC_CONF	4
#define	SACC_DATA	15

struct	dev_entry{
		char		 devname[2];	/* volume name		*/
short	unsigned	 acc_r;			/* access rights	*/
				};

struct	user_entry{
		efs_addr		 user_adr;	/* efs address of redirector	*/
short	unsigned		 sta_acc;	/* access rights				*/
				};

#ifdef _ARCHITECTURE_  
 #pragma	fixedparams	("seracc")
#endif

void _FIXED _FAR seracc ( unsigned, struct user_entry *, struct dev_entry *, unsigned int * );

#endif

/*
 *	structure declaration of a vcb ( volume control block ) used by efs
 */

typedef	struct	{
	char	 vcb_name [2];	/* 2 bytes volume name 							*/
	unsigned long	 vcb_sects;		/* local : number of 512-byte blocks on volume	*/
									/* efs : reserved						*/
	unsigned int	 vcb_dsze;		/* mass storage :
								size of root directory in blocks
							 * byte device  :
							    function codes for transparent read character
							    and write character ( 1 byte each )
							 * efs device   : id of efstask
							 */
	char	 vcb_dev [2];	/* if local device : device/unit number for volume
							 * if efs device   : reserved
							 */
	unsigned int	 vcb_status;	/* volume flags : see vib_flags					*/
	unsigned long 	 vcb_bmap;		/* if mass storage :
								address of bitmap buffer for volume
							 * if byte device  : address of "directory"
							 * if efs device   : rm2 reserve space for pointer
							 *                 : rm2 reserve space for pointer - 2
							 */
	unsigned short	 vcb_flg_grp;
	unsigned int	 vcb_flg_msk;	/* if efs   device :
								flag id / flag mask ( for rbs )				*/
	union	{
	char 	*vcb_boot;		/* if local device :
								address of boot sektor ( only for msdos )	*/
	char 	*vcb_data;		/* if efs   device : pointer to data segment	*/
			} u5;
	char 	*vcb_pref_buf;	/* pointer to prefetch buffer					*/
	unsigned int	 vcb_flags;		/* volume flags : see vib_flags, plus:
							 * bit 15 : if local   device : mounted
							 *			if network device : efs use bit
							 */
							/* the next entries may be changed freely 		*/
	unsigned int	 vcb_dccb;		/* address of volume's root directory's ccb		*/
	efs_addr *vcb_nadr;		/* pointer to net address						*/
	unsigned int	 vcb_open;		/* number of files open on the volume			*/
	unsigned short	 vcb_acc_rights;/* current access rights						*/
	char	 		*vcb_ser_namep; /* unit name on server						*/
	unsigned short	 vcb_ser_desc;	/* descriptor from server						*/
	unsigned char	 vcb_ser_dw;	/* data width on server							*/
	unsigned char	 vcb_ser_ver;	/* efs version on server						*/
	char	 vcb_ser_sys[16]; /* name of server operating system			*/
	char	 vcb_sname[16];	/* name of server ( logical name of address		*/
		} vcb;

typedef struct  {
    int (_NEAR *ts_initp)(    ); /* pointer to x_efs_ts_init()               */
    int (_NEAR *ts_exitp)(    ); /* pointer to x_efs_ts_exit()               */
    int (_NEAR *initp)(    );    /* pointer to x_efs_init()                  */
    int (_NEAR *exitp)(    );    /* pointer to x_efs_exit()                  */
    int (_NEAR *callp)(    );    /* pointer to x_efs_call()                  */
    int (_NEAR *listenp)(    );  /* pointer to x_efs_listen()                */
    int (_NEAR *closep)(    );   /* pointer to x_efs_close()                 */
    int (_NEAR *sendp)(    );    /* pointer to x_efs_send()                  */
    int (_NEAR *send_eomp)(    );/* pointer to x_efs_send_eom()              */
    int (_NEAR *receivep)(    ); /* pointer to x_efs_receive()               */
    int (_NEAR *snddgp)(    );   /* pointer to x_efs_snddg()                 */
    int (_NEAR *rcvdgp)(    );   /* pointer to x_efs_rcvdg()                 */
    int (_NEAR *cancelp)(    );  /* pointer to x_efs_cancel()                */
    int (_NEAR *statusp)(    );  /* pointer to x_efs_status()                */
    int (_NEAR *errorp)(    );   /* pointer to x_efs_error()                 */
    int (_NEAR *cmpadrp)(    );  /* pointer to x_efs_cmpadr()                */
#if 0
    int (_NEAR *gcnvadrp)(    ); /* pointer to x_efs_gcnvadr()               */
    int (_NEAR *cmpcnvadrp)(    ); /* pointer to x_efs_cmpcnvadr()           */
#endif
                } jump_table;

#if defined _MSC_VER
#pragma pack()            /* reset alignment to commandline specification */
#endif

#ifdef __BORLANDC__
#pragma option -a.  /* reset alignment to commandline specification */
#endif

int	_FAR RcInitEfs			( void );
int _FAR RcDecodeEfsError	( uint, int, char * );
int _FAR RcASCIIDecodeEfs	( char * );
int	_FAR RcInitEfsLayer	( jump_table const *(_NEAR *)(uchar), char *, char,
	ushort, ushort, ushort, ushort,	ushort, ushort, ushort, ushort );
int	_FAR RcInitEfsBk1Layer	( ushort, ushort, ushort );
int	_FAR RcInitEfsSocLayer	( ushort, ushort, ushort );
int	_FAR RcInitEfsMpiLayer	( ushort, ushort, ushort );
int	_FAR RcInitEfsSh1Layer	( ushort, ushort, ushort );
int	_FAR RcInitEfsRedir	( void );
int	_FAR RcAddEfsRedirUnit	( char *, ushort, ushort );
int	_FAR RcInitEfsServer	( ushort );
int _FAR RcInitEfsWdog	( void );

jump_table const	* _NEAR x_efs_bk1_init ( uchar );
jump_table const	* _NEAR x_efs_soc_init ( uchar );
jump_table const	* _NEAR x_efs_mpi_init ( uchar );
jump_table const	* _NEAR x_efs_sh1_init ( uchar );

#endif /* _EFS_H_ */
