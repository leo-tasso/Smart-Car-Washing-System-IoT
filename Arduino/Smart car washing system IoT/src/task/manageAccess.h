#ifndef _MENAGEACCESS_
#define _MENAGEACCESS_

#include "system/task.h"
#include "actuators/ServoMotor.h"
#include "CarWasher.h"

class ManageAccess : public Task{
    private:
        ServoMotor* motor;
        void setState(int state);
        CarWasher *carWasher;

        enum {CLOSED, OPENING, OPEN, CLOSING} state;

    public:
        ManageAccess(int period, CarWasher *carWasher);
        void tick() override;
};

#endif