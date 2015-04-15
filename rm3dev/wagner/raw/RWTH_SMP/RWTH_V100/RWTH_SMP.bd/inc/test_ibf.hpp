/*--FILE HEADER---------------------------------------------------------------
;   filename        : test_ibf.hpp
;   version         : V1.0
;   contents        : Testwerte aufbereiten
;   author          : K. Brauckmann, SMS Eumuco GmbH
;   date            : May, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   Testwerte werden auf die CARWIN-Testfelder gelegt
;
;   RMOS3 Version 3.30
;
;   (c) 2006 SMS Eumuco GmbH Produktbereich Ringwalzen
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   May , 12. 2006  0001  K.B.  original issue
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
#ifndef test_ibf_h
#define test_ibf_h

class   TEST_IBF
{
    public:

        TEST_IBF(void);
        ~TEST_IBF(){;}
        void WRITE_VALUES(long * TestDat, char * TestString, int SizeString);

    private:
        ulong   CountTest;

};

#ifdef MainModul
    TEST_IBF * tmode[4];
#else
    extern TEST_IBF * tmode[4];
#endif
#endif
