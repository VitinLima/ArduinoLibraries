#ifndef SerialRx_h
#define SerialRx_h

#include "arduino.h"

class SerialRx{
  public:
    static boolean messageAvailable();
    static String readMessage();
    static void update();
  private:
    static String receivingMessage;
    static String receivedMessage;
    static boolean messageReceived;
};

#endif
