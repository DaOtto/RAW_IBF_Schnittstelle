#include "rpw.hpp"
#include "iniFile.h"
#include <math.h>



/*-----------------------------------------------------------------------*/
/*                                                                       */
/*                    IBF DW-Regelungsfunktionen                         */
/*                                                                       */
/*             Hier alle Funktionen aus DA Jenkouk entstanden sind       */
/*             -Axialprofilieren -> DW anhand vom Weg positionieren      */
/*             - Version 1. Weginfo generieren                           */
/*             05.05.08 V. Jenkouk, D.Michl                              */
/*                                                                       */
/*-----------------------------------------------------------------------*/



/** Berechnen der Messwerte in \link Def_IBF_Allgemein_SOLL \endlink
* der \link Def_DW_Regelung_DA_Jenkouk \endlink mit Hilfe von 
\link Def_IBF_Allgemein_IST \endlink
* @param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
* @param *Soll_IBF ein Zeiger auf eine Struktur vom Typen \link Def_IBF_Allgemein_SOLL \endlink */
void MS_Daempfer(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF)
{
	// Lokale Variablen
	float Kpf = 1.0F;
	float T1f = 1.0F; // Filterzeit
	float Ta = 0.1F;  // Abtastzeit 

	Soll_IBF->DW_Regelung.Messwert_A_mf = (Kpf * Ist_IBF.DW_Regelung.Messwert_A + ((T1f / Ta) *
																				   Soll_IBF->DW_Regelung.
																				   Messwert_A_alt_mf)) / ((T1f / Ta) +
																										  1);
	Soll_IBF->DW_Regelung.Messwert_A_alt_mf = Soll_IBF->DW_Regelung.Messwert_A_mf;

	Soll_IBF->DW_Regelung.Messwert_A_unten_mf = (Kpf * Ist_IBF.DW_Regelung.Messwert_A_unten + ((T1f / Ta) *
																							   Soll_IBF->DW_Regelung.
																							   Messwert_A_unten_alt_mf
																							   )) / ((T1f / Ta) + 1);
	Soll_IBF->DW_Regelung.Messwert_A_unten_alt_mf = Soll_IBF->DW_Regelung.Messwert_A_unten_mf;



}

void RS_nach_Messwert_Fahren(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF)
{

	Soll_IBF->DW_Regelung.Messwertdifferenz = Soll_IBF->DW_Regelung.Messwert_A_mf -
		Soll_IBF->DW_Regelung.Startmesswert;

	Soll_IBF->RS_Pos = Ist_IBF.Rohling_s_angefahren + Soll_IBF->DW_Regelung.Messwertdifferenz + 4.0F;

}

// Funktionen mit denen Messwerte ermittelt und aufbereitet werden.......    



/** Berechnet die Wanddicke wie in der Doktorarbeit von W. Jenkouk beschrieben
* (Kapitel 4.2.2).
*@param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
*@param *Soll_IBF ein Zeiger auf eine Struktur vom Typ \link Def_IBF_Allgemein_SOLL \endlink
*/
void Axial_Wanddicke_bestimmen(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF)
{

	// Definieren von lokalen Variablen
	float ri_block1 = 0.0F;
	float ri_block2 = 0.0F;

	// ri_block1 = Ist_IBF.DW_Regelung.Abstand_C - (Soll_IBF->DW_Regelung.Messwert_A_mf - Ist_IBF.DW_Regelung.Tastrollen_Radius) * cos_zeta;
	ri_block1 = Ist_IBF.DW_Regelung.Abstand_C - Soll_IBF->DW_Regelung.Messwert_A_mf * cos_zeta;


	//  ri_block2 = Ist_IBF.AG_Pos + Ist_IBF.DW_Regelung.Offset - 0.5 *Ist_IBF.da  - ( Soll_IBF->DW_Regelung.Messwert_A_mf - Ist_IBF.DW_Regelung.Tastrollen_Radius) * sin_zeta;

	ri_block2 = Ist_IBF.AG_Pos + Ist_IBF.DW_Regelung.Offset - 0.5F * Ist_IBF.da
		- Soll_IBF->DW_Regelung.Messwert_A_mf * sin_zeta;


	Soll_IBF->DW_Regelung.ri_block1 = ri_block1;
	Soll_IBF->DW_Regelung.ri_block2 = ri_block2;

	// Soll_IBF->DW_Regelung.ri = sqrt( pow(ri_block1, 2) + pow(ri_block2, 2) ) ; // Wurzel aus .....
	Soll_IBF->DW_Regelung.ri = Ist_IBF.DW_Regelung.Tastrollen_Radius + sqrt(pow(ri_block1, 2) + pow(ri_block2, 2)); // Wurzel aus .....

	Soll_IBF->DW_Regelung.Wanddicke_berechnet = 0.5F * Ist_IBF.da -	Soll_IBF->DW_Regelung.ri;    /*Ist_Inter->da ist das der Aussendurchmesser*/
	Soll_IBF->DW_Regelung.Wanddicke_MS = Soll_IBF->DW_Regelung.Messwert_A_mf - Soll_IBF->DW_Regelung.Messwert_A_unten_mf;

	//Testoffset
	Soll_IBF->DW_Regelung.TestOffset = sqrt(pow(0.5F * Ist_IBF.di - Ist_IBF.DW_Regelung.Tastrollen_Radius,2) - pow(ri_block1, 2)) - (ri_block2 - Ist_IBF.DW_Regelung.Offset);

}



/** Abbildung 4-9 (Winkel) DA Jenkouk
* Winkel zwischen Walzwerksachse und Verbindungslinie Mittelpunktmessrolle-Mittelpunktring
*
*@param[in] Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
*@param[in] *Soll_IBF ein Zeiger auf eine Struktur vom Typ \link Def_IBF_Allgemein_SOLL \endlink */
void Alpha(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF)
{
	float Hilf_k = 0.0F;
	float Hilf_w = 0.0F;
	float Hilf_l = 0.0F;
	float Hilf_z = 0.0F;

	Hilf_k = Ist_IBF.DW_Regelung.Abstand_C - (Soll_IBF->DW_Regelung.Messwert_A_mf -
											  Ist_IBF.DW_Regelung.Tastrollen_Radius) * cos_zeta;

	Hilf_w = (Soll_IBF->DW_Regelung.Messwert_A_mf - Ist_IBF.DW_Regelung.Tastrollen_Radius) * sin_zeta;

	Hilf_l = Ist_IBF.AG_Pos + Ist_IBF.DW_Regelung.Offset;
	Hilf_z = Hilf_l - 0.5F * Ist_IBF.da - Hilf_w;

	Soll_IBF->DW_Regelung.Alpha = atan(Hilf_k / Hilf_z) * 180 / PI; /*Hier Taylorreihe für arctan rein!!!!*/

}

/** Winkel zwischen der Walzwerkachse und der Verbindungslinie Ringmittelpunkt und Beruehrungspunkt 
  * zwischen Innenring und Dornwalze (Eingang Radialwalzspalt) 
  * @param[in] Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink 
  * @param[in] *Soll_IBF ein Zeier auf eine Struktur vom Typ \link Def_IBF_Allgemein_SOLL \endlink */
void Gamma(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF)
{
	// Lokale Variablen
	float Hilf_t = 0.0F;
	float Hilf_p = 0.0F;
	float Hilf_tp = 0.0F;

	Hilf_t = 0.5F * Ist_IBF.da - Ist_IBF.Wanddicke_Ist - 0.5F * Ist_IBF.DW_Regelung.DW_Durchmesser;

	Hilf_p = (pow(Soll_IBF->DW_Regelung.ri, 2) - pow(0.5F * Ist_IBF.DW_Regelung.DW_Durchmesser, 2) - pow(Hilf_t,2)) / (2 * Hilf_t);
	Hilf_tp = Hilf_t + Hilf_p;

	Soll_IBF->DW_Regelung.Gamma = acos(Hilf_tp / Soll_IBF->DW_Regelung.ri) * 180 / PI;

}

/** Berechnet den Winkel Beta nach der Zeichnung in der DA von Jenkouk 
  * Abbildung 4-9 (Winkel). Beta ist also 
      180° - aplha - gamma
  *@param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
  *@param *Soll_IBF ein Zeiger auf eine Struktur vom Typ 
  * \link Def_IBF_Allgemein_SOLL \endlink
  */
void Beta(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF)
{
	Alpha(Ist_IBF, Soll_IBF);
	Gamma(Ist_IBF, Soll_IBF);


	Soll_IBF->DW_Regelung.Beta = 180.0F - Soll_IBF->DW_Regelung.Alpha - Soll_IBF->DW_Regelung.Gamma;
}



/** Berechnet die Zeit, bis der Punkt, welcher gerade vom Messsystem erfasst
  * wurde in den Radialwalzspalt gelangt.
  *
  *@param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
  *@param *Soll_IBF ein Zeiger auf eine Struktur vom Typ
  * \link Def_IBF_Allgemein_SOLL \endlink
  */
void T_Einlauf(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF)
{

	Beta(Ist_IBF, Soll_IBF);

	Soll_IBF->DW_Regelung.T_Einlauf = (Soll_IBF->DW_Regelung.Beta * Ist_IBF.da *
									   PI) / (360.0F * Ist_IBF.DW_Regelung.U_v_HW);

}




// Funktionen mit denen die Regelung der DW realisiert wird....




/** Diese Funktion hat keinen Inhalt
*@param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
*@param Soll_IBF ein Zeiger auf eine Struktur vom Typ 
*  \link Def_IBF_Allgemein_SOLL \endlink
*/
void T_V(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF) {}
/*--------Regelprogramm-------------------------------------------------------*/

/** Steuert das Zusammenspiel von Messsystem und Dornwalze.
  *
  * Diese Methode wird derzeit nicht genutzt 
  *
  * @param[in] Ist_IBF eine Struktur vorm Typ \link Def_IBF_Allgemein_IST \endlink
  * @param[in] *Soll_IBF ein Zeiger auf eine Struktur vom Typ 
  * \link Def_IBF_Allgemein_SOLL \endlink
  */
void DW_Regelalgo(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF)
{
	//Deklariere lokale Variablen

	float Delta_T;           // Aktuelle Zeitdifferenz wenn Dornwalze nach Aufnahem des Messsignals mit der Positionierung starten muss
	//int Anzahl_Zeitschritte; // Differenz der Anzahl von Regelzyklen



	Delta_T = Soll_IBF->DW_Regelung.T_Einlauf - Soll_IBF->DW_Regelung.T_Verzoegerung;

	Soll_IBF->DW_Regelung.Anzahl_Zeitschritte = (int)(Delta_T / (regel_zyklus_fak * 0.1F));



	// Verchieben des Arrays, damit Messwertposition um -1 reduziert wird (entsp. Zeitdauer vom Regelzyklus bis Messpos am DW anliegt)
	for (int i = 0; i <= (Arraygroesse - 2); i++)
	{
		Soll_IBF->DW_Regelung.DW_soll_Pos[i] = Soll_IBF->DW_Regelung.DW_soll_Pos[i + 1];
	}


	Soll_IBF->DW_Regelung.DW_soll_Pos[Arraygroesse - 1] = 0; //Letztes Element des Arrays muss Null sein

	Soll_IBF->DW_Regelung.DW_soll_Pos[Soll_IBF->DW_Regelung.Anzahl_Zeitschritte] = Soll_IBF->DW_Regelung.
		Wanddicke_berechnet; // Fülle Element mit Wanddicke auf

	if (Soll_IBF->DW_Regelung.DW_soll_Pos[0] == 0)
		Soll_IBF->RS_Pos = Ist_IBF.RS_Pos;
	else
		Soll_IBF->RS_Pos = Soll_IBF->DW_Regelung.DW_soll_Pos[0] +
			2.0F;
			/* Da MS starke Schwankungen von max. 2 mm aufweist, wird hiermit sichergestellt, dass DW keinen Kontakt zum RIng hat....*/

}


// Hauptprogramm des Regelalgorithmus der im rpw.cpp eingebunden werden kann

/** Regelt das Verhalten der Dornwalze.
  * In regelmäßigen Abständen werden \link MS_Daempfer \endlink und 
  * \link Axial_Wanddicke_bestimmen \endlink aufgerufen. Ab dem fünften
  * Methodenaufruf, werden zusätzlich die Methoden \link T_Einlauf \endlink,
  * \link T_V \endlink aufgerufen. Somit wird einer Berechnung der Zeit, die
  * ein Punkt benütigt, um vom Messsystem zum Raidalwalzspalt zu gelangen,
  * berechnet.
  *@param Ist_IBF eine Struktur vom Typ \link Def_IBF_Allgemein_IST \endlink
  *@param *Soll_IBF ein Zeiger auf eine Struktur vom Typ
  * \link Def_IBF_Allgemein_SOLL \endlink
  */
void DA_Jenkouk_Regler(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL* Soll_IBF)
{
	switch (Ist_IBF.Flag.DA_Jenkouk_DW_Regelung)
	{
	case 0:
		Soll_IBF->RS_Pos = Ist_IBF.RS_Pos;
		break;

	case 1:
		// Einlesen des gefilterten Messsignales
		MS_Daempfer(Ist_IBF, Soll_IBF);
		// Berechne die Wanddicke
		Axial_Wanddicke_bestimmen(Ist_IBF, Soll_IBF);

		if (Soll_IBF->DW_Regelung.Aufrufzeit_Regelzykl >= (regel_zyklus_fak - 1))
		{
			//Berechne die Einlaufzeit
			T_Einlauf(Ist_IBF, Soll_IBF);
			//Berechen die Verzögerungszeit
			T_V(Ist_IBF, Soll_IBF);
			//Berechen die DW-Zustellung
			if (Ist_IBF.Flag.DA_Jenkouk_Messen_ohne_Fahren == 1)
			{
				RS_nach_Messwert_Fahren(Ist_IBF, Soll_IBF);
			}

			Soll_IBF->DW_Regelung.Aufrufzeit_Regelzykl = -1;
		}
		Soll_IBF->DW_Regelung.Aufrufzeit_Regelzykl++;
		break;

	default:
		break;
	}

	//Test, ob Funktion aufgerufen wird....
	if (Soll_IBF->DW_Regelung.Funktios_Iter >= 500)
	{
		Soll_IBF->DW_Regelung.Funktios_Iter = 0;
	}
	Soll_IBF->DW_Regelung.Funktios_Iter++;

}

