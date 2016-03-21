#include <SenseMeLightSensor.h>
#include <SenseMeNeopixel.h>
#include <Wire.h>

//Step 1: Define variables

void setup() {
  // put your setup code here, to run once:
  SenseMeLightSensor.begin(); // this initializes the sensor
  SenseMeNeopixel.begin(); // this initializes the LED output
}

void loop() {
  // put your main code here, to run repeatedly:
  //Step 2: Read in the light level

  //Step 3: Turn on and off the light
  
}

