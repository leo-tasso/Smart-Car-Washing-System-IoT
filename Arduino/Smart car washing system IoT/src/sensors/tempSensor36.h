#ifndef _TEMP36_
#define _TEMP_

#include "tempSensor.h"

class TempSensor36: public TempSensor {

    public:
        TempSensor36(int pin, float aref);
        virtual double getTemperature();
    private:
        int pin;
        double aref; //Vcc
};

#endif