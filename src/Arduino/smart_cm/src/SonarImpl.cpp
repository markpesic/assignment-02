#include "SonarImpl.h"
#include "Arduino.h"

const float vs = 331.45 + 0.62*20;

SonarImpl::SonarImpl(int trigPin, int echoPin){
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
} 
  
float SonarImpl::getDistance(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin,HIGH);  
  delayMicroseconds(5);
  digitalWrite(trigPin,LOW);
  
  /* ricevi l’eco */
  float tUS = pulseIn(echoPin, HIGH);
  float t = tUS / 1000.0 / 1000.0 / 2;
  float d = t*vs;
  return d;
}
