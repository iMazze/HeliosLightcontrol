#include "src/WirelessConnection.h"
#include "src/TimerOne.h"
#include "src/Debug.h"

long timer_interval = 500;

WirelessConnection wc = WirelessConnection();
Debug d = Debug(9600, LED_BUILTIN);

void setup(){
    // Setup Timer
    Timer1.initialize(timer_interval*1000);
    Timer1.attachInterrupt(timer_loop);
};

void timer_loop() {
    // Executed each second
    d.toggleLed();
}
 
void loop(){

};
