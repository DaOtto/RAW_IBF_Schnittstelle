/*--DATEI HEADER---------------------------------------------------------------
;   Dateiname       : IBF_Geometrie_tool.hpp
;   Version         : V1.00a
;   Beschreibung    : Einige gemeinsame Geometrieberechnungen.	
;	Plattform		: RMOS3, WIN32				  
;
;                    
;
;   Autor           : D.Otto
;   date            : Dezember 2014
;
-----------------------------------------------------------------------------*/
#ifndef IBF_GEOMETRIE_TOOL_HPP
#define IBF_GEOMETRIE_TOOL_HPP

struct punkt2D_t
{
	float x;
	float y;
};

typedef punkt2D_t P4[4];

typedef punkt2D_t P2[2];

struct vektor2D_t
{
	float	dx;
	float	dy;
};

struct gerade2D_t
{
	punkt2D_t	Pu;
	vektor2D_t	Vr;
};

struct kreis_t
{
	punkt2D_t	M;
	float		r;
};

struct ellipse_t
{
	punkt2D_t M;
	float a;
	float b;
};

typedef double d6[6];
typedef double d5[5];
typedef double d4[4];
typedef double d3[3];
typedef double d2[2];

float	Norm( const vektor2D_t& );

int Schnittpunkt(		  P4&			,	///< [out] Vier berechnete Schnittpunkte
					const kreis_t&		,	///< [in]  Kreisdefinition
					const ellipse_t&		///< [in]  Ellipsendefinition	
				);	

int Schnittpunkt(		  P2&			,	///< [out] Zwei berechnete Schnittpunkte
					const gerade2D_t&	,	///< [in]  Geradendefinition
					const ellipse_t&		///< [in]  Ellipsendefinition	
				);

int LF4(d4& , const d5&);

int LF2(d2& , const d3&);

int norm(d5&); // Polynom normieren. Rueckgabe ist Grad des Polys
int norm(d3&); // Polynom normieren. Rueckgabe ist Grad des Polys

#endif // IBF_GEOMETRIE_TOOL_HPP


