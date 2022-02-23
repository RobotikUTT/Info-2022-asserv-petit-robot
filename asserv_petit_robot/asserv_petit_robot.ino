#include <PID_v1.h>
#include <Encoder.h>
#include "pins.h"
#include "Wheel.h"
#include "pid_coefs.h"

Wheel wheel(LEFT_WHEEL_ENABLE, LEFT_WHEEL_CONTROL1, LEFT_WHEEL_CONTROL2, ENCODER_LEFT_A, ENCODER_LEFT_B, MOTOR_SPEED_P,
            MOTOR_SPEED_I, MOTOR_SPEED_D, MOTOR_POS_P, MOTOR_POS_I, MOTOR_POS_D);

#include <Arduino.h>

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(10);

    wheel.set_desired_pos(2000);
}

void loop() {
    wheel.update();

    delay(100);
}

