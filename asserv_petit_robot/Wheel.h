#include <Encoder.h>
#include <PID_v1.h>

class Wheel
{

private:
    byte motor_en;
    byte motor_inA;
    byte motor_inB;

    Encoder encoder;

    float speed_pid_P;
    float speed_pid_I;
    float speed_pid_D;
    
    float pos_pid_P;
    float pos_pid_I;
    float pos_pid_D;

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
    Wheel(byte motor_en, byte motor_inA, byte motor_inB, byte encoderA, byte encoderB, float speed_pid_P, float speed_pid_I, float speed_pid_D, float pos_pid_P, float pos_pid_I, float pos_pid_D);

    void set_max_speed(float max_speed);
    void set_desired_pos(long desired_pos);

    long get_pos();
    float get_speed();
    
    void update();

};