#ifndef _WASHINGAREAPRESENCEDETECTION_
#define _WASHINGAREAPRESENCEDETECTION_

#include "sensors/PresenceDetector.h"
#include "CarWasher.h"
#include "system/task.h"

class WashingAreaPresenceDetection : public Task {
private:
    PresenceDetector *detector;
    CarWasher *carWasher;
    bool detected = false;

public:
    WashingAreaPresenceDetection(int period, CarWasher *carWasher, int pinSonar);
    void tick() override;

};

#endif