#ifndef RF433Rx_h
#define RF433Rx_h

#include "arduino.h"
#include "CyclicRedundantChecksum.h"
#include "Encoder.h"

class RF433Rx{
  public:
    static void setGP(String gp);
    static void updateSerial();
    static String readMessage();
    static boolean messageAvailable();
  private:
    static String GP;
    static String receivedMessage;
    static String receivingMessage;
    static boolean messageReceived;
};

#endif
