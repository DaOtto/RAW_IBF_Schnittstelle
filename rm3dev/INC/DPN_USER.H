/*--FILE HEADER-(no tabs used)-----------------------------------------------
;
;   filename    : DPN_USER.H
;   version     : 0002
;   contents    : Header file DP interface
;   author      : G.H.
;   date        : Jun  5, 1996
;
;---FUNCTION AND RMOS ENVIRONMENT--------------------------------------------
;
;   function    : The header file contains the declarations needed by an
;                 user of the DP interface.
;                 The DP interface supports the access to DP instances, that
;                 means access to  
;                 * local DP master(s) (class 1) like CP5412(A2),
;                 * local DP slave(s) or
;                 * a combination(s) of both.
;                  
;
;   RMOS3
;
;---END OF FILE HEADER-------------------------------------------------------
;
;---MODIFICATION HEADER------------------------------------------------------
;
;   Apr  9, 1996:        0000  Original issue
;   Apr 22, 1996:        0001  dpn_read_slv_par() gets input/output length too
;
;---END OF FILE HEADER-----------------------------------------------------*/

#ifndef __DPN_USER_H__
  #define __DPN_USER_H__

  /***** RMOS header *******************************************************/

  #ifndef _RMCOMP_H_
    #include <rmcomp.h>
  #endif
  #ifndef _TYPEDEFS_H_
    #include <typedefs.h>
  #endif

  /***** alignment and calling convention **********************************/

  #if ((defined(_ARCHITECTURE_)) || (defined(CADUL)))
                      /* Intel C compiler iC386 or CAD-UL C compiler CC386 */
    #pragma fixedparams("dpn_init", "dpn_read_cfg", "dpn_slv_diag")
    #pragma fixedparams("dpn_read_sys_info", "dpn_out_slv", "dpn_in_slv")
    #pragma fixedparams("dpn_read_slv", "dpn_reset", "dpn_signal")
    #pragma fixedparams("dpn_wd", "dpn_read_bus_par", "dpn_load_bus_par")
    #pragma fixedparams("dpn_read_slv_par", "dpn_set_slv_state")
    #pragma fixedparams("dpn_out_slv_m", "dpn_in_slv_m")
    #pragma fixedparams("dpn_set_mode", "dpn_get_mode", "dpn_global_ctrl")
    #pragma fixedparams("dpn_slv_out_diag", "dpn_slv_wd_state")

    #pragma align(REFERENCE=1)
    #pragma align(dpn_interface=1)
    #pragma align(dpn_interface_s=1)
    #pragma align(dpn_interface_m=1)
    #pragma align(dpn_buspar=1)
  #endif

  #if defined _MSC_VER                             /* Microsoft C compiler */
    #pragma pack(1)
  #endif

  #ifdef __BORLANDC__                                /* Borland C compiler */
    #pragma option -a-
  #endif

  /***** structures ********************************************************/

  #define MAX_DATA_LEN      255  
  #define DPN_MULTIPLE_SIZE  32         /* Number of structure elements in 
                                           array dpn_interface_m(ultiple)  */
  #define DPN_SINGLE_SIZE    32         /* Number of data bytes
                                           in the structure
                                           dpn_interface_s(ingle)          */
  #define DPN_IF_S_UNUSED   ((BYTE)-1)  /* Sign for a structure
                                           dpn_interface_s which isn't
                                           used                            */

  struct REFERENCE {
    BYTE board_select; 
    BYTE access;
  };

  struct dpn_interface {
    struct REFERENCE reference;
    BYTE             stat_nr;
    BYTE             length;
    WORD16           error_code;
    BYTE             slv_state;
    BYTE             sys_state;
    BYTE             sys_event;
    BYTE             user_data[MAX_DATA_LEN];
  };

  struct dpn_interface_s {                       /* dpn_interface_s(ingle) */
    struct REFERENCE reference;
    BYTE             stat_nr;
    BYTE             length;
    WORD16           error_code;
    BYTE             slv_state;
    BYTE             sys_state;
    BYTE             sys_event;
    BYTE             user_data[DPN_SINGLE_SIZE];
  };

  struct dpn_interface_m {
    struct dpn_interface_s dpn_if_single[DPN_MULTIPLE_SIZE];
  };

  /***** defines for dpn_init() ********************************************/

  /*************************************************************************
   *  REMARK: The defines for environment, role and access rights secure   *
   *          the formal compatibility to CP5412(A2).                      *
   *          All combinations of environment and role are valid but it    *
   *          always works like DPN_SYS_NOT_CENTRAL|DPN_ROLE_NOT_CENTRAL.  *
   *          All access rights are valid but it always works like         *
   *          DPN_SLV_WRITE_READ.                                          *
   *************************************************************************/

  #define DPN_SYS_CENTRAL               ((BYTE)0x20)       /* environments */
  #define DPN_SYS_NOT_CENTRAL           ((BYTE)0x10)

  #define DPN_ROLE_CENTRAL              ((BYTE)0x80)              /* roles */
  #define DPN_ROLE_NOT_CENTRAL          ((BYTE)0x40)

  #define DPN_SLV_NO_ACCESS             ((BYTE)0)         /* access rights */
  #define DPN_SLV_READ                  ((BYTE)1)
  #define DPN_SLV_WRITE_READ            ((BYTE)2)

  /***** defines for dpn_read() and load_bus_par() *************************/

  struct dpn_buspar {
    WORD16 Reserved;
    BYTE   FdlAdd;
    BYTE   baudrate;
    WORD16 Tsl;
    WORD16 MinTsdr;
    WORD16 MaxTsdr;
    BYTE   Tqui;
    BYTE   Tset;
    WORD32 Ttr;
    BYTE   G;
    BYTE   Hsa;
    BYTE   MaxRetryLimit;
    BYTE   BpFlag; 
    WORD16 MinSlaveInterval;
    WORD16 PollTimeout;
    WORD16 DataControlTime;   
  };

  /***** defines for dpn_read_slv_par() ************************************/

  #define DPN_SLV_PARA_TYP              ((BYTE)0)
  #define DPN_SLV_PARA_PRM_DATA         ((BYTE)1)
  #define DPN_SLV_PARA_CFG_DATA         ((BYTE)2)
  #define DPN_SLV_PARA_ADD_TAB          ((BYTE)3)
  #define DPN_SLV_PARA_USER_DATA        ((BYTE)4)
  #define DPN_SLV_PARA_INPUT_LEN        ((BYTE)5)           /* see .length */
  #define DPN_SLV_PARA_OUTPUT_LEN       ((BYTE)6)           /* see .length */

  /***** defines for dpn_set_slave_state() *********************************/

  #define DPN_SLV_ACTIVATE              ((BYTE)0x80)
  #define DPN_SLV_DEACTIVATE            ((BYTE)0)

  /***** defines for dpn_read_cfg() ****************************************/

  #define DPN_CFG_NO_SLV                ((BYTE)-1)
  #define DPN_CFG_NORM                  ((BYTE)0)
  #define DPN_CFG_ET200_U               ((BYTE)1)
  #define DPN_CFG_ET200K_B              ((BYTE)2)
  #define DPN_CFG_ET200_SPM             ((BYTE)3)
  #define DPN_CFG_MSTR                  ((BYTE)4)       /* local DP master */
  #define DPN_CFG_LSLV                  ((BYTE)5)        /* local DP slave */
  #define DPN_CFG_MSTR_LSLV             ((BYTE)6) /* local DP master+slave */

  /***** defines for structure element .sys_state **************************/

  #define  DPN_SYS_OFFLINE              ((BYTE)0)
  #define  DPN_SYS_STOP                 ((BYTE)0x40)
  #define  DPN_SYS_CLEAR                ((BYTE)0x80)
  #define  DPN_SYS_OPERATE              ((BYTE)0xC0) 

  /***** defines for structure element .slv_state **************************/

  #define  DPN_SLV_STAT_OFFLINE         ((BYTE)0)
  #define  DPN_SLV_STAT_NOT_ACTIVE      ((BYTE)1)
  #define  DPN_SLV_STAT_READY           ((BYTE)2)
  #define  DPN_SLV_STAT_READY_DIAG      ((BYTE)3)
  #define  DPN_SLV_STAT_NOT_READY       ((BYTE)4)
  #define  DPN_SLV_STAT_NOT_READY_DIAG  ((BYTE)5)

  /***** defines for structure element .sys_event **************************/

  #define MST_CLS_TWO_ACCESS            ((BYTE)0x80)      /* not supported */
  #define AUTOCLEAR                     ((BYTE)0x40)      /* not supported */
  #define WATCHDOG                      ((BYTE)0x20)      /* not supported */

  /***** defines for dpn_global_ctrl() *************************************/

  #define DPN_CLEAR                     ((BYTE)0x02) 
  #define DPN_UNFREEZE                  ((BYTE)0x04)
  #define DPN_FREEZE                    ((BYTE)0x08)
  #define DPN_UNSYNC                    ((BYTE)0x10)
  #define DPN_SYNC                      ((BYTE)0x20)

  #define DPN_GROUP_ADR                 ((BYTE)127)            /* .stat_nr */
  #define DPN_SELECT_ALL                ((BYTE)0)         /* .user_data[0] */

  /***** defines for dpn_slv_wd_state() ************************************/

  #define DPN_LSLV_WD_NOT_ACTIVE        ((BYTE)0)         /* .user_data[0] */
  #define DPN_LSLV_WD_ACTIVE            ((BYTE)1) 
  #define DPN_LSLV_WD_TIMEOUT           ((BYTE)2) 

  /***** defines for dpn_signal() ******************************************/

  #define DPN_NO_SIGNAL                 ((BYTE)-1)  /* no signal requested */
  #define DPN_SIGNAL                    ((BYTE)0)      /* signal requested */

  /***** signaled events ***************************************************/
  
  #define DPN_SIGNAL_SYS_STATE  ((BYTE)(1<<0))     /* master state changed */
  #define DPN_SIGNAL_RSLV_STATE ((BYTE)(1<<1))    /* rem slv state changed */
  #define DPN_SIGNAL_LSLV_STATE ((BYTE)(1<<2))    /* loc slv state changed */
  #define DPN_SIGNAL_LSLV_WD    ((BYTE)(1<<3)) /* loc slv watchdog changed */
  #define DPN_SIGNAL_LSLV_OUT   ((BYTE)(1<<4)) /* support context depended */

  /***** prototypes DP master class 1 / local DP slave *********************/

  WORD16 _FIXED _FAR dpn_init          (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_read_cfg      (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_slv_diag      (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_read_sys_info (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_out_slv       (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_in_slv        (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_read_slv      (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_reset         (struct dpn_interface _FAR *);

  WORD16 _FIXED _FAR dpn_signal        (struct dpn_interface _FAR *);

  /***** prototypes DP master class 1 only *********************************/

  WORD16 _FIXED _FAR dpn_wd            (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_read_bus_par  (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_load_bus_par  (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_read_slv_par  (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_set_slv_state (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_out_slv_m     (struct dpn_interface_m _FAR *);
  WORD16 _FIXED _FAR dpn_in_slv_m      (struct dpn_interface_m _FAR *);
  WORD16 _FIXED _FAR dpn_set_mode      (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_get_mode      (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_global_ctrl   (struct dpn_interface _FAR *);

  /***** prototypes local DP slave only ************************************/

  WORD16 _FIXED _FAR dpn_slv_out_diag  (struct dpn_interface _FAR *);
  WORD16 _FIXED _FAR dpn_slv_wd_state  (struct dpn_interface _FAR *);

  /***** defines for structure element .error_code / return codes **********/

  /*************************************************************************
   *  REMARK: Some error codes are impossible. They secure the formal      *
   *          compatibility to CP5412(A2).                                 *
   *************************************************************************/

  #define  DPN_NO_ERROR                 ((WORD16)0)
  #define  DPN_ACCESS_ERROR             ((WORD16)0x80)  /* dpn_signal only */
  #define  DPN_APPL_LIMIT_ERROR         ((WORD16)0x81)
  #define  DPN_CENTRAL_ERROR            ((WORD16)0x82)       /* impossible */
  #define  DPN_CLOSE_ERROR              ((WORD16)0x83)       /* impossible */
  #define  DPN_LENGTH_ERROR             ((WORD16)0x84)
  #define  DPN_MEM_BOARD_ERROR          ((WORD16)0x85)       /* impossible */
  #define  DPN_MEM_HOST_ERROR           ((WORD16)0x86)       /* impossible */
  #define  DPN_MODE_ERROR               ((WORD16)0x87)
  #define  DPN_NO_DBASE_ERROR           ((WORD16)0x88)
  #define  DPN_OPEN_ERROR               ((WORD16)0x89)       /* impossible */
  #define  DPN_RECEIVE_ERROR            ((WORD16)0x8a)       /* impossible */
  #define  DPN_REFERENCE_ERROR          ((WORD16)0x8b)
  #define  DPN_REFERENCE_DIFF_ERROR     ((WORD16)0x8c)       /* impossible */
  #define  DPN_SEND_ERROR               ((WORD16)0x8d)       /* impossible */
  #define  DPN_SLV_STATE_ERROR          ((WORD16)0x8e)
  #define  DPN_STAT_NR_ERROR            ((WORD16)0x8f)
  #define  DPN_USER_DATA_ERROR          ((WORD16)0x90)
  #define  DPN_WRONG_BOARD_ERROR        ((WORD16)0x91)
  #define  DPN_SYS_STATE_ERROR          ((WORD16)0x92)
  #define  DPN_GLB_CTRL_ERROR           ((WORD16)0x93)
  #define  DPN_BOARD_ERROR              ((WORD16)0x94)
  #define  DPN_WD_EXPIRED_ERROR         ((WORD16)0x95)       /* impossible */

  /*************************************************************************/

  #if defined _MSC_VER
    #pragma pack()         /* reset alignment to commandline specification */
  #endif

  #ifdef __BORLANDC__
    #pragma option -a.     /* reset alignment to commandline specification */
  #endif

#endif
