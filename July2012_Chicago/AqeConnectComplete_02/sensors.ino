
/* sensor vars and read functions 

***TODO: 
  - add in the 0x22 instructions
  - remove any differentiation between NO2 and CO (did this for time reasons, clarity)
  - remove delays

*/

#include "DHT.h"
#define DHTPIN 17 //analog pin 3
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

//debounce time (milliseconds) between each analog sensor reading
const int sensorDebounceTime = 15;
int numSensors = 0;

void sensorsSetup(){
  //sensor value vars
  currNo2 = 1; 
  currCo = 1;
  currHumidity = 1; 
  currTemp = 1;
  Wire.begin();

  currentDevice = 0x3; // set current device on our I2C bus to talk to --ATTiny on interface shield is set to address 0x3

  //  instructSlave(byte instruction, byte paramater);
  //  instructSlave(0x00, 0x00); // 0x00 == count number of sensors attached; null paramater
  //  numSensors = requestSlave(); // request a response to instruction
  //  Serial.print("NUMBER OF ATTACHED SENSORS = ");
  //  Serial.println(numSensors);

  //begin DHT after MAC address is discovered
  Serial.println("DHT22 BEGIN");
  // DHT dht(DHTPIN, DHTTYPE);
  dht.begin(); 
  Serial.println("\n...SETUP\n");

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
  Serial.println("--- getNO2()");
  int thisReading = 10;
  instructSlave(0x11, byte(0)); //0x11 == prepare current RAW sensor value; which sensor
  //Serial.println("...instructSlave");
  delay(250);
  thisReading = requestSlave();
  //Serial.println("...instructSlave");
  Serial.print("RAW SENSOR VAL = ");
  //Serial.println(thisSensorVal, HEX);
  Serial.println(thisReading);

  //  instructSlave(0x22, 0x00); //0x22 == prepare current CALCULATED sensor value; which sensor
  //  thisReading = requestSlave();
  //  Serial.print("CALC SENSOR VAL = ");
  //  //Serial.println(thisSensorVal, HEX);
  //  Serial.println(thisReading, DEC);
  delay(1000);
  return thisReading;
}

int getCO(){
  int thisReading = 10;
  instructSlave(0x11, byte(1)); //0x11 == prepare current RAW sensor value; which sensor
  delay(250);
  thisReading = requestSlave();
  Serial.print("RAW SENSOR VAL = ");
  //Serial.println(thisSensorVal, HEX);
  Serial.println(thisReading, DEC);

  //  instructSlave(0x22, byte(1)); //0x22 == prepare current CALCULATED sensor value; which sensor
  //  thisReading = requestSlave();
  //  Serial.print("CALC SENSOR VAL = ");
  //  //Serial.println(thisSensorVal, HEX);
  //  Serial.println(thisReading, DEC);
  delay(1000);
  return thisReading;
}


//--------- DHT22 humidity ---------
int getHumidity(){
  int thisReading = 0;

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

//--------- DHT22 temperature ---------
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
