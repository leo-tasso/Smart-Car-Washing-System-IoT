#ifndef _PROXIMITYSENSOR_
#define _PROXIMITYSENSOR_

#include "PresenceDetector.h"

class ProximitySensor {
    public:
    virtual float getDistance();
};

#endif