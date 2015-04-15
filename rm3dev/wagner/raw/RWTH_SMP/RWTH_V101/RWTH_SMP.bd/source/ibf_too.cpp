#include "rpw.hpp"

    /*-----------------------------------------------------------------------*/
    /*                                                                       */
    /*                          IBF Funktionen                               */
    /*                                                                       */
    /*-----------------------------------------------------------------------*/


    float KW_Drehzahl_oben(
    {

    Soll_Inter->kwo_n    = kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);
    Soll_Inter->kwu_n    = kw_ia/hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*sin_kw_winkel_halbe);               			
                 


     int Istwerte_RAW(struct Def_Ein_Puff    Ein_Puff,
                       struct Def_Lokal_Puff  Lokal_Puff,
                       struct Def_Aus_Puff    Aus_Puff,
                       struct Def_Ist_Inter   *ist_inter);

      int Main(struct Def_Ist_Inter          Ist_Inter,
               float  IBF_PARA[IBF_PARA_MAX], 
               struct Def_IBF_Allgemein_IST  *Ist_IBF, 
               struct Def_Soll_Inter         *Soll_Inter,
               struct Def_IBF_Allgemein_SOLL *Soll_IBF)
