#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

byte indexLvl1 = 0;
byte configLvl1Length = 2; // esto es la cantidad de items de lvl1 menos 1, actualizar si cambiamos el array
const char* configLvl1[] = {"UP   ", "CONST", "MODO "};  // config lvl 1

void refreshDisplay(byte st = 0);

#endif