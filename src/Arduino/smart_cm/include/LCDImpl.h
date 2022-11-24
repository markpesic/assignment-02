#ifndef __LCDIMPL__
#define __LCDIMPL__

#include "GeneralLCD.h"
#include <LiquidCrystal_I2C.h>

class LCDImpl {
 
public: 
  LCDImpl();
  virtual void pre_alarm_display(int waterLevel);
  virtual void alarm_display(int waterLevel, int valveDegrees);
  virtual void normal_display();

private:
    GeneralLCD *lcd =  new GeneralLCD();
};

#endif