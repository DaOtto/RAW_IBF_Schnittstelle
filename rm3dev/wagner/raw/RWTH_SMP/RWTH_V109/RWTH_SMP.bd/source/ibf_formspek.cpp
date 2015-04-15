/*--FILE HEADER------------------------------------------
;   filename     :  ibf_formspektrum.cpp
;   version      :  
;   contents     :  IBF-Modul FORMSPEKTRUM PROFILING
;   autor        :
;   Date         :  Jun, 2007
;---FUNKTION AND ENVIRONMENT-----------------------------
;
;
;
;
;---END OF FILE HEADER------------------------------------*/
/**********************************************************/
/*  includes                                              */
/**********************************************************/

#include "rpw.hpp"


/**********************************************************/
/*   function                                             */
/**********************************************************/

int RPW::formenspektrum(struct Def_Ist_Inter           Ist_Inter,
                      struct Def_IBF_Allgemein_IST   Ist_IBF,
					  struct Def_Soll_Inter          *Soll_Inter,
					  struct Def_IBF_Allgemein_SOLL  *Soll_IBF)
{
   //Programmmodul zum FORMSPEKTRUM PROFILIEREN
   
   switch (Ist_IBF.Formen.Profilflag)
       {
	   
       case 1:	     
	     // Walzung mit konstanter Abnahme eps pro Umdrehung!
 		/* Stützstellenberechnung*/
    		//	stuetzstellen(Ist_Inter, Ist_IBF, Soll_IBF);

		 /* Geschwindigkeiten  */

		 			if(Ist_IBF.Formen.t_U_Viola <= 0) 
							{
							 Soll_IBF->RS_V         = 0.0F;
							}
                    else 	 //Soll_IBF->RS_V         = Soll_IBF->Formen.delta_s_Viola/Ist_IBF.Formen.t_U_Viola;                                      
                     			Soll_IBF->RS_V         = Soll_IBF->stuetz_var.delta_s/Ist_Inter.Werkzeug.Ringumdrehung;         
								Soll_IBF->ASO_V        = 0.0F; 
                             
							 //Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 100.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F;

                             /* Kräfte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF ); //Funktionsaufruf							
							 /* Drehzahl */
                             Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                             Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                                                                         
                             
             /* Positionen */			   	
        				
        				// GIBT ES SCHON
        				//f_H = Ist_Inter.hw_n/(71*60);
        				//t_Halte = (float)(Umdrehungen*10*diam_f/((Ist_Inter->Werkzeug.Durchmesser_HW)*f_H));    //woanders hin
        				//Ringumdrehung = (float)(diam_f/((Ist_Inter->Werkzeug.Durchmesser_HW)*f_H));
        				
        			/*	if(t_Halte<=-1)
        				{
        				Soll_RS_V = ((Ist_IBF->IBF_Flag Flag.eps_Vorschub) * s1r)/t_Halte;
        				Soll_Inter->rs_v = Soll_RS_V;
        				};
        			*/
        				//definiere Endposition Radial
        				
        				       				
                  if(Ist_IBF.Zeit.t_Halte <= 0.0F)
                  {
                   Soll_IBF->Formen.delta_s_Viola = (Ist_IBF.Formen.epsilon) * (Ist_IBF.Radial.s_f);
                                      /* s1r = salt 
                     	  + salt * Ist_IBF->IBF_Flag Flag.eps_Vorschub;  // Berechnung des Delta s für die nächste Ringumdrehung
                  
                  	salt = s1r;                      // Speichern des aktuellen Wertes als s1r(t-1) für den nächsten Schleifenaufruf 
                  	*/
                   Soll_IBF->Zeit.t_Halte = (float)(10 * (Ist_Inter.da)/((Ist_Inter.Werkzeug.Durchmesser_HW) * (Ist_Inter.hw_n))); // Berechnen der Haltezeit für 1 Ringumdrehung und Übergabe an IBF-Struktur 
                  }
                    /*Zähler - Merker*/                
                   Soll_IBF->Zeit.t_Halte--;
    					 
    					 	 
    				 if(Ist_IBF.Formen.proz_s <= 0) Soll_IBF->Formen.proz_s = 0.0F;       //Begrenzung auf Zahl zwischen 0 und 94 (0%-94% Abnahme)
					  if(Ist_IBF.Formen.proz_s >= 94) Soll_IBF->Formen.proz_s = 94.0F;     

	                  Soll_IBF->Formen.Soll_RS_Pos_end = (Soll_IBF->Rohling_s_angefahren * (1 - Ist_IBF.Formen.proz_s/100.0F)); //Soll_RS_Pos_end ist Endwanddicke, hier auch = Enddornposition!
   	                  Soll_IBF->RS_Pos = Soll_IBF->Rohling_s_angefahren*(1 - Ist_IBF.Formen.proz_s/100.0F) - 1.0F; //falls  Soll_RS_Pos gewünscht    
							
                  		if (Soll_IBF->Rohling_s_angefahren <= 0) 
                  		{       
						Soll_IBF->Profilflag = 13; //Abbruch wg. fehlerhafter Festlegung der Endposition!                  		
                  		}            

                  	 	if(Ist_IBF.RS_Pos <= (Soll_IBF->Formen.Soll_RS_Pos_end)) //RE_Pos kleiner RS_end 
                  		{
							//Soll_IBF->Zeit.t_Halte= 30;
							Soll_IBF->Formen.Profilflag = 13; // Prozessende
                  		}                  				

    		break;    					


       case 2:
	   			//Walzung mit konstantem Cr (radial), Zustellung nach Geschwindigkeit

			       /* Stützstellenberechnung*/
                    konst_cr_radial(Ist_Inter, Ist_IBF, Soll_IBF);
                    stuetzstellen(Ist_Inter, Ist_IBF, Soll_IBF);

                    /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = Soll_IBF->stuetz_var.delta_s/Ist_Inter.Werkzeug.Ringumdrehung;
                             Soll_IBF->ASO_V        = 0.0F; // [mm/U] / [s/U]
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

    				if(Ist_IBF.Formen.proz_s <= 0) Soll_IBF->Formen.proz_s = 0.0F;       //Begrenzung auf Zahl zwischen 0 und 94 (0%-94% Abnahme)
					if(Ist_IBF.Formen.proz_s >= 94) Soll_IBF->Formen.proz_s = 94.0F;                   

   	                Soll_IBF->RS_Pos = Soll_IBF->Rohling_s_angefahren*(1 - Ist_IBF.Formen.proz_s/100.0F) - 1.0F; 
                  		if (Soll_IBF->Rohling_s_angefahren <= 0) 
                  		{       
						Soll_IBF->Profilflag = 13; //Abbruch wg. fehlerhafter Festlegung der Endposition!                  		
                  		}  
                  	 	if(Ist_IBF.RS_Pos <= (Soll_IBF->Rohling_s_angefahren*(1 - Ist_IBF.Formen.proz_s/100.0F))) 
                  		{
							//Soll_IBF->Zeit.t_Halte= 30;
							Soll_IBF->Formen.Profilflag = 13; // Prozessende
                  		}   
    		break;
	

       case 3:
				//Walzung mit konstantem Cr (radial), Zustellung durch Positionsvorgabe
			       /* Stützstellenberechnung*/
                    konst_cr_radial(Ist_Inter, Ist_IBF, Soll_IBF);
                    stuetzstellen(Ist_Inter, Ist_IBF, Soll_IBF);

                    /* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 5.0F;
                             Soll_IBF->ASO_V        = 0.0F; // [mm/U] / [s/U]
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

    				if(Ist_IBF.Formen.proz_s <= 0) Soll_IBF->Formen.proz_s = 0.0F;       //Begrenzung auf Zahl zwischen 0 und 94 (0%-94% Abnahme)
					if(Ist_IBF.Formen.proz_s >= 94) Soll_IBF->Formen.proz_s = 94.0F;                   

					Soll_IBF->RS_Pos = Ist_IBF.RS_Pos - Soll_IBF->stuetz_var.delta_s;
 
                  		if (Soll_IBF->Rohling_s_angefahren <= 0) 
                  		{       
						Soll_IBF->Profilflag = 13; //Abbruch wg. fehlerhafter Festlegung der Endposition!                  		
                  		}  
                  	 	if(Ist_IBF.RS_Pos <= (Soll_IBF->Rohling_s_angefahren*(1 - Ist_IBF.Formen.proz_s/100.0F))) 
                  		{
							//Soll_IBF->Zeit.t_Halte= 30;
							Soll_IBF->Formen.Profilflag = 13; // Prozessende
                  		}  

    		break;



       case 13:		//Rundungsphase, dann Prozessende!

    						/* Geschwindigkeiten  */
                             Soll_IBF->RS_V         = 0.0F; 
                             Soll_IBF->ASO_V        = 0.0F; //kein Zustellen in Rundungsphase!
                             Soll_IBF->Soll_ASU_V   = 0.0F;
                             Soll_IBF->AG_V         = 0.0F;
                             Soll_IBF->ZAL_V        = 0.0F;
                             Soll_IBF->ZAR_V        = 0.0F; 

                             /* Kräfte */
                             Kraftsteuerung (Ist_IBF , Soll_IBF); //Funktionsaufruf
                               
                             /* Drehzahl */
                             Soll_Inter->kwo_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);
                             Soll_Inter->kwu_n = KW_Drehzahl_axial(Ist_Inter, &Ist_IBF);

		 		Soll_IBF->RS_Pos = Ist_IBF.RS_Pos;
				Soll_IBF->AG_Pos = Ist_IBF.AG_Pos;

                if(Ist_IBF.Zeit.t_Halte <= 0) 
                          {
                          Soll_IBF->Profilflag = 13;
                          }
                Soll_IBF->Zeit.t_Halte--; // Runterzählen der Zeit für Glättungsrunde


    		break;


		default:   break;
	   	
	   }//Ende switch(profilflag)
	return TRUE;
}
