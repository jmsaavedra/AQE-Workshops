/*  *** air quality egg ***
 
 - for board v1.4
 
 vic aprea < http://wickeddevice.com > and joe saavedra < http://sensemake.rs >
 based on code by:
 2011-07-08 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php
 
 */
#include <EtherCard.h>
#include <Wire.h>

// change these settings to match your own setup
#define FEED    "68860"
#define APIKEY  "_sG8TKAucC_cY02I8FIjYzkZkv-SAKxWWGZDWVh2eDlJbz0g"

// ethernet interface mac address, must be unique on the LAN
byte mymac[] = { 
  0x74,0x69,0x69,0x2D,0x30,0x31 };

const int transmitFrequency = 10; //time to wait between calls in seconds

String unitID = "unit01"; //name of unique datastreams (prefix)

unsigned long int currTime;

int currNo2 = 11; 
int currCo = 11;
int currHumidity = 11; 
int currTemp = 11; 
int currentDevice = 0x3;

void setup () {
  Serial.begin(9600);
  Serial.println("\n[webClient]");

  pinMode(3, INPUT);  //button on dPin 3
  pinMode(5, OUTPUT); //LED on dPin 5

  etherSetup(); //nanode ethernet stup stuff
  sensorsSetup();
  readSensors();
}

void loop () {
  currTime = millis();

  ether.packetLoop(ether.packetReceive()); //needs to stay near top of loop

  if( !transmitTime() ){         //if transmitTime returns false
    if(currTime%1000 == 0){      //print the currTime every second
      Serial.print("millis: ");  
      Serial.println(currTime/1000);
      readSensors();
    }
  }
}




