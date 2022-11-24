#include "GeneralLCD.h"

GeneralLCD::GeneralLCD(){
  lcd.init();
  lcd.backlight();
}

void GeneralLCD::write(int coord_x, int coord_y, String msg){
  lcd.setCursor(coord_x, coord_y);
  lcd.print(msg);
}

void GeneralLCD::setUpLCD(){
  lcd.clear();
  lcd.display();
}

void GeneralLCD::turnOffLCD(){
  lcd.noDisplay();
}