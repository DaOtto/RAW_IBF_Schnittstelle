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
#include "rpw.hpp"
#include "iniFile.h"
#include "IBF_struct.hpp"

#ifndef _IBF_TOOL_H
    #define _IBF_TOOL_H

// Für IniFile.cpp
#include "stdio.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#define IBF_Position        1   //für Weg-/Kraftreglung wird IBF-Positionsvorgabe verwendet
#define SMS_Startposition   2   //nur beim Walzenstart (Beladen->Schließen & auf Position) kann hier zunächst die SMS-Position weiterverwnedet werden
#define Abschalten          3   //Endmaß erreicht. Abschalten

#define Euler               2.7182818284 //Eulersche Zahl





    //Drehzahlen
    float KW_Drehzahl_oben(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF);
    float KW_Drehzahl_unten(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF);

    // Kraftsteuerung
    void Kraftsteuerung(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Anwalzen_Radial (struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Anwalzen_Axial (struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF); 

    //AG-Modus
    void Modus_AG(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF, char Auswahl);
    void Abschaltung(struct Def_IBF_Allgemein_SOLL *Soll_IBF);
  
    //Axialschlittenhöhe Radial flexibel
    void Breitungsexp(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Durchme_t2(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

    void Volumenbestimmung(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Hoehenzunahme(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

        

                                                               
#endif


