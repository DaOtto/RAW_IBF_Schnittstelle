#ifndef _CTMCNCS_HPP
   #define _CTMCNCS_HPP

//---------------------------------------------------------------------------
// Strukturen
//---------------------------------------------------------------------------
	struct Def_fxyz
	{
		float x;
		float y;
		float z;
	};

	struct Def_dxyz
	{
		double x;
		double y;
		double z;
	};

        struct Def_ixy
	{
	        int   x; 
		int   y;
	};


	//---------------------------------------------------------------------------
	// Struktur Def_Kontur_Gewicht
	//---------------------------------------------------------------------------
	struct Def_Kontur_Volumen
	{
		double volumen_gesamt;
		double volumen_oben;
		double volumen_unten;
	};
   

#endif

