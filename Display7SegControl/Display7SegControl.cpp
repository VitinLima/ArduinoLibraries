#include "arduino.h"
#include "Display7SegControl.h"

Display7SegControl::Display7SegControl(int a, int b, int c, int d, int e, int f, int g, int p, int _delay_1, int _delay_2) {
  port[0] = a;
  port[1] = b;
  port[2] = c;
  port[3] = d;
  port[4] = e;
  port[5] = f;
  port[6] = g;
  dot = p;
  delay_1 = _delay_1;
  delay_2 = _delay_2;
  encoding[0] = 0b0000000;
  encoding[1] = 0b1111110;
  encoding[2] = 0b0110000;
  encoding[3] = 0b1101101;
  encoding[4] = 0b1111001;
  encoding[5] = 0b0110011;
  encoding[6] = 0b1011011;
  encoding[7] = 0b1011111;
  encoding[8] = 0b1110000;
  encoding[9] = 0b1111111;
  encoding[10] = 0b1110011;
  encoding[11] = 0b1110111;
  encoding[12] = 0b0011111;
  encoding[13] = 0b0001101;
  encoding[14] = 0b0111101;
  encoding[15] = 0b1001111;
  encoding[16] = 0b1000111;
  for (int i = 0; i < 7; i++) {
    pinMode(port[i], OUTPUT);
  }
  pinMode(dot, OUTPUT);
  write(0);
  writeDot(LOW);
}

void Display7SegControl::write(int _v) {
  if (_v < -1 || _v > 15) {
    return;
  }
  v = _v;
  v++;
  byte enc = encoding[v];
  byte mask = 0b1000000;
  for (int i = 0; i < 7; i++) {
    if (enc & mask) {
      digitalWrite(port[i], HIGH);
    } else {
      digitalWrite(port[i], LOW);
    }
    mask >>= 1;
  }
}

void Display7SegControl::writeDot(boolean _dotState) {
  dotState = _dotState;
  digitalWrite(dot, dotState);
}

void Display7SegControl::printByte(byte b){
  byte l = b&0x0f;
  byte h = b>>4;
  write((int)h);
  writeDot(HIGH);
  delay(delay_1);
  writeDot(LOW);
  delay(delay_2);
  write((int)l);
  writeDot(HIGH);
  delay(delay_1);
  writeDot(LOW);
  delay(delay_2);
}

void Display7SegControl::printInteger(int val){
  int inVal = 0;
  int k = 0;
  do{
    inVal *= 10;
    inVal += val%10;
    val /= 10;
    k++;
  }while(val>0);
  for(int i = 0; i < k; i++){
    write(inVal%10);
    inVal /= 10;
    if(v!=-1){
      writeDot(HIGH);
      delay(delay_1);
      writeDot(LOW);
      delay(delay_2);
    } else{
      delay(delay_1+delay_2);
    }
  }
}

int Display7SegControl::getValue() {
  return v - 1;
}

boolean Display7SegControl::getDotState() {
  return dotState;
}
