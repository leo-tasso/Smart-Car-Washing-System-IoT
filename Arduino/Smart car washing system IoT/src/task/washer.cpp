#include "washer.h"

#include <Arduino.h>

#include "CarWasher.h"
#include "config.h"
#include "system/logger.h"

Washer::Washer(int period,
               CarWasher *carWasher,
               int pinL2,
               int pinL3,
               int pinButton)
    : TaskWithState(period),
      carWasher(carWasher),
      l2(new Led(pinL2)),
      l3(new Led(pinL3)),
      button(new ButtonImpl(pinButton, true)) {
    this->setState(WasherStates::STOPPED);
    l2->turnOff();
    l3->turnOff();
}

void Washer::tick() {
    switch (this->getState()) {
        case WasherStates::STOPPED:

            if (this->carWasher->gateOpen) {
                if (this->elapsedTimeInState() > PERIOD_L2_GATE + ledTimer) {
                    l2->isOn() ? l2->turnOff() : l2->turnOn();
                    ledTimer = this->elapsedTimeInState();
                }
            } else {
                l2->turnOff();
                ledTimer = 0;
            }

            if (!carWasher->carInWashingArea) {
                l3->turnOff();
                if (!carWasher->gateOpen) {
                    carWasher->washingComplete = false;
                }
            }
            if (carWasher->carInWashingArea && !carWasher->gateOpen && button->isPressed()) {
                carWasher->washing = true;
                this->setState(WasherStates::WASHING);
            }
            break;
        case WasherStates::MAINT_REQ:
            // logger("maintReq");
            if (!this->carWasher->requiringManteinance) {
                this->setState(WasherStates::WASHING);
            }
            break;
        case WasherStates::WASHING:
            carWasher->washingPercentage = (this->elapsedTimeInState() + this->totalWashTime) / (N3 / 100);
            if (this->elapsedTimeInState() > PERIOD_L2_WASHING + ledTimer) {
                l2->isOn() ? l2->turnOff() : l2->turnOn();
                ledTimer = this->elapsedTimeInState();
            }
            if (this->elapsedTimeInState() + this->totalWashTime >= N3) {
                l3->turnOn();
                this->l2->turnOff();
                ledTimer = 0;
                this->carWasher->washing = false;
                this->carWasher->washingComplete = true;
                this->carWasher->washingPercentage = 0;
                this->carWasher->washedCars++;
                this->totalWashTime = 0;
                this->setState(WasherStates::STOPPED);
            }
            if (this->carWasher->requiringManteinance) {
                this->l2->turnOff();
                ledTimer = 0;
                this->totalWashTime += this->elapsedTimeInState();
                this->setState(WasherStates::MAINT_REQ);
            }
            break;
    }
};