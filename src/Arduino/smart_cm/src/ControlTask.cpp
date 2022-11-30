#include "ControlTask.h"
#include <math.h>

ControlTask::ControlTask(int button_pin, int pot_pin){
    this->button_pin = button_pin;
    this->pot_pin = pot_pin;
}

void ControlTask::init(int period){
    Task::init(period);
    this->state = AUTOMATIC;
    this->pot = new PotentiometerImpl(this->pot_pin);
    this->btn = new ButtonImpl(this->button_pin);
}

long ControlTask::getAngle(float distance){
    float dist = distance;
    if(distance <= 1.0f){
        dist = 1.0f;
    }else if(distance > 10.0f){
        dist = 10.0f;
    }
    return map(round(dist), round(1.0f), round(10.0f), 0, 180);
    
}


void ControlTask::tick(){
    switch (this->state)
    {
    case AUTOMATIC:
        alpha = getAngle(distance);
        //Serial.println("AUTOMATIC: "+String(alpha));
        if(this->btn->isPressed() && global_state == ALARM){
            this->state = MANUAL;
            alpha = map(this->pot->getValue(), 0, 1023, 0, 180);
        }
        break;
    
    case MANUAL:
        alpha = map(this->pot->getValue(), 0, 1023, 0, 180);
        //Serial.println("MANUAL CONTROL: "+String(alpha));
        if(this->btn->isPressed() || global_state != ALARM){
            this->state = AUTOMATIC;
            alpha = getAngle(distance);
        }
        break;
    }
}