/**
* \defgroup SenseMe LED functions
* 
* @{
*/

/**
* \file 
* 		LED matrix driver
* \author
* 		Venus Shum
*/



#include <Arduino.h>
#include <Adafruit_LEDBackpack.h>

//#ifndef __SenseMeMatrixTwo_H__
//#define __SenseMeMatrixTwo_H__


class SenseMeMatrixTwoClass : public Adafruit_BicolorMatrix  {
 public:
  SenseMeMatrixTwoClass(void);
  void begin(void);
  void setFace(String mood);
  void scrollText(String msg);
 private:


};

extern SenseMeMatrixTwoClass SenseMeMatrixTwo;

#define SenseMeLEDMatrix SenseMeMatrixTwo
//#endif

