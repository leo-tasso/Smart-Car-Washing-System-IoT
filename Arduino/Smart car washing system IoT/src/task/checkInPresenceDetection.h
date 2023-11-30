#ifndef __CHECKINPRESENCEDETECTION__
#define __CHECKINPRESENCEDETECTION__

#include "CarWasher.h"
#include "actuators/Led.h"
#include "sensors/Pir.h"
#include "system/taskWithState.h"

enum class CheckInStates {
    DETECTED,
    UNDETECTED
};
class CheckInPresenceDetion : public TaskWithState<CheckInStates> {
   private:
    PresenceDetector *detector;
    Light *l1;
    CarWasher *carWasher;

   public:
    CheckInPresenceDetion(int period, CarWasher *CarWasher, int pinPir, int pinL1);
    void tick() override;
};

#endif