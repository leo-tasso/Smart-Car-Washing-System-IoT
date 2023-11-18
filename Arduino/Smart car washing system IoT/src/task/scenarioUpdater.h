#ifndef __SCENARIO_UPDATER__
#define __SCENARIO_UPDATER__

#include "CarWasher.h"
#include "actuators/Led.h"
#include "sensors/Pir.h"
#include "system/task.h"

class ScenarioUpdater : public Task {
   private:
    CarWasher *carWasher;

   public:
    ScenarioUpdater(int period, CarWasher *CarWasher);
    void tick() override;
};

#endif