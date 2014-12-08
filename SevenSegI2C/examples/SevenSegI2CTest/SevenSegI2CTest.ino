#include <TimerOne.h>

#include <SevenSegI2C.h>
#include <Wire.h>

int DIG1 = 2;
int DIG2 = 7;
int pot = A1;
int pot2 = A3;

int lastValue = 0;
int lastValueBlue = 0;

int timer1_counter;
boolean toggle = false;
int i = 0;
SevenSeg *redSeg;
SevenSeg *blueSeg;

//SevenSeg seg(0x20, DIG1, DIG2);

void setup()
{
  Serial.begin(9600);
  redSeg = new SevenSeg(0x20, DIG1, DIG2);
  blueSeg = new SevenSeg(0x21, DIG1, DIG2);
  
  pinMode(pot, INPUT);
  pinMode(pot2, INPUT);
  
//  redSeg->setNumber(13);
  
  Timer1.initialize(10000);
  Timer1.attachInterrupt(callback);
  
//  // initialize timer1 
//  noInterrupts();           // disable all interrupts
//  //set timer0 interrupt at 2kHz
//  TCCR0A = 0;// set entire TCCR2A register to 0
//  TCCR0B = 0;// same for TCCR2B
//  TCNT0  = 0;//initialize counter value to 0
//  // set compare match register for 2khz increments
//  OCR0A = 200;//124;// = (16*10^6) / (2000*64) - 1 (must be <256)
//  // turn on CTC mode
//  TCCR0A |= (1 << WGM01);
//  // Set CS01 and CS00 bits for 64 prescaler
//  TCCR0B |= (1 << CS01) | (1 << CS00);   
//  // enable timer compare interrupt
//  TIMSK0 |= (1 << OCIE0A);
//  interrupts();             // enable all interrupts
}

void callback()
{
  toggle = !toggle;
}

//ISR(TIMER0_COMPA_vect)        // interrupt service routine 
//{
//  toggle = !toggle;
//}


void loop()
{
  int temp = analogRead(pot);
  if (abs(temp - lastValue) > 5) {
    lastValue = temp;
    redSeg->setNumber(map(lastValue, 0, 1023, 0, 99));
  }
  
  temp = analogRead(pot2);
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

