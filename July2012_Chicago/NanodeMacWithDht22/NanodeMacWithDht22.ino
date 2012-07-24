// Nanode_MAC
// Rufus Cable, June 2011 (threebytesfull)

// Sample code to read the MAC address from the 11AA02E48 on the
// back of the Nanode V5 board.

// This code is hacky and basic - it doesn't check for bus errors
// and will probably fail horribly if it's interrupted. It's best
// run in setup() - fetch the MAC address once and keep it. After
// the address is fetched, it puts the chip back in standby mode
// in which it apparently only consumes 1uA.

// Feel free to reuse this code - suggestions for improvement are
// welcome! :)

// BITS    7   6   5   4   3   2   1   0
// PORTD = D7  D6  D5  D4  D3  D2  D1  D0
// PORTB = -   -   D13 D12 D11 D10 D9  D8

// Nanode has UNI/O SCIO on DIG7

#include "DHT.h"
#include <NanodeMAC.h>
static uint8_t mymac[6] = { 
  0,0,0,0,0,0 };

#define DHTPIN 17 //analog pin 3
#define DHTTYPE DHT22   

void setup() {
  Serial.begin(9600);
  //get Nanode MAC address
  Serial.println("MAC Address Read:");
  NanodeMAC mac( mymac );
  Serial.print("MAC address is ");
  for (int i=0; i<6; i++) {
    if (mymac[i]<16) {
      Serial.print("0");
    }
    Serial.print(mymac[i], HEX);
    if (i<5) {
      Serial.print(":");
    } 
    else {
      Serial.println("");
    }
  }
  //begin DHT after MAC address is discovered
  Serial.println("DHT22 BEGIN");
  DHT dht(DHTPIN, DHTTYPE);
  dht.begin();
}

void loop() {
  // Sensor readings have about 2 - 5 seconds of response time
  DHT dht(DHTPIN, DHTTYPE);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = (t*9)/5 + 32;

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } 
  else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Celsius: "); 
    Serial.print(t);
    Serial.print(" *C\t");
    Serial.print("Fahrenheit: "); 
    Serial.print(f);
    Serial.println(" *F");
  }
  delay(150);
  //print MAC address 
  Serial.print("MAC address is ");
  for (int i=0; i<6; i++) {
    if (mymac[i]<16) {
      Serial.print("0");
    }
    Serial.print(mymac[i], HEX);
    if (i<5) {
      Serial.print(":");
    } 
    else {
      Serial.println("");
    }
  }
  delay(150);
}

