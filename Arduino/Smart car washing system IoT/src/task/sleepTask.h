#ifndef __SLEEPTASK__
#define __SLEEPTASK__

#include "CarWasher.h"
#include "system/scheduler.h"

class SleepTask : public Task {
    unsigned long timer{0};
    CarWasher* carWasher;
    int wakePin;

   public:
    SleepTask(int period,
              CarWasher* carWasher,
              int wakePin);
    void tick() override;
};

#endif