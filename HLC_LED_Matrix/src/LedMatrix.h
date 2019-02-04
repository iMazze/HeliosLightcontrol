#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

class LedMatrix
{    
public:
    LedMatrix();

    doSickShit();
private:
    const uint8_t ws2812_pin = 12;
    Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, ws2812_pin,   
        NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
        NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
        NEO_GRB            + NEO_KHZ800);
    uint16_t colors[];
};