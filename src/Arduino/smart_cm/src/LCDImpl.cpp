#include "LCDImpl.h"
#include "Arduino.h"

LCDImpl::LCDImpl(){
  lcd.init();
  lcd.backlight();
}

void LCDImpl::pre_alarm_display(int waterLevel){
  lcd.display();
  lcd.setCursor(0, 1);
  lcd.print("PRE ALARM STATE");
  lcd.setCursor(0,2);
  lcd.print(String("Water Level = ") + waterLevel);
}

void LCDImpl::alarm_display(int waterLevel, int valveDegrees){
  lcd.setCursor(0, 1);
  lcd.print("ALARM STATE");
  lcd.setCursor(0,2);
  lcd.print(String("Water Level = ") + waterLevel);
  lcd.setCursor(0,3);
  lcd.print(String("Valve Degrees = ") + valveDegrees);
}

void LCDImpl::normal_display(){
  lcd.noDisplay();
}