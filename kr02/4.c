#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum MAXES { INT32_T_MAX = 2147483647, INT32_T_MIN = -2147483648 };

void safe_int_add(int op1, int op2) {
    if (op1 >= 0) {
        if (op2 > INT_MAX - op1) {
            printf("1\n");
            return;
        }
    } else {
        if (op2 < INT_MIN - op1) {
            printf("1\n");
            return;
        }
    }
    printf("0\n");
    return;
}

void please_compute_and_print_some_strange_values_from_some_other_strange_values(
    const char *val1, const char *val2) {
    char *ptr1, *ptr2;
    int lhs = strtol(val1, &ptr1, 13);
    int rhs = strtol(val2, &ptr2, 13);
    safe_int_add(lhs, rhs);
    if (rhs == 0) {
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
