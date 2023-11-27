#include "task/washingAreaPresenceDetection.h"
#include "sensors/Sonar.h"
#include "config.h"

WashingAreaPresenceDetection::WashingAreaPresenceDetection(int period, 
                                                           CarWasher *carWasher, 
                                                           int echoPin,
                                                           int trigPin) 
    : TaskWithState(period), 
      sonar(new Sonar(echoPin, trigPin, 20000)), 
      carWasher(carWasher){
    setState(UNDETECTED);
}

void WashingAreaPresenceDetection::tick() {
    switch (this->getState()){
    case UNDETECTED:
        if (sonar->getDistance() <= minDist && this->elapsedTimeInState() >= N2){
            carWasher->carInWashingArea = true;
            setState(DETECTED);
        }
        break;
    /*case WAIT: Da discutere: gestisce caso in cui la macchina entra maesce prima che passi N2
        if (sonar->getDistance() <= minDist){
            if(this->elapsedTimeInState() >= N2)
                carWasher->carInWashingArea = true;
                setState(DETECTED);
        } else {
            setState(UNDETECTED);
        }
        break;*/
    case DETECTED:
        if (sonar->getDistance() >= maxDist || sonar->getDistance() == noObjDetected){
            if (this->elapsedTimeInState() >= N4){
                carWasher->carInWashingArea = false;
                setState(UNDETECTED);
            }
        }
        break;
    default:
        break;
    }
}