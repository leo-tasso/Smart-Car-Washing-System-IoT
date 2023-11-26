#include "task/washingAreaPresenceDetection.h"
#include "sensors/Sonar.h"
#include "config.h"

WashingAreaPresenceDetection::WashingAreaPresenceDetection(int period, 
                                                           CarWasher *carWasher, 
                                                           int pinSonar) 
    : Task(period), 
      carWasher(carWasher), 
      detector(new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, 1000))
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