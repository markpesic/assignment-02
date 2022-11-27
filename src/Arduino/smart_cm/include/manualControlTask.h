#ifndef __MANUAL_CONTROL_H__
#define __MANUAL_CONTROL_H__

#include "Task.h"
#include "ButtonImpl.h"
#include "PotentiometerImpl.h"
#include "ServoMotorImpl.h"

class ManualControlTask : public Task{
    int button_pin;
    int pot_pin;
    int servo_pin;

    bool btnPressed;

    Button *btn;
    Potentiometer *pot;
    ServoMotor *servo;

    enum{MANUAL, AUTOMATIC} state;

public:

    ManualControlTask(int button_pin,int pot_pin,int servo_pin);
    void init(int period);
    void tick();

};

#endif
