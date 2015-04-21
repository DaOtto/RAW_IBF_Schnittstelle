/*--DATEI HEADER---------------------------------------------------------------
;   Dateiname       : IBF_Geometrie_tool.cpp
;   Version         : V1.00a
;   Beschreibung    : Einige gemeinsame Geometrie Funktionen.
;					  	
;	Plattform		: RMOS3, WIN32				  
;
;                    
;
;   Autor           : D.Otto
;   date            : Dezember 2014
;
-----------------------------------------------------------------------------*/

#include <math.h>

#include "IBF_Geometrie_tool.hpp"

///////////////////////////////////////////
//Berechnet die Norm (Laenge) eines Vektors
float	Norm(const vektor2D_t& v_In ) { return sqrt( pow( v_In.dx , 2 ) + pow( v_In.dy , 2) ); };

//////////////////////////////////////////////////////////////
// Berechnet die Schnittpunkte eines Kreises und einer Ellipse
int Schnittpunkt(		  P4&			SPOut,
					const kreis_t&		k_In ,
					const ellipse_t&	e_In )
{
	// Kreisgleichung k
	double	k_a00	= pow( k_In.r , -2 ) ,			// 1/r^2
			k_a11	= pow( k_In.r , -2 ) ,			// 1/r^2		
			k_b0	= -2.0F * k_In.M.x * k_a00 ,	// -2xo/r^2
			k_b1	= -2.0F * k_In.M.y * k_a11 ,	// -2yo/r^2
			k_c		= pow( k_In.M.x / k_In.r , 2 ) + pow( k_In.M.y / k_In.r , 2 ) - 1.0F ;	// xo^2/r^2 + yo^2/r^2 - 1		
	
	// Ellipsengleichung e
	double	e_a00	= pow( e_In.a , -2 ) ,			// 1/a^2
			e_a11	= pow( e_In.b , -2 ) ,			// 1/b^2	
			e_b0	= -2.0F * e_In.M.x * e_a00 ,	// -2xo/a^2
			e_b1	= -2.0F * e_In.M.y * e_a11 ,	// -2yo/b^2
			e_c		= pow( e_In.M.x / e_In.a , 2 ) + pow( e_In.M.y / e_In.b , 2 ) - 1.0F ;	// xo^2/a^2 + yo^2/b^2 - 1		

	double	v1 = k_a00 * e_a11- e_a00 * k_a11,
			v2 = k_a00 * e_b0 - e_a00 * k_b0 ,
			v3 = k_a00 * e_b1 - e_a00 * k_b1 ,
			v4 = k_a00 * e_c  - e_a00 * k_c  ,
			v5 = k_a11 * e_b0 - e_a11 * k_b0 ,
			v6 = k_b0  * e_b1 - e_b0  * k_b1 ,
			v7 = k_b0  * e_c  - e_b0  * k_c  ;

	d5		u	= {  v2 * v7 - pow( v4 , 2 ) , 
					 v2 * v6 - 2.0F * v3 * v4 ,
					-v5 * v2 - pow( v3 , 2 ) - 2.0F * v1 * v4 , 
					-2.0F * v1 * v3 ,
					-pow( v1 , 2 ) };

	d4	nst		= {};
	int znst	= LF4( nst, u );

	if ( !znst ) return 0; // keine NSt (Schnittpunkte) gefunden

	d3		a	= {},
			b	= {};
	d2		nsta = {},
			nstb = {};

	for ( int i=0; i < znst; i++ )
	{
		SPOut[i].y = (float)nst[i];

		a[0] = k_c + nst[i] * k_b1 + SPOut[i].y * nst[i] * k_a11;
		a[1] = k_b0;
		a[2] = k_a00;

		b[0] = e_c + nst[i] * e_b1 + SPOut[i].y * nst[i] * e_a11;
		b[1] = e_b0;
		b[2] = e_a00;
	
		LF2( nsta , a );
		LF2( nstb , b );

		if ( ( fabs( nsta[0] - nstb[0] ) < 0.01F ) || ( fabs( nsta[0] - nstb[1] ) < 0.01F ) ) SPOut[i].x = (float)nsta[0];
		else SPOut[i].x = (float)nsta[1];		
	}
	
	return znst; // Anzahl der gefundenen Schnittpunkte
};

/////////////////////////////////////////////////////////////
// Berechnet die Schnittpunkte einer Gerade und einer Ellipse
int Schnittpunkt(		  P2&			SPOut	,
					const gerade2D_t&	g_In	,
					const ellipse_t&	e_In	)
{
	// Geradengleichung mx + c = y
	double	g_b0	= ( g_In.Vr.dy ) / ( g_In.Vr.dx ) ,	// dy/dx = m
			g_b1	= -1.0F ,							// -1y
			g_c		= g_In.Pu.y - ( g_b0 * g_In.Pu.x );	// yo - m*xo = c

	// Ellipsengleichung
	double	e_a00	= pow( e_In.a , -2 ) ,				// 1/a^2
			e_a11	= pow( e_In.b , -2 ) , 				// 1/b^2	
			e_b0	= -2.0F * e_In.M.x * e_a00 , 		// -2xo/a^2
			e_b1	= -2.0F * e_In.M.y * e_a11 ,		// -2yo/b^2
			e_c		= pow( e_In.M.x / e_In.a , 2 ) + pow( e_In.M.y / e_In.b , 2) - 1.0F ;	// xo^2/a^2 + yo^2/b^2 - 1		
	
	double	v0	= -e_a00 * g_b0 ,
			v1	=  e_a00        ,
			v2	= -e_a00 * g_c  ,
			v3	=  e_a11 * g_b0 ,
			v4	=  g_b0  * e_b1 - e_b0 * g_b1 ,
			v5	=  g_b0  * e_c  - e_b0 * g_c  ;

	// Polynomkoeffizienten
	d3		u	= { v0 * v5 - pow( v2 , 2 )	 ,
					v0 * v4 - 2.0F * v1 * v2 ,	
					v0 * v3 - pow( v1 , 2 )	};
	
	// Nullstellen
	d2		nst = {}; 
	
	int znst = LF2( nst , u );
	
	if ( znst > 0 )	// Schnittpunkte gefunden
	{
		SPOut[0].y = (float)nst[0];
		SPOut[1].y = (float)nst[1];
		SPOut[0].x = (float)( nst[0] - g_c ) / (float)g_b0 ;
		SPOut[1].x = (float)( nst[1] - g_c ) / (float)g_b0 ;

		return znst;
	};
	
	return 0; // keine Schnittpunkte
};

//////////////////////////////////////////////////////////////////
// Nullstellen eines Polynoms 4. Grades bestimmen (NUR reelle NSt)
// in Anlehnung an das Bairstow-Verfahren
int LF4(d4& nst, const d5& pn)
{
	// Lokale Kopie des Eingabepolynoms, (wg. Schreibzugriff)
	d5		poly	= { pn[0] ,	pn[1] ,	pn[2] ,	pn[3] ,	pn[4] };
	
	// Maximale Anzahl an Iterationen
	int		maxiter	= 20;

	// Anzahl der reellen Nullstellen (Returnvalue)
	int		znst	= 0;

	int		n = norm(poly),	// Polynom normieren und Grad (n) bestimmen
			j = n,			// Schleifenzaehler
			i = 0;			// Schleifenzaehler
	
	if ( n > 2 ) // wenn poly eigentlich 2.Grades -> Abkürzung nehmen.
	{
		double	b0 = poly[n],	// Divisionsrest
				b1 = 0,
				b2;
	
		double	q0 = 0,			// Quotient
				q1 = 0,
				q2;
	
		double	a0 = poly[n-2], // Startwert der Iteration
				a1 = poly[n-1], // Startwert der Iteration
				da0 = 0,
				da1 = 0;
	
		double	M = 0,
				D = 0;
		
		do // Zerlegung von poly^n -> a^2 * b^(n-2)
		{
			b0 = poly[n];
			b1 = 0;
			
			q0 = 0;
			q1 = 0;
			
			for ( j = n - 1; j >= 0; j-- )
			{
				b2 = b1;
				b1 = b0;
				b0 = poly[j] - a1 * b1 - a0 * b2;
				q2 = q1;
				q1 = q0;
				q0 = b2      - a1 * q1 - a0 * q2;
			}
	
			M = -a0 * q1 - a1 * q0;
			D =  q0 * q0 -  M * q1;
	
			da1 = (b0 * q1 - b1 * q0) / D;
			da0 = (b1 * M  - b0 * q0) / D;
	
			a1 = a1 - da1;
			a0 = a0 - da0;
			maxiter -=1 ;
		}
		while ( ( ( fabs(da0) > 0.0001F ) && ( fabs(da1) > 0.0001F ) ) || ( maxiter < 0 ) ); // Abbruchbedingung der Iterationsschleife
			
		d3 a = { a0, a1, 1  };	// P(2)
		d3 b = {};				// P(n-2)
	
		// Eingabe Polynom reduzieren durch abdividieren der
		// gefundenen Nullstellen ( poly(x)/a(x) = b(x) )
		for( i = n-2 ; i >= 0 ; i-- )
		{
			b[i] = poly[i+2] / a[2];
			for( j = 2 ; j >= 0 ; j-- )
				poly[i+j] = poly[i + j] - a[j] * b[i];
		}
		
		d2 n01 = {}; // x0,x1
		d2 n23 = {}; // x2,x3
		
		// Nullstellen-Array initialisieren...
		for ( i = 4 ; i > 0 ; nst[--i] = 0.0F );
		
		// Reelle Loesungen der quadratischen Faktoren bestimmen
		znst = LF2( n01 , a );
		if (znst)
		{
			nst[i++] = n01[0];
			nst[i++] = n01[1];
		}
		
		znst += LF2( n23 , b );
		if (znst)
		{
			nst[i++] = n23[0];
			nst[i  ] = n23[1];
		}
	} // if (n>2)
	else // Loesen alles <= 2.Grades
	{
		d3 a	= { poly[0], poly[1], poly[2] };
		d2 n01	= {};
		znst	= LF2( n01 , a );

		for ( i = 0 ; i < znst ; nst[i++] = n01[i] );
	}

	return znst; // Rueckgabewert ist die Anzahl der Reellen Loesungen (0 bis 4)
};

//////////////////////////////////////////////////////////////////////////
// Bestimmung der REELLEN Loesungen einer quadratischen/linearen Gleichung
int LF2(d2& nst, const d3& pn)
{
	double	p,
			q,
			D;
	
	// Lokale Kopie des Eingabepolynoms, mit Schreibzugriff
	d3		poly = { pn[0] , pn[1] , pn[2] };
	
	// Anzahl der reellen Nullstellen (Returnvalue)
	int		znst	= 0;

	switch ( norm(poly) )
	{	
	case 2:		// Quadratische Gl. ->Loesen mit pq-Formel
	
		q = poly[0] / poly[2];
		p = (poly[1] / poly[2]) / 2.0F; // genauer: p/2

		D = p*p - q;

		if (D > 0.0F)	// zwei reelle Loesungen
		{
			nst[0] = -p+sqrt(D);
			nst[1] = -p-sqrt(D);

			znst = 2;
		}
		else if ( D == 0.0F )	// doppelte Nullstelle
		{
			nst[0] = nst[1] = -p;

			znst = 2;
		}
		else			// keine reelle Loesung
		{
			nst[0] = 0.0F;
			nst[1] = 0.0F;

			znst = 0;
		}
		break;
	
	case 1:	// Lineare Gl. -> Eine Loesung 
	
		nst[0] = -poly[0] / poly[1];
		nst[1] = 0.0F;

		znst = 1;
		break;
	
	case 0:	// Konstante -> keine Loesung oder 0
	
		nst[0] = 0.0F;
		nst[1] = 0.0F;

		znst = ( poly[0] == 0.0F ) ? 1 : 0 ;
		break;

	default: break;
	};

	return znst; // Rueckgabewert ist die Anzahl der Reellen Loesungen (0 bis 2)
};

////////////////////////////////////
// Normieren eines Polynoms 4.Grades
int norm(d5& poly)
{
	int n = 4;
	while ( ( poly[n] == 0.0F ) && ( n > 0 ) ) n--; // Grad bestimmen...
	
	if ( n > 0 ) // ...und normieren
		for ( int j = 0; j <= n; j++ )
			poly[j] = poly[j] / poly[n];
	
	return n;
};

//////////////////////////////////////////
// Normieren einer quadratischen Gleichung
int norm(d3& poly)
{
	int n = 2;
	while ( ( poly[n] == 0.0F ) && ( n > 0 ) ) n--; // Grad bestimmen...
	
	if ( n > 0 ) // ...und normieren
		for ( int j = 0; j <= n; j++ )
			poly[j] = poly[j] / poly[n];
	
	return n;
};

