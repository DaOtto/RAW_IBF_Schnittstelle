#include "rpw.hpp"

    /*-----------------------------------------------------------------------*/
    /*                                                                       */
    /*                          IBF Funktionen                               */
    /*                                                                       */
    /*-----------------------------------------------------------------------*/


    float KW_Drehzahl_oben(struct Def_Ist_Inter Ist_Inter,struct Def_IBF_Allgemein_IST  *Ist_IBF)
    {

    return(kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe));

    }

    
    float KW_Drehzahl_unten(struct Def_Ist_Inter Ist_Inter,struct Def_IBF_Allgemein_IST  *Ist_IBF)
    {
        return(kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe));
    }

                 



