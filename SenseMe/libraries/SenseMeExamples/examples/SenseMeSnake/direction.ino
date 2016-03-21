float LT = 0.5;
float HT = 1.5;
float TT = 0.3;
int orient = 0;

/*************************************************************
 getOrientation function
 *************************************************************/
int getOrientation() {
  float xyz[3];
  char message[] = "0";
  SenseMeAccelerometer.xyz(xyz);
  int newOrient;
  
  if (abs(xyz[1]) > LT && abs(xyz[1]) < HT) {
    if (xyz[0] > TT) {
      newOrient = 1;
    }
    else if (xyz[0]< -TT) { 
      newOrient = 2;
    }
    
    else if (xyz[2] > TT) {
      newOrient = 3;
    }
    else if (xyz[2]< -TT) { 
      newOrient = 4;
    }
    else {
      newOrient = 5;
    }
  }
  else {
    newOrient = 0;
  }
  
  Serial.print("orientation=");
  Serial.println(newOrient);

   
  if (DEBUG) {
      Serial.print("Accelerometer x=");
      Serial.print(xyz[0]);
      Serial.print(", y=");
      Serial.print(xyz[1]);
      Serial.print(", z=");
      Serial.print(xyz[2]);
      Serial.print(", O=");
      Serial.println(newOrient);
    }
    return newOrient;
}

