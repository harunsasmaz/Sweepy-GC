#ifndef STATE_H
#define STATE_H

#include "gc.h"
#include <vector>

class State : public GarbageCollector {
    friend class VM;

public:
    State() {}
    ~State() {}

    State(const State &) = delete;
    const State &operator=(const State &) = delete;

    void runVM();

protected:
    // implement virtual methods
    void mark();
    void sweep();

    std::vector<Object *> m_stack;
};

#endif /* STATE_H */