#include "RF433Rx.h"
#include <LiquidCrystal.h>

  /* Vss=GNG, Vdd=5V, V0=Pot, A=R200_5V, K=GND */
const int rs = 2, en = 3, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(1200);

  lcd.begin(16, 2);
  lcd.print("Hello, World!   ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("receiving       ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(RF433Rx::messageAvailable()){
    String msg = RF433Rx::readMessage();
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,0);
    for(int i = 0; i < 32 && i < msg.length(); i++){
      if(i == 16){
        lcd.setCursor(0,1);
      } else if(msg[i]==0x0A){
        lcd.setCursor(0,1);
        continue;
      }
      lcd.print(msg[i]);
    }
    delay(30);
  }
}
