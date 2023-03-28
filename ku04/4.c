//
// Created by Roman Gostilo on 11.03.2023.
//
#include <stdbool.h>
#include <stdint.h>

typedef enum FPClass {
    FFP_ZERO,          // нули
    FFP_DENORMALIZED,  // числа в денормализованной форме
    FFP_NORMALIZED,  // числа в нормализованной форме
    FFP_INF,         // бесконечности
    FFP_NAN          // NaN-ы
} FPClass;

enum {
    SIGN_MASK = 0b10000000000000000000000000000000,
    EXP_MASK = 0b01111111100000000000000000000000,
    MANTISSA_MASK = 0b00000000011111111111111111111111
};

FPClass fpclassf(float value, int *psign) {

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

bool is_representable(uint32_t val) {
    enum { BITS_COUNT = 8, MANTISSA_LEN = 23, LAST_BIT_MASK = 0b1 };

    if (val == 0) {
        return true;
    }
    for (; !(LAST_BIT_MASK & val); val >>= 1) {
        ;
    }
    int8_t last_set_i = INT8_MAX;
    for (int i = 0; i < BITS_COUNT * sizeof(uint32_t); ++i) {
        if (LAST_BIT_MASK & val) {
            last_set_i = i;
        }
        val >>= 1;
    }
    return (last_set_i <= MANTISSA_LEN);
}

void sat_mul8(float *f) {
    union {
        float f;
        unsigned u;
    } uf;
    uf.f = *f;
    int *psign;
    //    Оставвить значение неизменным, если оно - бесконечность любого знака или NaN;
    if (fpclassf(*f, psign) == FFP_INF || fpclassf(*f, psign) == FFP_NAN) {
        return;
    }
    if (is_representable(uf.u)) {
        return ((EXP_MASK & uf.u) + 3) & EXP_MASK;
    }

//    Записать в *f значение 8 * (*f), если оно представимо в float;
//    Записать в *f максимальное по модулю конечное представимое число того же знака,
//    что f, в остальных случаях.

}