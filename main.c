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

    // TODO: argが整数であることを検証
    if(asd->argc > argc - 1) {
        fprintf(stderr, "Error: Not enough arguments provided for execution\n");
        return 1;
    }
    int res = evaluate(asd->as_stack, asd->argc, (int*)(argv + 1));

    printf("Result: %d\n", res);
    return 0;
}