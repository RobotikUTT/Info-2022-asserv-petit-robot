//
// Created by thgir on 21/02/2022.
//

#ifndef ASSERV_PETIT_ROBOT_ASSERVEDWHEEL_H
#define ASSERV_PETIT_ROBOT_ASSERVEDWHEEL_H

#include "Wheel.h"
#include <PID_v1.h>

class AsservedWheel : public Wheel {
    public:
        AsservedWheel();
        long read_asserv() const;
        inline void compute_pid() { m_pid.Compute(); }

    private:
        PID m_pid;

};


#endif //ASSERV_PETIT_ROBOT_ASSERVEDWHEEL_H
