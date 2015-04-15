/*--DATEI HEADER---------------------------------------------------------------
;   Dateiname       : IBF_Schuessel_Form.hpp
;   Version         : V1.00a
;   Beschreibung    : Ermittlung der Ringlage und -Geometrie beim Schuesselwalzen
;	Plattform		: RMOS3, WIN32				  
;
;                    
;
;   Autor           : D.Otto
;   date            : Dezember 2014
;
-----------------------------------------------------------------------------*/

#ifndef IBF_SCHUESSEL_FORM_HPP
#define IBF_SCHUESSEL_FORM_HPP

#define PUFF_LEN 3 ///< Messwertpufferlaenge für Filter

#include "IBF_Geometrie_tool.hpp"

struct Def_Schuessel_Walzform
{
	float da;					///< aktuelle Tastrollenposition [mm]
	float hm;					///< aktuelle mittlere Profilhoehe [mm]
	float sm;					///< aktuelle mittlere Profilbreite [mm]

	float r_eff_u;				///< Effektiver Radius des Ringes fuer Berechnung der Drehzahl der unteren KW [mm]
	float r_eff_o;				///< Effektiver Radius des Ringes fuer Berechnung der Drehzahl der oberen KW [mm]

	float dw_min_Pos;			///< Kleinste moegliche Position fuer Radialschlitten
	float dw_max_Pos;			///< Maximal moegliche Position fuer Radialschlitten

	int	  cursor;				///< Cursorposition der Ringpuffer [-]
	float TR_puffer[PUFF_LEN];	///< Puffer fuer vorangegangene Tastrollenpositionen [mm]
	float DRx_puffer[PUFF_LEN];	///< Puffer fuer vorangegangene x-Position der Druckrolle [mm]
	float DRy_puffer[PUFF_LEN];	///< Puffer fuer vorangegangene y-Position der Druckrolle [mm]

	float da_mf;				///< gefilterte Tastrollenposition (Mittelwert) [mm]
	float DRx_mf;				///< Gefilterte x-Position der Druckrolle (Mittelwert) [mm]
	float DRy_mf;				///< Gefilterte y-Position der Druckrolle (Mittelwert) [mm]

	float Kletterwinkel;		///< Kletterwinkel [rad]
	float Kletterhoehe;			///< z-Position des Ringes an der Hauptwalze [mm]

	ellipse_t RingGeo;			///< Geometrische Beschreibung der Projektion des Ringes auf der Walztischebene
};

int	Schuessel_Form_IST(	Def_IBF_Allgemein_IST& , const Def_Ist_Inter& );

int Vorform_geo_berechnen( Def_IBF_Allgemein_IST& );

#endif // IBF_SCHUESSEL_FORM_HPP
