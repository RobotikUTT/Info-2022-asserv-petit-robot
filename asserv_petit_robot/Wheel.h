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
        long current_pos, desired_pos, previous_pos;
        double current_speed, desired_speed;
        double pid_speed_input, pid_speed_output, pid_speed_target, pid_pos_input, pid_pos_output, pid_pos_target;
        PID pid_speed;
        PID pid_pos;
        int motor_output;
        uint16_t last_update;
        uint16_t dt;
        void update_dt();
        void update_position();
        void update_speed();
        void update_speed_pid();
        double calculate_pid_motor_output();
        void update_motor_output(double pid_motor_output);

    public:
        Wheel(uint8_t motor_en, uint8_t motor_inA, uint8_t motor_inB, uint8_t encoderA, uint8_t encoderB,
              float speed_pid_P, float speed_pid_I, float speed_pid_D, float pos_pid_P, float pos_pid_I,
              float pos_pid_D);

        void set_max_speed(float max_speed);
        void set_desired_pos(long desired_pos);
        inline double get_angle() const;
        inline double get_distance() const;
        inline long get_ticks() const;
        inline double get_speed() const;
        inline double get_angular_speed() const;

        void update();

};