/*--DATEI HEADER---------------------------------------------------------------
;   Dateiname       : IBF_Schuessel_ZR_pos.cpp
;   Version         : V1.00a
;   Beschreibung    : Sollwertbestimmung der Zentrierrollen beim Schuesselwalzen
;	Plattform		: RMOS3, WIN32				  
;
;                    
;
;   Autor           : D.Otto
;   date            : Dezember 2014
;
-----------------------------------------------------------------------------*/

#include <math.h>

#include "rpw.hpp"

///////////////////////////////////////////////////////
// Transformierung der Ist_Inter werte in Ist_IBF werte
///////////////////////////////////////////////////////

Def_IBF_Ist_ZER	ZER_trans_IST(const Def_Ist_Inter& Ist_Inter , const Def_IBF_Allgemein_IST& Ist_IBF)
{
	Def_IBF_Ist_ZER ret = {};
	const Def_Schuessel_Walzform& WForm = Ist_IBF.Schuessel.Walzform ;

	float	phi_A,
			phi_E;

	float   x_a,y_a,
			x_e,y_e;
	
	ret.ZRE.MTS = Ist_Inter.zal_pos, // MTSwerte Ein- und Auslaufseite
	ret.ZRA.MTS = Ist_Inter.zar_pos; 
		
	// Berechnung der Winkelpositionen der Zentrierarme
	phi_E = phi_von_MTS( ret.ZRE.MTS );
	phi_A = phi_von_MTS( ret.ZRA.MTS );

	x_a = -1074+1330*sin(phi_A);
	y_a = -870 +1330*cos(phi_A);
	x_e = -1074+1330*sin(phi_E);
	y_e =  870 -1330*cos(phi_E);

	P4			SP_a = {},
				SP_e = {};
	kreis_t		zre = { { x_e , y_e } , 135.0F },
				zra = { { x_a , y_a } , 135.0F };

	ret.ZRA.Flag_Kontakt = Schnittpunkt(SP_a, zra, WForm.RingGeo);
	ret.ZRE.Flag_Kontakt = Schnittpunkt(SP_e, zre, WForm.RingGeo);

	// Distanz[mm] der Zentrierollen zueinander
	// dient hauptsaechlich der Kalibrierung
	ret.delta_ZRA_ZRE	= sqrt(pow((ret.ZRE.Pos_y = y_e)-(ret.ZRA.Pos_y = y_a),2)+pow(x_e-x_a,2)) - 270;

	// Tangentenwinkel im Kontaktpunkt Zentrierolle|Ring
	// zur Berechnung der Kraftkomponenten auf den Ring
	float	phi_ri_ra_e = atan( ( ( WForm.RingGeo.b * x_e ) / WForm.RingGeo.a ) / ( ( -WForm.RingGeo.a * y_e ) / WForm.RingGeo.b)),
			phi_ri_ra_a = atan( ( ( WForm.RingGeo.b * x_a ) / WForm.RingGeo.a ) / ( ( -WForm.RingGeo.a * y_a ) / WForm.RingGeo.b)),
			phi_ra_ta_e = -phi_ri_ra_e - (PI/2) + phi_E,
			phi_ra_ta_a = -phi_ri_ra_a - (PI/2) - phi_A;//+

	float	Frad_e	= -cos(phi_ra_ta_e) * Ist_Inter.zal_f * (560.0F/1330.0F),
			Frad_a	=  cos(phi_ra_ta_a) * Ist_Inter.zar_f * (560.0F/1330.0F);

	// Kraftkomponenten in xy-Koordinaten
	ret.ZRE.F_y			=  Frad_e * cos(phi_ri_ra_e);
	ret.ZRE.F_x			=  Frad_e * sin(phi_ri_ra_e);
	ret.ZRA.F_y			=  Frad_a * cos(phi_ra_ta_a);
	ret.ZRA.F_x			=  Frad_a * -sin(phi_ra_ta_a);

	return ret;
};

// Transformierung der Soll_IBF werte in Soll_Inter werte
void ZER_trans_Soll(struct Def_Soll_Inter& Soll_Inter, const Def_IBF_Allgemein_SOLL& Soll_IBF,const Def_IBF_Allgemein_IST& Ist_IBF)
{
	const Def_Schuessel_Walzform& WForm = Ist_IBF.Schuessel.Walzform ;

	kreis_t		ZArm_E = {  {-1074,  870} , // Lagerkoordinaten Einlaufseite
									1330 };	// Radius Lager_arm -> Lager_Rolle
									  	
	kreis_t		ZArm_A = { {-1074, -870} ,	// Lagerkoordinaten Auslaufseite
									1330 };	// Radius Lager_arm -> Lager_Rolle
						            
	ellipse_t Ring_A = { {  WForm.RingGeo.M.x,
							WForm.RingGeo.M.y } ,
							WForm.RingGeo.a + Soll_IBF.ZER_Param.ZRA.delta_Ring +  135,
							WForm.RingGeo.b + Soll_IBF.ZER_Param.ZRA.delta_Ring +  135 };
	
	ellipse_t Ring_E = { {  WForm.RingGeo.M.x,
							WForm.RingGeo.M.y } ,
							WForm.RingGeo.a + Soll_IBF.ZER_Param.ZRE.delta_Ring +  135,
							WForm.RingGeo.b + Soll_IBF.ZER_Param.ZRE.delta_Ring +  135 };
	
	P4			SP_E  = {},
				SP_A  = {};
	
	float	phi_E = 0.0F,
			phi_A = 0.0F;

	if (!Schnittpunkt(SP_E , ZArm_E, Ring_E)) 
	{
		// Kein Schnittpunkt! -> Position halten.
		Soll_Inter.zal_pos = Ist_IBF.ZER_Param.ZRE.MTS;
	} 
	else 
	{
		phi_E = (SP_E[0].y>SP_E[1].y) ? acos( ( ZArm_E.M.y - SP_E[0].y ) / 1330 ) : acos( ( ZArm_E.M.y - SP_E[1].y ) / 1330 );
		Soll_Inter.zal_pos = MTS_von_phi( phi_E );
	};

	if (!Schnittpunkt(SP_A , ZArm_A, Ring_A)) 
	{
		// Kein Schnittpunkt! -> Position halten.
		Soll_Inter.zar_pos = Ist_IBF.ZER_Param.ZRA.MTS; 
	} 
	else 
	{
		phi_A = (SP_A[0].y<SP_A[1].y) ? acos( ( -ZArm_A.M.y + SP_A[0].y ) / 1330 ) : acos( ( -ZArm_A.M.y + SP_A[1].y ) / 1330 );
		Soll_Inter.zar_pos = MTS_von_phi( phi_A );
	};
	Soll_Inter.zal_pos = Soll_Inter.zar_pos;
	Soll_Inter.zar_v   = Soll_Inter.zal_v = Soll_IBF.ZER_Param.ZRE.V_Spur * ( 560.0F / 1330.0F );
	
	// Modus und Steuerung (act 0=SMS/1=IBF)
	Soll_Inter.zen_mode = Soll_IBF.ZER_Param.mode;
	Soll_Inter.zen_act	= Soll_IBF.ZER_Param.act;

	return;
};

/////////////////////////////////////////////////////
// Berechnet den MTS-Wert in Abhaenigkeit des Winkels
// zwischen Schwenkarm und Y-Achse
/////////////////////////////////////////////////////

float MTS_von_phi( const float phi ) { return sqrt( 3347000.0F + cos( phi - 0.04430F ) * -1951000.0F ); };

///////////////////////////////////////////////////
// berechnet den Winkel des Schwenkarms zur Y-Achse
// in Abhaenigkeit vom MTS-Wert
///////////////////////////////////////////////////

float phi_von_MTS( const float MTS ) { return acos( ( pow( MTS , 2 ) - 3347000.0F ) / -1951000.0F ) + 0.04430F; };


