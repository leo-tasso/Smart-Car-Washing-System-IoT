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
            if (!carWasher->carInWashingArea) {
                l3->turnOff();
                if (!carWasher->gateOpen) {
                    carWasher->washingComplete = false;
                }
            }
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
            if (this->carWasher->requiringManteinance) {
                this->setState(MAINT_REQ);
            }
            if (this->elapsedTimeInState() + this->timeInMainteinance >= N3) {
                l3->turnOn();

                this->carWasher->washing = false;
                this->carWasher->washingComplete = true;
                this->carWasher->washingPercentage = 0;
                this->carWasher->washedCars++;
                this->timeInMainteinance = 0;
                this->setState(STOPPED);
            }
            break;
    }
};