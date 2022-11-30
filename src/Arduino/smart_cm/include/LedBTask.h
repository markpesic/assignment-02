#ifndef __LEDB_TASK_H__
#define __LEDB_TASK_H__

#include "Task.h"
#include "Led.h"
#include "globals.h"
class LedBTask : public Task{
    int led_pin;

    Light *led;

    enum{ON, OFF} state;

public:

    LedBTask(int led_pin);
    void init(int period);
    void tick();

};

#endif