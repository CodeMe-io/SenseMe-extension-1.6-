/**
* \addtogroup SenseMeMagnetometer
*
* This is the driver code for Magnetometer on the SenseMe
* In v2.1 this magnetometer is a freescale FXMS3110
*
* @{
*/

/**
* \file 
* 		SenseMe magnetometer driver
* \author
* 		SenseMe team: support@SenseMe.org
*/

#include <pins_arduino.h>
//#include "../Wire/Wire.h"
#include <SenseMeMagnetometer.h>
#include <Wire.h>

/*---------------------------------------------------------------------------*/
/**
* \brief Constructor
* 
* C++ constructor for this class. Empty.
*/
SenseMeMagnetometerClass::SenseMeMagnetometerClass()
{
}

/*---------------------------------------------------------------------------*/
/**
* \brief begin function - must be called before using other functions
*
* This function enables the magnetometer.
* The magnetometer is an I2C device so we initialise the I2C communications,
* make contact with the magnetometer, and check that it's what we think it is.
*
* We set the sampling rate to 10Hz, but where the values are from a heavily
* oversampled set of values 
*/
void SenseMeMagnetometerClass::begin() 
{	uint8_t reg;

	// Join I2C bus as master
	//
	Wire.begin();
	
	// Check to see that the device is there
	//
	Wire.beginTransmission(FXMS3110_IIC_ADDRESS);
	int error = Wire.endTransmission();  
	if (error != 0) {
		Serial.println("Error: I2C device not found");
		return;
	}
	
	// Check that it's the device we think it is
	//
	readReg(FXMS3110_WHO_AM_I, &reg);
	if (reg != FXMS3110)  {
		Serial.println("Error: Not an FXMS3110");
		return;
	}

	// Set this to raw mode - no user correction
	// and automatically enable reset to deal with big magnetic
	// fields
	readReg(FXMS3110_CTRL_REG2,  &reg);
	reg |= AUTO_MRST_EN_MASK | RAW_MASK;
	writeReg(FXMS3110_CTRL_REG2, &reg);


	standby();		// Stop the magnetometer

	// Set 10Hz data rate = 1280 Hz ADC with 128 times oversampling
	readReg(FXMS3110_CTRL_REG1, &reg);
	reg &= ~(DR_MASK | OS_MASK);
	reg |= DATA_RATE_1280_128;
	writeReg(FXMS3110_CTRL_REG1, &reg);
	
	activate();		// And start it again
}

/*---------------------------------------------------------------------------*/
/**
* \brief end function - switch off the magnetometer
*
* Send the magnetometer to sleep
*
*/
void SenseMeMagnetometerClass::end() 
{
	standby();		// Stop the magnetometer
}


/*---------------------------------------------------------------------------*/
/**
* \brief Read the xyz values from the magnetometer
* \param buf A buffer of floats to put the magnetometer values into
*
* Get the instantaneous magnetometer values for the xyz axes. Convert the
* 16 bit digital value to a float value. 
*
*/
void SenseMeMagnetometerClass::xyz(float buf[3])
{	uint8_t reg[6];
	

	// Check to see if XYZ data is ready to read
	readReg(FXMS3110_DR_STATUS, reg);
	if (reg[0] & ZYXDR_MASK != 0)  {
		
		// Do a multiple read starting with X_MSB
		// because this is the first numbered
		// Read all the MSBs and LSBs = 6 registers
		//
		readReg(FXMS3110_OUT_X_MSB, reg, 6);
		
		// The most significant 8 bits are stored
		// in the MSB register, the other 8 bits
		// the LSB register. The complete 16 bit
		// number is stored as 2's complement
		// 
		for (int i = 0; i < 3; i++) {
			float f = (reg[2*i] << 8) + reg[2*i+1];
			buf[i] = f;
		}
	}

}

/*---------------------------------------------------------------------------*/
/**
* \brief Read the xyz values from the magnetometer
* \param buf A buffer of floats to put the magnetometer values into
*
* Get the instantaneous magnetometer values for the xyz axes. Convert the
* 16 bit digital value to a float value. 
*
*/
float SenseMeMagnetometerClass::getX()
{	uint8_t reg[6];
	float result;

	// Check to see if XYZ data is ready to read
	readReg(FXMS3110_DR_STATUS, reg);
	if (reg[0] & ZYXDR_MASK != 0)  {
		
		// Do a multiple read starting with X_MSB
		// because this is the first numbered
		// Read all the MSBs and LSBs = 6 registers
		//
		readReg(FXMS3110_OUT_X_MSB, reg, 6);
		
		// The most significant 8 bits are stored
		// in the MSB register, the other 8 bits
		// the LSB register. The complete 16 bit
		// number is stored as 2's complement
		// 
		
		float f = (reg[0] << 8) + reg[1];
		result = f;
	}
	return result;

}

float SenseMeMagnetometerClass::getY()
{	uint8_t reg[6];
	float result;


	// Check to see if XYZ data is ready to read
	readReg(FXMS3110_DR_STATUS, reg);
	if (reg[0] & ZYXDR_MASK != 0)  {
		
		// Do a multiple read starting with X_MSB
		// because this is the first numbered
		// Read all the MSBs and LSBs = 6 registers
		//
		readReg(FXMS3110_OUT_X_MSB, reg, 6);
		
		// The most significant 8 bits are stored
		// in the MSB register, the other 8 bits
		// the LSB register. The complete 16 bit
		// number is stored as 2's complement
		// 
		
		float f = (reg[2] << 8) + reg[3];
		result = f;
	}
	return result;

}

float SenseMeMagnetometerClass::getZ()
{	uint8_t reg[6];
	float result;


	// Check to see if XYZ data is ready to read
	readReg(FXMS3110_DR_STATUS, reg);
	if (reg[0] & ZYXDR_MASK != 0)  {
		
		// Do a multiple read starting with X_MSB
		// because this is the first numbered
		// Read all the MSBs and LSBs = 6 registers
		//
		readReg(FXMS3110_OUT_X_MSB, reg, 6);
		
		// The most significant 8 bits are stored
		// in the MSB register, the other 8 bits
		// the LSB register. The complete 16 bit
		// number is stored as 2's complement
		// 
		
		float f = (reg[4] << 8) + reg[5];
		result = f;
	}
	return result;

}


/*---------------------------------------------------------------------------*/
/**
* \brief Read the temperature value from the magnetometer
* \return The 8 bit temperature value in 2s complement - values lie between
*         -40�C and 125�C, but are uncalibrated.
*
* Get the temperature as measured by the magnetometer - the temperature
* of the die. The register contains the die temperature in degrees C expressed
* as an 8-bit 2's complement number. The sensitivity of the temperature sensor
* is factory trimmed to 1�C/LSB. The temperature sensor offset is not factory
* trimmed and must be calibrated by the user software if higher absolute
* accuracy is required. Note: The register allows for temperature measurements
* from -128�C to 127�C but the output range is limited to -40�C to 125�C. The
* temperature data is updated on every measurement cycle.
*
*/
int8_t SenseMeMagnetometerClass::temperature()
{	uint8_t reg;

	readReg(FXMS3110_DIE_TEMP, &reg);

	return (int8_t) reg;
}


/*---------------------------------------------------------------------------*/
/**
* \brief Activate the sensor
*
* Set the Active bit in System Control Register 1
*
*/
void SenseMeMagnetometerClass::activate()
{	uint8_t reg;

	readReg(FXMS3110_CTRL_REG1,  &reg);
	reg |= ACTIVE_MASK;
	writeReg(FXMS3110_CTRL_REG1, &reg);
}


/*---------------------------------------------------------------------------*/
/**
* \brief Put sensor into standby mode
*
* Clear the Active bit in System Control Register 1
*
*/
void SenseMeMagnetometerClass::standby()
{	uint8_t reg;
	readReg(FXMS3110_CTRL_REG1,  &reg);
	reg &= ~ACTIVE_MASK;
	writeReg(FXMS3110_CTRL_REG1, &reg);
}


/*---------------------------------------------------------------------------*/
/**
* \brief Internal routine to write magnetometer registers
* \param firstReg The first register to write
* \param buf      The buffer containing things to write to the registers
* \param nRegs	  Optional: The number of registers to write - defaults to 1 
*
* Do a multiple register write of the FXMS3110 over the I2C bus - where the
* number of registers written might only be one (as it is if the optional
* nRegs parameter is omitted).
*
*/
void SenseMeMagnetometerClass::writeReg(int firstReg, const uint8_t *buf, uint8_t nRegs)
{
	// Write out the address of the first register, then the set of values
	// for that and all subsequent registers. Release the I2C bus when we're done
	//
	Wire.beginTransmission(FXMS3110_IIC_ADDRESS);
	Wire.write(firstReg);
	Wire.write(buf, nRegs);
	Wire.endTransmission();
}

/*---------------------------------------------------------------------------*/
/**
* \brief Internal routine to read magnetometer registers
* \param firstReg The first register to read
* \param buf      The buffer to which to read from the registers
* \param nRegs	  Optional: The number of registers to read - defaults to 1 
*
* Do a multiple register read of the FXMS3110 over the I2C bus - where the
* number of registers read might only be one (as it is if the optional
* nRegs parameter is omitted).
*
*/
void SenseMeMagnetometerClass::readReg(int firstReg, uint8_t *buf, uint8_t nRegs)
{
	// Write out the register we'd like to start with reading
	// Hold the I2C bus since we're going to read values back
	//
	Wire.beginTransmission(FXMS3110_IIC_ADDRESS);
	Wire.write(firstReg);
	Wire.endTransmission(false); 

	// Read all the registers we're interested in,
	// but release the I2C bus when we're done.
	// This is determined by the default third
	// parameter to requestFrom
	//
	Wire.requestFrom((uint8_t)FXMS3110_IIC_ADDRESS, nRegs);

	int i = 0;
	while (Wire.available() && i < nRegs)
		buf[i++] = Wire.read();
}


/*---------------------------------------------------------------------------*/
/*
 * Preinstantiate Objects
 */ 
SenseMeMagnetometerClass SenseMeMagnetometer = SenseMeMagnetometerClass();

/** @} */
