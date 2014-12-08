#include <TimerOne.h>
#include <SevenSegI2C.h>
#include <Wire.h>

int DIG1 = 2;
int DIG2 = 7;
int redPot = A1;
int bluePot = A3;

int temp;
int lastValueRed = 0;
int lastValueBlue = 0;

boolean toggle = false;
SevenSeg *seg;

void setup()
{
  Serial.begin(9600);
  seg = new SevenSeg(0x20, 0x21, DIG1, DIG2);
  
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
  temp = analogRead(redPot);
  if (abs(temp - lastValueRed) > 5) {
    lastValueRed = temp;
    seg->setRedNumber(map(lastValueRed, 0, 1023, 0, 99));
  }
  
  temp = analogRead(bluePot);
  if (abs(temp - lastValueBlue) > 5) {
    lastValueBlue = temp;
    seg->setBlueNumber(map(lastValueBlue, 0, 1023, 0, 99));
  }
  
  seg->write(toggle);
}
