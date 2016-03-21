#include <SenseMeLEDMatrix.h>
#include <Wire.h>
#include <SenseMeLightSensor.h>

static const uint8_t PROGMEM frame1[]=
{
  B00001100,
  B00001100,
  B00011000,
  B00011000,
  B00011100,
  B00011000,
  B00111000,
  B00001000}; //This is the first frame of the animation

static const uint8_t PROGMEM frame2[]=
{
  B00001100,
  B00001100,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00001000}; //This is the second frame of the animation

static const uint8_t PROGMEM frame3[]=
{
  B00001100,
  B00001100,
  B00011000,
  B00111000,
  B00111100,
  B00011100,
  B00100100,
  B00100000};

static const uint8_t PROGMEM frame4[]=
{
  B00001100,
  B00001100,
  B00111000,
  B01011110,
  B00011000,
  B00100100,
  B01000100,
  B00000100}; //This is the fourth frame of the animation
  
int delayTime = 100;


void setup()
{
  SenseMeLEDMatrix.begin(); // initialises the LEDMatirx
  SenseMeLightSensor.begin(); //initialises the LightSensor
}
#define LEDColour LED_YELLOW

void loop() {
  // this draws the four frames with a delay in between to produce the animation
  SenseMeLEDMatrix.clear();
  SenseMeLEDMatrix.drawBitmap(0, 0, frame1, 8, 8, LEDColour);
  SenseMeLEDMatrix.writeDisplay();
  delay(delayTime );
  SenseMeLEDMatrix.clear();
  SenseMeLEDMatrix.drawBitmap(0, 0, frame2, 8, 8, LEDColour);
  SenseMeLEDMatrix.writeDisplay();
  delay(delayTime);
  SenseMeLEDMatrix.clear();
  SenseMeLEDMatrix.drawBitmap(0, 0, frame3, 8, 8, LEDColour);
  SenseMeLEDMatrix.writeDisplay();
  delay(delayTime);
  SenseMeLEDMatrix.clear();
  SenseMeLEDMatrix.drawBitmap(0, 0, frame4, 8, 8, LEDColour);
  SenseMeLEDMatrix.writeDisplay();
  delay(delayTime);

}
