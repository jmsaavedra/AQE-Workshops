
#include <Wire.h>

int thisSensorVal = 0;
int currentDevice = 0;
int numSensors = 0;

void setup() {
  delay(3000);
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println("\nSETUP...\n");
  
  currentDevice = 0x3; // set current device on our I2C bus to talk to --ATTiny on interface shield is set to address 0x3
  
  //instructSlave(byte instruction, byte paramater);
  instructSlave(0x00, 0x00); // 0x00 == count number of sensors attached; null paramater
  numSensors = requestSlave(); // request a response to instruction
  Serial.print("NUMBER OF ATTACHED SENSORS = ");
  Serial.println(numSensors);
  
  Serial.println("\n...SETUP\n");
}

void loop() {

  for (int i=0; i<numSensors; i++){
    //Serial.print("device number: "); //this is for when we have addons attached
    //Serial.print(currentDevice);
    Serial.print("------ sensor index: ");
    Serial.print(i);
    Serial.println(" ----");

    instructSlave(0x11, byte(i)); //0x11 == prepare current RAW sensor value; which sensor
    thisSensorVal = requestSlave();
    Serial.print("RAW SENSOR VAL = ");
    //Serial.println(thisSensorVal, HEX);
    Serial.println(thisSensorVal, DEC);

    instructSlave(0x22, byte(i)); //0x22 == prepare current CALCULATED sensor value; which sensor
    thisSensorVal = requestSlave();
    Serial.print("CALC SENSOR VAL = ");
    //Serial.println(thisSensorVal, HEX);
    Serial.println(thisSensorVal, DEC);
    
    Serial.println();
    delay(1000);
  }
  Serial.println("\n-------- loop end --------\n\n");
  delay(1000);
}

void instructSlave(byte instruction, byte parameter){
  Serial.print("--- instructSlave: (0x");
  Serial.print(instruction, HEX);
  Serial.print(", 0x");
  Serial.print(parameter, HEX);
  Serial.println(")");
  Wire.beginTransmission(currentDevice); // transmit to device #44 (0x2c)
  //Serial.println("--- wire.beginTransmission");
  Wire.write(instruction);         // sends instruction byte  0x00 = give me number of connected sensors
  //Serial.println("--- wire.write instruction");
  Wire.write(parameter);                 // null parameter
  //Serial.println("--- wire.write paramater");
  Wire.endTransmission(true);  // stop transmitting            
  //Serial.println("--- wire.endTransmission");
  delay(100);                             // for fun?
}

long requestSlave(){
  Serial.println("--- requestSlave");
  long responseVal = 0;
  int bNum = 0;                          // number of bytes received so far
  Wire.requestFrom(currentDevice, 4);    // request 4 bytes from slave device #44

    while(Wire.available()){
    char c = Wire.read();
    //Serial.println(c);
    responseVal = c;
  }
  return responseVal; 
}









