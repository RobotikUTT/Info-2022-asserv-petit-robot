#include "Robot.h"
#include "Wheel.h"
#include "Vector.h"

namespace Robot {
    namespace {
        Wheel left_wheel(LEFT_WHEEL_ENABLE, LEFT_WHEEL_CONTROL1, LEFT_WHEEL_CONTROL2, ENCODER_LEFT_A, ENCODER_LEFT_B, MOTOR_SPEED_P, MOTOR_SPEED_I, MOTOR_SPEED_D, MOTOR_POS_P, MOTOR_POS_I, MOTOR_POS_D);
        Wheel right_wheel(RIGHT_WHEEL_ENABLE, RIGHT_WHEEL_CONTROL1, RIGHT_WHEEL_CONTROL2, ENCODER_RIGHT_A, ENCODER_RIGHT_B, MOTOR_SPEED_P, MOTOR_SPEED_I, MOTOR_SPEED_D, MOTOR_POS_P, MOTOR_POS_I, MOTOR_POS_D);

        Vector robot_position;
        double robot_angle_rad;

        long last_left_ticks;
        long last_right_ticks;
    }

    void update()
    {
        left_wheel.update();
        right_wheel.update();

        long new_left_ticks = left_wheel.get_pos();
        long new_right_ticks = right_wheel.get_pos();

        long left_delta_ticks = new_left_ticks - last_left_ticks;
        long right_delta_ticks = new_right_ticks - last_right_ticks;

        double left_wheel_delta = left_delta_ticks / TICKS_PER_METER;
        double right_wheel_delta = right_delta_ticks / TICKS_PER_METER;

        double angle_delta = (right_wheel_delta - left_wheel_delta) / WHEEL_SPACING;

        double left_pivot_radius = left_wheel_delta / angle_delta;
        double center_pivot_radius = left_pivot_radius + WHEEL_SPACING / 2;

        double forward_delta = center_pivot_radius * sin(angle_delta);
        double right_delta = center_pivot_radius * (1 - cos(angle_delta));

        Vector forward_dir = get::forward_dir();
        Vector right_dir = get::right_dir();

        Vector position_delta = forward_delta * forward_dir + right_delta * right_dir;

        robot_position += position_delta;

    }

    void set_speed(double speed);
    
    void stop();
    void resume();

    namespace rotate{
        void absolute(double angle);
        void relative(double angle);
        void look_at(Vector position);
    }

    namespace move{
        void distance(int16_t distance);
        void to_position(position_t position);
    }

    namespace set{
        void position(Vector position);
        void angle(double angle);
    }

    namespace get{
        Vector position() {}
        Vector forward_dir() {}
        Vector right_dir() {}
        double angle() {}
    }
    
}


