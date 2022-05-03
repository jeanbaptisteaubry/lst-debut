#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

class Ecran {
private:
    TFT_eSPI ecran = TFT_eSPI();

public:
    Ecran()
    {
        //ecran = TFT_eSPI();
        
    }

    void EcranDAccueil(){ 
        ecran.drawCentreString("Initialisation", 80, 40, 2);
    }

    void EcranModeAffichage(String str)
    {
       
    }


};