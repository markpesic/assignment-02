#ifndef __LEDC_TASK_H__
#define __LEDC_TASK_H__

#include "Task.h"
#include "Led.h"
#include "globals.h"
class LedCTask : public Task{
    int led_pin;

    const int T1 = 1000;

    int start_time;
    int period;

    Light *led;

    enum{ON, OFF, BLINK} state;

    void wait2Seconds();

public:

    LedCTask(int led_pin);
    void init(int period);
    void tick();

};

#endif