#include "vm.h"
#include "state.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

static const int instructionCount = 64;

// Simulate executing opcodes, which are generated randomly.
void VM::run()
{
    srand(time(NULL));
    for (int i = 0; i < instructionCount; i++) {
        int opcode = rand() % 4;
        switch (opcode) {
        case 0: // push a new component into the m_stack
            push();
            break;
        case 1: // pop object, which becomes garbage
            pop();
            break;
        case 2:
            compose();
            break;
        default:
            circle();
            break;
        }
    }
    std::cout << ">> HALT\n";
}

// Push a new component into the m_stack
void VM::push()
{
    std::cout << ">> PUSH\n";
    auto object = m_state->newObject();
    m_state->m_stack.push_back(object);
}

void VM::pop()
{
    if (m_state->m_stack.size() > 0) {
        std::cout << ">> POP\n";
        m_state->m_stack.pop_back();
    }
}

// Compose top two objects
void VM::compose()
{
    int size = m_state->m_stack.size();
    if (size < 2)
        return;

    auto object1 = m_state->m_stack[size - 1];
    auto object2 = m_state->m_stack[size - 2];
    if (!object2->contains(object1)) {
        std::cout << ">> COMPOSE\n";
        object2->add(object1);
    }
}

// Circular references of top two objects
void VM::circle()
{
    int size = m_state->m_stack.size();
    if (size > 1) {
        auto object1 = m_state->m_stack[size - 1];
        auto object2 = m_state->m_stack[size - 2];
        if (!object2->contains(object1)) {
            object2->add(object1);
        }
        if (!object1->contains(object2)) {
            std::cout << ">> CIRCLE TOP TWO\n";
            object1->add(object2);
        }
    } else if (size > 0) {
        auto object = m_state->m_stack[size - 1];
        if (!object->contains(object)) {
            std::cout << ">> CIRCLE ITSELF\n";
            object->add(object);
        }
    }
}