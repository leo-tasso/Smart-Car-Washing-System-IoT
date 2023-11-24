#include "task/manageAccess.h"
#include <Arduino.h>
#include "actuators/ServoMotorImpl.h"
#include "CarWasher.h"
#include "config.h"


ManageAccess::ManageAccess(int period, CarWasher *carWasher) : Task(period), carWasher(carWasher) {
    this->motor = new ServoMotorImpl(SERVO_PIN);
    this->motor->on();
    setState(CLOSED);
}

void ManageAccess::tick() {
    switch (state){
    case CLOSED:
        if (carWasher->carInCheckIn){
            setState(OPENING);
            elapsedInState = millis();
        }
        break;
    case OPENING:
	if (millis() - elapsedInState >= N1 && startOpening == 0){
            this->motor->setPosition(90);
	    startOpening = millis();
        }
        if (millis()-startOpening >= openingTime)
            setState(OPEN);
            elapsedInState = millis();
        break;
    case OPEN:

        break;
    case CLOSING:

        break;
    default:
        break;
    }
};

void ManageAccess::setState(STATE newState){
    state = newState;
}