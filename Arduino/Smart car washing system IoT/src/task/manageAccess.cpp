#include "task/manageAccess.h"

#include <Arduino.h>

#include "CarWasher.h"
#include "actuators/ServoMotorImpl.h"
#include "config.h"

ManageAccess::ManageAccess(int period, CarWasher *carWasher, int servoPin)
    : TaskWithState(period),
      motor(new ServoMotorImpl(servoPin)),
      carWasher(carWasher) {
    this->motor->on();
    setState(GateState::CLOSED);
}

void ManageAccess::tick() {
    switch (this->getState()) {
        case GateState::CLOSED:
            if (carWasher->carInCheckIn && !carWasher->carInWashingArea) {
                setState(GateState::WAIT);
            } else if (carWasher->washingComplete) {
                this->motor->setPosition(90);
                this->setState(GateState::OPENING);
            }
            break;
        case GateState::WAIT:
            if (this->elapsedTimeInState() >= N1) {
                this->motor->setPosition(90);
                setState(GateState::OPENING);
            }
            break;
        case GateState::OPENING:
            if (this->elapsedTimeInState() >= transitionTime) {
                carWasher->gateOpen = true;
                setState(GateState::OPEN);
            }
            break;
        case GateState::OPEN:
            if (carWasher->carInWashingArea) {
                setState(GateState::WAIT_EXIT);
            } else {
                setState(GateState::WAIT_ENTRING);
            }
            break;
        case GateState::WAIT_ENTRING:
            if (carWasher->carInWashingArea) {
                this->motor->setPosition(0);
                setState(GateState::CLOSING);
            }
            break;
        case GateState::WAIT_EXIT:
            if (!carWasher->carInWashingArea) {
                this->motor->setPosition(0);
                setState(GateState::CLOSING);
            }
            break;
        case GateState::CLOSING:
            if (this->elapsedTimeInState() >= transitionTime) {
                carWasher->gateOpen = false;
                setState(GateState::CLOSED);
            }
            break;
        default:
            break;
    }
};