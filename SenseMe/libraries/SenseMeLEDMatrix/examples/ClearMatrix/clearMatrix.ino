#include <SenseMeLEDMatrix.h>
#include <Wire.h>
//#include <SenseMeMatrixOne.h>

void setup() {
  // put your setup code here, to run once:
  SenseMeLEDMatrix.begin();
  SenseMeLEDMatrix.clear();
  SenseMeLEDMatrix.writeDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
}
