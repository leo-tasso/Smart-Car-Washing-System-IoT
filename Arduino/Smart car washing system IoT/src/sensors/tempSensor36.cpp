#include "tempSensor36.h"
#include <Arduino.h>
#include "config.h"

TempSensor36::TempSensor36(int pin, float aref) : pin(pin), aref(aref){
    pinMode(pin, INPUT);
}

double TempSensor36::getTemperature(){
    int value = analogRead(pin);
    double valueInVolt = (value/1024.0)*aref;
    double valueInCelsius = (valueInVolt-.5)*100;
    return valueInCelsius;
}