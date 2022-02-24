#ifndef WHEEL_H
#define WHEEL_H

#include <Encoder.h>
#include <PID_v1.h>

#include <math.h>

 #define TICKS_PER_REVOLUTION 2248.86
 #define TICKS_PER_RADIAN 357.9171853216398
 #define WHEEL_DIAMETER 0.074
 #define WHEEL_PERIMETER 0.2324778563656447
 #define REVOLUTIONS_PER_METER 4.301484948429604  // 1 / WHEEL_PERIMETER
 #define TICKS_PER_METER 9673.4374411254  // TICKS_PER_REVOLUTION * REVOLUTION_PER_METER


class Wheel {
    private:
        uint8_t motor_en;
        uint8_t motor_inA;
        uint8_t motor_inB;
        Encoder encoder;
        long current_pos, previous_pos;
        double current_speed, target_speed, pid_speed_output;
        PID pid_speed;
        int motor_output;
        uint16_t last_update;
        void update_position();
        void update_speed(uint16_t dt);
        double calculate_pid_motor_output();
        void update_motor_output(double pid_motor_output);

    public:
        Wheel(uint8_t motor_en, uint8_t motor_inA, uint8_t motor_inB, uint8_t encoderA, uint8_t encoderB,
              float speed_pid_P, float speed_pid_I, float speed_pid_D);

        void set_target_speed(double speed_m_per_s);
        double get_angle() const;
        double get_distance() const;
        double get_speed() const;
        double get_angular_speed() const;

        void update();
};
#endif