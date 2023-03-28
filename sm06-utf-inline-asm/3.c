#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum CUMasksAndPrefixes {
    CU_MASK_PREFIX2_START = 0b11100000,
    CU_MASK_PREFIX3_START = 0b11110000,
    CU_MASK_PREFIX4_START = 0b11111000,
    CU_MASK_SUFFIX_CONTINUATION = 0b00111111,
    CU_MASK_SUFFIX2_START = 0b00011111,
    CU_PREFIX2_START = 0b11000000,
    CU_PREFIX3_START = 0b11100000,
    CU_PREFIX4_START = 0b11110000
};

enum UnicodeConstans {
    CYRILLIC_LEFT_BORDER = 0x0400,
    CYRILLIC_RIGHT_BORDER = 0x04FF
};

int16_t count_cu(char b) {
    if ((b & CU_MASK_PREFIX2_START) == CU_PREFIX2_START) {
        return 2;
    } else if ((b & CU_MASK_PREFIX3_START) == CU_PREFIX3_START) {
        return 3;
    } else if ((b & CU_MASK_PREFIX4_START) == CU_PREFIX4_START) {
        return 4;
    } else {
        return 1;
    }
}

int main() {
    int32_t codepoints_counter = 0, cyrillic_counter = 0;
    char cur = getchar();
    while (cur != EOF) {
        codepoints_counter++;
        int cu_count = count_cu(cur);
        if (cu_count != 2) {
            for (int i = 1; i < cu_count; i++) {
                getchar();
            }
        } else {
            int32_t cur_unicoded = (getchar() & CU_MASK_SUFFIX_CONTINUATION) +
                                   ((CU_MASK_SUFFIX2_START & cur) << 6);
            if ((CYRILLIC_LEFT_BORDER <= cur_unicoded &&
                 cur_unicoded <= CYRILLIC_RIGHT_BORDER)) {
                cyrillic_counter++;
            }
        }
        cur = getchar();
    }
    printf("%d %d\n", codepoints_counter, cyrillic_counter);
}