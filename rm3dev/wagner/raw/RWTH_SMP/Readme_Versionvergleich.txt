Version RWTH_V100
- erste Umsetzung des MRAW-Programmierung (mapw.cpp, axpro.h usw) auf Banningwalzwerk
- Vorgabe der Geschwindigkeit RADIALSCHLITTEN und AXIALSCHLITTEN m�glich
- Vorgabe der Postion noch nicht m�glich, hier fahren Achsen auf die min. Position (Kollision), die unter CARWIN definiert worden ist.

Mai 2006, Dipl.-Ing. D. Michl


Version RWTH_V101
- Neue *.h-File (onli_cnc_s.hpp, raw_t_cnc_s.hpp), die alte Version erstetzen
- Neue RAW_SMP.386 und TRT_SMP.386 (Datum 13.06.2006 und 26.06.2006)
- Neue Konfig.ini (10.07.2006)
- Vorgabe von Vorschub, Position und Kraft f�r Axialschlitten und Radialschlitten m�glich
- ! siehe auch info.txt (10.07.2006) f�r n�here Infos

17.07.2006, Dipl.-Ing. D.Michl

Version RWTH_V102

- Vollst�ndige Programmdatei zum radialen Profilieren. Mit diesem Stand wurde das DFG-Vorhaben abgeschlossen
- IBF-struct.hpp beinhaltet noch alle Strukturen (IST-IBF,Soll-IBF, Cr_Berechnung, Breitung, Radial_Flex_Prof)

03.04.2007, Dipl.-Ing. D.Michl

Version RWTH_V103

- Start mit Programmcode Axialprofilieren
- Aufsplitten der IBF-struct.hpp in IBF_radflex.hpp, IBF_axproflex.hpp.
- L�schen der M�glichkeiten 'Manuelle Steuerung', da diese nicht ben�tigt werden
- Class RPW erweitert um Funktion IstIbf_IstInter, f�r Daten austausch zwischen IST_IBF Ist_Inter als Call by Reference.
- Pfeiloperatoren/Punktoperatoren jetzt in rpw.cpp-File sauber verwendet. 
  Variablenwerte werden jetzt in Form von Referenzen ge�ndert (linke Seite), auslesen der Werte erfolgt durch das Verwenden von Zeigern (rechte Seite)


19.07.2007, Dipl.-Ing. D.Michl


Version RWTH_V104

- Einbinden der ge�nderten Headerdatein f�r die Benutzung der erneuerten SMS *386-Datein
- IBF-Messachsen 1-3 k�nnen sind in die Ist_Inter-Struktur eingebunden worden. Ini-Datei muss noch angepasst werden.
  Hier sind jetzt zus�tzliche Messungen m�glich, in dem Zusatzachsen (Z.B. weitere Tastrollen u.�) angebunden werden.
- Ist-Position der Zentriearme werden jetzt erfasst -> bereits eingebunden in Ist_Inter (rpw.h)
- Ist-Position des AG kann jetzt erfasst werden. Muss noch in IBF-Modul interiert werden. Bisher wird die Position aus Ringdurchmesser und TR-Position berechnet...

01.08.2007 Dipl.-Ing. D.Michl


Version RWTH_V107

Aktueller Stand CARWIN (inkl. SMS-Axialprofilieren) mit neuen Header f�r IBF-Modul
- Letzte Version des flexiblen axialen Profilierens vor dem Ausscheiden von MIR ;-)
- 'Flexibel axial Profieren' mit Biss 
- mit Turbinen (Biss 2te Ebene)
- DA Jenkouk
- St�tzstellenfunktion ca (cr hinterlegt, muss nur noch eingebunden werden -> Sascha Frank fragen)


Viel Spass beim weiterarbeiten
09.07.2008 Dipl.-Ing. D. Michl

  

Version RWTH_V108
Header aktualisiert f�r *.386-Datein mit den Versionsnummern CNC V138.0 und TRT V126 Rev. 1 .
13.01.2014 Dr.Michl



Version RWTH_V109
30.01.2014 J.Seitz, J.Uthoff
Neue Struktur f�r das Walzen von Sch�sseln unter Einsatz der Druckrollen. 
Grundpositionierung der Zentrierrollen entsprechend der Dissertation von V. Jenkouk
Automatisches �ffnen und Schlie�en der Zentrierrollen, sobal der Ring angedreht ist bzw. klettert (vgl. Esaform Paper Seitz)



Version RWTH_V110
30.3.2015 D.Otto
- Aenderungen des C++ Quellcodes um Projekt auch mit VS2010 kompilieren zu koennen (-> Debugumgebung)
- Header aktualisiert f�r Einsatz der Druckrollen (raw_t_cnc_s.hpp v.129 Rev.1)
- Steuerungsmoeglichkeit der Zentrierrollen implementiert (IBF_Schuessel_ZR_pos.cpp ; IBF_Geometrie_tool.cpp)
  -> Positionierung anhand 'Abstand zur Ringkontur'
- Steuerungsmoeglichkeit der Druckrollen implementiert (IBF_Schuessel_DR_pos.cpp ; IBF_Geometrie_tool.cpp)
  -> Positionierung anhand 'Abstand zur Ringkontur'
  -> Bestimmung der Koordinaten des Kontaktpunktes 'DrR<->Ring' (->Ringgeometriesensor)
- spezielle kinematische Berechnungen zur Steuerung des Schuesselwalzprozesses implementiert (IBF_Schuessel_Form.cpp)
- Walzstrategie 'Schuesselwalzen' implementiert (IBF_Schuessel.cpp)
- Konfigurationsdatei 'IBF_Data.ini' erweitert
- Kommentare erweitert, zur Erstellung einer Dokumentation durch 'doxyGen'

- Stand 30.3.2015: - Positionssteuerung ZR,RS,AG,AS getestet.
                   - Drehzahlsteuerung der Walzenantriebe m�ssen noch getestet werden
                   - Druckrollensteuerung noch nicht m�glich (keine Reaktion auf Sollwertvorgaben; Istwerte sind ok)
                   - Ablauf der Walzstrategiesteuerung in 'Debugumgebung' getestet
		   - Endg�ltige Tests der Walzstrategie stehen noch aus
  

