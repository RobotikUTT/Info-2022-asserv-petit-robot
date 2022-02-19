#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>

#include "Wheel.h"
#include "Encoder.h"
#include "pins.h"
#include "interrupts.h"

void right_interruptA(void);
void right_interruptB(void);
void left_interruptA(void);
void left_interruptB(void);


class Robot {
public:
  virtual ~Robot() = default;
  Robot();
  Robot(Wheel p_right_wheel, Wheel p_left_wheel, Encoder p_encoder_right, Encoder p_encoder_left);

private:
  Wheel m_right_wheel;
  Wheel m_left_wheel;
  Encoder m_right_encoder;
  Encoder m_left_encoder;
};

#endif