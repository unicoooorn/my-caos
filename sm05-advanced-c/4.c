#include <ctype.h>
#include <stdio.h>

int main(void) {
    unsigned long long char_summ = 0;
    int cur = getchar();
    while (cur != EOF) {
        if (isdigit(cur)) {
            char_summ += cur - '0';
        }
        cur = getchar();
    }
    printf("%lld\n", char_summ);
}