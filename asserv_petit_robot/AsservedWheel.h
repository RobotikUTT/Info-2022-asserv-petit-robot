//
// Created by thgir on 21/02/2022.
//

#ifndef ASSERV_PETIT_ROBOT_ASSERVEDWHEEL_H
#define ASSERV_PETIT_ROBOT_ASSERVEDWHEEL_H

#include "Wheel.h"
#include "pid_coefs.h"
#include <Encoder.h>
#include <PID_v1.h>

class AsservedWheel : public Wheel {
    public:
        explicit AsservedWheel(uint8_t p_enable_pin, uint8_t p_control_pin1, uint8_t p_control_pin2,
                               uint8_t p_encoderA, uint8_t p_encoderB);
        inline void compute_pid() { m_speed_pid.Compute(); }
        void asserv_speed(const double dt);

    private:
        PID m_speed_pid;
        Encoder m_encoder;
        double m_pid_input;
        double m_pid_output;
        double m_set_point;
        int32_t m_pos;
};


#endif //ASSERV_PETIT_ROBOT_ASSERVEDWHEEL_H
