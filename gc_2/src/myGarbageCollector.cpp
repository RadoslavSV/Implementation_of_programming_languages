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
        (*m_Root)->VisitReferences(this, nullptr);
        
        for (auto object : m_Visited)
        {
            object->VisitReferences(this, nullptr);
        }
        
        for (auto allocation : m_Allocations)
        {
            auto it = m_Visited.find(static_cast<Object*>(allocation));
            if (it == m_Visited.end())
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
