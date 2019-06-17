#define MINSPEED 25500 //23400
#define MAXSPEED 40500 //18000

void setup() {
  Serial.begin(9600);
  setupPWM16();
}

uint16_t icr = 0xffff;
int num = 0;
void loop() {
  Serial.println("*");
  for (uint16_t i = MINSPEED; i < MAXSPEED; i++)
  {
    analogWrite16(9, i);
    Serial.print(i);
    Serial.write("\n");
    delay(1);
  }
  //int num = Serial.read();
  //analogWrite16(9, num);
}

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
