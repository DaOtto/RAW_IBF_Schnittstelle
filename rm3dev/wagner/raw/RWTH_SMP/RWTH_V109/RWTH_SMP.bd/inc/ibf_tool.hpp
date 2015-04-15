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
;               Diese Headerdatei muss in alle IBF cpp-Datein eingebunden
;               werden.
;
;       RMOS3  Version 3.30
;       CAD-UL Version V120C
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   October , 10. 2006  0001  D.M.  original issue V1.0
;   November, 11. 2007  0002  D.M.  Erweiterung mit Funktionsprototypen 
;                                   für ibf_Filter.cpp                               
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


    
    //--------------------------------------------
    // Prototypenfunktionen aus ibf_tool.cpp Datei
    //--------------------------------------------

    //Drehzahlen

	/** @fn KW_Drehzahl_axial (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF)
	 * @brief Funktion, mit der fuer das Axialprofilieren die Drehzahl der Kegelwalzen bestimmt wird*/
    float KW_Drehzahl_axial  (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF);
    float KW_Drehzahl_unten (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF);
    
    
    // Radialschlitten Axialschlitten Betriebsmodus
    void rs_aso_mode(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF, int Funktionswahl);

    // Kraftsteuerung
    void Axialkraft     (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Kraftsteuerung (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Anwalzen_Radial(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Anwalzen_Axial (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF); 


    //AG-Modus
    void IBF_Abschaltung(struct Def_Soll_Inter *Soll_Inter,struct Def_IBF_Allgemein_IST Ist_IBF);
    //void Modus_AG(struct Def_Soll_Inter *Soll_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, char Auswahl); -> jetzt in der Klasse RPW deklariert
    
    
    // Funktionen Modul "Flexibel radial Profilieren" 
    // Axialschlittenhöhe Radial flexibel
    void Breitungsexp(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Durchme_t2  (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

    void Volumenbestimmung(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Hoehenzunahme(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

    // Funtionen zu Modul "Flexibel axial Profilieren"
    
    int   AGR_Pr_Wanddicken_Verhaeltnis_proz(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    char  AGR_Nachfuehr_Entscheider         (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    float AGR_Soll_Pos                      (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void AGR_Soll_Pos_delta_Tr             (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    //----------------------------------------------
    // Prototypenfunktionen aus ibf_Filter.cpp Datei
    //----------------------------------------------


                                                               
#endif


