#ifndef _MENAGEACCESS_
#define _MENAGEACCESS_

#include "system/taskWithState.h"
#include "actuators/ServoMotor.h"
#include "CarWasher.h"

enum class GateState{CLOSED, WAIT, OPEN_EXIT, OPEN_ENTRING, OPENING, CLOSING};

class ManageAccess : public TaskWithState<GateState>{
    private:
        ServoMotor* motor;
        CarWasher *carWasher;

    public:
        ManageAccess(int period, CarWasher *carWasher, int servoPin);
        void tick() override;
};

#endif