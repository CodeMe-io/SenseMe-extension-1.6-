#include <Wire.h>
#include <SenseMeAccelerometer.h>
#include <SenseMeMatrixTwo.h>
#include <SenseMeNeopixel.h>
#include <SHT2x.h>
#include <SenseMeBluetooth.h>
#include <SenseMeButton.h>
#include <SenseMeLightSensor.h>
#include <LEDMatrixConstants.h>
/*
 SenseMeDemo for SenseMe hardware v2
 The demo changes with the press of a button

 This demo uses:-
  - LED Matrix - dual colour
  - Bluetooth
  - NeoPixel - In the cube
  - Random number
  - Accelerometer
  - button uses timer 3 to drive
 
 Author: Venus SHum
*/


int mode = 0, lastmode = 9;
//Bluetooth
String content = "";
//char * content;
char character;
char incomingByte;  // incoming data

boolean DEBUG = true;
uint8_t brightness=0, dir=0;
uint8_t state=0, r=0, g=0, b=255;

bool changeMode = false;
long lastChanged;

    
void setup()
{
  Serial.begin(115200);
  
  
  SenseMeLEDMatrix.begin();  // pass in the address
  SenseMeAccelerometer.begin();
  SenseMeLEDMatrix.clear();
  SenseMeLEDMatrix.writeDisplay();
  randomSeed(analogRead(0));
  SenseMeNeopixel.begin();
  //SenseMeNeopixel.setColor(0,0,0); 
  SenseMeLightSensor.begin();
  SenseMeBluetooth.begin();
  SenseMeButton.begin();
  openSequence();
  //clear this flag to begin fresh - it's a workaround
  //SenseMeButton.wasPressed();
}

long ran;
bool buttonInterrupted;
void loop()
{   
  float amp;
  float xyz[3];
  
  //check if the button has been pressed to change the mode
  if (SenseMeButton.wasPressed() || changeMode == true) {
      mode ++ ;
      if (mode > 4) {
        mode = 0;
      }
      Serial.println(mode);
      changeMode = false;
  }
  
  SenseMeLEDMatrix.setRotation(0);
  //determine the demo mode 
  switch (mode) {
    case 0: //mode 0 temperature light
      SenseMeLEDMatrix.clear(); 
      SenseMeLEDMatrix.drawBitmap(0, 0, thermo_bmp, 8, 8, LED_GREEN);
      SenseMeLEDMatrix.writeDisplay();
      delay(1500);  // if button pressed at this time, we can't react until the delay is unblocked
      tempLight();
      break;
      
    case 1:  //mode 1 Mood icon, shake to get a new random icon
      SenseMeAccelerometer.xyz(xyz);
      amp = abs(xyz[0])  + abs(xyz[1]) + abs(xyz[2]);
      delay(50);    //accelerometer read needs to be ready. 
      //Serial.println(amp);
      if (amp > 1.5 || mode!=lastmode) {
        if (millis() - lastChanged > 1000) {
         SenseMeLEDMatrix.clear(); 
         SenseMeLEDMatrix.writeDisplay();
         delay(500);
         ran = random(3);
         luckyFace(ran);
         lastChanged = millis();
        }
      }
       break;
       
     case 2://mode 2 Bluetooth
       if (mode!=lastmode) {
         SenseMeLEDMatrix.clear(); 
         SenseMeLEDMatrix.drawBitmap(0, 0, blue_bmp, 8, 8, LED_GREEN);
         SenseMeLEDMatrix.writeDisplay();
         SenseMeLEDMatrix.setTextSize(1);
         SenseMeLEDMatrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
         SenseMeLEDMatrix.setTextColor(LED_YELLOW);
         Serial1.begin(9600); // initialization
       }
       Bluetooth();
       break;
       
     case 3:  //mode 3 light sensor
       lightSensor();
       break;
       
     case 4: 
       lightDemo();
       break;
  }
  
  lastmode = mode;
        
}




void openSequence() {
    SenseMeLEDMatrix.clear();
  int d = 0;
  for (int r=0; r < 4; r++) {  
    for (int i=r; i<8-r; i++) {
      pulse();
      SenseMeLEDMatrix.drawPixel(i, r, LED_GREEN);  
      SenseMeLEDMatrix.writeDisplay();
      delay(d);
      d-=1;
      d = constrain(d, 0, 255) ;
    }
    
    for (int i=r+1; i<8-r; i++) {
      pulse();
      SenseMeLEDMatrix.drawPixel(7-r, i, LED_YELLOW);  
      SenseMeLEDMatrix.writeDisplay();
      delay(d);
      d-=1;
      d = constrain(d, 0, 255) ;
    }
    
    for (int i=r+1; i<8-r; i++) {
      pulse();
      SenseMeLEDMatrix.drawPixel(7-i, 7-r, LED_RED);  
      SenseMeLEDMatrix.writeDisplay();
      delay(d);
      d-=1;
      d = constrain(d, 0, 255) ;
    }
    
    for (int i=r+1; i<7-r; i++) {
      pulse();
      SenseMeLEDMatrix.drawPixel(r, 7-i, LED_YELLOW);  
      SenseMeLEDMatrix.writeDisplay();
      delay(d);
      d-=1;
      d = constrain(d, 0, 255) ;
    }
    
  }
  delay(1000);
  SenseMeNeopixel.setBrightness(0);
  
}

//pulse the colour of the neopixel by 1 step. 
void pulse(void) {
  for (int i=0; i<8; i++) { 
    pulseColor(255,0,255);
  }
}
