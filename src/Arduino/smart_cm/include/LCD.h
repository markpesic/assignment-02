#ifndef __LCD__
#define __LCD__
#include"Arduino.h"

class LCD {
 
public: 
  virtual void write(int coord_x, int coord_y, String msg);
  virtual void setUpLCD();
  virtual void turnOffLCD();
};

#endif