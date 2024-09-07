#include "arduino.h"
#include "Encoder.h"

#define SP 0x1F

String Encoder::encodeToDEC(String inStr){
  String outStr;
  for(int i = 0; i < inStr.length(); i++){
    byte inByte = (byte)inStr[i];
    for(int j = 0; j < 3; j++){
      outStr += (char)(inByte%10+0x30);
      inByte /= 10;
    }
  }
  return outStr;
}

String Encoder::encodeToHEX(String inStr){
  String outStr;
  for(int i = 0; i < inStr.length(); i++){
    byte b = (byte)inStr[i];
    byte h = b>>4;
    byte l = b&0x0f;
    outStr += (char)(h + 48);
    outStr += (char)(l + 48);
  }
  return outStr;
}

String Encoder::encodeToJump(String str){
  String jumpedStr = "";
  byte b;
  for(int i = 0; i < str.length(); i++){
    b = (byte)str[i];
    if(b == 0x0A){
      jumpedStr += (char)SP;
      jumpedStr += (char)0x1A;
      continue;
    } else if(b == 0x0D){
      jumpedStr += (char)SP;
      jumpedStr += (char)0x1D;
      continue;
    } else if(b == SP){
      jumpedStr += (char)SP;
      jumpedStr += (char)SP;
      continue;
    }
    jumpedStr += (char)b;
  }
  return jumpedStr;
}

String Encoder::decodeFromDEC(String inStr){
  String outStr;
  for(int i = 0; i < inStr.length(); i++){
    byte inByte = 0x00;
    inByte += (byte)inStr[i++]-0x30;
    if(i == inStr.length()){
      continue;
    }
    inByte += ((byte)inStr[i++]-0x30)*10;
    if(i == inStr.length()){
      continue;
    }
    inByte += ((byte)inStr[i]-0x30)*100;
    outStr += (char)inByte;
  }
  return outStr;
}

String Encoder::decodeFromHEX(String inStr){
  String outStr;
  for(int i = 0; i < inStr.length(); i++){
    byte h = (byte)inStr[i++]-48;
    if(i == inStr.length()){
      continue;
    }
    byte l = (byte)inStr[i]-48;
    outStr += (char)((h<<4) | l);
  }
  return outStr;
}

String Encoder::decodeFromJump(String jumpedStr){
  String str = "";
  byte b;
  boolean sp = false;
  for(int i = 0; i < jumpedStr.length(); i++){
    b = (byte)jumpedStr[i];
    if(sp){
      if(b == 0x1A){
        str += (char)0x0A;
      } else if(b == 0x1D){
        str += (char)0x0D;
      } else if(b == SP){
        str += (char)SP;
      }
      sp = false;
      continue;
    } else if(b == SP){
      sp = true;
      continue;
    }
    str += (char)b;
  }
  return str;
}
