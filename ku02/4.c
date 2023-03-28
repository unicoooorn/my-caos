#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum MAXES { INT32_T_MAX = 2147483647, INT32_T_MIN = -2147483648 };

void please_compute_and_print_some_strange_values_from_some_other_strange_values(
    const char *val1, const char *val2) {
    char *ptr1, *ptr2;
    int lhs = strtol(val1, &ptr1, 13);
    int rhs = strtol(val2, &ptr2, 13);
    int result;
    if (__builtin_add_overflow(lhs, rhs, &result)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    if (rhs == 0 ||
        (rhs == -1 && (__builtin_mul_overflow(lhs, rhs, &result)))) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return;
}

int main() {
    please_compute_and_print_some_strange_values_from_some_other_strange_values(
        "25b47736b", "25b47736c");
}
