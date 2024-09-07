#include "arduino.h"
#include "CyclicRedundantChecksum.h"

//CyclicRedundantChecksum::CyclicRedundantChecksum(){
//  GP += (char)0xA4;
//  GP += (char)0x69;
//}

String CyclicRedundantChecksum::addCRC(String inStr, String GP){
  String rem = inStr;
  for(int i = 0; i < GP.length(); i++){
    rem += (char)0x00;
  }
  for(int i = 0; i < inStr.length(); i++){
    String den = GP + (char)0x00;
    byte mask = 0b10000000;
    for(int j = 0; j < 8; j++){
      if((rem[i]&mask)!=0x00){
        for(int k = 0; k < den.length(); k++){
          rem[i+k] ^= den[k];
        }
      }
      den = StringUtils::SR(den);
      mask>>=1;
    }
  }
  String outStr = inStr;
  for(int i = inStr.length(); i < inStr.length()+GP.length(); i++){
    outStr += rem[i];
  }
  return outStr;
}

boolean CyclicRedundantChecksum::check(String inStr, String GP){
  if(inStr.length() < GP.length() + 1){
    return false;
  }
  String rem = inStr;
  for(int i = 0; i < inStr.length(); i++){
    String den = GP + (char)0x00;
    byte mask = 0b10000000;
    for(int j = 0; j < 8; j++){
      if((rem[i]&mask)!=0x00){
        for(int k = 0; k < den.length(); k++){
          rem[i+k] ^= den[k];
        }
      }
      den = StringUtils::SR(den);
      mask>>=1;
    }
  }
  boolean f = true;
  for(int i = rem.length() - GP.length(); i < rem.length() && f; i++){
    if(rem[i] != 0x00){
      f = false;
    }
  }
  return f;
}

String CyclicRedundantChecksum::removeCRC(String inStr, String GP){
  return inStr.substring(0,inStr.length()-GP.length());
}

//void CyclicRedundantChecksum::setGeneratorPolynomial(String gp){
//  if(gp.length()>=2){
//    GP = gp;
//    bitSet(GP[0], 7);
//  }
//}
//
//void CyclicRedundantChecksum::describeMessage(String msg){
//  Serial.print("Message is...");
//  Serial.println(StringUtils::asBinary(msg));
//  boolean notCorrupted = check(msg);
//  if(notCorrupted){
//    Serial.println("Message is not corrupted.");
//    Serial.print("Decoded message...");
//    Serial.println(removeCRC(msg));
//  } else{
//    Serial.println("Message corrupted.");
//  }
//}
