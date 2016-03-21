// function display a face depanding on the value of ran
void luckyFace(int ran){
  switch (ran) {
    case 0:
      SenseMeLEDMatrix.clear();
      SenseMeLEDMatrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_GREEN);
      SenseMeLEDMatrix.writeDisplay();
      //pulseColor(255,255,0);
      break;
   case 1:
      SenseMeLEDMatrix.clear();
      SenseMeLEDMatrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_YELLOW);
      SenseMeLEDMatrix.writeDisplay();
      //pulseColor(255,255,255);
      break;
  case 2:
      SenseMeLEDMatrix.clear();
      SenseMeLEDMatrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
      SenseMeLEDMatrix.writeDisplay();
      //pulseColor(0,255,255);
      break;
  default:
      SenseMeLEDMatrix.clear();
      SenseMeLEDMatrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
      SenseMeLEDMatrix.writeDisplay();
  }
  
}
