//
// Created by Roman Gostilo on 04.03.2023.
//
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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

int main() {
    uint32_t u;
    while (scanf("%u", &u) != EOF) {
        printf("%d\n", is_representable(u));
    }
}
