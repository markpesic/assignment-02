#include <Arduino.h>
#include "Scheduler.h"
#include "SubsystemLight.h"

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

Scheduler sched;

void setup() {
    Serial.begin(9600);
    Timer1.initialize(10000000);
    sched.init(250000);

    Task *t0 = new SubSystemLight(LED_A, LS_PIN, PIR_PIN);
    t0->init(500000);
    sched.addTask(t0);
}

void loop() {
    sched.schedule();
}