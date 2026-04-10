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
    push_buttom(tokens, (void*)token);
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
    char c;
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

void print_tokens(Stack* tokens) {
    StackValue* current = tokens->top;
    while (current != NULL) {
        Token* token = (Token*)current->data;

        switch(token->type) {
            case TK_LEFT_PAREN:
                printf("LEFT_PAREN");
                break;
            case TK_RIGHT_PAREN:
                printf("RIGHT_PAREN");
                break;
            case TK_POSTFIX:
                printf("POSTFIX");
                break;
            case TK_NUMBER:
                printf("NUMBER");
                break;
            case TK_ADD:
                printf("ADD");
                break;
            case TK_SUB:
                printf("SUB");
                break;
            case TK_MUL:
                printf("MUL");
                break;
            case TK_DIV:
                printf("DIV");
                break;
            case TK_REM:
                printf("REM");
                break;
            case TK_LT:
                printf("LT");
                break;
            case TK_GT:
                printf("GT");
                break;
            case TK_EQ:
                printf("EQ");
                break;
            case TK_POP:
                printf("POP");
                break;
            case TK_SWAP:
                printf("SWAP");
                break;
            case TK_SEL:
                printf("SEL");
                break;
            case TK_NGET:
                printf("NGET");
                break;
            case TK_EXEC:
                printf("EXEC");
                break;
        }
        if(token->type == TK_NUMBER) printf(", %d\n", token->num_value);
        else printf("\n");

        current = current->next;
    }
}

int main() {
    FILE* fp = fopen("test.pf", "r");
    if(fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    Stack* tokens = lex(fp);
    print_tokens(tokens);
}