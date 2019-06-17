#include <Servo.h>
#define MINSPEED 25500 //23400
#define MAXSPEED 40500 //18000


uint16_t icr = 0xffff;


struct data{
  uint16_t speed;  
  char checksum;
} typedef Data; //set data structure. Contains speed and angle duty cycle value + checksum

char head[4] = {36,70}; //Set header value 2 byte header 

int inputHeader = 0;

int* comparisonHeader = (int*)head; //store header as long value since uno is 16 bit 

char* bytevalue;

Data* value = (Data*)calloc(sizeof(Data),1); //initialise storage struct

char checksum = 36+70; //initalise checksum 

char currvalue; 

void setup() {
  Serial.begin(9600); 
  setupPWM16();
  analogWrite16(9, MINSPEED);
}
 uint16_t itr = 0;


void loop() {
    value->speed = 0;
    while (*comparisonHeader != inputHeader) {
               if(Serial.available()){ //header capturing 
                  currvalue = Serial.read();
                  inputHeader = inputHeader << 8;
                  inputHeader = inputHeader|currvalue;
               }
    }
    while(Serial.available() < 3); //wait for three bytes for speed, angle and checksum
    
    bytevalue = (char*)value;
    bytevalue[1] = Serial.read();
    bytevalue[0] = Serial.read();
    value->checksum = Serial.read();
    
    checksum += (bytevalue)[0];//calc local checksum 
    checksum += (bytevalue)[1];
    
    if(value->checksum == checksum){ //write if checksum is correct
       analogWrite16(9, MINSPEED+itr++);//value->speed+MINSPEED);
    }
    analogWrite16(9, MINSPEED+(itr++));
    checksum = 36+70; //reset checksum value
    inputHeader = 0; //reset header storage
}

//16bit functions
void setupPWM16() {
  DDRB  |= _BV(PB1) | _BV(PB2);       /* set pins as outputs */
  TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
        | _BV(WGM11);                 /* mode 14: fast PWM, TOP=ICR1 */
  TCCR1B = _BV(WGM13) | _BV(WGM12)
        | _BV(CS10);                  /* prescaler 1 */
  ICR1 = icr;                         /* TOP counter value (freeing OCR1A*/
}

/* 16-bit version of analogWrite(). Works only on pins 9 and 10. */
void analogWrite16(uint8_t pin, uint16_t val)
{
  switch (pin) {
    case  9: OCR1A = val; break;
    case 10: OCR1B = val; break;
  }
} 



