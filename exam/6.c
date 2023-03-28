//
// Created by Roman Gostilo on 25.03.2023.
//
#include <setjmp.h>

// Функция вычисляет значение многочлена (A * x + B) * x + C в точке x

/*
bool __builtin_add_overflow (type1 a, type2 b, type3 *res);
bool __builtin_sub_overflow (type1 a, type2 b, type3 *res);
bool __builtin_mul_overflow (type1 a, type2 b, type3 *res);
 */

int eval_poly(int A, int B, int C, int x, jmp_buf overflow) {
    int Ax;
    if (__builtin_mul_overflow(A, x, &Ax)) {
        longjmp(overflow, 0);
    }
    int first_p;
    if (__builtin_add_overflow(Ax, B, &first_p)) {
        longjmp(overflow, 0);
    }
    int almost;
    if (__builtin_mul_overflow(first_p, x, &almost)) {
        longjmp(overflow, 0);
    }
    int final;
    if (__builtin_add_overflow(almost, C, &final)) {
        longjmp(overflow, 0);
    }
    return final;
}

int main() {

}