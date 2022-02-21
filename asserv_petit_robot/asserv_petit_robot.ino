#include "Robot.h"
#include "pins.h"
#include <PID_v1.h>
#include <Encoder.h>
#include <Arduino.h>

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(10);
}

void loop() {
    Robot::display_position();
}

