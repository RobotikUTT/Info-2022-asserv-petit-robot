//
// Created by thgir on 22/02/2022.
//

#include "ActionQueue.h"


ActionQueue::ActionQueue() : m_size(0), m_actions{nullptr} {}

void ActionQueue::add(Action *new_action) {
    m_actions[m_size++] = new_action;
}

void ActionQueue::add(Action *new_action, size_t index) {
    if (index < m_size)
        memmove(m_actions + index, m_actions + index + 1, m_size - index);
    m_actions[index] = new_action;
    m_size++;
}

ActionQueue &ActionQueue::operator+=(Action *new_action) {
    this->add(new_action);
    return *this;
}

Action* ActionQueue::remove() {
    return m_actions[m_size--];
}

Action *ActionQueue::remove(size_t index) {
    if (index < m_size)
        return nullptr;
    Action* result = m_actions[index];
    m_size--;
    memmove(m_actions + index + 1, m_actions + index, m_size - index);
    return result;
}

bool ActionQueue::is_empty() const {
    return m_size == 0;
}

bool ActionQueue::is_full() const {
    return m_size == MAX_ACTION_NBR;
}

Action *ActionQueue::operator[](size_t index) {
    if (m_size < index) return nullptr;
    return m_actions[index];
}