#include "LCDImpl.h"
#include "Arduino.h"

LCDImpl::LCDImpl(){};

void LCDImpl::pre_alarm_display(int waterLevel){
  this->lcd->setUpLCD();
  lcd->write(0, 0, String("Water Level = ") + String(waterLevel));
  lcd->write(0, 1, "PRE ALARM STATE");
}

void LCDImpl::alarm_display(int waterLevel, int valveDegrees){
  lcd->setUpLCD();
  lcd->write(0, 0, String("Water Level=") + String(waterLevel));
  lcd->write(0, 1, String("Valve Deg. = ") + String(valveDegrees));
  lcd->write(1, 2, String("ALARM STATE"));
}

void LCDImpl::normal_display(){
    lcd->turnOffLCD();
}