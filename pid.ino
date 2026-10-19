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
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  windowStartTime = millis();

  //initialize the variables we're linked to
  Setpoint = 28;

  myPID.SetOutputLimits(0, windowSize);

  //turn the PID on
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

  // Asegurar por seguridad que no se salga de los límites [0, 4000]
  if (quantizedOutput > windowSize) {
    quantizedOutput = windowSize;
  }

  // Control PWM Lento para el relé mecánico
  unsigned long now = millis();
  if (now - windowStartTime > windowSize) {
    windowStartTime += windowSize;
  }

  if (quantizedOutput  < (now - windowStartTime)) {
    digitalWrite(RELAY_PIN, HIGH);  // Apagar 1500W
  } else {
    digitalWrite(RELAY_PIN, LOW); // Encender 1500W
  }

  // Serial.print("Target: "); Serial.print(Setpoint);
  // Serial.print(" | Actual: "); Serial.print(Input);
  // Serial.print(" | Q Pulso ON (ms): "); Serial.print(Output);
  // Serial.print(" | Pulso ON (ms): "); Serial.println(quantizedOutput);
}

