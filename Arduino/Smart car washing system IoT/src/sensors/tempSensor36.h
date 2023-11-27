#ifndef _TEMP36_
#define _TEMP_

#include "tempSensor.h"

class TempSensor36: public TempSensor {

    public:
        TempSensor36(int pin, float aref);
        virtual float getTemperature();
    private:
        int pin;
        float aref; //Vcc
};

#endif