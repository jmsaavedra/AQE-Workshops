


void instructSlave(byte instruction, byte parameter){
  Serial.print("--- instructSlave: (0x");
  Serial.print(instruction, HEX);
  Serial.print(", 0x");
  Serial.print(parameter, HEX);
  Serial.println(")");
  Wire.beginTransmission(0x3); // transmit to device #44 (0x2c)
  //Serial.println("--- wire.beginTransmission");
  Wire.write(instruction);         // sends instruction byte  0x00 = give me number of connected sensors
  //Serial.println("--- wire.write instruction");
  Wire.write(parameter);                 // null parameter
  //Serial.println("--- wire.write paramater");
  Wire.endTransmission(true);  // stop transmitting            
  //Serial.println("--- wire.endTransmission");
  delay(100);                             // for fun?
}

int requestSlave(){
  Serial.println("--- requestSlave");
  long responseVal = 0;
  int bNum = 0;                          // number of bytes received so far
  Wire.requestFrom(0x3, 4);    // request 4 bytes from slave device #44

    while(Wire.available()){
    char c = Wire.read();
    //Serial.println(c);
    responseVal = c;
  }
  return responseVal; 
}

