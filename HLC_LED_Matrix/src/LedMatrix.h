/***************************************************************************************************************
FILE: LedMatrix.h
PROJECT: HELIOSLIGHTCONTROL
MODULE: HLC_LED_Matrix
Description: There are all functions round about the led matrix

Compiler dependencies or special instructions:
- HSV_RGB.c
- arduinoFFT.h
- Adafruit_GFX.h
- Adafruit_NeoMatrix.h
- Adafruit_NeoPixel.h

REVISION HISTORY
Date: By: Description:
18.02.2019: Maximilian Klug: First Commit
23.02.19: Maximilian Klug: Made last comments
****************************************************************************************************************/
#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <Arduino.h>
#include "FFT/arduinoFFT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// For FFT
#define SAMPLES 64              //Must be a power of 2
#define SAMPLING_FREQUENCY 5000 //Hz, must be less than 10000 due to ADC
 
class LedMatrix
{    
public:
    // Instance of Neopixel Matrix
	Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(10, 15, 8,
        NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
        NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
        NEO_GRB + NEO_KHZ800);

    // CTOR
    LedMatrix();

    void init();

    void printColorWheel();
    void printBar(int frequenz, int amplitude);

    void doFFT();

    void fullOn();
    void fullOff();

    void setRGB(uint8_t r, uint8_t g, uint8_t b);
    void setHSV(uint16_t h, uint8_t s, uint8_t v);
    void setHEX(unsigned long rgb);

    const uint8_t MatrixHeight = 15;
    const uint8_t MatrixWidth = 10;
private:
    const uint8_t ws2812_pin = 8;
    
    // for FFT
    arduinoFFT FFT = arduinoFFT();
    unsigned int sampling_period_us;
    unsigned long microseconds;
    
    double vReal[SAMPLES];
    double vImag[SAMPLES];
};

#endif