#include <SevenSegI2C.h>

int DIG1 = 2;
int DIG2 = 7;
int timer1_counter;
boolean toggle = 0;

SevenSeg seg(0x20, DIG1, DIG2);

void setup()
{
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  timer1_counter = 64886;   // preload timer 65536-16MHz/256/100Hz
//  timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
//  timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = timer1_counter;   // preload timer
  
  if (toggle){
    seg.writeDigit(DIG1);
    toggle = 0;
  }
  else{
    seg.writeDigit(DIG2);
    toggle = 1;
  }  
}

void loop()
{
  
}
