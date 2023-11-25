#ifndef _MENAGEACCESS_
#define _MENAGEACCESS_

#include "system/taskWithState.h"
#include "actuators/ServoMotor.h"
#include "CarWasher.h"

class ManageAccess : public TaskWithState{
    private:
        enum STATE{CLOSED, WAIT, WAIT_EXIT, WAIT_ENTRING, OPENING, OPEN, CLOSING} state;
        ServoMotor* motor;
        CarWasher *carWasher;
        long startOpening;

    public:
        ManageAccess(int period, CarWasher *carWasher);
        void tick() override;
};

#endif