/***************************************************************************************************************
FILE: Debug.cpp
PROJECT: HELIOSLIGHTCONTROL
MODULE: HLC_Sensor
Description:
    Debuging


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
08.02.2019: Maximilian Klug: Coding
08.02.2019: Jonas Schellhorn: Header, etc.
****************************************************************************************************************/
#include "Debug.h"


Debug::Debug(Print &print, int led_pin)
{
    printer = &print;
    pinMode(led_pin, OUTPUT);
    m_led = led_pin;
}

void Debug::log(String message)
{
    printer->println("log: " + message);
}

void Debug::logPackage(Package p)
{
    printer->print("Recieved Package:");
    printer->println(p.id);
    printer->println(p.data_0);
    printer->println(p.data_1);
    printer->println(p.data_2);
    printer->println(p.data_3);
}

void Debug::toggleLed()
{
    digitalWrite(m_led, digitalRead(m_led) ^ 1);
}



void Debug::onceBlink()
{
    digitalWrite(m_led, 0);
    delay(20);
    digitalWrite(m_led, 1);
    delay(20);
    digitalWrite(m_led, 0);
}
void Debug::doubleBlink()
{
    onceBlink();
    onceBlink();
}
void Debug::tripleBlink()
{
    onceBlink();
    onceBlink();
    onceBlink();
}