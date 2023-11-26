#ifndef _SONAR_
#define _SONAR_

#include "sensors/proximitySensor.h"

#define NO_OBJ_DETECTED -1;

class Sonar : public ProximitySensor{
    public:
        Sonar(int echoPin, int trigPin, long maxTime);
        float getDistance();
        float setTemperature(float temp);

    private:
        float getSoundVelocity();
        int echoPin, trigPin;
        float temperature;
        long timeOut; //if the signal don't come back in time the object is too far away = no object detected
};

#endif