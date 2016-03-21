/**
* \addtogroup SenseMeButton
*
* This is the driver code for the button on the SenseMe. This
* uses an ISR to debounce the button - it uses edges rather than
* the value of the digital pin.
* 
* The debounce time can be set in the begin routine, but defaults
* to the DEBOUNCE_DELAY value defined in the header.
*
* @{
*/

/**
* \file 
* 		SenseMe Button driver
* \author
* 		Venus Shum
*/

#include <pins_arduino.h>
#include <SenseMeButton.h>
#include <TimerThree.h>


static int timerValue = 10000;	// timer routine in microseconds. 50ms    

/*---------------------------------------------------------------------------*/
/**
* \brief Constructor
* 
* C++ constructor for this class. Empty.
*/
SenseMeButtonClass::SenseMeButtonClass()
{
}



/*---------------------------------------------------------------------------*/
/**
* \brief begin function - must be called before using other functions
*
* This function enables the button. It can be called with a parameter that
* represents the debounce delay, but this defaults to a sensible value if it
* is not provided.
*  
*/

void SenseMeButtonClass::begin(long debounceDelay) 
{	
	lastChangeTime   = 0;   	// The last time the button input changed
	buttonState      = false; 	// Whether the button is currently pressed
	fallingEdge      = true;	// Whether we're looking for a falling or rising edge in the ISR
	wasPressedState  = false;	// Whether the button has been pressed since we last checked
	wasReleasedState = false;	// Whether the button has been released since we last checked

	
	// Store the given debounce delay
	//
	debounceDelayTime = debounceDelay;
	
	// Set the button to be an input
	//
	pinMode(BUTTON, INPUT);
	
	// Use Timethree to detect interrupt
	
	Timer3.initialize(timerValue);	//time in microsection
	Timer3.attachInterrupt(timercallback, timerValue); 

	reset();
}


/*---------------------------------------------------------------------------*/
/**
* \brief end function - switch off the button
*
* Switch off the interrupt and reset state.
* 
*/
void SenseMeButtonClass::end() 
{
	// Disable the button pin interrupt
	//
	Timer3.stop();

	// Reset the wasPressed/wasReleased state
	//
	reset();	
}

/*---------------------------------------------------------------------------*/
/**
* \brief Check to see if the button is pressed.
*
* Check to see if the button is pressed. If it is not pressed, it is, by
* definition, released.
*
*/
bool SenseMeButtonClass::isPressed()
{	
	// The button state when it was pressed or released will have been set
	// in the ISR.
	//
	return buttonState;
}

/*---------------------------------------------------------------------------*/
/**
* \brief Wait until the button is pressed. Blocking call.
*
* Just loops indefinitely, polling the button state until the button is
* pressed. The event we wait for is the button going down. If the button is
* currently pressed, we wait for it to be released and then wait for it to
* be pressed again
*
*/
void SenseMeButtonClass::waitUntilPressed()
{	
	// If the button is pressed, first wait for it to be
	// released so we get the edge of it going down
	//
	if (isPressed())
		waitUntilReleased();
	
	while (!isPressed());
}

/*---------------------------------------------------------------------------*/
/**
* \brief Wait until the button is released. Blocking call.
*
* Just loops indefinitely, polling the button state until the button is
* released. The event we wait for is the button going up. If the button is
* currently released, we wait for it to be pressed and then wait for it to
* be released again
*
*/
void SenseMeButtonClass::waitUntilReleased()
{	
	// If the button is not pressed, first wait for it
	// to be pressed so we get the edge of it going up
	//
	if (!isPressed())
		waitUntilPressed();
	
	while (isPressed());
}


/*---------------------------------------------------------------------------*/
/**
* \brief Check to see if the button was pressed since our last check.
* \return Whether or not is has been pressed since we last checked.
*
* This function checks to see if the button has been pressed in some
* intervening period when we were not checking it actively. On each check
* we return a boolean that shows whether the button has been pressed, and 
* we reset the state so one can look for a new button press at some later
* point.
*
*/
bool SenseMeButtonClass::wasPressed()
{   bool rv = wasPressedState;

	wasPressedState = false;
	return(rv);
}


/*---------------------------------------------------------------------------*/
/**
* \brief Check to see if the button was released since our last check.
* \return Whether or not is has been released since we last checked.
*
* This function checks to see if the button has been released in some
* intervening period when we were not checking it actively. On each check
* we return a boolean that shows whether the button has been released, and 
* we reset the state so one can look for a new button release at some later
* point.
*
*/
bool SenseMeButtonClass::wasReleased()
{	bool rv = wasReleasedState;

	wasReleasedState = false;
	return(rv);
}


/*---------------------------------------------------------------------------*/
/**
* \brief Reset the wasPressed/wasReleased state.
*
* This function resets the wasPressed/wasReleased state to false - it can
* be used to start a period of looking for a button press, ignoring what
* happened before reset was called. Note, however, that calling wasPressed
* or wasReleased also resets the appropriate part of the state.
*
*/
void SenseMeButtonClass::reset()
{	
	wasPressedState  = false;	
	wasReleasedState = false;
}





/*---------------------------------------------------------------------------*/
/**
* TimerThree Timer call back
* 
*/
void SenseMeButtonClass::timercallback()
{	
	int newbuttonState = digitalRead(BUTTON);
	
	
	if (newbuttonState != SenseMeButton.lastState) {
		Serial.print(1);	
		if (SenseMeButton.fallingEdge) {
			Serial.print(2);
			if ((millis() - SenseMeButton.lastChangeTime) > SenseMeButton.debounceDelayTime) {
				// We have a falling edge and we're not bouncing
				Serial.print(3);
				SenseMeButton.buttonState      = true;
				SenseMeButton.wasPressedState  = true;
				//SenseMeButton.buttonInterrupted = true;		//for use in Application code
			}
			if (SenseMeButton.buttonState) {
				// Now we should look for a non-bouncing rising edge
				Serial.print(4);
				SenseMeButton.fallingEdge = false;		
			}
		}
		
		else {
			if ((millis() - SenseMeButton.lastChangeTime) > SenseMeButton.debounceDelayTime) {
				// We have a rising edge and we're not bouncing
				Serial.print(5);
				SenseMeButton.buttonState 	 = false;
				SenseMeButton.wasReleasedState = true;
			}
			if (!SenseMeButton.buttonState) {
				// Now we should look for a non-bouncing falling edge
				Serial.print(6);
				SenseMeButton.fallingEdge = true;
			}
		}
		
		// This is a change, so we record that fact.
		//
		SenseMeButton.lastChangeTime = millis();
	}
	
	SenseMeButton.lastState = newbuttonState;
	
}

/*---------------------------------------------------------------------------*/
/*
 * Preinstantiate Objects
 */ 
SenseMeButtonClass SenseMeButton = SenseMeButtonClass();

/** @} */
