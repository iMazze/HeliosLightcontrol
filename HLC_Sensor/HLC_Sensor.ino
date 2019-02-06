
#include "src/HLC_Global/WirelessConnection.h"
#include "src/HLC_Global/TimerOne.h"
#include "src/HLC_Global/Debug.h"

#include "src/Sensoring.h"


const uint16_t timer_interval = 50; // 50ms
uint32_t counter = 0;
RF24 radio_24(9,10);
WirelessConnection wc = WirelessConnection(radio_24, 0xC00B1E5000LL);
Sensoring Sensors;

void setup() {
  // put your setup code here, to run once:
  radio_24.begin();
    // Setup Timer
    Timer1.initialize(timer_interval*1000);
   // Timer1.attachInterrupt(timer_loop);

    // Setup WirelessConnection
    wc.start();
    //wc.attachInterruptFunction(nrf_interrupt);

    Serial.begin(9600);
    

    //TESTING
    Sensors.setMeasuringRate(60);
   //
}

// mainloop
void loop() {
  // put your main code here, to run repeatedly:
  Sensors.measuring();
        Package temp;
        temp.id = MSG_ID::Temperatur;
        temp.data_0 = Sensors.sendTemperature();
        temp.data_1 = 0;
        temp.data_2 = 0;
        temp.data_3 = 0;

        wc.sendData(temp, 0xA00B1E5000LL);
        delay(10);

        Package hum;
        hum.id = MSG_ID::Luftfeuchtigkeit;
        hum.data_0 = Sensors.sendHumidity();
        hum.data_1 = 0;
        hum.data_2 = 0;
        hum.data_3 = 0;

        wc.sendData(hum, 0xA00B1E5000LL);
        delay(10);

        Package colortemp;
        temp.id = MSG_ID::Farbtemperatur;
        temp.data_0 = Sensors.sendTemperature();
        //Sensors.sendTemperature()
        temp.data_1 = 0;
        temp.data_2 = 0;
        temp.data_3 = 0;

        wc.sendData(temp, 0xA00B1E5000LL);
        delay(10);

        Package temp;
        temp.id = MSG_ID::Helligkeit;
        temp.data_0 = Sensors.sendTemperature();
        //Sensors.sendTemperature()
        temp.data_1 = 0;
        temp.data_2 = 0;
        temp.data_3 = 0;

        wc.sendData(temp, 0xA00B1E5000LL);
        delay(10);

                Package temp;
        temp.id = MSG_ID::Temperatur;
        temp.data_0 = Sensors.sendTemperature();
        //Sensors.sendTemperature()
        temp.data_1 = 0;
        temp.data_2 = 0;
        temp.data_3 = 0;

        wc.sendData(temp, 0xA00B1E5000LL);
        delay(10);

}
