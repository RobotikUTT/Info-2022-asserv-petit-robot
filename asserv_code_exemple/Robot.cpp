#include "Robot.h"


Robot::Robot(Wheel p_right_wheel,Wheel p_left_wheel, Encoder p_encoder_right, Encoder p_encoder_left):
  m_right_wheel(p_right_wheel), m_left_wheel(p_left_wheel), m_right_encoder(p_encoder_right), m_left_encoder(p_encoder_left) {
  }

Robot::Robot(): m_right_wheel(enablePin2, controlPin3, controlPin4),
                m_left_wheel(enablePin1, controlPin1, controlPin2),
                m_right_encoder(encoderRightA, encoderRightB),
                m_left_encoder(encoderLeftA, encoderLeftB) {}