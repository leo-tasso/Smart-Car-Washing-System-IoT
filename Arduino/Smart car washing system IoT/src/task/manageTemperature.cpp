#include "manageTemperature.h"

#include <Arduino.h>

#include "config.h"
#include "sensors/tempSensor36.h"

constexpr float vcc = 5.0;

ManageTemperature::ManageTemperature(int period,
                                     CarWasher *carWasher,
                                     int pin)
    : TaskWithState(period),
      temperature(new TempSensor36(pin, vcc)),
      carWasher(carWasher) {
}

void ManageTemperature::tick() {
    carWasher->temp = (float)temperature->getTemperature();
    if (carWasher->washing) {
        this->setState( this->carWasher->temp >= MAXTEMP ? TemperatureState::ACCEPTABLE : TemperatureState::UNACCEPTABLE);
        if (this->getState() == TemperatureState::UNACCEPTABLE){
            carWasher->requiringManteinance = true;
        }
    }
}