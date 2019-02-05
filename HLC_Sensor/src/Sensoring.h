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
	bool accesControl(); //true= going in, false = going out
	void counter();
	bool personLeft(); //true = minimum one person in room, false = no one left at room



	//settingdata
	uint16_t rate;//measuring rate [1/min] (MAX: 30 /min)
	void setMeasuringRate();

	
private:
	//Initialization of lightsensor
	Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

	//Initialization of temp and humidity sensor
	#define DHTPIN 3 //Data-Pin which the sensor is conected to arduino
 	#define DHTTYPE DHT11 //Typ of DHT-Sensor
	DHT DHT11(DHTPIN, DHTTYPE);
	

	DHT11.begin();

	//Initialization of acces control
	//outdoor
	#define trigger1 4 //Triggerpin of first ultrasonicsensor
	#define echo1 5 //echopin of first ultrasonicsensor
	//indoor
	#define trigger2 6 //Triggerpin of second ultrasonicsensor
	#define echo2 7 //echopin of second ultrasonicsensor

	//variables
	//Measuring data
	uint16_t mRed; //0..255
	uint16_t mGreen; //0..255
	uint16_t mBlue; //0..255
	uint16_t mTemperature;
	uint16_t mHumidity;
	uint16_t mColorTemp;
	uint16_t mLux;
	uint16_t mNumberOfPersons;
	//settingdata
	uint16_t rate;//measuring rate [1/min] (MAX:1200 /min)

	//Methods
	void measuring();
	void measuringLight();
	//converts absolut values of red, green and blue to relative values depending to clearlight brightness
	void convertingRGB(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear);

};


#endif Sensoring_h