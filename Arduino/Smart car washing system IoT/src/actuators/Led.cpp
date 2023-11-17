#include "Led.h"

#include "Arduino.h"

Led::Led(int pin)
{
    this->pin = pin;
    this->status = false;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Led::turnOn()
{
    digitalWrite(pin, HIGH);
    this->status = true;
}

void Led::turnOff()
{
    digitalWrite(pin, LOW);
    this->status = false;
};

bool Led::isOn()
{
    return this -> status;
}