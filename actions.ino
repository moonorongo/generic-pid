#define SETPOINT_TIME 3000

unsigned long actionsEllapsedTime;


void actions_released(byte lastKeyPressed) {
  switch (mode) {
    case MODE_SHOW_TEMPERATURE:
      if(lastKeyPressed != K_ENTER) { // si se pulsa UP o DOWN
        mode = MODE_SET_POINT;
        actionsEllapsedTime = millis();
        new_SetPoint = Setpoint; // actualiza new sp para poder editarlo
      }

      break;

    case MODE_SET_POINT:  
        actions_setpoint_handler(lastKeyPressed, actionsEllapsedTime);
        break;

    case MODE_SETTINGS_LVL_1:
        actions_config_handler(lastKeyPressed, actionsEllapsedTime);
        break;
  }  
}

void actions_setup_pressed(byte lastKeyPressed) {
  mode = MODE_SETTINGS_LVL_1; 

  // fuerza released
  actions_released(lastKeyPressed);
}

void actions_setup() {
  actionsEllapsedTime = millis();
}

void actions_loop() {
  if(mode == MODE_SET_POINT) {
  // si pasa SETPOINT_TIME entnces vuelve a mode MODE_SHOW_TEMPERATURE
    if(millis() > actionsEllapsedTime + SETPOINT_TIME) {
      mode = MODE_SHOW_TEMPERATURE;
    }
  }

}