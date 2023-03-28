#include <stdio.h>

int main(void) {
    int cell_width, a, b;
    if (3 != scanf("%d %d %d", &a, &b, &cell_width)) {
        return 1;
    }
    printf("%*c", cell_width, ' ');
    printf(" ");
    for (int i = a; i < b; i++) {
        printf("%*d", cell_width, i);
        printf(" ");
    }
    printf("\n");
    for (long long int i = a; i < b; i++) {
        printf("%*lld", cell_width, i);
        printf(" ");
        for (long long int j = a; j < b; j++) {
            printf("%*lld", cell_width, i * j);
            printf(" ");
        }
        printf("\n");
    }
}