#include "DualShock2.h"
#include <SPI.h>

const int CS = 10, ACK=9;
DualShock2 cntrllr_1(CS, ACK);

uint8_t response[21];

void setup() {
//  // put your setup code here, to run once:
  Serial.begin(57600);
  SPI.begin();
  cntrllr_1.configurate(true, false, false);
}

void loop() {
  cntrllr_1.update();
  cntrllr_1.getData(response);
//  for(int i = 0; i < response.length(); i++){
//    String s = String((uint8_t)response[i], HEX);
//    for(int j = s.length(); j < 3; j++){
//      Serial.print("0");
//    }
//    Serial.print("0x" + s + " ");
//  }
//  Serial.print(response.length());
//  Serial.println("");
//  Serial.println(cntrllr_1.toString());
//  displayCommunication();
}

void displayCommunication(){
  Serial.print(cntrllr_1.isAnalog() ? "Analog Mode" : "Digital Mode");
  Serial.print("\tLx: ");Serial.print(cntrllr_1.getJoystick(JOYSTICK_Lx));
  Serial.print("\tLy: ");Serial.print(cntrllr_1.getJoystick(JOYSTICK_Ly));
  Serial.print("\tRx: ");Serial.print(cntrllr_1.getJoystick(JOYSTICK_Rx));
  Serial.print("\tRy: ");Serial.print(cntrllr_1.getJoystick(JOYSTICK_Ry));
  Serial.print("\tButtons pressed:");
  if(cntrllr_1.getButtonState(PAD_SELECT))  Serial.print("\tSEL");
  if(cntrllr_1.getButtonState(PAD_L3))  Serial.print("\tL3");
  if(cntrllr_1.getButtonState(PAD_R3))  Serial.print("\tR3");
  if(cntrllr_1.getButtonState(PAD_START))  Serial.print("\tSTART");
  if(cntrllr_1.getButtonState(PAD_UP))  Serial.print("\tUP");
  if(cntrllr_1.getButtonState(PAD_RIGHT))  Serial.print("\tRIGHT");
  if(cntrllr_1.getButtonState(PAD_DOWN))  Serial.print("\tDOWN");
  if(cntrllr_1.getButtonState(PAD_LEFT))  Serial.print("\tLEFT");
  if(cntrllr_1.getButtonState(PAD_L2))  Serial.print("\tL2");
  if(cntrllr_1.getButtonState(PAD_R2))  Serial.print("\tR2");
  if(cntrllr_1.getButtonState(PAD_L1))  Serial.print("\tL1");
  if(cntrllr_1.getButtonState(PAD_R1))  Serial.print("\tR1");
  if(cntrllr_1.getButtonState(PAD_TRIANGLE))  Serial.print("\tTRIANGLE");
  if(cntrllr_1.getButtonState(PAD_O))  Serial.print("\tO");
  if(cntrllr_1.getButtonState(PAD_X))  Serial.print("\tX");
  if(cntrllr_1.getButtonState(PAD_SQUARE))  Serial.print("\tSQUARE");
  Serial.print("\tpressures:");
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_UP));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_RIGHT));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_DOWN));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_LEFT));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_L2));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_R2));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_L1));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_R1));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_TRIANGLE));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_O));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_X));
  Serial.print("\t");Serial.print(cntrllr_1.getButtonPressure(PAD_SQUARE));
  Serial.print("\n");
}

byte charToHEX(char inChar){
  byte outByte;
  switch(inChar){
    case '0':
      outByte = 0x00;
      break;
    case '1':
      outByte = 0x01;
      break;
    case '2':
      outByte = 0x02;
      break;
    case '3':
      outByte = 0x03;
      break;
    case '4':
      outByte = 0x04;
      break;
    case '5':
      outByte = 0x05;
      break;
    case '6':
      outByte = 0x06;
      break;
    case '7':
      outByte = 0x07;
      break;
    case '8':
      outByte = 0x08;
      break;
    case '9':
      outByte = 0x09;
      break;
    case 'a':
      outByte = 0x0a;
      break;
    case 'b':
      outByte = 0x0b;
      break;
    case 'c':
      outByte = 0x0c;
      break;
    case 'd':
      outByte = 0x0d;
      break;
    case 'e':
      outByte = 0x0e;
      break;
    case 'f':
      outByte = 0x0f;
      break;
  }
  return outByte;
}

void printAsHEX(byte inByte){
  Serial.print("0x");
  if(inByte>>4 > 9){
    Serial.write((inByte>>4) + 87);
  } else{
    Serial.write((inByte>>4) + 48);
  }
  if((inByte&0x0f) > 9){
    Serial.write((inByte&0x0f) + 87);
  } else{
    Serial.write((inByte&0x0f) + 48);
  }
}

void printAsHEX(uint16_t inByte){
  Serial.print("0x");
  if(inByte>>12 > 9){
    Serial.write((inByte>>12) + 87);
  } else{
    Serial.write((inByte>>12) + 48);
  }
  if(((inByte>>8)&0x000f) > 9){
    Serial.write(((inByte>>8)&0x000f) + 87);
  } else{
    Serial.write(((inByte>>8)&0x000f) + 48);
  }
  if(((inByte>>4)&0x000f) > 9){
    Serial.write(((inByte>>4)&0x000f) + 87);
  } else{
    Serial.write(((inByte>>4)&0x000f) + 48);
  }
  if((inByte&0x000f) > 9){
    Serial.write((inByte&0x000f) + 87);
  } else{
    Serial.write((inByte&0x000f) + 48);
  }
}

void printAsBIN(byte inByte){
  Serial.print("0b");
  for(int i = 0; i < 8; i++){
    Serial.print((0x80>>i)&inByte ? "1" : "0");
  }
}

void printAsBIN(uint16_t inByte){
  Serial.print("0b");
  for(int i = 0; i < 16; i++){
    Serial.print((0x80>>i)&inByte ? "1" : "0");
  }
}
