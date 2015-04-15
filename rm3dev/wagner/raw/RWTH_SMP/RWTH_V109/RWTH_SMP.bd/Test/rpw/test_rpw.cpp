/* file for testing the file rpw.cpp */

#include <iostream>
#include "./rpw.cpp"

int main() {

  

  std::cout << "starte test" << std::endl;

  RPW::Main(
        Def_Ist_Inter          Ist_Inter,
        Def_IBF_Allgemein_IST  Ist_IBF, 
        Def_Soll_Inter         *Soll_Inter
        Def_IBF_Allgemein_SOLL *Soll_IBF);

    std::cout << "test beendet" << std::endl;


  return 1;
}
