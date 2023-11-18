#ifndef __CARWASHER__
#define __CARWASHER__

enum scenario {
    SLEEP,
    WELCOME,
    ENTER,
    FULL_ENTERED,
    WASHING,
    COMPLETE,
    MAINT_REQ,
};

class CarWasher {
   public:
    bool carInCheckIn;
    bool carInWashingArea;
    double temp;
    bool requiringManteinance;
    bool gateOpen;
    unsigned int washedCars;
    scenario activeScenario;
};

#endif