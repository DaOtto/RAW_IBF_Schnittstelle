/*--FILE HEADER---------------------------------------------------------------
;   filename        : rwth_task.hpp
;   version         : V1.0
;   contents        : global dat declarations
;   author          : K. Brauckmann, SMS Eumuco GmbH
;   date            : May, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   globale Datenstrukturen des Projekts 
;
;       RMOS3 Version 3.30
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   May , 10. 2006  0001  K.B.  original issue
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
#ifndef rwth_task_hpp
   #define rwth_task_hpp

   #define RWTH_Version "V101 Rev. 1 Der Michl spielt schon wieder ;-)"
   
   #define RWTH_Abtastzeit     100         //ganzzahlig in [ms]
   #define FLAG1               0x1
   #define STACK_SIZE          0x8000      //=32768 dez. für RmCreateTask()
   #define PRIO_RWTH           85          // Priorität ist auf die anderen Tasks
                                        // im System abgestimmt und darf nicht 
                                        // verändert werden!

   #include "puff_cnc_s.hpp"
   #include "onli_cnc_s.hpp"
   #include "rwth_logger.hpp"
   #include "rwth_exch.hpp"
   #include "rpw.hpp"

   #ifdef   MainModul  
      uint                FlagId;
      RWTH_EXCH           *rwth_exch;
      LOGGER_RWTH         *Logger;
      
      Def_Ein_Puff        ein_puff;
      Def_Aus_Puff        aus_puff;
      Def_Ein_Onli        ein_onli;
      Def_Aus_Onli        aus_onli;
      Def_Lokal_Puff      lokal_puff;
      ofstream            MyLogFile;
      
      ulong               TestCounter[20];
      //-----------------------------------------------------------------------
      // Klasse RPW wird einmal (dynamisch) angelegt
      
      RPW                 *rpw;
      float              IBF_PARA[IBF_PARA_MAX];
      
      int    iter_IBF;
      struct Def_Ist_Inter           Ist_Inter;
      struct Def_Soll_Inter          Soll_Inter;
      struct Def_IBF_Allgemein_SOLL  Soll_IBF;
      struct Def_IBF_Allgemein_IST   Ist_IBF;    
   #else
      extern uint                    FlagId;
      extern RWTH_EXCH               *rwth_exch;
      extern LOGGER_RWTH             *Logger;
      
      extern Def_Ein_Puff            ein_puff;
      extern Def_Aus_Puff            aus_puff;
      extern Def_Ein_Onli            ein_onli;
      extern Def_Aus_Onli            aus_onli;
      extern Def_Lokal_Puff          lokal_puff;
      extern ofstream                MyLogFile;
      
      extern ulong                   TestCounter[20];
      //-----------------------------------------------------------------------
      extern RPW                            *rpw;
      extern float                          IBF_PARA[IBF_PARA_MAX];
   
      extern int    iter_IBF;
      extern struct Def_Ist_Inter           Ist_Inter;
      extern struct Def_Soll_Inter          Soll_Inter;
      extern struct Def_IBF_Allgemein_SOLL  Soll_IBF;
      extern struct Def_IBF_Allgemein_IST   Ist_IBF;    
   
   #endif
#endif
