#include "evaluate.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void add(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for add\n");
        exit(EXIT_FAILURE);
    }

    Value* v1 = (Value*)pop(s);
    Value* v2 = (Value*)pop(s);

    if(v1->type != N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != N) {
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

    Value* v1 = (Value*)pop(s);
    Value* v2 = (Value*)pop(s);

    if(v1->type != N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != N) {
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

    Value* v1 = (Value*)pop(s);
    Value* v2 = (Value*)pop(s);

    if(v1->type != N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != N) {
        fprintf(stderr, "Error: Second operand is not a number\n");
        exit(EXIT_FAILURE);
    }

    v1->data.num_value = v2->data.num_value * v1->data.num_value;
    free(v2);
    push(s, v1);
}

void div(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for div\n");
        exit(EXIT_FAILURE);
    }

    Value* v1 = (Value*)pop(s);
    Value* v2 = (Value*)pop(s);

    if(v1->type != N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != N) {
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

    Value* v1 = (Value*)pop(s);
    Value* v2 = (Value*)pop(s);

    if(v1->type != N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != N) {
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

    Value* v1 = (Value*)pop(s);
    Value* v2 = (Value*)pop(s);

    if(v1->type != N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != N) {
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

    Value* v1 = (Value*)pop(s);
    Value* v2 = (Value*)pop(s);

    if(v1->type != N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != N) {
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

    Value* v1 = (Value*)pop(s);
    Value* v2 = (Value*)pop(s);

    if(v1->type != N) {
        fprintf(stderr, "Error: First operand is not a number\n");
        exit(EXIT_FAILURE);
    }
    if(v2->type != N) {
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
    Value* v = pop(s);
    free(v); // ポップした値を解放
}

void swap(Stack* s) {
    if(s->size < 2) {
        fprintf(stderr, "Error: Not enough operands for swap\n");
        exit(EXIT_FAILURE);
    }

    Value* v1 = (Value*)pop(s);
    Value* v2 = (Value*)pop(s);

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

    Value* v1 = (Value*)pop(s);
    Value* v2 = (Value*)pop(s);
    Value* v3 = (Value*)pop(s);

    if(v3->type != N) {
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

    Value* v1 = (Value*)pop(s);

    if(v1->type != N) {
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

    if(((Value *)current->data)->type != N) {
        fprintf(stderr, "Error: nget target should be a number\n");
        exit(EXIT_FAILURE);
    }

    // copy
    Value* copy = malloc(sizeof(Value));
    memcpy(copy, current->data, sizeof(Value));

    push(s, copy);
}

void exec(Stack* s) {
    fprintf(stderr, "Error: EXEC not implemented yet\n");
    exit(EXIT_FAILURE);
}

int evaluate(Stack* instruction_stack, int argc, int* argv) {
    Stack* implict_stack = create_stack();

    for(int i = 0 ; i < argc ; i++) {
        // 引数をスタックにプッシュ
        Value* arg_value = malloc(sizeof(Value));
        arg_value->type = N;
        arg_value->data.num_value = argv[i];
        push(implict_stack, (void *)arg_value);
    }

    while(instruction_stack->size > 0) {
        // 命令スタックから命令をポップして評価
        Value* instruction = (Value*)pop(instruction_stack);
        
        int ret;
        switch(instruction->type) {
            case N:
                // 数値はそのままスタックにプッシュ
                push(implict_stack, instruction);
                break;
            case ADD:
                add(implict_stack);
                break;
            case SUB:
                sub(implict_stack);
                break;
            case MUL:
                mul(implict_stack);
                break;
            case DIV:
                div(implict_stack);
                break;
            case REM:
                rem(implict_stack);
                break;
            case LT:
                // LTの実装
                break;
            case GT:
                // GTの実装
                break;
            case EQ:
                // EQの実装
                break;
            case POP:
                _pop(implict_stack);
                break;
            case SWAP:
                swap(implict_stack);
                break;
            case SEL:
                sel(implict_stack);
                break;
            case NGET:
                nget(implict_stack);
                break;
            case ES:
                fprintf(stderr, "Executable sequence should be executed with EXEC command\n");
                exit(EXIT_FAILURE);
            case EXEC:
                exec(implict_stack);
                break;
        }
    }

    if(implict_stack->size != 1) {
        fprintf(stderr, "Error: Stack should have exactly one value after evaluation\n");
        exit(EXIT_FAILURE);
    }

    Value* result = (Value*)pop(implict_stack);
    if(result->type != N) {
        fprintf(stderr, "Error: Result is not a number\n");
        exit(EXIT_FAILURE);
    }
    int n = result->data.num_value;
    free(result);
    free(implict_stack);
    return n;
}