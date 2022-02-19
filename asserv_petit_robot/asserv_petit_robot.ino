#include "Robot.h"
#include "pins.h"

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(10);
}

void loop() {
  Robot::asservissement();
  Robot::display_position();
}

