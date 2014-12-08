#include <TimerOne.h>
#include <SevenSegI2C.h>
#include <Wire.h>

int DIG1 = 2;
int DIG2 = 7;
int redPot = A1;
int bluePot = A3;

int lastValueRed = 0;
int lastValueBlue = 0;

boolean toggle = false;

SevenSeg *redSeg;
SevenSeg *blueSeg;

void setup()
{
  Serial.begin(9600);
  redSeg = new SevenSeg(0x20, DIG1, DIG2);
  blueSeg = new SevenSeg(0x21, DIG1, DIG2);
  
  pinMode(redPot, INPUT);
  pinMode(bluePot, INPUT);
  
  Timer1.initialize(10000);
  Timer1.attachInterrupt(callback);
}

void callback()
{
  toggle = !toggle;
}

void loop()
{
  int temp = analogRead(redPot);
  if (abs(temp - lastValueRed) > 5) {
    lastValueRed = temp;
    redSeg->setNumber(map(lastValueRed, 0, 1023, 0, 99));
  }
  
  temp = analogRead(bluePot);
  if (abs(temp - lastValueBlue) > 5) {
    Serial.println(temp);
    lastValueBlue = temp;
    blueSeg->setNumber(map(lastValueBlue, 0, 1023, 0, 99));
  }
  
  if (toggle)
  {
    redSeg->writeDigit(DIG1);
    blueSeg->writeDigit(DIG1);
  }
  else
  {
    redSeg->writeDigit(DIG2);
    blueSeg->writeDigit(DIG2);
  }
}
