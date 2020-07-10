#ifndef VM_H
#define VM_H

#include "state.h"
#include <vector>

class VM {
public:
    explicit VM(State *m_state)
        : m_state(m_state)
    {
    }

    void run();

private:
    Object *top()
    {
        return m_state->m_stack.back();
    }

    int size()
    {
        return m_state->m_stack.size();
    }

    // operations
    void push();
    void pop();
    void compose();
    void circle();

    State *m_state;
};

#endif /* VM_H */