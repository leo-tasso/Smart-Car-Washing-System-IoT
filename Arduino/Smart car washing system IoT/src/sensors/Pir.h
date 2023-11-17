#ifndef __PIR__
#define __PIR__

#include "PresenceDetector.h"

class Pir: public PresenceDetector {
 
public: 
  Pir(int pin);
  bool isDetected() override;

private:
  int pin;
  bool detected{false};
};

#endif