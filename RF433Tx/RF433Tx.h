#ifndef RF433Tx_h
#define RF433Tx_h

#include "arduino.h"
#include "CyclicRedundantChecksum.h"
#include "Encoder.h"

class RF433Tx{
  public:
    enum Encoding {decimal, hexadecimal, jump};
    static Encoding encoding;
    static boolean useCRC;
    static void setGP(String gp);
    static void send(String transmittingMessage);
  private:
    static String GP;
};

#endif
