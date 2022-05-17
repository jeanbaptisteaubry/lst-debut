#include <Arduino.h>
#include "Button.h"
#include "Param.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include <pgmspace.h>  

const uint8_t _img_eSprite_balleX3[] PROGMEM = {

};

class eSprite_balleX3 : public TFT_eSprite{

    private :
        int _width;
        int _height;
        
    public :
        eSprite_balleX3(TFT_eSPI *ecran) : TFT_eSprite (ecran)
        {
            setColorDepth(16);

        }

        void init()
        {
            setColorDepth(16);

            createSprite(32,36);
 
   
            pushImage(0, 0, 32, 36, (uint16_t *)_img_eSprite_balleX3);
        }
};