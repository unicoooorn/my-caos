.globl process, A, B, R
// .globl main

process:
    mov A, %eax
    mov B, %edx

    sal $1, %eax
    jo overflow
    add A, %eax
    jo overflow

    sar $4, %edx
    jo overflow

    sub %edx, %eax
    jo overflow

    mov %eax, R

overflow:
    ret

// main:
//     call process
//     movl R, %eax
//     call writei32
//     call finish

.data
A: .int 0
B: .int 0
R: .int 0