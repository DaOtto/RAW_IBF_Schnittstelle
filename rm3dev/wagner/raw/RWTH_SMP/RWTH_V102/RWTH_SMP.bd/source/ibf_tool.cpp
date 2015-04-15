#include "rpw.hpp"
#include "iniFile.h"




    /*-----------------------------------------------------------------------*/
    /*                                                                       */
    /*                          IBF Funktionen                               */
    /*                                                                       */
    /*-----------------------------------------------------------------------*/

    /* Drehzahlen */

    float KW_Drehzahl_oben(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF)
    {
        float diam_hw =751.0F;
    //return(Ist_Inter.kw_ia/Ist_Inter.hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*Ist_Inter.sin_kw_winkel_halbe));
    return 1;
    }

    
    float KW_Drehzahl_unten(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF)
    {
        float diam_hw=751.0F;
     //   return(Ist_Inter.kw_ia/Ist_Inter.hw_ir * (diam_hw * Ist_Inter.hw_n/2.0F)/((Ist_IBF->Del_Kr_AGR + Ist_IBF->Pos_auf_Mantel)*Ist_Inter.sin_kw_winkel_halbe));
         return 1;
    }


    /* Kraftsteuereung */

    void Kraftsteuerung(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        // Kraftvorgabe aus Carwin bezgl. DW-Durchmesser einbinden, um Dorndurchbiegung nicht zu vernachlässigen   
                
        Soll_IBF->RS_Kraft  = Ist_IBF->Flag.rs_kraftregler_aktiv  ? Soll_IBF->RS_Kraft_Vorgabe  : 500000.0F ;   // 1 T = 10.000 N
        Soll_IBF->AS_Kraft  = Ist_IBF->Flag.as_kraftregler_aktiv  ? Soll_IBF->AS_Kraft_Vorgabe  :  80000.0F ;   
        Soll_IBF->AG_Kraft  = Ist_IBF->Flag.ag_kraftregler_aktiv  ? Soll_IBF->AG_Kraft_Vorgabe  :  10000.0F ; 
        Soll_IBF->ZAR_Kraft = Ist_IBF->Flag.zal_kraftregler_aktiv ? Soll_IBF->ZAL_Kraft_Vorgabe :  10000.0F ; 
        Soll_IBF->ZAL_Kraft = Ist_IBF->Flag.zar_kraftregler_aktiv ? Soll_IBF->ZAR_Kraft_Vorgabe :  10000.0F ;
    }

    void Anwalzen_Radial(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF) 
     {

        Soll_IBF->AS_Kraft  = Ist_IBF->Flag.as_kraftregler_aktiv  ? Soll_IBF->AS_Kraft_Vorgabe  :  80000.0F ; 
        Soll_IBF->AG_Kraft  = Ist_IBF->Flag.ag_kraftregler_aktiv  ? Soll_IBF->AG_Kraft_Vorgabe  :  10000.0F ; 
        Soll_IBF->ZAR_Kraft = Ist_IBF->Flag.zal_kraftregler_aktiv ? Soll_IBF->ZAL_Kraft_Vorgabe :  10000.0F ; 
        Soll_IBF->ZAL_Kraft = Ist_IBF->Flag.zar_kraftregler_aktiv ? Soll_IBF->ZAR_Kraft_Vorgabe :  10000.0F ;
 

        if (Ist_IBF->Flag.rs_kraftanfahren_aktiv == 1) // Schalter: Walzen mit Kraftsteuerung 'AN' 
         {
           Soll_IBF->RS_Kraft = Ist_IBF->Flag.rs_kraftanfahren_aktiv ? Soll_IBF->RS_Kraft_Anfahren : 100000.0F ;
         }
        else
           Soll_IBF->RS_Kraft = Ist_IBF->Flag.rs_kraftregler_aktiv ? Soll_IBF->RS_Kraft_Vorgabe: 100000.0F;                                         
     }

    void Anwalzen_Axial(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF) 
     {
    
        Soll_IBF->RS_Kraft  = Ist_IBF->Flag.rs_kraftregler_aktiv  ? Soll_IBF->RS_Kraft_Vorgabe  : 100000.0F;                                         
        Soll_IBF->AG_Kraft  = Ist_IBF->Flag.ag_kraftregler_aktiv  ? Soll_IBF->AG_Kraft_Vorgabe  :  10000.0F ; 
        Soll_IBF->ZAR_Kraft = Ist_IBF->Flag.zal_kraftregler_aktiv ? Soll_IBF->ZAL_Kraft_Vorgabe :  10000.0F ; 
        Soll_IBF->ZAL_Kraft = Ist_IBF->Flag.zar_kraftregler_aktiv ? Soll_IBF->ZAR_Kraft_Vorgabe :  10000.0F ;
 

        if (Ist_IBF->Flag.as_kraftanfahren_aktiv == 1) // Schalter: Walzen mit Kraftsteuerung 'AN' 
         {
           Soll_IBF->RS_Kraft = Ist_IBF->Flag.as_kraftanfahren_aktiv ? Soll_IBF->AS_Kraft_Anfahren : 80000.0F ;
           Ist_IBF->Flag.as_kraftregler_aktiv = Ist_IBF->Flag.as_kraftanfahren_aktiv;
         }
        else
        Soll_IBF->AS_Kraft  = Ist_IBF->Flag.as_kraftregler_aktiv  ? Soll_IBF->AS_Kraft_Vorgabe  :  80000.0F ; 
           
     }
    

    
     /* Axialgerüststeuerung */
     
     void Abschaltung(struct Def_IBF_Allgemein_SOLL *Soll_IBF)
     {
        /* Abschaltmass ist ereicht und die Maschine öffnet sich */
         Soll_IBF->Flag.ag_mode = 2; //Abschaltmass erreicht wenn Bit 1 = 1 s.a. 'SMS-Mitteilung Schnittstelle'
         Soll_IBF->Flag.ag_act  = 2; //IBF übernimmt die Abschaltung wenn Bit 1 = 1 ('0000 0010' -> Wert = 2), 's.a. SMS-Mitteilung Schittstelle'
     }    
 
     void Modus_AG(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF, char Auswahl)
     {
     
        if(!Ist_IBF.Flag.ag_kraftregler_aktiv)  //Wenn Schalter = 0 (Vorschubregelung aus IBF_Para.ini, Default = 0)
        switch(Auswahl) 
        { 
        case 1: //Vorschubregelung, Abschaltung nicht erreicht, beim Schließen wird eine IBF-Position verwendet (allerdings ist bereits geschlossen, wenn Funktion aufgerufen wird)
                Soll_IBF->Flag.ag_mode = 4; 
                break;
        case 2: //Vorschubregelung, Abschaltmaß nicht erreicht, beim Schließen wird die SMS-Position verwendet (allerdings ist bereits geschlossen, wenn Funktion aufgerufen wird)
                Soll_IBF->Flag.ag_mode = 0; 
                break;
        case 3: //Vorschubregelung, Abschaltmaß erreicht, AG schließt auf SMS-Position
                Soll_IBF->Flag.ag_mode = 2; 
                break;
        }
        else switch(Auswahl)
        {
        
        case 1: //Kraftregelung, Abschaltung nicht erreicht, IBF-Position
                Soll_IBF->Flag.ag_mode = 5; 
                break;
        case 2: //Kraftregelung, Abschaltmaß nicht erreicht, AG schließt auf SMS-Position
                Soll_IBF->Flag.ag_mode = 1; 
                break;
        case 3: //Kraftregelung, Abschaltmaß nicht erreicht, AG schließt auf SMS-Position
                Soll_IBF->Flag.ag_mode = 3; 
                break;
        }

    }
    
    /* Berechnung der notwendigen Axialschlittenposition beim radial flexiblen Profilieren */

    void Breitungsexp(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {

        Ist_IBF->Radial.Breitung.qf = Ist_IBF->Radial.s_f / Ist_IBF->Radial.Werkzeugbreite ; /* Verhältnis Wanddicke - Werkzeugbreite */
        Ist_IBF->Radial.Breitung.ga = Ist_IBF->Radial.s_f / Soll_IBF->Radial.Rohlinghoehe;  /* Verhältnis Wanddicke - Rohlingshöhe   */
        
        //Breitungsexponent 
        Ist_IBF->Radial.Breitung.mr = -0.00954F + 0.03397F * Soll_IBF->Radial.Walzspalt_Cr + 0.00253 * Ist_IBF->Radial.Breitung.qf + 0.1556 * Ist_IBF->Radial.Breitung.ga;
        Ist_IBF->Radial.Breitung.e_mr = pow(Euler, -1*(Ist_IBF->Radial.Breitung.mr));
    }
    
    void Durchme_t2(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        /*Durchmesser zum nachfolgenden (zukünftigen) Zeitpunkt */
        Ist_IBF->Radial.Breitung.Da_t2 = Ist_IBF->Radial.s_f + (pow(Ist_Inter.da, 2) - pow(Ist_Inter.di,2))* Ist_IBF->Radial.Breitung.e_mr / 4 * Ist_IBF->Radial.s_f;
        Ist_IBF->Radial.Breitung.Da_t2_h2 = pow(Ist_IBF->Radial.Breitung.Da_t2,2);
        
        //Achtung diese Funktion muss ausgeführt werden, nachdem die Sollwanddicke bestimmt worden ist, da diese jetzt benötigt wird
        Ist_IBF->Radial.Breitung.Di_t2 = Ist_IBF->Radial.Breitung.Da_t2 - 2* Soll_IBF->Radial.Soll_Wanddicke; 
        Ist_IBF->Radial.Breitung.Di_t2_h2 = pow(Ist_IBF->Radial.Breitung.Di_t2,2);
    }

    void Volumenbestimmung(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        /* Volumen der Kontaktzone */
        Ist_IBF->Radial.Breitung.Volumen_t1 = PI/4 * Ist_IBF->Radial.Werkzeugbreite *(  Ist_IBF->Radial.Breitung.Da_t2_h2 
                                                                                      - Ist_IBF->Radial.Breitung.Di_t2_h2
                                                                                     );

        /* Volumen der Kontaktzone zum nachfolgenden Zeitpunkt*/
        Ist_IBF->Radial.Breitung.Volumen_t2 = Ist_IBF->Radial.Breitung.Volumen_t1 * Ist_IBF->Radial.Breitung.e_mr;

        /* verdrängtes Volumen*/
        Ist_IBF->Radial.Breitung.Volumen_diff = Ist_IBF->Radial.Breitung.Volumen_t1 - Ist_IBF->Radial.Breitung.Volumen_t2;
    }
    
    void Hoehenzunahme(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
    {
        /* Funktionsaufruf: Berechung des Breitungsexponentes */    
        Breitungsexp(Ist_IBF, Soll_IBF);
        /* Funktionsaufruf: Berechnung des zukünftigen Durchmesser*/
        Durchme_t2(Ist_Inter,Ist_IBF,Soll_IBF);
        /* Funktionsaufruf: Berechnung der Volumendifferenz */
        Volumenbestimmung(Ist_IBF,Soll_IBF);

        /* Berechnung des Delta_h*/
        Soll_IBF->Radial.Breitung.delta_h = 12 * Ist_IBF->Radial.Breitung.Volumen_diff / ( PI * (
                                                                                                    ( Ist_IBF->Radial.Breitung.Da_t2_h2 
                                                                                                    + Ist_IBF->Radial.Breitung.Da_t2 * Ist_Inter.da
                                                                                                    + pow(Ist_Inter.da, 2)
                                                                                                    )
                                                                                                   -
                                                                                                    ( Ist_IBF->Radial.Breitung.Di_t2_h2 
                                                                                                    + Ist_IBF->Radial.Breitung.Di_t2 * Ist_Inter.di
                                                                                                    + pow(Ist_Inter.di, 2)
                                                                                                    )
                                                                                                 )

                                                                                           ); //Ende Rechnung                                                                                                 
    } // Ende Funktion

    

    


    char IBFPARA_auslesen(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL Soll_IBF)
    {
            CIniFile iniFile( "IBF_Data.ini");

            //Einlesen der Sxhlüsselidentifikation
            iniFile.NumValues( "IBF_Wahlschalter_Kraft_Weg"); 
            //Einlesen der Werte unterhalb der Schlüssel-ID, wenn Wert nicht vorhanden wird DEFAULT-Wert verwendet
            Ist_IBF.Flag.rs_kraftregler_aktiv = iniFile.GetValueI( "IBF_Wahlschalter_Kraft_Weg", "Schalter_RS_Kraft_Weg", 0);
            Ist_IBF.Flag.as_kraftregler_aktiv = iniFile.GetValueI( "IBF_Wahlschalter_Kraft_Weg", "Schalter_AS_Kraft_Weg", 0);
            Ist_IBF.Flag.ag_kraftregler_aktiv = iniFile.GetValueI( "IBF_Wahlschalter_Kraft_Weg", "Schalter_AG_Kraft_Weg", 0);
            Ist_IBF.Flag.zal_kraftregler_aktiv = iniFile.GetValueI( "IBF_Wahlschalter_Kraft_Weg", "Schalter_ZAL_Kraft_Weg", 0);
            Ist_IBF.Flag.zar_kraftregler_aktiv = iniFile.GetValueI( "IBF_Wahlschalter_Kraft_Weg", "Schalter_ZAR_Kraft_Weg", 0);

            iniFile.NumValues( "IBF_Wahlschalter Anwalzen in Kraft"); 
            Ist_IBF.Flag.rs_kraftanfahren_aktiv = iniFile.GetValueI( "IBF_Wahlschalter Anwalzen in Kraft", "Schalter_Wanddicke", 0);
            Ist_IBF.Flag.as_kraftanfahren_aktiv = iniFile.GetValueI( "IBF_Wahlschalter Anwalzen in Kraft", "Schalter_Ringhoehe", 0);
            
            iniFile.NumValues( "IBF_Vorgabe Kraft"); 
            Soll_IBF.RS_Kraft_Vorgabe = iniFile.GetValueF( "IBF_Vorgabe Kraft", "RS_Kraftvorgabe", 80000.0);
            Soll_IBF.AS_Kraft_Vorgabe = iniFile.GetValueF( "IBF_Vorgabe Kraft", "AS_Kraftvorgabe", 60000.0);
            Soll_IBF.AG_Kraft_Vorgabe = iniFile.GetValueF( "IBF_Vorgabe Kraft", "AG_Kraftvorgabe", 5000.0);
            Soll_IBF.ZAL_Kraft_Vorgabe = iniFile.GetValueF( "IBF_Vorgabe Kraft", "ZAL_Kraftvorgabe", 2000.0);
            Soll_IBF.ZAR_Kraft_Vorgabe = iniFile.GetValueF( "IBF_Vorgabe Kraft", "ZAR_Kraftvorgabe", 2000.0);

            iniFile.NumValues( "IBF_Vorgabe Anwalzkraft"); 
            Soll_IBF.RS_Kraft_Anfahren = iniFile.GetValueF( "IBF_Vorgabe Anwalzkraft", "RS_Kraft_Anfahren", 1000.0);
            Soll_IBF.AS_Kraft_Anfahren = iniFile.GetValueF( "IBF_Vorgabe Anwalzkraft", "AS_Kraft_Anfahren", 1000.0);
            return 1;
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
                 



