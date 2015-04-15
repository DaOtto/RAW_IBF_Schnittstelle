/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : CLI.H
;   version     : 0024
;   contents    : Public include file for the CLI manager.
;   author      : W.K.
;   date        : Jul 31, 1992
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Public include file for the CLI manager.
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Jul 31, 1992  0021 P.J.  Original issue after beta test
;   Jul 14, 1994  0022 H.O.  includes MISC86.H instead of I86.H
;   Sep 15, 1994  0023 W.K.  rc_init_cli added
;   Jan 18, 1995  0024 W.K.  fixparams added for extend_..,_cancel
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _CLI_H_
#define _CLI_H_

#include <rmcomp.h>
#include <misc86.h>
#include <task.h>

#ifndef _NOVERS
const static char idstr_cli_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"  /* Incode identification. */
        "\1"    "CLI.H"                 "\1"
        "\2"    "0024"                  "\2"
        "\3"    "W.K."                  "\3"
} ;
#endif

/*
-------------------------------------------------------------------------------
Structure and type definitions
-------------------------------------------------------------------------------
*/

typedef int ( _FAR *MAIN )( int argc, char *argv[] ) ;  /* task entry */

/* Inline Command Data */

#pragma noalign (ICD_struct)
typedef struct ICD_struct
{
  char   *verb ;            /* Command name */
  MAIN   main ;             /* Procedure entry point */
} ICD ;

/* Permanent task data */

#pragma noalign (PTD_struct)
typedef struct PTD_struct
{
  char          *verb ;         /* Command name */
  MAIN          main ;          /* Procedure entry point */
  unsigned      stack_size ;    /* Expand up, initial ESP = stack_size */
} PTD ;

/* Notes about PTD
   1. Permanent tasks do not have a separate data segment.
      CLI will initially set DS=SS, but if the entry point is declared
      as a _FAR procedure, DS will be reloaded to the data segment which
      iC386 gives it. If it's in the CLI subsystem, this will be CLI_DATA.
*/

/* Device name data */

#pragma noalign (DND_struct)
typedef struct DND_struct
{
  char          *name ;         /* Device name */
  char          device ;        /* Device number */
  char          unit ;          /* Unit numner */
} DND ;

/*
-------------------------------------------------------------------------------
Macros
-------------------------------------------------------------------------------
*/

#define MAX_CHAR    256         /* Buffer size for command         */
#define MAX_PATH    256         /* Buffer size for full filename   */

/* CLI error codes */

#define E_CLI_IDENT              0x8200
#define E_HSFS_IDENT             0x8300
#define E_ERRNO_IDENT            0x8700

/* Use the following macro to convert an hsfs error to the cli format */
#define HSFS_STATUS(x)           (E_HSFS_IDENT+(unsigned char)(x))
#define ERRNO_STATUS(x)          (E_ERRNO_IDENT+(unsigned char)(x))

#define E_CLI_OK                 0
#define E_CLI_NOT_RESIDENT       E_CLI_IDENT + 0x01
#define E_CLI_FILE_FORMAT        E_CLI_IDENT + 0x02
#define E_CLI_DYNAMIC_MEM        E_CLI_IDENT + 0x03
#define E_CLI_INTERNAL_ERROR     E_CLI_IDENT + 0x04
#define E_CLI_LTT_FULL           E_CLI_IDENT + 0x05
#define E_CLI_CJT_FULL           E_CLI_IDENT + 0x06
#define E_CLI_CREATE_ERROR       E_CLI_IDENT + 0x07
#define E_CLI_START_ERROR        E_CLI_IDENT + 0x08
#define E_CLI_DELTSK_ERROR       E_CLI_IDENT + 0x09
#define E_CLI_LT_ACTIVE          E_CLI_IDENT + 0x0A
#define E_CLI_JOB_ACTIVE         E_CLI_IDENT + 0x0B
#define E_CLI_FILE_NOT_FOUND     E_CLI_IDENT + 0x0C
#define E_CLI_NOT_A_CLI_JOB      E_CLI_IDENT + 0x0D
#define E_CLI_NOT_A_CRUN_JOB     E_CLI_IDENT + 0x0E
#define E_CLI_NOT_INLINE         E_CLI_IDENT + 0x0F
#define E_CLI_SYNTAX_ERROR       E_CLI_IDENT + 0x10
#define E_CLI_ENVIRONMENT_FULL   E_CLI_IDENT + 0x11
#define E_CLI_NO_COMMAND         E_CLI_IDENT + 0x12
#define E_CLI_EOF                E_CLI_IDENT + 0x13
#define E_CLI_EXIT_STATUS        E_CLI_IDENT + 0x14
#define E_CLI_CATALOG_FULL       E_CLI_IDENT + 0x15
#define E_CLI_CREATESEMA_ERROR   E_CLI_IDENT + 0x16
#define E_CLI_REDIR_STDIN_FAIL   E_CLI_IDENT + 0x17
#define E_CLI_REDIR_STDOUT_FAIL  E_CLI_IDENT + 0x18
#define E_CLI_REDIR_STDERR_FAIL  E_CLI_IDENT + 0x19
#define E_CLI_UNKNOWN_SWITCH     E_CLI_IDENT + 0x1A
#define E_CLI_TOO_MANY_PARAMS    E_CLI_IDENT + 0x1B
#define E_CLI_INVALID_FILENAME   E_CLI_IDENT + 0x1C
#define E_CLI_INVALID_LT_INDEX   E_CLI_IDENT + 0x1D
#define E_CLI_INVALID_JOB_INDEX  E_CLI_IDENT + 0x1E
#define E_CLI_TOO_FEW_PARAMS     E_CLI_IDENT + 0x1F
#define E_CLI_FILE_READ_ERROR    E_CLI_IDENT + 0x20
#define E_CLI_FILE_WRITE_ERROR   E_CLI_IDENT + 0x21
#define E_CLI_COPY_TO_SELF       E_CLI_IDENT + 0x22
#define E_CLI_UNEXPECTED_EOF     E_CLI_IDENT + 0x23
#define E_CLI_PERMANENT_TASK     E_CLI_IDENT + 0x24
#define E_CLI_NO_PROMPT          E_CLI_IDENT + 0x25
#define E_CLI_JOB_ABORTED        E_CLI_IDENT + 0x26
#define E_CLI_NOT_A_DEVICE       E_CLI_IDENT + 0x27
#define E_CLI_MKDIR_FAIL         E_CLI_IDENT + 0x28
#define E_CLI_BATCH_FILE         E_CLI_IDENT + 0x29      /* not an error */
#define E_CLI_NOT_MOUNTED        E_CLI_IDENT + 0x2A
#define E_CLI_INVALID_WILDCARD   E_CLI_IDENT + 0x2B
#define E_CLI_NOT_A_DIRECTORY    E_CLI_IDENT + 0x2C
#define E_CLI_DIR_OPEN_FAIL      E_CLI_IDENT + 0x2D
#define E_CLI_FILE_OPEN_FAIL     E_CLI_IDENT + 0x2E
#define E_CLI_FILE_CLOSE_FAIL    E_CLI_IDENT + 0x2F
#define E_CLI_SVC_ERROR          E_CLI_IDENT + 0x30
#define E_CLI_DEV_READ_ERROR     E_CLI_IDENT + 0x31
#define E_CLI_DEV_WRITE_ERROR    E_CLI_IDENT + 0x32
#define E_CLI_IS_A_DIRECTORY     E_CLI_IDENT + 0x33
#define E_CLI_INLINE             E_CLI_IDENT + 0x34
#define E_CLI_COMPLETED          E_CLI_IDENT + 0x35
#define E_CLI_UNINITIALISED      E_CLI_IDENT + 0x36
#define E_CLI_OUT_OF_RANGE       E_CLI_IDENT + 0x37
#define E_CLI_NO_SPACE_FOR_NPX   E_CLI_IDENT + 0x38
#define E_CLI_NO_PARENT_JOB      E_CLI_IDENT + 0x39
#define E_CLI_INVALID_VOL_NAME   E_CLI_IDENT + 0x3A
#define E_CLI_MOUNTED            E_CLI_IDENT + 0x3B
#define E_CLI_INVALID_DATE_TIME  E_CLI_IDENT + 0x3C
#define E_CLI_READ_ONLY          E_CLI_IDENT + 0x3D
#define E_CLI_NO_CWD             E_CLI_IDENT + 0x3E
#define E_CLI_XINITT_FAIL        E_CLI_IDENT + 0x3F
#define E_CLI_SMRS_LOW           E_CLI_IDENT + 0x40
#define E_CLI_STACK_LOW          E_CLI_IDENT + 0x41
#define E_CLI_VOLUME_PROTECTED   E_CLI_IDENT + 0x42
#define CLI_MAX_ERROR            E_CLI_VOLUME_PROTECTED

/*
-------------------------------------------------------------------------------
Function definitions
-------------------------------------------------------------------------------
*/

/* public CLI functions */

#pragma varparams ("RcInitCli")
int      _FAR RcInitCli               ( void ) ;

#pragma fixedparams ("x_cli_init_manager")
int      _FAR x_cli_init_manager        ( void ) ;

/* public CLI functions with interface for loadable programs */

#pragma fixedparams ("x_cli_cmdexec")
#pragma fixedparams ("x_cli_cmdline")
#pragma fixedparams ("x_cli_session")
#pragma fixedparams ("x_cli_cancel")
#pragma fixedparams ("x_cli_start")
#pragma fixedparams ("x_cli_job_number")
#pragma fixedparams ("x_cli_job_command")
#pragma fixedparams ("x_cli_job_command_tail")
#pragma fixedparams ("x_cli_inhibit_abort")
#pragma fixedparams ("x_cli_test_abort")
#pragma fixedparams ("x_cli_get_device")
#pragma fixedparams ("x_cli_truename")
#pragma fixedparams ("x_cli_prompt")
#pragma fixedparams ("x_cli_load_ds")
#pragma fixedparams ("x_cli_errorlevel")
#pragma fixedparams ("x_cli_extended_session")
#pragma fixedparams ("x_cli_extended_start")

int      _FAR _FIXED x_cli_cmdexec     ( char        *cmd_line,
                                         char        *environment,
                                         STDSTRUCT   *cli_stream,
                                         int         *exit_status ) ;

int      _FAR _FIXED x_cli_cmdline     ( char        *prompt,
                                         unsigned    buf_len,
                                         char        *input_line,
                                         STDSTRUCT   *redir_data ) ;

int      _FAR _FIXED x_cli_session     ( char        *cmd_line,
                                         char        *environment,
                                         int         iConsDev,
                                         int         iConsUnit,
                                         char        *pszTempPath,
                                         unsigned    uPri,
                                         unsigned    uPriVal ) ;

int      _FAR _FIXED x_cli_extended_session
                                       ( char        *cmd_line,
                                         char        *environment,
                                         int         iConsDev,
                                         int         iConsUnit,
                                         char        *pszTempPath,
                                         unsigned    uPri,
                                         unsigned    uPriVal,
                                         int         *piJob,
                                         unsigned    uFlagId,
                                         unsigned    uStartupMask,
                                         unsigned    uJobEndMask ) ;

int      _FAR _FIXED x_cli_start       ( char        *pszCmdLine,
                                         char        *environment,
                                         STDSTRUCT   *cli_stream,
                                         int         iNPX,
                                         unsigned    uPri,
                                         unsigned    uPriVal ) ;

int      _FAR _FIXED x_cli_extended_start
                                       ( char        *pszCmdLine,
                                         char        *environment,
                                         STDSTRUCT   *cli_stream,
                                         int         iNPX,
                                         unsigned    uPri,
                                         unsigned    uPriVal,
                                         int         *piJob,
                                         unsigned    uFlagId,
                                         unsigned    uStartupMask,
                                         unsigned    uJobEndMask ) ;

int      _FAR _FIXED x_cli_cancel       ( int         iJob ) ;

int      _FAR _FIXED x_cli_job_number   ( int         *piJob ) ;
int      _FAR _FIXED x_cli_job_command  ( char        **ppszCmdLine ) ;
int      _FAR _FIXED x_cli_job_command_tail ( char        **ppszCmdLine ) ;
int      _FAR _FIXED x_cli_inhibit_abort    ( int         iRequest ) ;
int      _FAR _FIXED x_cli_test_abort       ( void ) ;

int      _FAR _FIXED x_cli_get_device  ( char        *pszDeviceName,
                                         int         *piDevice,
                                         int         *piUnit ) ;

int      _FAR _FIXED x_cli_truename    ( char        *pszFileSpec,
                                         char        *pszTrueName ) ;

int      _FAR _FIXED x_cli_prompt      ( char        *pszBuffer,
                                         unsigned    uBufferLen ) ;

void     _FAR _FIXED x_cli_load_ds     ( void ) ;

int      _FAR _FIXED x_cli_errorlevel  ( int         *piErrorlevel ) ;

/* inline commands */
#pragma fixedparams ("x_cli_inline_start")
#pragma fixedparams ("x_cli_inline_session")
#pragma fixedparams ("x_cli_inline_systat")
#pragma fixedparams ("x_cli_inline_set")
#pragma fixedparams ("x_cli_inline_path")
#pragma fixedparams ("x_cli_inline_prompt")
#pragma fixedparams ("x_cli_inline_cd")
#pragma fixedparams ("x_cli_inline_echo")
#pragma fixedparams ("x_cli_inline_exit")
#pragma fixedparams ("x_cli_inline_mount")
#pragma fixedparams ("x_cli_inline_truename")
#pragma fixedparams ("x_cli_inline_dismount")
#pragma fixedparams ("x_cli_inline_batch")
#pragma fixedparams ("x_cli_inline_cancel")
#pragma fixedparams ("x_cli_inline_cpri")
#pragma fixedparams ("x_cli_inline_npx")
#pragma fixedparams ("x_cli_inline_ver")
#pragma fixedparams ("x_cli_inline_rem")
int      _FAR _FIXED x_cli_inline_start        ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_session      ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_systat       ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_set          ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_path         ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_prompt       ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_cd           ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_echo         ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_exit         ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_mount        ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_truename     ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_dismount     ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_batch        ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_cancel       ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_cpri         ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_npx          ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_ver          ( int argc, char *argv[] ) ;
int      _FAR _FIXED x_cli_inline_rem          ( int argc, char *argv[] ) ;

/* permanent tasks */
#pragma fixedparams ("x_cli_permanent_shell")
int      _FAR _FIXED x_cli_permanent_shell     ( int argc, char *argv[] ) ;

#pragma fixedparams ("x_clix_permanent_shell")
int      _FAR _FIXED x_clix_permanent_shell     ( int argc, char *argv[] ) ;

/*
-------------------------------------------------------------------------------
CLI data
-------------------------------------------------------------------------------
*/

extern const char x_cli_pszCliVersion [] ;      /* in cli_vers.c */

/* in swccli.c */

extern char _FAR * const _FAR x_cli_batch_directory ;
extern char _FAR * const _FAR x_cli_temp_volume ;
extern const unsigned _FAR x_cli_pri ;
extern const ICD x_cli_ICT [] ;
extern const int x_cli_iInlineMax ;
extern const PTD x_cli_PTT [] ;
extern const int x_cli_iPermanentMax ;
extern const DND x_cli_DNT [] ;
extern const int x_cli_iDeviceNameMax ;

#endif  /* ifndef _CLI_H_ */
