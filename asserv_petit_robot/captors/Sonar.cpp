//
// Created by thgir on 24/02/2022.
//

#include "Sonar.h"

Sonar::Sonar(const uint8_t echo_pin, const uint8_t trigger_pin) : m_echo(echo_pin), m_trigger(trigger_pin) {
    pinMode(m_trigger, OUTPUT);
    digitalWrite(m_trigger, LOW);
    pinMode(m_echo, INPUT);
}

double Sonar::get_distance() const {
    digitalWrite(m_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigger, LOW);
    uint32_t time_interval = pulseIn(m_echo, HIGH, 25000UL) / 2;
    return time_interval * SOUND_SPEED;
}