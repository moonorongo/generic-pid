

void actions_setpoint_handler(byte lastKeyPressed, unsigned long &actionsEllapsedTime) {
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
}