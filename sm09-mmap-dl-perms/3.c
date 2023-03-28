//
// Created by Roman Gostilo on 11.03.2023.
//
#include <stdint.h>

int main() {



    int32_t i_start = 0;
    int32_t i_finish = 0;
    int32_t j_start = 0;
    int32_t j_finish = 0;
    int32_t current = 1;
    int32_t i = 0;
    int32_t j = 0;

    while (current <= row * col) {
        *(array + (col * i) + j) = current;

        if (i == i_start && j < col - j_finish - 1) {
            ++j;
        } else if (j == col - j_finish - 1 && i < row - i_finish - 1) {
            ++i;
        } else if (i == row - i_finish - 1 && j > j_start) {
            --j;
        } else {
            --i;
        }

        if ((i == i_start + 1) && (j == j_start) &&
            (j_start != col - j_finish - 1)) {
            ++i_start;
            ++i_finish;
            ++j_start;
            ++j_finish;
        }

        ++current;
    }
}