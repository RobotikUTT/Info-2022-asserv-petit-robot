//#define DEBUG

#include <PID_v1.h>
#include <Encoder.h>
#include "pins.h"
#include "Wheel.h"
#include "pid_coefs.h"

#include <Arduino.h>
#include "Robot.h"

void setup() {
#ifdef DEBUG
    Serial.begin(9600);
    Serial.setTimeout(10);
#endif
    Robot::setup();
//    Robot::set::target_speed(0);
}

void loop() {
    Robot::update();
#ifdef DEBUG
    Serial.println(Robot::get::angle());
#endif
}

