#ifndef _SONAR_
#define _SONAR_

#include "sensors/proximitySensor.h"
#include <Arduino.h> 
#include "config.h"

class Sonar : public ProximitySensor{
    public:
        Sonar(int echoPin, int trigPin, long maxTime);
        double getDistance();
        void setTemperature(double temp);

    private:
        double getSoundVelocity();
        int echoPin, trigPin;
        double temperature;
        long timeOut; //if the signal don't come back in time the object is too far away = no object detected
};

#endif