#include "Debug.h"


Debug::Debug(long baudrate, int led_pin)
{
    Serial.begin(baudrate);
    pinMode(led_pin, OUTPUT);
    m_led = led_pin;
}

void Debug::log(String message)
{
    Serial.print("log: " + message);
}

void Debug::toggleLed()
{
    digitalWrite(m_led, digitalRead(m_led) ^ 1);
}