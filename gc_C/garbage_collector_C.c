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

int main(int argc, const char * argv[]) {

    // TO DO

    return 0;
}
