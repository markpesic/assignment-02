#include <Arduino.h>
#include "Scheduler.h"
//#include "SubsystemRiverFlow.h"
//#include "manualControlTask.h"
#include "MsgService.h"
#include "globals.h"
#include "PirTask.h"
#include "LightSensorTask.h"
#include "LedATask.h"
#include "LCDTask.h"
#include "LedBTask.h"
#include "LedCTask.h"
#include "ControlTask.h"
#include "MotorTask.h"
#include "SonarTask.h"

#define LED_A 13
#define LED_B 12
#define LED_C 11
#define POT_PIN A1
#define TRIG_PIN 10
#define ECHO_PIN 9
#define BUTTON_PIN 8
#define SERVO_PIN 4
#define PIR_PIN 2
#define LS_PIN A0
#define SDA A4 
#define SCL A5

bool disable_light_system = false;
bool manual_control = false;
int alpha = 0;
bool is_alarm_state = false;
bool is_enough_light = false;
bool is_detected = false;
enum STATES global_state = NORMAL;
int PE_normal = 1000;
int PE_pre_alarm = 500;
int PE_alarm = 50;
float distance = 100.0f;
Scheduler sched;
MsgServiceClass *msgManager = new MsgServiceClass();

//Button *btn;

void setup() {
    msgManager->init();
    Timer1.initialize(100);
    sched.init(250);


    Task *t0 = new PirTask(PIR_PIN);
    t0->init(500);
    sched.addTask(t0);

    Task *t1 = new LightSensorTask(LS_PIN);
    t1->init(500);
    sched.addTask(t1);

    Task *t2 = new LedATask(LED_A);
    t2->init(500);
    sched.addTask(t2);

    Task *t7 = new SonarTask(TRIG_PIN, ECHO_PIN);
    t7->init(PE_normal);
    sched.addTask(t7);

    Task *t3 = new LedBTask(LED_B);
    t3->init(PE_normal);
    sched.addTask(t3);

    Task *t4 = new LedCTask(LED_C);
    t4->init(PE_normal);
    sched.addTask(t4);

    Task *t6 = new ControlTask(BUTTON_PIN, POT_PIN);
    t6->init(PE_alarm);
    sched.addTask(t6);

    Task *t5 = new LCDTask();
    t5->init(PE_normal);
    sched.addTask(t5);

    Task *t8 = new MotorTask(SERVO_PIN);
    t8->init(PE_alarm);
    sched.addTask(t8);
}

void loop() {
    sched.schedule();
    //Serial.println(btn->isPressed());
}