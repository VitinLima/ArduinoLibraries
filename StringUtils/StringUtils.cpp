#include "arduino.h"
#include "StringUtils.h"

String StringUtils::parse(String inStr){
  boolean cb = false;
  String outStr;
  for(int i = 0; i < inStr.length(); i++){
    char c = inStr[i];
    if (cb) {
      switch(c){
        case '\\':
          outStr += '\\';
          break;
        case 'n':
          outStr += '\n';
          break;
        case 't':
          outStr += '\t';
          break;
      }
      cb = false;
    } else if (c == '\\') {
      cb  = true;
    } else{
      outStr += c;
    }
  }
  return outStr;
}

String StringUtils::pad(String inStr, int padding){
  String outStr = "";
  int k = 0;
  boolean toPad = false;
  for(int i = 0; i < inStr.length(); i++){
    if(inStr[i]=='\n'){
      toPad = true;
    } else{
      outStr += inStr[i];
      k++;
      if(k==16){
        toPad = true;
      }
    }
    if(toPad){
      toPad = false;
      for(int j = k; j < 16; j++){
        outStr += ' ';
      }
      k = 0;
    }
  }
  return outStr;
}

String StringUtils::SR(String inStr){
  if(inStr.length() == 0){
    return "";
  }
  String outStr;
  byte b3 = (byte)inStr[0];
  outStr += (char)(b3>>1);
  for(int i = 1; i < inStr.length(); i++){
    byte b1 = ((byte)inStr[i])>>1;
    byte b2 = ((byte)inStr[i-1])<<7;
    outStr += (char)(b1|b2);
  }
  return outStr;
}

static int StringUtils::availableMemory() {
    // Use 1024 with ATmega168
    int size = 2048;
    byte *buf;
    while ((buf = (byte *) malloc(--size)) == NULL){
        free(buf);
    }
    free(buf);
    return size;
}

String StringUtils::asBinary(byte b){
  String s = "";
  byte mask = 0b10000000;
  for(int i = 0; i < 8; i++){
    if((b&mask)==0x00){
      s += "0";
    } else{
      s += "1";
    }
    mask>>=1;
  }
  return s;
}

String StringUtils::asBinary(String str){
  String s = "";
  int N = str.length()-1;
  if(N < 0){
    return;
  }
  for(int i = 0; i < N; i++){
    s += asBinary(str[i]);
    s += ",";
  }
  s+=asBinary(str[N]);
  return s;
}
