#ifndef __GENERALLCD__
#define __GENERALLCD__

#include "LCD.h"
#include <LiquidCrystal_I2C.h>

class GeneralLCD: public LCD {
 
public: 
  GeneralLCD();
  virtual void write(int coord_x, int coord_y, String msg);
  virtual void setUpLCD();
  virtual void turnOffLCD();

private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); 
};

#endif