.global main

main:
    pushl %ebp
    movl %esp, %ebp
    // prologue ends


    movl $array, %edx
    xor %esi, %esi
loop1:
    call readi32
    movl %eax, (%edx, %esi, 4)
    inc %esi
    cmpl $5, %esi
    jnz loop1

    pushl $5
    pushl $array
    call sort_by_abs

    movl $array, %edx
    xor %esi, %esi
loop:
    movl (%edx, %esi, 4), %eax
    call writei32
    inc %esi
    cmpl $5, %esi
    jnz loop
    
    // epilogue starts
    mov %ebp, %esp
    pop %ebp
    call finish
    




.data
array: .skip 4 * 5
format: .string "%d "