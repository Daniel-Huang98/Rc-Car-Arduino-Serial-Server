#include <Servo.h>

Servo Steering;

struct data{
  uint16_t angle;  
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

void connect(){
    while(true){
      readInData(dataPointer);
      if(value->angle == 'F'){
         return; 
      }
      Serial.print("Steering$");  
    }
  
}
void setup() {
  Serial.begin(9600); 
  Steering.attach(4);
  Steering.write(90);
  connect();
  Serial.flush();
}

void loop() {
  Serial.print("$"); 
  checkHeader();
  while(Serial.available() < 3);
  readInData(dataPointer);
  if(calCheckSum(dataPointer) != value->checksum){
    Steering.write(value->angle%255);
  }
}



