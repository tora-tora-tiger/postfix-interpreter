#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void push(Stack* stack, void* value) {
    Value* new_value = (Value*)malloc(sizeof(Value));
    new_value->data = value;
    new_value->next = stack->top;
    new_value->prev = NULL;

    if (stack->top != NULL) {
        stack->top->prev = new_value;
    }

    stack->top = new_value;
    stack->size++;
}

void* pop(Stack* stack) {
    if (stack->size == 0) {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }

    Value* top_value = stack->top;
    void* data = top_value->data;

    stack->top = top_value->next;
    if (stack->top != NULL) {
        stack->top->prev = NULL;
    }

    free(top_value);
    stack->size--;

    return data;
}