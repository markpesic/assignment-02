#ifndef __SONAR_TASK_H__
#define __SONAR_TASK_H__

#include "Task.h"
#include "SonarImpl.h"
#include "globals.h"
class SonarTask : public Task{
    int triger_pin;
    int echo_pin;

    Sonar *sonar;
    
    const float TWL_pre_alarm = 40.0f;
    const float TWL_alarm = 10.0f;
    const float TWL_max = 4.0f;

    enum{NORM, AL, PRE_AL} state;

public:

    SonarTask(int trig_pin, int echo_pin);
    void init(int period);
    void tick();

};

#endif