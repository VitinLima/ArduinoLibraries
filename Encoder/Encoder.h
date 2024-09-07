#ifndef Encoder_h
#define Encoder_h

#include "arduino.h"

class Encoder{
  public:
    static String encodeToDEC(String inStr);
    static String encodeToHEX(String inStr);
    static String encodeToJump(String str);
    static String decodeFromDEC(String inStr);
    static String decodeFromHEX(String inStr);
    static String decodeFromJump(String jumpedStr);
};

#endif
