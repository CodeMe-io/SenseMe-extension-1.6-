#include <SenseMeMatrixTwo.h>
#include <LEDMatrixConstants.h>

	  


SenseMeMatrixTwoClass::SenseMeMatrixTwoClass(void){
}

void SenseMeMatrixTwoClass::begin(void) {
  i2c_addr = 0x70;

  Wire.begin();

  Wire.beginTransmission(i2c_addr);
  Wire.write(0x21);  // turn on oscillator
  Wire.endTransmission();
  blinkRate(HT16K33_BLINK_OFF);
  
  setBrightness(15); // max brightness
  clear();
  writeDisplay();
}

// construct a bi-colour matrix



void SenseMeMatrixTwoClass::setFace(String mood){
  SenseMeMatrixTwo.clear();
  if(mood== "happy"){
      SenseMeMatrixTwo.drawBitmap(0, 0, smile_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixTwo.writeDisplay();
  }
  else if (mood == "sad"){
      SenseMeMatrixTwo.drawBitmap(0, 0, frown_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixTwo.writeDisplay();
  }
  else if (mood == "neutral"){
      SenseMeMatrixTwo.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixTwo.writeDisplay();
  }
  else if (mood == "laugh"){
      SenseMeMatrixTwo.drawBitmap(0, 0, laugh_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixTwo.writeDisplay();
  }
  else if (mood == "sleep"){
      SenseMeMatrixTwo.drawBitmap(0, 0, sleep_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixTwo.writeDisplay();
  }
  else if (mood == "yawn"){
      SenseMeMatrixTwo.drawBitmap(0, 0, yawn_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixTwo.writeDisplay();
  }
}

void SenseMeMatrixTwoClass::scrollText(String msg) {
	SenseMeMatrixTwo.clear();
	SenseMeMatrixTwo.setTextWrap(false);
	SenseMeMatrixTwo.setTextColor(LED_YELLOW);
	
	int len = msg.length();
	for (int8_t x=0; x>=-len * 6; x--) {
      SenseMeMatrixTwo.clear();
      SenseMeMatrixTwo.setCursor(x,0);
      SenseMeMatrixTwo.print(msg);
      SenseMeMatrixTwo.writeDisplay();
    delay(100);
  }
	
}


SenseMeMatrixTwoClass SenseMeMatrixTwo = SenseMeMatrixTwoClass();
