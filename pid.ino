/*
  utilizo PID by Brett Beauregard
  version 1.2.0
*/

#include <PID_v1.h>

#define RELAY_PIN 8

double Input, Output;

// SINTONIZACIÓN OPTIMIZADA PARA 1500W EN 10 LITROS:
// Kp = 45.0 (Reacciona con fuerza si está lejos)
// Ki = 1.5  (Muy lento para evitar que la inercia térmica cause sobrecalentamiento)
// Kd = 15.0 (Freno predictivo para anticipar el apagado antes de pasarse)
double Kp = 45.0, Ki = 1.5, Kd = 15.0; 
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// Ventana reducida a 4 segundos por la alta potencia del calefactor
unsigned long windowSize = 4000; 
unsigned long windowStartTime;

void pid_setup()
{
  Setpoint = 28;
  windowStartTime = millis();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  myPID.SetOutputLimits(0, windowSize);
  myPID.SetMode(AUTOMATIC);
}

void pid_loop()
{
  Input = temperature; // temperature es una variable global con la temperatura obtenida desde temperature.ino
  myPID.Compute();

  // 2. CUANTIZACIÓN: Redondear a los pasos de 1000 ms más cercanos
  // Sumamos 500 para lograr un redondeo simétrico antes de la división entera
  unsigned long quantizedOutput = ((unsigned long)Output + 500) / 1000;
  quantizedOutput = quantizedOutput * 1000; 

  if (quantizedOutput > windowSize) {
    quantizedOutput = windowSize;
  }

  // Control PWM Lento para el relé mecánico
  unsigned long now = millis();
  if (now - windowStartTime > windowSize) {
    windowStartTime += windowSize;
  }

  if (quantizedOutput  < (now - windowStartTime)) {
    digitalWrite(RELAY_PIN, HIGH);  // Apaga
  } else {
    digitalWrite(RELAY_PIN, LOW); // Enciende
  }
}

