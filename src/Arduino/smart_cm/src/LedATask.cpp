#include "LedATask.h"

LedATask::LedATask(int led_pin){
    this->led_pin = led_pin;
}

void LedATask::init(int period){
    Task::init(period);
    this->led = new Led(this->led_pin);
    this->state = OFF;
    this->start_time = 0;
    this->period = period;
}

/* verifies if in t1 seconds someone is detected or not  */
void LedATask::detectedSomeoneAfterT1(){
    if(this->start_time < this->T1){
        if(is_detected){
            this->start_time = 0;
            return;
        }
    }
    else if(this->start_time >= this->T1){
        this->start_time = 0;
    }
    this->start_time += this->period;
}

void LedATask::tick(){
    String msg = this->state == ON?"ON":"OFF";
    msgManager->sendMsg("LIGHT:"+msg);
    if(global_state == ALARM){
        this->state = OFF;
        this->led->switchOff();
    }else{
        switch (this->state)
        {
        case OFF:
            //Serial.println("The LED IS OFF: "+String(is_detected)+" "+String(is_enough_light));
            if(is_detected && !is_enough_light){
                this->state = ON;
                this->led->switchOn();
            }
        break;
        
        case ON:
            //Serial.println("The light is on");
            if(this->start_time >= this->T1 || is_enough_light){
                this->state = OFF;
                this->start_time = 0;
                this->led->switchOff();
            }
            this->detectedSomeoneAfterT1();
        break;
        }
    }
}