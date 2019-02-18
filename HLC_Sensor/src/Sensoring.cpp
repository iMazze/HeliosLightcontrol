/***************************************************************************************************************
FILE: 
PROJECT: HELIOSLIGHTCONTROL
MODULE: 
Description:


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
08.02.2019: Jonas Schellhorn: Header, etc.
****************************************************************************************************************/
#include "Sensoring.h"

Sensoring::Sensoring()
{
	dht1.begin();
	mNumberOfPersons=0;
}

uint16_t Sensoring::sendTemperature()
{
	return (mTemperature);
}

uint16_t Sensoring::sendHumidity()
{
	return mHumidity;
}

uint16_t Sensoring::sendColorTemp()
{
	return mColorTemp;
}

uint16_t Sensoring::sendLux()
{
	return mLux;
}

uint16_t Sensoring::sendRed()
{
	return mRed;
}
uint16_t Sensoring::sendGreen()
{
	return mGreen;
}
uint16_t Sensoring::sendBlue()
{
	return mBlue;
}
uint16_t Sensoring::sendNumberOfPersons()
{
	return mNumberOfPersons;
}

void Sensoring::accesControl()
{
	//sensor 1 outside, sensor 2 indoor
	long time1 = 0;
	long time2 = 0;
	//supersonicsensor 1
	digitalWrite(trigger1, LOW);
	delayMicroseconds(3);
	noInterrupts();
	digitalWrite(trigger1, HIGH); //Trigger impuls 10 us
	delayMicroseconds(10);
	digitalWrite(trigger1, LOW); //falling flank
	time1 = pulseIn(echo1, HIGH); //echotime1
	interrupts();
	//supersonicsensor 2
	digitalWrite(trigger2, LOW);
	delayMicroseconds(3);
	//noInterrupts();
	digitalWrite(trigger2, HIGH); //Trigger impuls 10 us
	delayMicroseconds(10);
	digitalWrite(trigger2, LOW); //falling flank
	time2 = pulseIn(echo2, HIGH); //echotime2
	//interrupts();
	//if distance of one sensor between doorframe (which is indicated through measured time)
	//is shorter than the other one, someone is going through the door
	//if outer sensor was shorter, someone went in
	if (time1 < (time2 - 800)) //~10 cm tolerance
	{
		++mNumberOfPersons;
		//delay(1000);
	}
	else if (time2 < (time1 - 800))
	{
		if (mNumberOfPersons!=0)
		{
			--mNumberOfPersons;
		}
		//delay(1000);
	}
}

bool Sensoring::personLeft()
{
	if (mNumberOfPersons>=1)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Sensoring::measuring()
{
	measuringLight();
	mHumidity = (uint16_t) dht1.readHumidity();
	mTemperature = (uint16_t)dht1.readTemperature();
}

void Sensoring::measuringLight()
{
	uint16_t clear;
	uint16_t red;
	uint16_t green;
	uint16_t blue;
	//get abslout values from sensor
	tcs.getRawData(&red, &green, &blue, &clear);
	convertingRGB(red, green, blue, clear);
	//calculating Lux
	mLux = tcs.calculateLux(red, green, blue);
	//calculating color temperature
	mColorTemp = tcs.calculateColorTemperature(red, green, blue);
}

void Sensoring::convertingRGB(uint16_t red, uint16_t green, uint16_t blue, uint16_t clear)
{
	//Division of each proportion of color through intensity of clear light, multiplicated with 255 for a known spread
	float r, g, b;
	uint16_t sum = clear;
	r = red; r /= sum;
	g = green; g /= sum;
	b = blue; b /= sum;
	r *= 255; g *= 255; b *= 255;
	mRed = r; mGreen = g; mBlue = b; 
}
