#include "SubsystemRiverFlow.h"
#include "Arduino.h"

SubsystemRiverFlow::SubsystemRiverFlow(int LB_pin, int LC_pin, int echo_pin, int trig_pin, int POT_pin,
    int SDA_pin, int SCL_pin, int button_pin, int servo_pin){
        this->LB_pin = LB_pin;
        this->LC_pin = LC_pin;
        this->echo_pin = echo_pin;
        this->trig_pin = trig_pin;
        this->SDA_pin = SDA_pin;
        this->SCL_pin = SCL_pin;
        this->button_pin = button_pin;
        this->servo_pin = servo_pin;
        this->time_start = 0;
    }

void SubsystemRiverFlow::init(int period){
    Task::init(period);
    this->led_b = new Led(this->LB_pin);
    this->led_c = new Led(this->LC_pin);
    this->sonar = new SonarImpl(this->trig_pin, this->echo_pin);
    this->lcd = new LCDImpl();
    this->button = new ButtonImpl(this->button_pin);
    this->servo = new ServoMotorImpl(this->servo_pin);
    this->state = NORMAL;
    this->period = period;
    this->led_b->switchOn();
    this->lcd->normal_display();
}

void SubsystemRiverFlow::wait2Seconds(){
    if(this->time_start >= 2000){
        this->led_c->switchOn();
        this->led_c->switchOff();
        this->time_start = 0;
    }
    this->time_start += period;
}

void SubsystemRiverFlow::tick(){
    float distance = this->sonar->getDistance();
    Serial.println("Distance: "+String(distance));
    switch (this->state)
    {
    case NORMAL:
        if(distance < this->TWL_pre_alarm && distance >= this->TWL_alarm){
            this->state = PRE_ALARM;
            this->led_c->switchOn();
            this->led_c->switchOff();
            this->time_start = 0;
            this->lcd->pre_alarm_display((int)distance);
            Task::init(this->PE_pre_alarm);
        }else if(distance < this->TWL_alarm && distance >= 0.0){
            this->state = this->ALARM;
            Task::init(this->PE_alarm);
        }
        break;
    case PRE_ALARM:
        this->wait2Seconds();
        if( distance >= this->TWL_pre_alarm){
            this->state = NORMAL;
            this->time_start = 0;
            this->led_b->switchOn();
            this->led_c->switchOff();
            this->lcd->normal_display();
            Task::init(this->PE_normal);
        }else if(distance < this->TWL_alarm && distance >= 0.0){
            Task::init(this->PE_alarm);
        }
        break;
    case ALARM:
    break;
    default:
        break;
    }
}