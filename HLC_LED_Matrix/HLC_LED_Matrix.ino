#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"

#include "src/LedMatrix.h"

const uint16_t timer_interval = 50; // 50ms
uint32_t counter = 0;



WirelessConnection wc = WirelessConnection(0xB00B1E5000LL);
Debug d = Debug(9600, LED_BUILTIN);
LedMatrix ledmatrix = LedMatrix();

// Initialisierung
void setup()
{
    // Setup Timer
    Timer1.initialize(timer_interval*1000);
    Timer1.attachInterrupt(timer_loop);

    // Setup WirelessConnection
    //wc.

    // Setup LedMatrix
    //...
};

// Loop from Timer1
void timer_loop() 
{
    // alle 500ms
    if(!(counter % 10))
    {
        d.toggleLed();
    } 
    // alle 1s
    else if(!(counter % 20))
    {
        ledmatrix.doSickShit();
    }

    // increment counter
    counter++;
}
 
// Main Loop
void loop(){

};
