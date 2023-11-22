#ifndef __CHECKINPRESENCEDETECTION__
#define __CHECKINPRESENCEDETECTION__

#include "CarWasher.h"
#include "actuators/Led.h"
#include "sensors/Pir.h"
#include "system/task.h"

class CheckInPresenceDetion : public Task {
   private:
    PresenceDetector *detector;
    Light *l1;
    CarWasher *carWasher;
    enum {
        DETECTED,
        UNDETECTED
    } state{UNDETECTED};

   public:
    CheckInPresenceDetion(int period, CarWasher *CarWasher, int pinPir, int pinL1);
    void tick() override;
};

#endif