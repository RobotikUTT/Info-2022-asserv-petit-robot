#include "Robot.h"

namespace Robot {
  namespace {
    Wheel right_wheel(RightWheelEnable, RightWheelControl1, RightWheelControl2);
    Wheel left_wheel(LeftWheelEnable, LeftWheelControl1, LeftWheelControl2);
    Encoder right_encoder(encoderRightA, encoderRightB);
    Encoder left_encoder(encoderLeftA, encoderLeftB);
    position_t position = {0.0, 0.0, 0.0};
    position_t objectif = {0.0, 0.0, 0.0};

    void update_position(const int l_ticks, const int r_ticks) {
      const double mean = (l_ticks + r_ticks) / 2.0;
      position.x += mean * cos(position.angle);
      position.y += mean * sin(position.angle);
    }
  }
  
  void move(const int8_t p_speed) {
    const uint8_t cmd_speed = abs(p_speed);
    if (p_speed > 0) {
      right_wheel.move_forward(cmd_speed);
      left_wheel.move_forward(cmd_speed);
    } else if (p_speed < 0) {
      right_wheel.move_backward(cmd_speed);
      left_wheel.move_backward(cmd_speed);
    } else {
      right_wheel.stop();
      left_wheel.stop();
    }
  }
  
  void set_new_objective(const int8_t trans_x, const int8_t trans_y) {
    objectif.x = position.x + trans_x;
  }

  void stop(){
      right_wheel.stop();
      left_wheel.stop();
  }

  void asservissement() {
    const int r_ticks = right_encoder.read();
    const int l_ticks = left_encoder.read();
    update_position(l_ticks, r_ticks);
    right_encoder.write(0);
    left_encoder.write(0);
    if (abs(objectif.x - position.x) > NEGLIGIBLE_ERROR) {
      if (objectif.x < position.x) {
        move(100);
      } else {
        move(-100);
      }
    } else {
      stop();
    }
  }
  
  void display_position() {
    Serial.print("position : ");
    Serial.print(position.x);
    Serial.println(position.y);
    Serial.print("objectif : ");
    Serial.print(objectif.x);
    Serial.println(objectif.y);
  }
};


