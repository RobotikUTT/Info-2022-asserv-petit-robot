#ifndef INTERRUPTS_H
#define INTERRUPTS_H


void right_interruptA(void) {
  right_encoder.trigger_interruptA();
}
void right_interruptB(void) {
  right_encoder.trigger_interruptB();
}
void left_interruptA(void) {
  left_encoder.trigger_interruptA();
}
void left_interruptB(void) {
  left_encoder.trigger_interruptB();
}

#endif