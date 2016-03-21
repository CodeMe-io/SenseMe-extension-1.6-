// pulse the Neopixel LED in turns with RGB
uint8_t delayval=5;

int pulsestate = 0;
int pulsedir = 0;

void pulseColor(uint8_t r, uint8_t g, uint8_t b) {
  int p_step = 1;
  if (pulsedir == 0) {
      // Neopixel.Color takes RGB values, from 0,0,0 up to 255,255,255
      SenseMeNeopixel.setBrightness(pulsestate),
      SenseMeNeopixel.setColor(r,g,b); // Moderately bright green color.
      SenseMeNeopixel.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
      pulsestate+=p_step;
      if (pulsestate >= 255) {
        pulsedir = 1;
        pulsestate = 255;
      }
  }
  else{
      // Neopixel.Color takes RGB values, from 0,0,0 up to 255,255,255
      SenseMeNeopixel.setBrightness(pulsestate),
      SenseMeNeopixel.setColor(r,g,b); // Moderately bright green color.
      SenseMeNeopixel.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
      pulsestate-=p_step;
      if (pulsestate <= 0) {
        pulsedir = 0;
        pulsestate = 0;
      }
  }
  
}

void setColor() {
    SenseMeNeopixel.setBrightness(brightness),
    SenseMeNeopixel.setColor(r,g,b); // Moderately bright green color.
    SenseMeNeopixel.show(); // This sends the updated pixel color to the hardware.
    if (dir == 0)   {
        if (brightness<255) brightness++;
        else 
          dir = 1;
    }
    else {
        if (brightness > 0)
          brightness --;
        else {
          dir = 0;
          switch(state) {
            case 0:
              state = 1; r=0; g=255; b=0; break;
            case 1:
              state = 2; r=255; g=0; b=0; break;
            case 2:
              state = 3; r=255; g=255; b=255; break;
            case 3:
              state = 0; r=0; g=0; b=255; break;
          }
    }
    }
}
