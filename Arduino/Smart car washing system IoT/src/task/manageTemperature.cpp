#include "manageTemperature.h"

#include <Arduino.h>

#include "config.h"
#include "sensors/tempSensor36.h"

constexpr float vcc = 5.0;

ManageTemperature::ManageTemperature(int period,
                                     CarWasher *carWasher,
                                     int pin)
    : Task(period),
      temperature(new TempSensor36(pin, vcc)),
      carWasher(carWasher) {
}

void ManageTemperature::tick() {
    carWasher->temp = (float)temperature->getTemperature();
    if (carWasher->washing) {
        this->state = this->carWasher->temp >= MAXTEMP ? ACCEPTABLE : UNACCEPTABLE;
        if (this->state == UNACCEPTABLE) {
            carWasher->requiringManteinance = true;
        }
    }
}