#ifndef Morse_h
#define Morse_h

#include <Arduino.h>

enum data_type
{
    DATA,
    TEMPERATURE,
    HUMIDITY,
    LUX,
    COLOR
};

struct package
{
    uint16_t sender = 00;
    uint16_t reciever = 01;
    data_type type = data;
    uint16_t val_a;
    uint16_t val_b;
    uint16_t val_c;
    uint16_t val_d;
    uint16_t val_e;
};




typedef struct package Package;

class WirelessConnection
{
    
  public:
    WirelessConnection();
    void sendData(Package data);
    Package getData();
    Package getDataWithFilter(uint16_t filter_id);
  private:
    int _pin;
    const uint16_t m_id = 00;   // Address of this node in Octal format ( 04,031, etc)
};

#endif

