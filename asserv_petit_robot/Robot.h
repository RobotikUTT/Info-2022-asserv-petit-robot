#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include <Encoder.h>
#include "Wheel.h"
#include "pins.h"
#include "interrupts.h"



namespace Robot {
  void initialize();
  void move(const int8_t p_speed);
  void stop();
  
  namespace {

    void right_interruptA(void);
    void right_interruptB(void);
    void left_interruptA(void);
    void left_interruptB(void);
  }
};

#endif