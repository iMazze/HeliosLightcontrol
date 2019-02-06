#include <Arduino.h>

#include "FFT/arduinoFFT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// For FFT
#define SAMPLES 64             //Must be a power of 2
#define SAMPLING_FREQUENCY 5000 //Hz, must be less than 10000 due to ADC
 

class LedMatrix
{    
public:
	Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(10, 15, 8,
        NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
        NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
        NEO_GRB + NEO_KHZ800);

    LedMatrix();

    void init();

    void printColorWheel();
    void printBar(int frequenz, int amplitude);
    //void printFFT(double fftArr[SAMPLES]);
    void doFFT();

    void fullOn();
    void fullOff();

    void setRGB(uint8_t r, uint8_t g, uint8_t b);
    void setHSV(uint16_t h, uint8_t s, uint8_t v);

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