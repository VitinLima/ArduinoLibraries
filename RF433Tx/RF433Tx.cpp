#include "arduino.h"
#include "RF433Tx.h"

String RF433Tx::GP = "" + (char)0x84 + (char)0x73 + (char)0xF1 + (char)0xAE + (char)0xA5;
boolean RF433Tx::useCRC = true;
RF433Tx::Encoding RF433Tx::encoding = RF433Tx::jump;

void RF433Tx::setGP(String gp){
  if(gp.length() < 2){
    return;
  }
  GP = gp;
  bitSet(GP[0], 7);
}

void RF433Tx::send(String transmittingMessage){
  String msg = transmittingMessage;
  if(useCRC){
    msg = CyclicRedundantChecksum::addCRC(msg, RF433Tx::GP);
  }
  switch(encoding){
    case decimal:
      msg = Encoder::encodeToDEC(msg);
      break;
    case hexadecimal:
      msg = Encoder::encodeToHEX(msg);
      break;
    case jump:
      msg = Encoder::encodeToJump(msg);
      break;
  }

  int N0 = 3;
  int N1 = 1;
  int D = 10;
  bitClear(UCSR0A, TXC0);
    /* Send new line characters to wake up the receiver */
  for(int i = 0; i < N0; i++){
    Serial.print("\n");
  }
    /* Wait for empty transmit buffer */
  while(!bitRead(UCSR0A, TXC0))//while (!(UCSR0A & (1<<TXC0)))
  ;
    /* Help synchronize the USART */
  delay(D);
    /* Will clear the receiving buffer in the receiver */
  for(int i = 0; i < N1; i++){
    Serial.print("\n");
  }
    /* Send message */
  Serial.println(msg);
}
