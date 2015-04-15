/******************************************************************************
Name:		Win_RWTH_EXCH.hpp
Plattform:	WIN32

Funktion:	Testbetrieb des IBF-Technologiemoduls ohne Walzwerk

Autor:		Daniel Otto

Version:	26.10.2014	V1.0
******************************************************************************/

#ifndef WIN_RWTH_EXCH_HPP
#define WIN_RWTH_EXCH_HPP

#define Kaliber_HW 0	// notwendig in Win_RWTH_EXCH:init()
#define Kaliber_DW 0	// notwendig in Win_RWTH_EXCH:init()

/******************************************************************************
Einbinden zusätzlicher Definitionen
******************************************************************************/

#include "puff_cnc_s.hpp"	// Def_Ein_Puff, Def_Aus_Puff, Def_Lokal_Puff
#include "onli_cnc_s.hpp"	// Def_Ein_Onli, Def_Aus_Onli
#include "rpw.hpp"			// Def_Ist_Inter, Def_Soll_Inter, RPW
#include "IBF_struct.hpp"	// Def_IBF_Allgemein_Soll, Def_IBF_Allgemein_IST
#include <windows.h>
#include <vector>
#include <iostream>

/******************************************************************************
Datenlogger Klassen
******************************************************************************/
// Macro 'logCh(var)' : vereinfachte Logger-Kanalerzeugung
#define logCh(x) logChannel(#x,x)
template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0));}

using namespace std;

class logChannel {
	private:
		float*	pfData;
		long*	piData;
		char*	psData;
		string	name;
		bool	Int; // true=integer;false=float
		bool	sym; // true=Symbol;false=Value
		vector<long>	idata;
		vector<float>	fdata;
		vector<char>	sdata;

	public:
		string	getName(void) { return name; };
		int		snapShot(void);
		size_t	size(void);
		string	sGetValue(unsigned int);
		logChannel(char*, long&);
		logChannel(char*, int&);
		logChannel(char*, float&);
		logChannel(char*, char&);
		logChannel(void);
		~logChannel(void);
};

class dataLog {
	private:
		bool	written;
		string	name;
		vector<logChannel> ChannelSet;
	public:
		string	setName(string);
		int		pushChannel(logChannel);
		int		snapShot();
		int		writeCSV(string ="");
		dataLog(void);
		~dataLog(void);
};

struct globData {
	Def_Ein_Puff 			Ein_Puff	;
	Def_Lokal_Puff			Lokal_Puff	;
	Def_Aus_Puff 			Aus_Puff	;
	Def_Ein_Onli 			Ein_Onli	;
	Def_Aus_Onli 			Aus_Onli	;
	Def_Ist_Inter 			Ist_Inter	;
	Def_Soll_Inter			Soll_Inter	;
	Def_IBF_Allgemein_SOLL	Soll_IBF	;
	Def_IBF_Allgemein_IST 	Ist_IBF		;
};

struct exchPool {
	Def_Aus_Puff 			Aus_Puff_RWTH;
	Def_Aus_Onli 			Aus_Onli_RWTH;
	Def_Ein_Puff 			Ein_Puff_back,
							Ein_Puff_RWTH;
	Def_Ein_Onli 			Ein_Onli_back,
							Ein_Onli_RWTH;
};

class Win_RWTH_EXCH {
	protected:
		
		int  Status_TRT;
		int  Steuer_TRT;
		int  Status_RWTH;
		int  Steuer_RWTH;
		int  Data_available;
		int  Data_availableRWTH;
		int  Data_initialed;

		
		struct Def_Ist_Inter			*pIst_Inter_Ini;
		struct Def_Soll_Inter			*pSoll_Inter_Ini;
		struct Def_IBF_Allgemein_SOLL	*pSoll_IBF_Ini;
		struct Def_IBF_Allgemein_IST	*pIst_IBF_Ini;
		
		Def_Ein_Puff	*Ein_Puff;			// Pointer auf globale Datenstruktur
		Def_Aus_Puff	*Aus_Puff; 
		Def_Ein_Onli	*Ein_Onli; 
		Def_Aus_Onli	*Aus_Onli;

		Def_Lokal_Puff	*Lokal_Puff;
		
		Def_Ist_Inter	*Ist_Inter;
		Def_Soll_Inter	*Soll_Inter;

		Def_IBF_Allgemein_IST	*Ist_IBF;
		Def_IBF_Allgemein_SOLL	*Soll_IBF;

		RPW*			lRPW;				// Pointer auf globales RPW-Objekt
		int				iter_IBF;			// Iterationszähler

	public:
		int				breakIter;			// Abbruchflag Iteration
		exchPool		ExchPool;

		int init(void);			// Initialisierung einiger Startparameter
		int run(void);			// Iterationsschritt durchführen.
								// Funktionswert gibt Abbr.bedingung an.
								// analog: RWTH_Task
		
		int put_puff(void);		// analog: RWTH_EXCH::put_puff()
		int get_puff(void);		// analog: RWTH_EXCH::get_puff()
		int Main_Control(void);	// analog: RWTH_EXCH::Main_Control()
		
		int genThread(LPVOID);	// Achsen-Positionen Aktualisieren

		float IstPos_SollPos(	float SP,	// Sollposition
								float IP,	// Istposition
								float V ,	// Geschwindigkeit
								float min,  // minpos
								float max,  // maxpos
								float dt);  // Zeitfaktor (t-Zyklus)

		Win_RWTH_EXCH(RPW*, globData*);		// C'tor
		~Win_RWTH_EXCH(void);				// D'tor
};

void Einlesen_IBF_Parameter(struct Def_Ein_Puff&);

#endif	// #ifndef WIN_RWTH_EXCH_HPP