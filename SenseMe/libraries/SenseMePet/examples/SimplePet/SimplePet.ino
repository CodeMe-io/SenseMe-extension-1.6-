#include <Wire.h>
#include <SenseMeLEDMatrix.h>
#include <SenseMeAccelerometer.h>
#include <SenseMeNeopixel.h>
#include <SenseMeLightSensor.h>
#include <SenseMeButton.h>
int i = 0;

void setup() {
  // put your setup code here, to run once:
  SenseMeLEDMatrix.begin(); //initialise matrix
  SenseMeAccelerometer.begin(); //initialise accelerometer
  SenseMeButton.begin();
  boolean stage1 = true;
  while(stage1)
  {
    long randNum = random(100);
    if(randNum < 80)
    {
      SenseMeLEDMatrix.setFace("happy");
      delay(1000);
    }
    else
    {
      SenseMeLEDMatrix.setFace("sad");
      boolean sad = true;
      while(sad)
      {
        if(getMag()>1.5)
        {
          SenseMeLEDMatrix.setFace("laugh");	
          delay( 1000 );
          sad = false;
          i++;
        }
      }
    }
    if(i>5)
    {
     stage1 = false; 
     i = 0;
    }
  }
  
  boolean stage2 = true;
  while(stage2)
  {
    long randNum = random(100);
    if(randNum < 80)
    {
      SenseMeLEDMatrix.setFace("happy");
      delay(1000);
    }
    else
    {
      SenseMeLEDMatrix.setFace("yawn");
      boolean upright = true;
      while(upright)
      {
        if (SenseMeAccelerometer.getY()  < ( -0.9 ) )
        {
          upright = false;
        }
      }
      SenseMeLEDMatrix.setFace("sleep");		
      delay( 1000 );
      boolean asleep = true;
      while (asleep)
      {
        if (SenseMeAccelerometer.getX() < ( -0.9 ) )
        {
          asleep = false;
        }
      }
      i++;
    }
    if(i>5)
    {
     stage2 = false; 
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  long randNum = 	random( 0 , 100 ) ;
  if (randNum < 80 )
  {
    SenseMeLEDMatrix.setFace("happy");		
    delay( 1000 );
  }
  else
  {
    if (randNum  < 90 )
    {
      SenseMeLEDMatrix.setFace("sad");	
      boolean sad = true;
      while ( sad )
      {
        float Acceleration = getMag();
        if (Acceleration > ( 1.5 ) )
        {
          SenseMeLEDMatrix.setFace("laugh");	
          delay( 1000 );
          sad = false;
        }
      }
    }
    else
    {
      SenseMeLEDMatrix.setFace("yawn");	
      boolean upright = true;
      while (upright)
      {
        if (SenseMeAccelerometer.getY() < ( -0.9 ) )
        {
          upright = false;
        }
      }

      SenseMeLEDMatrix.setFace("sleep");	
      delay( 1000 );
      boolean asleep = true;
      while (asleep == true )
      {
        if (SenseMeAccelerometer.getX() < ( -0.9 ) )
        {
          asleep = false;
        }
      }

    }
  }
  

}

float getMag()
{
  float magnitude = sqrt(pow(SenseMeAccelerometer.getX(), 2)+ pow(SenseMeAccelerometer.getX(), 2)+pow(SenseMeAccelerometer.getX(), 2));
  return magnitude;
}
