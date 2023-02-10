#include "gc.h"
#include <iostream>
#include <memory>
#include <vector>

class myGarbageCollector : public GarbageCollector
{
public:
    void* Allocate(size_t size) override
    {
        auto memory = ::operator new(size);
        m_Allocations.push_back(memory);
        return memory;
    }

    void SetRoot(Object** root) override
    {
        m_Root = root;
    }

    void VisitReference(Object* from, Object** to, void* state) override
    {
        if (*to != nullptr)
        {
            m_Visited.insert(*to);
            m_Referenced.push_back(*to);
        }
    }

    void Shutdown() override
    {
        std::stack<Object*> stack;

        if (m_Root != nullptr)
        {
            stack.push(*m_Root);
        }

        while (!stack.empty())
        {
            auto object = stack.top();
            stack.pop();

            if (m_Visited.count(object) > 0)
            {
                continue;
            }

            m_Visited.insert(object);
            object->VisitReferences(this, nullptr);

            for (auto ref : m_Referenced)
            {
                if (ref != nullptr)
                {
                    stack.push(ref);
                }
            }

            m_Referenced.clear();
        }

        for (auto allocation : m_Allocations)
        {
            if (m_Visited.count(static_cast<Object*>(allocation)) == 0)
            {
                ::operator delete(allocation);
            }
        }
    }

private:
    Object** m_Root = nullptr;
    std::unordered_set<Object*> m_Visited;
    std::vector<void*> m_Allocations;
    std::vector<Object*> m_Referenced;
};

std::unique_ptr<GarbageCollector> CreateGarbageCollector(int argc, char* argv[])
{
    return std::make_unique<myGarbageCollector>();
}
