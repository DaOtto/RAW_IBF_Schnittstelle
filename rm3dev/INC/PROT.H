/*--FILE HEADER-(set tabulator to 4)-------------------------------------------
;
;   filename    : PROT.H  
;   version     : 0004
;   contents    : Support macro for conditional translation 
;   author      : W.S.
;   date        : Dec 04, 1992
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Determine between code for RMOS2 and RMOS3.
;                 If 'PROT' is 'FALSE'                          ==> RMOS2
;                 If 'PROT' is 'TRUE' and 'RM3' is 'TRUE'       ==> RMOS3
;
;   RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec  4, 1992  W.S.  0003  New Header added
;   Nov 29, 1994  P.F.  0004  Allow multiple include of prot.h
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _PROT_H_
#define _PROT_H_

#ifndef PROT
#define PROT 1      /* Now, protected mode is selected */
#endif
#ifndef RM3
#define RM3  1      /* Now, RMOS3     mode is selected */
#endif

#endif /* _PROT_H_ */
