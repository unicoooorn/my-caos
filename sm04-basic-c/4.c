#include <stdio.h>

void normalize_path(char *buf) {
    char *new_buf = buf;
    char prev_symb = *buf;  // previous symbol
    buf++;
    new_buf++;
    while (prev_symb != '\0' && *buf != '\0') {
        if (*buf == '/') {
            if (*buf != prev_symb) {
                *new_buf = *buf;
                new_buf++;
                prev_symb = *buf;
            }
            buf++;
        } else {
            *new_buf = *buf;
            new_buf++;
            prev_symb = *buf;
            buf++;
        }
    }
    if (prev_symb != '\0') {
        *new_buf = '\0';
    }
}

int main(void) {
    char buf[20] = "\0";
    normalize_path(buf);
    printf("%s\n", buf);
}