#include "MAX6675.h"

/*
   instalar la libreria MAX6675 de Rob Tillart
   la version que utilizo es 0.3.4
*/

#define checkInterval 1000 
#define temp_SO 7
#define temp_CS 6
#define temp_SCK 5

unsigned long temperature_ellapsedTime;
int status;

MAX6675 thermoCouple(temp_CS, temp_SO, temp_SCK); // ok ?
// MAX6675 thermoCouple(temp_SCK, temp_CS, temp_SO);


void temperature_showTemperature() {
  if (status == 0) {
    if(mode == MODE_SHOW_TEMPERATURE) {
      toArrayDigits(temperature);
    } else if(mode == MODE_SET_POINT) {
      toArrayDigits(new_SetPoint);
    }

    refreshDisplay();
  }
  else if (status == 4) { 
    // toArrayDigits(temperature); // mostrar Err 1
    refreshDisplay(1);
    Serial.println("error 1");
  }

  else if (status == 129) {
    // toArrayDigits(temperature); // mostrar Err 2
    refreshDisplay(2);
    Serial.println("error 2");
  }
}

void temperature_checkTemperature() {
  status = thermoCouple.read();


  temperature = thermoCouple.getCelsius();
}

void temperature_setup() {
  SPI.begin();
  thermoCouple.begin();
  // thermoCouple.setSPIspeed(1000000);
  temperature_ellapsedTime = millis();
  thermoCouple.setOffset(-4.0); // correcion de temperatura para la cupla q estoy usando
}


void temperature_loop() {
  // si paso mas de "checkInterval"  
  if(millis() >= temperature_ellapsedTime + checkInterval) {
    temperature_ellapsedTime = millis();

    temperature_checkTemperature();
  }
  
  temperature_showTemperature();
}

