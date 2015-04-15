/*--DATEI HEADER---------------------------------------------------------------
;   Dateiname       : IBF_Schuessel_ZR_pos.hpp
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

#ifndef IBF_SCHUESSEL_ZR_POS_HPP
#define IBF_SCHUESSEL_ZR_POS_HPP

struct Def_Soll_ZER
{
	float delta_Ring;
	float V_Spur;
};

struct Def_Ist_ZER
{
	int	  Flag_Kontakt;
	float Pos_y;
	float F_x;
	float F_y;
	float MTS;
};

struct Def_IBF_Soll_ZER
{
	int				act;
	int				mode;
	float			Kraft;
	Def_Soll_ZER	ZRE;
	Def_Soll_ZER	ZRA;
};

struct Def_IBF_Ist_ZER
{
	float			delta_ZRA_ZRE;
	Def_Ist_ZER		ZRE;
	Def_Ist_ZER		ZRA;	
};

Def_IBF_Ist_ZER	ZER_trans_IST(	const Def_Ist_Inter& , 
								const Def_IBF_Allgemein_IST& );

void ZER_trans_Soll(struct	Def_Soll_Inter&, 
					const	Def_IBF_Allgemein_SOLL&,
					const	Def_IBF_Allgemein_IST&);

float MTS_von_phi( const float winkel );

float phi_von_MTS( const float MTS );

#endif // IBF_SCHUESSEL_ZR_POS_HPP
