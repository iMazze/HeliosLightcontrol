#include "Sensoring.h"

void Sensoring::getTemperature()
{
}

void Sensoring::getHumintiy()
{
}

void Sensoring::getColorTemp()
{
}

void Sensoring::getLux()
{
}

void Sensoring::setMeasuringRate()
{
}

void Sensoring::measuring()
{
	measuringLight();

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
