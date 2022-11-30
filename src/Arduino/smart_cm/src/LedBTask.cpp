#include "LedBTask.h"

LedBTask::LedBTask(int led_pin){
    this->led_pin = led_pin;
}

void LedBTask::init(int period){
    Task::init(period);
    this->state = OFF;
    this->led = new Led(this->led_pin);
}

void LedBTask::tick(){
    switch (this->state)
    {
    case OFF:
        if(global_state == NORMAL || global_state == PRE_ALARM){
            this->led->switchOn();
            this->state = ON;
        }
        if(global_state == PRE_ALARM){
            Task::init(PE_pre_alarm);
        }
        if(global_state == NORMAL){
            Task::init(PE_normal);
        }
        break;
    
    case ON:
        if(global_state == ALARM){
            Task::init(PE_alarm);
            this->led->switchOff();
            this->state = OFF;
        }
        break;
    }
}