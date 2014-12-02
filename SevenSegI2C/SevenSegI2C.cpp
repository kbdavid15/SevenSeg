/*
SevenSeg.cpp - Library for writing to multiple 
seven segment displays using I2C
Kyle David
*/

#include "Arduino.h"
#include <Wire.h>
#include "SevenSegI2C.h"

// number values need to be inverted due to common anode configuration
const unsigned char _NUMBER[] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6 };
const unsigned char _CLEAR = 0x00;

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

// should only be called after setNumber() is called
unsigned char SevenSeg::getDigit(int digit)
{
	switch (digit)
	{
	case _DIG1:
		return _num1;
	case _DIG0;
		return _num0;
	}
	return _CLEAR;	// must have some return value
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
}

void SevenSeg::writeDigit(int digit)
{
	//if (digit == _DIG0)
	//{
	//	digitalWrite(_DIG1, LOW);
	//	Wire.beginTransmission(address);
	//	Wire.write(~_num0);
	//	Wire.endTransmission();
	//	digitalWrite(_DIG0, HIGH);
	//}
	//else if (digit == _DIG1)
	//{
	//	digitalWrite(_DIG0, LOW);
	//	Wire.beginTransmission(address);
	//	Wire.write(~_num1);
	//	Wire.endTransmission();
	//	digitalWrite(_DIG1, HIGH);
	//}
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