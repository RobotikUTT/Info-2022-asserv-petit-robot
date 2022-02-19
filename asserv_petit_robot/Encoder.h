#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

#define NB_ENCODERS 2
#define TICKS_PER_REVOLUTION 2176.0f

class Encoder {
public:
  Encoder(uint8_t p_interruptA, uint8_t p_interruptB);
  const int64_t get_ticks() const {return m_ticks;}
  const int64_t get_wheel_turns() const {return m_ticks / TICKS_PER_REVOLUTION;}
  void trigger_interruptA(void);
  void trigger_interruptB(void);
  void set_interruptA(void (*f)(void));
  void set_interruptB(void (*f)(void));
  void reinitialize(void);

private:
  uint8_t m_interruptA;
  uint8_t m_interruptB;
  int64_t m_ticks;
};

#endif