/** 
 * @file Schuessel_Test.cpp
 * @brief Datei zum Testen der Methoden der Klasse 
 * \link ibf_Schuessel.cpp \endlink
 *
 * @author Jan Uthoff
 *
 * @version 0.1
 */

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Schuessel_Test.hpp"

struct Def_IBF_Allgemein_IST    Ist_IBF_Test={0};
struct Def_IBF_Allgemein_SOLL   Soll_IBF_Test={0};
struct Def_Ist_Inter            Ist_Inter_Test={0};
struct Def_Soll_Inter           Soll_Inter_Test={0};

int main() {

  int i;
  for(i = 0; i< 5; i++) {
    std::cout << std::endl;
  }
  
  int erfolgreicheTests = 0;
  int gemachteTests = 0;

  // Tests
  erfolgreicheTests += Schuessel_Test::berechneRingdurchmesser_Test(); 
  gemachteTests++;
  erfolgreicheTests += Schuessel_Test::steuerungZentrierrollen_Test();
  gemachteTests++;
  erfolgreicheTests += Schuessel_Test::zentrierRollenOeffnen_Test(); 
  gemachteTests++;
  erfolgreicheTests += Schuessel_Test::zentrierRollenSchliessen_Test();
  gemachteTests++;
  erfolgreicheTests += Schuessel_Test::zentrierrollenPositionBerechnen(); 
  gemachteTests++;
  erfolgreicheTests += Schuessel_Test::berechneAlpha(); 
  gemachteTests++;
  erfolgreicheTests += Schuessel_Test::berechneBeta1(); 
  gemachteTests++;
  erfolgreicheTests += Schuessel_Test::berechneBeta2(); 
  gemachteTests++;
  erfolgreicheTests += Schuessel_Test::berechneBeta3(); 
  gemachteTests++;
  erfolgreicheTests += Schuessel_Test::berechneBeta4(); 
  gemachteTests++;

  std::cout << "Es sind alle Tests durchlaufen worden," 
            << "von den " << gemachteTests <<"  waren " 
            << erfolgreicheTests << " erfolgreich" << std::endl;
  
  
  for(i = 0; i< 5; i++) {
    std::cout << std::endl;
  }


  return 1;
}

void Schuessel_Test::bereiteTestVor(void) {

  
  struct Def_IBF_Allgemein_IST    Ist_IBF_Test={0};
  struct Def_IBF_Allgemein_SOLL   Soll_IBF_Test={0};
  struct Def_Ist_Inter            Ist_Inter_Test={0};
  struct Def_Soll_Inter           Soll_Inter_Test={0};

}


int Schuessel_Test::berechneRingdurchmesser_Test(void) {


  bool bestanden = true;
  int i;
  srand(time(NULL));
  for(i = 0; i < 10; i++) {
    bereiteTestVor();
    Ist_Inter_Test.da = 100;
    if(Ist_Inter_Test.da == 
          ibf_Schuessel::berechneRingdurchmesser(&Ist_IBF_Test, Ist_Inter_Test)
        && bestanden == true)
    {
      bestanden = true;
    }
    else
    {
      bestanden = false;
      int p = ibf_Schuessel::berechneRingdurchmesser(&Ist_IBF_Test, Ist_Inter_Test);
      std::cout << "Fehlgeschlagen bei:" << Ist_Inter_Test.da 
                << "!=" << p << " and : " << p / Ist_Inter_Test.da
                << std::endl;
    }
  }
  
  if(bestanden)
    return 1;
  else
    return 0;
}

int Schuessel_Test::steuerungZentrierrollen_Test(void) {
  return 0;
}

int Schuessel_Test::zentrierRollenOeffnen_Test(void) {
  return 0;
}

int Schuessel_Test::zentrierRollenSchliessen_Test(void) {
  return 0;
}

int Schuessel_Test::zentrierrollenPositionBerechnen(void) {
  return 0;
}

int Schuessel_Test::berechneAlpha(void) {
  /* @warning not implemented yet */
  return 0;
}

int Schuessel_Test::berechneBeta1(void) {
  return 0;
}

int Schuessel_Test::berechneBeta2(void) {
  return 0;
}

int Schuessel_Test::berechneBeta3(void) {
  return 0;
}

int Schuessel_Test::berechneBeta4(void) {
  return 0;
}


