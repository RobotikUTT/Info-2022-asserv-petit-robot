#include <PID_v1.h>
#include <Encoder.h>
#include "pins.h"
#include "Wheel.h"
#include "pid_coefs.h"

#include <Arduino.h>
#include "Robot.h"

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(10);
    Robot::setup();
    Robot::set::target_speed(0.2);
}

void loop() {
    Robot::update();
    Serial.println(Robot::get::angle());
    delay(100);
}

