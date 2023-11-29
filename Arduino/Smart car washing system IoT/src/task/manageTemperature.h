#ifndef _TEMPERATURE_
#define _TEMPERATURE_

#include "system/task.h"
#include "sensors/tempSensor.h"
#include "CarWasher.h"

class ManageTemperature : public Task{
    private:
        TempSensor *temperature;
        CarWasher *carWasher;
        enum { ACCEPTABLE, UNACCEPTABLE} state{ACCEPTABLE};

    public:
        ManageTemperature(int period, CarWasher *carWasher, int pin);
        void tick() override;

};

#endif