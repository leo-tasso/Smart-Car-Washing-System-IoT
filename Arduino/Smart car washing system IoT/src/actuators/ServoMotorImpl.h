#ifndef _SERVO_MOTOR_IMPL_
#define _SERVO_MOTOR_IMPL_

#include "ServoMotor.h"
#include <Arduino.h>
#include <ServoTimer2.h>

class ServoMotorImpl: public ServoMotor{

private:
    int pin;

public:
    ServoMotorImpl(int pin);

    void on() = 0;
    void off() = 0;
    void setPosition(int angle) = 0;
    
};

#endif