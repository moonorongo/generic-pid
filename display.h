#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

// Config level 1 Items
byte indexLvl1 = 0;
byte configLvl1Length = 2; // esto es la cantidad de items de lvl1 menos 1, actualizar si cambiamos el array
const char* configLvl1[] = {"UP   ", "CONST", "MODO "};  // config lvl 1

// Config Level 2 Items
byte indexLvl2Const = 0;
byte configLvl2ConstLength = 3;
const char* configLvl2Const[] = {"UP   ", "P    ", "I    ", "D    "};  // items lvl 2: Constantes

byte indexLvl2Mode = 0;
byte configLvl2ModeLength = 3;
const char* configLvl2Mode[] = {"UP   ", "PID  ", "FIJO ", "LOG  "};  // items lvl 2: Modo

void refreshDisplay(byte st = 0);

#endif