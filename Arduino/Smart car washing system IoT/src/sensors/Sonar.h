#ifndef _SONAR_
#define _SONAR_

#include "sensors/proximitySensor.h"
#include "config.h"

class Sonar : public ProximitySensor{
    public:
        Sonar(int echoPin, int trigPin, long maxTime);
        float getDistance();
        void setTemperature(float temp);

    private:
        float getSoundVelocity();
        int echoPin, trigPin;
        float temperature;
        long timeOut; //if the signal don't come back in time the object is too far away = no object detected
};

#endif