#include <Wire.h>

int DIG1 = 2;
int DIG2 = 7;
int timer1_counter;
boolean toggle = 0;
int address = 0x20;
char _NUMBER[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F };

void setup()
{
  pinMode(DIG1, OUTPUT);
  pinMode(DIG2, OUTPUT);
  Wire.begin();
  allOff();
}

void loop()
{
  digitalWrite(DIG2, HIGH);
  for (int i = 0; i < 10; i++)
  {
    Wire.beginTransmission(address);
    Wire.write(~_NUMBER[i]);
    Wire.endTransmission();
    delay(250);
  }
  
}

void allOff()
{
 Wire.beginTransmission(address);
 Wire.write(255); 
 Wire.endTransmission();
}
