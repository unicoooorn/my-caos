#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void tinyconv(uint8_t bytes[], size_t size) {
    enum ByteConsts { BYTE_LEN = 8, MASK_FIRST_BIT = 0x01 };

    for (size_t index = 0; index < size; ++index) {
        uint8_t tiny_byte = 0;
        for (size_t i = 0; i < BYTE_LEN; ++i) {
            tiny_byte <<= 1;
            tiny_byte |= (bytes[index] & MASK_FIRST_BIT);
            bytes[index] >>= 1;
        }
        bytes[index] = tiny_byte;
    }
}
/*
void tinyconv(uint8_t bytes[], size_t size) {
    enum ByteRolling {
        BIT_LEN = 8,
        NEW_BYTE = 0x00,
        SHIFT = 1,
        MASK_S = 0x01,
        MASK_R = 0x80,
    };

    for (size_t index = 0; index < size; ++index) {
        uint8_t byte = NEW_BYTE;
        uint8_t mask_straight = MASK_S;
        uint8_t mask_reverse = MASK_R;

        for (size_t bit = 0; bit < BIT_LEN; ++bit) {
            if (bytes[index] & mask_straight) {
                byte |= mask_reverse;
            }
            mask_reverse >>= SHIFT;
            mask_straight <<= SHIFT;
        }

        bytes[index] = byte;
    }
}
*/
int main(void) {
    uint8_t b[] = {0xfa, 0x04};
    tinyconv(b, 2);
    for (size_t index = 0; index < 2; ++index) {
        printf("%x\n", b[index]);
    }
    return 0;
}