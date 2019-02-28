#include <Servo.h>

Servo Throttle; //set throttle and steering PWM objects
Servo Steering;

struct data{
  char speed;
  char angle;  
  char checksum;
} typedef Data; //set data structure. Contains speed and angle duty cycle value + checksum

char head[4] = {36,70,42,100}; //Set header value (4 byte header probably unnecessary)

long inputHeader = 0;
long* comparisonHeader = (long*)head; //store header as long value since uno is 16 bit 

int speed = 90; //initialise initial speed and angle values    
int angle = 90;
char incomingByte; //initalise recieved byte var 
 
Data* value = calloc(sizeof(Data),1); //initialise storage struct
char checksum = 36+70+42+100; //initalise checksum 

void setup() {
  Throttle.attach(5); //throttle output at pin 5
  Steering.attach(6); //steering output at pin 6
  Serial.begin(9600); 
  Throttle.write(speed); //initialise throttle position (especially important for some escs)
  Steering.write(angle); //move servo to center position 
}

char currvalue; 

void loop() {
    while (*comparisonHeader != inputHeader) {
               if(Serial.available()){ //header capturing 
                  currvalue = Serial.read();
                  inputHeader = inputHeader << 8;
                  inputHeader = inputHeader|currvalue;
               }
    }
    while(Serial.available() < 3); //wait for three bytes for speed, angle and checksum
    value->speed = Serial.read();
    value->angle = Serial.read();
    value->checksum = Serial.read();
    checksum += value->speed; //calc local checksum 
    checksum += value->angle;
    if(value->checksum == checksum){ //write if checksum is correct
       Throttle.write(value->speed);
       Steering.write(value->angle);
    }
    checksum = 36+70+42+100; //reset checksum value
    inputHeader = 0; //reset header storage
}
