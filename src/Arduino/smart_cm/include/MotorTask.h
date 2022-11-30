#ifndef __MOTOR_TASK_H__
#define __MOTOR_TASK_H__

#include "Task.h"
#include "ServoMotorImpl.h"
#include "globals.h"
class MotorTask : public Task{
    int servo_pin;

    ServoMotor *servo;

    enum{ON, OFF} state;

public:

    MotorTask(int servo_pin);
    void init(int period);
    void tick();

};

#endif