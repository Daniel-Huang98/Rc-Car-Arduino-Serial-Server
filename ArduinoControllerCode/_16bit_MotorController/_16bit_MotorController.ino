#define MINSPEED 25500 //23400
#define MAXSPEED 26500
//#define MAXSPEED 40500 //18000

struct data{
  uint16_t speed;  
  char checksum;
} typedef Data; 

//Start Initialise all variables
uint16_t speed = 90;//add the min speed here
char header[2] = {36,70};
unsigned int inputHeader = 0;
int* comparisonHeader = (int*)header;
Data* value = (Data*)calloc(sizeof(Data),1);//initialise storage struct
char checksum = 36+70;
char currvalue;
char* dataPointer = (char*) value;
uint16_t icr = 0xffff;
//End Initialise all variables


void checkHeader(){
   while (*comparisonHeader != inputHeader){
      if(Serial.available()){ //header capturing 
        currvalue = Serial.read();
        Serial.print(currvalue);
        inputHeader = inputHeader << 8;
        inputHeader = inputHeader|currvalue;
      }
    }
    inputHeader = 0;
}

char calCheckSum(char* dataPointer){
  char checksum = 36+70;
  for(int itr = 0; itr < 1; itr++){
    checksum += dataPointer[itr];
  }
  return checksum;
}

void readInData(char* dataPointer){
  dataPointer[1] = Serial.read(); //read in lower byte first
  dataPointer[0] = Serial.read(); //then read in higher byte
  dataPointer[2] = Serial.read();
}

void setup() {
  Serial.begin(9600); 
  setupPWM16();
  analogWrite16(9, 25500);
  delay(2000);
}

void loop() {
  checkHeader();
  while(Serial.available() < 3);
  readInData(dataPointer);
  if(calCheckSum(dataPointer) != value->checksum){
     if(value->speed > MAXSPEED)value->speed = MAXSPEED;
     analogWrite16(9, value->speed);
     
  }
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

