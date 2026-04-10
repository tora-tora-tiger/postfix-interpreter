#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct FilePos {
//     long int line;
//     long int column;
// } FilePos;

void add_token(Stack* tokens, TokenType type, int num_value) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->num_value = num_value;
    push_bottom(tokens, (void*)token);
}

void raise_error(char* s, FILE* fp, int start_offset, int end_offset) {
    // long int current_pos = ftell(fp);
    // if(current_pos != -1) {
    //     fprintf(stderr, "ftell cannot be called\n");
    //     start_offset = start_offset > current_pos ? current_pos : start_offset;
    //     fseek(fp, -start_offset, SEEK_SET);
    // }

    for(int i = 0 ; i < start_offset; i++) fseek(fp, -1, SEEK_CUR);
    
    fprintf(stderr, "Syntax Error: Invalid character %s\n", s);

    char error_line[start_offset + end_offset + 1];
    fgets(error_line, sizeof(error_line), fp);
    fprintf(stderr, "%s\n", error_line);
    for(int i = 0 ; i < start_offset - 2; i++) fprintf(stderr, " ");
    fprintf(stderr, "^^^^\n");
    exit(EXIT_FAILURE);
}

int get_word(FILE* fp, char* buf, int buf_size) {
    int i = 0;
    char c;
    // 空白文字をスキップ
    while((c = fgetc(fp)) != EOF && (c == ' ' || c == '\n' || c == '\t'));
    ungetc(c, fp); // 最後の非空白文字を再度読み取るために戻す

    while ((c = fgetc(fp)) != EOF && i < buf_size - 1) {
        if (c == ' ' || c == '\n' || c == '\t') {
            break;
        }
        if(c == '(' || c == ')') {
            if(i == 0) {
                buf[i++] = c;
                break;
            } else {
            ungetc(c, fp); // 次の読み取りでこの文字が再度読み取られるようにする
            break;
            }
        }

        if('A' <= c && c <= 'Z') c += 'a' - 'A'; // 大文字を小文字に変換
        buf[i++] = c;
    }
    buf[i] = '\0';
    
    return i;
}

Stack* lex(FILE* fp) {
    Stack* tokens = create_stack();
    char buff[1<<8]; // 256バイトのバッファ
    int buff_index = 0;
    // struct FilePos pos = {1, 0};

    while(get_word(fp, buff, sizeof(buff))) {
        if(buff[0] == '\0') continue;

        if(buff[0] == '(') add_token(tokens, TK_LEFT_PAREN, 0);
        else if(buff[0] == ')') add_token(tokens, TK_RIGHT_PAREN, 0);
        else if(strcmp(buff, "postfix") == 0) add_token(tokens, TK_POSTFIX, 0);
        else if(strcmp(buff, "add") == 0) add_token(tokens, TK_ADD, 0);
        else if(strcmp(buff, "sub") == 0) add_token(tokens, TK_SUB, 0);
        else if(strcmp(buff, "mul") == 0) add_token(tokens, TK_MUL, 0);
        else if(strcmp(buff, "div") == 0) add_token(tokens, TK_DIV, 0);
        else if(strcmp(buff, "rem") == 0) add_token(tokens, TK_REM, 0);
        else if(strcmp(buff, "lt") == 0) add_token(tokens, TK_LT, 0);
        else if(strcmp(buff, "gt") == 0) add_token(tokens, TK_GT, 0);
        else if(strcmp(buff, "eq") == 0) add_token(tokens, TK_EQ, 0);
        else if(strcmp(buff, "pop") == 0) add_token(tokens, TK_POP, 0);
        else if(strcmp(buff, "swap") == 0) add_token(tokens, TK_SWAP, 0);
        else if(strcmp(buff, "sel") == 0) add_token(tokens, TK_SEL, 0);
        else if(strcmp(buff, "nget") == 0) add_token(tokens, TK_NGET, 0);
        else if(strcmp(buff, "exec") == 0) add_token(tokens, TK_EXEC, 0);
        else {
            char* endptr;
            int num_value = strtol(buff, &endptr, 10);
            if(*endptr != '\0') {
                raise_error(buff, fp, buff_index - strlen(buff), strlen(buff));
            }
            add_token(tokens, TK_NUMBER, num_value);
        }
    }

    return tokens;
}

char* print_token(TokenType type) {
    switch(type) {
        case TK_LEFT_PAREN:
            return "LEFT_PAREN";
        case TK_RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TK_POSTFIX:
            return "POSTFIX";
        case TK_NUMBER:
            return "NUMBER";
        case TK_ADD:
            return "ADD";
        case TK_SUB:
            return "SUB";
        case TK_MUL:
            return "MUL";
        case TK_DIV:
            return "DIV";
        case TK_REM:
            return "REM";
        case TK_LT:
            return "LT";
        case TK_GT:
            return "GT";
        case TK_EQ:
            return "EQ";
        case TK_POP:
            return "POP";
        case TK_SWAP:
            return "SWAP";
        case TK_SEL:
            return "SEL";
        case TK_NGET:
            return "NGET";
        case TK_EXEC:
            return "EXEC";
    }
    return "UNKNOWN";
}

void print_tokens(Stack* tokens) {
    StackValue* current = tokens->top;
    while (current != NULL) {
        Token* token = (Token*)current->data;

        printf("%s", print_token(token->type));
        if(token->type == TK_NUMBER) printf(", %d\n", token->num_value);
        else printf("\n");

        current = current->next;
    }
}