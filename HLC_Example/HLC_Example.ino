#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"

final uint16_t timer_interval = 50; // 50ms
uint32_t counter = 0;


WirelessConnection wc = WirelessConnection();
Debug d = Debug(9600, LED_BUILTIN);


// Initialisierung
void setup()
{
    // Setup Timer
    Timer1.initialize(timer_interval*1000);
    Timer1.attachInterrupt(timer_loop);

    // Setup WirelessConnection
    //wc.
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
        
    }

    // increment counter
    counter++;
}
 
// Main Loop
void loop(){

};
