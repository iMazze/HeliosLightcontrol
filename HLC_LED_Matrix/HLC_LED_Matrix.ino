/***************************************************************************************************************
FILE: HLC_LED_Matrix.ino
PROJECT: HELIOSLIGHTCONTROL
MODULE: HLC_LED_Matrix
Description: Its the Main File of the LED Matrix

Compiler dependencies or special instructions:
- WirelessConnection.h
- TimerOne.h
- Debug.h
- PackageBuffer.h
- LedMatrix.h

REVISION HISTORY
Date: By: Description:
18.02.2019: Maximilian Klug: First Commit
23.02.19: Maximilian Klug: Made last comments
****************************************************************************************************************/
#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"
#include "src/HLC_Global/PackageBuffer.h"
#include "src/LedMatrix.h"


// Timer Intervall for Interrupt
const uint16_t timer_interval = 25; // 25ms

// Counter for dividing timer
uint32_t counter = 0;

// Radio Interface
RF24 radio_24(9,10);

WirelessConnection wc = WirelessConnection(radio_24, ID_HLC_MATRIX);

Debug d = Debug(Serial, LED_BUILTIN);

// New instance of LED Matrix
LedMatrix ledmatrix = LedMatrix();

// Instance of the buffer
PackageBuffer pckBuff;

// Internal states
boolean fft_active = false;

/*========================================================================*/
/*                          Initializing                                  */
/*========================================================================*/
void setup()
{
    // Setup HW Serial
    Serial.begin(9600);
    d.log("Init Started");
    
    // Setup RF24
    radio_24.begin();

    // Setup WirelessConnection
    wc.attachInterruptFunction(nrf_interrupt);
    wc.start();
    
    // Setup LedMatrix
    ledmatrix.init();

    // Setup Timer
    Timer1.initialize(timer_interval*1000);
    Timer1.attachInterrupt(timer_loop);
    
    d.log("Init Complete");
};

// Interrupt function for recieving package data
void nrf_interrupt()
{
    Package p = wc.getData();
    d.logPackage(p);

    //Adds the recieved package to the Buffer
    pckBuff.addPackage(p);
}

/*========================================================================*/
/*                            Timer Loop                                  */
/*========================================================================*/
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
                    ledmatrix.fullOff();
                }
                break;
            case MSG_ID::Matrix_Fullon:
                fft_active = false;
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
                fft_active = false;
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
                fft_active = false;
                if(p.data_0 == 1)
                {
                    ledmatrix.setRGB(p.data_1, p.data_2, p.data_3);
                }
                else
                {
                    ledmatrix.fullOff();
                }
                break;   
            case MSG_ID::Matrix_HEX:
                fft_active = false;
                if(p.data_0 == 1)
                {
                    ledmatrix.setHEX(p.data_1);
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
        // alive information
        d.log("iam still alive");
    } 
    // alle 0.5s
    if(!(counter % 20))
    {
        //ledmatrix.doFFT();
    }

    // increment counter
    counter++;
}
 
/*========================================================================*/
/*                            Main Loop                                   */
/*========================================================================*/
void loop(){

    // Does the FFT if active
    if(fft_active)
    {
        ledmatrix.doFFT();
    }
};
