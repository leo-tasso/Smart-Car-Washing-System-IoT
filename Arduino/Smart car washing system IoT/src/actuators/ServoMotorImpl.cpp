#include "ServoMotorImpl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin){
    this->pin = pin;
}

void ServoMotorImpl::on(){
    //motor.attach(pin);
}

void ServoMotorImpl::off(){
    //motor.detach();
}

void ServoMotorImpl::setPosition(int angle){
    if (angle > 180){
        angle = 180;
    } else if (angle < 0){
        angle = 0;
    }
    float coeff = (2400.0-544.0)/180;
    //motor.write(544 + angle*coeff);
}