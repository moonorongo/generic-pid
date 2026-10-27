#include"display.h"

void actions_config_handler(byte lastKeyPressed, unsigned long &actionsEllapsedTime) {
  switch(lastKeyPressed) {
    case K_UP:
        Serial.println("K_UP");
      if(indexLvl1 > 0) {
        Serial.println("decremento K_UP");
        indexLvl1--;
      } 
      break;

    case K_DOWN:
        Serial.println("K_UP");
      if(indexLvl1 < configLvl1Length) {
        Serial.println("incremento K_UP");
        indexLvl1++;
      } 
      break;
  }

  refreshDisplay();

}


void actions_config_setup() {};

void actions_config_loop() {};