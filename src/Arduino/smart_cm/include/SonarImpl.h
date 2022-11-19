#ifndef __SONARIMPL__
#define __SONARIMPL__

#include "Sonar.h"

class SonarImpl: public Sonar {
 
public: 
  SonarImpl(int trigPin, int echoPin);
  float getDistance();

private:
  int trigPin;
  int echoPin;
};

#endif