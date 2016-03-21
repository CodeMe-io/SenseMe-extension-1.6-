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

//#ifndef __SenseMeMatrixOne_H__
//#define __SenseMeMatrixOne_H__


class SenseMeMatrixOneClass : public Adafruit_8x8matrix  {
 public:
  SenseMeMatrixOneClass(void);
  void begin(void);
  void setFace(String mood);
  void scrollText(String msg);
 private:


};

extern SenseMeMatrixOneClass SenseMeMatrixOne;

#define SenseMeLEDMatrix SenseMeMatrixOne
//#endif

