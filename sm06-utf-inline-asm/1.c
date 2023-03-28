#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int arg_count, char **argv) {
    for (int i = 1; i < arg_count; i++) {
        char *endptr;
        errno = 0;
        long res = strtol(argv[i], &endptr, 10);
        if (endptr != argv[i] && errno != ERANGE && *endptr == '\0') {
            if (res == (int8_t)res) {
                printf("1\n");
            } else if (res == (int16_t)res) {
                printf("2\n");
            } else if (res == (int32_t)res) {
                printf("4\n");
            } else {
                printf("-1\n");
            }
        } else {
            printf("-1\n");
        }
    }
}