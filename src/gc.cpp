#include "gc.h"
#include <iostream>

int GCObject::m_totalCount = 0;

GCObject::GCObject()
    : m_marked(0)
{
    m_totalCount++;
    m_id = m_totalCount;
    std::cout << ".. Creating a new object, id: " << m_id << std::endl;
}

GCObject::~GCObject()
{
    std::cout << ".. Deleting object, id: " << m_id << std::endl;
}

GarbageCollector::~GarbageCollector()
{
    // delete all the remaining objects
    for (auto object : m_objectPool)
        delete object;
}

Object *GarbageCollector::newObject()
{
    if (m_objectPool.size() == m_thresholdCount)
        gc();
    Object *object = new Object;
    m_objectPool.push_back(object);
    return object;
}

void GarbageCollector::gc()
{
    mark();
    sweep();
    if (m_objectPool.size() >= m_thresholdCount)
        m_thresholdCount = 2 * m_thresholdCount;
}