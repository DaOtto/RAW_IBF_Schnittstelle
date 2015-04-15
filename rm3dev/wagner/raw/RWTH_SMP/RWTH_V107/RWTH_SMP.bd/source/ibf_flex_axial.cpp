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


/** Definiert das Verhalten, beim Axialprofilieren in den Verschiedenen Phasen.
 * <p>Fuer den Fall, dass sich der ring in der ersten Phase befindet und somit
 * das Ringwalzwerk erst noch zugestellt werden muss, wird dies mit einer
 * konstanten vorgegeben Geschwindigkeit getan. Die Position, zu der zugestellt
 * wird, wird mit Hilfe von \link AGR_Soll_Pos \endlink berechnet. </p>
 * <p>Fuer den Fall, dass sich der Ring in der Rundungsphae befindet, werden
 * konstante Geschwindigkeiten fuer Radial-, Axialschlitten oben und unten, sowie
 * fuer die Zentriererollen rechts und links festgelegt. Die Kräfte der Rollen
 * werden mit Hilfe der Methode \link Kraftsteuerung \endlink festgelegt.
 * Die Drehzahlen fuer die obere und untere Kegelwalze werden mit Hilfe
 * von \link KW_Drehzahl_axial \endlink . Die Anzahl der Methodenaufrufe waehrend
 * der Rundungsphase entspricht der Anzahl der Glaettungsrunden. Ist die Anzahl
 * erreicht, wird das \link Axial_Flex_Prof.Profilflag \endlink auf '12' gesetzt und 
 * somit die naechste Phase eingeleitet.</p>
 * <p> Fuer den Fall, dass der Ring gerade eine Rundungsphase beendet hat, werden
 * konstante Geschwindigkeiten fuer Radial-,Axialschlitten oben und unten, sowie
 * fuer die Zentrierarme rechts und links gesetzt. Die Kraefte der Rollen werden
 * mit Hilfe von \link  Kraftsteuerung \endlink und die Drehzahlen mit \link
 * KW_Drehzahl_axial \endlink berechnet. Es folgt eine Abfrage, ob weitere Profile
 * gewaltz werden sollen.
 *
 *@param[in] Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 *@param[in] Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
 *@param[in] *Soll_Inter ein Zeiger auf eine Struktur vom Typ 
    \link Def_Soll_Inter \endlink
 *@param[in] *Soll_IBF ein Zeiger auf eine Struktur vom Typ 
    \link Def_IBF_Allgemein_SOLL \endlink
 *@return[out] Nach Ablauf der Methode beziehungsweise nach Beendigung einer der 
 * Profilierphasen, wird der Rückgabewert \link TRUE \endlink zurückgegeben.
 */
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
                             //DA_Jenkouk_Regler_AG(Ist_IBF, Soll_IBF);
  

                             if(Ist_IBF.Axial.Turbine.zweite_Ebene_erreicht == 1 && (Ist_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num] >= 0.0F) ) // Wenn kein Profil erzeugt werden soll, mus Zeit gespart werden
                             {
                              int Hilfsv = Ist_IBF.Axial.Pr_Num - Ist_IBF.Axial.Biss.Anzahl;
                              Soll_IBF->ASO_Pos = Ist_IBF.Rohling_h_angefahren 
                                                - Ist_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num] 
                                                - Ist_IBF.Axial.Pr_Tiefe[Hilfsv]; // Profiltiefe der 2ten ebene muss noch Profiltief der 1sten Ebende abgezogen werden. 
                             }
                             else   
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
                                                    
                             if(Ist_IBF.Flag.Bissverhaeltnis == 1) // Walzen mit Bissverhältnis / Bissversatz
                                {
                                  
                                  if(      (Soll_IBF->Axial.Biss.Anzahl >= (Ist_IBF.Axial.Biss.Anzahl-1))
                                        && (Soll_IBF->Axial.Biss.Anzahl < (Ist_IBF.Axial.Biss.Anzahl_zweite_Ebene - 1))
                                        && (Soll_IBF->Axial.Biss.Anzahl != Ist_IBF.Axial.Biss.Anzahl_zweite_Ebene)
                                    )
                                        {
                                            if((Ist_IBF.Axial.Turbine.Turbinenscheibe == 1) && (Ist_IBF.Axial.Turbine.zweite_Ebene_erreicht == 0))
                                                {
                                                Soll_IBF->Axial.Biss.Anzahl++;  // Erhöhen der Anzahl für nächsten Durchlauf
                                                Soll_IBF->Axial.Pr_Num = Soll_IBF->Axial.Pr_Num + 1; // Hochsetzen für nächste Bisshöhe/Profilhöhe
                                                Soll_IBF->Axial.Turbine.s_akt_Merker = Ist_IBF.RS_Pos;
                                                //Soll_IBF->Zeit.t_Halte = -1;
                                                //Soll_IBF->tr_pos = 3.0F;
                                                Soll_IBF->Axial.Profilflag = 14;
                                                }
                                            if((Ist_IBF.Axial.Turbine.Turbinenscheibe == 1) && (Ist_IBF.Axial.Turbine.zweite_Ebene_erreicht == 1))
                                                {
                                                Soll_IBF->Axial.Biss.Anzahl++;  // Erhöhen der Anzahl für nächsten Durchlauf
                                                Soll_IBF->Axial.Pr_Num = Soll_IBF->Axial.Pr_Num + 1; // Hochsetzen für nächste Bisshöhe/Profilhöhe
                                                Soll_IBF->Axial.Profilflag = 13;
                                                }
                                     
                                        }
                                   
                                   else if (   (Soll_IBF->Axial.Biss.Anzahl < (Ist_IBF.Axial.Biss.Anzahl-1)) 
                                            && (Soll_IBF->Axial.Biss.Anzahl != Ist_IBF.Axial.Biss.Anzahl) )
                                        { 
                                        Soll_IBF->Axial.Biss.Anzahl++;  // Erhöhen der Anzahl für nächsten Durchlauf
                                        Soll_IBF->Axial.Pr_Num = Soll_IBF->Axial.Pr_Num + 1; // Hochsetzen für nächste Bisshöhe/Profilhöhe
                                        Soll_IBF->Axial.Profilflag = 13;
                                        }
                                   else if (Soll_IBF->Axial.Biss.Anzahl == Ist_IBF.Axial.Biss.Anzahl_zweite_Ebene )
                                        Soll_IBF->Profilflag = 13; 
                                   
                                  }// endif Bissverhältnis
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
                                                                    
                                  Soll_IBF->Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num] = Ist_Inter.tr_pos
                                                                                - Ist_IBF.Axial.Kr_geo.Kr_Br 
                                                                                - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR;
                                 }
                                 
                             if(Ist_IBF.Axial.Biss.AG_Pos_Erreicht == 1)  
                                {
                                     if(Ist_IBF.Axial.Turbine.zweite_Ebene_erreicht == 1)
                                        {
                                        int Hilfsv = Ist_IBF.Axial.Pr_Num - Ist_IBF.Axial.Biss.Anzahl;
                                        Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos_Start 
                                                          - Ist_IBF.ASO_Pos_Differenz 
                                                          - Ist_IBF.Axial.Pr_Tiefe[Hilfsv]; 
                                        }
                                     
                                      else
                                      {
                                        Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos_Start 
                                                          - Ist_IBF.ASO_Pos_Differenz; 
                                      }
                                    
                                     if(Ist_IBF.ASO_Pos <= Soll_IBF->ASO_Pos) 
                                       {
                                       Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos;
                                       Soll_IBF->Axial.Profilflag = 9;
                                       Soll_IBF->Axial.Biss.AG_Pos_Erreicht = 0;
                                       }
                                }
                                
                                 
                     
                            break; 

                case 14:    /* Positionieren des Axialgerüstes für zweite Ebene beim Turbinenwalzen an Außendurchmesser*/
                            
                            
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
                 
                             /* Positionsvorgabe: Kragenwalze wird hier immer auf die mittlere Wanddicke positioniert */

                                Soll_IBF->AG_Pos   =   Ist_Inter.da 
                                                    - Ist_IBF.Axial.AGR_Pr[0] 
                                                    - Ist_IBF.Axial.Kr_geo.Kr_Br 
                                                    - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
                                                    + Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw; 

                            /*
                             if(Soll_IBF->Zeit.t_Halte <=0 && Soll_IBF->Axial.Turbine.AG_Pos_Erreicht == 0)
                              {
                               
                              Soll_IBF->tr_pos =    Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
                                                    + Ist_IBF.Axial.Kr_geo.Kr_Br
                                                    + Ist_IBF.Axial.AGR_Pr[3];

                               Soll_IBF->delta_tr = Ist_Inter.tr_pos - Soll_IBF->tr_pos;
                               
                               Soll_IBF->AG_Pos = Ist_IBF.AG_Pos + Soll_IBF->delta_tr;
                               Soll_IBF->Zeit.t_Halte=10;
                              }
                           if(Soll_IBF->tr_pos <= Ist_IBF.Axial.Kr_geo.Del_Kr_AGR)
                              {
                              Soll_IBF->AG_Pos = Ist_IBF.AG_Pos + Soll_IBF->delta_tr;
                           
                              }
                             Soll_IBF->Zeit.t_Halte--; 
                           */
                                                            
                           if( (Ist_IBF.AG_Pos <= (Soll_IBF->AG_Pos + 2.0F)) && (Ist_IBF.AG_Pos >= (Soll_IBF->AG_Pos - 2.0F)) )  
                                 {
                                  Soll_IBF->Axial.Turbine.AG_Pos_Erreicht = 1;
                                  
                                  // Für die nachfolgenden case-Anweisung ist es wichtig, dem Gerüst die neue Position mitzuteilen
                                  Soll_IBF->Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num]  = Ist_Inter.tr_pos
                                                                                - Ist_IBF.Axial.Kr_geo.Kr_Br 
                                                                                - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR;
                                 }

                            /*                                               
                             if (Soll_IBF->delta_tr >= -1.0F && Soll_IBF->delta_tr <= 1.0F)
                                 {
                                  Soll_IBF->Axial.Turbine.AG_Pos_Erreicht = 1;
                                  
                                  // Für die nachfolgenden case-Anweisung ist es wichtig, dem Gerüst die neue Position mitzuteilen
                                  Soll_IBF->Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num]  = Ist_Inter.tr_pos
                                                                                - Ist_IBF.Axial.Kr_geo.Kr_Br 
                                                                                - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR;
                                 }
                             */

                              if(Soll_IBF->Axial.Turbine.AG_Pos_Erreicht == 1)
                              {
                                 
                                     Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos_Start 
                                                          - Ist_IBF.ASO_Pos_Differenz 
                                                          - Ist_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Biss.Anzahl - Ist_IBF.Axial.Pr_Num] ; 
                                        
                                
                                     if(Ist_IBF.ASO_Pos <= Soll_IBF->ASO_Pos) 
                                       {
                                           Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos;
                                           Soll_IBF->Axial.Profilflag = 9;
                                           Soll_IBF->Axial.Turbine.zweite_Ebene_erreicht = 1;
                                           // Profiltiefe wird in rpw.cpp vorgegeben
                                       }
                                 }
                     
                            break; 

                            


                 
         default:   break;
         }// end switch(Profilflag)
         
    return TRUE;
}

