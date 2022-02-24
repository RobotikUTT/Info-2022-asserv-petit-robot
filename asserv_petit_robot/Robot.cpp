#include "Robot.h"
#include "Wheel.h"
#include "Vector.h"

namespace Robot {
    namespace {
        Wheel left_wheel(LEFT_WHEEL_ENABLE, LEFT_WHEEL_CONTROL1, LEFT_WHEEL_CONTROL2, ENCODER_LEFT_A, ENCODER_LEFT_B,
                         MOTOR_SPEED_P, MOTOR_SPEED_I, MOTOR_SPEED_D, MOTOR_POS_P, MOTOR_POS_I, MOTOR_POS_D);
        Wheel right_wheel(RIGHT_WHEEL_ENABLE, RIGHT_WHEEL_CONTROL1, RIGHT_WHEEL_CONTROL2, ENCODER_RIGHT_A,
                          ENCODER_RIGHT_B, MOTOR_SPEED_P, MOTOR_SPEED_I, MOTOR_SPEED_D, MOTOR_POS_P, MOTOR_POS_I,
                          MOTOR_POS_D);

        Vector robot_position(0, 0);
        double robot_angle_rad = 0;

        long last_left_ticks;
        long last_right_ticks;
        double last_left_pos;
        double last_right_pos;
    }

    void update() {
        left_wheel.update();
        right_wheel.update();

        double new_distance_l = left_wheel.get_distance();
        double new_distance_r = right_wheel.get_distance();
        double left_wheel_delta = new_distance_l - last_left_pos;
        double right_wheel_delta = new_distance_r - last_right_pos;

        last_left_pos = new_distance_l;
        last_right_pos = new_distance_r;

        double angle_delta = (right_wheel_delta - left_wheel_delta) / WHEEL_SPACING;

        robot_angle_rad += angle_delta;

        Vector forward_dir = get::forward_dir();
        Vector right_dir = get::right_dir();

        double forward_delta = 0;
        double right_delta = 0;

        if (angle_delta == 0)
        {
            forward_delta = left_wheel_delta;
        }
        else
        {
            double left_pivot_radius = left_wheel_delta / angle_delta;
            double center_pivot_radius = left_pivot_radius + WHEEL_SPACING / 2;

            forward_delta = center_pivot_radius * sin(angle_delta);
            right_delta = center_pivot_radius * (1 - cos(angle_delta));
        }
        Vector position_delta = forward_dir * forward_delta + right_dir * right_delta;
        robot_position += position_delta;
    }

    void set_speed(double speed);

    void stop();
    void resume();

    namespace rotate {
        void absolute(double angle);
        void relative(double angle);
        void look_at(Vector position);
    }

    namespace move {
        void distance(int16_t distance);
        void to_position(Vector position);
    }

    namespace set {
        void position(Vector position);
        void angle(double angle);
    }

    namespace get{
        Vector position() {
            return robot_position;
        }
        Vector forward_dir() {
            return Vector(cos(robot_angle_rad), sin(robot_angle_rad));
        }
        Vector right_dir() {
            return Vector(sin(robot_angle_rad), -cos(robot_angle_rad));
        }
        double angle() {}
    }

}


