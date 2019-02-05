#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"
#include "src/HLC_Global/PackageBuffer.h"

#include "src/LedMatrix.h"



const uint16_t timer_interval = 25; // 25ms
uint32_t counter = 0;


RF24 radio_24(9,10);

WirelessConnection wc = WirelessConnection(radio_24, 0xB00B1E5000LL);
Debug d = Debug(Serial, LED_BUILTIN);
LedMatrix ledmatrix = LedMatrix();
PackageBuffer pckBuff;

// States
boolean fft_active = false;

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
    
    // Setup LedMatrix
    //ledmatrix.init();

    // Setup Timer
    Timer1.initialize(timer_interval*1000);
    Timer1.attachInterrupt(timer_loop);

    d.log("Init Complete");
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
            case MSG_ID::Matrix_FFT_Show:
                if(p.data_0 == 1)
                {
                    // switch on
                    fft_active = true;
                }
                else
                {
                    // switch off
                    fft_active = false;
                }
                break;
            case MSG_ID::Matrix_Fullon:
                if(p.data_0 == 1)
                {
                    ledmatrix.fullOn();
                }
                else
                {
                    ledmatrix.fullOff();
                }
                break;
            case MSG_ID::Matrix_HSV:
                if(p.data_0 == 1)
                {
                    ledmatrix.setHSV(p.data_1, p.data_2, p.data_3);
                }
                else
                {
                    ledmatrix.fullOff();
                }
                break;
            case MSG_ID::Matrix_RGB:
                if(p.data_0 == 1)
                {
                    ledmatrix.setRGB(p.data_1, p.data_2, p.data_3);
                }
                else
                {
                    ledmatrix.fullOff();
                }
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

    if(fft_active)
    {
        ledmatrix.doFFT();
    }
};
