#ifndef WIRELESSCONNECTION_H
#define WIRELESSCONNECTION_H

#include <Arduino.h>

#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>

#define CE_PIN 9 //This pin is used to set the nRF24 to standby (0) or active mode (1)
#define CSN_PIN 10 //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
#define IRQ_PIN 0

enum MSG_ID
{
    EMPTY = 0,
    Sensor_Temperature = 11,
    Sensor_Humidity = 12,
    Sensor_Colortemp = 13,
    Sensor_Lux = 14,
    Sensor_RGB = 15,
    Sensor_Doorsensor =16,
    Matrix_FFT_Show = 20,
    Matrix_Fullon = 21,
    Matrix_RGB = 22,
    Matrix_HSV = 23
};

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
    uint64_t m_id;  //Create a pipe addresses for the nodes to communicate over
    void static recieve_interrupt();
    RF24& radio; /**< Underlying radio driver, provides link/physical layers */
    
};

#endif

