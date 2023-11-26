#ifndef _WASHINGAREAPRESENCEDETECTION_
#define _WASHINGAREAPRESENCEDETECTION_

#include "sensors/Sonar.h"
#include "CarWasher.h"
#include "system/taskWithState.h"

enum class PresenceStates{DETECTED, UNDETECTED, WAIT};
class WashingAreaPresenceDetection : public TaskWithState<PresenceStates> {
private:
    Sonar *sonar;
    CarWasher *carWasher;

public:
    WashingAreaPresenceDetection(int period, CarWasher *carWasher, int pinSonar);
    void tick() override;

};


#endif