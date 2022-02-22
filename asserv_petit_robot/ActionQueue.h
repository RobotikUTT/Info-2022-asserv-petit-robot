//
// Created by thgir on 22/02/2022.
//

#ifndef ASSERV_PETIT_ROBOT_ACTIONLIST_H
#define ASSERV_PETIT_ROBOT_ACTIONLIST_H

#include <Arduino.h>
#include "Action.h"

#define MAX_ACTION_NBR 15

class ActionQueue {
    public:
        ActionQueue();
        void add(Action* new_action);
        void insert(Action* new_action, size_t index);
        ActionQueue &operator+=(Action *new_action);
        ActionQueue &operator+=(ActionQueue &other);
        Action* remove();
        Action* remove(size_t index);
        inline bool is_empty() const;
        inline bool is_full() const;
        inline size_t size();
        Action* operator[](size_t index);

    private:
        Action *m_actions[MAX_ACTION_NBR];
        size_t m_size;
};


#endif //ASSERV_PETIT_ROBOT_ACTIONLIST_H
