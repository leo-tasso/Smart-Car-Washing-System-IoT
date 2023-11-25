#include "washer.h"

#include <Arduino.h>

#include "CarWasher.h"
#include "config.h"

Washer::Washer(int period,
               CarWasher *carWasher,
               int pinL3,
               int pinButton)
    : TaskWithState(period),
      carWasher(carWasher),
      l3(new Led(pinL3)),
      button(new ButtonImpl(pinButton, true)) {
    this->setState(STOPPED);
}

void Washer::tick() {
    switch (this->getState()) {
        case STOPPED:
            if (carWasher->carInWashingArea && !carWasher->gateOpen && button->isPressed()) {
                carWasher->washing = true;
                this->setState(WASHING);
            }
            break;
        case MAINT_REQ:
            if (!carWasher->requiringManteinance) {
                this->timeInMainteinance += this->elapsedTimeInState();
                this->setState(WASHING);
            }
            break;
        case WASHING:
            carWasher->washingPercentage = (this->elapsedTimeInState() + this->timeInMainteinance) / N3;
            if (this->elapsedTimeInState() + this->timeInMainteinance >= N3) {
                carWasher->washing = false;
                carWasher->washingComplete = true;
                carWasher->washingPercentage = 0;
                carWasher->washedCars++;
                this->setState(STOPPED);
            }
            break;
    }
};