#ifndef _TEMP_SENSOR_IMPL_
#define _TEMP_SENSOR_IMPL_

#include "sensors/tempSensor.h"

class TempSensorImpl : public TempSensor{

private:
    int pin;

public:
    //TempSensor36GZ(int pin);
    virtual float getTemperature();
};

#endif