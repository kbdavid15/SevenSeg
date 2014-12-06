#include <SevenSeg.h>

int SER_Pin = 8;    // pin 14 on the 75HC595
int RCLK_Pin = 9;   // pin 12 on the 75HC595
int SRCLK_Pin = 10; // pin 11 on the 75HC595
int DIG1 = 2;
int DIG2 = 7;

int numRegisters = 1;
SevenSeg seg(1, SER_Pin, RCLK_Pin, SRCLK_Pin, DIG1, DIG2);

boolean toggle0 = 0;
boolean toggle1 = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(DIG1, OUTPUT);
  pinMode(DIG2, OUTPUT);  
  Serial.println("Class created successfully"); 
  
//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  
}

ISR(TIMER0_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  Serial.println("HI");
  if (toggle1){
    digitalWrite(DIG2, LOW);
    seg.setNumber(1);
    digitalWrite(DIG1, HIGH);
    toggle1 = 0;
  }
  else{
    digitalWrite(DIG1, LOW);
    seg.setNumber(5);
    digitalWrite(DIG2, HIGH);
    toggle1 = 1;
  }
}

void loop()
{
//  digitalWrite(DIG1, HIGH);
//  for(int i = 0; i < 10; i++){
//    seg.setNumber(i);
//    delay(500);
//  }
  

}
