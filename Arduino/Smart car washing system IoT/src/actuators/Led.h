#ifndef __LED__
#define __LED__

#include "Light.h"

class Led : public Light
{
public:
    Led(int pin);
    void turnOn();
    void turnOff();
    bool isOn();

protected:
    int pin;
    bool status;
};

#endif