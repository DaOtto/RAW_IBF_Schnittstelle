#ifndef _UFTCNCS_HPP
   #define _UFTCNCS_HPP

struct Def_APW_Halbe_Form
{
	double DaWP;
	double diWP;
	double hWP_m;
	double sWP_a;
	double sWP_i;
	double hWP_a;
	double hWP_i;
	double alpha_Profil_a_bo;
	double alpha_Profil_i_bo;
	double dhWP_a;
	double dhWP_i;
	double ddh_m;
	double dx_Schraege_Profil_a;
	double dx_Schraege_Profil_i;
	double sWP_ges;
	double dx_Breite_Profil_max;
	double dx_Breite_Profil_min;
	double dxWP_vor_iu;
	double dxWP_nach_au;
	double dyWP_vor_iu;
	double dyWP_nach_au;
	double d_Fliessscheide;
	double d_WP_Profil_i;
	double d_WP_Profil_a;
};

//---------------------------------------------------------------------------
// Struktur Def_Form: Definition der Ringgrössen
//---------------------------------------------------------------------------
struct Def_Form
{
	float da;                              // Ringe: Aussendurchmesser       [mm]
	float dm;                              // Ringe: Mittlerer Durchmesser   [mm]
	float di;                              // Ringe: Innendurchmesser        [mm]
	float sm;                              // Ringe: Wanddicke               [mm]
	float hm;                              // Ringe: Höhe                    [mm]

	float gewicht;                         // Gewicht                        [kg]

	double dFSWP;                          // APW: Durchm Fliessscheide      [mm]

	struct Def_APW_Halbe_Form Halbe_Form_o;// APW: Daten obere  Hälfte    
	struct Def_APW_Halbe_Form Halbe_Form_u;// APW: Daten untere Hälfte    
};

#endif
