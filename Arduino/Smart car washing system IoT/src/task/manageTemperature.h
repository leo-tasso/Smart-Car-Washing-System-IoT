#ifndef _TEMPERATURE_
#define _TEMPERATURE_

#include "system/taskWithState.h"
#include "sensors/tempSensor.h"
#include "CarWasher.h"

enum class TemperatureState{ACCEPTABLE, UNACCEPTABLE};
class ManageTemperature : public TaskWithState<TemperatureState>{
    private:
        TempSensor *temperature;
        CarWasher *carWasher;

    public:
        ManageTemperature(int period, CarWasher *carWasher, int pin);
        void tick() override;

};

#endif