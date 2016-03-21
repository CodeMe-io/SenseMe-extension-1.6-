#include <SenseMeMatrixOne.h>
#include <LEDMatrixConstants.h>
#include <Arduino.h>
/*
static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100};
static const uint8_t PROGMEM	
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 };
	
static const uint8_t PROGMEM
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };
	
static const uint8_t PROGMEM	
  laugh_bmp[] =
  { B00111100,
    B01100110,
    B11011011,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 };
	
static const uint8_t PROGMEM	
  yawn_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01011010,
    B00111100 };
	
static const uint8_t PROGMEM	
  sleep_bmp[] =
  { B00000001,
    B00000011,
    B00011100,
    B00001000,
    B00011100,
    B11100000,
    B01000000,
    B11100000 };

static const uint8_t PROGMEM	
  blue_bmp[] =
  { B00011000,
    B10010100,
    B01010010,
    B00110100,
    B00111000,
    B01010100,
    B10010010,
    B00011100 };

static const uint8_t PROGMEM	
  thermo_bmp[] =
  { B00111000,
    B00101110,
    B00101000,
    B00101110,
    B00101000,
    B01000100,
    B01000100,
    B00111000 };
	  
*/

SenseMeMatrixOneClass::SenseMeMatrixOneClass(void){
}

void SenseMeMatrixOneClass::begin(void) {
  i2c_addr = 0x70;

  Wire.begin();

  Wire.beginTransmission(i2c_addr);
  Wire.write(0x21);  // turn on oscillator
  Wire.endTransmission();
  blinkRate(HT16K33_BLINK_OFF);
  
  setBrightness(15); // max brightness
}

// construct a bi-colour matrix



void SenseMeMatrixOneClass::setFace(String mood){
  SenseMeMatrixOne.clear();
  if(mood== "happy"){
      SenseMeMatrixOne.drawBitmap(0, 0, smile_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixOne.writeDisplay();
  }
  else if (mood == "sad"){
      SenseMeMatrixOne.drawBitmap(0, 0, frown_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixOne.writeDisplay();
  }
  else if (mood == "neutral"){
      SenseMeMatrixOne.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixOne.writeDisplay();
  }
  else if (mood == "laugh"){
      SenseMeMatrixOne.drawBitmap(0, 0, laugh_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixOne.writeDisplay();
  }
  else if (mood == "sleep"){
      SenseMeMatrixOne.drawBitmap(0, 0, sleep_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixOne.writeDisplay();
  }
  else if (mood == "yawn"){
      SenseMeMatrixOne.drawBitmap(0, 0, yawn_bmp, 8, 8, LED_GREEN);
      SenseMeMatrixOne.writeDisplay();
  }
}

void SenseMeMatrixOneClass::scrollText(String msg) {
	SenseMeMatrixOne.clear();
	SenseMeMatrixOne.setTextWrap(false);
	SenseMeMatrixOne.setTextColor(LED_YELLOW);
	
	int len = msg.length();
	for (int8_t x=0; x>=-len * 6; x--) {
      SenseMeMatrixOne.clear();
      SenseMeMatrixOne.setCursor(x,0);
      SenseMeMatrixOne.print(msg);
      SenseMeMatrixOne.writeDisplay();
    delay(100);
  }
	
}



SenseMeMatrixOneClass SenseMeMatrixOne = SenseMeMatrixOneClass();
