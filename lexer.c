#include "lexer.h"
#include <stdlib.h>

void add_token(Stack* tokens, TokenType type, int num_value) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->num_value = num_value;
    push_buttom(tokens, (void*)token);
}

void raise_error(char c, FILE* fp, int start_offset, int end_offset) {
    long int current_pos = ftell(fp);
    if(current_pos != -1) {
        start_offset = start_offset > current_pos ? current_pos : start_offset;
        fseek(fp, -start_offset, SEEK_SET);
    }
    
    fprintf(stderr, "Syntax Error: Invalid character '%c'\n", c);

    char error_line[start_offset + end_offset + 1];
    fgets(error_line, sizeof(error_line), fp);
    fprintf(stderr, "%s\n", error_line);
    for(int i = 0 ; i < start_offset - 2; i++) fprintf(stderr, " ");
    fprintf(stderr, "^^^^\n");
    exit(EXIT_FAILURE);
}

