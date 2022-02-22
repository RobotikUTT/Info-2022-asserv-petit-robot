//
// Created by thgir on 22/02/2022.
//

#ifndef ASSERV_PETIT_ROBOT_ACTIONLIST_H
#define ASSERV_PETIT_ROBOT_ACTIONLIST_H

#include <Arduino.h>
#include "Action.h"

#define MAX_ACTION_NBR 15

class ActionList {
    public:
        ActionList();
        void add(Action* new_action);
        void add(Action* new_action, size_t index);
        ActionList &operator+=(Action *new_action);
        Action* remove();
        Action* remove(size_t index);
        inline bool is_empty() const;
        inline bool is_full() const;
        Action* operator[](size_t index);

    private:
        Action *m_actions[MAX_ACTION_NBR];
        size_t m_size;
};


#endif //ASSERV_PETIT_ROBOT_ACTIONLIST_H
