#include "arduino.h"
#include "SerialRx.h"

String SerialRx::receivingMessage = "";
String SerialRx::receivedMessage = "";
boolean SerialRx::messageReceived = false;

boolean SerialRx::messageAvailable(){
  return SerialRx::messageReceived;
}

String SerialRx::readMessage(){
  SerialRx::messageReceived = false;
  return SerialRx::receivedMessage;
}

void SerialRx::update(){
  while(Serial.available()){
    byte b = Serial.read();
    if(b == 0x0D){
      continue;
    } else if(b == 0x0A){
      SerialRx::receivedMessage = SerialRx::receivingMessage;
      SerialRx::receivingMessage = "";
      SerialRx::messageReceived = true;
    } else{
      receivingMessage += (char)b;
    }
  }
}

void serialEvent(){
  SerialRx::update();
}
