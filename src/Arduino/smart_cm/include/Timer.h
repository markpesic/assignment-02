#ifndef TIMER_H
#define TIMER_H

#include<TimerOne.h>

class Timer{
    public:
    Timer();
    void setupInitialFreq(int period);
    void setupPeriod(int period);
    void waitForNextTick();
};

#endif