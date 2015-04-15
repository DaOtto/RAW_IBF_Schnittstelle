/*--FILE HEADER---------------------------------------------------------------
;   filename        : ibf_tool.hpp
;   version         : V1.0
;   contents        : Tool for IBF software 
;   author          : D. Michl, IBF RWTH Aachen
;   date            : October, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   stellt Funtionen, die im IBF-Modul häufiger verwendet werden zur 
;               Verfügung.
;               Diese Datei muss in alle Projekte von SMS und IBF eingebunden
;               werden.
;
;       RMOS3  Version 3.30
;       CAD-UL Version V120C
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   October , 10. 2006  0001  D.M.  original issue V1.0
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
#ifndef _IBF_TOOL_HPP
    #define _IBF_TOOL_HP


    #include "rpw.hpp"




    float KW_Drehzahl_oben (struct Def_Ist_Inter Ist_Inter,struct Def_IBF_Allgemein_IST  *Ist_IBF);
    float KW_Drehzahl_unten(struct Def_Ist_Inter Ist_Inter,struct Def_IBF_Allgemein_IST  *Ist_IBF);

#endif
