#include "Robot.h"


Robot::Robot(Wheel p_right_wheel,Wheel p_left_wheel, Encoder p_encoder_right, Encoder p_encoder_left):
  m_right_wheel(p_right_wheel), m_left_wheel(p_left_wheel), m_right_encoder(p_encoder_right), m_left_encoder(p_encoder_left) {
  }

void Robot::move(const int8_t speed) {
  const uint8_t cmd_speed = abs(speed);
  if (speed > 0) {
    m_right_wheel.move_forward(cmd_speed);
    m_left_wheel.move_forward(cmd_speed);
  } else if (speed < 0) {
    m_right_wheel.move_backward(cmd_speed);
    m_left_wheel.move_backward(cmd_speed);
  } else {
    m_right_wheel.stop();
    m_left_wheel.stop();
  }
}

void Robot::stop(){
    m_right_wheel.stop();
    m_left_wheel.stop();
}