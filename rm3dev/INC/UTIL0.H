/*--FILE HEADER---(set tabulator to 8)----------------------------------------
;
;   filename    : UTIL0.H
;   version     : 0001
;   contents    : headerfile functions for read/write ser. eeprom
;   author      : B.N.
;   date        : Jul 28, 1999
;
;---FUNCTION AND RMOS ENVIRONMENT---------------------------------------------
;
;   function    : headerfile functions for read/write ser. eeprom
;
;   RMOS2 & RMOS3
;
;---END OF FILE HEADER--------------------------------------------------------
;
;---MODIFICATION HEADER-------------------------------------------------------
;
;   Jul 28, 1999  B.N.   0001  Original issue
;
;---END OF MODIFICATION HEADER----------------------------------------------*/

#ifndef _UTIL0_H_
#define _UTIL0_H_


/* SMB-Registers */
#define SMB_STATUS_REG     0x5000
#define SMB_CONTROL_REG    0x5002
#define SMB_DEV_ADR_REG    0x5004
#define SMB_SUB_ADR_REG    0x5003
#define SMB_DATA0_REG      0x5005
#define SMB_DATA1_REG      0x5006
#define CORE_TOP           0x0D

int _FIXED _FAR ReadSerEEPROM( unsigned long fepr_offset, 
                               unsigned long numofBytes,
                               unsigned char _FAR* dstptr);

int _FIXED _FAR WriteSerEEPROM( unsigned long fepr_offset,
                                unsigned long numofBytes,
                                unsigned char _FAR* dstptr);

int _FIXED _FAR GetMaxLengthSerEEPROM( unsigned long _FAR* numofBytes);

int _FIXED _FAR ReadTemperatureCore( unsigned char _FAR* buffer );

int _FIXED _FAR SecEraseFEPROM (unsigned long fepr_offset);

int _FIXED _FAR WriteFEPROM (unsigned long fepr_offset,
                             unsigned long numofBytes,
                             unsigned char _FAR *dstptr);

int _FIXED _FAR ReadFEPROM (unsigned long fepr_offset,
                            unsigned long numofBytes,
                            unsigned char _FAR *srcptr);

int _FIXED _FAR GetCPUTyp( char _FAR * buffer,
                           unsigned int _FAR * typ);

#endif /* _UTIL0_H_ */
