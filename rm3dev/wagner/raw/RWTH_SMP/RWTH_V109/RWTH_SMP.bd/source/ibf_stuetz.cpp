#include "rpw.hpp"
#include "IBF_struct.hpp" // NEU EINGEBUNDEN MIC



    /*-----------------------------------------------------------------------*/
    /*                                                                       */
    /*                   IBF Funktionen: Stuetzstellenberechnung             */
    /*                                                                       */
    /*                                                                       */
    /*                                                                       */
    /*                                                                       */
    /*                                                                       */
    /*                                                                       */
    /*-----------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------
//Die Variablen müssen an geeigneter Stelle (z.B. rwth_exch? rpw?) wie folgt initialisiert werden:
//----------------------------------------------------------------------------------------------------

/*Soll_IBF->stuetz_var.crtimer = 0; //als Zählvariable zur Bestimmung des Stützstellenwechsels
Soll_IBF->stuetz_var.stellen[2][maxstellen]={0};	//Array zur Aufnahme der Stützstellen. 0. Spalte für Wanddicke, 1. für Höhe!
Soll_IBF->stuetz_var.merker = 0;		//Variable, welche die jeweils aktive Stützstelle im Array aufnimmt
Soll_IBF->stuetz_var.skip_faktor = 1;	//Wird verwendet um hohe Werte von maxstellen bei zu kleinen Ringen umsetzen zu können
*/






//----------------------------------------------------------------------------------------------------
//Es folgt die eigentliche Funktion
//----------------------------------------------------------------------------------------------------


/** Schreibt die aktuell gemessene Stuetzstelle in das Array \link stuetzstellen_var.stellen  \endlink . Sollten
 * nicht alle Stuetzstellen aus zeitlichen Gruenden gemessen worden sein, so werden fehlende Eintraege des
 * Arrays mit Hilfe des Arithmetischen Mittels berechnet. Weitere Erlaeuterungen gibt es in der Studienarbeit
 * von Sascha Frank ("Programmiervorschrift des IBF-Moduls der Ringwalzsteuerung 'SMS-CARWIN' am Beispiel
 * des Funktionsbausteins 'Zustellung durch Walzspaltverha¿ltnis' und Automatisierung der Messschriebauswertung").
 *
 * @param[in] Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param[in] Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
 * @param[in] *Soll_IBF ein Zeiger auf eine Struktur vom Typ \link Def_IBF_Allgemein_SOLL \endlink*/
void stuetzstellen(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
{



					if (Soll_IBF->stuetz_var.crtimer <= 100)   // Teilumdrehung gelaufen. Stützstellenwechsel und neue Berechnung					
			      	{					      	
					      if ((Soll_IBF->stuetz_var.stellen[0][maxstellen-1] > 0) && (Soll_IBF->stuetz_var.stellen[0][0] > 0))	//Prüfung: alle Stützstellen schon eingelesen?
							{
								//************hier Zusatzfunktionsaufruf einsetzen!**************
								//************Berücksichtigung von "Funktionswahl" nicht vergessen!**************
							}
               
                     		Soll_IBF->stuetz_var.crtimer = (float)(1000*Ist_Inter.Werkzeug.Ringumdrehung / maxstellen);   //Timer neu setzen. Faktor 10, aus Ringumdrehung in s (=1000 Millisek.) und Aufruf alle 100ms
                     		
                            if (Soll_IBF->stuetz_var.crtimer <= 100)
							{
								//Soll_IBF->stuetz_var.skip_faktor = (int)(maxstellen*100 / 1000*Ist_Inter.Werkzeug.Ringumdrehung);
                        Soll_IBF->stuetz_var.skip_faktor = (int)(maxstellen / (10 * Ist_Inter.Werkzeug.Ringumdrehung) ); //Faktor 10 wg. 100ms (Zeit zw. 2 Aufrufen) / 1000ms (Ringumdrehung in s angegeben)
                                //Soll_IBF->stuetz_var.skip_faktor = (int)(maxstellen*100/t_U);	//evtl. +0.5 oder +0.9, alternativ: floor/ceiling zum Runden
											//skip_faktor = Anz.Stellen(vorgegeben)/Anz.Stellen(tatsächlich machbar), abgerundet!!!
											//Grund: Abrunden führt evtl. zu Timer Werten < 100, aber insgesamt zu geringeren Abweichun-
											//gen von der Umdrehungszeit!
						  		Soll_IBF->stuetz_var.crtimer = (float)(Soll_IBF->stuetz_var.crtimer * Soll_IBF->stuetz_var.skip_faktor);
							}
							else Soll_IBF->stuetz_var.skip_faktor = 1;
							for(int i_for = 0; i_for < Soll_IBF->stuetz_var.skip_faktor; i_for++)
							{
								if ((Soll_IBF->stuetz_var.skip_faktor > 1) && (i_for < (Soll_IBF->stuetz_var.skip_faktor-1)))
								{	//falls Stellen übersprungen werden müssen werden diese hier mit Mittelwerten aufgefüllt
									if ((Soll_IBF->stuetz_var.merker-i_for-1)<=0)	//Berücksichtigung des Wechsels vom Ende des Arrays zum Anfang!
									{
										Soll_IBF->stuetz_var.stellen[0][Soll_IBF->stuetz_var.merker] = (float)(( Soll_IBF->stuetz_var.stellen[0][(Soll_IBF->stuetz_var.merker-i_for-1+maxstellen)] + Ist_IBF.RS_Pos )/2);
										if (Soll_IBF->stuetz_var.stellen[0][(Soll_IBF->stuetz_var.merker-i_for-1+maxstellen)] == 0) Soll_IBF->stuetz_var.stellen[0][Soll_IBF->stuetz_var.merker] = Ist_IBF.RS_Pos;
										Soll_IBF->stuetz_var.stellen[1][Soll_IBF->stuetz_var.merker] = (float)(( Soll_IBF->stuetz_var.stellen[1][(Soll_IBF->stuetz_var.merker-i_for-1+maxstellen)] + Ist_IBF.ASO_Pos )/2);
										if (Soll_IBF->stuetz_var.stellen[1][(Soll_IBF->stuetz_var.merker-i_for-1+maxstellen)] == 0) Soll_IBF->stuetz_var.stellen[1][Soll_IBF->stuetz_var.merker] = Ist_IBF.ASO_Pos;
									}
									else
									{
										Soll_IBF->stuetz_var.stellen[0][Soll_IBF->stuetz_var.merker] = (float)(( Soll_IBF->stuetz_var.stellen[0][(Soll_IBF->stuetz_var.merker-i_for-1)] + Ist_IBF.RS_Pos )/2);
										Soll_IBF->stuetz_var.stellen[1][Soll_IBF->stuetz_var.merker] = (float)(( Soll_IBF->stuetz_var.stellen[1][(Soll_IBF->stuetz_var.merker-i_for-1)] + Ist_IBF.ASO_Pos )/2);
									}
								}
								else
								{
									Soll_IBF->stuetz_var.stellen[0][Soll_IBF->stuetz_var.merker] = (float)(Ist_IBF.RS_Pos);
									Soll_IBF->stuetz_var.stellen[1][Soll_IBF->stuetz_var.merker] = (float)(Ist_IBF.ASO_Pos);
						  		}	
								Soll_IBF->stuetz_var.merker++;
								if (Soll_IBF->stuetz_var.merker >= maxstellen) Soll_IBF->stuetz_var.merker = 0; 
							}
							//if (Soll_IBF->stuetz_var.merker >= maxstellen) Soll_IBF->stuetz_var.merker = 0;						
					}
					else Soll_IBF->stuetz_var.crtimer = Soll_IBF->stuetz_var.crtimer - 100; //Timer herunterzählen. Programm wird alle 100ms aufgerufen.			
				


                    Soll_IBF->stuetz_var.kontrollmerker = Soll_IBF->stuetz_var.kontrollmerker + (float)(maxstellen / (10 * Ist_Inter.Werkzeug.Ringumdrehung) );

                    if (int(Soll_IBF->stuetz_var.kontrollmerker) > Soll_IBF->stuetz_var.merker)
                        {
                        	if (int(Soll_IBF->stuetz_var.kontrollmerker) >= maxstellen)
                    	       {
                        		Soll_IBF->stuetz_var.kontrollmerker = Soll_IBF->stuetz_var.kontrollmerker - maxstellen;
                        		if (int(Soll_IBF->stuetz_var.kontrollmerker) < Soll_IBF->stuetz_var.merker)
                            		{
                        			for(int i_for = Soll_IBF->stuetz_var.merker; i_for < maxstellen; i_for++)
			                            {
                        				Soll_IBF->stuetz_var.stellen[0][i_for] = (float)(Ist_IBF.RS_Pos);
        		                  		Soll_IBF->stuetz_var.stellen[1][i_for] = (float)(Ist_IBF.ASO_Pos);
                		                }
            	                   for(int i_for2 = 0; i_for2 < int(Soll_IBF->stuetz_var.kontrollmerker); i_for2++)
                        		        {
                        				Soll_IBF->stuetz_var.stellen[0][i_for2] = (float)(Ist_IBF.RS_Pos);
		                        		Soll_IBF->stuetz_var.stellen[1][i_for2] = (float)(Ist_IBF.ASO_Pos);				
                                		}
		                            } //endif            	
                                } //endif

            	           if (int(Soll_IBF->stuetz_var.kontrollmerker) > Soll_IBF->stuetz_var.merker)
                                {
                        		for(int i_for = Soll_IBF->stuetz_var.merker; i_for < int(Soll_IBF->stuetz_var.kontrollmerker); i_for++)
		                          {
                        		  	Soll_IBF->stuetz_var.stellen[0][i_for] = (float)(Ist_IBF.RS_Pos);
                        			Soll_IBF->stuetz_var.stellen[1][i_for] = (float)(Ist_IBF.ASO_Pos);				
                    	           }
                            	}//endif
                        	Soll_IBF->stuetz_var.merker = int(Soll_IBF->stuetz_var.kontrollmerker);
                        }//endif

							

					#ifdef MRAW
					if ((Soll_IBF->stuetz_var.stellen[0][0] <= 0) && (Soll_IBF->stuetz_var.stellen[0][maxstellen-1] > 0))  
					{
							_settextposition(20,50); printf(" Fehler bei Stützstellenbestimmung!?!??!???");
					}
                    #endif
					
					
} // Ende der Funktion 





//AUFRUF: muss direkt VOR Einlesen der nächsten Stützstelle aufgerufen werden (sonst ist Stützstelle bereits mit aktuellen Werten überschrieben!)

/** Diese Methode berechnet nur etwas, wenn das Array mit den Stuetzstellen bereits 
 * komplett gefuellt ist.
 * Falls dann genug Zeit bleibt (wenn \link stuetzstellen_var::crtimer \endlink > 0.001 ms ist), wird 
 * \link stuetzstellen_var::crtimer \endlink neu berechnet. Unabhaengig davon, welche Zeit
 * in \link stuetzstellen_var::crtimer \endlink steht, wird auch noch die Stichabnahme fuer eine
 * Ringumdrehung berechnet. Die Formel fuer die Berechnung haengt jedoch
 * wieder von \link stuetzstellen_var::crtimer \endlink ab.
 *
 * <p>
 * Zeitpunkt des Aufrufes muss direkt <b>vor</b> der naechsten Stuetzstelle aufgerufen 
 * weren (sonst ist die Stuetzstelle bereits mit aktuellen Werten ueberschrieben!)
 * </p>
 * @param[in] Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param[in] Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
 * @param[in] *Soll_IBF ein Zeiger auf eine Struktur vom Typ \link Def_IBF_Allgemein_SOLL \endlink*/
void konst_cr_radial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
{


    if ((Soll_IBF->stuetz_var.stellen[0][maxstellen-1] > 0) && (Soll_IBF->stuetz_var.crtimer <= 100))	//Ausführung nur, falls komplettes Array bereits gefüllt und timer Ausführung vorsieht!
      {
        //lokal benötigte Variablen
		float S0r, S1r, Smr, dHstrich, d_innen, dDstrich, rrstrich;	

		S0r = Soll_IBF->stuetz_var.stellen[0][Soll_IBF->stuetz_var.merker]; //Einlaufwanddicke = Stuetzstelle = Wert vor 1 Umdrehung
		S1r = (float)(Ist_IBF.RS_Pos); //Auslaufwanddicke = aktueller Walzspalt
		
		//Hinweis: RS_Pos entspricht der radialen Wanddicke. Überprüfung: Ist_Inter.s0r, Ist_Inter.s1r
		Smr = (S0r + S1r) / 2; //ACHTUNG: Berechnung aus ALTEN Werten für s0r+s1r! Anders nicht machbar.
        
		// Berechnung dH' = (Hauptwalzendurch. * Durchmesser)/(Summe der beiden); diam_f= gefilterter Durchm.
        // dH' = fiktiver Durchmesser der Hauptwalze, Ist_Inter.Werkzeug.Durchmesser_HW = Hauptwalzendurchmesser aus Carwin [mm]
	   	dHstrich = (float)(Ist_Inter.Werkzeug.Durchmesser_HW * Ist_Inter.da / (Ist_Inter.Werkzeug.Durchmesser_HW + Ist_Inter.da));
		d_innen = (float)(Ist_Inter.da - 2*Smr); //Innendurchmesser
	   	
		// Berechnung dD' = (Innendurchm.*Durchm.Dornwalze)/Differenz der beiden; diam_dw = Durchm. Dornwalze
	   	// dD' = fiktiver Durchmesser der Dornwalze, Ist_Inter.Werkzeug.Durchmesser_DW = Dornwalzendurchmesser aus Carwin [mm]
		dDstrich = (float)(d_innen * Ist_Inter.Werkzeug.Durchmesser_DW / (d_innen - Ist_Inter.Werkzeug.Durchmesser_DW));
		
		// rr' = rrstrich = fiktiver Radius  (Produkt der fikt. Durchmesser/Summe)
	   	rrstrich = dHstrich*dDstrich/(dHstrich+dDstrich);
		if (Ist_IBF.stuetz_var.cr <= 0.001)	//Cr muss vorgegeben sein!
			{
				Soll_IBF->stuetz_var.cr = (sqrt((S0r-S1r)*rrstrich))/Smr;
                Soll_IBF->stuetz_var.delta_s = (float)(2*rrstrich/pow(Soll_IBF->stuetz_var.cr,2)+sqrt(8*S0r*rrstrich/pow(Soll_IBF->stuetz_var.cr,2)+4*pow(rrstrich,2)/pow(Soll_IBF->stuetz_var.cr,4)));
			}
		
        //Soll_IBF->RS_Pos = delta_S -S0r = angestrebte Wanddicke = Ziel dieser Berechnung!!! delta_S = (cr*smr)²/fiktiver Radius
		else Soll_IBF->stuetz_var.delta_s = (float)(2*rrstrich/pow(Ist_IBF.stuetz_var.cr,2)+sqrt(8*S0r*rrstrich/pow(Ist_IBF.stuetz_var.cr,2)+4*pow(rrstrich,2)/pow(Ist_IBF.stuetz_var.cr,4)));

      } //endif
				

} //Ende konst_cr_radial


/**
 * Berechnet die angestrebte axiale Wanddicke. Sollte kein \link stuetzstellen_var::crtimer \endlink berechnet worden sein, so wird auch dieser berechnet.
 * <p>Eine Warnung bezueglich des Quellcodes. Es wird von 'S0r' und 'S1r' gesprochen, diese Variablen beziehen sich jedoch auf radiale
 * Eigenschaften. Es müsste eigentlich von 'H0r' und 'H1r' die Rede sein.</p> 
 * @param[in] Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param[in] Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
 * @param[in] *Soll_IBF ein Zeiger auf eine Struktur vom Typ \link Def_IBF_Allgemein_SOLL \endlink 
 * @bug Bei der Berechnung von 'axi_e' wird statt mit dem Radius mit dem Durchmesser gerechnet.
 * 'axi_e' Soll den Abstand zwischen Mittelpunkt und theoretischer Spitze beschreiben.
 * Dies führt zu einem Fehler in der Berechnung von 'delta_h'*/
void konst_cr_axial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF)
{

	//Bedeutung _A_X_I_A_L_ mit konstantem Cr und KRAGENWALZE walzen (Kragenwalze verursacht andere gedrückte Länge als Kegelwalze)!
	
					if ((Soll_IBF->stuetz_var.stellen[1][maxstellen-1] > 0) && (Soll_IBF->stuetz_var.crtimer <= 100))	//Ausführung nur, falls komplettes Array bereits gefüllt und timer Ausführung vorsieht!
					{
					//lokal benötigte Variablen	
                    float h0a, h1a, hma, axi_Rm, axi_e;	
					
                   	h0a = Soll_IBF->stuetz_var.stellen[1][Soll_IBF->stuetz_var.merker]; //Einlaufwanddicke axial = Stuetzstelle = Wert vor 1 Umdrehung
					h1a = (float)Ist_IBF.ASO_Pos;  //Auslaufwanddicke = aktueller axialer Walzspalt
					hma = (h0a + h1a) / 2;  //hier ist "Smr" in Wahrheit die mittlere Höhe (Axialspalt).

					// axi_Rm = Radius bis Mitte Profil. Ist_IBF->Axial.AGR_Pr[Profilnummer] ist Profilposition von Aussenrand aus gemessen
					axi_Rm = Ist_Inter.da - Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num] - Ist_IBF.Axial.Kr_geo.Kr_Br/2;
                    
                    // axi_e ist der Abstand der imaginären Kegelwalzenspitze zur Ringachse
					// Abstand Kragenkante zu imaginärer Kegelwalzenspitze: Ist_IBF->Axial.Kr_geo.Del_Kr_AGR = Ist_IBF->Axial.Kr_geo.Kr_d_nenn_vorne / (2*Ist_IBF->Axial.Kr_geo.sin_kw_winkel_halbe); //= 359.5??????
			
        			axi_e = axi_Rm - Ist_IBF.Axial.Kr_geo.Del_Kr_AGR - Ist_IBF.Axial.Kr_geo.Kr_Br/2;		//Kragenbreite = 32.

                    //Falls cr nicht vorgegeben wird, wird dieses mit dem ersten Funtionsaufruf berechnet und entsprechend verwendet
               		if (Ist_IBF.stuetz_var.ca <= 0.001)	//Cr muss vorgegeben sein!
	       				{
		  				Soll_IBF->stuetz_var.ca = (sqrt((h0a-h1a)*tan(22.5*PI/180)*(axi_Rm-axi_e)))/hma;
                        Soll_IBF->stuetz_var.delta_h = (float)(pow(Soll_IBF->stuetz_var.ca,2)*pow(hma,2)/(tan(22.5*PI/180)*(axi_Rm-axi_e)));
		      			}
						//Soll_IBF->ASO_Pos = delta_h -h0r = angestrebte axiale Ringhöhe = Ziel dieser Berechnung!!!
			 		else Soll_IBF->stuetz_var.delta_h = (float)(pow(Ist_IBF.stuetz_var.ca,2)*pow(hma,2)/(tan(22.5*PI/180)*(axi_Rm-axi_e)));
                    }


} //Ende konst_cr
