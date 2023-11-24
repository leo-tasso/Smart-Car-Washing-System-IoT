#include "task/manageAccess.h"
#include <Arduino.h>
#include "actuators/ServoMotorImpl.h"
#include "CarWasher.h"
#include "config.h"

ManageAccess::ManageAccess(int period, CarWasher *carWasher) : Task(period), carWasher(carWasher) {
    this->motor = new ServoMotorImpl(SERVO_PIN);
    setState(CLOSED);
}

void ManageAccess::tick() {
    
};