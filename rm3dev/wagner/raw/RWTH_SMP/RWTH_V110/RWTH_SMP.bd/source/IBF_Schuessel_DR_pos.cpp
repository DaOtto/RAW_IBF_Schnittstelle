/*--DATEI HEADER---------------------------------------------------------------
;   Dateiname       : IBF_Schuessel_DR_pos.cpp
;   Version         : V1.00a
;   Beschreibung    : Sollwertbestimmung der Druckrollen
					  Istwertbestimmung der Druckrollen
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

///////////////////////////////////////////////////////
// Transformierung der Ist_Inter werte in Ist_IBF werte
///////////////////////////////////////////////////////

Def_IBF_Ist_DRR	DRR_trans_IST(const Def_Ist_Inter& Ist_Inter , Def_IBF_Allgemein_IST& Ist_IBF)
{
	Def_IBF_Ist_DRR ret = Ist_IBF.DRR_Param;

	// Messachse normieren
	float	norm_pos_A =  Ist_Inter.DRR_Param.DrR_A.Pos - Ist_IBF.DRR_Param.Dist_VK_NUL_A,
			norm_pos_E =  Ist_Inter.DRR_Param.DrR_E.Pos - Ist_IBF.DRR_Param.Dist_VK_NUL_E;

	// Ortsvektor der Druckrollenspur bei aktuelle AG-Position (Auslaufseite)
	punkt2D_t	Pu_A = { PREFX_A + Ist_Inter.ag_pos_real ,
						 PREFY_A };

	// Richtungsvektor der Druckrollenspur (Pmax - Pref) (Auslaufseite)
	vektor2D_t	Vr_A = { PMAXX_A - PREFX_A ,	// dx
						 PMAXY_A - PREFY_A };	// dy
	
	// Berechnung der Koordinaten der NULL-Position (Auslaufseite)
	punkt2D_t	Pnul_A = {	Pu_A.x + ( Vr_A.dx / Norm( Vr_A ) ) * Ist_IBF.DRR_Param.Dist_VK_NUL_A ,
							Pu_A.y + ( Vr_A.dy / Norm( Vr_A ) ) * Ist_IBF.DRR_Param.Dist_VK_NUL_A };

	// Ortsvektor der Druckrollenspur bei aktuelle AG-Position (Einlaufseite)
	punkt2D_t	Pu_E = { PREFX_E + Ist_Inter.ag_pos_real ,
						 PREFY_E };

	// Richtungsvektor der Druckrollenspur (Pmax - Pref) (Einlaufseite)
	vektor2D_t	Vr_E = { PMAXX_E - PREFX_E ,	// dx
						 PMAXY_E - PREFY_E };	// dy
	
	// Berechnung der Koordinaten der NULL-Position (Einlaufseite)
	punkt2D_t	Pnul_E = {	Pu_E.x + ( Vr_E.dx / Norm( Vr_E ) ) * Ist_IBF.DRR_Param.Dist_VK_NUL_E ,
							Pu_E.y + ( Vr_E.dy / Norm( Vr_E ) ) * Ist_IBF.DRR_Param.Dist_VK_NUL_E };

	//////////////////////////////////////////////////////////////
	// Berechnung der Ist-Position der Druckrollen in x,y bzgl. HW
	//////////////////////////////////////////////////////////////

	//Positionen der Druckrollenachsen berechnen 
	punkt2D_t P_achse_A = {	Pnul_A.x + ( Vr_A.dx / Norm( Vr_A ) ) * norm_pos_A, 
							Pnul_A.y + ( Vr_A.dy / Norm( Vr_A ) ) * norm_pos_A };

	punkt2D_t P_achse_E = {	Pnul_E.x + ( Vr_E.dx / Norm( Vr_E ) ) * norm_pos_E,
							Pnul_E.y + ( Vr_E.dy / Norm( Vr_E ) ) * norm_pos_E };
	
	/////////////////////////////////
	// Kontaktpunkt am Ring berechnen
	/////////////////////////////////
	
	ellipse_t Ring = Ist_IBF.Schuessel.Walzform.RingGeo; // aktuelle Geometrie der Ringprojektion
	
	// Verbindungsgerade Ringmitte/Druckrollenachse fuer Ein- und Auslaufseite
	gerade2D_t	PM_PR_A = { Ring.M.x				, Ring.M.y				,	// Ursprungspunkt
							P_achse_A.x - Ring.M.x	, P_achse_A.y - Ring.M.y }, // Richtungsvektor 
				PM_PR_E = { Ring.M.x				, Ring.M.y				,	// Ursprungspunkt
							P_achse_E.x - Ring.M.x	, P_achse_E.y - Ring.M.y }; // Richtungsvektor

	P2			SP_R_Av = {}, // Zwei Schnittpunkte Gerade/Ring Ausl.
				SP_R_Ev = {}; // Zwei Schnittpunkte Gerade/Ring Einl.

	punkt2D_t	SP_R_A	= {}, // relevanter Schnittpunkt Gerade/Ring Ausl.
				SP_R_E	= {}; // relevanter Schnittpunkt Gerade/Ring Einl.

	Schnittpunkt( SP_R_Av , PM_PR_A , Ring );
	Schnittpunkt( SP_R_Ev , PM_PR_E , Ring );
	
	// Relevanten Schnittpunkt auswählen. Liegt fuer Auslaufseite im 4.Quadranten der Ringkontur
	if ( ( SP_R_Av[0].y < 0.0F ) && ( SP_R_Av[0].x > Ring.M.x ) ) SP_R_A = SP_R_Av[0];
	if ( ( SP_R_Av[1].y < 0.0F ) && ( SP_R_Av[1].x > Ring.M.x ) ) SP_R_A = SP_R_Av[1];
	
	// Relevanten Schnittpunkt auswählen. Liegt fuer Einlaufseite im 1.Quadranten der Ringkontur
	if ( ( SP_R_Ev[0].y > 0.0F ) && ( SP_R_Ev[0].x > Ring.M.x ) ) SP_R_E = SP_R_Ev[0];
	if ( ( SP_R_Ev[1].y > 0.0F ) && ( SP_R_Ev[1].x > Ring.M.x ) ) SP_R_E = SP_R_Ev[1];
	
	///////////////////////////////////////
	// Kontaktpunkt an Druckrolle berechnen
	///////////////////////////////////////

	ellipse_t	Kreis_DrA = { { P_achse_A.x , P_achse_A.y } , 160.0F , 160.0F },
				Kreis_DrE = { { P_achse_E.x , P_achse_E.y } , 160.0F , 160.0F };
	P2			SP_Av = {}, // Zwei Schnittpunkte Gerade/Druckrolle Ausl.
				SP_Ev = {};	// Zwei Schnittpunkte Gerade/Druckrolle Einl.
	punkt2D_t	SP_A  = {},	// relevanter Schnittpunkt Gerade/Druckrolle Ausl.
				SP_E  = {};	// relevanter Schnittpunkt Gerade/Druckrolle Einl.
	
	Schnittpunkt( SP_Av , PM_PR_A , Kreis_DrA );
	Schnittpunkt( SP_Ev , PM_PR_E , Kreis_DrE );

	// Relevanten Schnittpunkt auswählen. Liegt fuer Auslaufseite im 2.Quadranten der Druckrollenkontur
	if ( ( SP_Av[0].y - Kreis_DrA.M.y > 0.0F ) && ( SP_Av[0].x - Kreis_DrA.M.x < 0.0F ) ) SP_A = SP_Av[0];
	if ( ( SP_Av[1].y - Kreis_DrA.M.y > 0.0F ) && ( SP_Av[1].x - Kreis_DrA.M.x < 0.0F ) ) SP_A = SP_Av[1];
	
	// Relevanten Schnittpunkt auswählen. Liegt fuer Einlaufseite im 3.Quadranten der Druckrollenkontur
	if ( ( SP_Ev[0].y - Kreis_DrE.M.y < 0.0F ) && ( SP_Ev[0].x - Kreis_DrE.M.x < 0.0F ) ) SP_E = SP_Ev[0];
	if ( ( SP_Ev[1].y - Kreis_DrE.M.y < 0.0F ) && ( SP_Ev[1].x - Kreis_DrE.M.x < 0.0F ) ) SP_E = SP_Ev[1];

	vektor2D_t	V_M_SPRo_A	= { SP_A.x   - Ring.M.x , SP_A.y   - Ring.M.y },
				V_M_SPRi_A	= { SP_R_A.x - Ring.M.x , SP_R_A.y - Ring.M.y },
				V_M_SPRo_E	= { SP_E.x   - Ring.M.x , SP_E.y   - Ring.M.y },
				V_M_SPRi_E	= { SP_R_E.x - Ring.M.x , SP_R_E.y - Ring.M.y };

	////////////////////////////////////////////////////////////////////
	// Uebergabe der berechneten Werte an Druckrollen-Parameter Struktur
	////////////////////////////////////////////////////////////////////

	// Druckrolle Einlaufseite
	ret.DrR_E.PosXY.x				= SP_E.x;
	ret.DrR_E.PosXY.y				= SP_E.y;
	ret.DrR_E.delta_Ring			= Norm( V_M_SPRo_E ) - Norm( V_M_SPRi_E );
	ret.DrR_E.Kraft					= Ist_Inter.DRR_Param.DrR_E.Kraft;
	ret.DrR_E.V_DrR					= Ist_Inter.DRR_Param.DrR_E.V;
	ret.DrR_E.act					= Ist_Inter.DRR_Param.DrR_E.act;
	ret.DrR_E.mode					= Ist_Inter.DRR_Param.DrR_E.mode;

	// Druckrolle Auslaufseite
	ret.DrR_A.PosXY.x				= SP_A.x;
	ret.DrR_A.PosXY.y				= SP_A.y;
	ret.DrR_A.delta_Ring			= Norm( V_M_SPRo_A ) - Norm( V_M_SPRi_A );
	ret.DrR_A.Kraft					= Ist_Inter.DRR_Param.DrR_A.Kraft;
	ret.DrR_A.V_DrR					= Ist_Inter.DRR_Param.DrR_A.V;
	ret.DrR_A.act					= Ist_Inter.DRR_Param.DrR_A.act;
	ret.DrR_A.mode					= Ist_Inter.DRR_Param.DrR_A.mode;

	//////////////////////////////////////////////////
	// Setzen der Kraft_erreicht Flags bei >95% Soll_F
	// Loeschen bei <5% Soll_F
	//////////////////////////////////////////////////

	// Im Testmodus werden die Kraft_erreicht-Flags durch Kollisionsprüfung im Hauptmodul verwaltet
	if (!Ist_IBF.Schuessel.Test.Flag_oRing)
	{
		if ( (ret.DrR_E.Kraft / Ist_IBF.Schuessel.F_Soll_DrR) >= 0.95F ) Ist_IBF.Flag.DRE_kraft_anfahren_erreicht = 1;
		if ( (ret.DrR_E.Kraft / Ist_IBF.Schuessel.F_Soll_DrR) <= 0.05F ) Ist_IBF.Flag.DRE_kraft_anfahren_erreicht = 0;

		if ( (ret.DrR_A.Kraft / Ist_IBF.Schuessel.F_Soll_DrR) >= 0.95F ) Ist_IBF.Flag.DRA_kraft_anfahren_erreicht = 1;
		if ( (ret.DrR_A.Kraft / Ist_IBF.Schuessel.F_Soll_DrR) <= 0.05F ) Ist_IBF.Flag.DRA_kraft_anfahren_erreicht = 0;
	}

	////////////////////////////////////////////////////////////
	// Rueckgabe der Druckrollen-Parameter Struktur (an Ist_IBF)
	////////////////////////////////////////////////////////////

	return ret;
};

/////////////////////////////////////////////////////////
// Transformierung der Soll_IBF werte in Soll_Inter werte
/////////////////////////////////////////////////////////

Def_Soll_Inter_DRR DRR_trans_Soll(const Def_IBF_Allgemein_IST& Ist_IBF , const Def_IBF_Allgemein_SOLL& Soll_IBF)
{
	Def_Soll_Inter_DRR ret = {};

	// Ortsvektor der Druckrollenspur bei aktuelle AG-Position (Auslaufseite)
	punkt2D_t	Pu_A = { PREFX_A + Ist_IBF.AG_Pos ,
						 PREFY_A };

	// Richtungsvektor der Druckrollenspur (Pmax - Pref) (Auslaufseite)
	vektor2D_t	Vr_A = { PMAXX_A - PREFX_A ,	// dx
						 PMAXY_A - PREFY_A };	// dy
	
	// Berechnung der Koordinaten der NULL-Position (Auslaufseite)
	punkt2D_t	Pnul_A = {	Pu_A.x + ( Vr_A.dx / Norm( Vr_A ) ) * Ist_IBF.DRR_Param.Dist_VK_NUL_A ,
							Pu_A.y + ( Vr_A.dy / Norm( Vr_A ) ) * Ist_IBF.DRR_Param.Dist_VK_NUL_A };

	// Ortsvektor der Druckrollenspur bei aktuelle AG-Position (Einlaufseite)
	punkt2D_t	Pu_E = { PREFX_E + Ist_IBF.AG_Pos ,
						 PREFY_E };

	// Richtungsvektor der Druckrollenspur (Pmax - Pref) (Einlaufseite)
	vektor2D_t	Vr_E = { PMAXX_E - PREFX_E ,	// dx
						 PMAXY_E - PREFY_E };	// dy
	
	// Berechnung der Koordinaten der NULL-Position (Einlaufseite)
	punkt2D_t	Pnul_E = {	Pu_E.x + ( Vr_E.dx / Norm( Vr_E ) ) * Ist_IBF.DRR_Param.Dist_VK_NUL_E ,
							Pu_E.y + ( Vr_E.dy / Norm( Vr_E ) ) * Ist_IBF.DRR_Param.Dist_VK_NUL_E };

	gerade2D_t Spur_A = { Pnul_A.x , Pnul_A.y , Vr_A.dx, Vr_A.dy }; // Vektor der Druckrollenspur (Pnul -> Pmax)
	gerade2D_t Spur_E = { Pnul_E.x , Pnul_E.y , Vr_E.dx, Vr_E.dy }; // Vektor der Druckrollenspur (Pnul -> Pmax)

	ellipse_t	Ring_A = Ist_IBF.Schuessel.Walzform.RingGeo, // Ringgeometrie von der erweiterten 'Tastrolle' holen
				Ring_E = Ring_A;

	/////////////////////////////////////////////////////////////////////////////////////////
	// Die folgende Vorgehensweise stellt eine Vereinfachung des tatsaechlichen Problems dar.
	// Fuer perfekte Kreise (Ringe) ist das ermittelte Ergebniss exakt. Mit zunehmender
	// Exzentrizitaet der Kreisprojektion waechst jedoch der Fehler. Fuer die zu erwartenden
	// Ringgeometrieen bleibt der Fehler jedoch (Simulationslaeufen zu folge) tolerabel.
	// Dennoch sollte beachtet werden, dass bei der Rückwaertsrechnung (CNC->Ist_IBF) ein
	// Abweichendes Ergebniss ermittelt wird. D.O. 2015
	/////////////////////////////////////////////////////////////////////////////////////////

	Ring_A.a += 160 + Soll_IBF.DRR_Param.DrR_A.delta_Ring; // Sollabstand + Radius der Druckrolle
	Ring_A.b += 160 + Soll_IBF.DRR_Param.DrR_A.delta_Ring; // Sollabstand + Radius der Druckrolle
	Ring_E.a += 160 + Soll_IBF.DRR_Param.DrR_E.delta_Ring; // Sollabstand + Radius der Druckrolle
	Ring_E.b += 160 + Soll_IBF.DRR_Param.DrR_E.delta_Ring; // Sollabstand + Radius der Druckrolle

	/////////////////////////////////////////////////////
	// Sollwert fuer CNC aus Abstandsdefinition bestimmen
	/////////////////////////////////////////////////////
	
	P2			SP_A_v = {},	// Schnittpunkte Gerade/Ring Ausl.
				SP_E_v = {};    // Schnittpunkte Gerade/Ring Einl.
	punkt2D_t	SP_A = {},		// relevanter Schnittpunkt Gerade/Ring Ausl.
				SP_E = {};		// relevanter Schnittpunkt Gerade/Ring Einl.

	if ( Schnittpunkt( SP_A_v, Spur_A, Ring_A ) ) 
	{
		// Gueltige Schnittpunkte der Auslaufseite liegen IMMER im 4.Quadrant der Ringkontur
		if ( ( SP_A_v[0].y < 0.0F ) && ( SP_A_v[0].x > Ring_A.M.x ) ) SP_A = SP_A_v[0];
		if ( ( SP_A_v[1].y < 0.0F ) && ( SP_A_v[1].x > Ring_A.M.x ) ) SP_A = SP_A_v[1];
	} else SP_A = Pnul_A; // Kein gueltiger Schnittpunkt -> Soll-Position auf NULL-Position

	if ( Schnittpunkt( SP_E_v, Spur_E, Ring_E ) ) 
	{
		// Gueltige Schnittpunkte der Auslaufseite liegen IMMER im 1.Quadrant der Ringkontur
		if ( ( SP_E_v[0].y > 0.0F ) && ( SP_E_v[0].x > Ring_E.M.x ) ) SP_E = SP_E_v[0];
		if ( ( SP_E_v[1].y > 0.0F ) && ( SP_E_v[1].x > Ring_E.M.x ) ) SP_E = SP_E_v[1];
	} else SP_E = Pnul_E; // Kein gueltiger Schnittpunkt -> Soll-Position auf NULL-Position

	// Soll-Laenge der Druckrollenspur berechnen (Distanz SP_i bis P_nul)
	float Soll_pos_A = sqrt( pow( SP_A.x - Pnul_A.x , 2 ) + pow( SP_A.y - Pnul_A.y , 2 ) ), // Wertebereich 0..max
		  Soll_pos_E = sqrt( pow( SP_E.x - Pnul_E.x , 2 ) + pow( SP_E.y - Pnul_E.y , 2 ) );

	//////////////////////////////////
	// Uebergabe der berechneten Werte
	//////////////////////////////////

	// Druckrolle Auslaufseite
	ret.DrR_A.Kraft	=	Soll_IBF.DRR_Param.DrR_A.Kraft;
	ret.DrR_A.Pos	=	Soll_pos_A + Ist_IBF.DRR_Param.Dist_VK_NUL_A; 
	ret.DrR_A.V		=	Soll_IBF.DRR_Param.DrR_A.V_DrR;
	ret.DrR_A.act	=	Soll_IBF.DRR_Param.DrR_A.act;
	ret.DrR_A.mode	=	Soll_IBF.DRR_Param.DrR_A.mode;

	// Druckrolle Einlaufseite
	ret.DrR_E.Kraft	=	Soll_IBF.DRR_Param.DrR_E.Kraft;
	ret.DrR_E.Pos	=	Soll_pos_E + Ist_IBF.DRR_Param.Dist_VK_NUL_E; 
	ret.DrR_E.V		=	Soll_IBF.DRR_Param.DrR_E.V_DrR;
	ret.DrR_E.act	=	Soll_IBF.DRR_Param.DrR_E.act;
	ret.DrR_E.mode	=	Soll_IBF.DRR_Param.DrR_E.mode;
	
	///////////////////////////////////////////////////////////////
	// Rueckgabe der Druckrollen-Parameter Struktur (an Soll_Inter)
	///////////////////////////////////////////////////////////////

	return ret;
};
