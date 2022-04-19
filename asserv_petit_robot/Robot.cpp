#include "Robot.h"
#include "Wheel.h"
#include "Vector.h"
#include "PID_v1.h"
#include "pid_coefs.h"

#define LEFT 0
#define RIGHT 1

namespace Robot {
    namespace {
        Wheel wheel[2]{
                {LEFT_WHEEL_ENABLE, LEFT_WHEEL_CONTROL1, LEFT_WHEEL_CONTROL2, ENCODER_LEFT_A, ENCODER_LEFT_B,
                 MOTOR_SPEED_P, MOTOR_SPEED_I, MOTOR_SPEED_D},
                {RIGHT_WHEEL_ENABLE, RIGHT_WHEEL_CONTROL1, RIGHT_WHEEL_CONTROL2, ENCODER_RIGHT_A,
                 ENCODER_RIGHT_B, MOTOR_SPEED_P, MOTOR_SPEED_I, MOTOR_SPEED_D}
        };

        Vector position(0, 0);
        double angle_rad = 0;

        long last_left_ticks;
        long last_right_ticks;
        double last_pos[2];
        double last_left_pos;
        double last_right_pos;

        double _target_speed = 0;

        double target_angle_rad = 0;
        double yaw_output;

        double speed[2]{0, 0};

        PID pid_yaw(&angle_rad, &yaw_output, &target_angle_rad, YAW_P, YAW_I, YAW_D, DIRECT);
    }

    void setup() {
        pid_yaw.SetMode(AUTOMATIC);
        pid_yaw.SetOutputLimits(-0.5, 0.5);
        Robot::set::target_speed(0);
    }

    const static inline double update_angle(const double *wheel_delta) {
        /* If the robot is turning left, angle > 0
         * If --- ----- -- ------ right, angle < 0 */
        const double angle_delta = (wheel_delta[RIGHT] - wheel_delta[LEFT]) / WHEEL_SPACING;
        Robot::angle_rad += angle_delta;
        return angle_delta;
    }

    static inline void update_pos(const double angle_delta, const double *wheel_delta) {
        const Vector forward_dir = get::forward_dir();
        const Vector right_dir = forward_dir.normal();

        if (angle_delta != 0) {  // Robot goes straight
            const double forward_delta = wheel_delta[RIGHT];
            Robot::position += forward_dir * forward_delta;
        } else {  // Rotation
            const double right_pivot_radius = wheel_delta[RIGHT] / angle_delta;
            const double center_pivot_radius = right_pivot_radius + WHEEL_SPACING / 2;

            const double forward_delta = center_pivot_radius * sin(angle_delta);
            const double right_delta = center_pivot_radius * (1 - cos(angle_delta));
            Robot::position += forward_dir * forward_delta - right_dir * right_delta;
        }
    }

    void update() {
        double wheel_delta[2];
        for (int i = 0; i < 2; ++i) {
            Robot::wheel[i].update();
            const double new_distance = wheel[i].get_distance();
            wheel_delta[i] = new_distance - Robot::last_pos[i];
            Robot::last_pos[i] = new_distance;
        }

        const double angle_delta = Robot::update_angle(wheel_delta);
        Robot::update_pos(angle_delta, wheel_delta);

        pid_yaw.Compute();  // This will modify yaw_output
#ifdef DEBUG
        Serial.println(yaw_output, 6);
#endif
        speed[LEFT] = -yaw_output + _target_speed;
        speed[RIGHT] = yaw_output + _target_speed;

        wheel[LEFT].set_target_speed(speed[LEFT]);
        wheel[RIGHT].set_target_speed(speed[RIGHT]);
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

        void target_speed(double speed) {
            _target_speed = speed;
        }
    }

    namespace get {
        Vector position() {
            return Robot::position;
        }

        Vector forward_dir() {
            return Vector(cos(Robot::angle_rad), sin(Robot::angle_rad));
        }

        Vector right_dir() {
            return Vector(sin(Robot::angle_rad), -cos(Robot::angle_rad));
        }

        double angle() {
            return Robot::angle_rad;
        }
    }
}


