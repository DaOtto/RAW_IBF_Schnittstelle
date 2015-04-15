/*--DATEI HEADER---------------------------------------------------------------
;   Dateiname       : IBF_Schuessel_DR_pos.hpp
;   Version         : V1.00a
;   Beschreibung    : Sollwertbestimmung der Druckrollen beim Schuesselwalzen
;	Plattform		: RMOS3, WIN32				  
;
;                    
;
;   Autor           : D.Otto
;   date            : Dezember 2014
;
-----------------------------------------------------------------------------*/
#ifndef IBF_SCHUESSEL_DR_POS_HPP
#define IBF_SCHUESSEL_DR_POS_HPP

#include "IBF_Geometrie_tool.hpp"

// Auslaufseite
// Abstand Theoretische Kegelwalzenspitze, Vorderkante Vierkantführung [mm]  
#define PREFX_A		948.35F
// Abstand Maschinenmitte, Vorderkante Vierkantführung [mm]
#define PREFY_A		-915.79F
// Abstand Theoretische Kegelwalzenspitze, Druckrollenmitte bei voll ausgefahrenem Kolben [mm]  
#define PMAXX_A		394.46F
// Abstand Maschinenmitte, Druckrollenmitte bei voll ausgefahrenem Kolben [mm]
#define PMAXY_A		-466.38F

// Einlaufseite
// Abstand Theoretische Kegelwalzenspitze, Vorderkante Vierkantführung [mm]  
#define PREFX_E		952.29F
// Abstand Maschinenmitte, Vorderkante Vierkantführung [mm]
#define PREFY_E		906.87F
// Abstand Theoretische Kegelwalzenspitze, Druckrollenmitte bei voll ausgefahrenem Kolben [mm]  
#define PMAXX_E		395.63F
// Abstand Maschinenmitte, Druckrollenmitte bei voll ausgefahrenem Kolben [mm]
#define PMAXY_E		464.54F

struct Def_Ibf_DrR
{
	float	delta_Ring;
	float	V_DrR;
	float	Kraft;
	punkt2D_t PosXY;
	int		act;
	int		mode;
};

struct Def_RAW_DrR
{
	float Pos;
	float Kraft;
	float V;
	int act;
	int mode;
};

struct Def_IBF_Ist_DRR
{
	Def_Ibf_DrR DrR_E;
	Def_Ibf_DrR DrR_A;
	float		Dist_VK_NUL_A;
	float		Dist_VK_NUL_E;
};

struct Def_IBF_Soll_DRR
{
	Def_Ibf_DrR DrR_E;
	Def_Ibf_DrR DrR_A;
};

struct Def_Ist_Inter_DRR
{
	Def_RAW_DrR DrR_E;
	Def_RAW_DrR DrR_A;
};

struct Def_Soll_Inter_DRR
{
	Def_RAW_DrR DrR_E;
	Def_RAW_DrR DrR_A;
};


Def_IBF_Ist_DRR		DRR_trans_IST(const Def_Ist_Inter& , Def_IBF_Allgemein_IST&);

Def_Soll_Inter_DRR	DRR_trans_Soll(const Def_IBF_Allgemein_IST& , const Def_IBF_Allgemein_SOLL&);

#endif // IBF_SCHUESSEL_DR_POS_HPP


