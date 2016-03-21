#include <SenseMeNeopixel.h>

void setup() {
  // put your setup code here, to run once:
  SenseMeNeopixel.begin();
}

int brightness = 0;
int dir = 0;

void loop() {
  // put your main code here, to run repeatedly:
  SenseMeNeopixel.setColor(255,15,200, brightness);
  if (dir == 0) 
	brightness ++;
  else 
	brightness --;
  if (brightness == 255)
    dir = 1;
  if (brightness == 0)
    dir = 0;
  delay(10);
  
}
