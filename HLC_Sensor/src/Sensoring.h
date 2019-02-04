#ifndef Sensoring_h
#define Sensoring_h

#include <Wire.h>
#include "Adafruit_TCS34725.h"

class Sensoring
{
public:
	Sensoring();
	void getTemperature();
	void getHumidity();
	void getColorTemp();
	void getLux();
	bool accesControl();// True= going in, False = going out


	//settingdata
	uint16_t rate;//measuring rate [1/min] (MAX: 30 /min)
	void setMeasuringRate();

	
private:
	//Initialization of lightsensor
	Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

	//Initialization of temp and huminity sensor
	dht11 DHT11;
	//Pin of sensor at arduino
	#define DHT11PIN 8 //TODO: ANPASSEN!!
	dht.begin();

	//Initialization of acces control
	//outdoor
	#define trigger1 3 //TODO: ANPASSEN!!
	#define echo1 2 //TODO: ANPASSEN!!
	//indoor
	#define trigger2 3 //TODO: ANPASSEN!!
	#define echo2 2 //TODO: ANPASSEN!!

	//variables
	//Measuring data
	uint16_t mRed; //0..256
	uint16_t mGreen; //0..256
	uint16_t mBlue; //0..256
	uint16_t mTemperature;
	uint16_t mHumidity;
	uint16_t mColorTemp;
	uint16_t mLux;
	//settingdata
	uint16_t rate;//measuring rate [1/min] (MAX:1200 /min)

	//Methods
	void measuring();
	void measuringLight();
	//converts absolut values of red, green and blue to relative values depending to clearlight brightness
	void convertingRGB(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear);

};


#endif Sensoring_h