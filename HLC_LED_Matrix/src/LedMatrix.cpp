/***************************************************************************************************************
FILE: LedMatrix.cpp
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
#include "LedMatrix.h"
#include "HSV_RGB.c"
        
// Constructor of LedMatrix        
LedMatrix::LedMatrix()
{
    matrix.begin();

    // Setups the FFT    
    sampling_period_us = round(1500000*(1.0/SAMPLING_FREQUENCY));

    for(int i = 0; i<MatrixWidth; i++)
    {
        temperatureBuffer[i] = 10; // Sets to the Minimum value;
    }
}

// Initializes the LedMatrix
void LedMatrix::init()
{
    //matrix.fillScreen(matrix.Color(15, 0, 0));
    //printColorWheel();
    //matrix.show();

    //delay(2000);
    matrix.fillScreen(0);
    matrix.show();
}

// Some demoshit
void LedMatrix::printColorWheel()
{
    int      x, y, hue;
    float    dx, dy, d;
    uint8_t  sat, val;
    uint16_t c;

    uint8_t r,g,b;

    for(y=0; y < MatrixHeight; y++) {
    dy = 15.5 - (float)y;
        for(x=0; x < MatrixWidth; x++) {
            dx = 15.5 - (float)x;
            d  = dx * dx + dy * dy;
            if(d <= (16.5 * 16.5)) { // Inside the circle(ish)?
                hue = (int)((atan2(-dy, dx) + PI) * 1536.0 / (PI * 2.0));
                d = sqrt(d);
                if(d > 15.5) {
                    // Do a little pseudo anti-aliasing along perimeter
                    sat = 255;
                    val = (int)((1.0 - (d - 15.5)) * 255.0 + 0.5);
                } else
                {
                    // White at center
                    sat = (int)(d / 15.5 * 255.0 + 0.5);
                    val = 255;
                }


                HSV_to_RGB(hue, sat, val, &r, &g, &b);
            } else {
                r=0;
                g=0;
                b=0;
            }
            matrix.drawPixel(x, y, matrix.Color(r,g,b));
        }
    }
    
}

// Does an rendering of the FFT
void LedMatrix::doFFT()
{
    /*SAMPLING*/
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(0);
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
 
    /*PRINT RESULTS*/ 
    int arr[16];
    arr[0] = 0;
    int cnt = 0;
    int index = 0;
    for(int i=0; i<(SAMPLES); i++)
    {
        arr[index] += vReal[i];

        if(cnt == 3)
        {
            index ++;
            arr[index] = 0;
            cnt = 0;
        }
        cnt++;
    }

    // Print calculated values to the matrix
    matrix.fillScreen(0);
    for(int i=0; i<17; i++)
    {
        printBar(i-1, (float)arr[i]/3000.0*15.0);

    }
    matrix.show();

}

// Prints one Bar on the Matrix
void LedMatrix::printBar(int frequenz, int amplitude)
{
    for(int i = 0; i < amplitude; i++)
    {
        uint8_t r,g,b;
        // Calc HSV
        HSV_to_RGB(24*(14-i), 200,200, &r, &g, &b);

        //matrix.drawPixel(frequenz, 14-i, matrix.Color(50, 0, 0));
        matrix.drawPixel(frequenz, 14-i,matrix.Color(r,g,b));
    }
}

// Prints a temperature as a bar to the matrix
void LedMatrix::printTemperatureAsBar(int xValue, int temperature)
{
    for(int i = 0; i < temperature; i++)
    {
        uint8_t r,g,b;
        // Calc HSV
        //240...360
        HSV_to_RGB((8*i)+239, 253,150, &r, &g, &b);
        

        matrix.drawPixel(xValue, 15-i,matrix.Color(r,g,b));
    }
}

// Sets the matrix to full on mode
void LedMatrix::fullOn()
{
    matrix.fillScreen(0);
    matrix.fillScreen(matrix.Color(255, 255, 255));
    matrix.show();

    delay(500);

    matrix.fillScreen(0);
    matrix.show();
}

// Sets the matrix full off
void LedMatrix::fullOff()
{
    delay(500);
    matrix.fillScreen(0);
    matrix.show();
    delay(50);
}

// Sets the whole matrix to a specific rgb value
void LedMatrix::setRGB(uint8_t r, uint8_t g, uint8_t b)
{
    matrix.fillScreen(0);
    matrix.fillScreen(matrix.Color(r, g, b));
    matrix.show();
}

// Sets the whole matrix to a specific hex value
void LedMatrix::setHEX(unsigned long rgb)
{
    // Makes a conversation from hex to rgb
    int red, green,blue;
    red = rgb >> 16 ;
    
    green = (rgb & 0x00ff00) >> 8;
    
    blue = (rgb & 0x0000ff);
    
    rgb = 0;
    
    rgb |= red <<16;
    rgb |= blue <<8;
    rgb |=green;


    setRGB(red, green, blue);
}

// Sets the whole matrix to a specific hsv value
void LedMatrix::setHSV(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t r,g,b;

    // Calc HSV
    HSV_to_RGB(h, s, v, &r, &g, &b);

    setRGB(r,g,b);
}

void LedMatrix::addTemperatureToBuffer(int temperature)
{
    // Shift all temperatrures
    for(int i = MatrixWidth - 1; i!=0; i--)
    {
        temperatureBuffer[i] = temperatureBuffer[i-1];
    }
    temperatureBuffer[0] = temperature;
}

void LedMatrix::showTemperatureChart()
{
    matrix.fillScreen(0);
    for(int i = 0; i<MatrixWidth; i++)
    {
        printTemperatureAsBar(i, (temperatureBuffer[i]-10)/2);
    }
    matrix.show();
}