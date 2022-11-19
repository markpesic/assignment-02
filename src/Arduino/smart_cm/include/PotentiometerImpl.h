#ifndef __POTENTIOMETERIMPL__
#define __POTENTIOMETERIMPL__

#include "Potentiometer.h"

class PotentiometerImpl: public Potentiometer {
 
public: 
  PotentiometerImpl(int pin);
  int getValue();

private:
  int pin;
  int current = 0;
};

#endif