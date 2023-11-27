#ifndef _PROXIMITYSENSOR_
#define _PROXIMITYSENSOR_

#include "PresenceDetector.h"

class ProximitySensor {
    public:
    virtual double getDistance();
};

#endif