#ifndef __COMMUNICATOR__
#define __COMMUNICATOR__

#include "CarWasher.h"
#include "system/task.h"

class Communicator : public Task {
   private:
    CarWasher* carWasher;

   public:
    Communicator(int period, CarWasher* CarWasher);
    void tick() override;
};

#endif