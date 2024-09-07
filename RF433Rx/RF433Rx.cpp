#include "arduino.h"
#include "RF433Rx.h"

String RF433Rx::GP = "" + (char)0x84 + (char)0x73 + (char)0xF1 + (char)0xAE + (char)0xA5;
String RF433Rx::receivedMessage="";
String RF433Rx::receivingMessage="";
boolean RF433Rx::messageReceived=false;

void RF433Rx::setGP(String gp){
  if(gp.length() < 2){
    return;
  }
  GP = gp;
  bitSet(GP[0], 7);
}

void RF433Rx::updateSerial(){
  while (Serial.available()) {
    byte b = Serial.read();
    if(b == 0x0D){
      continue;
    }else if (b == 0x0A) {
      String msg = RF433Rx::receivingMessage;
      if(msg.length() == 0){
        RF433Rx::receivingMessage = "";
        continue;
      }
      msg = Encoder::decodeFromJump(msg);
      boolean check = CyclicRedundantChecksum::check(msg, RF433Rx::GP);
      if(check){
        RF433Rx::receivedMessage = CyclicRedundantChecksum::removeCRC(msg, RF433Rx::GP);
        RF433Rx::messageReceived = true;
      }
      RF433Rx::receivingMessage = "";
    } else {
      RF433Rx::receivingMessage += (char)b;
    }
  }
}

String RF433Rx::readMessage(){
  RF433Rx::messageReceived = false;
  return RF433Rx::receivedMessage;
}

boolean RF433Rx::messageAvailable(){
  return RF433Rx::messageReceived;
}

void serialEvent() {
  RF433Rx::updateSerial();
}
