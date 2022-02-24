//
// Created by thgir on 24/02/2022.
//

#include "Switch.h"

Switch::Switch(const uint8_t p_pin, const uint8_t p_type): m_pin(p_pin), m_type(p_type) {
    pinMode(m_pin, m_type);
}

Switch::Switch(const uint8_t p_pin): m_pin(p_pin), m_type(PULL_UP) {
    pinMode(m_pin, INPUT_PULLUP);
}

const inline bool Switch::is_pressed() const { return digitalRead(m_pin) == m_type; }
