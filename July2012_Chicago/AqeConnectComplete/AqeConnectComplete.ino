
/*

*** NEED TO ADD DYNAMIC MAC ADDRESS QUERY ***
*** NEED TO REMOVE BUTTON ***

>>> Air Quality Egg v1.4 <<<
 
 Nanode based environmental sensor ethernet connected unit. 
 Measures NO2, CO, air quality, humidity, temperature.
 
 reset hack connects digital pin 3 to RESET pin. must be disconnected when programming.
 
 uses ethercard (Nanode) library from 
 http://github.com/jcw/ethercard
 
 jos.ph 2012
 http://cosm.com
 http://citizensensor.cc
 
*/

#include <EtherCard.h>
#include <Wire.h>

#define FEED    "68860" //unique feed id -- Egg feeds are below:
//unit01: 48091 // unit02: 48306 // unit03: 48307 // unit04: 48308 // unit05: 48309 // unit06: 48310 //
#define APIKEY  "_sG8TKAucC_cY02I8FIjYzkZkv-SAKxWWGZDWVh2eDlJbz0g"

//timer vars
const int transmitFrequency = 10; //time to wait between sending data in seconds
unsigned long currTime; //holds ms passed since board started

const int buttonPin = 7;

//sensor value vars
int currNo2, currCo, currQuality, currHumidity, currTemp, currButton = 0;

boolean debug = true;

//reset for when ethernet times out and never comes back
const int resetterPin = 3; //when pulled low, will reset board.

void setup () {
//  digitalWrite(resetterPin, HIGH); //this is a hack!

//  pinMode(resetterPin, OUTPUT);  
//  pinMode(buttonPin, INPUT);

  Serial.begin(57600); 
  Serial.println("...serial.begin");
//  ledSetup();
  nanodeSetup(); //nanode ethernet stup stuff
  Serial.println("...nanodeSetup");  
  sensorsSetup();
  Serial.println("...sensorsSetup");
  Wire.begin(); 
}

void loop () {
  currTime = millis();

  nanodeUpdate(); //checking for received data

  buttonUpdate(); //separate from sensors, we want to check it all the time

  ledUpdate();

  //note: transmitTime() contains sending function 
  if( !transmitTime() ){   //if we are not transmitting
    if(currTime%2000 == 0){  //print the currTime every second
      Serial.print("currTime: ");  
      Serial.println(currTime/1000);
      readSensors(); //update sensor values every second
    }
  } //else we are transmitting!
}


