#ifndef PARSER_H
#define PARSER_H

#include "stack.h"
#include "lexer.h"

typedef enum Command {
    AS_N,
    AS_ADD,
    AS_SUB,
    AS_MUL,
    AS_DIV,
    AS_REM,
    AS_LT,
    AS_GT,
    AS_EQ,
    AS_POP,
    AS_SWAP,
    AS_SEL,
    AS_NGET,
    AS_ES, // executable sequence
    AS_EXEC
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