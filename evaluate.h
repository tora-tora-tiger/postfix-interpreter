#ifndef EVALUATE_H
#define EVALUATE_H

#include "stack.h"

typedef enum Command {
    N,
    ADD,
    SUB,
    MUL,
    DIV,
    REM,
    LT,
    GT,
    EQ,
    POP,
    SWAP,
    SEL,
    NGET,
    ES, // executable sequence
    EXEC
} Command;

// typedef struct NumericalData {
//     Command type;
//     int value;
// } NumericalData;

// typedef struct ESData {
//     Command type;
//     Stack* es_stack;
// } ESData;

typedef struct Value {
    Command type;
    union {
        int num_value;
        Stack* es_stack;
    } data;
} Value;

// typedef struct Result {
//     bool success;
//     union {
//         int num_value;
//         Stack* es_stack;
//     } data;
// } Result;

int evaluate(Stack* instruction_stack, int argc, int* argv);

#endif // EVALUATE_H