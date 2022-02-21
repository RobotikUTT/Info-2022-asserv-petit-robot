//
// Created by thgir on 21/02/2022.
//

#include "AsservedWheel.h"

AsservedWheel::AsservedWheel(uint8_t p_enable_pin, uint8_t p_control_pin1, uint8_t p_control_pin2,
                             uint8_t p_encoderA, uint8_t p_encoderB) :
        m_pid_input(0), m_pid_output(0), m_set_point(10), m_pos(0),
        Wheel(p_enable_pin, p_control_pin1, p_control_pin2),
        m_encoder(p_encoderA, p_encoderB),
        m_speed_pid(&m_pid_input, &m_pid_output, &m_set_point, MOTOR_POS_P, MOTOR_POS_I, MOTOR_POS_D, DIRECT) {
    m_speed_pid.SetSampleTime(10);
    m_speed_pid.SetMode(AUTOMATIC);
    m_speed_pid.SetOutputLimits(-255, 255);
}

void AsservedWheel::asserv_speed(const double dt) {
    int32_t new_pos = m_encoder.read();
    m_pid_input = (dt == 0 ? 0 : (new_pos - m_pos) / dt);
    m_pos = new_pos;
}

