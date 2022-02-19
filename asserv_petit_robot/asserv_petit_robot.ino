#include "Wheel.h"
#include "Encoder.h"
#include "Robot.h"
#include "pins.h"


Wheel right_wheel(enablePin2, controlPin3, controlPin4);
Wheel left_wheel(enablePin1, controlPin1, controlPin2);
Encoder right_encoder(encoderRightA, encoderRightB);
Encoder left_encoder(encoderLeftA, encoderLeftB);
Robot petit_robot(right_wheel, left_wheel, right_encoder, left_encoder);

void setup() {
  left_wheel.set_speed(100);
  right_wheel.set_speed(100);
  Serial.begin(9600);
    left_wheel.move_forward();
    right_wheel.move_forward();
}

void loop() {
  if (right_encoder.get_wheel_turns() >= 10) {
    left_wheel.stop();
    right_wheel.stop();
  } else {
    Serial.print("R : ");
    Serial.print((int) right_encoder.get_ticks());
    Serial.print(" ; L : ");
    Serial.println((int) left_encoder.get_ticks());
  }
}

