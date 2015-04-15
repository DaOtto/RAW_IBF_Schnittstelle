#include "rpw.hpp"
#include "iniFile.h"




    /*-----------------------------------------------------------------------*/
    /*                                                                       */
    /*                   Allgemeine IBF Funktionen                           */
    /*                                                                       */
    /*             Bitte beachten, dass einige Funktionen in Class RPW       */
    /*             eingebunden wurden, da diese neben der rpw.cpp-Datei      */
    /*             auch in der rwth-exch.cpp verwendet werden.               */
    /*                                                                       */
    /*             RPW::Modus_AG                                             */
    /*             RPW::Kr_Geo_berechnen                                     */
    /*             20.07.07 D.Michl                                          */
    /*                                                                       */
    /*-----------------------------------------------------------------------*/


    /* Drehzahlen */

    float KW_Drehzahl_axial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF)
    {
        // Es wird die Motordrehzahl vorgegeben, deshalb wird Übersetzung benötigt 
        return  Ist_Inter.kw_ia * (Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.hw_n / Ist_Inter.da)
                            * (Ist_Inter.da/2 - Ist_IBF->Axial.AGR_Pr[Ist_IBF->Axial.Pr_Num])
                            / ((Ist_IBF->Axial.Kr_geo.Del_Kr_AGR + Ist_IBF->Axial.Kr_geo.Kr_Br/2)*Ist_IBF->Axial.Kr_geo.sin_kw_winkel_halbe);
    }

    float KW_Drehzahl_unten(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF)
    {
        
     //   return(Ist_Inter.kw_ia/Ist_Inter.hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*Ist_Inter.sin_kw_winkel_halbe));
         return 1;
    }



    /* Radialschlitten Axialschlitten Betriebsmodus */

    void rs_aso_mode(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF, int Funktionswahl)
    {
        //Betriebsartvorwahl aufgrund der gesetzten Schalter Funktionswahl= 0 kommt von der Funktion Walzkraft
        //                                                   Funktionswahl= 1 kommt von den Funktionen Anwalzen 

        //Los geht´s
       
       switch(Funktionswahl)
       {
       case 0:
                // Radialschlitten
                if(Ist_IBF.Flag.rs_kraftregler_aktiv)
                    { 
                        Soll_IBF->Flag.rs_mode = 1;
                    }
                else 
                    {
                        Soll_IBF->Flag.rs_mode = 0; 
                    }

                // Axialschlitten
               if(Ist_IBF.Flag.as_kraftregler_aktiv)
                    {  
                        Soll_IBF->Flag.aso_mode = 1;
                    }
                else 
                    {
                        Soll_IBF->Flag.aso_mode = 0; 
                    }
                break;

         case 1:
                 // Radialschlitten
                 if( Ist_IBF.Flag.rs_kraftanfahren_aktiv)
                    { 
                        Soll_IBF->Flag.rs_mode = 1;
                    }
                else 
                    {
                        Soll_IBF->Flag.rs_mode = 0; 
                    }
            
                // Axialschlitten
                if(Ist_IBF.Flag.as_kraftanfahren_aktiv)
                    {  
                        Soll_IBF->Flag.aso_mode = 1;
                    }
                else 
                    {
                        Soll_IBF->Flag.aso_mode = 0; 
                    }
                break;

         default: break;
         }
       
    }


    /* Kraftsteuerung */

    void Axialkraft(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
      // Das Kegelwalzenadapter zum Axialprofiliern bedarf einer Kraftbegrenzung von max. 40T 
      // Die Kraftgrenze liegt derzeit bei 38 Tonnen !!!!
      // ----------------------------------------------------------
      // Ist_IBF.Flag.Axial_Radialwalzen = 0 für Axialprofilieren 
      // Ist_IBF.Flag.Axial_Radialwalzen = 1 für Radialprofilieren
      
      // Funktion wird immer von der Funktion Kraftsteuerung vorgegeben

      // Los geht´s

      if(Ist_IBF.Flag.Axial_Radialwalzen == 0)
        {
            Soll_IBF->AS_Kraft  = Ist_IBF.Flag.as_kraftregler_aktiv  ? Soll_IBF->AS_Kraft_Vorgabe  : 380000.0F ;  // 1 T = 10.000 N -> 38 T = 380.000 N
        }
      else
        {
            Soll_IBF->AS_Kraft  = Ist_IBF.Flag.as_kraftregler_aktiv  ? Soll_IBF->AS_Kraft_Vorgabe  : 380000.0F ; // erhöht auf 38 Tonnen (08.11.2007)
        } 

    }

    void Kraftsteuerung(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        // Vorgabe der Drück unter Berücksichtigung der Betriebsart Vorschubs-, Kraftsteuerung
        // Langrfistig Kraftvorgabe aus Carwin bezgl. DW-Durchmesser einbinden, um Dorndurchbiegung nicht zu vernachlässigen 27.07.07 D. Michl  
    
        // Los geht´s
        
        rs_aso_mode(Ist_IBF, &*Soll_IBF, 0);

        Axialkraft(Ist_IBF, &*Soll_IBF);

        Soll_IBF->RS_Kraft  = Ist_IBF.Flag.rs_kraftregler_aktiv  ? Soll_IBF->RS_Kraft_Vorgabe  : 100000.0F ;   // 10 T = 10.000 N = 10 kN
        //Soll_IBF->AS_Kraft  = Ist_IBF.Flag.as_kraftregler_aktiv  ? Soll_IBF->AS_Kraft_Vorgabe  :  80000.0F ;  
        Soll_IBF->AG_Kraft  = Ist_IBF.Flag.ag_kraftregler_aktiv  ? Soll_IBF->AG_Kraft_Vorgabe  :  10000.0F ; 
        Soll_IBF->ZAR_Kraft = Ist_IBF.Flag.zal_kraftregler_aktiv ? Soll_IBF->ZAL_Kraft_Vorgabe :  10000.0F ; 
        Soll_IBF->ZAL_Kraft = Ist_IBF.Flag.zar_kraftregler_aktiv ? Soll_IBF->ZAR_Kraft_Vorgabe :  10000.0F ;

     }

    void Anwalzen_Radial(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF) 
     {
        // Druckvorgabe für das Anwalzen unter Berücksichtigung der Vorschubs-; Kraftsteuerung
        
        //Los geht´s

        rs_aso_mode(Ist_IBF, &*Soll_IBF, 1); // Funktionsübergabe Struktur Ist_IBF, Soll_IBF, Zahlenwert 0=Walzen_gesamt/1=Anwalzen_speziell

        Axialkraft(Ist_IBF, &*Soll_IBF);
        
        Soll_IBF->AG_Kraft  = Ist_IBF.Flag.ag_kraftregler_aktiv  ? Soll_IBF->AG_Kraft_Vorgabe  :  100001.0F ; // 10 Tonnen = 100.000 N
        Soll_IBF->ZAR_Kraft = Ist_IBF.Flag.zal_kraftregler_aktiv ? Soll_IBF->ZAL_Kraft_Vorgabe :  10001.0F ;  //  1 Tonne  =  10.000 N
        Soll_IBF->ZAL_Kraft = Ist_IBF.Flag.zar_kraftregler_aktiv ? Soll_IBF->ZAR_Kraft_Vorgabe :  10001.0F ;  //  1 Tonne  =  10.000 N
 
        // Soll Radialwalzkraft vorgeben (DEFAULT-Zahlenwert +1,+2,+3, um zu ermitteln aus welcher if-Anweisung Wert kommt)
        if (Ist_IBF.Flag.rs_kraftanfahren_aktiv == 1) // Schalter: Anwalzen in Kraft (rs_kraftanfahren_aktiv = 1) oder generell in Kraft walzen 
         {
           Soll_IBF->RS_Kraft = Ist_IBF.Flag.rs_kraftanfahren_aktiv ? Soll_IBF->RS_Kraft_Anfahren : 80001.0F ; // 8 Tonnen = 80.000 N  
         }
        else
           Soll_IBF->RS_Kraft = Ist_IBF.Flag.rs_kraftregler_aktiv ? Soll_IBF->RS_Kraft_Vorgabe: 80002.0F;      // 8 Tonnen = 80.000 N                                    
 
        //-------------------------------------------------------------------------        
          // Beim Anfahren muss eine Mindestkraft vorgegeben werden! 
          // Liegt bei Kraftregelung die Soll-Walzkraft unter diesem Wert, dann 
          // kann u.U. die Kraft nicht ausreichend sein, dass der Radialschlitten
          // positioniert werden kann. Hierdurch wird die Position nicht erreicht
          // und das Programm kann nicht in die nachfolgende case-Anweisung springen
          if(Soll_IBF->RS_Kraft <= 79999.0F ) Soll_IBF->RS_Kraft = 80003.0F; 
     }

    void Anwalzen_Axial(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF) 
     {
           // Druckvorgabe für das Anwalzen unter Berücksichtigung der Vorschubs-; Kraftsteuerung
        
        //Los geht´s
        
        rs_aso_mode(Ist_IBF, &*Soll_IBF, 1);

        // Abfrage ob Schalter Kraftregler gesetz ist, wenn JA, dann wird vorgegeben Kraft verwendet, sonst DEFAULT-Zahlenwert [N]
        Soll_IBF->RS_Kraft  = Ist_IBF.Flag.rs_kraftregler_aktiv  ? Soll_IBF->RS_Kraft_Vorgabe  :  100002.0F;   // 10 Tonnen = 100.000 N                                      
        Soll_IBF->AG_Kraft  = Ist_IBF.Flag.ag_kraftregler_aktiv  ? Soll_IBF->AG_Kraft_Vorgabe  :  10002.0F ;   //  1 Tonne  =  10.000 N
        Soll_IBF->ZAR_Kraft = Ist_IBF.Flag.zal_kraftregler_aktiv ? Soll_IBF->ZAL_Kraft_Vorgabe :  10002.0F ;   //  1 Tonne  =  10.000 N
        Soll_IBF->ZAL_Kraft = Ist_IBF.Flag.zar_kraftregler_aktiv ? Soll_IBF->ZAR_Kraft_Vorgabe :  10002.0F ;   //  1 Tonne  =  10.000 N
 

        if (Ist_IBF.Flag.as_kraftanfahren_aktiv == 1) // Schalter: Walzen mit Kraftsteuerung 'AN' 
         {
           Soll_IBF->AS_Kraft = Ist_IBF.Flag.as_kraftanfahren_aktiv ? Soll_IBF->AS_Kraft_Anfahren : 2000.0F ;
          }
        else
           Axialkraft(Ist_IBF, &*Soll_IBF); 
           
     }
    

    
     /* Axialgerüststeuerung */

     void IBF_Abschaltung(struct Def_Soll_Inter *Soll_Inter,struct Def_IBF_Allgemein_IST Ist_IBF)
     {
        // Funktion mit der das automatische Öffnen nach erreichen des Abschaltmases realisiert werden soll
        // Funktionier deszeit noch nicht 24.07.07 D.Michl

        // Los geht´s
         if(Ist_IBF.Flag.ag_kraftregler_aktiv) // Vorschubregelung, Abschaltmaß erreicht, AG schließt auf SMS-Position
             {
             Soll_Inter->ag_mode = 0x02; 
             Soll_Inter->ag_act  = 0x02;
             }
         else
            { 
            Soll_Inter->ag_mode = 0x03;         // Kraftregelung, Abschaltmaß erreicht, AG schließt auf SMS-Position   
            Soll_Inter->ag_act  = 0x02;
            }
     }  

     
     int RPW::Modus_AG(struct Def_Soll_Inter *Soll_Inter, struct Def_IBF_Allgemein_IST *Ist_IBF, int Auswahl)
     {
        // Funktion mit der die richtigen Bits des Axialgerüstmodus eingestellt werden 

        // Los geht´s

        //Setzen des SMS-Flag Sollwert/Abschaltung Axialgerüst
        if(Ist_IBF->Flag.IBF_Abschaltung == 1 && Ist_IBF->Flag.Axial_Radialwalzen == 0)
            {
            Soll_Inter->ag_act = 0x03; //3=0x03= 0000 0011 (Bit0=1 IBF übernimmt Regelung AG, Bit1=1 IBF übernimmt Anschaltung
            }
         else if(Ist_IBF->Flag.IBF_Abschaltung == 1 && Ist_IBF->Flag.Axial_Radialwalzen == 1)
            {
            Soll_Inter->ag_act = 0x01; // 0000 0010 (Bit0=0 SMS übernimmt Regelung AG, Bit1=1 IBF übernimmt Anschaltung
            }
        else Soll_Inter->ag_act = 0x00; // 0000 0000 (Bit0=0 SMS übernimmt Regelung AG, Bit1=1 SMS übernimmt Anschaltung
     
        //Setzen der Betriebsart des Axialgerüstes
        if(!Ist_IBF->Flag.ag_kraftregler_aktiv)  //Wenn FLAG = 0 ist -> Vorschubregelung gewählt (IBF_Para.ini, Defaultwert = 0)
        switch(Auswahl) 
        { 
        case 0: //Axialprofilieren: Vorschubregelung-IBF (Bit0=0), Abschaltung nicht erreicht (Bit1=0), beim Schließen/Anfahren wird eine IBF-Position verwendet (Bit2=1) (allerdings ist bereits geschlossen, wenn Funktion aufgerufen wird)
                Soll_Inter->ag_mode = 0x04; // 0000 0100 
                break;
        case 1: //Radialprofilieren: Vorschubregelung-IBF (Bit0=0), Abschaltmaß nicht erreicht (Bit1=0), beim Schließen/Anfahren wird die SMS-Position verwendet (Bit2=0) (allerdings ist bereits geschlossen, wenn Funktion aufgerufen wird)
                Soll_Inter->ag_mode = 0x02; // 0000 0000
                break;

        default: break;
        }
        else switch(Auswahl)
        {
        
        case 0: //Axialprofilieren: Kraftregelung-IBF (Bit0=1), Abschaltung nicht erreicht (Bit1=0), beim Schließen/Anfahren wird eine IBF-Position verwendet (Bit2=1)
                Soll_Inter->ag_mode = 0x05; // 0000 0101
                break;
        case 1: //Radialprofilieren: Kraftregelung-IBF, Abschaltmaß nicht erreicht, beim Schließen/Anfahren wird die SMS-Position verwendet (Bit2=0)
                Soll_Inter->ag_mode = 0x01; // 0000 0001 
                break;
        }
        
        return TRUE;

    }
    
    /*--------------------------------------------------------------------------------------*/
    /*                                                                                      */
    /*                  Funktionen für Programmmodul Radialprofilieren                      */
    /*                                                                                      */
    /*--------------------------------------------------------------------------------------*/

    
    /* Berechnung der notwendigen Axialschlittenposition beim radial flexiblen Profilieren */

    void Breitungsexp(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {

        Soll_IBF->Radial.Breitung.qf = Ist_IBF.Radial.s_f / Ist_IBF.Radial.Werkzeugbreite ; /* Verhältnis Wanddicke - Werkzeugbreite */
        Soll_IBF->Radial.Breitung.ga = Ist_IBF.Radial.s_f / Soll_IBF->Radial.Rohlinghoehe;  /* Verhältnis Wanddicke - Rohlingshöhe   */
        
        //Breitungsexponent 
        Soll_IBF->Radial.Breitung.mr = -0.00954F + 0.03397F * Soll_IBF->Radial.Walzspalt_Cr + 0.00253 * Soll_IBF->Radial.Breitung.qf + 0.1556 * Soll_IBF->Radial.Breitung.ga;
        Soll_IBF->Radial.Breitung.e_mr = pow(Euler, -1*(Ist_IBF.Radial.Breitung.mr));
    }
    
    void Durchme_t2(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        /*Durchmesser zum nachfolgenden Zeitpunkt t+1 */
        Soll_IBF->Radial.Breitung.Da_t2 = Ist_IBF.Radial.s_f + (pow(Ist_Inter.da, 2) - pow(Ist_Inter.di,2))* Soll_IBF->Radial.Breitung.e_mr / 4 * Ist_IBF.Radial.s_f;
        Soll_IBF->Radial.Breitung.Da_t2_h2 = pow(Soll_IBF->Radial.Breitung.Da_t2,2);
        
        //Achtung diese Funktion muss ausgeführt werden, nachdem die Sollwanddicke bestimmt worden ist, da diese jetzt benötigt wird
        Soll_IBF->Radial.Breitung.Di_t2 = Soll_IBF->Radial.Breitung.Da_t2 - 2* Soll_IBF->Radial.Soll_Wanddicke; 
        Soll_IBF->Radial.Breitung.Di_t2_h2 = pow(Soll_IBF->Radial.Breitung.Di_t2,2);
    }

    void Volumenbestimmung(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        /* Volumen der Kontaktzone */
        Soll_IBF->Radial.Breitung.Volumen_t1 = PI/4 * Ist_IBF.Radial.Werkzeugbreite *(  Soll_IBF->Radial.Breitung.Da_t2_h2 
                                                                                      - Soll_IBF->Radial.Breitung.Di_t2_h2
                                                                                     );

        /* Volumen der Kontaktzone zum nachfolgenden Zeitpunkt*/
        Soll_IBF->Radial.Breitung.Volumen_t2 = Soll_IBF->Radial.Breitung.Volumen_t1 * Soll_IBF->Radial.Breitung.e_mr;

        /* verdrängtes Volumen*/
        Soll_IBF->Radial.Breitung.Volumen_diff = Soll_IBF->Radial.Breitung.Volumen_t1 - Soll_IBF->Radial.Breitung.Volumen_t2;
    }
    
    void Hoehenzunahme(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        /* Funktionsaufruf: Berechung des Breitungsexponentes */    
        Breitungsexp(Ist_IBF, Soll_IBF);
        /* Funktionsaufruf: Berechnung des zukünftigen Durchmesser*/
        Durchme_t2(Ist_Inter,Ist_IBF,Soll_IBF);
        /* Funktionsaufruf: Berechnung der Volumendifferenz */
        Volumenbestimmung(Ist_IBF,Soll_IBF);

        /* Berechnung des Delta_h*/
        Soll_IBF->Radial.Breitung.delta_h = 12 * Soll_IBF->Radial.Breitung.Volumen_diff / ( PI * (
                                                                                                    ( Soll_IBF->Radial.Breitung.Da_t2_h2 
                                                                                                    + Soll_IBF->Radial.Breitung.Da_t2 * Ist_Inter.da
                                                                                                    + pow(Ist_Inter.da, 2)
                                                                                                    )
                                                                                                   -
                                                                                                    ( Soll_IBF->Radial.Breitung.Di_t2_h2 
                                                                                                    + Soll_IBF->Radial.Breitung.Di_t2 * Ist_Inter.di
                                                                                                    + pow(Ist_Inter.di, 2)
                                                                                                    )
                                                                                                 )

                                                                                           ); //Ende Rechnung                                                                                                 
    } // Ende Funktion


    /*--------------------------------------------------------------------------------------*/
    /*                                                                                      */
    /*                  Funktionen für Programmmodul Axialprofilieren                       */
    /*                                                                                      */
    /*--------------------------------------------------------------------------------------*/
    
    int RPW::Kr_Geo_berechnen(struct Def_IBF_Allgemein_IST *Ist_IBF)
    {
        // Funktion zur Berechnung benötigter Kragenwalzengeometrien, Vorgegeben wird Vordere Durchmesser Kragenwalze, Kragenbreite

        // Los geht´s

        //Abstand Vorderkante Kragenwalze-theoretische Spitze
        Ist_IBF->Axial.Kr_geo.Del_Kr_AGR = Ist_IBF->Axial.Kr_geo.Kr_d_nenn_vorne / (2*Ist_IBF->Axial.Kr_geo.sin_kw_winkel_halbe); 
        
        //Kragendurchmesser an Kragenmittelpunkt
        Ist_IBF->Axial.Kr_geo.Kr_d_nenn_mitte = 2* Ist_IBF->Axial.Kr_geo.sin_kw_winkel_halbe *(Ist_IBF->Axial.Kr_geo.Del_Kr_AGR 
                                                                                            + Ist_IBF->Axial.Kr_geo.Kr_Br/2 );
        
        return TRUE;
    }

    int RPW::Kr_Geo_pruefen(struct Def_IBF_Allgemein_IST *Ist_IBF)
    {
        // Überprüfen der vorgegeben Kragengeometrie, Abstand zwischen reellen KW-Spitze und Ansatzpunkt des Kragens muss am RAW gemessen werden können

        // Los geht´s
        Ist_IBF->Axial.Kr_geo.l_mantel_ukw_o_fehlende_spitze = (Ist_IBF->Axial.Kr_geo.Kr_d_nenn_vorne/2)/Ist_IBF->Axial.Kr_geo.sin_kw_winkel_halbe - Ist_IBF->Axial.Kr_geo.l_fehlende_spitze_ukw;
        return TRUE;
    }

    

    int AGR_Pr_Wanddicken_Verhaeltnis_proz(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        // Bestimmen des Verhältnis Wanddicke/Profilierposition

        // Los geht´s

        Soll_IBF->Axial.Verh_pr_sf_proz_start = (Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num]/Ist_IBF.Vorring.Wandstaerke_Null) * 100.0F; // Verhältnis bei Walzstart
        Soll_IBF->Axial.Verh_pr_sf_proz       = (Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num]/Ist_Inter.s0a) * 100.0F;                    // Verhältnis während Walzung
        return TRUE;
    }


    char AGR_Nachfuehr_Entscheider(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        // Zunächst wird die Entscheidung zu Programmbeginn anahnd der Vorformwanddicke und SOll-Profilierposition getroffen, 
        // später ist Wechsel im Programm ggf. sinnvoll 24.07.07 D.Michl

        // Los geht´s
        char Wert;
        
        AGR_Pr_Wanddicken_Verhaeltnis_proz(Ist_Inter, Ist_IBF, &*Soll_IBF);
        //Ist_IBF.Axial.Verh_pr_sf_proz_start = Soll_IBF->Axial.Verh_pr_sf_proz_start;
        //Ist_IBF.Axial.Verh_pr_sf_proz = Soll_IBF->Axial.Verh_pr_sf_proz;

        if(Soll_IBF->Axial.Verh_pr_sf_proz <= 60.0F) //Proflposition befindet sich vom äußeren Randbereich auf min. 60% der Wanddicke
            {
                Soll_IBF->Axial.Wert = 'A';
                Wert = 'A';
            }
        else if(Soll_IBF->Axial.Verh_pr_sf_proz > 60.0F) //Proflposition befindet sich vom äußeren Randbereich über 60% der Wanddicke
            {
                Soll_IBF->Axial.Wert = 'I';
                Wert = 'I';
            }

        return Wert;
    }

    
    float AGR_Soll_Pos(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        // Funktion zum Bestimmen der Axialgerüstposition, 
        // insbesondere beim Axialprofilieren in Abhängigkeit der Nachführung "Anhand Außendurchmesser" oder "Anhand Innendurchmesser"

        // Los geht´s
        float AG_Position;

        // Wird anhand des Außendurchmessers positioniert ?
        if(AGR_Nachfuehr_Entscheider(Ist_Inter, Ist_IBF, &*Soll_IBF)== 'A')
            {
             AG_Position      =   Ist_Inter.da 
                                - Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num] 
                                - Ist_IBF.Axial.Kr_geo.Kr_Br 
                                - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
                                + Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw;  
            }
        // oder doch eher anhand des Innendurchmessers ? 
        else if(AGR_Nachfuehr_Entscheider(Ist_Inter, Ist_IBF, &*Soll_IBF)== 'I')
            {
             AG_Position      =   Ist_Inter.da 
                                - Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num] 
                                - Ist_IBF.Axial.Kr_geo.Kr_Br 
                                - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
                                + Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw; 

/*             AG_Position      =   Ist_Inter.s0r 
                                + Ist_Inter.di 
                                + Ist_Inter.s0a 
                                - Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num]
                                - Ist_IBF.Axial.Kr_geo.Kr_Br 
                                - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR
                                + Ist_IBF.Axial.Kr_geo.l_fehlende_spitze_ukw; 
*/
             }
        return AG_Position;
    }
   
    /*--------------------------------------------------------------------------------------*/
    /*                                                                                      */
    /*                  Funktionen für Programmmodul Einlesen der IBF-INI-Datei              */
    /*                                                                                      */
    /*--------------------------------------------------------------------------------------*/

    


    int RPW::IBFPARA_auslesen(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
                //los geht´s
                 CIniFile iniFile( "IBF_Data.ini");
         if(!iniFile.ReadFile()) //Fehlerbehandlung
           { 
            return 0;
            
           }
         else 
           {
                     
            
            //Einlesen der Schlüsselidentifikation
            iniFile.NumValues( "IBF_Wahlschalter Axialprofilieren(0) Radialprofilieren(1)"); 
            Ist_IBF->Flag.Axial_Radialwalzen  = iniFile.GetValueI( "IBF_Wahlschalter Axialprofilieren(0) Radialprofilieren(1)", "Axial- / Radialprofilieren", 0);
            
            iniFile.NumValues( "IBF_Wahlschalter Abschalten: SMS-Vorgabe (0) IBF-Vorgabe (1)"); 
            Ist_IBF->Flag.IBF_Abschaltung  = iniFile.GetValueI( "IBF_Wahlschalter Abschalten: SMS-Vorgabe (0) IBF-Vorgabe (1)", "Abschalten SMS(0) IBF(1)", 0);
            
          //Einlesen der Schlüsselidentifikation
            iniFile.NumValues( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)"); 
            //Einlesen der Werte unterhalb der Schlüssel-ID, wenn Wert nicht vorhanden wird der DEFAULT-Wert verwendet
            Ist_IBF->Flag.rs_kraftregler_aktiv  = iniFile.GetValueI( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)", "Schalter_RS_Kraft_Weg", 0);
            Ist_IBF->Flag.as_kraftregler_aktiv  = iniFile.GetValueI( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)", "Schalter_AS_Kraft_Weg", 0);
            Ist_IBF->Flag.ag_kraftregler_aktiv  = iniFile.GetValueI( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)", "Schalter_AG_Kraft_Weg", 0);
            Ist_IBF->Flag.zal_kraftregler_aktiv = iniFile.GetValueI( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)", "Schalter_ZAL_Kraft_Weg", 0);
            Ist_IBF->Flag.zar_kraftregler_aktiv = iniFile.GetValueI( "IBF_Wahlschalter Kraftsteuerung(0) Wegsteuerung(1)", "Schalter_ZAR_Kraft_Weg", 0);
 
            iniFile.NumValues( "IBF_Vorgabe Kraft"); 
            Soll_IBF->RS_Kraft_Vorgabe  = iniFile.GetValueF( "IBF_Vorgabe Kraft", "RS_Kraftvorgabe", 80000.0); //8   Tonnen = 80.000 N
            Soll_IBF->AS_Kraft_Vorgabe  = iniFile.GetValueF( "IBF_Vorgabe Kraft", "AS_Kraftvorgabe", 60000.0); //6   Tonnen = 60.000 N
            Soll_IBF->AG_Kraft_Vorgabe  = iniFile.GetValueF( "IBF_Vorgabe Kraft", "AG_Kraftvorgabe", 5000.0);  //0.5 Tonnen =  5.000 N
            Soll_IBF->ZAL_Kraft_Vorgabe = iniFile.GetValueF( "IBF_Vorgabe Kraft", "ZAL_Kraftvorgabe", 2000.0);
            Soll_IBF->ZAR_Kraft_Vorgabe = iniFile.GetValueF( "IBF_Vorgabe Kraft", "ZAR_Kraftvorgabe", 2000.0);

            iniFile.NumValues( "IBF_Wahlschalter Anwalzen in Kraft"); 
            Ist_IBF->Flag.rs_kraftanfahren_aktiv = iniFile.GetValueI( "IBF_Wahlschalter Anwalzen in Kraft", "Schalter_Wanddicke", 0);
            Ist_IBF->Flag.as_kraftanfahren_aktiv = iniFile.GetValueI( "IBF_Wahlschalter Anwalzen in Kraft", "Schalter_Ringhoehe", 0);
           
            iniFile.NumValues( "IBF_Vorgabe Anwalzkraft"); 
            Soll_IBF->RS_Kraft_Anfahren = iniFile.GetValueF( "IBF_Vorgabe Anwalzkraft", "RS_Kraft_Anfahren", 1000.0);
            Soll_IBF->AS_Kraft_Anfahren = iniFile.GetValueF( "IBF_Vorgabe Anwalzkraft", "AS_Kraft_Anfahren", 10000.0);

            iniFile.NumValues ("IBF-Variablen Radialprofilieren");
            Ist_IBF->Radial.Schalter_Kont_DisKo = iniFile.GetValueI( "IBF-Variablen Radialprofilieren", "Vorschubsart (0->const_Vorschub 1->Epsilon/Weg 2->mit Walzspaltverhältnis Cr)", 0);
            Ist_IBF->Radial.Werkzeugbreite      = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Profilierwerkzeugbreite", 10.0);   
            Soll_IBF->Radial.Vorschubgeschw_Dw  = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "const.Vorschubgeschwindigkeit", 0.0);   
            Soll_IBF->Radial.Stegstaerke        = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Endstegstaerke", 0.0);
            Soll_IBF->Radial.delta_s            = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "delta_s", 0.0);
            Soll_IBF->Radial.Umdrehungen        = iniFile.GetValueI( "IBF-Variablen Radialprofilieren", "Umdrehungen in Rundungsphase", 0);
            Soll_IBF->Radial.eps_Vorschub       = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Espilon für Auswahl 'Epsilon/Weg'", 0);
            Soll_IBF->Radial.Walzspalt_Cr       = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Walzspaltverhältnis Cr", 0);
            Soll_IBF->Radial.Rohlinghoehe       = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Rohlinghoehe", 100);
            Soll_IBF->Radial.Vorschubgeschw_ASO = iniFile.GetValueF( "IBF-Variablen Radialprofilieren", "Vorschubgeschw._ASO", 5.0);

            iniFile.NumValues ("IBF-Variablen Axialprofilieren Werkzeugdaten");
            Ist_IBF->Axial.Kr_geo.Kr_d_nenn_vorne = iniFile.GetValueF( "IBF-Variablen Axialprofilieren Werkzeugdaten", "Durchmesser vordere Kragenkante", 275.134);
            Ist_IBF->Axial.Kr_geo.Kr_Br           = iniFile.GetValueF( "IBF-Variablen Axialprofilieren Werkzeugdaten", "Kragenbreite", 50);
            Ist_IBF->Axial.Kr_geo.max_Pr_Tiefe    = iniFile.GetValueF( "IBF-Variablen Axialprofilieren Werkzeugdaten", "max. Profilierungstiefe", 45);

            iniFile.NumValues ("IBF-Variablen Axialprofilieren - Walzparameter");
            Ist_IBF->Axial.Anfahrdurchm           = iniFile.GetValueF( "IBF-Variablen Axialprofilieren - Walzparameter", "Start_Ringdurchmesser", 1500);
            Ist_IBF->Axial.Profilanzahl           = iniFile.GetValueI( "IBF-Variablen Axialprofilieren - Walzparameter", "Anzahl der zu walzenden Profile", 1);
            Soll_IBF->Axial.Umdrehungen           = iniFile.GetValueI( "IBF-Variablen Radialprofilieren", "Umdrehungen in Rundungsphase", 0);
            Ist_IBF->Axial.Vorschub               = iniFile.GetValueF( "IBF-Variablen Axialprofilieren - Walzparameter", "Zustellgeschwindigkeit in mm/U", 3.125);
            Ist_IBF->Axial.AGR_Pr[0]              = iniFile.GetValueF( "IBF-Variablen Axialprofilieren - Walzparameter", "1. Profilposition von Außenrand", 0);
            Ist_IBF->Axial.Pr_Tiefe[0]            = iniFile.GetValueF( "IBF-Variablen Axialprofilieren - Walzparameter", "1. Profiltiefe", 0);
            Ist_IBF->Axial.AGR_Pr[1]              = iniFile.GetValueF( "IBF-Variablen Axialprofilieren - Walzparameter", "2. Profilposition von Außenrand", 0);
            Ist_IBF->Axial.Pr_Tiefe[1]            = iniFile.GetValueF( "IBF-Variablen Axialprofilieren - Walzparameter", "2. Profiltiefe", 0);
            Ist_IBF->Axial.AGR_Pr[2]              = iniFile.GetValueF( "IBF-Variablen Axialprofilieren - Walzparameter", "3. Profilposition von Außenrand", 0);
            Ist_IBF->Axial.Pr_Tiefe[2]            = iniFile.GetValueF( "IBF-Variablen Axialprofilieren - Walzparameter", "3. Profiltiege", 0);

            iniFile.NumValues ("IBF-Testwalzung - Walzparameter");                                         
            Ist_IBF->Test.Flag                    = iniFile.GetValueI( "IBF-Testwalzung - Walzparameter", "Testfahrt (0->Nein 1->Ja)", 0);
            Ist_IBF->Test.Ring_AD                 = iniFile.GetValueF( "IBF-Testwalzung - Walzparameter", "Test_Ringdurchmesser", 1500);
            
            
            
             return 1;
          }        

               
         
    } //Ende der Funktion




   
     /* weitere Funktionen */

/*
     

    void AG_Steuerung(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_Soll_Inter &Soll_Inter)
    {
     
        if(Ist_IBF.Flag.ag_kraftregler_aktiv == TRUE)
        { 
            Soll_Inter->ag_mode & 1 = 2; // Bit 0 = 1 -> Kraftregler aktiv. In der *.ini-Datei muss Kraftregler aktiviert worden sein
        }
       // else 
      //      Soll_Inter.ag_mode & 1 = 1; // Bit 0= 0 -> Vorschubsregelung

    }
    
*/
                 



