#include <stdio.h>

int main(void) {
    enum { INCORRECT_IO = 1 };

    unsigned int a, b;
    if (scanf("%u %u", &a, &b) != 2) {
        return INCORRECT_IO;
    }
    if (printf("%u\n", a / 2 + b / 2 + (a % 2 + b % 2) / 2) < 0) {
        return INCORRECT_IO;
    }

    return 0;
}
