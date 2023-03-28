#include <stdio.h>

int mystrcmp(const char *str1, const char *str2) {  // neg if <, pos if >
    const unsigned char *t_str1 = (const unsigned char *)str1;
    const unsigned char *t_str2 = (const unsigned char *)str2;
    while (*t_str1 != '\0' && *t_str2 != '\0') {
        if (*t_str1 == *t_str2) {
            t_str1++;
            t_str2++;
            continue;
        } else if (*t_str1 > *t_str2) {
            return 1;
        } else {
            return -1;
        }
    }
    return (*t_str1 == '\0' ? (*t_str2 == '\0' ? 0 : -1) : 1);
}

int main(void) {
    printf("%d\n", mystrcmp("bb", "b"));
}