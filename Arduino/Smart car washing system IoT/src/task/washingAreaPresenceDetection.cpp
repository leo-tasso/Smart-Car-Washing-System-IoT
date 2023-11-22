#include "task/washingAreaPresenceDetection.h"

WashingAreaPresenceDetection::WashingAreaPresenceDetection(int period, 
                                                           CarWasher *carWasher, 
                                                           int pinSonar) 
    : Task(period), carWasher(carWasher)//, detector(new Sonar(pinSonar))
{}