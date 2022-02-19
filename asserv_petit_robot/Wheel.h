#ifndef WHEEL_H
#define WHEEL_H

#include <Arduino.h>

#define FORWARD 1
#define BACKWARD -1
#define STOPPED 0

#define MAX_SPEED 255
#define MIN_SPEED 100

class Wheel {
  public:
    Wheel(uint8_t p_enable_pin, uint8_t p_control_pin1, uint8_t p_control_pin2) :
            m_enable_pin(p_enable_pin), m_control_pin{p_control_pin1, p_control_pin2}, m_speed(MAX_SPEED) {
        pinMode(m_enable_pin, OUTPUT);
        pinMode(m_control_pin[0], OUTPUT);
        pinMode(m_control_pin[1], OUTPUT);
        digitalWrite(m_enable_pin, LOW);
    }

    virtual ~Wheel() = default;

    void move_forward() {
        m_direction = FORWARD;
        analogWrite(m_enable_pin, m_speed);
        digitalWrite(m_control_pin[0], HIGH);
        digitalWrite(m_control_pin[1], LOW);
    }

    void move_forward(const uint8_t p_speed) {
        m_direction = FORWARD;
        analogWrite(m_enable_pin, max(MIN_SPEED, min(p_speed, MAX_SPEED)));
        digitalWrite(m_control_pin[0], HIGH);
        digitalWrite(m_control_pin[1], LOW);
    }
    void move_backward() {
        m_direction = BACKWARD;
        analogWrite(m_enable_pin, m_speed);
        digitalWrite(m_control_pin[0], LOW);
        digitalWrite(m_control_pin[1], HIGH);
    }

    void move_backward(const uint8_t p_speed) {
        m_direction = BACKWARD;
        analogWrite(m_enable_pin, max(MIN_SPEED, min(p_speed, MAX_SPEED)));
        digitalWrite(m_control_pin[0], LOW);
        digitalWrite(m_control_pin[1], HIGH);
    }

    void stop(const bool force = true) {
        if (force) {
            /* gives a short impulse in the opposite direction to 
            the current direction to immediately stop the movement of the wheel */
            if (m_direction == FORWARD)
                move_backward(MAX_SPEED);
            else if (m_direction == BACKWARD) {
                move_forward(MAX_SPEED);
            }
            delay(10);
        }
        m_direction = STOPPED;
        digitalWrite(m_enable_pin, LOW);
    }

    void set_speed(const uint8_t new_speed) {
        m_speed = max(MIN_SPEED, min(new_speed, MAX_SPEED));
    }

    inline void increase_speed(const uint8_t add_speed) {
        set_speed(m_speed + add_speed);
    }

    uint8_t get_speed() const {
      return m_speed;
    }

  private:
    uint8_t m_enable_pin;
    uint8_t m_control_pin[2];
    int8_t m_direction;
    uint8_t m_speed;
};

#endif