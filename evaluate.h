#ifndef EVALUATE_H
#define EVALUATE_H

#include "stack.h"
#include "parser.h"

typedef struct DataValue {
    Command type;
    union {
        int num_value;
        Stack* es_stack;
    } data;
} DataValue;

// typedef struct Result {
//     bool success;
//     union {
//         int num_value;
//         Stack* es_stack;
//     } data;
// } Result;

int evaluate(Stack* instruction_stack, int argc, int* argv);

#endif // EVALUATE_H