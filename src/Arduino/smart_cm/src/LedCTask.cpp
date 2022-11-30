#include "LedCTask.h"

LedCTask::LedCTask(int led_pin){
    this->led_pin = led_pin;
}

void LedCTask::init(int period){
    Task::init(period);
    this->state = OFF;
    this->period = period;
    this->led = new Led(this->led_pin);
}

void LedCTask::wait2Seconds(){
    if(this->start_time <= 1000){
        this->led->switchOn();
    }
    if(this->start_time >= 2000){
        this->led->switchOff();
        this->start_time = 0;
    }
    this->start_time += this->period;
}

void LedCTask::tick(){
    switch (this->state)
    {
    case OFF:
        if(global_state == ALARM){
            Task::init(PE_alarm);
            this->state = ON;
            this->led->switchOn();
        }else if(global_state == PRE_ALARM){
            Task::init(PE_pre_alarm);
            this->state = BLINK;
            this->start_time = 0;
        }
    case ON:
        if(global_state == NORMAL){
            Task::init(PE_normal);
            this->state = OFF;
            this->led->switchOff();
        }else if(global_state == PRE_ALARM){
            Task::init(PE_pre_alarm);
            this->state = BLINK;
            this->start_time = 0;
        }
        break;
    case BLINK:
        this->wait2Seconds();
        if(global_state == ALARM){
            Task::init(PE_alarm);
            this->state = ON;
            this->led->switchOn();
        }else if(global_state == NORMAL){
            Task::init(NORMAL);
            this->state = OFF;
            this->led->switchOff();
        }
        break;
    
    }
}