.global process
process:
    push %ebx
    mov A, %eax
    mov B, %ebx
    mov $32, %ecx // counter
    xor %edx, %edx // res
loop:
    test $1, %ebx
    jz no_sum
sum:
    add %eax, %edx
no_sum:
    sal %eax
    dec %ecx
    sar %ebx
    cmp $0, %ecx
    jne loop
    mov %edx, R
    pop %ebx
    ret
    
/*
.global main
main:
    call process
    mov R, %eax
    call writei32
    call finish
*/

.data
.global A, B, R
    A : .int 2
    B : .int 2
    R : .int 0