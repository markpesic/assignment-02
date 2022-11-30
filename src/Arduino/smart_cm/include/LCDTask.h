#ifndef __LCD_TASK_H__
#define __LCD_TASK_H__

#include "Task.h"
#include "LCDImpl.h"
#include "globals.h"
class LCDTask : public Task{

    LCDImpl *lcd;

    enum{OFF, WL, WL_AND_ANGLE} state;

public:

    LCDTask();
    void init(int period);
    void tick();

};

#endif