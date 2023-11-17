#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pin) : pin(pin)
{
  pinMode(pin, INPUT);
}

bool Pir::isDetected(){
  return detected;
}