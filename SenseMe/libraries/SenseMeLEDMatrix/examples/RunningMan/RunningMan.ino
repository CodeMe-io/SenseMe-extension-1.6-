#include <SenseMeMatrixTwo.h>
// for version 1 cubes 
// #include <SenseMeMatrixOne.h> 
#include <Wire.h>


int delayTime = 100;

static const uint8_t PROGMEM
   sprite1[] =
   { B00001100,
     B00001100,
     B00011000,
     B00011000,
     B00011100,
     B00011000,
     B00111000,
     B00001000 };

static const uint8_t PROGMEM
   sprite2[] =
   { B00001100,
     B00001100,
     B00011000,
     B00011000,
     B00011000,
     B00011000,
     B00011000,
     B00010000 };

static const uint8_t PROGMEM
   sprite3[] =
   { B00001100,
     B00001100,
     B00011000,
     B00111000,
     B00111100,
     B00011100,
     B00100100,
     B00100000 };

static const uint8_t PROGMEM
   sprite4[] =
   { B00001100,
     B00001100,
     B00111000,
     B01011110,
     B00011000,
     B00100100,
     B01000100,
     B00000100 };

static const uint8_t PROGMEM
   sprite5[] =
   { B00000000,
     B00000000,
     B00000000,
     B00000000,
     B00000000,
     B00000000,
     B00000000,
     B00000000 };


void setup() {
   // put your setup code here, to run once:
   SenseMeLEDMatrix.begin();
   SenseMeLEDMatrix.clear();
   SenseMeLEDMatrix.writeDisplay();
}

void loop() {
   SenseMeLEDMatrix.clear();
   SenseMeLEDMatrix.drawBitmap(0, 0, sprite1, 8, 8, LED_ON);
   SenseMeLEDMatrix.writeDisplay();
   delay(delayTime);
   SenseMeLEDMatrix.clear();
   SenseMeLEDMatrix.drawBitmap(0, 0, sprite2, 8, 8, LED_ON);
   SenseMeLEDMatrix.writeDisplay();
   delay(delayTime);
   SenseMeLEDMatrix.clear();
   SenseMeLEDMatrix.drawBitmap(0, 0, sprite3, 8, 8, LED_ON);
   SenseMeLEDMatrix.writeDisplay();
   delay(delayTime);
   SenseMeLEDMatrix.clear();
   SenseMeLEDMatrix.drawBitmap(0, 0, sprite4, 8, 8, LED_ON);
   SenseMeLEDMatrix.writeDisplay();
   delay(delayTime);
}
