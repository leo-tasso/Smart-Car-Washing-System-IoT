#ifndef __CARWASHER__
#define __CARWASHER__

class CarWasher {
   public:
    bool carInCheckIn;
    bool carInWashingArea;
    double temp;
    bool requiringManteinance;
    bool gateOpen;
    bool washing;
    bool washingComplete;
    unsigned int washingPercentage;
    unsigned int washedCars;
};

#endif