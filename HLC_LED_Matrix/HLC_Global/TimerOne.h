/***************************************************************************************************************
FILE: TimerOne.h
PROJECT: HELIOSLIGHTCONTROL
MODULE: HLC_Global
Description: There are the most functions for setting and working with Atmega328s Timer one.


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
23.02.19: Maximilian Klug: Made last comments
****************************************************************************************************************/
#ifndef TIMERONE_H
#define TIMERONE_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define RESOLUTION 65536    // Timer1 is 16 bit

class TimerOne
{
  public:
  
    // properties
    unsigned int pwmPeriod;
    unsigned char clockSelectBits;

    // methods
    void initialize(long microseconds=1000000);
    void start();
    void stop();
    void restart();
    void pwm(char pin, int duty, long microseconds=-1);
    void disablePwm(char pin);
    void attachInterrupt(void (*isr)(), long microseconds=-1);
    void detachInterrupt();
    void setPeriod(long microseconds);
    void setPwmDuty(char pin, int duty);
    void (*isrCallback)();
};

extern TimerOne Timer1;

#endif