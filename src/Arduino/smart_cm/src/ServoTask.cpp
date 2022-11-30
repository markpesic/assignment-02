#include "MotorTask.h"

MotorTask::MotorTask(int servo_pin){
    this->servo_pin = servo_pin;
}

void MotorTask::init(int period){
    Task::init(period);
    this->servo = new ServoMotorImpl(this->servo_pin);
    this->servo->on();
    this->state = OFF;
}

void MotorTask::tick(){
    switch (this->state)
    {
    case ON:
        this->servo->setPosition(alpha);
        if(global_state == PRE_ALARM || global_state == NORMAL){
            this->state = OFF;
            this->servo->setPosition(180);
        }
        break;
    case OFF:
        if(global_state == ALARM){
            this->state = ON;
            this->servo->setPosition(alpha);
        }
    default:
        break;
    }
}
