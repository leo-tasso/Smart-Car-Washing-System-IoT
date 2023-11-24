#ifndef _MENAGEACCESS_
#define _MENAGEACCESS_

#include "system/task.h"
#include "actuators/ServoMotor.h"
#include "CarWasher.h"

class ManageAccess : public Task{
    private:
        enum STATE{CLOSED, OPENING, OPEN, CLOSING} state;
        ServoMotor* motor;
        CarWasher *carWasher;
        void setState(STATE state);
        long elapsedInState;
        long startOpening;

    public:
        ManageAccess(int period, CarWasher *carWasher);
        void tick() override;
};

#endif