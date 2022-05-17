#include <Arduino.h>
#include "Button.h"
#include "Param.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include <pgmspace.h>  

const uint8_t _img_eSprite_balleX5[] PROGMEM = {
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 0xf7, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xe7, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 0xf7, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x6b, 0x4d, 0xb5, 0x76, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xd3, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc6, 0x18, 0x52, 0x8a, 0xf7, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x6b, 0x4d, 0xb5, 0x76, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xd3, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0x42, 0x08, 0x63, 0x2c, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 0x52, 0x8a, 0x4a, 0x49, 0xe7, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7b, 0xef, 0x42, 0x08, 0xce, 0x59, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0x42, 0x08, 0x63, 0x2c, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 0x52, 0x8a, 0x4a, 0x49, 0xe7, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0x84, 0x10, 0x52, 0x6a, 0xde, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc6, 0x38, 0x63, 0x2c, 0x73, 0x8e, 0xb5, 0x96, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x3c, 0x42, 0x28, 0x84, 0x30, 0x84, 0x30, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0x84, 0x10, 0x52, 0x6a, 0xde, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc6, 0x38, 0x63, 0x2c, 0x73, 0x8e, 0xb5, 0x96, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x8a, 0xd6, 0x7a, 0x9c, 0xb3, 0x9c, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x30, 0xad, 0x75, 0xc5, 0xf8, 0x73, 0x6e, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x83, 0xf0, 0xde, 0xfb, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x8a, 0xd6, 0x7a, 0x9c, 0xb3, 0x9c, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x30, 0xad, 0x75, 0xc5, 0xf8, 0x73, 0x6e, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0x52, 0x8a, 0xf7, 0xbe, 0xce, 0x79, 0x5a, 0xeb, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 0x4a, 0x49, 0xde, 0xfb, 0xef, 0x5d, 0x42, 0x08, 0xef, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x73, 0xae, 0xbd, 0xd7, 0xff, 0xff, 0x63, 0x2c, 0xce, 0x59, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0x52, 0x8a, 0xf7, 0xbe, 0xce, 0x79, 0x5a, 0xeb, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 0x4a, 0x49, 0xde, 0xfb, 0xef, 0x5d, 0x42, 0x08, 0xef, 0x3d, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xbd, 0xb7, 0x84, 0x10, 0xff, 0xff, 0xef, 0x7d, 0x41, 0xe8, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0x52, 0x8a, 0xf7, 0xbe, 0xff, 0xff, 0x63, 0x2c, 0xce, 0x59, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbe, 0x4a, 0x69, 0xde, 0xfb, 0xff, 0xff, 0x9c, 0xf3, 0xa5, 0x14, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xb7, 0x84, 0x10, 0xff, 0xff, 0xef, 0x7d, 0x41, 0xe8, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0x52, 0x8a, 0xf7, 0xbe, 0xff, 0xff, 0x63, 0x2c, 0xce, 0x59, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xa4, 0xf4, 0xa5, 0x14, 0xff, 0xff, 0xff, 0xdf, 0x52, 0x8a, 0xde, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc6, 0x38, 0x73, 0x8e, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x71, 0xb5, 0x96, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x3c, 0x4a, 0x49, 0xf7, 0x7e, 0xff, 0xff, 0xbd, 0xb7, 0x8c, 0x51, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa4, 0xf4, 0xa5, 0x14, 0xff, 0xff, 0xff, 0xdf, 0x52, 0x8a, 0xde, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc6, 0x38, 0x73, 0x8e, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x71, 0xb5, 0x96, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x94, 0x72, 0xb5, 0x96, 0xff, 0xff, 0xff, 0xdf, 0x63, 0x2d, 0xd6, 0x9a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0x7b, 0xef, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xd3, 0xad, 0x35, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x1c, 0x52, 0x8a, 0xf7, 0xbe, 0xff, 0xff, 0xc6, 0x39, 0x7b, 0xaf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x94, 0x72, 0xb5, 0x96, 0xff, 0xff, 0xff, 0xdf, 0x63, 0x2d, 0xd6, 0x9a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0x7b, 0xef, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xd3, 0xad, 0x35, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xb5, 0xb6, 0xff, 0xff, 0xff, 0xdf, 0x6b, 0x4d, 0xd6, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0xa5, 0x34, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe6, 0xfc, 0x52, 0x8a, 0xf7, 0xbe, 0xff, 0xff, 0xce, 0x59, 0x73, 0x8e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xb5, 0xb6, 0xff, 0xff, 0xff, 0xdf, 0x6b, 0x4d, 0xd6, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0xa5, 0x34, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xb5, 0xb6, 0xff, 0xff, 0xff, 0xdf, 0x6b, 0x4d, 0xd6, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0xa5, 0x34, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe6, 0xfc, 0x52, 0x8a, 0xf7, 0xbe, 0xff, 0xff, 0xce, 0x59, 0x73, 0x8e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xb5, 0xb6, 0xff, 0xff, 0xff, 0xdf, 0x6b, 0x4d, 0xd6, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0xa5, 0x34, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xb5, 0xb6, 0xff, 0xff, 0xff, 0xdf, 0x6b, 0x4d, 0xd6, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0xa5, 0x34, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe6, 0xfc, 0x52, 0x8a, 0xf7, 0xbe, 0xff, 0xff, 0xce, 0x59, 0x73, 0x8e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xb5, 0xb6, 0xff, 0xff, 0xff, 0xdf, 0x6b, 0x4d, 0xd6, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0xa5, 0x34, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xb5, 0xb6, 0xff, 0xff, 0xff, 0xff, 0x6b, 0x4d, 0xd6, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0xa5, 0x34, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe6, 0xfc, 0x52, 0x8a, 0xf7, 0xbe, 0xff, 0xff, 0xce, 0x59, 0x73, 0x8e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xb5, 0xb6, 0xff, 0xff, 0xff, 0xff, 0x6b, 0x4d, 0xd6, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0xa5, 0x34, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xdf, 0x7b, 0xaf, 0x94, 0xb2, 0xd6, 0x9a, 0xd6, 0x7a, 0x62, 0xec, 0xbd, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa5, 0x14, 0x73, 0x6e, 0xd6, 0x9a, 0xd6, 0x9a, 0x84, 0x10, 0x94, 0x72, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x52, 0x6a, 0xce, 0x59, 0xd6, 0x9a, 0xa5, 0x34, 0x63, 0x0c, 0xf7, 0x9e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x7b, 0xaf, 0x94, 0xb2, 0xd6, 0x9a, 0xd6, 0x7a, 0x62, 0xec, 0xbd, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa5, 0x14, 0x73, 0x6e, 0xd6, 0x9a, 0xd6, 0x9a, 0x84, 0x10, 0x94, 0x72, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xd6, 0x7a, 0x42, 0x28, 0x5a, 0xab, 0x5a, 0xab, 0x5a, 0xab, 0x52, 0x8a, 0x52, 0x6a, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0x42, 0x28, 0x52, 0xab, 0x5a, 0xab, 0x5a, 0xab, 0x52, 0xab, 0x42, 0x08, 0xe7, 0x1c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x73, 0x6e, 0x52, 0x8a, 0x5a, 0xab, 0x5a, 0xab, 0x5a, 0xab, 0x4a, 0x29, 0xbd, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd6, 0x7a, 0x42, 0x28, 0x5a, 0xab, 0x5a, 0xab, 0x5a, 0xab, 0x52, 0x8a, 0x52, 0x6a, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0x42, 0x28, 0x52, 0xab, 0x5a, 0xab, 0x5a, 0xab, 0x52, 0xab, 0x42, 0x08, 0xe7, 0x1c, 0xff, 0xff, 
  0xff, 0xff, 0xce, 0x79, 0x63, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xfb, 0x4a, 0x6a, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0x42, 0x28, 0xef, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 0x52, 0x8a, 0xe6, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6b, 0x4d, 0xce, 0x59, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0xbd, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x79, 0x63, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xfb, 0x4a, 0x6a, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0x42, 0x28, 0xef, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 0x52, 0x8a, 0xe6, 0xfc, 0xff, 0xff, 
  0xff, 0xff, 0xce, 0x79, 0x63, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe6, 0xfc, 0x4a, 0x69, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0x42, 0x28, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbe, 0x52, 0x8a, 0xe6, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6b, 0x4d, 0xce, 0x79, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0xbd, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x79, 0x63, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe6, 0xfc, 0x4a, 0x69, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0x42, 0x28, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbe, 0x52, 0x8a, 0xe6, 0xfc, 0xff, 0xff, 
  0xff, 0xff, 0xce, 0x79, 0x63, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe6, 0xfc, 0x4a, 0x69, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0x42, 0x28, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbe, 0x52, 0x8a, 0xe6, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6b, 0x4d, 0xce, 0x79, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0xbd, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x79, 0x63, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe6, 0xfc, 0x4a, 0x69, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0x42, 0x28, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbe, 0x52, 0x8a, 0xe6, 0xfc, 0xff, 0xff, 
  0xff, 0xff, 0xce, 0x79, 0x5a, 0xeb, 0xef, 0x7d, 0xf7, 0x7e, 0xf7, 0x7e, 0xd6, 0x7a, 0x4a, 0x6a, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0x42, 0x28, 0xde, 0xdb, 0xf7, 0x7e, 0xf7, 0x7e, 0xe7, 0x3c, 0x52, 0x6a, 0xe6, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6b, 0x4d, 0xc5, 0xf8, 0xf7, 0x7e, 0xf7, 0x7e, 0xf7, 0x7e, 0x7b, 0xf0, 0xbd, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x79, 0x5a, 0xeb, 0xef, 0x7d, 0xf7, 0x7e, 0xf7, 0x7e, 0xd6, 0x7a, 0x4a, 0x6a, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0x42, 0x28, 0xde, 0xdb, 0xf7, 0x7e, 0xf7, 0x7e, 0xe7, 0x3c, 0x52, 0x6a, 0xe6, 0xfc, 0xff, 0xff, 
  0xff, 0xff, 0xce, 0x39, 0x42, 0x08, 0x41, 0xe8, 0x41, 0xe8, 0x41, 0xe8, 0x41, 0xe8, 0x4a, 0x49, 0xf7, 0x9e, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x42, 0x08, 0x41, 0xe8, 0x41, 0xe8, 0x41, 0xe8, 0x41, 0xe8, 0x42, 0x08, 0xde, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x63, 0x0c, 0x42, 0x08, 0x39, 0xe7, 0x39, 0xe8, 0x39, 0xe8, 0x42, 0x08, 0xb5, 0x96, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x39, 0x42, 0x08, 0x41, 0xe8, 0x41, 0xe8, 0x41, 0xe8, 0x41, 0xe8, 0x4a, 0x49, 0xf7, 0x9e, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x42, 0x08, 0x41, 0xe8, 0x41, 0xe8, 0x41, 0xe8, 0x41, 0xe8, 0x42, 0x08, 0xde, 0xdb, 0xff, 0xff, 
  0xff, 0xff, 0xa4, 0xf4, 0x94, 0x92, 0xef, 0x5d, 0xef, 0x5d, 0xef, 0x5d, 0xe6, 0xfc, 0x52, 0x8a, 0xde, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x63, 0x0c, 0xef, 0x3d, 0xef, 0x5d, 0xef, 0x5d, 0xef, 0x5d, 0x7b, 0xcf, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x42, 0x28, 0xde, 0xdb, 0xef, 0x5d, 0xef, 0x5d, 0xef, 0x5d, 0xad, 0x35, 0x84, 0x31, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa4, 0xf4, 0x94, 0x92, 0xef, 0x5d, 0xef, 0x5d, 0xef, 0x5d, 0xe6, 0xfc, 0x52, 0x8a, 0xde, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x63, 0x0c, 0xef, 0x3d, 0xef, 0x5d, 0xef, 0x5d, 0xef, 0x5d, 0x7b, 0xcf, 0xbd, 0xb7, 0xff, 0xff, 
  0xff, 0xdf, 0x73, 0x6e, 0xc6, 0x38, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0xf0, 0xb5, 0xb6, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0x9c, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0xce, 0x39, 0x6b, 0x2d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd6, 0xba, 0x5a, 0xab, 0xf7, 0xbe, 0xff, 0xff, 0xff, 0xdf, 0x73, 0x6e, 0xc6, 0x38, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0xf0, 0xb5, 0xb6, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0x9c, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x84, 0x10, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x55, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xde, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x35, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xb5, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x39, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x3d, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xde, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xad, 0x35, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0xb5, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x39, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0x63, 0x0c, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x52, 0xaa, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0x5a, 0xcb, 0x6b, 0x6e, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x5a, 0xeb, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x52, 0x8a, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6e, 0x6b, 0x4d, 0x6b, 0x2d, 0x4a, 0x29, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0x63, 0x0c, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x52, 0xaa, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0x5a, 0xcb, 0x6b, 0x6e, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x5a, 0xeb, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xb5, 0x96, 0xce, 0x79, 0xce, 0x7a, 0xce, 0x79, 0xce, 0x59, 0x8c, 0x51, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0x9c, 0xb3, 0xce, 0x59, 0xce, 0x59, 0xce, 0x59, 0xce, 0x59, 0xa5, 0x34, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x7b, 0xcf, 0xce, 0x79, 0xce, 0x79, 0xce, 0x59, 0xce, 0x59, 0xbd, 0xd7, 0x4a, 0x29, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xb5, 0x96, 0xce, 0x79, 0xce, 0x7a, 0xce, 0x79, 0xce, 0x59, 0x8c, 0x51, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0x9c, 0xb3, 0xce, 0x59, 0xce, 0x59, 0xce, 0x59, 0xce, 0x59, 0xa5, 0x34, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xbf, 0x52, 0x6a, 0xbd, 0xd7, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0x94, 0x92, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0x9c, 0xf3, 0xde, 0xbb, 0xde, 0xbb, 0xde, 0xbb, 0xde, 0xbb, 0xad, 0x55, 0x6b, 0x4d, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x83, 0xf0, 0xde, 0xbb, 0xde, 0xbb, 0xde, 0xbb, 0xde, 0xbb, 0xc6, 0x38, 0x4a, 0x49, 0xef, 0x5d, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x6a, 0xbd, 0xd7, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0x94, 0x92, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x51, 0x9c, 0xf3, 0xde, 0xbb, 0xde, 0xbb, 0xde, 0xbb, 0xde, 0xbb, 0xad, 0x55, 0x6b, 0x4d, 0xff, 0xff, 
  0xff, 0xdf, 0x6b, 0x6e, 0x52, 0x6a, 0x4a, 0x6a, 0x4a, 0x6a, 0x4a, 0x6a, 0x52, 0x6a, 0x52, 0x6a, 0xad, 0x75, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0x52, 0x6a, 0x4a, 0x69, 0x4a, 0x6a, 0x4a, 0x6a, 0x4a, 0x6a, 0x52, 0x6a, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0xc6, 0x18, 0x52, 0x6a, 0x52, 0x6a, 0x4a, 0x6a, 0x4a, 0x6a, 0x4a, 0x6a, 0x52, 0x6a, 0x62, 0xec, 0xf7, 0x9e, 0xff, 0xff, 0xff, 0xdf, 0x6b, 0x6e, 0x52, 0x6a, 0x4a, 0x6a, 0x4a, 0x6a, 0x4a, 0x6a, 0x52, 0x6a, 0x52, 0x6a, 0xad, 0x75, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0x52, 0x6a, 0x4a, 0x69, 0x4a, 0x6a, 0x4a, 0x6a, 0x4a, 0x6a, 0x52, 0x6a, 0x84, 0x10, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xbf, 0xff, 0xbf, 0xff, 0xbf, 0xff, 0xbf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xff, 

   };

class eSprite_balleX5 : public TFT_eSprite{

    private :
        int _width;
        int _height;
        
    public :
        eSprite_balleX5(TFT_eSPI *ecran) : TFT_eSprite (ecran)
        {
            setColorDepth(16);

        }

        void init()
        {
            setColorDepth(16);

            createSprite(32,36);
 
   
            pushImage(0, 0, 32, 36, (uint16_t *)_img_eSprite_balleX5);
        }
};