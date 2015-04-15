/*--FILE HEADER---------------------------------------------------------------
;	filename	    : rmos_inc.h
;   version         : V0.1
;	contents	    : Includes for RMOS
;   author          : K. Brauckmann, SMS Eumuco GmbH
;   date            : 2004
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;	function:	Zusammenfassung der Includes für RMOS
;
;       RMOS3 Version 3.20
;
;---END OF	FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   February, 03. 2004  0001  K.B.  original issue
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
#ifndef rmos_inc_h
	#define rmos_inc_h

#define SMP16_RMOS3

#ifdef __WIN32
		#include <stdio.h>
		#include <stdlib.h>
		#include <exception>
		#include <new.h>
		#include <typeinfo.h>
		#include <stdexcept>
		#include <iostream>
		#include <iomanip> // setprecision
		#include <fstream>
		#include <strstream>
		#include <string.h>
		#include <io.h>
//		#include <rmapi.h>
//		#include <task.h>
		#include <rmos320.h>
		#include <math.h>
//		#include <rio.h>
//		#include <rmnames.h>
		#include <ctype.h>
//		#include <com201.h>
//		#include <dpn_user.h>
	#else
		#include <stdio.h>
		#include <stdlib.h>
		#include <exception.h>
		#include <new.h>
		#include <typeinfo.h>
		#include <stdexcept.h>
		#include <iostream.h>
		#include <iomanip> // setprecision
		#include <fstream.h>
		#include <strstream.h>
		#include <string.h>
		#include <\rm3dev\inc\io.h>
		#include <rmapi.h>
		#include <task.h>
		#include <rmos320.h>
		#include <math.h>
		#include <rio.h>
		#include <rmnames.h>
		#include <ctype.h>
		#include <com201.h>
		#include <dpn_user.h>
	#endif // __WIN32

#endif //rmos_inc_h

