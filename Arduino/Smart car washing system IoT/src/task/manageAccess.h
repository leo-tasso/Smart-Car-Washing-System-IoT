#ifndef _MENAGEACCESS_
#define _MENAGEACCESS_

#include "system/taskWithState.h"
#include "actuators/ServoMotor.h"
#include "CarWasher.h"

enum class GateState{CLOSED, WAIT, WAIT_EXIT, WAIT_ENTRING, OPENING, OPEN, CLOSING};
class ManageAccess : public TaskWithState<GateState>{
    private:
        ServoMotor* motor;
        CarWasher *carWasher;

    public:
        ManageAccess(int period, CarWasher *carWasher);
        void tick() override;
};

#endif