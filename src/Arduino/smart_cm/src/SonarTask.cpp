#include "SonarTask.h"

SonarTask::SonarTask(int triger_pin, int echo_pin){
    this->triger_pin = triger_pin;
    this->echo_pin = echo_pin;
}

void SonarTask::init(int period){
    Task::init(period);
    this->sonar = new SonarImpl(this->triger_pin, this->echo_pin);
    this->state = NORM;
}

void SonarTask::tick(){
    distance = this->sonar->getDistance();
    String msg = this->state == NORM?"NORMAL":this->state == PRE_AL?"PRE ALARM":"ALARM";
    msgManager->sendMsg("WATLV:"+msg);
    msgManager->sendMsg("DISTA:"+String(distance));
    switch (this->state)
    {
    case NORM:
         if(distance < this->TWL_pre_alarm && distance >= this->TWL_alarm){
            Task::init(PE_pre_alarm);
            this->state = PRE_AL;
            global_state = STATES::PRE_ALARM;
        }else if(distance < this->TWL_alarm && distance >= 0.0){
            Task::init(PE_alarm);
            this->state = AL;
            global_state = STATES::ALARM;
        }
        break;
    case PRE_AL:
        if( distance >= this->TWL_pre_alarm){
            Task::init(PE_normal);
            this->state = NORM;
            global_state = STATES::NORMAL;
        }else if(distance < this->TWL_alarm && distance >= 0.0){
            Task::init(PE_alarm);
            this->state = AL;
            global_state = STATES::ALARM;
        }
    case AL:
        if(distance >= this->TWL_pre_alarm){
            Task::init(PE_normal);
            this->state = NORM;
            global_state = STATES::NORMAL;
        }else if(distance < this->TWL_pre_alarm && distance >= this->TWL_alarm){
            Task::init(PE_pre_alarm);
            this->state = PRE_AL;
            global_state = STATES::PRE_ALARM;
        }
        break;
    }
}