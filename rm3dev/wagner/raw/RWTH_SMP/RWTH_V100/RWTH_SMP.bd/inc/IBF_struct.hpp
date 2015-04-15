#ifndef _IBF_struct_HPP
   #define _IBF_struct_HPP

//#define MRAW 0          // 0= Modellwalzwerk || 1=Banning Ringwalzwerk
#define RAW  0

//---------------------------------------------------------------------------
//          Protottypen der IBF_Funktionen                                    
//---------------------------------------------------------------------------

void Einlesen_IBF_Parameter(struct Def_Ein_Puff *Ein_Puff);

void IBF_Werte(struct Def_IBF_Allgemein_SOLL *Soll_IBF, struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_Ein_Puff Ein_Puff);




//---------------------------------------------------------------------------
//                  Allgemeine IST-Werte der IBF-Module
//---------------------------------------------------------------------------
struct Geometrie
{
int a;
};


struct Def_IBF_Allgemein_IST
{

//---------------------------------------------------------------------------
// Definition der allgemeinen Variabeln
// ehemals Axpro.H
//---------------------------------------------------------------------------
   
int AUTO;               // 1: automatisch; 0: manuell gesteuerte Profilierung 
int StartPos;           // Bedingung für Anfahren der Startpositionen (erste Profilposition) 
                     
                        // Info Modellwalzwerk: wird in mapwonli zu Null und in interfac wieder 1 gesetzt    
char ManAuswahl;        // Auswahl von Aktion bei manueller Steuerung


int  Profilflag;        // Einlesen des Profilflags, das in der Soll-Struktur geschrieben wird
char InitAchse;         // Einlesen des Flags für Anfahren der Startposition in Reihenfolge RS, AG, AS
char ExitAchse;         // Flag für Lüften in Reihenfolge vgl InitAchse

float RS_Pos;           // Aktuelle Dornposition
float AG_Pos;           // Aktuelle Position Axialgerüst
float ASO_Pos;          // Aktuelle Axialschlittenposition oben
                        
float TR_Pos;           // Aktuelle Tastrollen-(Laser-)position           
 
float FR;               // aktuelle rad. Walzkraft   
float FA;               // aktuelle axiale Walzkraft  

#ifdef MRAW
float ASU_Pos;          // Aktuelle Axialschlittenposition unten
#endif

float RS_Pos_Null;      // bla_Null -> Initialisierung nach manueller Anfahrt / vor Profilieren 
float ASO_Pos_Null;
float AG_Pos_Null;           

float RS_Pos_Start;     // Positionen in 'Walzen' vor Profilieren 
float AG_Pos_Start;  
float ASO_Pos_Start;                                                       

float FR_f;             //
float FA_f;             // in Intefac gefiltere FA           || gefilterte Werte 
float s_f ;             // in interfac gefilterte Wanddicke  || gefilterte Werte



//---------------------------------------------------------------------------
// TO-DO : in separate Struktur "AxialeVariable" überführen

struct Geometrie Kragenwalze;


float Del_Kr_AGR;       // Wert für Axialprofilieren
float Pos_auf_Mantel;   // Position des Ringaußendurchmessers auf der Mantelfläche	

//---------------------------------------------------------------------------
//--------------------------Variablen aus IBFPARA3.c-------------------------
//---------------------------------------------------------------------------
// TODO -> in separate Struktur überführen

float D_Null;              // Aussendurchmesser 
float Wandstaerke_Null;    // Anfangswanddicke ->notwendig, da am Modellwalzwerk Daten nicht eingelesen werden können
float Start_Ringhoehe;     // Anfangsringhöhe
float Werkzeugdurchmesser; // Durchmesser Dornwalzenaufsatz


float Schalter_Kont_DisKo; // 0 = kontinuierlicher Vorschub, 1= diskontinuierlicher Vorschub (eps/Weg), 2=(eps/Geschwindigkeit)
float eps_Vorschub; // epsilon für diskontinuierlich

};



//---------------------------------------------------------------------------
//                  Allgemeine SOLL-Werte der IBF-Module
//---------------------------------------------------------------------------

struct Def_IBF_Allgemein_SOLL
{

//---------------------------------------------------------------------------
// Definition der allgemeinen Variabeln
// ehemals Axpro.H
//---------------------------------------------------------------------------
   

int  Profilflag;        //Schreiben des Profilflags, das in der Ist-Struktur eingelesen wird 
char InitAchse;         //Schreiben des Flags für Anfahren der Startposition in Reihenfolge RS, AG, AS
char ExitAchse;         // Flag für Lüften in Reihenfolge vgl InitAchse

// Radialschlitten
float RS_Pos;           // Aktuelle Dornposition
float Soll_RS_Pos;      // Sollposition Radialschlitten 
float Soll_RS_Pos_end;  // Soll-Endposition
float Soll_RS_V;        // Sollgeschwindigkeit Radialschlitten 
float RS_Pos_Null;      // Initialisierung nach manueller Anfahrt / vor Profilieren 
float RS_Pos_Start;     // Positionen in 'Walzen' vor Profilieren 
float FR;               // aktuelle rad. Walzkraft   


// Axialschlitten oben
float ASO_Pos;          // Aktuelle Axialschlittenposition oben
float Soll_ASO_Pos;     // Sollposition Axialschlitten oben
float Soll_ASO_Pos_alt; // Sollposition des oberen Axialschlitten zum Zeitpunkt t-1 benötigt in case 12/13
float Soll_ASO_V;       // Sollgeschwindigkeit Axialschlitten oben
float ASO_Pos_Null;
float ASO_Pos_Start;
float FA;               // aktuelle axiale Walzkraft  


// Axialschlitten unten      
#ifdef MRAW
float ASU_Pos;          // Aktuelle Axialschlittenposition unten
#endif
float Soll_ASU_Pos;     // Sollposition Axialschlitten unten
float Soll_ASU_V;       // Sollgeschwindigkeit Axialschlitten unten

// Axialgeruest
float AG_Pos;           // Aktuelle Position Axialgerüst
float Soll_AG_Pos;      // Sollposition Axialgerüst
float Soll_AG_V;        // Sollgeschwindigkeit Axialgerüst
float AG_Pos_Null;           
float AG_Pos_Start;

// Tastrolle Laser                        
float TR_Pos;           // Aktuelle Tastrollen-(Laser-)position 

// Zentrierarm Einlaufseite = rechts
float Soll_ZAR_V;        // Sollgeschwindigkeit Zentrierarm rechts


// Zentrierarm Auslaufseite = links
float Soll_ZAL_V;        // Sollgeschwindigkeit Zentrierarm links          

//----------------------------------------------------------------------------------------------
//--------------------------Variablen aus IBFPARA3.c--------------------------------------------
//----------------------------------------------------------------------------------------------
//TODO: separieren in eigene Struktur
float Umdrehungen;         // Umdrehungen für Rundungsphase
float delta_s;             // Eindringtiefe 
float Vorschubgeschw_Dw;   // Vorschubgeschwindigkeit Dornwalze
float Steg;

};




#endif	
