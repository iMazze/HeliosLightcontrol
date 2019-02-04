#include "Sensoring.h"

void Sensoring::getTemperature()
{
}

void Sensoring::getHumidity()
{
}

void Sensoring::getColorTemp()
{
}

void Sensoring::getLux()
{
}

bool Sensoring::accesControl()
{
	long time1 = 0;
	long time2 = 0;
	digitalWrite(trigger1, LOW);
	delayMicroseconds(3);
	noInterrupts();
	digitalWrite(trigger1, HIGH); //Trigger impuls 10 us
	delayMicroseconds(10);
	digitalWrite(trigger1, LOW);
	time1 = pulseIn(echo1, HIGH); //echotime1
	interrupts();
	digitalWrite(trigger2, LOW);
	delayMicroseconds(3);
	noInterrupts();
	digitalWrite(trigger2, HIGH); //Trigger impuls 10 us
	delayMicroseconds(10);
	digitalWrite(trigger2, LOW);
	time2 = pulseIn(echo2, HIGH); //echotime2
	interrupts();

	if (time1 < (time2 - 100)) //3 cm tolerance
	{
		return true;
	}
	else if (time2 < (time1 - 100))
	{
		return false;
	}
	else
	{

	}
}

void Sensoring::setMeasuringRate()
{
}

void Sensoring::measuring()
{
	measuringLight();
	mHumidity = DHT11.readHumidity();
	mTemperature = DHT11.readTemperature();

	//delaytime out of measurement rate
	delay(60000/rate);
}

void Sensoring::measuringLight()
{
	uint16_t clear;
	uint16_t red;
	uint16_t green;
	uint16_t blue;
	//get abslout values from sensor
	tcs.getRawData(&red, &green, &blue, &clear);
	convertingRGB(&red, &green, &blue, &clear);
	//calculating Lux
	mLux = calculateLux(red, green, blue);
	//calculating color temperature
	mColorTemp = calculateColorTemperature(red, green, blue);
}

void Sensoring::convertingRGB(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear)
{
	//Division of each proportion of color through intensity of clear light, multiplicated with 256 for a known spread
	float r, g, b;
	r = red; r /= sum;
	g = green; g /= sum;
	b = blue; b /= sum;
	r *= 256; g *= 256; b *= 256;
	mRed = r; mGreen = g; mBlue = b;
}
