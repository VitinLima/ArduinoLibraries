#ifndef StringUtils_h
#define StringUtils_h

#include "arduino.h"

class StringUtils{
  public:
    static String parse(String inStr);
    static String pad(String inStr, int padding);
    static String SR(String inStr);
    static String asBinary(byte b);
    static String asBinary(String str);
    static int availableMemory();
};

#endif
