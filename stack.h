#ifndef STACK_H
#define STACK_H


typedef struct StackValue StackValue;
struct StackValue {
    StackValue* next;
    StackValue* prev;
    void* data;
};

typedef struct Stack {
    StackValue* top;
    StackValue* bottom;
    int size;
} Stack;

Stack* create_stack();
void push(Stack* stack, void* value);
void* pop(Stack* stack);

#endif // STACK_H