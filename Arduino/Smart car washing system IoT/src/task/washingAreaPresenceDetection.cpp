#include "task/washingAreaPresenceDetection.h"
#include "sensors/Sonar.h"
#include "config.h"
#include "system/logger.h"

WashingAreaPresenceDetection::WashingAreaPresenceDetection(int period, 
                                                           CarWasher *carWasher, 
                                                           int echoPin,
                                                           int trigPin) 
    : TaskWithState(period), 
      sonar(new Sonar(echoPin, trigPin, 20000)), 
      carWasher(carWasher){
    setState(PresenceStates::UNDETECTED);
}

void WashingAreaPresenceDetection::tick() {
    logger(this->sonar->getDistance());
    switch (this->getState()){
    case PresenceStates::UNDETECTED:
        if (sonar->getDistance() <= minDist && this->elapsedTimeInState() >= N2){
            carWasher->carInWashingArea = true;
            setState(PresenceStates::DETECTED);
        }
        break;
    case PresenceStates::DETECTED:
        if (sonar->getDistance() >= maxDist || sonar->getDistance() == noObjDetected){
            if (this->elapsedTimeInState() >= N4){
                carWasher->carInWashingArea = false;
                setState(PresenceStates::UNDETECTED);
            }
        }
        break;
    default:
        break;
    }
}