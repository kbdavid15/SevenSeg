#include <SevenSegI2C.h>
#include <Wire.h>

int DIG1 = 2;
int DIG2 = 7;
int timer1_counter;
boolean toggle = 0;

SevenSeg *redSeg;

//SevenSeg seg(0x20, DIG1, DIG2);

void setup()
{
  Serial.begin(9600);
  redSeg = new SevenSeg(0x20, DIG1, DIG2);  
//  // initialize timer1 
//  noInterrupts();           // disable all interrupts
//  //set timer0 interrupt at 2kHz
//  TCCR0A = 0;// set entire TCCR2A register to 0
//  TCCR0B = 0;// same for TCCR2B
//  TCNT0  = 0;//initialize counter value to 0
//  // set compare match register for 2khz increments
//  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
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
  Serial.println("HI");
}

ISR(TIMER0_COMPA_vect)        // interrupt service routine 
{
  Serial.println("int");

  if (toggle){
    redSeg->writeDigit(DIG1);
    toggle = 0;
  }
  else{
    redSeg->writeDigit(DIG2);
    toggle = 1;
  }
}


void loop()
{
//  for (int i = 0; i < 100; i++) {
//    redSeg->setNumber(i);
//    //delay(500);
//  }
  
  redSeg->setNumber(13);
  redSeg->writeDigit(DIG2);  
  
}

