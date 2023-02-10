Implement a simple garbage collector algorithm in C.

An implementation of a virtual machine that runs a garbage-collected heap. 

The heap is implemented as a linked list of objects, and the GC algorithm uses a mark-and-sweep method.

What is used in the code:
- ObjectType: an enumeration type that reprsents the type of an object in the heap (an integer or a pair of objects)
- Object: a structure that represents an object in the heap. It has a type (ObjectType), a marked field (used during garbage collection), a next field (a pointer to the next object in the linked list), and a union field that contains the actual data of the object (either an integer or two pointers to other objects, depending on the type).
- VM: a struct that represents the virtual machine. It has an array stack of Object pointers (the stack), a field stackSize that holds the number of objects in the stack, a pointer firstObject to the first object in the linked list of objects on the heap, a field numObjects that holds the number of objects on the heap, and a field maxObjects that holds the maximum number of objects the heap can hold before a GC cycle is triggered.

Functions for allocating and manipulating objects on the heap and on the stack:
- newVM: creates a new virtual machine and returns a pointer to it.
- push: pushes an object onto the stack.
- pop: pops an object from the stack.
- mark: recursively marks an object as "reachable".
- markAll: marks all objects on the stack as "reachable".
- sweep: collects all objects on the heap that are not marked as "reachable".
- gc: triggers a garbage collection cycle (calls markAll and sweep).
- newObject: creates a new object on the heap and returns a pointer to it.
- pushInt: creates a new integer object on the heap and pushes it onto the stack.
- pushPair: creates a new pair object on the heap by popping two objects from the stack and pushing the resulting pair object onto the stack.
- objectPrint: prints the value of an object.
- freeVM: frees all memory used by a virtual machine.

Tests that demonstrate the behavior of the virtual machine:
- test1: verifies that objects on the stack are preserved during a garbage collection cycle.
- test2: verifies that unreachable objects are collected during a garbage collection cycle.
- test3: verifies that cyclic references are handled correctly by the garbage collector.
- test4: tests the ability of the garbage collector in the virtual machine to handle cycles.
- perfTest: tests the performance of the virtual machine by performing a series of push and pop operations on the virtual machine's stack and measures how quickly the operations can be executed.
