#ifndef __SUBSYSTEM_LIGHT_H__
#define __SUBSYSTEM_LIGHT_H__

#include "Task.h"
#include "Led.h"
#include "PirImpl.h"
#include "LightSensorImpl.h"

class SubSystemLight : public Task{
    int LA_pin;
    int LS_pin;
    int PIR_pin;

    int period;
    int time_start;
    bool detected;

    const int THls = 100;
    const int t1 = 1000;//1s in ms

    Light *led;
    Pir *pir;
    LightSensor *ls;

    enum{ ON , OFF} state;

    void detectSomeoneAfterT1();

public:
    SubSystemLight(int LA_pin, int LS_pin, int PIR_pin);
    void init(int period);
    void tick();
};

#endif