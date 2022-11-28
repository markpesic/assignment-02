#include "SubsystemLight.h"
#include "Arduino.h"
#include "globals.h"

SubSystemLight::SubSystemLight(int LA_pin, int LS_pin, int PIR_pin){
    this->LA_pin = LA_pin;
    this->LS_pin = LS_pin;
    this->PIR_pin = PIR_pin;
    this->time_start = 0;
}

void SubSystemLight::init(int period){
    Task::init(period);
    this->led = new Led(this->LA_pin);
    this->pir = new PirImpl(this->PIR_pin);
    this->ls = new LightSensorImpl(this->LS_pin);
    this->state = OFF;
    this->period = period;
}

/* verifies if in t1 seconds someone is detected if not  */
void SubSystemLight::detectSomeoneAfterT1(){
    if(this->time_start < this->t1){
        bool detected = this->pir->isDetected();
        if(detected){
            this->time_start = 0;
            return;
        }
    }
    else if(this->time_start >= this->t1){
        this->time_start = 0;
    }
    this->time_start += this->period;
}

void SubSystemLight::tick(){
    String msg = this->state == ON?"ON":"OFF";
    msgManager->sendMsg("LIGHT:"+msg);
    if(disable_light_system){
        this->led->switchOff();
        this->state = OFF;
    }else{
        switch (this->state)
        {
        case OFF:
            //Serial.println(String(this->pir->isDetected())+" "+String(this->ls->getLightIntensity()) );
            if(this->pir->isDetected() && this->ls->getLightIntensity() < this->THls){
                this->led->switchOn();
                this->time_start = 0;
                state = ON;
            }
            break;
        case ON:
            //Serial.println("The time passed is: "+String(this->time_start)+" The led is on with intensity: "+String(this->ls->getLightIntensity()) );
            if(this->time_start >= this->t1 || this->ls->getLightIntensity() >= this->THls){
                this->led->switchOff();
                state = OFF;
            }
            this->detectSomeoneAfterT1();
            break;
        }
    }
}