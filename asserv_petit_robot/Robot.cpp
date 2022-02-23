#include "Robot.h"
#include "Wheel.h"

namespace Robot {
    namespace {
        Wheel left_wheel(LEFT_WHEEL_ENABLE, LEFT_WHEEL_CONTROL1, LEFT_WHEEL_CONTROL2, ENCODER_LEFT_A, ENCODER_LEFT_B, MOTOR_SPEED_P, MOTOR_SPEED_I, MOTOR_SPEED_D, MOTOR_POS_P, MOTOR_POS_I, MOTOR_POS_D);
        Wheel right_wheel(RIGHT_WHEEL_ENABLE, RIGHT_WHEEL_CONTROL1, RIGHT_WHEEL_CONTROL2, ENCODER_RIGHT_A, ENCODER_RIGHT_B, MOTOR_SPEED_P, MOTOR_SPEED_I, MOTOR_SPEED_D, MOTOR_POS_P, MOTOR_POS_I, MOTOR_POS_D);
        position_t robot_position;
        double robot_angle;
    }

    void update();

    void set_speed(double speed);
    
    void stop();
    void resume();

    namespace rotate{
        void absolute(double angle);
        void relative(double angle);
        void look_at(position_t position);
    }

    namespace move{
        void distance(int16_t distance);
        void to_position(position_t position);
    }

    namespace set{
        void position(position_t position);
        void angle(double angle);
    }

    namespace get{
        position_t position();
        double angle();
    }

    
    
}


