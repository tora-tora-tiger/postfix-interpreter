#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* stack;

typedef enum Command {
    N,
    ADD,
    SUB,
    MUL,
    DIV,
    REM,
    GT,
    LT,
    EQ,
    SEL,
    NGET,
    ES, // executable sequence
    EXEC
} Command;

typedef struct NumericalData {
    Command type;
    int value;
} NumericalData;

typedef struct ESData {
    Command type;
    Stack* es_stack;
} ESData;


int main(int argc, char *argv[]) {
    // 引数の確認
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // ファイルのオープン
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read 開始

    stack = create_stack();

    char buff[1<<8]; // 256バイトのバッファ
    char c;
    while (fscanf_s(file, "%255s", buff, (unsigned)_countof(buff)) != EOF) {
        // 文字を出力
        printf("%s\n", buff);
    }

    // ファイルを閉じる
    fclose(file);

    return 0;
}