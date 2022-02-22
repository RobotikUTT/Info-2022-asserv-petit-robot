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

void Wheel::update()
{

    uint16_t now = millis();
    double dt = (double)(now - last_update);

    long new_pos = encoder.read();

    double new_speed;
    if(dt == 0)
    {
        new_speed = 0;
    }
    else
    {
        new_speed = (new_pos - current_pos) / dt;
    }

    // new_speed = min(10, new_speed);
    // new_speed = min(-10, new_speed);

    current_pos = new_pos;
    current_speed = new_speed;

    pid_pos_input = (double)current_pos;
    pid_pos_target = (double)desired_pos;

    pid_pos.Compute();

    desired_speed = pid_pos_output;
    // desired_speed = 5;
    
    pid_speed_input = current_speed;
    pid_speed_target = desired_speed;

    pid_speed.Compute();

    double motor_output = pid_speed_output;

    #define DEADZONE 20

    int actual_output;
    if(motor_output > 0){
        actual_output = map((int)motor_output, 0, 255, DEADZONE, 255);
        digitalWrite(motor_inA, LOW);
        digitalWrite(motor_inB, HIGH);
    }
    else
    {
        actual_output = map((int)motor_output, -255, 0, -255, -DEADZONE);
        digitalWrite(motor_inA, HIGH);
        digitalWrite(motor_inB, LOW);
    }

    analogWrite(motor_en, abs(actual_output));


    // Serial.print(desired_pos);
    // Serial.print(" ");
    // Serial.print(current_pos % 2248);
    // Serial.print(" ");
    Serial.print(desired_speed);
    Serial.print(" ");
    Serial.print(current_speed);
    Serial.print(" ");
    Serial.print(motor_output / 255);
    Serial.println();    

    last_update = now;
}

void Wheel::set_desired_pos(long pos){
    this->desired_pos = pos;
}