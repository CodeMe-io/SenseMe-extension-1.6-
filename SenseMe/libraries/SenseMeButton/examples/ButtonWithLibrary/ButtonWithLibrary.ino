#include <SenseMeMatrixTwo.h>
#include <SenseMeButton.h>
#include <Wire.h>
/*
 * Example of a button using SenseMe Button library
 * slightly adapted for the SenseMe from 
 * http://www.arduino.cc/en/Tutorial/Debounce
 *
*/

void setup()
{
  SenseMeLEDMatrix.begin();  // pass in the address
  SenseMeButton.begin();
  Serial.begin(9600);
  SenseMeLEDMatrix.setRotation(0);
  SenseMeLEDMatrix.setTextSize(1);
  SenseMeLEDMatrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  SenseMeLEDMatrix.setTextColor(LED_ON);
  SenseMeLEDMatrix.clear(); 

}

int buttonState = 0;
void loop() {
  // set the LEDs
  if (SenseMeButton.wasReleased()) {
    SenseMeLEDMatrix.clear(); 
    SenseMeLEDMatrix.setCursor(1,0);
    if (buttonState == 0) {
        SenseMeLEDMatrix.print("X");  
        buttonState = 1;
    }
    else {
        SenseMeLEDMatrix.print("O"); 
       buttonState = 0; 
    }
    SenseMeLEDMatrix.writeDisplay();
  }
      
  
}
