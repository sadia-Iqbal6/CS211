#include <stdlib.h>
#include <string.h>

#include "stack.h"

Stack newStack(size_t size) {
    Stack s = { .memory = NULL, .elements = 0, .index = 0 };
    s.memory = calloc(size, sizeof(int));
    s.elements = size;
    return s;
}

void freeStack(Stack s) {
    free(s.memory);
}

void push(Stack* s, int element) {
    // Double the memory whenever it is filled
    if (s->index + 1 >= s->elements) {
        int* new_memory = calloc(s->elements * 2, sizeof(int));
        // Copy from the old memory into the new memory and then free the old memory
        memcpy(new_memory, s->memory, s->elements * sizeof(int));
        free(s->memory);
        s->memory = new_memory;
        s->elements = s->elements * 2;
    }
    s->memory[s->index] = element;
    s->index += 1;
}

int pop(Stack* s) {
    if (0 == s->index) {
        return '\0';
    }
    // Index is at the first empty position
    s->index -= 1;
    int output = s->memory[s->index];
    return output;
}

size_t len(Stack s) {
    return s.index;
}

