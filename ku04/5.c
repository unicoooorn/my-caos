//
// Created by Roman Gostilo on 11.03.2023.
//
#include <stdio.h>
/*
computation:
    movl 4(%esp), %ecx
    movl 8(%esp), %eax

    xorps %xmm0, %xmm0
    test %eax, %eax
    jz end

    movups (%ecx), %xmm0
    subl $4, %eax
    addl $16, %ecx
    test %eax, %eax
    jz end

loop:
    test %eax, %eax
    jz end
    movups (%ecx), %xmm1
    mulps %xmm1, %xmm0
    subl $4, %eax
    addl $16, %ecx
    jmp loop
end:
    movl 12(%esp), %eax
    haddps %xmm0, %xmm0
    haddps %xmm0, %xmm0
    movss %xmm0, (%eax)
    ret
 */

void computation(float *arr, int counter, float *ans) {
    float res[4] = {1, 1, 1, 1};
    float kek = 0;
    if (counter == 0) {
        *ans = kek;
        return;
    }
    while (counter > 0) {
        for (int i = 0; i < 4; i++) {
            res[i] *= arr[i];
        }
        arr += 4;
        counter -= 4;
    }
    kek = res[0] + res[1] + res[2] + res[3];
    *ans = kek;
    return;
}

int main() {
    float keks[] = {1, 2, 3, 4, 5, 6, 7, 8};
    float ans;
    computation(keks, 8, &ans);
    printf("%f\n", ans);
}