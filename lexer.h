#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "stack.h"

typedef enum TokenType {
    TK_LEFT_PAREN,
    TK_RIGHT_PAREN,
    TK_POSTFIX,
    TK_NUMBER,
    TK_ADD,
    TK_SUB,
    TK_MUL,
    TK_DIV,
    TK_REM,
    TK_LT,
    TK_GT,
    TK_EQ,
    TK_POP,
    TK_SWAP,
    TK_SEL,
    TK_NGET,
    TK_EXEC
} TokenType;

typedef struct Token {
    TokenType type;
    int num_value;
} Token;

Stack* lex(FILE* fp);
char* print_token(TokenType type);
void print_tokens(Stack* tokens);

#endif // LEXER_H