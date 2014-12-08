/*
SevenSeg.cpp - Library for writing to multiple 
seven segment displays using I2C
Kyle David
*/

#include "Arduino.h"
#include <Wire.h>
#include "SevenSegI2C.h"

// number values need to be inverted due to common anode configuration
const unsigned char _NUMBER[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
const unsigned char _CLEAR = 0x00;

SevenSeg::SevenSeg(int redAddress, int blueAddress, int DIG0, int DIG1)
{
	pinMode(DIG0, OUTPUT);
	pinMode(DIG1, OUTPUT);

	_redAddress = redAddress;
	_blueAddress = blueAddress;
	_DIG0 = DIG0;
	_DIG1 = DIG1;

	setMode();	// default mode is true, represents manual mode

	Wire.begin();
}

void SevenSeg::setRedNumber(int value)
{
	if (value > 9 && value < 100)
	{
		int d0, d1;
		split(value, &d0, &d1);
		_red[0] = _NUMBER[d0];
		_red[1] = _NUMBER[d1];
	}
	else if (value >= 0)
	{
		_red[1] = _NUMBER[value];
		_red[0] = _CLEAR;
	}
	
	if (_mode == false)
	{
		_red[1] |= (1 << 7);
	}
}

void SevenSeg::setBlueNumber(int value)
{
	if (value > 9 && value < 100)
	{
		int d0, d1;
		split(value, &d0, &d1);
		_blue[0] = _NUMBER[d0];
		_blue[1] = _NUMBER[d1];
	}
	else if (value >= 0)
	{
		_blue[1] = _NUMBER[value];
		_blue[0] = _CLEAR;
	}

	if (_mode == false)
	{
		_blue[1] |= (1 << 7);
	}
}

void SevenSeg::write(bool toggle)
{
	if (toggle)
	{
		digitalWrite(_DIG1, LOW);

		Wire.beginTransmission(_blueAddress);
		Wire.write(~_blue[0]);
		Wire.endTransmission();
		Wire.beginTransmission(_redAddress);
		Wire.write(~_red[0]);
		Wire.endTransmission();

		digitalWrite(_DIG0, HIGH);
	}
	else
	{
		digitalWrite(_DIG0, LOW);

		Wire.beginTransmission(_blueAddress);
		Wire.write(~_blue[1]);
		Wire.endTransmission();
		Wire.beginTransmission(_redAddress);
		Wire.write(~_red[1]);
		Wire.endTransmission();

		digitalWrite(_DIG1, HIGH);
	}
}

// writes high to both digits, so nothing is displayed
void SevenSeg::clearRed()
{
	_red[0] = _CLEAR;
	_red[1] = _CLEAR;
}

void SevenSeg::clearBlue()
{
	_blue[0] = _CLEAR;
	_blue[1] = _CLEAR;
}

// if mode = true, manual mode is enabled
// if mode = false, auto mode is enabled.
// Auto mode is signified by lighting up the decimal point
void SevenSeg::setMode(bool mode)
{
	_mode = mode;
}

void SevenSeg::split(int input, int * pFirst, int * pSecond)
{
   *pFirst = input / 10;
   *pSecond = input % 10;
}