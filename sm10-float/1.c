//
// Created by Roman Gostilo on 04.03.2023.
//
#include <math.h>
#include <stdio.h>

typedef enum FPClass {
    FFP_ZERO,          // нули
    FFP_DENORMALIZED,  // числа в денормализованной форме
    FFP_NORMALIZED,  // числа в нормализованной форме
    FFP_INF,         // бесконечности
    FFP_NAN          // NaN-ы
} FPClass;

#include <stdbool.h>

FPClass fpclassf(float value, int *psign) {
    enum {
        SIGN_MASK = 0b10000000000000000000000000000000,
        EXP_MASK = 0b01111111100000000000000000000000,
        MANTISSA_MASK = 0b00000000011111111111111111111111
    };

    union {
        float f;
        unsigned u;
    } uf;

    uf.f = value;
    if ((uf.u & EXP_MASK) == EXP_MASK && (uf.u & MANTISSA_MASK)) {
        *psign = 0;
        return FFP_NAN;
    }
    if ((uf.u & EXP_MASK) == EXP_MASK && !(uf.u & MANTISSA_MASK)) {
        *psign = (bool)(uf.u & SIGN_MASK);
        return FFP_INF;
    }
    if (!(uf.u & EXP_MASK) && !(uf.u & MANTISSA_MASK)) {
        *psign = (bool)(uf.u & SIGN_MASK);
        return FFP_ZERO;
    }
    if (!(uf.u & EXP_MASK)) {
        *psign = (bool)(uf.u & SIGN_MASK);
        return FFP_DENORMALIZED;
    }
    *psign = (bool)(uf.u & SIGN_MASK);
    return FFP_NORMALIZED;
}

int main() {
    int sign = 0;
    float f = -0.0;
    printf("%d\n", fpclassf(f, &sign));
    printf("%d\n", sign);
}
