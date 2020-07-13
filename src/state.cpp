#include "state.h"
#include <iostream>

/* depth-first marking */
class MarkVisitor : public GCObjectVisitor {
public:
    virtual void visit(Object *object)
    {
        if (object->m_marked)
            return;
        object->m_marked = 1;
        for (auto child : object->m_objects)
            child->accept(this);
    }
};

class UnmarkVisitor : public GCObjectVisitor {
public:
    virtual void visit(Object *object)
    {
        if (!object->m_marked)
            return;
        object->m_marked = 0;
        for (auto child : object->m_objects)
            child->accept(this);
    }
};

/* depth-first */
class PrintVisitor : public GCObjectVisitor {
public:
    virtual void visit(Object *object)
    {
        //if (object->m_marked)
            //return;
        object->m_marked = 1;
        std::cout << object->m_id;
        for (auto child : object->m_objects) {
            if (child->m_marked)
                continue;
            child->m_marked = 1;
            std::cout << "--";
            child->accept(this);
        }
    }
};

void State::mark()
{
    MarkVisitor marker;
    for (auto object : m_stack)
        object->accept(&marker);
}

void State::sweep()
{
    int garbageCount = 0;
    for (auto i = m_objectPool.begin(); i != m_objectPool.end();) {
        if (!(*i)->m_marked) {
            delete *i;
            m_objectPool.erase(i); // don't advance the iterator
            garbageCount++;
        } else {
            (*i)->m_marked = 0;
            ++i;
        }
    }

    if (garbageCount > 0) {
        std::cout << "\t" << garbageCount << " object(s) collected\n";
        if (m_objectPool.size() == 0)
            return;
        std::cout << "\tthe remaining object(s):\n";
        PrintVisitor printer;
        UnmarkVisitor unmarker;
        for (auto object : m_objectPool) {
            std::cout << "\t";
            object->accept(&printer);
            object->accept(&unmarker);
            std::cout << "\n";
        }
    }
}