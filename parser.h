#ifndef PARSER_H
#define PARSER_H

#include "stack.h"
#include "lexer.h"

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

typedef struct ASNode {
    Command cmd;
    union {
        int num_value; // NUMBERの場合の値
        Stack* child; // 子ノード
    } data;
} ASNode;

Stack* parse(Stack* tokens);

#endif // PARSER_H