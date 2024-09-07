#include "StringUtils.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  String s = "Utilities\nString functions";
  s = StringUtils::pad(s, 16);
  Serial.print(s);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
