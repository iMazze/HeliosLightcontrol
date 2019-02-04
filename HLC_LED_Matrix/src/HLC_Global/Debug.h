#include <Arduino.h>

class Debug
{
    public:
        Debug(long baudrate, int led_pin);
        void log(String message);
        void toggleLed();
    private:
        int m_led;
};