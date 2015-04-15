/*--FILE HEADER---------------------------------------------------------------
;   filename        : ibf_flex_radial.cpp
;   version         : V1.02
;   contents        : IBF-Modul FLEXIBLE RADIAL PROFILING 
;   author          : D. MIchl, Institute of Metal Fotrming, RWTH-Aachen University
;   date            : Oct, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   calculaton of radial feed rate, 
;
;       RMOS3 Version 3.30
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   Oct , 10. 2006  0001  D.M.  original issue
;   Feb , 09. 2007  0002  D.M.  const. rollgap ratio   
;   Apr , 01. 2007  0003  D.M.  End of DFG-Project, preliminary discontinue 
;                               of programming 
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/
/****************************************************************************/
/*  includes                                                                */
/****************************************************************************/

#include "rpw.hpp"


/****************************************************************************/
/*  function                                                                 */
/****************************************************************************/



int RPW::flexibel_Radial(struct Def_Ist_Inter          Ist_Inter,
                          struct Def_IBF_Allgemein_IST  Ist_IBF, 
                          struct Def_Soll_Inter         *Soll_Inter,
                          struct Def_IBF_Allgemein_SOLL *Soll_IBF)
{
    // Programmmodul IBF-FLEXIBEL RADIAL PROFILIEREN
    // Funktion wird in der rpw.cpp-Datei unter RPW:Main aufgerufen, nachdem die Startpositionen angefahren sind

    // Los geht�s
    float eps = 1.0F;          // Positioniergenauigkeit michl:-> war 0.1F
   

    switch(Ist_IBF.Profilflag)
        {
         case 10:     // Vergleich der eingegebenen Wandst�rke und der, per Kraftsteuerung angefahrenen Wandst�rke
                     // Routine, ob Schalter gesetzt ist oder nicht -> Schalter (0,1,2)
                     
                     Soll_IBF->Soll_ASO_Pos_alt = Ist_IBF.ASO_Pos;    // F�r Berechnung der neuen ASO-H�he w�hrend der Walzung . Derzeit in case 11 & case 12 (konti & diskonti Vorschub) verwendet.
 

                     Ist_IBF.Radial.s_f_alt = Ist_IBF.Radial.s_f;   // dem Wert s_f_alt wird hier bereits der erste Wert vorgegeben, damit in case 11/12 keine Division durch NULL stattfindet.... 
                     
                     
                     if(Ist_IBF.Radial.Schalter_Kont_DisKo == 0)  // kontinuierlicher Vorschub
                        {
                            Soll_IBF->Profilflag = 11; 
                             //Ist_IBF.Radial.s_ist = 0;
                            break;
                         }
                     
                     if(Ist_IBF.Radial.Schalter_Kont_DisKo == 1) //diskontinuierlicher Vorschub (eps �ber Weg)
                        {
                            Soll_IBF->Profilflag = 12; 
                            Soll_IBF->RS_Pos = Ist_IBF.RS_Pos - 0.5f;
                            break;
                        }
                     
                     if (Ist_IBF.Radial.Schalter_Kont_DisKo == 2) //f�r Ingos Cr-Vorschub
		   			   {
		   					Soll_IBF->Profilflag = 15; 
                            Soll_IBF->Radial.Cr.os_i = 0;    //erste Ringh�lfte 0, zweite 1

		   				   //Zeit f�r 2 Umdrehungen bei denen der Dorn in den Ring vorf�hrt bis Schnabel-Formel greift
                        	//Soll_IBF->Radial.t_dis_h = 2*(Ist_IBF.Vorring.D_Null/(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.Werkzeug.Frequenz_HW)); 
                            Soll_IBF->Radial.t_dis_h = Ist_IBF.Zeit.Ringumdrehung * 10.0;
		   				
                        	Ist_IBF.Zeit.Halbe_Ringumdrehung = Ist_IBF.Zeit.Ringumdrehung / 2; 

		   					Soll_IBF->RS_Pos = Ist_IBF.RS_Pos - 10.0F; /*Soll_RS_Pos = Afpos_dw - 1.0F*/ 
                            Soll_IBF->Zeit.t_Halte = 30; // 30*100 ms = 3000 ms -> 1s = 1000 ms
                            break;
                        } //Soll_RS_Pos damit er in case 15 einfach kontinuierlich(mit vorgegebener Geschw.) verf�hrt
		   					
                     
                     else
                     {
                        #ifdef MRAW
                           _settextposition(10,15);
                           printf("Fehler in Schalterstellung");
                        #endif
                     }
                     break;
                    
       
        case 11:      /* Walzungsroutine: const. Vorschub */
                     
                     /* Geschwindigkeiten  */
                     Soll_IBF->RS_V         = Soll_IBF->Radial.Vorschubgeschw_Dw;   // Vorschubgeschwindigkeit Dornwalze;
                     Soll_IBF->ASO_V        = 10.0F; 
                     //Soll_IBF->Soll_ASU_V   = 0.0F;
                     Soll_IBF->AG_V         = 10.0F;
                     Soll_IBF->ZAL_V        = 0.0F;
                     Soll_IBF->ZAR_V        = 0.0F;

                     /* Kr�fte */
                     Kraftsteuerung(Ist_IBF, Soll_IBF);   
  
                     /* Drehzahl */
                     //Soll_Inter->kwo_n = KW_Drehzahl_oben(Ist_Inter, &Ist_IBF);
                     //Soll_Inter->kwu_n = KW_Drehzahl_unten(Ist_Inter, &Ist_IBF);
                          
                     /*Position*/  
                     
                     if(Soll_IBF->Radial.Stegstaerke != 0)   // Abfrage ob Stegst�rke angegeben
                        {
                            //Soll_IBF->RS_Pos = (Ist_Inter.Werkzeug.Durchmeser_HW + Ist_Inter.Werkzeug.Durchmesser_DW)/2 + Soll_IBF->Radial.Stegstaerke;
                            Soll_IBF->RS_Pos = Soll_IBF->Radial.Stegstaerke;
                        }
                     else Soll_IBF->RS_Pos = Ist_IBF.Radial.Anfangsposition_DW - Soll_IBF->Radial.delta_s;  //Ist_IBF.Radial.Anfangsposition_DW wird in case 0 -> case 'a' gesetzt.....
                                                
                     

                     if(Ist_IBF.RS_Pos <= Soll_IBF->RS_Pos || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos + eps) || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos - eps))
                        {	
                            Soll_IBF->Zeit.t_Halte= Soll_IBF->Radial.Umdrehungen * 10 * (Ist_IBF.Vorring.D_Null/(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.hw_n)); // n Umdrehungen, 10 * "100" ms Aufrufzyklus = 1000 ms = 1s;  
                            
                            Soll_IBF->ASO_Pos = Ist_IBF.ASO_Pos; // damit kein Durck ausge�bt wird wenn Walzproze� beendet ist muss hier noch eine Konstante eingef�gt werden (z.B. 5)
                            
                            Soll_IBF->Profilflag = 2; 
                            break;
                        }                  
                     
                        //------------------------------------------------------------------------------------------------------
                        //----------------------- Positionssteuerung des oberen Axialschlittens --------------------------------
                        //------------------------------------------------------------------------------------------------------
                        
                        if(Soll_IBF->Radial.t_dis_h <=0)
                        {
                           // Berechnung der H�henabnahme f�r den n�chsten Zeitschritt nach der Formel:
                           // Delta_h = 10 mm Werkzeugbreite *gef.Wanddicke (diam_f)*(Wanddicke[n]^2-Wanddicke[n-1]^2)+Wanddicke[n-1]^2-Wanddike[n]^2/(Klammerausdruck)
                           Soll_IBF->Radial.delta_h = Ist_IBF.Radial.Werkzeugbreite *(Ist_Inter.da *   (Ist_IBF.Radial.s_f_alt - Ist_IBF.Radial.s_f)
                                                        - (Ist_IBF.Radial.s_f_alt*Ist_IBF.Radial.s_f_alt) 
                                                        + (Ist_IBF.Radial.s_f*Ist_IBF.Radial.s_f)
                                                        )/(Ist_Inter.da * Ist_IBF.Radial.s_f_alt - (Ist_IBF.Radial.s_f_alt*Ist_IBF.Radial.s_f_alt)); 
                           
                           
                           /* Positionen */
                           Soll_IBF->ASO_Pos = Soll_IBF->Soll_ASO_Pos_alt + Soll_IBF->Radial.delta_h;
                           
                           Soll_IBF->Soll_ASO_Pos_alt = Soll_IBF->ASO_Pos; 
 
                           Ist_IBF.Radial.s_f_alt = Ist_IBF.Radial.s_f;   
                           /* Zeit setzen */
                           Soll_IBF->Radial.t_dis_h = 10*(Ist_IBF.Vorring.D_Null/(Ist_Inter.Werkzeug.Durchmesser_HW*Ist_Inter.hw_n)); // 1 Umdrehungen (kein Wert vor der 10), 10*100 ms = 1000 ms = 1s
                        }        
                        
                        Soll_IBF->Radial.t_dis_h--;
                        
                        break;

           case 12:    /* Walroutine: diskontinuierlicher Vorschub (bezogen Wanddicke Epsilon �ber Weg) */
	   				    
                       /* Geschwindigkeiten  */
                        Soll_IBF->RS_V         = Soll_IBF->Radial.Vorschubgeschw_Dw;   // Vorschubgeschwindigkeit Dornwalze;
                        Soll_IBF->ASO_V        = 5.0F; 
                        //Soll_IBF->Soll_ASU_V   = 0.0F;
                        Soll_IBF->AG_V         = 10.0F;
                        Soll_IBF->ZAL_V        = 0.0F;
                        Soll_IBF->ZAR_V        = 0.0F;

                       /* Kr�fte */
                        Kraftsteuerung(Ist_IBF, Soll_IBF);   
  
                       /* Drehzahl */
                        //Soll_Inter->kwo_n = KW_Drehzahl_oben(Ist_Inter, &Ist_IBF);
                        //Soll_Inter->kwu_n = KW_Drehzahl_unten(Ist_Inter, &Ist_IBF);
                          
                       /*Position*/  
		
                       if(Soll_IBF->Radial.Stegstaerke != 0)   // Abfrage ob Stegst�rke angegeben wurde
                        {
                            //Soll_IBF->RS_Pos = (Ist_Inter.Werkzeug.Durchmeser_HW + Ist_Inter.Werkzeug.Durchmesser_DW)/2 + Soll_IBF->Radial.Stegstaerke;
                            Soll_IBF->RS_Pos_end = Soll_IBF->Radial.Stegstaerke;
                        }
                       else Soll_IBF->RS_Pos_end = Ist_IBF.Radial.Anfangsposition_DW - Soll_IBF->Radial.delta_s;  //Ist_IBF.Radial.Anfangsposition_DW wird in case 0 -> case 'a' gesetzt.....
                   
                  	 
                  	  //------------------------------------------------------------------------------------------------------
                  	  //-------------Routine bei der die neue RS-Pos bestimmt wird, dies in Abh�ngigkeit von eps -------------
                  	  //------------------------------------------------------------------------------------------------------
                  	  
                  	  
                  	  if((Soll_IBF->Radial.t_dis_h <= 0) && (Ist_IBF.RS_Pos == Soll_IBF->RS_Pos || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos + 0.1) /*|| RS_Pos >= (Soll_RS_Pos-0.01)*/))
                  	  { 
                  	   	
                  	   // DELTA S = abnahme_s ; s_f ist die gefilterte Wanddicke aus dem Interfac.h
                  	   Soll_IBF->Radial.abnahme_s = (Soll_IBF->Radial.eps_Vorschub/100) * Ist_IBF.Radial.s_f; // eps_Vorschub aus IBF_Data.ini
                  	                                            
                  	   Soll_IBF->RS_Pos = Ist_IBF.RS_Pos - Soll_IBF->Radial.abnahme_s;
                  	                     	 
                  	   // neue Zeit f�r n�chste Ringumdrehung. Bezieht sich allerdings auf den Anfangs-Ausgangsdurchmesser...
                  	   Soll_IBF->Radial.t_dis_h = 10*(Ist_IBF.Vorring.D_Null/(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.hw_n)); // 10*100 ms = 1000 ms = 1s
                  	   break;
                  	   }  
                  	                     	    
                  	   if(Ist_IBF.RS_Pos == Soll_IBF->RS_Pos || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos + 0.1) /*|| RS_Pos >= (Soll_RS_Pos-0.01)*/) 
                  	   {Soll_IBF->Radial.t_dis_h--;}

                       //------------------------------------------------------------------------------------------------------
                        //----------------------- Positionssteuerung des oberen Axialschlittens --------------------------------
                        //------------------------------------------------------------------------------------------------------
                        
                        if(Soll_IBF->Radial.t_dis_h <=0)
                        {
                           // Berechnung der H�henabnahme f�r den n�chsten Zeitschritt nach der Formel:
                           // Delta_h = 10 mm Werkzeugbreite *gef.Wanddicke (diam_f)*(Wanddicke[n]^2-Wanddicke[n-1]^2)+Wanddicke[n-1]^2-Wanddike[n]^2/(Klammerausdruck)
                           Soll_IBF->Radial.delta_h = Ist_IBF.Radial.Werkzeugbreite *(Ist_Inter.da *   (Ist_IBF.Radial.s_f_alt - Ist_IBF.Radial.s_f)
                                                        - (Ist_IBF.Radial.s_f_alt*Ist_IBF.Radial.s_f_alt) 
                                                        + (Ist_IBF.Radial.s_f*Ist_IBF.Radial.s_f)
                                                        )/(Ist_Inter.da * Ist_IBF.Radial.s_f_alt - (Ist_IBF.Radial.s_f_alt*Ist_IBF.Radial.s_f_alt)); 
                           
                           
                           Soll_IBF->ASO_Pos = Soll_IBF->Soll_ASO_Pos_alt + Soll_IBF->Radial.delta_h;
                           
                           Soll_IBF->Soll_ASO_Pos_alt = Soll_IBF->ASO_Pos;  
                           Ist_IBF.Radial.s_f_alt = Ist_IBF.Radial.s_f;   
                        }
                  	                     		
                  		//---------------------------------------------------------------------------------------------------
                  		//----------------------            Abbruchkriterium                           ----------------------
                  		//---------------------------------------------------------------------------------------------------
                  		      
                  				
						if(Ist_IBF.RS_Pos <= Soll_IBF->RS_Pos_end || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos_end + eps) || Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos_end - eps))
                  		 {	
                  			Soll_IBF->Zeit.t_Halte= Soll_IBF->Radial.Umdrehungen * 10 * (Ist_IBF.Vorring.D_Null/(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.hw_n)); // n Umdrehungen, 10 * "100" ms Aufrufzyklus = 1000 ms = 1s;  

           				    Soll_IBF->Profilflag=2; 
                  	
           					break;
                         }                  				
		   							   							
						
											
                  break;   

        

        case 15:     /* Walzroutine Cr-Vorschub. 1 Schritt Berechnung der Parameter f�r die erste Ringumdrehung, die in case 16 ben�tigt werden */
                          
        
                          Soll_IBF->Radial.Cr.a = Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.da;           // Hauptwalzendurch. * Au�endurchmesser
                          Soll_IBF->Radial.Cr.b = Ist_Inter.di * Ist_Inter.Werkzeug.Durchmesser_DW;           // Innendurchmesser(Durchmesser-2*Wandst�rke) * Dornwalze
	   				      Soll_IBF->Radial.Cr.c = Ist_Inter.Werkzeug.Durchmesser_HW + Ist_Inter.da;           // Hauptwalzemdurch. + Au�endurchmesser
	   				      Soll_IBF->Radial.Cr.d = Ist_Inter.di - Ist_Inter.Werkzeug.Durchmesser_DW;			  // Innendurchmesser - Dornwalze
	   				      Soll_IBF->Radial.Cr.e = pow(Soll_IBF->Radial.Walzspalt_Cr,2);                       // Cr * Cr
	   				    
	   				      Soll_IBF->Radial.Cr.o = (Soll_IBF->Radial.Cr.a/Soll_IBF->Radial.Cr.c) * (Soll_IBF->Radial.Cr.b/Soll_IBF->Radial.Cr.d);
	   				      Soll_IBF->Radial.Cr.u = (Soll_IBF->Radial.Cr.a/Soll_IBF->Radial.Cr.c) + (Soll_IBF->Radial.Cr.b/Soll_IBF->Radial.Cr.d); 
	   				    
	   				 		                  
		                  Soll_IBF->Radial.Cr.g = (Ist_IBF.Radial.s_f + 1/Soll_IBF->Radial.Cr.e * (Soll_IBF->Radial.Cr.o / Soll_IBF->Radial.Cr.u));     
		                  Soll_IBF->Radial.Cr.f = 2 * Soll_IBF->Radial.Cr.g;

		                  //abnahme_s = -2*g + ( sqrt( pow(f,2) - 4*pow(s_f,2)))
                          Soll_IBF->Radial.abnahme_s = -2*Soll_IBF->Radial.Cr.g + ( sqrt( pow(Soll_IBF->Radial.Cr.f,2) - 4*pow(Ist_IBF.Radial.s_f,2))); //Delta s mittels der momentanen Wanddicke berechnen
		                  
                          
                          if(Ist_IBF.Zeit.t_Halte <= 0)
                          {
		                  // Weil Zeitprobleme mit ausgestellter HW keine Vorschubgeschwi ergeben habenSoll_IBF->Radial.dw_vn = 2.0F; 
                          Soll_IBF->Radial.dw_vn = -1* Soll_IBF->Radial.abnahme_s /(Ist_IBF.Zeit.Ringumdrehung * 2);   //Dornvorschubgeschwindigkeit f�r case 15      
		                  Soll_IBF->Profilflag =  16;       
                          }
                          Soll_IBF->Zeit.t_Halte--;
		                  break;
        
        case 16:    /* Walzroutine Cr-Vorschub: 2. Schritt: Dorn in der ersten Ringumdrehung positionieren und ben�tigte Werte aufnehmen */
                    
                    /* Geschwindigkeiten  */
                        Soll_IBF->RS_V         = Soll_IBF->Radial.dw_vn;   /* Vorschubgeschw_DW erechnet in case 15 */
                        Soll_IBF->ASO_V        = 5.0F; 
                        //Soll_IBF->Soll_ASU_V   = 0.0F;
                        Soll_IBF->AG_V         = 10.0F;
                        Soll_IBF->ZAL_V        = 0.0F;
                        Soll_IBF->ZAR_V        = 0.0F;

                       /* Kr�fte */
                        Kraftsteuerung (Ist_IBF , Soll_IBF);   
  
                       /* Drehzahl */
                        //Soll_Inter->kwo_n = KW_Drehzahl_oben(Ist_Inter, &Ist_IBF);
                        //Soll_Inter->kwu_n = KW_Drehzahl_unten(Ist_Inter, &Ist_IBF);
                          
                       
     		                
		                		                 
		                //Wanddicke f�r 2 St�tzpunkte �ber Umfang aufzeichnen
		             
		                if ((Soll_IBF->Radial.Cr.os_i == 0) && (Soll_IBF->Radial.t_dis_h >= Ist_IBF.Zeit.Halbe_Ringumdrehung)) //Aufzeichnen des ersten St�tzpunkt, wenn erste St�tzstelle aufgezeichnet wird muss die Zeit gr�der als die halbe Umlaufzeit sein
		                  {
		                	 Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i] = Ist_IBF.Radial.s_f; // speicher die Wandst�rke im Feld [i]
		                			                	
		                	 if(Soll_IBF->Radial.Cr.os_i >= 1)      	   
		                	    {
                                 Soll_IBF->Radial.Cr.os_i = -1;
                                }
    
		                	 Soll_IBF->Radial.Cr.os_i = Soll_IBF->Radial.Cr.os_i + 1;
		                  }
		                	
		                else 
                        if((Soll_IBF->Radial.Cr.os_i ==1) && (Soll_IBF->Radial.t_dis_h <= Ist_IBF.Zeit.Halbe_Ringumdrehung)) //Aufzeichnen des zweiten St�tzpunktes
		                  {
		                	Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i] = Ist_IBF.Radial.s_f; // speicher die Wandst�rke im Feld [i]
		                	
                            if(Soll_IBF->Radial.Cr.os_i >=1)      //bei Array[2]	          
                              {
                               Soll_IBF->Radial.Cr.os_i = -1;
                              }  
  
		                	Soll_IBF->Radial.Cr.os_i= Soll_IBF->Radial.Cr.os_i + 1;
		                  }

                        /*Position*/  
		                           	   
                  	    if(Soll_IBF->Radial.t_dis_h <=0 )  //Zeit wird in case 1 definiert
                  	     { 
                  	        Soll_IBF->Profilflag = 17; 
                            Soll_IBF->Radial.Cr.os_i = 0;
                            Soll_IBF->Radial.t_dis_h = 0;
                            Ist_IBF.Zeit.Halbe_Ringumdrehung = Ist_IBF.Zeit.Ringumdrehung / 2;
                  	
	                        if(Soll_IBF->Radial.Stegstaerke != 0)   // Abfrage ob Stegst�rke angegeben wurde
                              {
                               Soll_IBF->RS_Pos_end = Soll_IBF->Radial.Stegstaerke;
                              }
                            else 
                            Soll_IBF->RS_Pos_end = Ist_IBF.Radial.Anfangsposition_DW - Soll_IBF->Radial.delta_s;  //Ist_IBF.Radial.Anfangsposition_DW wird in case 0 -> case 'a' gesetzt.....
                                                      	
                  	        break;
                        } 
                  	
                  	    Soll_IBF->Radial.t_dis_h--; // runterz�hlen der Zeit, die bei case 1 gesetzt wurde
                  	    break;

        case 17:    /* Walzroutine Cr-Vorschub: 3. Schritt: Dornposition f�r jede halbe Ringumdrehung neu vorgeben  */
                        
                        /* Geschwindigkeiten  */
                        Soll_IBF->RS_V         = Soll_IBF->Radial.Vorschubgeschw_Dw;   /* Vorschubgeschw_DW erechnet in case 15 */
                        Soll_IBF->ASO_V        = Soll_IBF->Radial.Vorschubgeschw_ASO; 
                        //Soll_IBF->Soll_ASU_V   = 0.0F;
                        Soll_IBF->AG_V         = 10.0F;
                        Soll_IBF->ZAL_V        = 0.0F;
                        Soll_IBF->ZAR_V        = 0.0F;


                        // f�r �berpr�fung im Logger
                        //Soll_IBF->Radial.dw_vn = Soll_IBF->RS_V;

                       /* Kr�fte */
                        Kraftsteuerung(Ist_IBF, Soll_IBF);   
  
                       /* Drehzahl */
                        // Soll_Inter->kwo_n = KW_Drehzahl_oben(Ist_Inter, &Ist_IBF);
                        // Soll_Inter->kwu_n = KW_Drehzahl_unten(Ist_Inter, &Ist_IBF);
                          
                       
	   				    //------------------------------------------------------------------------
	   				    //Delta_s anhand des const Walzspaltverh�ltnis cr
	   				    	   				    

	   				    if(Soll_IBF->Radial.t_dis_h <= Ist_IBF.Zeit.Halbe_Ringumdrehung) 
     	   				  {
	   				       
                           //Neue Zeiten f�r n�chsten Zyklus vorgeben....
		                   Ist_IBF.Zeit.Halbe_Ringumdrehung = Ist_IBF.Zeit.Ringumdrehung / 2;
                                                              
                           //Zahlenwert der Ringumdrehung in Sekunde vorgegeben. 
                           //Da Zyklus alle 100 ms aufgerufen wird, muss t_dis_h von vorhandenen Millisekunden auf Sekunde normiert werden. Faktor 10
                           //+1 f�r die ersten 100 ms, die sofort nach der Klammer subtrahiert werden
                           Soll_IBF->Radial.t_dis_h   = Ist_IBF.Zeit.Ringumdrehung * 10.0 + 1; 
 
                          
                           
                           // Variablen der Formel berechnen
    	   				   Soll_IBF->Radial.Cr.a = Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.da;           // Hauptwalzendurch. * Au�endurchmesser
                           Soll_IBF->Radial.Cr.b = Ist_Inter.di * Ist_Inter.Werkzeug.Durchmesser_DW;           // Innendurchmesser(Durchmesser-2*Wandst�rke) * Dornwalze
	   				       Soll_IBF->Radial.Cr.c = Ist_Inter.Werkzeug.Durchmesser_HW + Ist_Inter.da;           // Hauptwalzemdurch. + Au�endurchmesser
	   				       Soll_IBF->Radial.Cr.d = Ist_Inter.di - Ist_Inter.Werkzeug.Durchmesser_DW;		   // Au�endurchmesser - Dornwalze
	   				       //Soll_IBF->Radial.Cr.e = pow(Soll_IBF->Radial.Walzspalt_Cr,2);                       // Cr * Cr |-> bereits in 16 berechnet
	   				    
	   				       Soll_IBF->Radial.Cr.o = (Soll_IBF->Radial.Cr.a/Soll_IBF->Radial.Cr.c) * (Soll_IBF->Radial.Cr.b/Soll_IBF->Radial.Cr.d);
	   				       Soll_IBF->Radial.Cr.u = (Soll_IBF->Radial.Cr.a/Soll_IBF->Radial.Cr.c) + (Soll_IBF->Radial.Cr.b/Soll_IBF->Radial.Cr.d); 
	   				    
	   				        //-------------------------------------------------------------------------
	   				    
		                   Soll_IBF->Radial.Cr.g = (Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i] + 1/ Soll_IBF->Radial.Cr.e*(Soll_IBF->Radial.Cr.o / Soll_IBF->Radial.Cr.u));
		                   Soll_IBF->Radial.Cr.f = 2 * Soll_IBF->Radial.Cr.g;

                           Soll_IBF->Radial.abnahme_s = -2*Soll_IBF->Radial.Cr.g + ( sqrt( pow(Soll_IBF->Radial.Cr.f,2) - 4*pow(Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i],2)));

		                          //  l_r = sqrt( -1 * abnahme_s * ( o / u));                                     // Gedr�ckte L�nge
		                         //   s_m = Array[os_i] + ( abnahme_s /2);                                        // mittlere Wanddicke
		                         //   c_ri = l_r / s_m;                                                         // momentanes Walzspaltverh�ltnis
                           
		                  
		                	/* neue Abnahme bestimmen */
                            //Radial
		                	Soll_IBF->Radial.Soll_Wanddicke = Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i] + Soll_IBF->Radial.abnahme_s;
		                	Soll_IBF->RS_Pos = Soll_IBF->Radial.Soll_Wanddicke; 
		                	

                            //Axial (bei Radialprof = H�henzunahme)
                            Hoehenzunahme(Ist_Inter, Ist_IBF, Soll_IBF);	 
                            Soll_IBF->ASO_Pos = Soll_IBF->Radial.Rohlinghoehe + Soll_IBF->Radial.Breitung.delta_h;
                           
                               
          	  

		                	 		                	
		                	//Aktuelle Wanddicke speichern
		                	Soll_IBF->Radial.Cr.Array[Soll_IBF->Radial.Cr.os_i] = Ist_IBF.Radial.s_f;         	// Speichern der Wandst�rken im Feld [i]
		                  
		                    //Umstellen von os_i
		                  
		                    if(Soll_IBF->Radial.Cr.os_i == 1)
		                     {
                               Soll_IBF->Radial.Cr.os_i = 0;
                             }
		                    else Soll_IBF->Radial.Cr.os_i = 1;                            
		                  
		                   // if (os_i >=1)  //f�r Array [2]
		                   //	{os_i = -1;}
		                   // os_i= os_i+1;
		                   // Vorschub_v = ((s_f - position_ip1)/t_hU); // Geschwindigkeit f�r 2 Messungen per Zeiteinheit, t_hU Zeit f�r eine 1/2Umdrehung
        		         
                      }//endif


                     // Festhalten des Radialschlittens, wenn dieser die Position erreicht hat...
		                 
		           //  if( Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos + eps))     
                     //   {
                       //   Soll_IBF->RS_Pos = Ist_IBF.RS_Pos;
                        //}
		                
		               	                              		
                  		                     
                  	//-----------------------------------------------------------------------------
                  	//----------    Abbruchkriterium                        ----------------------
                  	//-----------------------------------------------------------------------------
                  		      
                  	 if( Ist_IBF.RS_Pos <= (Soll_IBF->RS_Pos_end + eps)) 
                  	  {	
                  		 Soll_IBF->Zeit.t_Halte= Soll_IBF->Radial.Umdrehungen * 10 * (Ist_Inter.da /(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.hw_n)); // n Umdrehungen, 10 * "100" ms Aufrufzyklus = 1000 ms = 1s;  
                         Soll_IBF->RS_Pos = Ist_IBF.RS_Pos;
                  		 Soll_IBF->Profilflag=2; 
  
                  		break;
                      }                  				

                     Soll_IBF->Radial.t_dis_h--;  
		  													
                  break;

             default :break;
         } //Klammer switch()


    return TRUE;
	// Ende der Funktion flexibel_Radial()
}
