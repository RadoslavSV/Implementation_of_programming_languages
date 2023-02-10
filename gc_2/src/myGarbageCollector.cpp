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
        if(*to != nullptr)
        {
            m_Visited.insert(*to);
        }
    }

    void Shutdown() override
    {
        std::unordered_set<Object*> visited;
        std::stack<Object*> stack;

        if (m_Root != nullptr)
        {
            stack.push(*m_Root);
        }

        while (!stack.empty())
        {
            auto object = stack.top();
            stack.pop();

            if (visited.count(object) > 0)
            {
                continue;
            }

            visited.insert(object);
            object->VisitReferences(this, nullptr);
        }

        for (auto allocation : m_Allocations)
        {
            if (visited.count(static_cast<Object*>(allocation)) == 0)
            {
                ::operator delete(allocation);
            }
        }
    }

private:
    Object** m_Root = nullptr;
    std::unordered_set<Object*> m_Visited;
    std::vector<void*> m_Allocations;
};

std::unique_ptr<GarbageCollector> CreateGarbageCollector(int argc, char* argv[])
{
    return std::make_unique<myGarbageCollector>();
}
