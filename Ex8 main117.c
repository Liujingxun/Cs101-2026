#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int (*fp)(int, int) = add;
    printf("fp = %p, add = %p\n", (void*)fp, (void*)add);
    printf("result = %d\n", fp(3, 4));
    return 0;
}
