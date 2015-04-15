# Script for fast compiling and test specific parts of the source code


echo "Fall 1:"
echo "  kompiliere IBF_Schuessel.cpp"
echo ""
echo "Fall 2:"
echo "  kompiliere Schuessel_Test.hpp"
echo ""
echo "Fall 3:"
echo "  kompiliere Schuessel_Test.cpp"
echo ""
echo "Fall 4:"
echo "  kompiliere und teste Schuessel_Test.cpp"
echo ""
echo "Fall 5:"
echo "  kompileren von rpw.cpp"

echo "Welcher Fall so ausgeführt werden?"
read -p "" fall
echo ""

case "$fall" in 
  1)
    echo "ibf_Schuessel wird kompiliert"
    c++ source/ibf_Schuessel.cpp -o Schuessel.out;
    echo ""
    echo ""
    echo "Kompilevorgang abgeschlossen"
    ;;
  2)
    echo "Schuessel_Test_Header kompilieren"
    c++ Test/Schuessel/Schuessel_Test.hpp -o Schuessel_Test_Header.out;
    echo ""
    echo ""
    echo "Kompilevorgang abgeschlossen"
    ;;
  3)
    echo "Schuessel_Test kompilieren"
    c++ Test/Schuessel/Schuessel_Test.cpp -o Schuessel_Test.out;
    echo ""
    echo ""
    echo "Kompilevorgang abgeschlossen"
    ;;
  4)
    echo "Schuessel_Test kompilieren und testen"
    c++ Test/Schuessel/Schuessel_Test.cpp -o Schuessel_Test.out;
    echo ""
    echo ""
    echo "Kompilevorgang abgeschlossen"
    echo ""
    if [ -f ./Schuessel_Test.out ]
    then
      echo "Verschiebe Testdatei"
      mv  ./Schuessel_Test.out ./Test/Schuessel/
      echo ""
      echo "Starte Testphase"
      ./Test/Schuessel/Schuessel_Test.out
    else
      echo "Der Kompilvorgang wurde nicht fehlerfrei abgeschlossen"
    fi
    ;;
  5)
    echo "rpw.cpp wird kompiliert"
    c++ ./source/rpw.cpp -o rpw.out
    echo ""
    echo ""
    echo "Kompiliervorgang abgeschlossen"
    ;;
  *)
    echo "Kein gueltiger Fall"
    ;;
esac
