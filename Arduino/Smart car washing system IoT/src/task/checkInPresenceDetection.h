#ifndef __CHECKINPRESENCEDETECTION__
#define __CHECKINPRESENCEDETECTION__

#include "system/task.h"
#include "sensors/Pir.h"
#include "actuators/Led.h" 

class CheckInPresenceDetector: public Task {
  PresenceDetector * detector;
  Light * l1; 


public:
  CheckInPresenceDetector(int period, int pinPir, int pinL1);
  void tick();

private:
    enum { DETECTED, UNDETECTED} state;
};

#endif