#include "evaluate.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void _push_num(Stack* s, int num) {
    DataValue* value = (DataValue*)malloc(sizeof(DataValue));
    value->type = DT_N;
    value->data.num_value = num;
    push(s, (void*)value);
}

void add(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for add\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);
    DataValue* v2 = (DataValue*)pop(s);

    if(v1->type != DT_N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != DT_N) {
        fprintf(stderr, "Error: Second operand is not a number\n");
        exit(EXIT_FAILURE);
    }

    v1->data.num_value = v2->data.num_value + v1->data.num_value;
    free(v2);
    push(s, v1);
}

void sub(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for sub\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);
    DataValue* v2 = (DataValue*)pop(s);

    if(v1->type != DT_N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != DT_N) {
        fprintf(stderr, "Error: Second operand is not a number\n");
        exit(EXIT_FAILURE);
    }

    v1->data.num_value = v2->data.num_value - v1->data.num_value;
    free(v2);
    push(s, v1);
}

void mul(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for mul\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);
    DataValue* v2 = (DataValue*)pop(s);

    if(v1->type != DT_N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != DT_N) {
        fprintf(stderr, "Error: Second operand is not a number\n");
        exit(EXIT_FAILURE);
    }

    v1->data.num_value = v2->data.num_value*  v1->data.num_value;
    free(v2);
    push(s, v1);
}

void _div(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for div\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);
    DataValue* v2 = (DataValue*)pop(s);

    if(v1->type != DT_N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != DT_N) {
        fprintf(stderr, "Error: Second operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v1->data.num_value == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        exit(EXIT_FAILURE);
    }

    v1->data.num_value = v2->data.num_value / v1->data.num_value;
    free(v2);
    push(s, v1);
}

void rem(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for rem\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);
    DataValue* v2 = (DataValue*)pop(s);

    if(v1->type != DT_N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != DT_N) {
        fprintf(stderr, "Error: Second operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v1->data.num_value == 0) {
        fprintf(stderr, "Error: Division by zero in rem\n");
        exit(EXIT_FAILURE);
    }

    v1->data.num_value = v2->data.num_value % v1->data.num_value;
    free(v2);
    push(s, v1);
}

void lt(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for lt\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);
    DataValue* v2 = (DataValue*)pop(s);

    if(v1->type != DT_N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != DT_N) {
        fprintf(stderr, "Error: Second operand is not a number\n");
        exit(EXIT_FAILURE);
    }

    v1->data.num_value = (v2->data.num_value < v1->data.num_value) ? 1 : 0;
    free(v2);
    push(s, v1);
}

void gt(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for gt\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);
    DataValue* v2 = (DataValue*)pop(s);

    if(v1->type != DT_N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != DT_N) {
        fprintf(stderr, "Error: Second operand is not a number\n");
        exit(EXIT_FAILURE);
    }

    v1->data.num_value = (v2->data.num_value > v1->data.num_value) ? 1 : 0;
    free(v2);
    push(s, v1);
}

void eq(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for eq\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);
    DataValue* v2 = (DataValue*)pop(s);

    if(v1->type != DT_N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != DT_N) {
        fprintf(stderr, "Error: Second operand is not a number\n");
        exit(EXIT_FAILURE);
    }

    v1->data.num_value = (v2->data.num_value == v1->data.num_value) ? 1 : 0;
    free(v2);
    push(s, v1);
}

void _pop(Stack* s) {
    if(s->size == 0) {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    DataValue* v = pop(s);
    free(v); // ポップした値を解放
}

void swap(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for swap\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);
    DataValue* v2 = (DataValue*)pop(s);

    push(s, v1);
    push(s, v2);
}

/*
 * when stack |-v3, v2, v1
 * then if v3 then v2 else v1
 */
void sel(Stack* s) {
    if(s->size < 3) {
        fprintf(stderr, "Error: Not enough operands for sel\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);
    DataValue* v2 = (DataValue*)pop(s);
    DataValue* v3 = (DataValue*)pop(s);

    if(v3->type != DT_N) {
        fprintf(stderr, "Error: Condition is not a number\n");
        exit(EXIT_FAILURE);
    }

    if(v3->data.num_value == 0) {
        push(s, v1);
        free(v2);
    } else {
        push(s, v2);
        free(v1);
    }

    free(v3);
}

void nget(Stack* s) {
    if(s->size < 1) {
        fprintf(stderr, "Error: Not enough operands for nget\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);

    if(v1->type != DT_N) {
        fprintf(stderr, "Error: Operand is not a number\n");
        exit(EXIT_FAILURE);
    }

    int n = v1->data.num_value;
    free(v1);

    if(n <= 0 || n > s->size) {
        fprintf(stderr, "Error: Invalid index for nget\n");
        exit(EXIT_FAILURE);
    }

    StackValue* current = s->top;
    for(int i = 1; i < n; i++) {
        current = current->next;
    }

    if(((DataValue* )current->data)->type != DT_N) {
        fprintf(stderr, "Error: nget target should be a number\n");
        exit(EXIT_FAILURE);
    }

    // copy
    DataValue* copy = malloc(sizeof(DataValue));
    memcpy(copy, current->data, sizeof(DataValue));

    push(s, copy);
}

void exec(Stack* inst_stack, Stack* s) {
    if(s->size < 1) {
        fprintf(stderr, "Error: Not enough operands for exec\n");
        exit(EXIT_FAILURE);
    }

    DataValue* v1 = (DataValue*)pop(s);

    if(v1->type != DT_ES) {
        fprintf(stderr, "Error: Operand for exec is not an executable sequence\n");
        exit(EXIT_FAILURE);
    }

    Stack* es_stack = v1->data.es_stack;
    free(v1);

    es_stack->bottom->next = inst_stack->top;
    free(inst_stack);
    inst_stack = es_stack;
}

int evaluate(Stack* instruction_stack, int argc, int* argv) {
    Stack* implict_stack = create_stack();

    for(int i = 0 ; i < argc ; i++) {
        // 引数をスタックにプッシュ
        DataValue* arg_value = malloc(sizeof(DataValue));
        arg_value->type = DT_N;
        arg_value->data.num_value = argv[i];
        push(implict_stack, (void* )arg_value);
    }

    while(instruction_stack->size > 0) {
        // 命令スタックから命令をポップして評価
        ASNode* instruction = (ASNode*)pop(instruction_stack);
        
        switch(instruction->cmd) {
            case AS_N:
                // 数値はそのままスタックにプッシュ
                _push_num(implict_stack, instruction->data.num_value);
                break;
            case AS_ADD:
                add(implict_stack);
                break;
            case AS_SUB:
                sub(implict_stack);
                break;
            case AS_MUL:
                mul(implict_stack);
                break;
            case AS_DIV:
                _div(implict_stack);
                break;
            case AS_REM:
                rem(implict_stack);
                break;
            case AS_LT:
                lt(implict_stack);
                break;
            case AS_GT:
                gt(implict_stack);
                break;
            case AS_EQ:
                eq(implict_stack);
                break;
            case AS_POP:
                _pop(implict_stack);
                break;
            case AS_SWAP:
                swap(implict_stack);
                break;
            case AS_SEL:
                sel(implict_stack);
                break;
            case AS_NGET:
                nget(implict_stack);
                break;
            case AS_ES:
                fprintf(stderr, "Executable sequence should be executed with EXEC command\n");
                exit(EXIT_FAILURE);
            case AS_EXEC:
                exec(instruction_stack, implict_stack);
                break;
            default:
                fprintf(stderr, "Error: Unknown command %s\n", print_asnode(instruction->cmd));
                exit(EXIT_FAILURE);
        }
        free(instruction);
    }

    if(implict_stack->size != 1) {
        fprintf(stderr, "Error: Stack should have exactly one value after evaluation\n");
        exit(EXIT_FAILURE);
    }

    DataValue* result = (DataValue*)pop(implict_stack);
    if(result->type != DT_N) {
        fprintf(stderr, "Error: Result is not a number\n");
        exit(EXIT_FAILURE);
    }
    int n = result->data.num_value;
    free(result);
    free(implict_stack);
    return n;
}