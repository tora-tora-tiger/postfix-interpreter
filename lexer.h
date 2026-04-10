#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "stack.h"

typedef enum TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
    POSTFIX,
    NUMBER,
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
    EXEC
} TokenType;

typedef struct Token {
    TokenType type;
    int num_value;
} Token;

Stack* lex(FILE* fp);
void print_tokens(Stack* tokens);

#endif // LEXER_H