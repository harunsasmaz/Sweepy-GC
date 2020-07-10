#ifndef GC_H
#define GC_H

#include <vector>

static const int initialThresholdCount = 4;

// GC objects derived from GCObject
class Component; // the simple object
class Object; // the complex object, consist of simple objects

// visitor of visitor pattern
class GCObjectVisitor {
public:
    virtual void visit(Object *) = 0;
};

// base class of GC objects
class GCObject {
    friend class MarkVisitor;
    friend class PrintVisitor;
    friend class State;
    friend class GarbageCollector;

public:
    GCObject();
    virtual ~GCObject();

    virtual void accept(GCObjectVisitor *) = 0;

    // the number of allocated objects, including those collected garbage
    static int m_totalCount;

protected:
    // GC flag
    unsigned char m_marked;
    // object id
    int m_id;
};

class GarbageCollector {
public:
    GarbageCollector()
        : m_thresholdCount(initialThresholdCount)
    {
    }
    ~GarbageCollector();

    GarbageCollector(const GarbageCollector &) = delete;
    const GarbageCollector &operator=(const GarbageCollector &) = delete;

    // allocate GC objects
    Object *newObject();

    void unmarkAll()
    {
        for (auto object : m_objectPool)
            object->m_marked = 0;
    }

protected:
    // mark-and-sweep steps
    virtual void mark() = 0;
    virtual void sweep() = 0;
    virtual void gc();

    // all the remaining objects
    std::vector<GCObject *> m_objectPool;

    // the number of objects required to trigger a GC.
    int m_thresholdCount;
};

// complex GC object, consist of objects
class Object : public GCObject {
    friend class MarkVisitor;
    friend class UnmarkVisitor;
    friend class PrintVisitor;

public:
    Object()
        : GCObject()
    {
    }
    virtual void accept(GCObjectVisitor *visitor)
    {
        visitor->visit(this);
    }

    void add(Object *object)
    {
        m_objects.push_back(object);
    }

    bool contains(Object *object)
    {
        for (auto child : m_objects)
            if (object == child)
                return true;
        return false;
    }

private:
    std::vector<Object *> m_objects;
};

#endif /* GC_H */