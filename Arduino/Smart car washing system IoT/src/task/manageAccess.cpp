#include "task/manageAccess.h"
#include <Arduino.h>
#include "actuators/ServoMotorImpl.h"
#include "CarWasher.h"
#include "config.h"

ManageAccess::ManageAccess(int period, CarWasher *carWasher) 
    : TaskWithState(period), 
      motor(new ServoMotorImpl(SERVO_PIN)),
      carWasher(carWasher) {
    this->motor->on();
    setState(CLOSED);
}

void ManageAccess::tick() {
    switch (this->getState()){
    case CLOSED:
        if (carWasher->carInCheckIn && !carWasher->carInWashingArea){
            setState(WAIT);
        } else if (carWasher->washingComplete){
            this->motor->setPosition(90);
            this->setState(OPENING);
        }
        break;
    case WAIT:
        if (this->elapsedTimeInState() >= N1){
            this->motor->setPosition(90);
            setState(OPENING);
        }
        break;
    case OPENING:
	    if (this->elapsedTimeInState() >= transitionTime)
            carWasher->gateOpen = true;
            setState(OPEN);
        break;
    case OPEN:
        if (carWasher->carInWashingArea){
            setState(WAIT_EXIT);
        } else setState(WAIT_ENTRING);
        break;
    case WAIT_ENTRING:
        if (carWasher->carInWashingArea){
            this->motor->setPosition(0);
            setState(CLOSING);
        }
        break;
    case WAIT_EXIT:
        if (!carWasher->carInWashingArea){
            if (carWasher->carInCheckIn)
                setState(WAIT_ENTRING);
            this->motor->setPosition(0);
            setState(CLOSING);
        }
        break;
    case CLOSING:
        if(this->elapsedTimeInState() >= transitionTime)
            carWasher->gateOpen = false;
            setState(CLOSED);
        break;
    default:
        break;
    }
};