/*--DATEI HEADER---------------------------------------------------------------
;   Dateiname       : IBF_Schuessel_Form.cpp
;   Version         : V1.00a
;   Beschreibung    : Ermittlung der Ringlage und -Geometrie beim Schuesselwalzen
;	Plattform		: RMOS3,WIN32				  
;
;                    
;
;   Autor           : D.Otto
;   date            : Dezember 2014
;
-----------------------------------------------------------------------------*/
#include "rpw.hpp"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Funktion zur Bestimmung der aktuellen Walzform beim Schuesselwalzen
//////////////////////////////////////////////////////////////////////

int	Schuessel_Form_IST(			Def_IBF_Allgemein_IST&	Ist_IBF,
						const	Def_Ist_Inter&			Ist_Inter )
{
	Def_Schuessel_Walzform& WF = Ist_IBF.Schuessel.Walzform ;
	
	WF.da	= Ist_Inter.tr_pos+Ist_Inter.ag_pos_real-Ist_Inter.Werkzeug.l_fehlende_spitze;

	// Bei Testfahrt ohne Ring, Tastrollenvorgabe aus IBF_Data.ini verwenden
	if (Ist_IBF.Schuessel.Test.Flag_oRing) WF.da = Ist_IBF.Schuessel.Test.Tastrolle_da;

	// Simuliertes Ringwachstum im Testmodus
	if (Ist_IBF.Schuessel.Test.Flag_oRing) WF.da = WF.da * (1 + Ist_IBF.K_Iter*0.0003F);

	
	//////////////////////////////////////////////////////////////
	// Puffern und filtern der Sensorwerte durch Mittelwertbildung
	//////////////////////////////////////////////////////////////

	WF.cursor					= Ist_IBF.Iter % PUFF_LEN;
	WF.TR_puffer[WF.cursor]		= WF.da;
	WF.DRx_puffer[WF.cursor]	= Ist_IBF.DRR_Param.DrR_E.PosXY.x;
	WF.DRy_puffer[WF.cursor]	= Ist_IBF.DRR_Param.DrR_E.PosXY.y;
	
	WF.da_mf	= 0.0F;
	WF.DRx_mf	= 0.0F;
	WF.DRy_mf	= 0.0F;

	for ( int i = PUFF_LEN ; --i >= 0 ;  ) 
	{
		WF.da_mf	+= WF.TR_puffer[i];
		WF.DRx_mf	+= WF.DRx_puffer[i];
		WF.DRy_mf	+= WF.DRy_puffer[i];
	}

	WF.da_mf	= WF.da_mf	/ PUFF_LEN;
	WF.DRx_mf	= WF.DRx_mf	/ PUFF_LEN;
	WF.DRy_mf	= WF.DRy_mf	/ PUFF_LEN;
	
	////////////////////////////////////////////////////////////////////////////////////
	// Berechnung der Radien der Projektion des Ringes (Schuessel) in der Walztischebene
	////////////////////////////////////////////////////////////////////////////////////

	WF.RingGeo.a = WF.da_mf / 2.0F;		// Halbachse 'a' der elliptischen Ringprojektion (Laengs)
	
	// Berechnung der langen Halbachse b, wenn Druckrolle Kontakt zum Ring hat.
	if(Ist_IBF.Flag.DRE_kraft_anfahren_erreicht)
	{
		float al		= asin( ( WF.DRx_mf / WF.RingGeo.a ) - 1.0F );
		WF.RingGeo.b	= fabs( WF.DRy_mf / cos( al ) );	// Halbachse 'b' der elliptischen Ringprojektion (Quer)
	}
	else
	{
		WF.RingGeo.b = WF.RingGeo.a;// * 1.065F; // 20° Kletterwinkel
		
		// Simuliertes Ringklettern im Testmodus
		if (Ist_IBF.Schuessel.Test.Flag_oRing) WF.RingGeo.b = WF.RingGeo.a * (1 + min(0.065F,Ist_IBF.K_Iter*0.0001F));
	}
	
	
	///////////////////////////////////////////////////////////////
	// Festlegen der Lage der Ringprojektion auf die Walztischebene
	///////////////////////////////////////////////////////////////

	WF.RingGeo.M.x = WF.da_mf/2.0F;	// Mittelpunkt X
	WF.RingGeo.M.y = 0.0;			// Mittelpunkt Y

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Berechnung des aktuellen Kletterwinkels
	// Verhaeltnis der Radien a/b. Wird fuer einige berechnungen benoetigt, und hier vorberechnet
	/////////////////////////////////////////////////////////////////////////////////////////////

	float a_zu_b		= WF.RingGeo.a / WF.RingGeo.b;
	WF.Kletterwinkel	= acos(min(1.0F,a_zu_b));
	
	/////////////////////////////////////////////////////////
	//Berechnung der momentanen Wandbreite sm des Ringprofils
	/////////////////////////////////////////////////////////

	// Wanddicke sm des Ringprofils aus Axialwalzspalthoehe, Volumenkonstanz und Kletterwinkel berechnen
	
	WF.hm	= min(Ist_IBF.ASO_Pos , Ist_IBF.Schuessel.Vorform.hm_mm);	// Aktuelle Hoehe des Ringprofils
	d3	a	= {};														// double[3] , Koeffizientenvektor
	d2	l	= {};														// double[2] , Loesungsvektor
	
	//a[2]	=	-PI*WF.hm*pow(cos(WF.Kletterwinkel),2);
	//a[1]	=	2.0F*PI*WF.hm*WF.RingGeo.b*cos(WF.Kletterwinkel) - PI*pow(WF.hm,2)*sin(WF.Kletterwinkel)*cos(WF.Kletterwinkel);
	//a[0]	= 	-Ist_IBF.Schuessel.Vorform.Volumen;

	a[2]	=	a_zu_b*a_zu_b;
	a[1]	=	WF.hm*sin(WF.Kletterwinkel)*a_zu_b - WF.da_mf;
	a[0]	= 	Ist_IBF.Schuessel.Vorform.Volumen / (PI*WF.hm);
	
	LF2( l , a );	
	
	// die relevante Loesung ist die betragsmaessig kleinere ->
	WF.sm = (float)min( l[0] , l[1] );
	
	////////////////////////////////////////
	// Berechnung der aktuellen Kletterhoehe
	////////////////////////////////////////

	WF.Kletterhoehe		= 2.0F * WF.RingGeo.b * sin( WF.Kletterwinkel ) + WF.hm;

	/////////////////////////////
	// Positionsbereich Dornwalze
	/////////////////////////////

	WF.dw_min_Pos = WF.sm * cos( 2.0F * WF.Kletterwinkel ) + WF.hm * sin( 2.0F * WF.Kletterwinkel );
	WF.dw_max_Pos = WF.da_mf - WF.sm - Ist_Inter.Werkzeug.Durchmesser_DW;

	////////////////////////////////////////////////////////////
	// Effektive Radien zur Berechnung der Axialwalzendrehzahlen
	////////////////////////////////////////////////////////////

	WF.r_eff_u = WF.RingGeo.b;
	WF.r_eff_o = WF.r_eff_u - WF.hm * sin( WF.Kletterwinkel );
	
	return 0;
};

int Vorform_geo_berechnen( Def_IBF_Allgemein_IST& Ist_IBF )
{
	// Vorformvolumen berechnen in [mm^3]. Dichte und Masse sind in IBF_Data.ini definiert.
	Ist_IBF.Schuessel.Vorform.Volumen = Ist_IBF.Schuessel.Vorform.Masse_kg / Ist_IBF.Schuessel.Vorform.Dichte_warm * 1000000.0F;

	// Mittlere Profilbreite [mm] berechnen.
	float di = sqrt(pow(Ist_IBF.Schuessel.Vorform.da_mm,2)-Ist_IBF.Schuessel.Vorform.Volumen/(PI*Ist_IBF.Schuessel.Vorform.hm_mm/4.0F));

	Ist_IBF.Schuessel.Vorform.sm_mm = (Ist_IBF.Schuessel.Vorform.da_mm - di) / 2.0F;
	
	return 0;
};


