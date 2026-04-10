#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

void push_node_num(Stack* st, Command cmd, int num_value) {
    ASNode* node = (ASNode*)malloc(sizeof(ASNode));
    node->cmd = cmd;
    node->data.num_value = num_value;
    push_buttom(st, node);
}

void push_node_cmd(Stack* st, Command cmd) {
    ASNode* node = (ASNode*)malloc(sizeof(ASNode));
    node->cmd = cmd;
    push_buttom(st, node);
}

void push_node_es(Stack* st, Stack* child) {
    ASNode* node = (ASNode*)malloc(sizeof(ASNode));
    node->cmd = AS_ES;
    node->data.child = child;
    push_buttom(st, node);
}

Stack* _parse(Stack* tokens) {
    Stack* st = create_stack();

    while(tokens->size > 0) {
        Token* token = (Token*)pop(tokens);

        if(token->type == TK_LEFT_PAREN) {
            push_node_es(st, _parse(tokens));
        } else if(token->type == TK_POSTFIX) {
            return st;
        }
        else switch(token->type) {
            case TK_NUMBER:
                push_node_num(st, AS_N, token->num_value);
                break;
            case TK_ADD:
                push_node_cmd(st, AS_ADD);
                break;
            case TK_SUB:
                push_node_cmd(st, AS_SUB);
                break;
            case TK_MUL:
                push_node_cmd(st, AS_MUL);
                break;
            case TK_DIV:
                push_node_cmd(st, AS_DIV);
                break;
            case TK_REM:
                push_node_cmd(st, AS_REM);
                break;
            case TK_LT:
                push_node_cmd(st, AS_LT);
                break;
            case TK_GT:
                push_node_cmd(st, AS_GT);
                break;
            case TK_EQ:
                push_node_cmd(st, AS_EQ);
                break;
            case TK_POP:
                push_node_cmd(st, AS_POP);
                break;
            case TK_SWAP:
                push_node_cmd(st, AS_SWAP);
                break;
            case TK_SEL:
                push_node_cmd(st, AS_SEL);
                break;
            case TK_NGET:
                push_node_cmd(st, AS_NGET);
                break;
            case TK_EXEC:
                push_node_cmd(st, AS_EXEC);
                break;
            default:
                fprintf(stderr, "Syntax Error: Unexpected token %s\n", print_token(token->type));
                exit(EXIT_FAILURE);
        }
        free(token);
    }

    fprintf(stderr, "Syntax Error: Expected ')'\n");
    exit(EXIT_FAILURE);
}

ASD* parse(Stack* tokens) {
    // (postfix N __)をみる
    if(tokens->size < 2) {
        fprintf(stderr, "Syntax Error: Not enough tokens\n");
        exit(EXIT_FAILURE);
    }

    Token* first = (Token*)pop(tokens);
    if(first->type != TK_LEFT_PAREN) {
        fprintf(stderr, "Syntax Error: Expected '('\n");
        exit(EXIT_FAILURE);
    }
    free(first);

    Token* second = (Token*)pop(tokens);
    if(second->type != TK_POSTFIX) {
        fprintf(stderr, "Syntax Error: Expected 'postfix'\n");
        exit(EXIT_FAILURE);
    }
    free(second);

    Token* third = (Token*)pop(tokens);
    if(third->type != TK_NUMBER) {
        fprintf(stderr, "Syntax Error: Expected a number for Number of Arguments\n");
        exit(EXIT_FAILURE);
    }
    int argc = third->num_value;
    free(third);

    Stack* st = _parse(tokens);

    ASD* asd = (ASD*)malloc(sizeof(ASD));
    asd->as_stack = st;
    asd->argc = argc;

    return asd;
}