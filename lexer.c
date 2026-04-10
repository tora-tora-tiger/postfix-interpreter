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

Stack *lex(FILE *fp) {
    Stack *tokens = create_stack();
    char buff[1<<8]; // 256バイトのバッファ
    char c;
    int buff_index = 0;
    // struct FilePos pos = {1, 0};

    while ((c = fgetc(fp)) != EOF) {
        // 空白文字は無視
        if (c == ' ' || c == '\n' || c == '\t') {
            // if(c == '\n') {
            //     pos.line++;
            //     pos.column = 0;
            // }
            continue;
        }

        if('A' <= c && c <= 'Z') c += 'a' - 'A'; // 大文字を小文字に変換

        // -?[0-9]+の形式の数値を読み取る
        if(('0' <= c && c <= '9') || c == '-') {
            buff[buff_index++] = c;
            while ((c = fgetc(fp)) != EOF) {
                if('0' <= c && c <= '9') {
                    buff[buff_index++] = c;
                    continue;
                }

                // 空白文字が来たら数値の終わり
                if(c == ' ' || c == '\n' || c == '\t') break;
                
                // その他の文字が来たらエラー
                raise_error(c, fp, buff_index, 4);
            }
            buff[buff_index] = '\0';
            int n = atoi(buff);
            add_token(tokens, NUMBER, n);
            buff_index = 0;
            continue;
        }
        
        if(c == '(') {
            add_token(tokens, LEFT_PAREN, 0);
            continue;
        }
        else if(c == ')') {
            add_token(tokens, RIGHT_PAREN, 0);
            continue;
        }
        if(c == 'a') {
            c = fgetc(fp);
            if(c == 'd') {
                c = fgetc(fp);
                if(c == 'd') add_token(tokens, ADD, 0);
                else {
                    raise_error(c, fp, 5, 4);
                }
            } else {
                raise_error(c, fp, 4, 4);
            }

            continue;
        }

        if(c == 'd') {
            c = fgetc(fp);
            if(c == 'i') {
                c = fgetc(fp);
                if(c == 'v') add_token(tokens, DIV, 0);
                else {
                    raise_error(c, fp, 5, 4);
                }
            } else {
                raise_error(c, fp, 4, 4);
            }

            continue;
        }

        if(c == 'e') {
            c = fgetc(fp);
            if(c == 'x') {
                c = fgetc(fp);
                if(c == 'e') {
                    c = fgetc(fp);
                    if(c == 'c') add_token(tokens, EXEC, 0);
                    else {
                        raise_error(c, fp, 6, 4);
                    }
                } else {
                    raise_error(c, fp, 5, 4);
                }
            } else if (c == 'q') {
                add_token(tokens, EQ, 0);
            } else {
                raise_error(c, fp, 4, 4);
            }

            continue;
        }

        if(c == 'g') {
            c = fgetc(fp);
            if(c == 't') add_token(tokens, GT, 0);
            else {
                raise_error(c, fp, 4, 4);
            }
            continue;
        }

        if(c == 'l') {
            c = fgetc(fp);
            if(c == 't') add_token(tokens, LT, 0);
            else {
                raise_error(c, fp, 4, 4);
            }
            continue;
        }

        if(c == 'm') {
            c = fgetc(fp);
            if(c == 'u') {
                c = fgetc(fp);
                if(c == 'l') add_token(tokens, MUL, 0);
                else {
                    raise_error(c, fp, 5, 4);
                }
            } else {
                raise_error(c, fp, 4, 4);
            }
            continue;
        }

        if(c == 'n') {
            c = fgetc(fp);
            if(c == 'g') {
                c = fgetc(fp);
                if(c == 'e') {
                    c = fgetc(fp);
                    if(c == 't') add_token(tokens, NGET, 0);
                    else {
                        raise_error(c, fp, 6, 4);
                    }
                } else {
                    raise_error(c, fp, 4, 4);
                }
            } else {
                raise_error(c, fp, 4, 4);
            }
            continue;
        }

        if(c == 'p') {
            c = fgetc(fp);
            if(c == 'o') {
                c = fgetc(fp);
                if(c == 'p') add_token(tokens, POP, 0);
                else if (c == 's') {
                    c = fgetc(fp);
                    if(c == 't') {
                        c = fgetc(fp);
                        if(c == 'f') {
                            c = fgetc(fp);
                            if(c == 'i') {
                                c = fgetc(fp);
                                if(c == 'x') add_token(tokens, POSTFIX, 0);
                                else {
                                    raise_error(c, fp, 7, 4);
                                }
                            } else {
                                raise_error(c, fp, 6, 4);
                            }
                        } else {
                            raise_error(c, fp, 6, 4);
                        }
                    }
                    else {
                        raise_error(c, fp, 6, 4);
                    }
                }
                else {
                    raise_error(c, fp, 5, 4);
                }
            } else {
                raise_error(c, fp, 4, 4);
            }
            continue;
        }

        if(c == 'r') {
            c = fgetc(fp);
            if(c == 'e') {
                c = fgetc(fp);
                if(c == 'm') add_token(tokens, REM, 0);
                else {
                    raise_error(c, fp, 5, 4);
                }
            } else {
                raise_error(c, fp, 4, 4);
            }
            continue;
        }

        if(c == 's') {
            c = fgetc(fp);
            if(c == 'e') {
                c = fgetc(fp);
                if(c == 'l') {
                    add_token(tokens, SEL, 0);
                } else {
                    raise_error(c, fp, 5, 4);
                }
            } else if (c == 'u') {
                c = fgetc(fp);
                if(c == 'b') add_token(tokens, SUB, 0);
                else {
                    raise_error(c, fp, 5, 4);
                }
            } else if (c == 'w') {
                c = fgetc(fp);
                if(c == 'a') {
                    c = fgetc(fp);
                    if(c == 'p') add_token(tokens, SWAP, 0);
                    else {
                        raise_error(c, fp, 6, 4);
                    }
                } else {
                    raise_error(c, fp, 5, 4);
                }
            } else {
                raise_error(c, fp, 4, 4);
            }
            continue;
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

//     raise_error('x', fp, 5, 20);
// }