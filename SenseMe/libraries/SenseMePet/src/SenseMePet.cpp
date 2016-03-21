#include "SenseMePet.h"

//need to include these libraries both here and in the Sketch"
#include "SenseMeLEDMatrix.h"
#include "SenseMeNeopixel.h"
#include "SenseMeLightSensor.h"
#include "SenseMeAccelerometer.h"
#include "TimerOne.h"

int total, threshold1, threshold2;
volatile int status; // 0=happy 1=sad 2=tired 3=asleep

int i = 0;

#define PERIOD 10
int timerCountdown = PERIOD;


void* pt2Object;		//wrapper function use

//constructor
SenseMePetClass::SenseMePetClass()
{}


//use default values to initialise SenseMe Pet
void SenseMePetClass::begin()
{
	int happy, sad, tired;
	happy = 70;
	sad = 20;
	tired = 20;
	
	begin(happy, sad, tired);
}



//begin : initialise the senseMe pet with proportion of time spent on each mood. 
void SenseMePetClass::begin(int happy, int sad, int tired)
{
	total = happy+sad+tired;
	threshold1 = happy;
	threshold2 = happy+sad;
	status = 0;

	//initialise the SenseMe libraries used for SenseMePEt
	SenseMeLEDMatrix.begin(); //initialise matrix
	SenseMeAccelerometer.begin(); //initialise accelerometer
	//SenseMeButton.begin();
	
	pinMode(13, OUTPUT);   
	
	//use timer 1
	Timer1.initialize(100000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
	Timer1.attachInterrupt( timerIsr ); // attach the service routine here
	timerCountdown =PERIOD;
	
	
  
}


void SenseMePetClass::updateStatus()
{
	if(status == 0)//happy
	{
		long randNum = random(total);
		if (randNum>threshold2)
		{
			status = 2; //tired
		}
		else if (randNum>threshold1)
		{
			status = 1; //sad
		}
	}
	if(status == 1)//sad
	{
		delay(10);
		float magnitude = SenseMeAccelerometer.magnitude();
		//sqrt(pow(SenseMeAccelerometer.getX(),2)+pow(SenseMeAccelerometer.getY(),2)+pow(SenseMeAccelerometer.getZ(),2))
		if(magnitude>1.5)
		{
			status = 0;
		}
	}
	if(status == 2)//tired
	{
		if(SenseMeAccelerometer.getY()<(-0.9))
		{
			status = 3;
		}
	}
	if(status == 3)//asleep
	{
		if(SenseMeAccelerometer.getX()<(-0.9))
		{
			status = 0;
		}
	}
}

int SenseMePetClass::getStatus()
{
	return status;
}

void SenseMePetClass::setStatus(int newStatus) //expected arguments "happy" "sad" "tired" "asleep"
{
	status = newStatus;
}


void SenseMePetClass::updateMood(){

  updateStatus();
  
  if(status == 0)
  {
    SenseMeLEDMatrix.setFace("happy");
  }
  else if(status == 1)
  {
    SenseMeLEDMatrix.setFace("sad");
  }
  else if(status == 2)
  {
    SenseMeLEDMatrix.setFace("yawn");
  }
  else if(status == 3)
  {
    SenseMeLEDMatrix.setFace("sleep");
  }


}

/************ Load Pet **************/
void SenseMePetClass::loadPet()
{

  boolean stage1 = true;
  
  //initiate variables
  
  status = 0;		//always start off happy
  delay(1000);
  SenseMeLEDMatrix.setFace("happy");


}

/// --------------------------
/// Custom ISR Timer Routine
/// --------------------------
void SenseMePetClass::timerIsr()
{
	
	timerCountdown--;
	
	if (timerCountdown == 0) {
	digitalWrite( 13, digitalRead( 13 ) ^ 1 );
	// explicitly cast to a pointer to Classname
		SenseMePetClass* mySelf = (SenseMePetClass*) pt2Object;
		mySelf->updateMood();
		timerCountdown=PERIOD;
		
	}
}


SenseMePetClass SenseMePet = SenseMePetClass();