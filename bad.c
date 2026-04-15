#include <stdio.h>
#include <stdlib.h>

// ポインタが動かない例

void f(int *p) {
    int *q = (int*)malloc(sizeof(int));
    *q = 42;
    int *tmp = p;
    p = q;
    free(tmp);
}

int main() {
    int *p = (int*)malloc(sizeof(int));
    *p = 10;
    printf("%d\n", *p);
    f(p);
    printf("%d\n", *p);
    free(p);
}