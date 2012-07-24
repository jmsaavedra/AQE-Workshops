
/* sensor vars and read functions */
#include "DHT.h"
#define DHTPIN 17 //analog pin 3
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

//debounce time (milliseconds) between each analog sensor reading
const int sensorDebounceTime = 15;

void sensorsSetup(){
  
   //begin DHT after MAC address is discovered
  Serial.println("DHT22 BEGIN");
 // DHT dht(DHTPIN, DHTTYPE);
  dht.begin(); 
}

void readSensors(){
  //sensors
  Serial.println("reading sensors");
  currNo2 = getNo2();
  delay(sensorDebounceTime);
  currCo = getCO();
  delay(sensorDebounceTime);
  currHumidity = getHumidity();
  delay(sensorDebounceTime);
  currTemp = getTemperature();
  delay(sensorDebounceTime);
}

//--------- e2v gas sensors ---------
int getNo2(){
  int thisReading = 10;
  instructSlave(0x11, byte(0)); //0x11 == prepare current RAW sensor value; which sensor
  thisReading = requestSlave();
  Serial.print("RAW SENSOR VAL = ");
  //Serial.println(thisSensorVal, HEX);
  Serial.println(thisReading, DEC);

//  instructSlave(0x22, 0x00); //0x22 == prepare current CALCULATED sensor value; which sensor
//  thisReading = requestSlave();
//  Serial.print("CALC SENSOR VAL = ");
//  //Serial.println(thisSensorVal, HEX);
//  Serial.println(thisReading, DEC);
    
  return thisReading;
}

int getCO(){
  int thisReading = 10;
  instructSlave(0x11, byte(1)); //0x11 == prepare current RAW sensor value; which sensor
  thisReading = requestSlave();
  Serial.print("RAW SENSOR VAL = ");
  //Serial.println(thisSensorVal, HEX);
  Serial.println(thisReading, DEC);

//  instructSlave(0x22, byte(1)); //0x22 == prepare current CALCULATED sensor value; which sensor
//  thisReading = requestSlave();
//  Serial.print("CALC SENSOR VAL = ");
//  //Serial.println(thisSensorVal, HEX);
//  Serial.println(thisReading, DEC);
    
  return thisReading;
}


//--------- DHT22 humidity sensor ---------
int getHumidity(){
  int thisReading = 13;

  float h = dht.readHumidity();

  if (isnan(h)){
    //failed to get reading from DHT
  } 
  else {
    thisReading = int(h);
    return thisReading;
  }
  return thisReading;
}

//--------- DHT22 temperature sensor ---------
int getTemperature(){
  int thisReading = 0;
  
  float t = dht.readTemperature();

  if (isnan(t)){
    //failed to get reading from DHT
  } 
  else {
    thisReading = int(t);
    return thisReading;
  }
}

