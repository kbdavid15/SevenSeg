/*
SevenSeg.cpp - Library for writing to multiple 
seven segment displays using 74HC595
Kyle David
*/

#include "Arduino.h"
#include "SevenSeg.h"
const unsigned char _NUMBER[] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6 };

SevenSeg::SevenSeg(int numRegisters, int SER, int RCLK, int SRCLK, int DIG0, int DIG1)
{
	pinMode(SER, OUTPUT);
	pinMode(RCLK, OUTPUT);
	pinMode(SRCLK, OUTPUT);
	// make _shiftRegister static so it can be accessed by red or blue instances of this class
	// try to use default frequency of Timer 0 to set interrupts. On interrupt write the value of the register
	// could have a register for digit 1 and another for digit 2
	
	_numOfRegisterPins = numRegisters * 8;	
	_numRegisters = numRegisters;
	_SER = SER;
	_RCLK = RCLK;
	_SRCLK = SRCLK;
	_DIG0 = DIG0;
	_DIG1 = DIG1;
}

void SevenSeg::setNumber(int value)
{
	if (value >= 0 && value <= 9)
	{
		for (int i = 0; i < 8; i++)
		{
			_shiftRegister[i] = ((~_NUMBER[value] >> (7 - i)) & 1) == 1 ? HIGH : LOW; 
		}
		writeRegisters();
	}
}

void SevenSeg::clear()
{
	clearRegisters();
}

// set all register pins in the array to low
void SevenSeg::clearRegisters()
{
	for (int i = _numOfRegisterPins - 1; i >= 0; i--)
	{
		_shiftRegister[i] = HIGH;
	}
	
	writeRegisters();
}

void SevenSeg::writeRegisters()
{
	digitalWrite(_RCLK, LOW);	
	for (int i = _numOfRegisterPins - 1; i >= 0; i--)
	{
		digitalWrite(_SRCLK, LOW);
		int val = _shiftRegister[i];
		digitalWrite(_SER, val);
		digitalWrite(_SRCLK, HIGH);
	}	
	digitalWrite(_RCLK, HIGH);
}

void SevenSeg::setRegisterPin(int idx, int value)
{
	_shiftRegister[idx] = value;
}