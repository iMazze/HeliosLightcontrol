/***************************************************************************************************************
FILE: WirelessConnection.h
PROJECT: HELIOSLIGHTCONTROL
MODULE: HLC_Global
Description:    There are the most functions for sending and recieving data over our 2.4Ghz protocoll.
                There is also a attach Interrupt method. 


Compiler dependencies or special instructions:
- Arduino.h
- SPI.h
- RF24.h

REVISION HISTORY
Date: By: Description:
23.02.19: Maximilian Klug: Made last comments
****************************************************************************************************************/
#ifndef WIRELESSCONNECTION_H
#define WIRELESSCONNECTION_H

#include <Arduino.h>

#include <SPI.h>
#include <RF24.h>


#define CE_PIN 9    //  This pin is used to set the nRF24 to standby (0) or active mode (1)
#define CSN_PIN 10  //  This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
#define IRQ_PIN 0   // 0 for pin 2 or 1 for pin 3 at the Arduino Nano/Uno

// The List with all Package IDs
enum MSG_ID
{
    EMPTY = 0,
    Sensor_Temperature = 11,
    Sensor_Humidity = 12,
    Sensor_Colortemp = 13,
    Sensor_Lux = 14,
    Sensor_RGB = 15,
    Sensor_Doorsensor = 16,
    Matrix_FFT_Show = 20,
    Matrix_Fullon = 21,
    Matrix_RGB = 22,
    Matrix_HSV = 23,
    Matrix_HEX = 24,
    Matrix_AddTempValue = 25,
    Matrix_Tempchart_Show = 26
};

// The define List with all device IDs
#define ID_HLC_BASE     0xA00B1E5000LL
#define ID_HLC_MATRIX   0xB00B1E5000LL
#define ID_HLC_SENSOR   0xC00B1E5000LL
#define ID_HLC_LAMP     0xD00B1E5000LL

// The Package with is sendet trough the room wirelessly
struct package
{
    MSG_ID id = MSG_ID::EMPTY;
    uint64_t source_id = 00;
    uint16_t data_0;
    uint16_t data_1;
    uint16_t data_2;
    uint16_t data_3;
};

typedef struct package Package;


class WirelessConnection
{
  public:
    WirelessConnection(RF24& _radio, uint64_t id);

    void start();
    void attachInterruptFunction(void (* InterruptFunction)());    
    void sendData(Package data, uint64_t reciever_address);
    Package getData();
  private:
    uint64_t m_id;  //Create a pipe addresses for the nodes to communicate over in the constructor
    RF24& radio;
    
};

#endif

