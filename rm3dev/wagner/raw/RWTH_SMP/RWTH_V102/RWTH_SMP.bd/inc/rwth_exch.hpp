/*--FILE HEADER---------------------------------------------------------------
;	filename	    : rwth_exch.hpp
;   version         : V1.0
;	contents	    : Data transfer to and from CNC / TRT
;   author          : K. Brauckmann, SMS Eumuco GmbH
;   date            : May, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;	function:	ein_puff / aus_puff Strukturen von bzw. auf globealen  
;				Memorypool kopieren
;
;       RMOS3 Version 3.30
;
;---END OF	FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   May , 10. 2006  0001  K.B.  original issue
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
#ifndef rwth_exch_hpp
#define rwth_exch_hpp
void svc_sts (unsigned int index, char *svc_txt, int status);



class	RWTH_EXCH
{
	public:
		RWTH_EXCH(void);
		~RWTH_EXCH();
		int put_puff(void);
		int get_puff(void);
		int Main_Control(void);
		int running_flag;
		int finish_flag;

        TeDat4_type     TeDat;

        uint * get_pCountBlinker(void){return(&CountBlinker);} //Test Logger
        uint * get_pBlinker(void){return(&Blinker);}           //Test Logger

	protected:
		uint Sema_PowerSendID;
		uint Sema_PowerRecID;
		uint TRT_Mail_id;
		int	 Status;
		RmMailboxStruct TRT_Mail;
		RmEntryStruct   Entry;

        uint  CountBlinker;
        uint  Blinker;
    
};

#endif
