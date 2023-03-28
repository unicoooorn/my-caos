    .global main  
main:
    call readi32
    mov %eax, %ebx  // a

    call readi32
    mov %eax, %ecx  // b

    call readi32
    mov %eax, %edx   // c

    call readi32     // %eax = d

    call writei32
    mov %ebx, %eax

    add %ecx, %ecx  // 2 * b

    mov %edx, %esi
    sal $4, %esi
    add %edx, %esi

    sub %ecx, %eax
    add %esi, %eax


    call writei32
    call finish