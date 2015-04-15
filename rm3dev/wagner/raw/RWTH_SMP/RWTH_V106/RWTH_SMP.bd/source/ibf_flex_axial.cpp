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

    switch (Ist_IBF.Axial.Profilflag)
        {

        case 9:   /* -------------------------------------------------------------
                    ; Axialschlitten mit const. vorgegebener Geschwindigkeit zustellen
                    ; Axialgerüst mit Funktion AGR_Soll_Pos() positionieren
                    ; Radialschlitten in Kraftsteuerung an Ring andrücken, dafür muss allerdings Kraftsteuerung vorgewählt sein -> 
                    ;--------------------------------------------------------------*/
        
                    /* Stützstellenberechnung*/
                    konst_cr_axial(Ist_Inter, Ist_IBF, Soll_IBF);
                    stuetzstellen(Ist_Inter, Ist_IBF, Soll_IBF);

                    /*Dornwalzenregelung*/
                   // DA_Jenkouk_Regler(Ist_IBF, Soll_IBF);
  

                    /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 5.0F;
                             Soll_IBF->ASO_V        = Soll_IBF->stuetz_var.delta_h/Ist_Inter.Werkzeug.Ringumdrehung; // [mm/U] / [s/U]
                             //Soll_IBF->ASO_V        = Ist_IBF.Axial.Vorschub/Ist_IBF.Zeit.Ringumdrehung; // [mm/U] / [s/U]
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 10.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F; 

                             /* Kräfte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf
                               
                             /* Drehzahl */
                             Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                             Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                 
                             /* Positionsvorgabe: Abhängig ob Kraft- oder Weggebunden */
                             Soll_IBF->AG_Pos = AGR_Soll_Pos(Ist_Inter, Ist_IBF, Soll_IBF);
                             Soll_IBF->ASO_Pos = Ist_IBF.Rohling_h_angefahren - Ist_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num];
                             

                             if(Ist_IBF.ASO_Pos <= Soll_IBF->ASO_Pos) 
                                 {
                                   Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos;
                                   Soll_IBF->Zeit.t_Halte = 10 * Ist_Inter.Werkzeug.Ringumdrehung * Soll_IBF->Axial.Umdrehungen;   //Zeit berechnen für x-Ringumdrehungen
                                   Soll_IBF->Axial.Profilflag = 11;
                                 }
                     
                            break; 

          case 11:          /* -------------------------------------------------------------
                            ;  Rundungsphase
                            ;--------------------------------------------------------------*/

                              /*Dornwalzenregelung*/
                            //  DA_Jenkouk_Regler(Ist_IBF, Soll_IBF);
  

                            /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 2.0F; 
                             Soll_IBF->ASO_V        = 1.0F; //Axialschlitten soll in Rundungsphase nicht zustellen
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 10.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F; 

                             /* Kräfte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf
                               
                             /* Drehzahl */
                             Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                             Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                 
                             /* Positionsvorgabe: Abhängig ob Kraft- oder Weggebunden */
                             Soll_IBF->AG_Pos = AGR_Soll_Pos(Ist_Inter,Ist_IBF,&*Soll_IBF);
                             
                             if(Ist_IBF.Zeit.t_Halte <= 0) 
                                 {
                                   Soll_IBF->Axial.Profilflag = 12;
                                   Soll_IBF->Axial.Biss.AG_Pos_alt = Ist_IBF.AG_Pos;    // Merke für Bissverhältnis die Axialgerüstposition
                                 }
                             Soll_IBF->Zeit.t_Halte--; // Runterzählen der Zeit für Glättungsrunde
                             break;

         case 12:           /* -------------------------------------------------------------
                            ; Hochfahren des Axialschlittens und Abfragen, ob weitere                             
                            ; Profilstufe gewalzt werden soll
                            ;--------------------------------------------------------------*/

                                                        
                            /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 2.0F; 
                             Soll_IBF->ASO_V        = 30.0F; 
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 10.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F; 

                             /* Kräfte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf
                               
                             /* Drehzahl */
                             Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                             Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

                             /* Position */
                            Soll_IBF->ASO_Pos = Ist_IBF.Rohling_h_angefahren + 30.0F;
                            Soll_IBF->RS_Pos  = Ist_IBF.RS_Pos;

                          
                         if(Ist_IBF.ASO_Pos >= Soll_IBF->ASO_Pos - 1.0F) 
                            {
                             /* Abfrage ob weiteres Profil gewalzt werden soll / Schalter setzen*/
                                                    
                             if(Ist_IBF.Flag.Bissverhaeltnis == 1) // Walzen mit Bissverhältnis
                                {
                                   
                                    if(Soll_IBF->Axial.Biss.Anzahl == Ist_IBF.Axial.Biss.Anzahl)
                                    {
                                     Soll_IBF->Profilflag = 13;
                                    }
                                    else if (Soll_IBF->Axial.Biss.Anzahl != Ist_IBF.Axial.Biss.Anzahl)
                                    { 
                                        Soll_IBF->Axial.Biss.Anzahl++;  // Erhöhen der Anzahl für nächsten Durchlauf
                                        Soll_IBF->Axial.Profilflag = 13;
                                    }
                                }
                              else                                  
                                {
                                    Soll_IBF->Axial.Pr_Num = Soll_IBF->Axial.Pr_Num + 1;
                                    if(Soll_IBF->Axial.Pr_Num == Ist_IBF.Axial.Profilanzahl)
                                       {
                                        Soll_IBF->Profilflag = 13; // Prozessende
                                       }
                                    if(Soll_IBF->Axial.Pr_Num < Ist_IBF.Axial.Profilanzahl) 
                                       {
                                        Soll_IBF->AG_Pos_Start =  Ist_Inter.da 
                                                                - Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num] 
                                                                - Ist_IBF.Axial.Kr_geo.Kr_Br 
                                                                - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
                                                                + Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw;
                                       Soll_IBF->Profilflag = 0;    // Axialgerüst neu positionieren
                                       Soll_IBF->InitAchse = 'b';   
                                       }
                                 }
                              }
                         break;

         case 13:    /* Positionieren des Axialgerüstes anhand des vorgegebenen Bissverhältnisses  */

                            /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 0.0F;
                             Soll_IBF->ASO_V        = 20.0F; // [mm/U] / [s/U]
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 10.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F; 

                             /* Kräfte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf
                               
                             /* Drehzahl */
                             Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                             Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                 
                             /* Positionsvorgabe:  */
                             if(Ist_IBF.Axial.Biss.Position == 0 && Ist_IBF.Axial.Biss.AG_Pos_Erreicht != 1 ) // Innen neben dem Profil
                                {
                                Soll_IBF->AG_Pos = Soll_IBF->Axial.Biss.AG_Pos_alt - (Ist_IBF.Axial.Kr_geo.Kr_Br/100.0F * Ist_IBF.Axial.Biss.Verhaeltnis);
                                }
                             if(Ist_IBF.Axial.Biss.Position == 1 && Ist_IBF.Axial.Biss.AG_Pos_Erreicht != 1 ) // Außen neben dem Profil
                                {
                                Soll_IBF->AG_Pos = Soll_IBF->Axial.Biss.AG_Pos_alt + (Ist_IBF.Axial.Kr_geo.Kr_Br/100.0F * Ist_IBF.Axial.Biss.Verhaeltnis);
                                }
                       
                   

                             if( (Ist_IBF.AG_Pos <= (Soll_IBF->AG_Pos + 2.0F)) && (Ist_IBF.AG_Pos >= (Soll_IBF->AG_Pos - 2.0F)) ) 
                                 {
                                  Soll_IBF->Axial.Biss.AG_Pos_Erreicht = 1;
                                                                    
                                  Soll_IBF->Axial.AGR_Pr[0] = Ist_Inter.tr_pos
                                                            - Ist_IBF.Axial.Kr_geo.Kr_Br 
                                                            - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR;
                                 }
                                 
                             if(Ist_IBF.Axial.Biss.AG_Pos_Erreicht == 1)  
                                {
                                     Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos_Start - Ist_IBF.ASO_Pos_Differenz; 
                                
                                     if(Ist_IBF.ASO_Pos <= Soll_IBF->ASO_Pos) 
                                       {
                                       Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos;
                                       Soll_IBF->Axial.Profilflag = 9;
                                       }
                                 }
                     
                            break; 
                            


                 
         default:   break;
         }// end switch(Profilflag)
         
    return TRUE;
}

