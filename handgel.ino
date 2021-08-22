#include <math.h>
#include <SoftwareSerial.h>
int pinOut = 9;
SoftwareSerial mySerial(11,10); // RX, TX
unsigned char data[4]={};
float distance;
#define LEDPIN 13
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin  6: Teensy++ 2.0 has the LED on pin 6
  // Pin 13: Teensy 3.0 has the LED on pin 13

#define SENSORPIN 4

// variables will change:
int sensorState = 0, lastState=0;         // variable for reading the pushbutton status

void setup()
{
 Serial.begin(57600);
 mySerial.begin(9600); 
  Serial.begin(9600);
  pinMode(9, OUTPUT);
   // initialize the LED pin as an output:
  pinMode(pinOut, OUTPUT);      
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT);     
  digitalWrite(SENSORPIN, HIGH); // turn on the pullup
 
}

void loop()
{
    do{
     for(int i=0;i<4;i++)
     {
       data[i]=mySerial.read();
     }
  }while(mySerial.read()==0xff);

  mySerial.flush();


    // read the state of the pushbutton value:
  sensorState = digitalRead(SENSORPIN);

  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState == LOW) {     
    // turn LED on:
    digitalWrite(pinOut, LOW); 
      if(data[0]==0xff)
    {
      int sum;
      sum=(data[0]+data[1]+data[2])&0x00FF;
      if(sum==data[3])
      {
        distance=(data[1]<<8)+data[2];
        if(distance>10)
          {
           Serial.print("distance=");   //If the distance is less than 3 cm we will give a warning 
           Serial.print(distance/30);
           Serial.println("cm");
          }else 
             {
               Serial.println("Below the lower limit");
               Serial.println("De handgel is bijna leeg");
             }
      }
     }
     delay(100);
  } 
  else {
    // turn LED off:
    digitalWrite(pinOut, HIGH); 
  }
  
  if (sensorState && !lastState) {
    Serial.println("Unbroken");
  } 
  if (!sensorState && lastState) {
    Serial.println("Broken");
  }
  lastState = sensorState;
   if (Serial.available() > 0){ // at least one byte is available from the Lopy
   // read the message from the Lopy
   String msg = Serial.readStringUntil('\n');
   // and repeat the message back
   Serial.println("Lopy, did you say: " + msg + "?");
   }  
}
