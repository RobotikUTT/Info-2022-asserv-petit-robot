#ifndef ROBOT_H
#define ROBOT_H

#include <Encoder.h>
#include <PID_v1.h>

#include "Wheel.h"
#include "pins.h"

#define TICKS_PER_REVOLUTION 2248.86
#define WHEEL_DIAMETER 0.074
#define WHEEL_PERIMETER 0.2325
#define REVOLUTIONS_PER_METER 4.3015  // 1/WHEEL_PERIMETER = 1/0.2325
#define TICKS_PER_METER 9673.44  // 2248.86 * 4.3015


typedef struct {
    double x;
    double y;
} position_t;


namespace Robot {

    namespace rotate{
        void absolute(double angle);
        void relative(double angle);
        void look_at(position_t position);
    }

    namespace move{
        void distance(int16_t distance);
        void to_position(position_t position);
    }

    namespace set{
        void position(position_t position);
        void angle(double angle);
    }

    namespace get{
        position_t position();
        double angle();
    }

    void set_speed(double speed);
    
    void stop();   // Interompre l'action
    void resume(); // Continuer l'action
    
    void update(); // Appelé à chaque boucle
}

#endif