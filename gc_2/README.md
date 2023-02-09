This is an implementation of the gc.h interface and the factory function.

A custom class "myGarbageCollector" is defined that derives from the GarbageCollector interface. 
The class implements all the virtual methods declared in the GarbageCollector interface.
The "Allocate" method uses the global operator "new" to allocate memory for the objects and stores a pointer to the memory in the "m_Allocations" vector. 
The "SetRoot" method stores the root object pointer in the "m_Root" member variable. 
The "VisitReference" method adds the object pointer to the "m_Visited" set to keep track of all visited objects.
The "Shutdown" method first visits all references of all objects in the "m_Visited" set.
Then, it frees up all the memory previously allocated by calling operator "delete" on each pointer stored in the "m_Allocations" vector.
The factory function "CreateGarbageCollector" simply creates and returns a std::unique_ptr to an instance of the "myGarbageCollector" class.
