/*
SevenSeg.cpp - Library for writing to multiple 
seven segment displays using I2C
Kyle David
*/

#include "Arduino.h"
#include <Wire.h>
#include "SevenSeg.h"

// number values need to be inverted due to common anode configuration
const unsigned char _NUMBER[] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6 };
const unsigned char _CLEAR = 0xFF;

SevenSeg::SevenSeg(int address, int DIG0, int DIG1)
{
	pinMode(DIG0, OUTPUT);
	pinMode(DIG1, OUTPUT);
	// try to use default frequency of Timer 0 to set interrupts. On interrupt write the value of the register
	// could have a register for digit 1 and another for digit 2
	
	_address = address;
	_DIG0 = DIG0;
	_DIG1 = DIG1;
}

void SevenSeg::configureInterrupt()
{

}

void SevenSeg::setNumber(int value)
{
	if (value > 9 && value < 100)
	{
		int d0, d1;
		split(value, &d1, &d0);
		_num0 = _NUMBER[d0];
		_num1 = _NUMBER[d1];
	}
	else if (value >= 0)
	{
		_num0 = _NUMBER[value];
		_num1 = _CLEAR;
	}
	
	
	if (value >= 0 && value <= 9)
	{
		for (int i = 0; i < 8; i++)
		{
			//_shiftRegister[i] = ((~_NUMBER[value] >> (7 - i)) & 1) == 1 ? HIGH : LOW; 
		}
	}
}

// writes high to both digits, so nothing is displayed
void SevenSeg::clear()
{
	_num0 = _CLEAR;
	_num1 = _CLEAR;
}

void SevenSeg::split(int input, int * pFirst, int * pSecond)
{
   *pFirst = input / 10;
   *pSecond = input % 10;
}