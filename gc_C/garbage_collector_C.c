#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 256
#define INIT_OBJ_NUM_MAX 8

typedef enum {
    OBJ_INT,
    OBJ_PAIR
} ObjectType;

typedef struct sObject {
    ObjectType type;
    unsigned char marked;
    struct sObject *next;
    union {
        int value;
        struct {
            struct sObject *head;
            struct sObject *tail;
        };
    };
} Object;

typedef struct {
    Object* stack[MAX_STACK];
    int stackSize;
    Object* firstObject;
    int numObjects;
    int maxObjects;
} VM;

void assert(int condition, const char* message) {
    if (!condition) {
        printf("%s\n", message);
        exit(1);
    }
}

VM* newVM() {
    VM* vm = malloc(sizeof(VM));
    vm->stackSize = 0;
    vm->firstObject = NULL;
    vm->numObjects = 0;
    vm->maxObjects = INIT_OBJ_NUM_MAX;
    return vm;
}

void push(VM* vm, Object* value) {
    assert(vm->stackSize < MAX_STACK, "Stack overflow!");
    vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm) {
    assert(vm->stackSize > 0, "Stack underflow!");
    return vm->stack[--vm->stackSize];
}

void mark(Object* object) {
    if (object->marked) {
        return;
    }
    object->marked = 1;
    if (object->type == OBJ_PAIR) {
        mark(object->head);
        mark(object->tail);
    }
}

void markAll(VM* vm) {
    for (int i = 0; i < vm->stackSize; i++) {
        mark(vm->stack[i]);
    }
}

void sweep(VM* vm) {
    Object** object = &vm->firstObject;
    while (*object) {
        if (!(*object)->marked) {
            Object* unreached = *object;
            *object = unreached->next;
            free(unreached);
            vm->numObjects--;
        } else {
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

int main(int argc, const char * argv[]) {

    // TO DO

    return 0;
}
