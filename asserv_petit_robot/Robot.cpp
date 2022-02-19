#include "Robot.h"

namespace Robot {
  namespace {
    Wheel m_right_wheel(RightWheelEnable, RightWheelControl1, RightWheelControl2);
    Wheel m_left_wheel(LeftWheelEnable, LeftWheelControl1, LeftWheelControl2);
    Encoder m_right_encoder(encoderRightA, encoderRightB);
    Encoder m_left_encoder(encoderLeftA, encoderLeftB);
  }
  
  void move(const int8_t p_speed) {
    const uint8_t cmd_speed = abs(p_speed);
    if (p_speed > 0) {
      m_right_wheel.move_forward(cmd_speed);
      m_left_wheel.move_forward(cmd_speed);
    } else if (p_speed < 0) {
      m_right_wheel.move_backward(cmd_speed);
      m_left_wheel.move_backward(cmd_speed);
    } else {
      m_right_wheel.stop();
      m_left_wheel.stop();
    }
  }
  void stop(){
      m_right_wheel.stop();
      m_left_wheel.stop();
  }
};


