#ifndef ROBOT_H
#define ROBOT_H

#include <Encoder.h>
#include <PID_v1.h>

#include "Wheel.h"
#include "pins.h"
#include "pid_coefs.h"

#include "Vector.h"

#define TICKS_PER_REVOLUTION 2248.86
#define WHEEL_DIAMETER 0.074
#define WHEEL_PERIMETER 0.2325
#define REVOLUTIONS_PER_METER 4.3015  // 1/WHEEL_PERIMETER = 1/0.2325
#define TICKS_PER_METER 9673.44  // 2248.86 * 4.3015

#define WHEEL_SPACING   0.2

typedef struct {
    const Vector position;
    const double angle;
} transform_t;


namespace Robot {
    namespace rotate{
        void absolute(double angle);
        void relative(double angle);
        void look_at(Vector position);
    }
    namespace move{
        void distance(int16_t distance);
        void to_position(Vector position);
    }
    namespace set{
        void position(Vector position);
        void angle(double angle);
    }

    namespace get{
    Vector position();
    Vector forward_dir();
    Vector right_dir();
    double angle();
}

    void set_speed(double speed);
    
    void stop();   // Interompre l'action
    void resume(); // Continuer l'action
    
    void update(); // Appelé à chaque boucle
}

#endif