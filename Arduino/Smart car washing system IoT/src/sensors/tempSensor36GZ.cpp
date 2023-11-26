#include "tempSensor36GZ.h"
#include <Arduino.h>
#include "config.h"

#define VCC ((float)5)

TempSensor36GZ::TempSensor36GZ(int p) : pin(TMP_PIN){
}

float TempSensor36GZ::getTemperature(){
    int value = analogRead(pin);
    float valueInVolt = value*VCC/1023;
    float valueInCelsius = valueInVolt/0.01;
    return valueInCelsius;
}