/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : VC_RIO.H
;   version     : 0013
;   contents    : Include-File for RIO-Systemcalls in C
;		  for the RMOS3-DOS VC-Driver
;   author      : P.J.
;   date        : July 17, 1992
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Structures and Macros for RIO's to the RMOS3-DOS
;		  VC ( virtual console ) Driver.
;
;   note	: - This header file only supports ANSI Standard C.
;		  - These definitions will probably be superceded by
;		    new definitions in rio.h
;
;   RMOS3-PC1/DOS
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   July 16, 1992   0012   Added modification header
;   Dec  14, 1994   0013   Modification for RMOS V3.1
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _VC_RIO_H_
#define _VC_RIO_H_

#include <rmcomp.h>
#include <svc.h>

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
#ifndef _NOVERS
 static const char idstr_vc_rio_h [] =
{
        "\0"    "(C) SIEMENS AG 1994"   "\0"    /* In-code identification. */
        "\1"    "VC_RIO.H"              "\1"
        "\2"    "0013"                  "\2"
        "\3"    "P.J."                  "\3"
};
#endif
#endif  /* defined(_ARCHITECTURE_)  ||  defined(CADUL) */

/*
----------------------------------------------------------------------------
Compiler dependant pragmas
----------------------------------------------------------------------------
*/
#ifdef _ARCHITECTURE_

/* INTEL C */
#pragma noalign ( status_struct )
#pragma noalign ( vc_read_parm )
#pragma noalign ( vc_write_parm )
#pragma noalign ( vc_write_read_parm )
#pragma noalign ( vc_spec_rw_parm )
#pragma noalign ( vc_check_abo_parm )

#else
#ifdef _MSC_VER

/* Microsoft C */
/* This is quite pointless, because a microsoft C DOS program will never
   access the structures in this file. However, I do include it in
   some of the modules in RM3_CON.EXE for the macros, and the Intel pragmas
   upset Microsoft.
*/
#pragma pack (1)

#endif
#endif

/*
----------------------------------------------------------------------------
Function codes without the Wait Option
----------------------------------------------------------------------------
*/

#define VC_RESERVE	      0x00  /* RESERVE UNIT	    */
#define VC_RELEASE	      0x01  /* RELEASE UNIT	    */
#define VC_READ 	      0x02  /* NORMAL READ	    */
#define VC_WRITE	      0x03  /* NORMAL WRITE	    */
#define VC_WRT_XREAD	      0x06  /* WRITE & TRANSP. READ */
#define VC_WRT_READ	      0x07  /* WRITE & NORMAL READ  */
#define VC_SPEC_READ	      0x0A  /* SPECIAL READ	    */
#define VC_SPEC_WRITE	      0x0B  /* SPECIAL WRITE	    */
#define VC_POLL_XBUF	      0x0C  /* POLL EXTRA-BUFFER    */
#define VC_CHECK_ABO	      0x0D  /* CHECK FOR ABORT-FLAG */

/*
----------------------------------------------------------------------------
Function codes with the Wait Option
----------------------------------------------------------------------------
*/

#define VC_RESERVE_WAIT       0x40  /* RESERVE UNIT	    */
#define VC_RELEASE_WAIT       0x41  /* RELEASE UNIT	    */
#define VC_READ_WAIT	      0x42  /* NORMAL READ	    */
#define VC_WRITE_WAIT	      0x43  /* NORMAL WRITE	    */
#define VC_WRT_XREAD_WAIT     0x46  /* WRITE & TRANSP. READ */
#define VC_WRT_READ_WAIT      0x47  /* WRITE & NORMAL READ  */
#define VC_SPEC_READ_WAIT     0x4A  /* SPECIAL READ	    */
#define VC_SPEC_WRITE_WAIT    0x4B  /* SPECIAL WRITE	    */
#define VC_POLL_XBUF_WAIT     0x4C  /* POLL EXTRA-BUFFER    */
#define VC_CHECK_ABO_WAIT     0x4D  /* CHECK FOR ABORT-FLAG */

/*
----------------------------------------------------------------------------
Bits for sub_control field with special read and special write.
----------------------------------------------------------------------------
*/
#define VC_SUB_TRANSPARENT	0x0001	/* Transparent read or write	*/
#define VC_SUB_STATUS		0x0002	/* Enable status check		*/
#define VC_SUB_NO_ECHO		0x0004	/* Disable echo 		*/
#define VC_SUB_RESET_BUFFER	0x0008	/* Flush typeahead buffer	*/
#define VC_SUB_POLL_BUFFER	0x0010	/* Read from typeahead buffer	*/

/*
----------------------------------------------------------------------------
Additional macros
----------------------------------------------------------------------------
*/

#define MAX_VC_FUNC	      0x0d  /* MAX. FUNCTION CODE   */
#define VC_IMMED_BIT	      0x80  /* EMERGENCY-OPTION     */
#define VC_WAIT_BIT	      0x40  /* WAIT-OPTION	    */

/*
----------------------------------------------------------------------------
Statusblock structure definition
----------------------------------------------------------------------------
*/

struct status_struct
{
  byte	 prim_status ;
  char	 terminator  ;
  word16 byte_count  ;
  word32 reserved    ;
} ;

/*
----------------------------------------------------------------------------
Parameterblock structure definitions
----------------------------------------------------------------------------
*/

/* for VC_READ and VC_POLL_XBUF */

struct vc_read_parm
{
  char	       *res_1  ;	       /* reserved		 */
  unsigned int res_2   ;	       /* reserved		 */
  char	       *ip_buf ;	       /* Input buffer address	 */
  unsigned int ip_len  ;	       /* Input buffer length	 */
  unsigned int res_5   ;	       /* reserved		 */
} ;

/* for VC_WRITE */

struct vc_write_parm
{
  char	       *op_buf ;	       /* Output buffer address  */
  unsigned int op_len  ;	       /* Output buffer length	 */
  char	       *res_3  ;	       /* reserved		 */
  unsigned int res_4   ;	       /* reserved		 */
  unsigned int res_5   ;	       /* reserved		 */
} ;

/* for VC_WRT_XREAD and VC_WRT_READ */

struct vc_write_read_parm
{
  char	       *op_buf ;	       /* Output buffer address  */
  unsigned int op_len  ;	       /* Output buffer length	 */
  char	       *ip_buf ;	       /* Input buffer address	 */
  unsigned int ip_len  ;	       /* Input buffer length	 */
  unsigned int res_5   ;	       /* reserved		 */
} ;

/* for VC_SPEC_READ and VC_SPEC_WRITE */

struct vc_spec_rw_parm
{
  word16       res_1	   ;	      /* reserved */
  word16       sub_control ;	      /* Function sub control */
  char	       *io_buf	   ;	      /* Address of Input/Output buffer */
  unsigned int io_len	   ;	      /* Length of Input/Output buffer */
} ;

/* for VC_CHECK_ABO */

struct vc_check_abo_parm
{
  char	       *abo_buffer	      ;   /* Address of user buffer 	  */
  unsigned int res_2		      ;   /* reserved			  */
  void	  (_FAR *abort_function)(void);   /* pointer to user's abort function */
  unsigned int res_4		      ;   /* reserved			  */
  unsigned int res_5		      ;   /* reserved			  */
} ;

/*
-------------------------------------------------------------------------------
Status values for the primary status byte
-------------------------------------------------------------------------------
*/

#define VC_RIO_SUCCESS	    2
#define VC_RIO_IN_PROGRESS  1
#define VC_RIO_PENDING	    0
#define VC_RIO_PARAMETER   -1
#define VC_RIO_NO_BUFFER   -9
#define VC_RIO_MEMORY	   -11
#define VC_RIO_INTERNAL    -12

    
#endif /* _VC_RIO_H_ */

