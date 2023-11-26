#ifndef _MENAGEACCESS_
#define _MENAGEACCESS_

#include "system/taskWithState.h"
#include "actuators/ServoMotor.h"
#include "CarWasher.h"

class ManageAccess : public TaskWithState{
    private:
        ServoMotor* motor;
        CarWasher *carWasher;

    public:
        ManageAccess(int period, CarWasher *carWasher);
        void tick() override;
};

enum GateState{CLOSED, WAIT, WAIT_EXIT, WAIT_ENTRING, OPENING, OPEN, CLOSING};
#endif