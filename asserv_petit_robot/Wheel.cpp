#include "Wheel.h"

Wheel::Wheel(
        byte motor_en, byte motor_inA, byte motor_inB, byte encoderA, byte encoderB,
        float speed_pid_P, float speed_pid_I, float speed_pid_D
)
        : motor_en(motor_en), motor_inA(motor_inA), motor_inB(motor_inB),
          encoder(encoderA, encoderB),
          pid_speed(&current_speed, &pid_speed_output, &target_speed, speed_pid_P, speed_pid_I, speed_pid_D,
                    DIRECT) {

    pid_speed.SetMode(AUTOMATIC);
    pid_speed.SetOutputLimits(-255, 255);

    pinMode(motor_en, OUTPUT);
    pinMode(motor_inA, OUTPUT);
    pinMode(motor_inB, OUTPUT);
}


void Wheel::update_position() {
    long new_pos = encoder.read();
    previous_pos = current_pos;
    current_pos = new_pos;
}

void Wheel::update_speed(const uint16_t dt) {
    double new_speed;
    if (dt != 0) {
        new_speed = (double) (current_pos - previous_pos) / dt;
    } else {
        new_speed = 0;
    }
    new_speed = min(10, new_speed);
    new_speed = max(-10, new_speed);
    current_speed = new_speed;
}

double Wheel::calculate_pid_motor_output() {
    pid_speed.Compute();
    return pid_speed_output;
}

void Wheel::update_motor_output(double pid_desired_speed) {
    #define deadzone 20

    if (pid_desired_speed > 0) {
        motor_output = map((int) pid_desired_speed, 0, 255, deadzone, 255);
        digitalWrite(motor_inA, LOW);
        digitalWrite(motor_inB, HIGH);
    } else {
        motor_output = map((int) pid_desired_speed, -255, 0, -255, -deadzone);
        digitalWrite(motor_inA, HIGH);
        digitalWrite(motor_inB, LOW);
    }

    analogWrite(motor_en, abs(motor_output));
}

void Wheel::update() {
    uint16_t now = millis();
    uint16_t dt = now - last_update;
    last_update = now;

    update_position();
    update_speed(dt);
    double pid_motor_output = calculate_pid_motor_output();
    update_motor_output(pid_motor_output);
}

void Wheel::set_target_speed(double speed_m_per_s) {
    target_speed = speed_m_per_s * TICKS_PER_METER / 1000.0;
}

double Wheel::get_angle() const {
    return (current_pos / TICKS_PER_REVOLUTION) * 2 * PI;
}

double Wheel::get_distance() const {
    return current_pos / TICKS_PER_METER;
}

double Wheel::get_speed() const {
    return 1000.0 * current_speed / TICKS_PER_METER;
}

double Wheel::get_angular_speed() const {
    return 1000.0 * current_speed / TICKS_PER_RADIAN;
}