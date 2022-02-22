#include "Wheel.h"

Wheel::Wheel(
    byte motor_en, byte motor_inA, byte motor_inB, byte encoderA, byte encoderB, 
    float speed_pid_P, float speed_pid_I, float speed_pid_D, 
    float pos_pid_P, float pos_pid_I, float pos_pid_D
    ) 
    : motor_en(motor_en), motor_inA(motor_inA), motor_inB(motor_inB), 
      encoder(encoderA, encoderB), 
      pid_speed(&pid_speed_input, &pid_speed_output, &pid_speed_target, speed_pid_P, speed_pid_I, speed_pid_D, DIRECT),
      pid_pos(&pid_pos_input, &pid_pos_output, &pid_pos_target, pos_pid_P, pos_pid_I, pos_pid_D, DIRECT)
{

    pid_speed.SetMode(AUTOMATIC);
    pid_speed.SetOutputLimits(-255, 255);
    pid_pos.SetMode(AUTOMATIC);
    pid_pos.SetOutputLimits(-5, 5);

    pinMode(motor_en, OUTPUT);
    pinMode(motor_inA, OUTPUT);
    pinMode(motor_inB, OUTPUT);
}

void Wheel::update_dt()
{
    uint16_t now = millis();
    dt = (double)(now - last_update);
    last_update = now;
}

void Wheel::update_position()
{
    long new_pos = encoder.read();
    previous_pos = current_pos;
    current_pos = new_pos;
}

void Wheel::update_speed()
{
    double new_speed;
    if(dt == 0)
    {
        new_speed = 0;
    }
    else
    {
        new_speed = (current_pos - previous_pos) / dt;
    }
    new_speed = min(10, new_speed);
    new_speed = max(-10, new_speed);
    current_speed = new_speed;
}

void Wheel::update_speed_pid()
{
    pid_pos_input = (double)current_pos;
    pid_pos_target = (double)desired_pos;

    pid_pos.Compute();

    desired_speed = pid_pos_output;
}

double Wheel::calculate_pid_motor_output()
{
    pid_speed_input = current_speed;
    pid_speed_target = desired_speed;

    pid_speed.Compute();

    return pid_speed_output;
}

void Wheel::update_motor_output(double pid_desired_speed)
{
    const int deadzone = 20;
    int adjusted_output;  

    if(pid_desired_speed > 0){
        adjusted_output = map((int)pid_desired_speed, 0, 255, deadzone, 255);
        digitalWrite(motor_inA, LOW);
        digitalWrite(motor_inB, HIGH);
    }
    else
    {
        adjusted_output = map((int)pid_desired_speed, -255, 0, -255, -deadzone);
        digitalWrite(motor_inA, HIGH);
        digitalWrite(motor_inB, LOW);
    }

    motor_output = adjusted_output;

    analogWrite(motor_en, abs(adjusted_output));
}

void Wheel::update()
{
    update_dt();
    update_position();
    update_speed();

    update_speed_pid();

    double pid_motor_output = calculate_pid_motor_output();

    update_motor_output(pid_motor_output);

    Serial.print(desired_speed);
    Serial.print(" ");
    Serial.print(current_speed);
    Serial.print(" ");
    Serial.print(motor_output / 255);
    Serial.println();    

}

void Wheel::set_desired_pos(long pos){
    this->desired_pos = pos;
}