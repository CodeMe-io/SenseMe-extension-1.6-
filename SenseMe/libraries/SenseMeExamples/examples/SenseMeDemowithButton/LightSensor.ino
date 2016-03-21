int y[8];

void lightSensor() {
  // put your main code here, to run repeatedly:
  int a = SenseMeLightSensor.lightLevel();;
  Serial.println(a);
  SenseMeLEDMatrix.clear();
  int b = a/128;
  if (b > 7)
  {
    b = 7;
  }
  for(int i=0; i<7; i++)
  {
    if (!SenseMeButton.wasPressed())  {
    y[i]= y[i+1];
    SenseMeLEDMatrix.drawPixel(i, y[i], LED_ON);
    }else {
              changeMode = true;
              break;
            }
  }
  y[7] = 7-b;
  SenseMeLEDMatrix.drawPixel(7, y[7], LED_ON);
  SenseMeLEDMatrix.writeDisplay();
  
  int c = a/4;
  if(c>255)
  {
    c = 255;
  }
  SenseMeNeopixel.setColor(127,0,127, c);
  
  delay(1000);

}
