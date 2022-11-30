#include "manualControlTask.h"
#include "globals.h"
#include "Arduino.h"


ManualControlTask::ManualControlTask(int button_pin,int pot_pin,int servo_pin){
    this->button_pin = button_pin;
    this->pot_pin = pot_pin;
    this->servo_pin = servo_pin;
}

void ManualControlTask::init(int period){
    Task::init(period);
    this->btn = new ButtonImpl(this->button_pin);
    this->pot = new PotentiometerImpl(this->pot_pin);
    this->servo = new ServoMotorImpl(this->servo_pin);
    this->state = AUTOMATIC;
    this->btnPressed = false;
}

void ManualControlTask::tick(){
    switch(this->state){
        case AUTOMATIC:
        //Serial.println("is_alaram_state: "+String(is_alarm_state));
        //Serial.println(this->btn->isPressed());
            if(is_alarm_state && this->btn->isPressed()){
                //Serial.println("AUTOMATIC MANAGMENT");
                this->state = MANUAL;
                manual_control = true;
            }
        break;
        case MANUAL:
            if(this->btn->isPressed() || !is_alarm_state){
                this->state = AUTOMATIC;
                manual_control = false;
            }else{
                Serial.println("Pot Value: "+String(this->pot->getValue()));
                alpha = map(this->pot->getValue(), 0, 1023, 0, 180);
                this->servo->setPosition(alpha);
            }
        break;
    }
}