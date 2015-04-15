
30.04.2007 
- erste Tests zum Verfahren des Axialger�stes 
- RWTH_V103 vorbereiten f�r Axialprofilieren.
D.Michl


19.07.2007 
- Start mit Programmcode Axialprofilieren
- Aufsplitten der IBF-struct.hpp in IBF_radflex.hpp, IBF_axproflex.hpp.
- L�schen der M�glichkeiten 'Manuelle Steuerung', da diese nicht ben�tigt werden
- Class RPW erweitert um Funktion IstIbf_IstInter, f�r Daten austausch zwischen IST_IBF Ist_Inter als Call by Reference.
- Pfeiloperatoren/Punktoperatoren jetzt in rpw.cpp-File sauber verwendet. 
  Variablenwerte werden jetzt in Form von Referenzen ge�ndert (linke Seite), auslesen der Werte erfolgt durch das Verwenden von Zeigern (rechte Seite)
D.Michl


20.07.2007
- Funktion RPW::Kr_Geo_berechnen unter ibf_tool.cpp zur Berechnung von Kragengeometrien.
- Modifizieren der Funktion RPW::Modus_AG ibf_tool.cpp, hiermit erstmals Vorgabe der AG-Modi als Funktion m�glich. Test steht aus.
  AG_Act wird jetzt durch Vorwahlm�glichkeit in IBF_PARA.ini gesetzt (rwthexch.cpp -> Funktionsblock Initialisierung)
- Anlegen der Testcode 10030 'Kragengeometrie', 10031 'Axialger�st' unter test_ibf.cpp
D.Michl


24.07.2007
- Funktion AGR_Soll_Pos, AGR_Pr_Wanddicken_Verhaeltnis_proz, AGR_Nachfuehr_Entscheider zum Nachf�hren des AG eingebunden.
- AGR-Position sollte jetzt stimmen
D.Michl


30.07.2007
- Axilschlitten f�hrt jetzt wahlweise in Kraft oder in Position auf die vorgegebene Ringh�he an 
- Case-Anweisungen zum Walzzylkus "Flexibel Radial" wurden in eigene Funktion RPW::flexibel_Radial() eingebunden. Funktion befindet sich in   der neuen Datei ibf_flex_radial.cpp (Header rpw.hpp)
D.Michl

31.07.2007
- Es wurde eine Funktion RPW::flexibel_Axial() eingebunden (ibf_flex_axial.cpp) in der die Berechnungen f�r den Walzzyklus Axialprofilieren eingebunden werden
- test_ibf.cpp wurde sortiert
- Anfahren Dornwalze Kraft getestet -> Bugs vorhanden
D.MIchl

01.08.2007
Ende Abschluss Version V103 durch erweiterung der Strukturen Seites SMS am 01.August 2007
-> S.A Version V104
D.Michl

