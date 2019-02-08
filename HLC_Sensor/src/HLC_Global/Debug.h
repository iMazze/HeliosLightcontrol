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
