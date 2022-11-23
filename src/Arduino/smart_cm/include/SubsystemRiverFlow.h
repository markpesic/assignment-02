#ifndef __SUBSYSTEMRIVERFLOW_H__
#define __SUBSYSTEMRIVERFLOW_H__

#include "Task.h"
#include "Led.h"
#include "SonarImpl.h"
#include "PotentiometerImpl.h"
#include "LCDImpl.h"
#include "ButtonImpl.h"
#include "ServoMotorImpl.h"


class SubsystemRiverFlow : public Task{
    int LB_pin;
    int LC_pin;
    int echo_pin;
    int trig_pin;
    int POT_pin;
    int SDA_pin;
    int SCL_pin;
    int button_pin;
    int servo_pin;

    int period;
    int time_start;

    const float TWL_pre_alarm = 40.0f;
    const float TWL_alarm = 10.0f;
    const float TWL_max = 1.0f;

    const int PE_normal = 1000;
    const int PE_pre_alarm = 500;
    const int PE_alarm = 250;

    Light *led_b;
    Light *led_c;
    Sonar *sonar;
    Potentiometer *pot;
    LCD *lcd;
    Button *button;
    ServoMotor *servo;

    enum{NORMAL, PRE_ALARM, ALARM} state;

    void wait2Seconds();
public:
    SubsystemRiverFlow(int LB_pin, int LC_pin, int echo_pin, int trig_pin, int POT_pin,
    int SDA_pin, int SCL_pin, int button_pin, int servo_pin);
    void init(int period);
    void tick();

};

#endif