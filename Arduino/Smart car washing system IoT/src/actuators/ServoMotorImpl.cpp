#include "ServoMotorImpl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin) : pin(pin){
}

void ServoMotorImpl::on(){
    motor.attach(pin);
}

void ServoMotorImpl::off(){
    motor.detach();
}

void ServoMotorImpl::setPosition(int angle){
    motor.write(angle);
}