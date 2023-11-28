#include "manageTemperature.h"
#include "sensors/tempSensor36.h"
#include <Arduino.h>
#include "config.h"

constexpr float vcc = 5.0;

ManageTemperature::ManageTemperature(int period, 
                                     CarWasher *carWasher, 
                                     int pin) 
    : Task(period), 
      temperature(new TempSensor36(pin, vcc)), 
      carWasher(carWasher){
}

void ManageTemperature::tick(){
    this->state = temperature->getTemperature() >= MAXTEMP ? ACCETTABILE : UNACCETTABILE;
    carWasher->temp = temperature->getTemperature();
    if (this->state == UNACCETTABILE){
      carWasher->requiringManteinance = true;
    }
}