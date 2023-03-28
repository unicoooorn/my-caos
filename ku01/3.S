.global main

main:
    call readi64
    test $0x80000000, %edx
    jnz negative
    jz positive

positive:
    test $0xFFFFFFFF, %edx
    jnz maximum
    test $0x80000000, %eax
    jnz maximum
    jmp same

negative:
    cmp $0xFFFFFFFF, %edx
    jnz minimum
    test $0x80000000, %eax
    jz minimum
    jmp same



maximum:
    mov $2147483647, %eax
    // call writei32
    // call writei32
    call writei32
    call finish

    

same:
    call writei32
    // call writei32
    call finish





minimum:
    mov $-2147483648, %eax  // -2147483649
    call writei32
    call finish