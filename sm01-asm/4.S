    .global main

main:
    xor %ebx, %ebx // even sum
    xor %ecx, %ecx // odd sum
    mov $1, %edx // checker
loop:
    call readi32
    jc output
    test %eax, %edx
    jz even_inc
    add %eax, %ecx
    jmp loop
even_inc:
    add %eax, %ebx
    jmp loop

output:
    mov %ebx, %eax
    call writei32
    mov %ecx, %eax
    call writei32
    call finish