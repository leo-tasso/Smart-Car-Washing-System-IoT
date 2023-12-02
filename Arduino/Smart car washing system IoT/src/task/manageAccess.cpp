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
    this->motor->setPosition(ANGLE_CLOSED);
    setState(GateState::CLOSED);
}

void ManageAccess::tick() {
    switch (this->getState()) {
        case GateState::CLOSED:
            if (carWasher->carInCheckIn && !carWasher->carInWashingArea) {
                setState(GateState::WAIT);
            } else if (carWasher->washingComplete) {
                this->motor->setPosition(ANGLE_OPENED);
                this->setState(GateState::OPENING);
            }
            break;
        case GateState::WAIT:
            if (this->elapsedTimeInState() >= N1) {
                this->motor->setPosition(ANGLE_OPENED);
                setState(GateState::OPENING);
            }
            break;
        case GateState::OPENING:
            if (this->elapsedTimeInState() >= transitionTime) {
                carWasher->gateOpen = true;
                if (carWasher->carInWashingArea) {
                    setState(GateState::OPEN_EXIT);
                } else {
                    setState(GateState::OPEN_ENTRING);
                }
            }
            break;
        case GateState::OPEN_ENTRING:
            if (carWasher->carInWashingArea) {
                this->motor->setPosition(ANGLE_CLOSED);
                setState(GateState::CLOSING);
            }
            break;
        case GateState::OPEN_EXIT:  // Wait that the car exit also from the check in area.
            if (!carWasher->carInWashingArea && !carWasher->carInCheckIn) {
                this->motor->setPosition(ANGLE_CLOSED);
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