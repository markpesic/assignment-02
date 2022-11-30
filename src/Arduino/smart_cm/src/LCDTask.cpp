#include "LCDTask.h"

LCDTask::LCDTask(){}

void LCDTask::init(int period){
    Task::init(period);
    this->lcd = new LCDImpl();
    this->state = OFF;
}

void LCDTask::tick(){
    switch (this->state)
    {
    case OFF:
        if(global_state == PRE_ALARM){
            Task::init(PE_pre_alarm);
            this->state = WL;
            this->lcd->pre_alarm_display(max((100.0f-distance),0.0f));//float to int
        }else if(global_state == ALARM){
            Task::init(PE_alarm);
            this->state = WL_AND_ANGLE;
            this->lcd->alarm_display(max((100.0f-distance),0.0f), alpha);//float to int
        }
        break;
    case WL:
        this->lcd->pre_alarm_display(max((100.0f-distance),0.0f));
        if(global_state == NORMAL){
            Task::init(PE_normal);
            this->state = OFF;
            this->lcd->normal_display();
        }else if(global_state == ALARM){
            Task::init(PE_alarm);
            this->state = WL_AND_ANGLE;
            this->lcd->alarm_display(max((100.0f-distance),0.0f), alpha);//float to int
        }
        break;
    
    case WL_AND_ANGLE:
        this->lcd->alarm_display(max((100.0f-distance),0.0f), alpha);
        if(global_state == NORMAL){
            Task::init(PE_normal);
            this->state = OFF;
            this->lcd->normal_display();
        }else if(global_state == PRE_ALARM){
            Task::init(PE_pre_alarm);
            this->state = WL;
            this->lcd->pre_alarm_display(max((100.0f-distance),0.0f));//float to int
        }
        break;
    }
}