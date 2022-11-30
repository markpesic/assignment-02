#ifndef __LEDA_TASK_H__
#define __LEDA_TASK_H__

#include "Task.h"
#include "Led.h"
#include "globals.h"
class LedATask : public Task{
    int led_pin;

    const int T1 = 1000;

    int start_time;
    int period;

    Light *led;

    enum{ON, OFF} state;

    void detectedSomeoneAfterT1();

public:

    LedATask(int led_pin);
    void init(int period);
    void tick();

};

#endif