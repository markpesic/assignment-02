#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "Task.h"
#include "globals.h"
#include "ButtonImpl.h"
#include "PotentiometerImpl.h"

class ControlTask : public Task{
    int button_pin;
    int pot_pin;

    bool btnPressed;

    Button *btn;
    Potentiometer *pot;

    long getAngle(float distance);

    enum{MANUAL, AUTOMATIC} state;

public:

    ControlTask(int button_pin,int pot_pin);
    void init(int period);
    void tick();

};

#endif