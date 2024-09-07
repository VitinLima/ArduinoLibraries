#include "RF433Tx.h"
#include "SerialRx.h"

#define SU StringUtils
#define PH 0.20
#define T 20

RF433Tx Tx;

String transmittingMessage = "Link Stablished!";
int count = 0;

int D0 = 200;
int D1 = 800;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(1200);

  D0 = T*PH;
  D1 = T*(1.0 - PH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(SerialRx::messageAvailable()){
    transmittingMessage = SerialRx::readMessage();
  }
  String msg = transmittingMessage + count++;
  if(count==10){
    count = 0;
  }
  
  Tx.send(msg);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(D0);
  digitalWrite(LED_BUILTIN, LOW);
  delay(D1);
  Serial.println("");
}
