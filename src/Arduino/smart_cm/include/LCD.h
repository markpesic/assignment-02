#ifndef __LCD__
#define __LCD__

class LCD {
 
public: 
  virtual void pre_alarm_display(int waterLevel);
  virtual void alarm_display(int waterLevel, int valveDegrees);
  virtual void normal_display();
};

#endif