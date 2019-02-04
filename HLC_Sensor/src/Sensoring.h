#ifndef Sensoring_h
#define Sensoring_h

#include <Wire.h>
#include "Adafruit_TCS34725.h"

class Sensoring
{
public:
	Sensoring();
	void getTemperature();
	void getHumintiy();
	void getColorTemp();
	void getLux();

	//settingdata
	uint16_t rate;//measuring rate [1/min] (MAX:1200 /min)
	void setMeasuringRate();

	
private:
	//Methods
	void measuring();
	void measuringLight();
	//converts absolut values of red, green and blue to relative values depending to clearlight brightness
	void convertingRGB(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear);
	
	//Initialization of lightsensor
	Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


	//variables
	//Measuring data
	uint16_t mRed; //0..256
	uint16_t mGreen; //0..256
	uint16_t mBlue; //0..256
	uint16_t mTemperature;
	uint16_t mHuminity;
	uint16_t mColorTemp;
	uint16_t mLux;
	//settingdata
	uint16_t rate;//measuring rate [1/min] (MAX:1200 /min)
};


#endif Sensoring_h