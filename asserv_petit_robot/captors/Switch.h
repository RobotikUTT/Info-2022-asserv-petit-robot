//
// Created by thgir on 24/02/2022.
//

#ifndef ASSERV_PETIT_ROBOT_SWITCH_H
#define ASSERV_PETIT_ROBOT_SWITCH_H

#include <Arduino.h>

#define PULL_UP 0
#define PULL_DOWN 1

class Switch {
    private:
        const uint8_t m_pin;
        const uint8_t m_type;

    public:
        Switch(uint8_t p_pin, uint8_t p_type);
        Switch(uint8_t p_pin);

        /**
         * Check if this button is pressed or not.
         * @return true if the button is pressed, else false
         */
        const bool is_pressed() const;
};


#endif //ASSERV_PETIT_ROBOT_SWITCH_H
