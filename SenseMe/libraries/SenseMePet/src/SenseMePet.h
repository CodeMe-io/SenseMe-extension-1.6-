#ifndef __SENSEMEPET_H__
#define __SENSEMEPET_H__

//#include "../SenseMeLEDMatrix/SenseMeLEDMatrix.h"
//#include "../SenseMeAccelerometer/SenseMeAccelerometer.h"
//#include "../SenseMeNeopixel/SenseMeNeopixel.h"
//#include "../SenseMeLightSensor/SenseMeLightSensor.h"


class SenseMePetClass 
{	
	public:
		SenseMePetClass();
		void begin();
		void begin(int happy_prop, int sad_prop, int tired_prop);
		void updateStatus();
		void setStatus(int newStatus);
		int getStatus();
		static void timerIsr();
	private:
		void loadPet();
		void updateMood();
};

extern SenseMePetClass SenseMePet;

#endif