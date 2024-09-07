#ifndef Display7SegControl_h
#define Display7SegControl_h

#include "arduino.h"

class Display7SegControl{
  public:
    Display7SegControl(int a, int b, int c, int d, int e, int f, int g, int p, int _delay_1=500, int _delay_2=500);
    void write(int _v);
    void writeDot(boolean _dotState);
    void printByte(byte b);
    void printInteger(int val);
    int getValue();
    boolean getDotState();
  private:
    int v = 0;
    int port[7];
    int dot;
    boolean dotState;
    int encoding[17];
    int delay_1, delay_2;
};

#endif
