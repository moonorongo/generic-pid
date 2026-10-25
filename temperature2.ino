/*
  libs utilizadas:
    OneWire 2.3.8
    DallasTemperature 4.0.6
*/

#include <OneWire.h>
#include <DallasTemperature.h>

#define checkInterval 1000
#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long temperature2_elapsedTime = 0;
bool conversionPending = false;

void temperature2_showTemperature() {
  if(mode == MODE_SHOW_TEMPERATURE) {
    toArrayDigits(temperature);
  } else if(mode == MODE_SET_POINT) {
    toArrayDigits(new_SetPoint);
  }

  refreshDisplay();
}

void temperature2_checkTemperature() {
  // Si hay una conversión pendiente, obtenemos el resultado.
  if (conversionPending) {
    float tempC = sensors.getTempCByIndex(0);

    if (tempC == DEVICE_DISCONNECTED_C) {
      Serial.println("Error: No se pudo leer el sensor DS18B20.");
    } else {
      temperature = tempC;
    }
  }

  // Iniciamos una nueva conversión sin bloquear el programa.
  sensors.requestTemperatures();
  conversionPending = true;
}

void temperature2_setup() {
  sensors.begin();

  // Desactiva la espera hasta completar la conversión.
  sensors.setWaitForConversion(false);

  // Inicia la primera conversión.
  sensors.requestTemperatures();
  conversionPending = true;

  temperature2_elapsedTime = millis();
}

void temperature2_loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - temperature2_elapsedTime >= checkInterval) {
    temperature2_elapsedTime = currentMillis;
    temperature2_checkTemperature();
  }

  temperature2_showTemperature();
}