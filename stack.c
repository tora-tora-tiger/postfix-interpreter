#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = stack->bottom = NULL;
    stack->size = 0;
    return stack;
}

void push(Stack* stack, void* value) {
    StackValue* new_value = (StackValue*)malloc(sizeof(StackValue));
    new_value->data = value;
    new_value->next = stack->top;
    new_value->prev = NULL;

    if (stack->top != NULL) {
        stack->top->prev = new_value;
    }

    if (stack->bottom == NULL) {
        stack->bottom = new_value;
    }

    stack->top = new_value;
    stack->size++;
}

void* pop(Stack* stack) {
    if (stack->size == 0) {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }

    StackValue* top_value = stack->top;
    void* data = top_value->data;

    stack->top = top_value->next;
    if (stack->top != NULL) {
        stack->top->prev = NULL;
    } else {
        stack->bottom = NULL;
    }

    free(top_value);
    stack->size--;

    return data;
}

void push_buttom(Stack* stack, void* value) {
    StackValue* new_value = (StackValue*)malloc(sizeof(StackValue));
    new_value->data = value;
    new_value->next = NULL;
    new_value->prev = stack->bottom;

    if (stack->bottom != NULL) {
        stack->bottom->next = new_value;
    }

    if (stack->top == NULL) {
        stack->top = new_value;
    }

    stack->bottom = new_value;
    stack->size++;
}