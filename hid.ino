#define DEBOUNCE_TIME 50
#define PRESSING_TIME 2000

        
byte buttons[] = { 10, 9, 11 };  // pins utilizados en el arduino

unsigned long ellapsedTime;
byte keyStatus = 0;
byte lastKeyPressed = 255;
byte i = 0;
int buttonsLength;


void hid_setup() {
  buttonsLength = sizeof(buttons) / sizeof(buttons[0]); // una forma muy low level de obtener la longitud de un array :)
  for(i = 0; i < buttonsLength; i++) {
    pinMode(buttons[i], INPUT_PULLUP); 
  }
  
  ellapsedTime = millis();
  keyStatus = 0;
}

void hid_loop() {
  switch(keyStatus) {
    case 0: // read initial status
      for(i = 0; i < buttonsLength; i++) {
        if(!digitalRead(buttons[i])) {
          ellapsedTime = millis();
          keyStatus = 1;
          lastKeyPressed = i;
          break;
        }
      } // end for
      break;

    case 1: // key press (debounce)
      if(digitalRead(buttons[lastKeyPressed])) { // if released key
        if(millis() < ellapsedTime + DEBOUNCE_TIME) {
          keyStatus = 0;
          lastKeyPressed = 255;  
        } else {
          keyStatus = 4;
        }
      } else { // key still pressing
        if(millis() > ellapsedTime + PRESSING_TIME) {
          keyStatus = 3;
          actions_setup_pressed(lastKeyPressed);
        }          
      }
      break;

    case 3: // key still pressing
      if(digitalRead(buttons[lastKeyPressed])) { // if released key (after pressing time)
        keyStatus = 0; // bypass key released
        lastKeyPressed = 255;
      }
      break;

    case 4: // key released
      // disparar la accion correspondiente a la tecla presionada (kup, kdown o kenter)
      actions_released(lastKeyPressed);
      keyStatus = 0;
      lastKeyPressed = 255;
      break;
  }
  // END SWITCH MUSIC PLAYER

}