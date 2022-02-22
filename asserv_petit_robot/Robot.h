// #ifndef ROBOT_H
// #define ROBOT_H

// #include <Arduino.h>
// #include <Encoder.h>
// #include <PID_v1.h>

// #include "Wheel.h"
// #include "pins.h"
// #include "AsservedWheel.h"


// #define TICKS_PER_REVOLUTION 2248.86
// #define WHEEL_DIAMETER 0.074
// #define WHEEL_PERIMETER 0.2325
// #define REVOLUTIONS_PER_METER 4.3015  // 1/WHEEL_PERIMETER = 1/0.2325
// #define TICKS_PER_METER 9673.44  // 2248.86 * 4.3015

// #define SAMPLING_FREQUENCY 50.0
// #define NEGLIGIBLE_ERROR 0.01


// typedef struct {
//     double x;
//     double y;
//     double angle;
// } position_t;


// namespace Robot {
//     void move(const int8_t p_speed);
//     void stop();
//     void compute_pid();
// }

// #endif