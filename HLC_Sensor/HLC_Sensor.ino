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


void setup() {
  radio_24.begin();

  // Setup WirelessConnection
  wc.start();
  
  Serial.begin(9600);
}

// mainloop
void loop() 
{
    // ~every 50ms
    if(!(counter % 1))
    {
       restarted=false;
       
       // Meassuring of distance between the doorframe, to ackknowledge if someone enters or left the room
       Sensors.accesControl();
       uint16_t tNumber = Sensors.sendNumberOfPersons();
       if (NumberOfPersonsOld != tNumber || restarted == true)
       {
          Serial.println("Sending Number of persons");
          Package Persons; //Package with number of persons which are actual inside the room
          Persons.id = MSG_ID::Sensor_Doorsensor;
          Persons.data_0 = tNumber;
          Persons.data_1 = 0;
          Persons.data_2 = 0;
          Persons.data_3 = 0;
          NumberOfPersonsOld = tNumber;
          wc.sendData(Persons, ID_HLC_BASE);
          delay(1000);
       }
    }

    // ~every 2s
    if(!(counter % 20))
    {
        Sensors.measuring();
        Serial.println("Temp");
        //Serial.println(Sensors.sendTemperature());
        //Serial.println("Humidity");
        //Serial.println(Sensors.sendHumidity());
        //Serial.println("Lux");
        //Serial.println(Sensors.sendLux());
        //Serial.println("ColorTemp");
        //Serial.println(Sensors.sendColorTemp());
        
        Package temp; // Package with temperaturvalue
        temp.id = MSG_ID::Sensor_Temperature;
        temp.data_0 = Sensors.sendTemperature();
        temp.data_1 = 0;
        temp.data_2 = 0;
        temp.data_3 = 0;

        wc.sendData(temp, ID_HLC_BASE);
        delay(10);

        Package hum; //Package with humidityvalue
        hum.id = MSG_ID::Sensor_Humidity;
        hum.data_0 = Sensors.sendHumidity();
        hum.data_1 = 0;
        hum.data_2 = 0;
        hum.data_3 = 0;

        wc.sendData(hum, ID_HLC_BASE);
        delay(10);

        Package colortemp; //Package with colortemperature
        colortemp.id = MSG_ID::Sensor_Colortemp;
        colortemp.data_0 = Sensors.sendColorTemp();
        colortemp.data_1 = 0;
        colortemp.data_2 = 0;
        colortemp.data_3 = 0;

        wc.sendData(colortemp, ID_HLC_BASE);
        delay(10);
        wc.sendData(colortemp, ID_HLC_LAMP);
        delay(10);

        Package lux; //Package with 
        lux.id = MSG_ID::Sensor_Lux;
        lux.data_0 = Sensors.sendLux();
        lux.data_1 = 0;
        lux.data_2 = 0;
        lux.data_3 = 0;

        wc.sendData(lux, ID_HLC_BASE);
        delay(10);

        Package RGB; //Package with all RGB values of light
        RGB.id = MSG_ID::Sensor_RGB;
        RGB.data_0 = Sensors.sendRed();
        RGB.data_1 = Sensors.sendGreen();
        RGB.data_2 = Sensors.sendBlue();
        RGB.data_3 = 0;

        wc.sendData(RGB, ID_HLC_BASE);
        delay(10);
        // delay (1000);
        //reset counter
        counter = 0;
    }

    // increment counter
    counter++;
    delay(10);
};
