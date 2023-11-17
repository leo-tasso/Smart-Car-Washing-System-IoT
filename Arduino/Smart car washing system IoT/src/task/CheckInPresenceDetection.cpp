#include "task/checkInPresenceDetection.h"

CheckInPresenceDetector::CheckInPresenceDetector(int period, CarWasher *carWasher, int pinPir, int pinL1)
    : Task(period), detector(new Pir(pinPir)), l1(new Led(pinL1)), carWasher(carWasher)
{
}

void CheckInPresenceDetector::tick()
{
    this->state = detector->isDetected() ? DETECTED : UNDETECTED;
    if (this->state == DETECTED)
    {
        carWasher->carInCheckIn = true;
        l1->turnOn();
    }
    else
    {
        l1->turnOff();
        carWasher->carInCheckIn = false;
    }
};
