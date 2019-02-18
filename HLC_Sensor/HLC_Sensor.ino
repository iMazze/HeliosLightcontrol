/***************************************************************************************************************
FILE: HLC_Sensor.ino
PROJECT: HELIOSLIGHTCONTROL
MODULE: HLC_Sensor
Description:
  Arduino mainskript for sensor module.
  Opening up an 2.4 GHz connection to send all datapackages to base.
  controlling of timer loop and measuring rate


Compiler dependencies or special instructions:
  AVRISP mkII
REVISION HISTORY
Date: By: Description:
08.02.2019: Jonas Schellhorn: Header, etc.
****************************************************************************************************************/
#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"

#include "src/Sensoring.h"


const uint16_t timer_interval = 50; // 50ms
uint32_t counter = 0;

RF24 radio_24(9,10);
WirelessConnection wc = WirelessConnection(radio_24, 0xC00B1E5000LL);

Sensoring Sensors;

uint16_t NumberOfPersonsOld = 0;
bool restarted = true;
bool t_50ms = false;
bool t_2000ms = false;


void setup() {
  // put your setup code here, to run once:
  radio_24.begin();

  // Setup WirelessConnection
  wc.start();

  // Setup Timer
  Timer1.initialize(timer_interval*1000);
  Timer1.attachInterrupt(timer_loop);
  
  Serial.begin(9600);
  Serial.println ("Ende Setup");
}

// Loop from Timer1
void timer_loop() 
{
 // alle 50ms
    if(!(counter % 1))
    {
        t_50ms = true;
    }
    // alle 2000ms
    if(!(counter % 40))
    {
        t_2000ms = true;
    }
    if(!(counter%100))
    {
        Package Persons; //Package with number of persons which are actual inside the room
        Persons.id = MSG_ID::Sensor_Doorsensor;
        Persons.data_0 = random(0,3);
        Persons.data_1 = 0;
        Persons.data_2 = 0;
        Persons.data_3 = 0;
        //NumberOfPersonsOld = tNumber;
        wc.sendData(Persons, 0xA00B1E5000LL);
    }
    counter++;   
}

// mainloop
void loop() {
  // put your main code here, to run repeatedly:
 //Serial.println("");
 //Serial.println("Main");
 //Serial.println(dht2.readHumidity());

    // alle 50ms
    if(t_50ms == true)
    {
       restarted=false;
       
       //Durchlaufen der Abstandsmessung zwischen den Türrahmen, um ein- bzw herausgehende Personen zu erkennen
       //Sensors.accesControl();
       //uint16_t tNumber = Sensors.sendNumberOfPersons();
       //Serial.println(tNumber);
       //if (NumberOfPersonsOld != tNumber || restarted == true)
       //{
       //   Serial.println ("Number:");
       //   Serial.println (tNumber);
        //      Package Persons; //Package with number of persons which are actual inside the room
        //      Persons.id = MSG_ID::Sensor_Doorsensor;
        //      Persons.data_0 = tNumber;
        //      Persons.data_1 = 0;
        //      Persons.data_2 = 0;
        //      Persons.data_3 = 0;
        //  NumberOfPersonsOld = tNumber;
        //      wc.sendData(Persons, 0xA00B1E5000LL);
        //t_50ms=false;
        //  delay(1000);
       //
    }

    // alle 2s
    if(t_2000ms == true)
    {
        Serial.println("");
        Serial.println("Sensordaten 1000ms");
        //Serial.println(dht2.readTemperature());
        //Serial.println(dht2.readHumidity());
        Sensors.measuring();
        Serial.println("Temp");
        Serial.println(Sensors.sendTemperature());
        //Serial.println(Sensors.sendHumidity());
        //Serial.println("Lux");
        //Serial.println(Sensors.sendLux());
        Serial.println("ColorTemp");
        Serial.println(Sensors.sendColorTemp());
        Package temp; // Package with temperaturvalue
        temp.id = MSG_ID::Sensor_Temperature;
        temp.data_0 = Sensors.sendTemperature();
        temp.data_1 = 0;
        temp.data_2 = 0;
        temp.data_3 = 0;

        wc.sendData(temp, 0xA00B1E5000LL);
        delay(10);

        Package hum; //Package with humidityvalue
        hum.id = MSG_ID::Sensor_Humidity;
        hum.data_0 = Sensors.sendHumidity();
        hum.data_1 = 0;
        hum.data_2 = 0;
        hum.data_3 = 0;

        wc.sendData(hum, 0xA00B1E5000LL);
        delay(10);

        Package colortemp; //Package with colortemperature
        colortemp.id = MSG_ID::Sensor_Colortemp;
        colortemp.data_0 = Sensors.sendColorTemp();
        colortemp.data_1 = 0;
        colortemp.data_2 = 0;
        colortemp.data_3 = 0;

        wc.sendData(colortemp, 0xA00B1E5000LL);
        delay(10);

        Package lux; //Package with 
        lux.id = MSG_ID::Sensor_Lux;
        lux.data_0 = Sensors.sendLux();
        lux.data_1 = 0;
        lux.data_2 = 0;
        lux.data_3 = 0;

        wc.sendData(lux, 0xA00B1E5000LL);
        delay(10);

        Package RGB; //Package with all RGB values of light
        RGB.id = MSG_ID::Sensor_RGB;
        RGB.data_0 = Sensors.sendRed();
        RGB.data_1 = Sensors.sendGreen();
        RGB.data_2 = Sensors.sendBlue();
        RGB.data_3 = 0;

        wc.sendData(RGB, 0xA00B1E5000LL);
        delay(10);
        // delay (1000);
        t_2000ms = false;
        delay (100);
    }

    // increment counter
 //delay(1000);
};
