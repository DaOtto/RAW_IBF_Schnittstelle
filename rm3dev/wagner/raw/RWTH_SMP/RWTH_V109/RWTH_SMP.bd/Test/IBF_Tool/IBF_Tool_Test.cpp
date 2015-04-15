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
#include "IBF_Tool_Test.hpp"


int main() {

  int i;
  for(i = 0; i< 5; i++) {
    std::cout << std::endl;
  }
  
  int erfolgreicheTests = 0;
  int gemachteTests = 0;


  std::cout << "Es sind alle Tests durchlaufen worden," 
            << "von den " << gemachteTests <<"  waren " 
            << erfolgreicheTests << " erfolgreich" << std::endl;
  
  
  for(i = 0; i< 5; i++) {
    std::cout << std::endl;
  }


  return 1;
}

int IBF_Tool_Test::IBFPARA_auslesen(){
  return 0;
}
