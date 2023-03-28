.globl process, A, B, R
// .globl main

process:
    mov A, %eax
    mov B, %edx

    sar $4, %edx
    neg %edx
    add %eax, %edx
    jo overflow
    add %eax, %edx
    jo overflow
    add %eax, %edx
    jo overflow

    mov %edx, R

overflow:
    ret

/*

main:
    call process
    movl R, %eax
    call writei32
    call finish
*/

.data
A: .int -100
B: .int -100
R: .int 0