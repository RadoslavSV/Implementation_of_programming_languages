Source directory for all files that are needed for the genie.lua project

myGarbageCollector.cpp implements a simple garbage collector algorothm.
The CreateGarbageCollector function creates and returns an instance of the myGarbageCollector class.
In the Allocate method, memory is allocated using the ::operator new funtcion, and the address of the allocated memory is stored in a vector of allocations. This allows the garbage collector to keep track of all memory that has been allocated by the system.
The SetRoot method sets a pointer to the root object of the GC, which is used as the starting point for the garbage collection process.
The VisitReference method is called for each reference from one object to another. If the reference is not null, the VisitReference method adds the target object to a list of referenced objects and marks it as visited by inserting it into an unordered set of visited objects.
The Shutdown method implements the mark-and-sweep garbage collection algorithm. It starts by pushing the root obejct onto a stack. The method then pops an object from the stack, marks it as visited, and calls its VisitReferences method. This allows the garbage collector to traverse the object graph and mark all reachable objects. After all reachable objects have been marked, the method iterates over all allocated objects and frees those that have not been marked as reachable.
