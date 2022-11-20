#include "Timer.h"
#include "Arduino.h"

volatile bool flag;

void isr(void){
    flag = true;
}

Timer::Timer(){
    flag = false;
}

void Timer::setupInitialFreq(int period){
    Timer1.initialize(period);
}

void Timer::setupPeriod(int period){
    Timer1.setPeriod(period);
    Timer1.attachInterrupt(isr);
}

void Timer::waitForNextTick(){
    bool flagLoop = false;
    while(!flagLoop){
        noInterrupts();
        flagLoop = flag;
        interrupts();
    }
    noInterrupts();
    flag = false;
    interrupts();
}