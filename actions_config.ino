#include"display.h"

void actions_config_main_handler(byte lastKeyPressed) {
  switch(lastKeyPressed) {
    case K_UP:
      if(indexLvl1 > 0) {
        indexLvl1--;
      } 
      break;

    case K_DOWN:
      if(indexLvl1 < configLvl1Length) {
        indexLvl1++;
      } 
      break;

    case K_ENTER:
      actions_config_lvl1_handler(); 
      break;
  }

  refreshDisplay();
}

void actions_config_lvl1_handler() {
  switch(indexLvl1) {
    case 0: // UP
      // BACK to SHOW TEMP
      mode = MODE_SHOW_TEMPERATURE;
      break;

    case 1: // CONST
      // muestra menu Constantes
      mode = MODE_SETTINGS_LVL_2_CONST;
      break;

    case 2: // CONST
      // muestra menu Constantes
      mode = MODE_SETTINGS_LVL_2_MODO;
      break;
  }
}


// Seccion Constantes
void actions_config_lvl2_const_handler(byte lastKeyPressed) {
  switch(lastKeyPressed) {
    case K_UP:
      if(indexLvl2Const > 0) {
        indexLvl2Const--;
      } 
      break;

    case K_DOWN:
      if(indexLvl2Const < configLvl2ConstLength) {
        indexLvl2Const++;
      } 
      break;

    case K_ENTER:
      actions_config_lvl2_const_actions_handler();
      break;
  }

  refreshDisplay();
}

void actions_config_lvl2_const_actions_handler() {
  switch(indexLvl2Const) {
    case 0: // UP
      // BACK to LVL 1
      mode = MODE_SETTINGS_LVL_1;
      break;

    case 1: // P
      // mode = MODE_SETTINGS_LVL_2_CONST;
      break;
    case 2: // I
      // mode = MODE_SETTINGS_LVL_2_CONST;
      break;
    case 3: // D
      // mode = MODE_SETTINGS_LVL_2_CONST;
      break;


  }

}



// Seccion MODO
void actions_config_lvl2_mode_handler(byte lastKeyPressed) {
  switch(lastKeyPressed) {
    case K_UP:
      if(indexLvl2Mode > 0) {
        indexLvl2Mode--;
      } 
      break;

    case K_DOWN:
      if(indexLvl2Mode < configLvl2ModeLength) {
        indexLvl2Mode++;
      } 
      break;

    case K_ENTER:
      actions_config_lvl2_mode_actions_handler();
      break;
  }

  refreshDisplay();
}

void actions_config_lvl2_mode_actions_handler() {
  switch(indexLvl2Mode) {
    case 0: // UP
      // BACK to LVL 1
      mode = MODE_SETTINGS_LVL_1;
      break;

    case 1: // PID
      // mode = MODE_SETTINGS_LVL_2_CONST;
      break;
    case 2: // FIJO
      // mode = MODE_SETTINGS_LVL_2_CONST;
      break;
    case 3: // Logger
      // mode = MODE_SETTINGS_LVL_2_CONST;
      break;
  }

}

