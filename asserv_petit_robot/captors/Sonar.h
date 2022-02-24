//
// Created by thgir on 24/02/2022.
//

#ifndef ASSERV_PETIT_ROBOT_SONAR_H
#define ASSERV_PETIT_ROBOT_SONAR_H

#include <Arduino.h>

#define SOUND_SPEED 340.0

class Sonar {
    private:
        const uint8_t m_echo;
        const uint8_t m_trigger;

    public:
        Sonar(const uint8_t echo_pin, const uint8_t trigger_pin);
        /**
         * Compute and return the distance between the sonar and the first obstacle encountered
         * @return the distance in meters
         */
        double get_distance() const;
};


#endif //ASSERV_PETIT_ROBOT_SONAR_H
