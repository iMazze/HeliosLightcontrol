 #include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"
#include "src/HLC_Global/PackageBuffer.h"


const uint16_t timer_interval = 25; // 25ms
uint32_t counter = 0;


RF24 radio_24(9,10);

WirelessConnection wc = WirelessConnection(radio_24, 0xA00B1E5000LL);
Debug d = Debug(Serial, LED_BUILTIN);
PackageBuffer pckBuff;

// Initialisierung
void setup()
{
    Serial.begin(9600);
    d.log("Init Started");
    d.toggleLed();
    
    // Setup RF24
    radio_24.begin();


    // Setup WirelessConnection
    wc.attachInterruptFunction(nrf_interrupt);
    wc.start();

    // Setup Timer
    Timer1.initialize(timer_interval*1000);
    Timer1.attachInterrupt(timer_loop);

    d.log("Init Complete");
    Package p;
    p.id = MSG_ID::Matrix_FFT_Show;
    p.data_0 = 1;
    wc.sendData(p, 0xB00B1E5000LL);
};

void nrf_interrupt()
{
    
    Package p = wc.getData();
    d.logPackage(p);

    // Adds the recieved package to the Buffer
    pckBuff.addPackage(p);
}

// Loop from Timer1
void timer_loop() 
{
    // alle 25ms
    if(!(counter % 1))
    {
        if(pckBuff.hasPackages())
        {
            Package p = pckBuff.returnFirstPackage();
            switch (p.id)
            {
            case MSG_ID::Temperatur:
              //sendColor(map(p.data_0, 20, 30, 0, 359));
              break;   
            case MSG_ID::Farbtemperatur:
              sendColor(map(p.data_0, 20, 30, 0, 359));
              break;  
            }
        }
    }
    // alle 250ms
    if(!(counter % 10))
    {
        // Weil ich es kann!
        d.toggleLed();
        d.log("Blink");
    } 
    // alle 0.5s
    if(!(counter % 20))
    {
        
    }

    // increment counter
    counter++;
}
 
// Main Loop
void loop(){
  
    
};

void sendColor(int val)
{
  Package p;
  p.id = MSG_ID::Matrix_HSV;
  p.data_0 = 1;
  p.data_1 = val;
  p.data_2 = 250;
  p.data_3 = 100;
  wc.sendData(p, 0xB00B1E5000LL);
}
