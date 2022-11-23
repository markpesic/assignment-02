#include "LCDImpl.h"
#include "Arduino.h"

LCDImpl::LCDImpl(){
  lcd.init();
  lcd.backlight();
}

void LCDImpl::pre_alarm_display(int waterLevel){
  lcd.clear();
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print(String("Water Level = ") + waterLevel);
  lcd.setCursor(0, 1);
  lcd.print("PRE ALARM STATE");
}

void LCDImpl::alarm_display(int waterLevel, int valveDegrees){
  lcd.clear();
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print(String("Water Level=") + waterLevel);
  lcd.setCursor(0,1);
  lcd.print(String("Valve Deg. = ") + valveDegrees);
  lcd.setCursor(1, 2);
  lcd.print("ALARM STATE");
}

void LCDImpl::normal_display(){
  lcd.noDisplay();
}