#include "CyclicRedundantChecksum.h"

#define CRC CyclicRedundantChecksum

const String GP = "" + (char)0x89 + (char)0xAE + (char)0x0E + (char)0xFF;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(CRC::addCRC("Hello World!", GP));
  delay(1000);
}
