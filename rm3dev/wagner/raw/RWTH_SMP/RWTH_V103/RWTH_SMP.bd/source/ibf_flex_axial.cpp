/*--FILE HEADER---------------------------------------------------------------
;   filename        : ibf_flex_radial.cpp
;   version         : V1.02
;   contents        : IBF-Modul FLEXIBLE AXIAL PROFILING 
;   author          : D. Michl, Institute of Metal Fotrming, RWTH-Aachen University
;   date            : Jul, 2007
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   required calculaton of tool path, feed rate, etc. 
;               for axial profiling
;       RMOS3 Version 3.30
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   Jul , 30. 2007  0001  D.M.  original issue
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
/****************************************************************************/
/*  includes                                                                */
/****************************************************************************/

#include "rpw.hpp"


/****************************************************************************/
/*  function                                                                 */
/****************************************************************************/

int RPW::flexibel_Axial(struct Def_Ist_Inter          Ist_Inter,
                        struct Def_IBF_Allgemein_IST  Ist_IBF, 
                        struct Def_Soll_Inter         *Soll_Inter,
                        struct Def_IBF_Allgemein_SOLL *Soll_IBF)
{
    //Programmmodul zum FLEXIBLEN AXIALEN PROFILIEREN

    switch(Ist_IBF.Profilflag)
        {
         case 10:   /* -------------------------------------------------------------
                    ; Axialschlitten mit const. vorgegebener Geschwindigkeit zustellen
                    ; Axialgerüst mit Funktion AGR_Soll_Pos() positionieren
                    ; Radialschlitten in Kraftsteuerung an Ring andrücken
                    ;--------------------------------------------------------------*/

                    /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 2.0F; 
                             Soll_IBF->ASO_V        = Ist_IBF.Axial.Vorschub/Ist_IBF.Zeit.Ringumdrehung; // [mm/U] / [s/U]
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 0.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F; 

                             /* Kräfte */
                             Anwalzen_Radial(Ist_IBF , Soll_IBF); // Vorgabe der gefordeten Kräfte, Spezialroutine für Kraftreglung Radialschlitten
                               
                             /* Drehzahl */
                             Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                             Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                 
                             /* Positionsvorgabe: Abhängig ob Kraft- oder Weggebunden */


                    break; 

         default:   break;
         }// end switch(Profilflag)
    return TRUE;
}

