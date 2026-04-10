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

void raise_error(char *s, FILE* fp, int start_offset, int end_offset) {
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

int get_word(FILE *fp, char *buf, int buf_size) {
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

Stack *lex(FILE *fp) {
    Stack *tokens = create_stack();
    char buff[1<<8]; // 256バイトのバッファ
    char c;
    int buff_index = 0;
    // struct FilePos pos = {1, 0};

    while(get_word(fp, buff, sizeof(buff))) {
        if(buff[0] == '\0') continue;

        if(buff[0] == '(') add_token(tokens, LEFT_PAREN, 0);
        else if(buff[0] == ')') add_token(tokens, RIGHT_PAREN, 0);
        else if(strcmp(buff, "postfix") == 0) add_token(tokens, POSTFIX, 0);
        else if(strcmp(buff, "add") == 0) add_token(tokens, ADD, 0);
        else if(strcmp(buff, "sub") == 0) add_token(tokens, SUB, 0);
        else if(strcmp(buff, "mul") == 0) add_token(tokens, MUL, 0);
        else if(strcmp(buff, "div") == 0) add_token(tokens, DIV, 0);
        else if(strcmp(buff, "rem") == 0) add_token(tokens, REM, 0);
        else if(strcmp(buff, "lt") == 0) add_token(tokens, LT, 0);
        else if(strcmp(buff, "gt") == 0) add_token(tokens, GT, 0);
        else if(strcmp(buff, "eq") == 0) add_token(tokens, EQ, 0);
        else if(strcmp(buff, "pop") == 0) add_token(tokens, POP, 0);
        else if(strcmp(buff, "swap") == 0) add_token(tokens, SWAP, 0);
        else if(strcmp(buff, "sel") == 0) add_token(tokens, SEL, 0);
        else if(strcmp(buff, "nget") == 0) add_token(tokens, NGET, 0);
        else if(strcmp(buff, "exec") == 0) add_token(tokens, EXEC, 0);
        else {
            char* endptr;
            int num_value = strtol(buff, &endptr, 10);
            if(*endptr != '\0') {
                raise_error(buff, fp, buff_index - strlen(buff), strlen(buff));
            }
            add_token(tokens, NUMBER, num_value);
        }
    }

    return tokens;
}

void print_tokens(Stack* tokens) {
    StackValue* current = tokens->top;
    while (current != NULL) {
        Token* token = (Token*)current->data;

        switch(token->type) {
            case LEFT_PAREN:
                printf("LEFT_PAREN");
                break;
            case RIGHT_PAREN:
                printf("RIGHT_PAREN");
                break;
            case POSTFIX:
                printf("POSTFIX");
                break;
            case NUMBER:
                printf("NUMBER");
                break;
            case ADD:
                printf("ADD");
                break;
            case SUB:
                printf("SUB");
                break;
            case MUL:
                printf("MUL");
                break;
            case DIV:
                printf("DIV");
                break;
            case REM:
                printf("REM");
                break;
            case LT:
                printf("LT");
                break;
            case GT:
                printf("GT");
                break;
            case EQ:
                printf("EQ");
                break;
            case POP:
                printf("POP");
                break;
            case SWAP:
                printf("SWAP");
                break;
            case SEL:
                printf("SEL");
                break;
            case NGET:
                printf("NGET");
                break;
            case EXEC:
                printf("EXEC");
                break;
        }
        if(token->type == NUMBER) printf(", %d\n", token->num_value);
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