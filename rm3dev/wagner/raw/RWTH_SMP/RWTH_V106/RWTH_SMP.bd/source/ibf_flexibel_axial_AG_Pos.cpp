#include "rpw.hpp"
//#include "iniFile.h"




    /*-----------------------------------------------------------------------*/
    /*                                                                       */
    /*                    IBF Profilpositions-Regelung                       */
    /*                                                                       */
    /*             Hier alle Funktionen aus DA Jenkouk entstanden sind       */
    /*             -Axialprofilieren -> KW so positionieren,                 */
    /*                dass sAX,A/sAX= const.                                 */
    /*             - Version 1. Weginfo generieren                           */
    /*             05.05.08 V. Jenkouk, D.Michl                              */
    /*                                                                       */
    /*-----------------------------------------------------------------------*/


 
    
// Funktionen mit denen Messwerte ermittelt und aufbereitet werden.......    
  

// Funktionen mit denen die Regelung der Axialgeruestes realisiert wird....


 
 
 
/*--------Regelprogramm-------------------------------------------------------*/

void AG_Regelalgo(struct Def_IBF_Allgemein_IST Ist_IBF, 
                  struct Def_IBF_Allgemein_SOLL *Soll_IBF)
 {
    //Deklariere lokale Variablen

    
    int schritt; // Differenz der Anzahl von Regelzyklen
    


 
    schritt = (int)(Ist_IBF.Zeit.Ringumdrehung/(2*regel_zyklus_fak*0.1F)); 
    //Regel_zyklus_fak wie oft Regelfkt aufgerufen wird

    
    // Bei jedem Aufruf muss das Hilfsarray einmal komplett gefüllt werden
    for( int i=0; i< (Arraygroesse - 1); i++)
    {
     Soll_IBF->AG_Regelung.Wanddicke_axial_soll[i] = Soll_IBF->AG_Regelung.Wanddicke_axial_Hilf[i];
    }

    // Verchieben des Arrays, damit Messwertposition im -1 reduziert wird (entsp. Zeitdauer vom Regelzyklus bis Radialwalzspalt am Axialwalzspalt anliegt)
      for( int i=0; i< (Arraygroesse - 2); i++)
    {
     Soll_IBF->AG_Regelung.Wanddicke_axial_soll[i] = Soll_IBF->AG_Regelung.Wanddicke_axial_Hilf[i+1];
    }


    Soll_IBF->AG_Regelung.Wanddicke_axial_soll[Arraygroesse-1] = 0; //Letztes Element des Arrays muss Null sein
    
    Soll_IBF->AG_Regelung.Wanddicke_axial_soll[schritt] = Ist_IBF.RS_Pos; // Fülle Element mit Wanddicke vom Radialwalzspalt aus

    if(Soll_IBF->AG_Regelung.Wanddicke_axial_soll[0] != 0) 
        { 
          Soll_IBF->AG_Pos = Ist_IBF.AG_Pos 
                            + Ist_IBF.TR_Pos
                            - Soll_IBF->AG_Regelung.psi * Soll_IBF->AG_Regelung.Wanddicke_axial_soll[0]
                            - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
                            + Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw; 
 
       }

     Soll_IBF->AG_Regelung.Wanddicke_axial_Aussensegment = Ist_IBF.TR_Pos 
                                                          - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
                                                          + Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw;  
         
    
  
 
 };
 

 // Hauptprogramm des Regelalgorithmus der im rpw.cpp eingebunden werden kann

void DA_Jenkouk_Regler(struct Def_IBF_Allgemein_IST Ist_IBF, 
                       struct Def_IBF_Allgemein_SOLL *Soll_IBF)
{
    
    if(Soll_IBF->AG_Regelung.Aufrufzeit_Regelzykl >= (regel_zyklus_fak - 1))
    {
    //Berechne die Zeit von Radialwalzspalt in den Axialwalzspalt 
    
    //Berechen die DW-Zustellung
    AG_Regelalgo(Ist_IBF, Soll_IBF);
    Soll_IBF->AG_Regelung.Aufrufzeit_Regelzykl = -1;
    }
    Soll_IBF->AG_Regelung.Aufrufzeit_Regelzykl++;
    
}
 



