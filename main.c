#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "lexer.h"
#include "evaluate.h"

int main(int argc, char* argv[]) {
    // 引数の確認
    if (argc != 2) {
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

    // 構文解析
    ASD* asd = parse(tokens);


    // TODO: argが整数であることを検証
    evaluate(asd->as_stack, asd->argc, (int*)(argv + 1));

    return 0;
}