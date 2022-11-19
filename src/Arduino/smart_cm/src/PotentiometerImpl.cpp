#include "PotentiometerImpl.h"
#include "Arduino.h"

PotentiometerImpl::PotentiometerImpl(int pin){
  this->pin = pin;
} 
  
int PotentiometerImpl::getValue(){
  int newValue = analogRead(pin);
  if (newValue != current){
    current = newValue;
  }
  return current;
}
