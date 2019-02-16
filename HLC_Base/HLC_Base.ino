/***************************************************************************************************************
FILE: 
PROJECT: HELIOSLIGHTCONTROL
MODULE: 
Description:


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
****************************************************************************************************************/
#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"
#include "src/HLC_Global/PackageBuffer.h"


char buf[80];

#include <SoftwareSerial.h>

SoftwareSerial gtSerial(8, 7); // Arduino RX, Arduino TX


const uint16_t timer_interval = 25; // 25ms
uint32_t counter = 0;


RF24 radio_24(9,10);

WirelessConnection wc = WirelessConnection(radio_24, 0xA00B1E5000LL);
Debug d = Debug(Serial, LED_BUILTIN);
PackageBuffer pckBuff;

// Lokale Werte
enum Matrix_Mode {
  unknown,
  off,
  beleuchtung,
  farbenspiel,
  fft,
  zutrittskontrolle
};


boolean recievedData = false;
Matrix_Mode matrixMode = zutrittskontrolle;

// Initialisierung
void setup()
{
    Serial.begin(9600);
    d.log("Init Started");
    //d.toggleLed();

    //Setup HW Serial 
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
};

void nrf_interrupt()
{
    recievedData = true;
    Package p = wc.getData();
    d.logPackage(p);

    // Adds the recieved package to the Buffer
    pckBuff.overritePackage(p);
}

// Loop from Timer1
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
          Serial.print("It was Doorsensor:");
          Serial.println(p.data_0);
          if(p.data_0 == 0)
          {
            matrixMode = off;
          }
          else
          {
            matrixMode = beleuchtung;
          }
          pckBuff.deleteLastRecieved();
          break;
        }
      }
    }
    // alle 250ms
    if(!(counter % 10))
    {
      if(recievedData)
      {
        recievedData = false;
        handleNewRecieve();
      }
    } 
    // alle 0.5s
    if(!(counter % 20))
    {
        // Weil ich es kann!
        //d.toggleLed();
        d.log("Blink");
    }

    // increment counter
    counter++;
}
 
// Main Loop
void loop()
{
    // Handle Serial Input
    noInterrupts();
    if (readline(gtSerial.read(), buf, 80) > 0) 
    {
        handleSerialRecieve();
    }
    interrupts();
};
