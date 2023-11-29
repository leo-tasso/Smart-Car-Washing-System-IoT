#include "task/checkInPresenceDetection.h"

CheckInPresenceDetion::CheckInPresenceDetion(int period,
                                             CarWasher *carWasher,
                                             int pinPir,
                                             int pinL1)
    : TaskWithState(period),
      detector(new Pir(pinPir)),
      l1(new Led(pinL1)),
      carWasher(carWasher) {
}

void CheckInPresenceDetion::tick() {
    this->setState(detector->isDetected() ? CheckInStates::DETECTED : CheckInStates::UNDETECTED);
    switch (this->getState()) {
        case CheckInStates::DETECTED:
            carWasher->carInCheckIn = true;
            l1->turnOn();
            if (!detector->isDetected()) {
                this->setState(CheckInStates::UNDETECTED);
            }
            break;
        case CheckInStates::UNDETECTED:
            l1->turnOff();
            carWasher->carInCheckIn = false;
            if (detector->isDetected()) {
                this->setState(CheckInStates::DETECTED);
            }
            break;
    }
};
