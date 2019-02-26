/***************************************************************************************************************
FILE: Debug.cpp
PROJECT: HELIOSLIGHTCONTROL
MODULE: HLC_Global
Description: Class for communicate debug messages to the user trough the console or the debug led.


Compiler dependencies or special instructions:
- WirelessConnection.h
- Arduino.h

REVISION HISTORY
Date: By: Description:
23.02.19: Maximilian Klug: Made last comments
****************************************************************************************************************/
#include "Debug.h"


// Constructor with Serial as Reference and the LED Pin
Debug::Debug(Print &print, int led_pin)
{
    printer = &print;
    pinMode(led_pin, OUTPUT);
    m_led = led_pin;
}

// Logs a normal message to the console
void Debug::log(String message)
{
    printer->println("log: " + message);
}

// Becomes a package, which will be looged on the console
void Debug::logPackage(Package p)
{
    printer->print("Recieved Package:");
    printer->println(p.id);
    printer->println(p.data_0);
    printer->println(p.data_1);
    printer->println(p.data_2);
    printer->println(p.data_3);
}

// Toggles the debug LED
void Debug::toggleLed()
{
    digitalWrite(m_led, digitalRead(m_led) ^ 1);
}

// Lets the Debug LED blink once
void Debug::onceBlink()
{
    digitalWrite(m_led, 0);
    delay(20);
    digitalWrite(m_led, 1);
    delay(20);
    digitalWrite(m_led, 0);
}

// Lets the Debug LED blink twice
void Debug::doubleBlink()
{
    onceBlink();
    onceBlink();
}

// Lets the Debug LED blink 3 times
void Debug::tripleBlink()
{
    onceBlink();
    onceBlink();
    onceBlink();
}