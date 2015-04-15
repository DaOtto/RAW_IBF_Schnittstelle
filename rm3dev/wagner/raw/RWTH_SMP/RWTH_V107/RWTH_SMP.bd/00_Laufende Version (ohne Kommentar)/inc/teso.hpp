#ifndef _TESO_H
	#define _TESO_H	

      #ifdef _BORLAND_C
        #define __max(a, b)  (((a) > (b)) ? (a) : (b))
        #define __min(a, b)  (((a) < (b)) ? (a) : (b))
      #endif
   
#ifdef SMP16   
	#ifndef TRUE
		#define TRUE    -1
	#endif
	#ifndef FALSE
		#define FALSE   0
	#endif
#else
	#ifndef TRUE
		#define TRUE    1
	#endif
	#ifndef FALSE
		#define FALSE   0
	#endif
#endif

	#define ZAHLGROSS 100000000.0F
	#define EPSILON	0.001F

	// Korrekturfaktoren
	#define DM3_MM3_FAK		(1.0F / 1000000.0F)// Umrechnungsfaktor Kubikdezimeter/Kubikmillimeter
	#define MILL_FAK			1000000.0F			 // Korrekturfaktor eine Million
	#define BAR_FAK			0.1F					 // Umrechnungsfaktor 1 Bar == 0.1N/mm² in 
	#define PROZ_FAK			0.01F					 // Umrechnungsfaktor Prozent
	#define PROMILL_FAK		0.001F				 // Umrechnungsfaktor Promille
	#define KILO_FAK			1000.0F				 // Korrekturfaktor Tausend
	#define MIN_FAK			(1.0F / 60.0F)		 // Umrechnungsfaktor eine Minute

	#ifndef M_PI
		#define M_PI		3.14159265358979323846
	#endif

	#ifdef WIN32	// MSVC++ 6.0
		#ifndef PI
			#define PI		3.14159265358979323846
		#endif
	#else				// Borland 3.1
		#define PI	M_PI
        //-------------------------------------------------------------------
        // Maximum und Minimum bestimmen
        //-------------------------------------------------------------------
        inline long max(long a, long b)
 	    			{return(a > b ? a : b);}
        inline long min(long a, long b)
 	    			{return(a < b ? a : b);}
        inline double max(double a, double b)
 	    			{return(a > b ? a : b);}
        inline double min(double a, double b)
 	    			{return(a < b ? a : b);}
	#endif

   #ifdef PI
      #define GRAD      (2 * PI / 360.0)      
   #endif

   #ifndef EULER
      #define EULER 2.7182818284590452
   #endif

//---------------------------------------------------------------------------
// Definition der Messageboxtypen
//---------------------------------------------------------------------------
	#define GUI_T_MB_ABORTRETRYIGNORE	0
	#define GUI_T_MB_OK						1	
	#define GUI_T_MB_OKCANCEL				2	
	#define GUI_T_MB_RETRYCANCEL			3
	#define GUI_T_MB_YESNO					4
	#define GUI_T_MB_YESNOCANCEL			5

//---------------------------------------------------------------------------	
// Definition der Messageboxbitmaps
//---------------------------------------------------------------------------
	#define GUI_T_MB_WARNING			0
	#define GUI_T_MB_INFORMATION		1
	#define GUI_T_MB_QUESTION			2
	#define GUI_T_MB_STOP				3

//---------------------------------------------------------------------------
// Definition der Messageboxrückgabewerte
//---------------------------------------------------------------------------
 	#define GUI_T_MB_RET_OK				0
 	#define GUI_T_MB_RET_ABORT			1
 	#define GUI_T_MB_RET_RETRY			2
 	#define GUI_T_MB_RET_IGNORE		3
 	#define GUI_T_MB_RET_CANCEL		4
 	#define GUI_T_MB_RET_YES			5
 	#define GUI_T_MB_RET_NO				6

   #ifdef WIN32

	   struct Def_f012
	   {
		   float nr0;
		   float nr1;
		   float nr2;
	   };

	   struct 	Def_s012
	   {
		   short nr0;
		   short nr1;
		   short nr2;
	   };

	   struct Def_sxyz
	   {
		   short x;
		   short y;
		   short z;
	   };

	   struct Def_i01
	   {
		   int	nr0;
		   int	nr1;
	   };

	   struct Def_i012
	   {
		   int	nr0;
		   int	nr1;
		   int	nr2;
	   };

	   struct Def_RGB
	   {
		   int	rot;
		   int	gruen;
		   int	blau;
	   };

	   struct Def_i0123
	   {
		   int	nr0;
		   int	nr1;
		   int	nr2;
		   int	nr3;
	   };

	   struct Def_Rechteck
	   {
		   double hoehe;
		   double breite;
		   double x;
		   double y;
	   };

   #endif

#endif

