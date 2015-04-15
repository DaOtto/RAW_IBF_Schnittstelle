/*--FILE HEADER-(set tabs 4)---------------------------------------------------
;
;   filename    : COM.H
;   version     : 0001
;   contents    : Definitions for COM-DRIVER
;   author      : P.F.
;   date        : Oct 27, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Include-file for official Defines for COM-DRIVER  
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER-------------------------------------------------------*/


/*  ** FUNCTIONS IN THE USERS CALL'S (RIO-SVC) **/


#define C64_RESERVE            0x00  /* RESERVE UNIT         */
#define C64_RELEASE            0x01  /* RELEASE UNIT         */
#define C64_READ               0x02  /* NORMAL READ          */
#define C64_WRITE              0x03  /* NORMAL WRITE         */
#define C64_CREATE_NEW         0x04  /* CREATE NEW UNIT      */


/*  ** FUNCTIONS IN THE USERS CALL'S WITH WAIT OPTION (RIO-SVC) **/


#define C64_RESERVE_WAIT       0x40  /* RESERVE UNIT         */
#define C64_RELEASE_WAIT       0x41  /* RELEASE UNIT         */
#define C64_READ_WAIT          0x42  /* NORMAL READ          */
#define C64_WRITE_WAIT         0x43  /* NORMAL WRITE         */
#define C64_CREATE_NEW_WAIT    0x44  /* CREATE NEW UNIT      */

