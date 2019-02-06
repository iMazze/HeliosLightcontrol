
#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"

#include "src/Sensoring.h"


const uint16_t timer_interval = 25; // 25ms
uint32_t counter = 0;

RF24 radio_24(9,10);
WirelessConnection wc = WirelessConnection(radio_24, 0xC00B1E5000LL);

Sensoring Sensors;
uint16_t NumberOfPersonsOld = 0;
bool restarted = true;

void setup() {
  // put your setup code here, to run once:
  radio_24.begin();
    // Setup Timer
    Timer1.initialize(timer_interval*1000);
    Timer1.attachInterrupt(timer_loop);

    // Setup WirelessConnection
    wc.start();

    Serial.begin(9600);
}

// Loop from Timer1
void timer_loop() 
{
    // alle 25ms
    if(!(counter % 1))
    {
        //Code, der alle 25 ms ausgeführt werden soll
    }
    // alle 50ms
    if(!(counter % 2))
    {
        //Durchlaufen der Abstandsmessung zwischen den Türrahmen, um ein- bzw herausgehende Personen zu erkennen
        Sensors.counter();
        if (NumberOfPersonsOld != Sensors.sendNumberOfPersons() || restarted == true)
        {
            Package Persons; //Package with number of persons which are actual inside the room
            Persons= MSG_ID::Sensor_Doorsensor;
            Persons.data_0 = Sensors.sendNumberOfPersons();
            Persons.data_1 = 0;
            Persons.data_2 = 0;
            Persons.data_3 = 0;

            wc.sendData(RGB, 0xA00B1E5000LL);
            delay(10);
        }
        restarted=false;
    }
    // alle 250ms
    if(!(counter % 10))
    {
    } 
    // alle 0.5s
    if(!(counter % 20))
    {
    }
    // alle 1s
    if(!(counter % 40))
    {
        Sensors.measuring();
        Package temp; // Package with temperaturvalue
        temp.id = MSG_ID::Sensor_Temperature;
        temp.data_0 = Sensors.sendTemperature();
        temp.data_1 = 0;
        temp.data_2 = 0;
        temp.data_3 = 0;

        wc.sendData(temp, 0xA00B1E5000LL);
        delay(10);

        Package hum; //Package with humdityvalue
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
        RGB= MSG_ID::Sensor_RGB;
        RGB.data_0 = Sensors.sendRed();
        RGB.data_1 = Sensors.sendGreen();
        RGB.data_2 = Sensors.sendBlue();
        RGB.data_3 = 0;

        wc.sendData(RGB, 0xA00B1E5000LL);
        delay(10);
    }

    // increment counter
    counter++;
}

// mainloop
void loop() {
  // put your main code here, to run repeatedly:
 
}
