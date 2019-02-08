/***************************************************************************************************************
FILE: 
PROJECT: HELIOSLIGHTCONTROL
MODULE: 
Description:


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
****************************************************************************************************************/
#include "LedMatrix.h"
#include "HSV_RGB.c"



        
LedMatrix::LedMatrix()
{
    matrix.begin();

    // FFT    
    sampling_period_us = round(1500000*(1.0/SAMPLING_FREQUENCY));
}

void LedMatrix::init()
{
    //matrix.fillScreen(matrix.Color(15, 0, 0));
    printColorWheel();
    matrix.show();

    delay(2000);
    matrix.fillScreen(0);
    matrix.show();
}

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

                sat = map(sat, 0, 255, 0, 100);
                val = map(val, 0, 255, 0, 100);


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
 
    matrix.fillScreen(0);
  
  
    for(int i=0; i<17; i++)
    {
        printBar(i-1, (float)arr[i]/3000.0*15.0);

    }
    matrix.show();

}

void LedMatrix::printBar(int frequenz, int amplitude)
{
    for(int i = 0; i < amplitude; i++)
    {
        uint8_t r,g,b;
        // Calc HSV
        //HSV_to_RGB(24*(14-i), 200,200, &r, &g, &b);

        matrix.drawPixel(frequenz, 14-i, matrix.Color(50, 0, 0));
    }
}

void LedMatrix::fullOn()
{
    matrix.fillScreen(0);
    matrix.fillScreen(matrix.Color(255, 255, 255));
    matrix.show();

    delay(500);

    matrix.fillScreen(0);
    matrix.show();
}
void LedMatrix::fullOff()
{
    delay(500);
    matrix.fillScreen(0);
    matrix.show();
    delay(50);
}

void LedMatrix::setRGB(uint8_t r, uint8_t g, uint8_t b)
{
    matrix.fillScreen(0);
    matrix.fillScreen(matrix.Color(r, g, b));
    matrix.show();

}
void LedMatrix::setHSV(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t r,g,b;
    // Calc HSV
    HSV_to_RGB(h, s, v, &r, &g, &b);


    Serial.println(r);
    Serial.println(g);
    Serial.println(b);

    matrix.fillScreen(0);
    matrix.fillScreen(matrix.Color(r, g, b));
    matrix.show();
}