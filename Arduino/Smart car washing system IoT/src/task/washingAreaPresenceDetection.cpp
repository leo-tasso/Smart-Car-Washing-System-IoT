#include "task/washingAreaPresenceDetection.h"

WashingAreaPresenceDetection::WashingAreaPresenceDetection(int period, 
                                                           CarWasher *carWasher, 
                                                           int pinSonar) 
    : Task(period), 
      carWasher(carWasher)//, detector(new Sonar(pinSonar))
{

}

void WashingAreaPresenceDetection::tick() {
    this->state = detector->isDetected() ? DETECTED : UNDETECTED;
    if (this->state == DETECTED) {
        carWasher->carInWashingArea = true;
    } else {
        carWasher->carInWashingArea = false;
    }
}