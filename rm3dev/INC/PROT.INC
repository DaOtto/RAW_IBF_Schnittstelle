$SAVE NOLIST
;---FILE HEADER----------------------------------------------------------------
;   filename    : PROT.INC
;   version     : 0002
;   contents    : Support include for conditional translation
;   author      : K.P.H.
;   date        : Feb 01, 1995
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : Some equates for help to use the same file in 
;                 protected mode and real mode
;                 
;
;   RMOS2   package
;   RMOS3   package
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec  09, 1993  W.S.  0001  Original issue
;   Feb  01, 1995  K.P.H.0002  Correction for RMOS2/3
;
;---END OF MODIFICATION HEADER-------------------------------------------------


%SET (FALSE,0)
%SET (TRUE,NOT %FALSE)

%IF(%RM3)THEN(
%DEFINE (MODEL) (NEAR)	;MODEL FOR FUNCTIONS
%DEFINE (DP) (DP)	;DEFINE	POINTER
%DEFINE (DO) (DD)	;	OFFSET
%DEFINE (DW) (DD)	;	PROCESSOR NATIVE WORD
%DEFINE (PWORD) (PWORD)	;	POINTER LABEL
%DEFINE (OWORD) (DWORD)	;	OFFSET LABEL
%DEFINE (WORD)  (DWORD)	;	PROCESSOR NATIVE WORD LABEL

_MOVZX_		EQU	MOVZX
_JECXZ_		EQU	JECXZ

%*DEFINE (NUC_PROC (NAME)) (%'
%NAME	PROC	NEAR
)
)ELSE(
%DEFINE (MODEL) (FAR)	;MODEL FOR FUNCTIONS
%DEFINE (DP) (DD)	;DEFINE	POINTER
%DEFINE (DO) (DW)	;	OFFSET
%DEFINE (DW) (DW)	;	PROCESSOR NATIVE WORD
%DEFINE (PWORD) (DWORD)	;	POINTER LABEL
%DEFINE (OWORD) (WORD)	;	OFFSET LABEL
%DEFINE (WORD)  (WORD)	;	PROCESSOR NATIVE WORD LABEL

EAX		EQU	AX
EBX		EQU	BX
ECX		EQU	CX
EDX		EQU	DX
EDI		EQU	DI
ESI		EQU	SI
EBP		EQU	BP
ESP		EQU	SP
PUSHFD		EQU	PUSHF
POPFD		EQU	POPF
PUSHAD		EQU	PUSHA
POPAD		EQU	POPA
IRETD		EQU	IRET

_MOVZX_		EQU	MOV
_JECXZ_		EQU	JCXZ


%*DEFINE (NUC_PROC (NAME)) (%'
%NAME	PROC	FAR
)
)FI
$RESTORE
