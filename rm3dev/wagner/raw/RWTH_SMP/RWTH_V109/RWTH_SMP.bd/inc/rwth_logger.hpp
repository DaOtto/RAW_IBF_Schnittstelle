/*--FILE HEADER---------------------------------------------------------------
;   filename        : RWTH_LOGGER.HPP
;   version         : V1.0
;   contents        : Loggerfunktionen
;   author          : K. Brauckmann, SMS Eumuco GmbH
;   date            : May, 2004
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   Loggersteuerung und Loggerkanäle für IBF
;
;       RMOS3 Version 3.30
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   May, 11. 2006  0001  K.B.  original issue
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
/****************************************************************************/

#ifndef logger_h
#define logger_h

#include "raw_t_pool.hpp"

//---------------------------------------------------------------------------

class   LOGGER_RWTH
{
    public:
        LOGGER_RWTH(void);
        ~LOGGER_RWTH(){;}
        int Kanalliste(void);

        LOG_CHANNEL_DEF * getLogPointer(void){return(&TableLogRWTH[0]);}

    private:
        LOG_CHANNEL_DEF TableLogRWTH[MAX_LOG_KANAELE_RWTH];     //Speicherbereich Auswahlliste
};
#endif
