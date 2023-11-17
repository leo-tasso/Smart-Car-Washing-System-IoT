#ifndef __CARWASHER__
#define __CARWASHER__

class CarWasher {
   public:
    bool carInCheckIn;
    bool carInWashingArea;
    double temp;
    bool isWashing;
    bool washingComplete;
    bool requiringManteinance;
    bool gateOpen;
    unsigned int washedCars;
};

#endif