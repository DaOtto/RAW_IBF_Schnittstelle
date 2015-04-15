#include "../inc/ibf_Schuessel.hpp"

/*-----------------------------------------------------*/
/*                IBF Schuesselwalzung                 */
/*                                                     */
/*    Methoden zur Walzung einer Schüssel in           */
/*    Zusammenhang mit der DA von Joachim Seitz        */
/*    01.16.2014 Jan Uthoff                            */
/*                                                     */
/*-----------------------------------------------------*/

/** Hauptmethode zur Walzung einer Schuessel.
 * Es wird die Zeit 
 * \link T_KLETTERN_STARTEN \endlink abgewartet, bevor mit dem eigentlichen
 * Walzvorgang begonnen wird. Um das Klettern des Ringes zu erzwingen wird der
 * obere Axialschlitten zugestellt. Hierfür wird die Methode 
 * \link axialSchlittenAnfahren \endlink verwendet.
 * @param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
 * @param *Soll_IBF Zeiger einer Struktur vom Typ \link Def_IBF_Allgemein_SOLL \endlink
 * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param *Soll_Inter Zeiger einer Struktur vom Typ \link Def_Soll_Inter \endlink
 * @todo Abbruchbedingung fuer die Berechnung der Zentrierrollenpositionen
 * @bug Die Abbruchbedinung fuer das Walzen einer Schuessel nicht nicht korrekt*/
void ibf_Schuessel::Main(struct Def_IBF_Allgemein_IST Ist_IBF,
          struct Def_IBF_Allgemein_SOLL *Soll_IBF,
          struct Def_Ist_Inter Ist_Inter,
          struct Def_Soll_Inter *Soll_Inter) {

   

  ibf_Schuessel::radialSchlittenAnfahren(Ist_IBF, Soll_IBF, Ist_Inter, Soll_Inter);
//  ibf_Schuessel::axialGeruestAnfahren(Ist_IBF, Soll_IBF, Ist_Inter, Soll_Inter);
//  ibf_Schuessel::axialSchlittenAnfahren(Ist_IBF, Soll_IBF, Ist_Inter, Soll_Inter);
  ibf_Schuessel::zentrierRollenSchliessen(&Ist_IBF, Soll_IBF, Ist_Inter);

  /*Lasse eine bestimmte Zeit ablaufen, bevor das Klettern erzwungen wird.
   * t_start dient zusätzlich auch noch zur Zeitmessung für Berechnung der
   * Zentrierrollenpositionen.*/
  time_t t_start,t_aktuell;

  t_start=time(NULL);
  t_aktuell=time(NULL);
  while(t_aktuell-t_start < T_KLETTERN_STARTEN){
    t_aktuell=time(NULL);
  }
  

  /*
	Soll_IBF->ZAR_Pos = 1415;
	Soll_IBF->ZAL_Pos = 1415;
   */

  Ist_IBF.IBF_Schuessel.ringDurchmesserKlettern = Ist_Inter.da; 
  
  ibf_Schuessel::zentrierRollenOeffnen(&Ist_IBF, Soll_IBF, Ist_Inter);
  
  t_start=time(NULL);
  time_t t_Zentrierrollen = T_ZENTRIERROLLEN_KONTROLLE;
  int running = 1;
  while(running && Ist_IBF.ASO_Pos > Soll_IBF->ASO_Pos){
    try  {
      if(t_Zentrierrollen >= T_ZENTRIERROLLEN_KONTROLLE)
      {
        ibf_Schuessel::steuerungZentrierrollen(	Ist_IBF,
	    										Soll_IBF,
											 	Ist_Inter,
											 	Soll_Inter);
        t_Zentrierrollen = 0; // Resetten des Timers
      }
      else 
      { 
        t_Zentrierrollen = time(NULL);
        t_Zentrierrollen = (t_Zentrierrollen - t_start) % T_ZENTRIERROLLEN_KONTROLLE;
      }
    }
    catch (const int exNummer){
	
      running = 0;
      switch(exNummer){

        case EXCEPTION_WRONG_ARGUMENT_1:
            cout << "ERROR: ungueltige Parameter fuer die Funktion 'berechneAlpha'";
            cout << " in ibf_Schuessel.cpp wurden uebergeben. "<< endl;
        break;
        
          case EXCEPTION_WRONG_ARGUMENT_2:	
            cout << "ERROR: ungueltige Parameter fuer die Funktion ";
            cout <<"'zentrierrollenPositionBerechnen'";
            cout << " in ibf_Schuessel.cpp wurden uebergeben. "<< endl;
        break;
          
          case EXCEPTION_WRONG_ARGUMENT_3:
            cout << "ERROR: ungueltige Parameter fuer die Funktion 'berechneBeta4'";
            cout << " in ibf_Schuessel.cpp wurde uebergeben." << endl;
        break;
       
          case EXCEPTION_WRONG_ARGUMENT_4:
            cout << "ERROR: ungueltige Parameter fuer die Funktion 'berechneBeta1'";
            cout << " wurden uebergeben." << endl;
        break; 
          
          case EXCEPTION_WRONG_ARGUMENT_5:
            cout << "ERROR: ungueltige Parameter fuer die Funktion ";
            cout << "'zentrierrollenPositionBerechnen' wurden uebergeben." << endl;
        break;
          
        default:
          cout << "ERROR: ein unbekannter Fehler ist aufgetreten" << endl;
          break;
      }
    }
  }
  
  Ist_IBF.Profilflag = 13;
}

/** Faehrt den Radialschlitten an.
  * Hierbei  wird genau genommen nicht der Radialschlitten zugestellt, 
  * sonder die Dornwalze.
  *
  * @param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
  * @param *Soll_IBF ein Zeiger auf eien Struktur vom Typ
  * \link Def_IBF_Allgemein_SOLL \endlink
  * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
  * @param *Soll_Inter ein Zeiger auf eien Struktur vom Typ
  * \link Def_Soll_Inter
  */
void ibf_Schuessel::radialSchlittenAnfahren( struct Def_IBF_Allgemein_IST Ist_IBF,
                                            struct Def_IBF_Allgemein_SOLL* Soll_IBF,
                                            struct Def_Ist_Inter Ist_Inter,
                                            struct Def_Soll_Inter *Soll_Inter) {
 

    Soll_IBF->RS_Pos =  Ist_Inter.Vorform.sm
                      + RADIALER_PUFFER
                      + Ist_Inter.Werkzeug.Durchmesser_DW/2;
                        

	while(Ist_IBF.RS_Pos != Soll_IBF->RS_Pos) {}
}


/** Stellt das Axialgeruest zu.
  * Dies wird so zugestellt, dass das die Axialwalzen bis kurz vor die vor die
  * Dornwalze gefahren werden. Die Distanz zwischen Dornwalze und Axialgeruest
  * werden durch \link AXIAL_PUFFER \endlink festgelegt.
  *
  * bis die Abbruchsringhoehe erreicht ist.
  * Wenn diese Ringhoehe erreicht wurde, so verharrt der obere Axialschlitten an
  * der Position.
  * @param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
  * @param *Soll_IBF ein Zeiger einer Struktur vom Typ i
  * link Def_IBF_Allgemein_SOLL \endlink
  * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
  * @param *Soll_Inter ein Zeiger einer Struktur vom Typ
  * \link Def_Soll_Inter \endlink
  * @bug Berechnung der Axialgeruestposition fehlt*/
void ibf_Schuessel::axialGeruestAnfahren( struct Def_IBF_Allgemein_IST Ist_IBF,
                                          struct Def_IBF_Allgemein_SOLL* Soll_IBF,
                                          struct Def_Ist_Inter Ist_Inter,
                                          struct Def_Soll_Inter *Soll_Inter) {
    


    Soll_Inter->ag_pos =  Ist_Inter.da
						- Ist_Inter.Vorform.sm
						- AXIAL_PUFFER_GERUEST;
                            
    while(Ist_Inter.ag_pos != Soll_Inter->ag_pos){}

}


/** Stellt den oberen Axialschlitten zu, bis die Abbruchsringhoehe erreicht ist.
 * Wenn diese Ringhoehe erreicht wurde, so verharrt der obere Axialschlitten an
 * der Position.
 * @param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
 * @param *Soll_IBF ein Zeiger einer Struktur vom Typ \link Def_IBF_Allgemein_SOLL \endlink 
 * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param *Soll_Inter ein Zeiger einer Struktur vom Typ 
 * \link Def_Soll_Inter \endlink
 * @bug Berechnung der Axialgeruestposition fehlt*/
void ibf_Schuessel::axialSchlittenAnfahren(	struct Def_IBF_Allgemein_IST Ist_IBF,
                                            struct Def_IBF_Allgemein_SOLL* Soll_IBF,
                                            struct Def_Ist_Inter Ist_Inter,
                                            struct Def_Soll_Inter *Soll_Inter) {
  
  Soll_IBF->ASO_V = V_ZUSTELLUNG_AXIALSCHLITTEN_OBEN;
  Soll_Inter->aso_pos = Ist_Inter.Vorform.hm + AXIAL_PUFFER_ASO;

  while(Ist_Inter.aso_pos != Soll_Inter->aso_pos) {}
}





/** Berechnet einen durchnittlichen Aussendruchmesser.
 * Zur Berechnung werden \link ANZAHL_DURCHMESSER_MESSUNGEN \endlink viele
 * Messungen verwendet.
 * @param Ist_IBF ein Zeiger auf eine Struktur vom Typ 
 * \link Def_IBF_Allgemein_Ist \endlink
 * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @return gemittelterAussenDurchmesser*/
int ibf_Schuessel::berechneRingdurchmesser(	struct Def_IBF_Allgemein_IST *Ist_IBF,
											struct Def_Ist_Inter Ist_Inter) {
    
  int gemittelterAussenDurchmesser = 0;
  int i;

  for(i = 0; i<ANZAHL_DURCHMESSER_MESSUNGEN; i++){
    gemittelterAussenDurchmesser = gemittelterAussenDurchmesser + Ist_Inter.da;
  }

  gemittelterAussenDurchmesser = gemittelterAussenDurchmesser 
                                / ANZAHL_DURCHMESSER_MESSUNGEN;

  // aktualisiere den Aussendruchmesser
  Ist_IBF->IBF_Schuessel.ringDurchmesserKlettern = gemittelterAussenDurchmesser;

  return gemittelterAussenDurchmesser;

}


/** Steuert die Zentrierrollen.
 * Abhaenging davon, ob der Ring klettert oder nicht muessen die
 * Zentrierrollen gesteuert werden. Wenn der Ring klettert, werden die Rollen
 * geschlossen, um den Ring zu stabilisieren. Sollte der Ring nicht klettern,
 * so werden die Rollen geoeffnet, so dass leichter klettern kann. Ob ein Ring
 * klettert wird mit Hilfe von 
 * \link Def_IBF_Schuessel::ringDurchmesserKlettern \endlink
 * festgestellt. Sollte der aktuelle Ringdurchmesser kleiner sein als 
 * \link Def_IBF_Schuessel::ringDurchmesserKlettern \endlink so muss der 
 * Ring klettern.
 * @param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
 * @param *Soll_IBF ein Zeiger auf eine Struktur vom Typ
 * \link Def_IBF_Allgemein_SOLL \endlink
 * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param *Soll_Inter ein Zeiger auf eine Struktur vom Typ 
 * \link Def_Soll_Inter \endlink
 * \throw int eine Nummer an Hand dessen festgestellt werden kann, wo ein
 * Fehler aufgetreten ist. Die Nummer die Bezug zum Schuesselwalzen haben sind
 * in \link ibf_Schuessel.hpp \endlink als Macro aufgelistet.
 */
void ibf_Schuessel::steuerungZentrierrollen( 
                              struct Def_IBF_Allgemein_IST Ist_IBF,
                              struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                              struct Def_Ist_Inter Ist_Inter,
                              struct Def_Soll_Inter *Soll_Inter) 
                              {  

  try {
    if(Ist_IBF.IBF_Schuessel.zentrierrollenOffen)
    {/* Die Zentrierrollen sind geöffnet */
      
      if(!ibf_Schuessel::ringKlettert(&Ist_IBF, Ist_Inter))
      {/* der Ring klettert */
        ibf_Schuessel::zentrierRollenSchliessen(&Ist_IBF,
												Soll_IBF,
												Ist_Inter);
      }
    }
    else
    {/* Die Zentrierrollen sind geschlossen */
      if(!ibf_Schuessel::ringKlettert(&Ist_IBF, Ist_Inter))
      {/* Der Ring klettert nicht */
        ibf_Schuessel::zentrierRollenOeffnen(	&Ist_IBF,
												Soll_IBF,
												Ist_Inter);
      }
    }
  }
  catch (const int exNummer){
    throw exNummer;
  }
}

/** Öffnet die Zentrierrollen.
 * Wenn diese schon geoeffnet sind, so bleiben diese geoeffnet, dennoch wird
 * die Berechung der Positionen erneut vorgenommen. Die Berechnung
 * der genauen Position der Zentrierrollen erfolgt in der Methode 
 * \link ibf_Schuessel::zentrierrollenPositionBerechnen \endlink.
 * @param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
 * @param *Soll_IBF ein Zeiger auf eine Struktur vom Typ 
 * \link Def_IBF_Allgemein_SOLL \endlink 
 * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * \link Def_Soll_Inter \endlink
 */
void ibf_Schuessel::zentrierRollenOeffnen( 
                            struct Def_IBF_Allgemein_IST *Ist_IBF,
                            struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                            struct Def_Ist_Inter Ist_Inter){
    
	try{
    Soll_IBF->ZAR_Pos = 
		ibf_Schuessel::zentrierrollenPositionBerechnen(Ist_Inter,
                                                       RECHTS,
													   ZENTRIERROLLEN_OEFFNEN_OFFSET,
													   OEFFNEN);
    Soll_IBF->ZAL_Pos = 
		ibf_Schuessel::zentrierrollenPositionBerechnen(Ist_Inter,
                                                       LINKS,
													   ZENTRIERROLLEN_OEFFNEN_OFFSET,
													   OEFFNEN);
	Ist_IBF->IBF_Schuessel.zentrierrollenOffen = OEFFNEN;
  }
  catch (const int exInt){
    throw;
  }
  
}

/** Schließt die Zentrierrollen
 * Wenn diese schon geschlossen sind, so bleiben diese geschlossen, dennoch
 * wird die Berechnung der Positionen erneut vorgenommen. Die Berechung der
 * genauen Position der Zentrierrollen erfolgt in der Methode
 * \link ibf_Schuessel::zentrierrollenPositionBerechnen \endlink .
 * @param Ist_IBF eine Struktur des Types
 * \link Def_IBF_Allgemein_IST \endlink
 * @param *Soll_IBF ein Zeiger auf eine Struktur des Typs 
 * \link Def_IBF_Allgemein_SOLL \endlink
 * @param Ist_Inter eine Struktur des Typs
 * \link Def_Ist_Inter \endlink
 * @throw int eine Nummer an Hand dessen festgestellt werden kann, wo ein
 * Fehler aufgetreten ist. Die Nummer die Bezug zum Schuesselwalzen haben,
 * sind in \link ibf_Schuessel.hpp \endlink als Macro aufgelistet..
 */
void ibf_Schuessel::zentrierRollenSchliessen(  
                                struct Def_IBF_Allgemein_IST *Ist_IBF,
                                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                                struct Def_Ist_Inter Ist_Inter){
  try {
    
    Soll_IBF->ZAR_Pos = 
		ibf_Schuessel::zentrierrollenPositionBerechnen(Ist_Inter, 
                                                       RECHTS,
													   0,
												       SCHLIESSEN);
    Soll_IBF->ZAL_Pos = 
		ibf_Schuessel::zentrierrollenPositionBerechnen(Ist_Inter,
                                                       LINKS,
													   0,
													   SCHLIESSEN);
    Ist_IBF->IBF_Schuessel.zentrierrollenOffen = SCHLIESSEN;
  }
  catch (const int intNummer){
    throw intNummer;
  }
}


/** Berechnet der Zentrierrollenpositionen.
 * Die Berechnung erfolgt abhaengig davon, ob die Zentrierrollen geoeffnet
 * werden soll (kein Kontakt am Ring haben) oder geschlossen sind (Kontakt am
 * Ring haben). Der berechnete Wert entspricht der Position fuer die
 * Zentrierrolle rechts und links.
 * Die Herleitung für die Berechnung ist in dem Paper  "Finite element 
 * analysis of the ring rolling process with integrated closed-loop control,"
 * CIRP Annals - Manufacturing Technology, vol. 61/1, pp. 267-270, 2012
 * von V. Jenkouk, Hirt, G., Franzke, M., Zhang, T. zu finden.
 * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param armseite bezeichnet den Arm, für den die Berechung durchgeführt
 * wird. Wenn dieser Wert '1' ist, so wird der rechte Armbetrachtet. Wen er
 * '0' ist, so wird der linke Arm betrachtet
 * @param offset Distanz, den die Zentrierrolle zum Ring haben soll
 * @param oeffnen gibt an, ob die Zentrierrollen geöffnet oder geschlossen
 * werden sollen. Im Falle dass sie geschlossen werden sollen, so muss dieser
 * Wert 0 sein. Wenn die Zentrierrollen geöffnet werden sollen, muss er 1
 * sein. Sollte dem nicht so sein, so wird in der Konsole ausgegeben, welcher
 * Wert stattdessen übergeben wurde.
 * @return Sollposition der Zentrierrollen rechts und links
 * @throw int eine Nummer an Hand dessen festgestellt werden kann, wo ein
 * Fehler aufgetreten ist. Die Nummer die Bezug zum Schuesselwalzen haben sind
 * in \link ibf_Schuessel.hpp \endlink als Macro aufgelistet.
 * */
int ibf_Schuessel::zentrierrollenPositionBerechnen(  
                                      struct Def_Ist_Inter Ist_Inter,
                                      int armseite,
                                      int offset,
                                      int oeffnen){
  int w,wsq,g,v;
  int beta2;

  try{


    switch(armseite)  {
      case LINKS:
        g =   Ist_Inter.Werkzeug.werkzeug_zl.dist_Hauptwalze_SenkrechteZentrierarmfixpunkt
            + Ist_Inter.Werkzeug.Durchmesser_HW
            + Ist_Inter.da/2;
        v =   Ist_Inter.Werkzeug.werkzeug_zl.dist_Kolbenende_Zentrierarmfixpunkt;
        break;
      case RECHTS:
        g =   Ist_Inter.Werkzeug.werkzeug_zr.dist_Hauptwalze_SenkrechteZentrierarmfixpunkt
            + Ist_Inter.Werkzeug.Durchmesser_HW
            + 0.5*Ist_Inter.da;
        v =   Ist_Inter.Werkzeug.werkzeug_zr.dist_Kolbenende_Zentrierarmfixpunkt;
        break;
      default:
        throw EXCEPTION_WRONG_ARGUMENT_5;  
    }

    if(oeffnen == OEFFNEN)
    {
      beta2 = ibf_Schuessel::berechneBeta2(	Ist_Inter,
	  										ZENTRIERROLLEN_OEFFNEN_OFFSET,
											armseite);
    }
    else if(oeffnen == SCHLIESSEN)
    {
      beta2 = ibf_Schuessel::berechneBeta2(	Ist_Inter,
	  										0,
											armseite);
    }
    else
    {
      throw (2);
    }
  }
  catch (const int exNummer){
    throw exNummer;
  }

  wsq =   pow(g,2)
        + pow(v,2)
        - 2* g * v * cos(beta2);
  w = (int)sqrt((double)wsq);

  return w;
}
/** Berechnet den Winkel am Fixpunkt des Zentriarms im Dreieck Mittelpunkt
 * Ring, Fixpunkt des Zentriarms und der Senkrechten zur Mittelachse, die
 * durch den Fixpunkt des Zentrierarms geht.
 *
 * Sowohl eine Grafik als auch die Herleitung der Berechung ist in "Finite element 
 * analysis of the ring rolling process with integrated closed-loop control,"
 * CIRP Annals - Manufacturing Technology, vol. 61/1, pp. 267-270, 2012
 * von V. Jenkouk, Hirt, G., Franzke, M., Zhang, T. zu finden.
 * @param Ist_Inter eine Sturkur vom Typ \link Def_Ist_Inter \endlink
 * @param offset Distanz, den die Zentrierrolle zum Ring haben soll
 * @param armseite bezeichnet den Arm, für den die Berechung durchgeführt
 * wird. Wenn dieser Wert '1' ist, so wird der rechte Zentrierarm betrachtet.
 * Wenn er '0' ist, so wird der linke Arm betrachtet
 * @return Winkel zwischen Senkrechte zur Mittelachse des Walzwerks, welche
 * durch den Fixpunkt geht, und Mittelpunkt des Ringes
 * \throw int Schmeißt eine Exception, wenn ein falsche Parameter für armseite
 * übergeben wurde.
 */
int ibf_Schuessel::berechneAlpha(	struct Def_Ist_Inter Ist_Inter,
                    				int offset,
                    				int armseite){
  
  int alpha,alpha1,alpha2;

  int r_a,a,c,b,e;

  r_a =   Ist_Inter.da
        + offset;
  
 
  switch(armseite){
    case LINKS:
      a = 	Ist_Inter.Werkzeug.werkzeug_zl.dist_Mittelachse_Zentrierarmfixpunkt;
      c =   0.5*Ist_Inter.Werkzeug.werkzeug_zl.durchmesser_zr
            + offset
            + 0.5*Ist_Inter.da;
      b = 	Ist_Inter.Werkzeug.werkzeug_zl.dist_Fixpunkt_Zentrierrolle;
      e =   Ist_Inter.Werkzeug.werkzeug_zl.dist_Hauptwalze_SenkrechteZentrierarmfixpunkt 
            + Ist_Inter.Werkzeug.Durchmesser_HW;
      break;
    case RECHTS: 
      a = 	Ist_Inter.Werkzeug.werkzeug_zr.dist_Mittelachse_Zentrierarmfixpunkt;
      c =   0.5*Ist_Inter.Werkzeug.werkzeug_zr.durchmesser_zr
            + offset
            + 0.5*Ist_Inter.da;
      b = 	Ist_Inter.Werkzeug.werkzeug_zr.dist_Fixpunkt_Zentrierrolle;
      e =   Ist_Inter.Werkzeug.werkzeug_zr.dist_Hauptwalze_SenkrechteZentrierarmfixpunkt 
            + Ist_Inter.Werkzeug.Durchmesser_HW;
      break;
    default: throw 1;
  }
  
  alpha1 = atan((e+r_a)/a);
  


  int zaehler = pow(a,2) + pow((e+r_a),2)+pow(b,2) - pow((c+r_a+offset),2);
  int nenner =  2*b
                * sqrt(pow(a,2)+pow((e+r_a),2));

  alpha2 = acos(zaehler/nenner);

  alpha = alpha1 + alpha2;

  return alpha;

}
/** Berechnet den Winkel zwischen einer Parallelen der Mittelachse des
 * Walzwerks, welche durch den Fixpunkt des Kolbens geht, und der Strecke vom
 * Fixpunkt des Kolbens zum Fixpunkt des Zentrierarms.
 *
 * Sowohl eine Grafik als auch die Herleiung der Berechnung ist in "Finite
 * elemente - analysis of the ring rolling process with integrated closed-loop
 * control" CIRP Annals - Manufacturing Technology, vol. 61/1, pp. 267-270, 2012
 * von V. Jenkouk, Hirt, G., Franzke, M., Zhang, T. zu finden.
 * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param armseite bezeichnet den Arm, für den die Berechung durchgeführt
 * wird. Wenn dieser Wert '1' ist, so wird der rechte Zentrierarm betrachtet.
 * Wenn er '0' ist, so wird der linke Arm betrachtet
 * @return Winkel zwischen einer Parallelen der Mittelachse des Walzwerks,
 * welche durch den Fixpunkt des Kolbens geht, und dem der Strecke vom
 * Fixpunkt des Kolbens zum Fixpunkt des Zentrierarms.
 * @throw int Fehlercode \link EXCEPTION_WRONG_ARGUMENT_4 \endlink, da ein
 * ungültiger Wert für den Parameter 'armseite' vorliegt.
 *
 */
int ibf_Schuessel::berechneBeta1(  struct Def_Ist_Inter Ist_Inter,
                    int armseite){
  int a,u,p;
  
  switch(armseite){
    case LINKS:
	  a = Ist_Inter.Werkzeug.werkzeug_zl.dist_Mittelachse_Zentrierarmfixpunkt;
      u = Ist_Inter.Werkzeug.werkzeug_zl.dist_Mittelachse_Kolbenfixpunkt;
	  p = Ist_Inter.Werkzeug.werkzeug_zl.dist_Kolben_Zentrierarm;
      break;
    case RECHTS:
	  a = Ist_Inter.Werkzeug.werkzeug_zr.dist_Mittelachse_Zentrierarmfixpunkt;
      u = Ist_Inter.Werkzeug.werkzeug_zr.dist_Mittelachse_Kolbenfixpunkt;
	  p = Ist_Inter.Werkzeug.werkzeug_zr.dist_Kolben_Zentrierarm;
      break;
    default:
      throw EXCEPTION_WRONG_ARGUMENT_4;
  }

  int zaehler =   a
                - u;
  int nenner = p;

  int beta1 = atan(zaehler/nenner);

  return beta1;
      
}

/** Berechnet den Winkel zwischen der Verbindung Kolben-Fixpunkt des
 * Zentrierarms und der Strecke Fixpunkt des Kolbens - Fixpunkt des
 * Zentrierarms.
 *
 * Sowohl eine Grafik als auch die Herleiung der Berechnung ist in "Finite
 * elemente - analysis of the ring rolling process with integrated closed-loop
 * control" CIRP Annals - Manufacturing Technology, vol. 61/1, pp. 267-270, 2012
 * von V. Jenkouk, Hirt, G., Franzke, M., Zhang, T. zu finden.
 * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param offset Abstand zum Ring, den die Zentrierrolle halten soll
 * @param armseite bezeichnet den Arm, für den die Berechung durchgeführt
 * wird. Wenn dieser Wert '1' ist, so wird der rechte Zentrierarm betrachtet.
 * Wenn er '0' ist, so wird der linke Arm betrachtet
 * @return Den Winkel zwischen den Strecken Endekolben-Fixpunk des
 * Zentrierarms und Fixpunkt des Kolbens-Fixpunkt des Zentrierarms.
 * \throw int Leitet die Exceptions mit dem Fehlercode 
 * \link EXCEPTION_WRONG_ARGUMENT_1 \endlink und
 * \link EXCEPTION_WRONG_ARGUMENT_3 \endlink der Methode 
 * \link berechneBeta3 \endlink und 
 * \link EXCEPTION_WRONG_ARGUMENT_4 \endlink der Methode 
 * \link berechneBeta1 \endlink weiter.*/
int ibf_Schuessel::berechneBeta2(  struct Def_Ist_Inter Ist_Inter,
                    int offset,
                    int armseite) {
  int beta1,beta3;

  try{
    beta1 = ibf_Schuessel::berechneBeta1(Ist_Inter,armseite);
    beta3 = ibf_Schuessel::berechneBeta3(Ist_Inter,offset,armseite);
  }
  catch (const int exNummer)
  {
    throw;
  }

  int beta2 = 90 - beta1 - beta3;

  return beta2;
}


/** Berechnet den Winkel zwischen Senkrechten zur Mittelachse, welche durch
 * den Fixpunkt des Zentrierarms geht und der Verbindung vom Kolbenende bis
 * zum Fixpunkt des Zentrierarms.
 *
 * Sowohl eine Grafik als auch die Herleiung der Berechnung ist in "Finite
 * elemente - analysis of the ring rolling process with integrated closed-loop
 * control" CIRP Annals - Manufacturing Technology, vol. 61/1, pp. 267-270, 2012
 * von V. Jenkouk, Hirt, G., Franzke, M., Zhang, T. zu finden.
 * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param offset Distanz, den die Zentrierrolle zum Ring haben soll
 * @param armseite bezeichnet den Arm, für den die Berechung durchgeführt
 * wird. Wenn dieser Wert '1' ist, so wird der rechte Zentrierarm betrachtet.
 * Wenn er '0' ist, so wird der linke Arm betrachtet
 * @return Den Winkel zwischen den Strecken Endekolben-Fixpunk des
 * Zentrierarms und Fixpunkt des Kolbens-Fixpunkt des Zentrierarms.
 * \throw int Leitet die Exceptions mit dem Fehlercode
 * \link EXCEPTION_WRONG_ARGUMENT_1 \endlink von der Methode 
 * \link berechneAlpha \endlink und 
 * \link EXCEPTION_WRONG_ARGUMENT_3 \endlink von der Methode
 * \link berechneBeta4 \endlink weiter.*/
int ibf_Schuessel::berechneBeta3(  struct Def_Ist_Inter Ist_Inter,
                    int offset,
                    int armseite) {
  int alpha, beta4;
      
  try {
    alpha = ibf_Schuessel::berechneAlpha(Ist_Inter,offset,armseite);
    beta4 = ibf_Schuessel::berechneBeta4(Ist_Inter,armseite);
  }
  catch (const int exNummer){
    throw;
  }	     
  int beta3 = beta4 - alpha;

  return beta3;
      
}

/** Berechnet den Winkel zwischen Ende des Kolbens zum Fixpunkt des Zentrierarmes
 * und Fixpunkt des Zentrierarmes zum Mittelpunkt der Zentrierrolle.
 *
 * Sowohl eine Grafik als auch die Herleiung der Berechnung ist in "Finite
 * elemente - analysis of the ring rolling process with integrated closed-loop
 * control" CIRP Annals - Manufacturing Technology, vol. 61/1, pp. 267-270, 2012
 * von V. Jenkouk, Hirt, G., Franzke, M., Zhang, T. zu finden.
 * @param Ist_Inter eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @param armseite bezeichnet den Arm, für den die Berechung durchgeführt
 * wird. Wenn dieser Wert '1' ist, so wird der rechte Zentrierarm betrachtet.
 * Wenn er '0' ist, so wird der linke Arm betrachtet
 * @return Den Winkel zwischen den Strecken Endekolben-Fixpunk des
 * Zentrierarms und Fixpunkt des Zentrierarms-Mittelpunkt der Zentrierrolle
 * \throw int Schmeißt eine Exception, wenn ein falsche Parameter für armseite
 * übergeben wurde.*/
int ibf_Schuessel::berechneBeta4(  struct Def_Ist_Inter Ist_Inter,
                    int armseite) {
  int v, b, q;

  switch(armseite){
    case LINKS:
      v = Ist_Inter.Werkzeug.werkzeug_zl.dist_Kolbenende_Zentrierarmfixpunkt;
      b = Ist_Inter.Werkzeug.werkzeug_zl.dist_Fixpunkt_Zentrierrolle;
      q = Ist_Inter.Werkzeug.werkzeug_zl.dist_Kolbenende_Zentrierrolle;
      break;
    case RECHTS:
      v = Ist_Inter.Werkzeug.werkzeug_zr.dist_Kolbenende_Zentrierarmfixpunkt;
      b = Ist_Inter.Werkzeug.werkzeug_zr.dist_Fixpunkt_Zentrierrolle;
      q = Ist_Inter.Werkzeug.werkzeug_zr.dist_Kolbenende_Zentrierrolle;
      break;
    default: throw EXCEPTION_WRONG_ARGUMENT_3;
  }

  int zaehler =   pow(v,2)
                + pow(b,2)
                - pow(q,2);
  int nenner =    2
                * b
                * v;
  int beta4 = acos(zaehler/nenner);
  
  return beta4;

}


/** Überprüft, ob der Ring klettert.
 * Die Aussage kann mit Hilfe des Ringaussendruchmessers getroffen werden.
 * Der aktuelle Ringaussendruchmesser wird mit dem verglichen, welcher vor
 * Beginn der Schüsselwalzung vor lag(
 * \link Def_IBF_Schuessel::ringDurchmesserKlettern \endlink). Der aktuelle
 * Ringdurchmesser wird durch die Funktion 
 * \link ibf_Schuessel::berechneRingdurchmesser \endlink berechnet.
 * @param Ist_IBF [in] eine Struktur vom Typ 
 * \link Def_IBF_Allgemein_IST \endlink
 * @param Ist_Inter [in] eine Struktur vom Typ \link Def_Ist_Inter \endlink
 * @return 1 genau dann wenn der Ring klettert, sonst 0.
 */
int ibf_Schuessel::ringKlettert( struct Def_IBF_Allgemein_IST *Ist_IBF,
                  struct Def_Ist_Inter Ist_Inter) {

  int klettert;
  
  if(ibf_Schuessel::berechneRingdurchmesser(Ist_IBF,Ist_Inter) 
  		< Ist_IBF->IBF_Schuessel.ringDurchmesserKlettern)
  {
    klettert = 1;
  }
  else
  {
    klettert = 0;
  }

  Ist_IBF->IBF_Schuessel.ringKlettert = klettert;

  return klettert;

}
