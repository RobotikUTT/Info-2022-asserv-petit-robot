#include "Robot.h"

namespace Robot {
    namespace {
        Encoder right_encoder(encoderRightA, encoderRightB);
        Encoder left_encoder(encoderLeftA, encoderLeftB);
        AsservedWheel right_wheel(RightWheelEnable, RightWheelControl1, RightWheelControl2, encoderRightA, encoderRightB);
        AsservedWheel left_wheel(LeftWheelEnable, LeftWheelControl1, LeftWheelControl2, encoderLeftA, encoderLeftB);
    }

    void move(const int8_t p_speed) {
        const uint8_t cmd_speed = abs(p_speed);
        if (p_speed > 0) {
            right_wheel.move_forward(cmd_speed);
            left_wheel.move_forward(cmd_speed);
        } else if (p_speed < 0) {
            right_wheel.move_backward(cmd_speed);
            left_wheel.move_backward(cmd_speed);
        } else {
            right_wheel.stop();
            left_wheel.stop();
        }
    }

    void stop() {
        right_wheel.stop();
        left_wheel.stop();
    }

    void compute_pid() {
        right_wheel.compute_pid();
        left_wheel.compute_pid();
    }
}


