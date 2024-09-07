#include "Encoder.h"

#define ENC Encoder

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  String msg = "11";
  Serial.println(msg);
  msg = ENC::encodeToHEX(msg);
  Serial.println(msg);
  msg = ENC::decodeFromHEX(msg);
  Serial.println(msg);
}

void loop() {
  // put your main code here, to run repeatedly:

}
