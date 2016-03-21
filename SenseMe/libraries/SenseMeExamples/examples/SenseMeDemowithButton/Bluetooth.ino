// Bluetooth receiver, display any received messages

void Bluetooth() {
  //Serial.println("Bluetooth");
  //Serial1.println("HC-05");
  content = "";
  
  while(Serial1.available()) 
  {
      character = Serial1.read();
      content.concat(character);
      Serial.println(character);
      //content[sizeof(content)]=character;
      delay(50);
  }
  
  if (content.length() >0) 
  {
    
    Serial.println(content.length());
    Serial.println(content);
    int st = 0;
    if (content[0] =='1') {
      SenseMeLEDMatrix.setTextColor(LED_RED);
      st = 1;
    }
    else if (content[0] =='2') {
      SenseMeLEDMatrix.setTextColor(LED_YELLOW);
      st = 1;
    }
    else if (content[0] =='3') {
      SenseMeLEDMatrix.setTextColor(LED_GREEN);
      st = 1;
    }
    //int led = content.toInt();  // use atoi to convert the string to an int
          int len=content.length();
          
          for (int8_t x=0; x>=-((len+1)*6); x--) {
            if (!SenseMeButton.wasPressed())  {
              SenseMeLEDMatrix.clear();
              SenseMeLEDMatrix.setCursor(x,0);
              SenseMeLEDMatrix.print(&content[st]);
              SenseMeLEDMatrix.writeDisplay();
              delay(100);
            }else {
              changeMode = true;
              break;
            }
          }
          
          SenseMeLEDMatrix.clear();
          SenseMeLEDMatrix.writeDisplay();
          

    content = "";
    //delay(10); 
  }
  
}
