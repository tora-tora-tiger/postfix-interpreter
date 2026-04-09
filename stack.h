#ifndef STACK_H
#define STACK_H


typedef struct Value Value;
struct Value {
    Value* next;
    Value* prev;
    void* data;
};

typedef struct Stack {
    Value* top;
    int size;
} Stack;

Stack* create_stack();
void push(Stack* stack, void* value);
void* pop(Stack* stack);

#endif // STACK_H