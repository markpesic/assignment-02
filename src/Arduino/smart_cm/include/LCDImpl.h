#ifndef __LCDIMPL__
#define __LCDIMPL__

#include "LCD.h"
#include <LiquidCrystal_I2C.h>

class LCDImpl: public LCD {
 
public: 
  LCDImpl();
  void pre_alarm_display(int waterLevel);
  void alarm_display(int waterLevel, int valveDegrees);
  void normal_display();

private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); 
};

#endif