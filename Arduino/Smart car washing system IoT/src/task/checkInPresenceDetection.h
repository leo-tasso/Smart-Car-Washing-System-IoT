#ifndef __CHECKINPRESENCEDETECTION__
#define __CHECKINPRESENCEDETECTION__

#include "CarWasher.h"
#include "system/task.h"
#include "sensors/Pir.h"
#include "actuators/Led.h" 

class CheckInPresenceDetector: public Task {
  PresenceDetector * detector;
  Light * l1; 
  CarWasher * carWasher;


public:
  CheckInPresenceDetector(int period, CarWasher *CarWasher, int pinPir, int pinL1);
  void tick() override;

private:
  enum
  {
    DETECTED,
    UNDETECTED
  } state{UNDETECTED};
};


#endif