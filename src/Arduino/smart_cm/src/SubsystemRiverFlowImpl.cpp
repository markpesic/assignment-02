#include "SubsystemRiverFlow.h"
#include "Arduino.h"
#include "globals.h"
#include <math.h>


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
    is_alarm_state = false;
    alpha = 0;
}

void SubsystemRiverFlow::wait2Seconds(){
    if(this->time_start <= 1000){
        this->led_c->switchOn();
    }
    if(this->time_start >= 2000){
        this->led_c->switchOff();
        this->time_start = 0;
    }
    this->time_start += period;
}

long SubsystemRiverFlow::getAngle(float distance){
    float dist = distance;
    if(distance <= this->TWL_max){
        dist = this->TWL_alarm;
    }else if(distance > this->TWL_alarm){
        dist = this->TWL_alarm;
    }
    return map(round(dist), round(this->TWL_max), round(this->TWL_alarm), 0, 180);
    
}

void SubsystemRiverFlow::setNormal(){
    is_alarm_state = false;
    this->state = NORMAL;
    this->time_start = 0;
    this->led_b->switchOn();
    this->led_c->switchOff();
    this->lcd->normal_display();
    disable_light_system = false;
    this->servo->off();
    Task::init(this->PE_normal);
}

void SubsystemRiverFlow::setPreAlarm(float distance){
    is_alarm_state = false;
    this->state = PRE_ALARM;
    this->time_start = 0;
    this->lcd->pre_alarm_display((int)distance);
    disable_light_system = false;
    this->servo->off();
    Task::init(this->PE_pre_alarm);
}

void SubsystemRiverFlow::setAlarm(float distance){
    is_alarm_state = true;
    this->state = this->ALARM;
    Task::init(this->PE_alarm);
    this->led_b->switchOff();
    this->led_c->switchOn();
    disable_light_system = true;
    alpha = getAngle(distance);
    this->lcd->alarm_display((int)distance,(int) alpha);
    this->servo->on();
    this->servo->setPosition(alpha);
}

void SubsystemRiverFlow::tick(){
    float distance = this->sonar->getDistance();
    //Serial.println("Distance: "+String(distance));
    String msg = this->state == NORMAL?"NORMAL":this->state == PRE_ALARM?"PRE ALARM":"ALARM";
    msgManager->sendMsg("WATLV:"+msg);
    msgManager->sendMsg("DISTA:"+String(distance));
    switch (this->state)
    {
    case NORMAL:
        if(distance < this->TWL_pre_alarm && distance >= this->TWL_alarm){
            this->setPreAlarm(distance);
        }else if(distance < this->TWL_alarm && distance >= 0.0){
            this->setAlarm(distance);
        }
        break;
    case PRE_ALARM:
        this->lcd->pre_alarm_display(distance);
        this->wait2Seconds();
        if( distance >= this->TWL_pre_alarm){
            this->setNormal();
        }else if(distance < this->TWL_alarm && distance >= 0.0){
            this->setAlarm(distance);

        }
        break;
    case ALARM:
        if(!manual_control){
            alpha = getAngle(distance);
            this->servo->setPosition(alpha);
            //Serial.println("AUTOMATIC SERVO MOTOR");
        }
        this->lcd->alarm_display((int)round(distance), alpha);
        if(distance >= this->TWL_pre_alarm){
            this->servo->setPosition(180);
            this->setNormal();
        }else if(distance < this->TWL_pre_alarm && distance >= this->TWL_alarm){
            this->servo->setPosition(180);
            this->setPreAlarm(distance);
        }
        break;
    }
}