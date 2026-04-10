#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "lexer.h"
#include "evaluate.h"

int main(int argc, char* argv[]) {
    // 引数の確認
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // ファイルのオープン
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 字句解析
    Stack* tokens = lex(file);
    fclose(file);
    fprintf(stderr, "Lexed successfully. Number of tokens: %d\n", tokens->size);
    printf("Tokens:\n");
    print_tokens(tokens);
    puts("");

    // 構文解析
    ASD* asd = parse(tokens);
    fprintf(stderr, "Parsed successfully. Number of arguments: %d\n", asd->argc);
    printf("Abstract Syntax Tree:\n");
    print_asnodes(asd->as_stack);
    puts("");

    // 実行時引数がプログラムの指示に足りているか
    if(!(asd->argc <= argc - 2)) {
        fprintf(stderr, "Error: Not enough arguments provided for execution. Expected %d, got %d.\n", asd->argc, argc - 2);
        return 1;
    }
    // argが整数であることを検証
    int *args = (int*)malloc(sizeof(int) * asd->argc);
    for(int i = 0 ; i < asd->argc ; i++) {
        char* endptr;
        args[i] = strtol(argv[i + 2], &endptr, 10);
        if(*endptr != '\0') {
            fprintf(stderr, "Error: Argument %s is not a valid integer\n", argv[i + 2]);
            return 1;
        }
    }
    int res = evaluate(asd->as_stack, asd->argc, args);

    printf("Result: %d\n", res);
    return 0;
}