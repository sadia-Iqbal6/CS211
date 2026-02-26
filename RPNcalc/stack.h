// For the size_t type definition
#include <stddef.h>

typedef struct Stack Stack;
struct Stack {
    int *memory;
    size_t elements;
    size_t index;
};

Stack newStack(size_t size);

void freeStack(Stack s);

void push(Stack* s, int element);

int pop(Stack* s);

size_t len(Stack s);
