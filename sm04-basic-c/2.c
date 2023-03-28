#include <stdio.h>

int main(void) {
    enum { MAX_FIB_NEEDED = 100 };  // max - 218922995834555169026

    unsigned long long fib[MAX_FIB_NEEDED];
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i < MAX_FIB_NEEDED; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    long long cur;
    while (scanf("%llx", &cur) != EOF) {
        for (int i = 0; i < MAX_FIB_NEEDED; i++) {
            if (fib[i] > cur) {
                printf("%x ", i - 1);
                break;
            }
        }
    }
    printf("\n");
}