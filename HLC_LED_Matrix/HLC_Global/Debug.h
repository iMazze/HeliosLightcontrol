/***************************************************************************************************************
FILE: Debug.h
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
#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include "WirelessConnection.h"

class Debug
{
    public:
        Debug(Print &print, int led_pin);
        void log(String message);
        void logPackage(Package p);
        void toggleLed();
        void onceBlink();
        void doubleBlink();
        void tripleBlink();

    private:
        int m_led;
        Print* printer;
};

#endif