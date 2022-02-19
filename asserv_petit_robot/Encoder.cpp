#include "Encoder.h"

Encoder::Encoder(uint8_t p_interruptA,
                 uint8_t p_interruptB)
  : m_interruptA(p_interruptA),
    m_interruptB(p_interruptB) {
  pinMode(m_interruptA, INPUT);
  pinMode(m_interruptB, INPUT);
}

void Encoder::trigger_interruptB(void) {
    if (digitalRead(m_interruptA) == digitalRead(m_interruptB))
      m_ticks++;
    else
      m_ticks--;
}

void Encoder::trigger_interruptA(void) {
    if (digitalRead(m_interruptA) == digitalRead(m_interruptB))
      m_ticks--;
    else
      m_ticks++;
}

void Encoder::set_interruptA(void (*f)(void)) {
  attachInterrupt(digitalPinToInterrupt(m_interruptA), f, CHANGE);
}

void Encoder::set_interruptB(void (*f)(void)) {
  attachInterrupt(digitalPinToInterrupt(m_interruptB), f, CHANGE);
}

void Encoder::reinitialize(void) {
  m_ticks = 0;
}
