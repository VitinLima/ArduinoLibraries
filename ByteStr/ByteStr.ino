#include "ByteStr.h"

void setup() {
  // put your setup code here, to run once:
  unsigned short int i = 2;
  int j = (int)i;
  Serial.begin(9600);
  Serial.println(j);
//  String str = "abc";
//  ByteStr bs1 = "abc";
//  ByteStr bs2 = bs1 + 'b';
//  Serial.begin(9600);
//  Serial.println(bs1);
//  Serial.println(bs2);
//  Serial.println(bs2.toString());
}

void loop() {
  // put your main code here, to run repeatedly:

}
