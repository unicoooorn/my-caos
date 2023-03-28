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
    DIACRITIC_LEFT_BORDER = 0x0300,
    DIACRITIC_RIGHT_BORDER = 0x036F
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

int count_glyphs(const char* utf8_text) {
    int32_t codepoints_counter = 0, diacritic_counter = 0;
    int32_t k = 0;
    char cur;
    while ((cur = utf8_text[k]) != '\0') {
        codepoints_counter++;
        int cu_count = count_cu(cur);
        if (cu_count != 2) {
            for (int i = 1; i < cu_count; i++) {
                ++k;
            }
        } else {
            ++k;
            int32_t cur_unicoded = (utf8_text[k] & CU_MASK_SUFFIX_CONTINUATION) +
                                   ((CU_MASK_SUFFIX2_START & cur) << 6);
            if ((DIACRITIC_LEFT_BORDER <= cur_unicoded &&
                 cur_unicoded <= DIACRITIC_RIGHT_BORDER)) {
                diacritic_counter++;
            }
        }
        ++k;
    }
//    printf("%d %d\n", codepoints_counter, diacretic_counter);
    return codepoints_counter - diacritic_counter;
}

int main() {
    printf("%d\n", count_glyphs("H̸̡̪̯ͨ͊̽̅̾̎Ȩ̬̩̾͛ͪ̈́̀́͘ ̶̧̨̱̹̭̯ͧ̾ͬC̷̙̲̝͖ͭ̏ͥͮ͟Oͮ͏̮̪̝͍M̲̖͊̒ͪͩͬ̚̚͜Ȇ̴̟̟͙̞ͩ͌͝S̨̥̫͎̭ͯ̿̔̀ͅ"));
}