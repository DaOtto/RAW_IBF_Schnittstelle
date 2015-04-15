/*--FILE HEADER----------------------------------------------------------------
;
;   filename    : CTYPE.H
;   version     : 0012
;   contents    : Header file for RMOS-CRUN
;   author      : P.F.
;   date        : Dec 19, 1994
;
;---FUNCTION AND RMOS ENVIRONMENT----------------------------------------------
;
;   function    : This header file contains macros that interrogate
;                 single ascii characters for certain attributes
;                 (e.g. numeric, alphabetic). The attributes are
;                 recorded in the character attribute table which has
;                 one entry for each ascii value (0x00 - 0x7F).  Each
;                 entry in this table has one or more bits set to
;                 indicate the defined attributes for that ascii
;                 character.  For the most part, the macros here test
;                 the appropriate bits and return 0 for FALSE and
;                 non-zero for TRUE.
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER---------------------------------------------------------
;
;---MODIFICATION HEADER--------------------------------------------------------
;
;   Dec 19, 1994  P.F.  0012  Modification for RMOS2/3 V3.1
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/

#ifndef _CTYPE_H_
#define _CTYPE_H_

#ifndef _RMCOMP_H_
#include <rmcomp.h>
#endif  /* _RMCOMP_H_ */

#if defined(_ARCHITECTURE_)  ||  defined(CADUL)
           /* ======= Intel C Compiler iC86/386 is used ======= */
#pragma fixedparams("tolower", "toupper")
#pragma fixedparams("__chattr")
#endif  /* _ARCHITECTURE_ || CADUL */


#define _ALPH   0x0001  /* alphabetic */
#define _DEC    0x0002  /* numeric decimal */
#define _HEX    0x0004  /* numeric hexadecimal */

#define _CTL    0x0008  /* control character */
#define _SPAC   0x0010  /* white space */
#define _PUNC   0x0020  /* punctuation */
#define _GRPH   0x0040  /* graphic (= "printable" - blank) */
#define _PRNT   0x0080  /* printable */
#define _LOWR   0x0100  /* lower case */
#define _UPPR   0x0200  /* upper case */
#define _BLNK   0x0400  /* blank (the ascii character for 0x40) */


#define isalnum(c)    ( __chattr((char)((c) & 0xFF)) & (_ALPH | _DEC) )
#define isalpha(c)    ( __chattr((char)((c) & 0xFF)) & (_ALPH)        )
#define isdigit(c)    ( __chattr((char)((c) & 0xFF)) & (_DEC)         )
#define isgraph(c)    ( __chattr((char)((c) & 0xFF)) & (_GRPH)        )
#define islower(c)    ( __chattr((char)((c) & 0xFF)) & (_LOWR)        )
#define isupper(c)    ( __chattr((char)((c) & 0xFF)) & (_UPPR)        )
#define isprint(c)    ( __chattr((char)((c) & 0xFF)) & (_PRNT)        )
#define ispunct(c)    ( __chattr((char)((c) & 0xFF)) & (_PUNC)        )
#define isspace(c)    ( __chattr((char)((c) & 0xFF)) & (_SPAC)        )
#define isxdigit(c)   ( __chattr((char)((c) & 0xFF)) & (_HEX)         )
#define iscntrl(c)    ( __chattr((char)((c) & 0xFF)) & (_CTL)         )
#define isascii(c)    ( !( (c) & ~0x7f) )

#define toascii(c)    ( (c) & 0x7f )

#define _tolower(c)   ( (c) - 'A' + 'a' )
#define _toupper(c)   ( (c) - 'a' + 'A' )


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int       _FIXED _FAR tolower  (int c);
extern int       _FIXED _FAR toupper  (int c);
extern short int _FIXED _FAR __chattr (char c);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* _CTYPE_H_ */
