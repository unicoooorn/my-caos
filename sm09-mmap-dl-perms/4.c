//
// Created by Roman Gostilo on 11.03.2023.
//
#include <dlfcn.h>
#include <gnu/lib-names.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    void *h = dlopen(LIBM_SO, RTLD_LAZY);
    double (*func)(double) = dlsym(h, argv[1]);
    double cur;
    while (scanf("%lf", &cur) == 1) {
        printf("%.10g\n", (*func)(cur));
    }
}
