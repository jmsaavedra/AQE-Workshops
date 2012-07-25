
/* I2C functions 
 
 TODO: 
 - un-hardcode the device number (right now set to device 3)
 - FIX REQUEST SLAVE baaahhh :-(
 */

void instructSlave(byte instruction, byte parameter){
  Serial.print("--- instructSlave: (0x");
  Serial.print(instruction, HEX);
  Serial.print(", 0x");
  Serial.print(parameter, HEX);
  Serial.println(")");
  Wire.beginTransmission(0x3);           // transmit to device 3 
  //Serial.println("--- wire.beginTransmission");
  Wire.write(instruction);               // sends instruction byte  0x00 = give me number of connected sensors
  //Serial.println("--- wire.write instruction");
  Wire.write(parameter);                 // null parameter
  //Serial.println("--- wire.write paramater");
  Wire.endTransmission(true);            // stop transmitting            
  //Serial.println("--- wire.endTransmission");
  delay(100);                             // for fun?
}

long requestSlave(){
  Serial.println("--- requestSlave");
  long responseVal = 0;
  int bNum = 0;                          // number of bytes received so far
  Wire.requestFrom(0x3, 4);              // request 4 bytes from slave device 3
  uint16_t r;
  while(Wire.available()){
    r = Wire.read();
    responseVal += r; 
    responseVal = responseVal << 8;   //aaaaahhhhhhhhh whyyyy

    //Serial.print("VALUE IN DEC: ");
    //Serial.println(r, DEC);
  }
  return responseVal; 
}

