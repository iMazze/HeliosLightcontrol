/***************************************************************************************************************
FILE: HLC_Base.ino
PROJECT: HELIOSLIGHTCONTROL
MODULE: Base Module
Description: Main File of Base Module

Compiler dependencies or special instructions:
- WirelessConnection.h
- TimerOne.h
- Debug.h
- PackageBuffer.h
- SoftwareSerial.h

REVISION HISTORY
Date: By: Description:
18.02.19: Maximilian Klug: First Commit
23.02.19: Maximilian Klug: Made last comments
****************************************************************************************************************/
#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"
#include "src/HLC_Global/PackageBuffer.h"
#include <SoftwareSerial.h>

// Buffer for recieving serial Data from the HLC_Web
char buf[80];

// Software Serial interface for HLC_Web
SoftwareSerial gtSerial(8, 7); // Arduino RX, Arduino TX

// Timer Intervall for Interrupt
const uint16_t timer_interval = 25; // 25ms

// Counter for dividing timer
uint32_t counter = 0;

// Radio Interface
RF24 radio_24(9,10);

WirelessConnection wc = WirelessConnection(radio_24, ID_HLC_BASE);

Debug d = Debug(Serial, LED_BUILTIN);

// Instance of the buffer
PackageBuffer pckBuff;

// Lokale Werte
enum Matrix_Mode {
  off,
  fft,
  beleuchtungNachTemperatur,
  temperaturverlauf
};

boolean recievedData = false;
Matrix_Mode matrixMode = off;

boolean isRoomEmpty = true;
boolean lampOn = false;

/*========================================================================*/
/*                          Initializing                                  */
/*========================================================================*/
void setup()
{
    // Setup HW Serial
    Serial.begin(9600);
    d.log("Init Started");

    //Setup SW Serial 
    gtSerial.begin(9600);  // software serial port
    
    // Setup RF24
    radio_24.begin();

    // Setup WirelessConnection
    wc.attachInterruptFunction(nrf_interrupt);
    wc.start();

    // Setup Timer
    Timer1.initialize(timer_interval*1000);
    Timer1.attachInterrupt(timer_loop);

    d.log("Init Complete");

    // Make LED initially Off
    matrixSetOff();
    // Make Lamp initially Off
    lampSetOff();
};

// Interrupt function for recieving package data
void nrf_interrupt()
{
    recievedData = true;
    Package p = wc.getData();
    //d.logPackage(p);

    // Adds the recieved package to the Buffer
    pckBuff.overritePackage(p);
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
        Package p = pckBuff.readLastPackage();
        switch (p.id)
        {  
        case MSG_ID::Sensor_Doorsensor:
            Serial.print("It was Doorsensor: ");
            Serial.println(p.data_0);
            if(p.data_0 == 0)
            {
                isRoomEmpty = true;
            }
            else
            {
                isRoomEmpty = false;
            }
            pckBuff.deleteLastRecieved();
            recievedData = false;
        break;
        }
      }
    }
    // alle 0.5s
    if(!(counter % 20))
    {
      // alive information
      d.log("iam still alive");
    }
    // alle 1s
    if(!(counter % 40))
    {
        // Handle the Recieved data from the Interrupt
        if(recievedData)
        {
            recievedData = false;
            handleNewRecieve();
        }
        handleStaticModes();

    } 
    // alle 4s
    if(!(counter % 160))
    {
        if(matrixMode == temperaturverlauf)
        {
            // If there is no package --> break;
            if(pckBuff.hasPackageWithId(MSG_ID::Sensor_Temperature))
            {
                uint16_t actTemperature = pckBuff.getPackageWithId(MSG_ID::Sensor_Temperature).data_0;
                matrixSendTemperature(actTemperature);
            }
            
        }
    }
    if(!(counter % 320))
    {
        
    }

    // increment counter
    counter++;
}
 
/*========================================================================*/
/*                            Main Loop                                   */
/*========================================================================*/
void loop()
{
    // Handle Serial Input recieved from HLC_Web
    // Deactivate Interrupts
    noInterrupts();
    if (readline(gtSerial.read(), buf, 80) > 0) 
    {
        handleSerialRecieve();
    }

    // Activate Interrupts
    interrupts();
};
