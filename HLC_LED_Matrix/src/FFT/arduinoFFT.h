#ifndef arduinoFFT_h /* Prevent loading library twice */
#define arduinoFFT_h
#ifdef ARDUINO
	#if ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h" /* This is where the standard Arduino code lies */
	#endif
#else
	#include <stdlib.h>
	#include <stdio.h>
	#ifdef __AVR__
		#include <avr/io.h>
	#endif
	#include <math.h>
	#include "defs.h"
	#include "types.h"
#endif

#define FFT_LIB_REV 0x14
/* Custom constants */
#define FFT_FORWARD 0x01
#define FFT_REVERSE 0x00

/* Windowing type */
#define FFT_WIN_TYP_RECTANGLE 0x00 /* rectangle (Box car) */
#define FFT_WIN_TYP_HAMMING 0x01 /* hamming */
#define FFT_WIN_TYP_HANN 0x02 /* hann */
#define FFT_WIN_TYP_TRIANGLE 0x03 /* triangle (Bartlett) */
#define FFT_WIN_TYP_NUTTALL 0x04 /* nuttall */
#define FFT_WIN_TYP_BLACKMAN 0x05 /* blackman */
#define FFT_WIN_TYP_BLACKMAN_NUTTALL 0x06 /* blackman nuttall */
#define FFT_WIN_TYP_BLACKMAN_HARRIS 0x07 /* blackman harris*/
#define FFT_WIN_TYP_FLT_TOP 0x08 /* flat top */
#define FFT_WIN_TYP_WELCH 0x09 /* welch */
/*Mathematial constants*/
#define twoPi 6.28318531
#define fourPi 12.56637061
#define sixPi 18.84955593

class arduinoFFT {
public:
	/* Constructor */
	arduinoFFT(void);
	arduinoFFT(double *vReal, double *vImag, uint16_t samples, double samplingFrequency);
	/* Destructor */
	~arduinoFFT(void);
	/* Functions */
	uint8_t Revision(void);
	uint8_t Exponent(uint16_t value);
	void ComplexToMagnitude(double *vReal, double *vImag, uint16_t samples);
	void Compute(double *vReal, double *vImag, uint16_t samples, uint8_t dir);
	void Compute(double *vReal, double *vImag, uint16_t samples, uint8_t power, uint8_t dir);
	void DCRemoval(double *vData, uint16_t samples);
	double MajorPeak(double *vD, uint16_t samples, double samplingFrequency);
	void Windowing(double *vData, uint16_t samples, uint8_t windowType, uint8_t dir);
	void ComplexToMagnitude();
	void Compute(uint8_t dir);
	void DCRemoval();
	double MajorPeak();
	void Windowing(uint8_t windowType, uint8_t dir);

	void MajorPeak(double *f, double *v);
	void MajorPeak(double *vD, uint16_t samples, double samplingFrequency, double *f, double *v);


private:
	/* Variables */
	uint16_t _samples;
	double _samplingFrequency;
	double *_vReal;
	double *_vImag;
	uint8_t _power;
	/* Functions */
	void Swap(double *x, double *y);
};

#endif
