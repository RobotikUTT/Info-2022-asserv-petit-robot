#include "Robot.h"
#include "pins.h"
#include <PID_v1.h>
#include <Encoder.h>
#include <Arduino.h>
#include "Action.h"
#include "ActionQueue.h"
void setup() {
    ActionList liste;
    Action a;
    liste.add(&a);
    liste += &a;
    Serial.begin(9600);
    Serial.setTimeout(10);
}

void loop() {
    Robot::compute_pid();
}

