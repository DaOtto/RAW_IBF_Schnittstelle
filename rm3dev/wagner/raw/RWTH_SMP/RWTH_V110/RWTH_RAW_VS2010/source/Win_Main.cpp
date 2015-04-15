/******************************************************************************
Name:		Win_Main.cpp
Plattform:	WIN32

Funktion:	Testbetrieb des IBF-Technologiemoduls ohne Walzwerk

Autor:		Daniel Otto

Version:	26.10.2014	V1.0
******************************************************************************/

#include "Win_RWTH_EXCH.hpp" // Win_RWTH_EXCH, logChannel, dataLog, globData

#include "rpw.hpp"			// RPW
#include <Windows.h>
#include <time.h>
#include <conio.h>			// _getch()

///////////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

	RPW*		pRpw	= new RPW;
	RPW&		Rpw		= *pRpw;

	globData	gBuf	= {};

	Win_RWTH_EXCH*	pSimRaw	= new Win_RWTH_EXCH(pRpw, &gBuf);
	Win_RWTH_EXCH&	SimRaw	= *pSimRaw;
	
	dataLog		DataLog;

	DataLog.pushChannel( logCh( SimRaw.breakIter				));
	DataLog.pushChannel( logCh( gBuf.Soll_IBF.Zeit.t_Halte		));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.Profilflag			));
	DataLog.pushChannel( logCh( gBuf.Soll_IBF.InitAchse			));
	
	//Soll / Ist Axialschlitten
	DataLog.pushChannel( logCh( gBuf.Aus_Onli.Ibf_nominal.Soll_AS_Pos	));	
	DataLog.pushChannel( logCh( gBuf.Ein_Puff.form_mess_of.dis_aw		));

	//Soll / Ist Radialschlitten
	DataLog.pushChannel( logCh( gBuf.Aus_Onli.Ibf_nominal.Soll_RS_Pos	));
	DataLog.pushChannel( logCh( gBuf.Ein_Puff.form_mess_of.dis_hw_dw	));
	
	//Soll / Ist Axialgeruest
	DataLog.pushChannel( logCh( gBuf.Ein_Onli.Ibf_actual.Ist_AG			));
	
	//Soll / Ist Zentrierrollen
	DataLog.pushChannel( logCh( gBuf.Aus_Onli.Ibf_nominal.Soll_ZA_Pos ));
	DataLog.pushChannel( logCh( gBuf.Ein_Onli.Ibf_actual.Ist_ZEN_A ));
	DataLog.pushChannel( logCh( gBuf.Aus_Onli.Ibf_nominal.Soll_ZE_Pos ));
	DataLog.pushChannel( logCh( gBuf.Ein_Onli.Ibf_actual.Ist_ZEN_E ));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.ZER_Param.delta_ZRA_ZRE ));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.ZER_Param.ZRA.Pos_y ));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.ZER_Param.ZRE.Pos_y ));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.ZER_Param.ZRA.Flag_Kontakt ));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.ZER_Param.ZRE.Flag_Kontakt ));

	//Zentrierrollenposition bezogen auf Ringkontur
	DataLog.pushChannel( logCh( gBuf.Soll_IBF.ZER_Param.ZRA.delta_Ring));
	DataLog.pushChannel( logCh( gBuf.Soll_IBF.ZER_Param.ZRE.delta_Ring));
	
	//Druckrollenposition bezogen auf Ringzentrum
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.DRR_Param.DrR_A.delta_Ring ));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.DRR_Param.DrR_E.delta_Ring ));
	
	//Druckrollenpositionen XY
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.DRR_Param.DrR_A.PosXY.x ));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.DRR_Param.DrR_A.PosXY.y ));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.DRR_Param.DrR_E.PosXY.x ));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.DRR_Param.DrR_E.PosXY.y ));
	DataLog.pushChannel( logCh( gBuf.Soll_Inter.DRR_Param.DrR_A.Pos ));
	DataLog.pushChannel( logCh( gBuf.Soll_Inter.DRR_Param.DrR_E.Pos ));
	
	// Walzform
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.Schuessel.Walzform.da));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.Schuessel.Walzform.RingGeo.a));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.Schuessel.Walzform.RingGeo.b));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.Schuessel.Walzform.Kletterhoehe));
	DataLog.pushChannel( logCh( gBuf.Ist_IBF.Schuessel.Walzform.Kletterwinkel));
	
	// Motordrehzahlen
	DataLog.pushChannel( logCh( gBuf.Soll_Inter.hw_n));
	DataLog.pushChannel( logCh( gBuf.Soll_Inter.kwu_n));
	DataLog.pushChannel( logCh( gBuf.Soll_Inter.kwo_n));
	DataLog.pushChannel( logCh( gBuf.Ist_Inter.hw_n));
	DataLog.pushChannel( logCh( gBuf.Ist_Inter.kwu_n));
	DataLog.pushChannel( logCh( gBuf.Ist_Inter.kwo_n));
	DataLog.pushChannel( logCh( gBuf.Aus_Puff.n_omega.n_hw_motor ));
	DataLog.pushChannel( logCh( gBuf.Aus_Puff.n_omega.n_aw_motor_g_o));
	DataLog.pushChannel( logCh( gBuf.Aus_Puff.n_omega.n_aw_motor_g_u));
	// Initialisierung der Startparameter
	SimRaw.init();			
	
	// Initialisieren der Vor- und Fertigringmasse
	Einlesen_IBF_Parameter(gBuf.Ein_Puff);
	
	// MemPool initialisieren
	SimRaw.put_puff();									

	// Iterationsschleife
	while ((SimRaw.breakIter<4500)&&(gBuf.Ist_IBF.Profilflag!=3)) {
		
		// Gesamtwalzdauer
		gBuf.Ein_Puff.zeit_walzen = gBuf.Ein_Puff.dt_zyklus * SimRaw.breakIter;
		
		// Iteration der Walzstrategie
		SimRaw.run();

		// IST-Werte erzeugen
		SimRaw.genThread((LPVOID)(&SimRaw.ExchPool));

		// Aktuelle Werte in Log schreiben
		DataLog.snapShot();
		//Sleep(100);
		if (SimRaw.breakIter==508)
		{
			int bp=0;
			bp = bp;
		}
	}

	// Log als CSV-Datei exportieren
	DataLog.writeCSV();
	cout << "\r\nhabe fertig... Taste" << endl;
	_getch();

	delete	pRpw, 
			pSimRaw,
			&DataLog;

	return 0;
};


//---------------------------------------------------------------------------
// Funktion: Einlesen der Ringgeometrien aus *.dat-Datei
//---------------------------------------------------------------------------

void Einlesen_IBF_Parameter(struct Def_Ein_Puff &Ein_Puff)
{ 
   
   //Definition der lokalen Variablen
   FILE* Para = NULL;
   float Puffer_l[]={0,0,0,0,0,0};  //Auslesen
   float temp;                      //Auslesen
   int   i=0;                       //Auslesen

   
//---------------------------------------------------------------------------
// Beispiele für Ringgeometrien, die in Bsp.Datei geschrieben werden, sofern 
// diese nicht Vorhanden ist
//---------------------------------------------------------------------------
   char  *Dummy[] = {" (Vorringausendurchmesser    )", 
                     " (Vorringinnendurchmesser    )",
                     " (Vorringhöhe                )",
                     " (Fertigringaussendurchmesser)",
                     " (Fertiggringinnendurchmesser)",
                     " (Fertigringhöhe             )"}; 

   float Puffer[] = {  600.00F,
                       192.00F,
                       176.00F,
                      1304.83F,
                      1064.83F,
                       100.00F}; 
//---------------------------------------------------------------------------

//Los geht's

   // File Handling
    
   if((Para = fopen ("IBF_Parameter.dat", "rt")) == NULL) // öffnen der Textdatei sofern vorhanden
     {
        Para = fopen("IBF_Parameter.dat","w"); //erzeugen einer Textdatei zum schreiben, wenn IBF_*.dat gelöscht wurde 
       
        for(i=0; i<6; ++i)
            {
              fprintf(Para,"%6.2f %-20s \n", Puffer[i], Dummy[i]);
            }//Ende for
        
        fclose(Para); //Schließen der Datei
        exit(1);
     }// Ende if

   if(Para != NULL)  //Textdatei vorhanden
     {
      
      while(fscanf(Para,"%f /&[']c",&temp) !=EOF)
      //while(fscanf(Para,"%f \n",&temp) != EOF) //(fgets(s,1000,Para))!= NULL)//!=EOF) //Einlesen der Datei bis Dateiende......... fscanf(Para,"f \n",&temp) != EOF
           {
             Puffer_l[i]=temp;          //Übergeben der gelesenen Werte an Puffer[i]
             i++;                       //Hochzählen 
             fseek(Para,30L,SEEK_CUR);
           } //Ende while

    fclose(Para); //Schließen der Datei
     }//Ende if

// Übergabe der gelesenen Werte an entsprechende Struktur
   
   
   Ein_Puff.vorform.da = Puffer_l[0];            
   Ein_Puff.vorform.di = Puffer_l[1];            
   Ein_Puff.vorform.hm = Puffer_l[2];     
   
   Ein_Puff.vorform.sm	= (Ein_Puff.vorform.da - Ein_Puff.vorform.di) / 2.0F;
                                                   
   Ein_Puff.soll_walzform.da = Puffer_l[3];      
   Ein_Puff.soll_walzform.di = Puffer_l[4];      
   Ein_Puff.soll_walzform.hm = Puffer_l[5];   
  
};



