#ifndef TEST
  #define TEST
    
    #include "../../source/ibf_Schuessel.cpp"
 
    class Schuessel_Test{
      
      public:

        static void bereiteTestVor(void);

        static int radialSchlittenAnfahren_Test(void);

        static int axialGeruestAnfahren_Test(void);

        static int axialSchlittenAnfahren_Test(void);

        static int berechneRingdurchmesser_Test(void);

        static int steuerungZentrierrollen_Test(void);


        static int zentrierRollenOeffnen_Test(void);


        static int zentrierRollenSchliessen_Test(void);


        static int zentrierrollenPositionBerechnen(void);


        static int berechneAlpha(void);

        static int berechneBeta1(void);

        static int berechneBeta2(void);

        static int berechneBeta3(void);

        static int berechneBeta4(void);

  };

#endif
