#ifndef _TEMP_SENSOR_36GZ_
#define _TEMP_SENSOR_36GZ_

#include "tempSensor.h"

class TempSensor36GZ: public TempSensor {

    public:
        TempSensor36GZ(int pin);
        virtual float getTemperature();
    private:
        int pin;
};

#endif