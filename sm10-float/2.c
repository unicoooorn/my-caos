//
// Created by Roman Gostilo on 04.03.2023.
//
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main() {
    enum {
        SIGN_MASK = 0b10000000000000000000000000000000,
        EXP_MASK = 0b01111111100000000000000000000000,
        MANTISSA_MASK = 0b00000000011111111111111111111111,
        SIGN_LEN = 1,
        EXP_LEN = 8,
        MANTISSA_LEN = 23,
        FLOAT_LEN = 64
    };

    union {
        float f;
        unsigned u;
    } uf;

    while (scanf("%f", &uf.f) != EOF) {
        unsigned sign = (bool)(SIGN_MASK & uf.u);
        unsigned exp = (EXP_MASK & uf.u) >> MANTISSA_LEN;
        unsigned mantissa = (MANTISSA_MASK & uf.u);
        printf("%u %u %x\n", sign, exp, mantissa);
    }
    return 0;
}
