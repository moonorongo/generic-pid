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

/*
        if(lastKeyPressed != K_ENTER) { // Se incrementa o decrementa valor TEMPORARIO de Setpoint
          mode = MODE_SET_POINT;
          actionsEllapsedTime = millis();
          
          if(lastKeyPressed == K_UP) {
            if(new_SetPoint > 0) {
              new_SetPoint--;
            }
          } else {
              new_SetPoint++;
          }

        }

        if(lastKeyPressed == K_ENTER) { // se confirma valor de Setpoint
          mode = MODE_SHOW_TEMPERATURE;
          actionsEllapsedTime = millis();
          Setpoint = new_SetPoint; // actualiza SetPoint
          // Aqui deberiamos actualizar la configuracion en EEPROM
          // de manera correcta (que no use siempre la misma parte de la memoria)
          // pero para eso tengo que tener toda la estructura (SP, KP, Kd, Ki)
        }
*/
        break;

  }  
}

void actions_setup_pressed(byte lastKeyPressed) {
  mode = MODE_SETTINGS_LVL_1; 
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