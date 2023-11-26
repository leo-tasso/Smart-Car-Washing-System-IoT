#ifndef __WASHER__
#define __WASHER__

#include "CarWasher.h"
#include "actuators/Led.h"
#include "system/taskWithState.h"
#include "sensors/ButtonImpl.h"
#include "actuators/Led.h"

enum class WasherStates {STOPPED, WASHING, MAINT_REQ};
class Washer : public TaskWithState<WasherStates>{
   private:
    CarWasher *carWasher;
    Led * l3;
    Button * button;
    unsigned long timeInMainteinance{0};

   public:
    Washer(int period,
           CarWasher *CarWasher, 
           int pinL3,
           int pinButton);
    void tick() override;
};

#endif