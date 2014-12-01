/*
  SevenSeg.h - Library for writing to 7 segment displays using I2C
  Kyle David
*/
#ifndef SevenSeg_h
#define SevenSeg_h

#include "Arduino.h"

class SevenSeg
{
	public:
		SevenSeg(int address, int DIG0, int DIG1);
		void configureInterrupt();
		void setNumber(int value);
		void clear();
	private:
		int _address, _DIG0, _DIG1;
		int _num0, _num1;
		// function prototypes
		void split(int input, int& first, int& second);
};
#endif