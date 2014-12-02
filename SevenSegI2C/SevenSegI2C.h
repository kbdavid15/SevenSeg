/*
  SevenSegI2C.h - Library for writing to 7 segment displays using I2C
  Kyle David
*/
#ifndef SevenSegI2C_h
#define SevenSegI2C_h

#include "Arduino.h"
#include <Wire.h>

class SevenSeg
{
	public:
		SevenSeg(int address, int DIG0, int DIG1);
		void configureInterrupt();
		void setNumber(int value);
		unsigned char getDigit(int digit);
		void writeDigit(int digit);
		void clear();
	private:
		int _address, _DIG0, _DIG1;
		unsigned char _num0, _num1;
		// function prototypes
		void split(int input, int * pFirst, int * pSecond);
};
#endif