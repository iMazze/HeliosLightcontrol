/***************************************************************************************************************
FILE: 
PROJECT: HELIOSLIGHTCONTROL
MODULE: 
Description:


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
****************************************************************************************************************/
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
