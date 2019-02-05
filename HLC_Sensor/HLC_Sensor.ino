#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"
#include "src/HLC_Global/PackageBuffer.h"

#include "src/Sensoring.h"


const uint16_t timer_interval = 50; // 50ms
uint32_t counter = 0;

WirelessConnection wc = WirelessConnection(0xB00B1E5000LL);
Sensoring Sensors;

void setup() {
  // put your setup code here, to run once:
  
    // Setup Timer
    Timer1.initialize(timer_interval*1000);
    Timer1.attachInterrupt(timer_loop);

    // Setup WirelessConnection
    wc.attachInterruptFunction(nrf_interrupt);

    Serial.begin(9600);
    

    //TESTING
    Sensors.setMeasuringRate(1);
   //
}


// Loop from Timer1

void timer_loop() 

{

    // alle 50ms

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

                        ledmatrix.setRGB(p.data_1, p.data_2, p.data_3);

                    }

                    else

                    {

                        ledmatrix.fullOff();

                    }

                    break;

                case MSG_ID::Matrix_RGB:

                    if(p.data_0 == 1)

                    {

                        ledmatrix.setHSV(p.data_1, p.data_2, p.data_3);

                    }

                    else

                    {

                        ledmatrix.fullOff();

                    }

                    break;    

            }

        }

    }

    // alle 500ms

    else if(!(counter % 10))

    {

        // Weil ich es kann!

        d.toggleLed();

    } 

    // alle 1s

    else if(!(counter % 20))

    {

        

    }



    // increment counter

    counter++;

}

// mainloop
void loop() {
  // put your main code here, to run repeatedly:
  Sensors.measuring();

}