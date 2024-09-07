#ifndef CyclicRedundantChecksum_h
#define CyclicRedundantChecksum_h

#include "arduino.h"
#include "StringUtils.h"

class CyclicRedundantChecksum{
  public:
//    CyclicRedundantChecksum();
    static String addCRC(String inputBytes, String GP);
    static boolean check(String inputBytes, String GP);
    static String removeCRC(String inputBytes, String GP);
//    void setGP(String gp);
//    void describeMessage(String str);
};

#endif
