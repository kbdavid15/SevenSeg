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
		// constructor
		SevenSeg(int redAddress, int blueAddress, int DIG0, int DIG1);		

		// function prototypes
		void setRedNumber(int value);
		void setBlueNumber(int value);
		void write(bool toggle);
		void clearRed();
		void clearBlue();
		void setMode(bool mode = true);

	private:
		int _redAddress, _blueAddress, _DIG0, _DIG1;
		unsigned char _red[2], _blue[2];
		bool _mode;
		// function prototype
		void split(int input, int * pFirst, int * pSecond);
};
#endif