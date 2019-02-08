#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"


const uint16_t timer_interval = 25; // 25ms
uint32_t counter = 0;


RF24 radio_24(9,10);

WirelessConnection wc = WirelessConnection(radio_24, 0xC00B1E5000LL);
Debug d = Debug(Serial, LED_BUILTIN);


//sensors
#define SwitchPin 8 // Arcade switch is connected to Pin 8 on NANO


// Initialisierung
void setup()
{
    Serial.begin(9600);
    d.log("Init Started");
    d.toggleLed();
    
    // Setup RF24
    radio_24.begin();


    // Setup WirelessConnection
    wc.start();

    // Setup Timer
    Timer1.initialize(timer_interval*1000);
    Timer1.attachInterrupt(timer_loop);

    pinMode(SwitchPin, INPUT_PULLUP); // Define the arcade switch NANO pin as an Input using Internal Pullups
    digitalWrite(SwitchPin,HIGH); // Set Pin to HIGH at beginning

    randomSeed(analogRead(1));

    Package p;
        p.id = MSG_ID::Matrix_RGB;
        p.data_0 = 1;
        p.data_1 = 100;
        p.data_2 = 100;
        p.data_3 = 0;

        wc.sendData(p, 0xB00B1E5000LL);
        
    d.log("Init Complete");
};

// Loop from Timer1
void timer_loop() 
{
    // alle 25ms
    if(!(counter % 1))
    {
        //ENTWEDER HIER
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

 bool on=true;
// Main Loop
void loop(){
  delay(50);
  //ODER HIER
  if (digitalRead(SwitchPin) == LOW){ // If Switch is Activated
        Package p;
        p.id = MSG_ID::Temperatur;
        p.data_0 = random(0,30);
        p.data_1 = 0;
        p.data_2 = 0;
        p.data_3 = 0;

        wc.sendData(p, 0xA00B1E5000LL);
        delay(500);
   }
};
