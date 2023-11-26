#ifndef _WASHINGAREAPRESENCEDETECTION_
#define _WASHINGAREAPRESENCEDETECTION_

#include "sensors/Sonar.h"
#include "CarWasher.h"
#include "system/taskWithState.h"

class WashingAreaPresenceDetection : public TaskWithState {
private:
    Sonar *sonar;
    CarWasher *carWasher;

public:
    WashingAreaPresenceDetection(int period, CarWasher *carWasher, int pinSonar);
    void tick() override;

};

enum {DETECTED, UNDETECTED, WAIT};
#endif