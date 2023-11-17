#include "task/checkInPresenceDetection.h"

CheckInPresenceDetector::CheckInPresenceDetector(int period, int pinPir, int pinL1) : Task(period)
{
    this->detector = new Pir(pinPir);
    this->l1 = new Led(pinL1);
    this->state = UNDETECTED;
};

void CheckInPresenceDetector::tick()
{
    // TODO change the global variables
    this->state = detector->isDetected() ? DETECTED : UNDETECTED;
    if (this->state == DETECTED)
    {
        l1->turnOn();
    }
    else
    {
        l1->turnOff();
    }
};
