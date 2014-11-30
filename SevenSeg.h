/*
  SevenSeg.h - Library for writing to 7 segment displays using 74HC595
  Kyle David
*/
#ifndef SevenSeg_h
#define SevenSeg_h

#include "Arduino.h"

class SevenSeg
{
	public:
		SevenSeg(int numRegisters, int SER, int RCLK, int SRCLK, int DIG0, int DIG1);
		void setNumber(int value);
		void clear();
	private:
		int _numRegisters, _SER, _RCLK, _SRCLK, _DIG0, _DIG1;
		bool _shiftRegister[8];
		int _numOfRegisterPins;		
		//const unsigned char _NUMBER[];
		// function prototypes
		void clearRegisters();
		void writeRegisters();
		void setRegisterPin(int idx, int value);
};
#endif