.global main

main:
    call readi64
    test $0x80000000, %eax
    jnz eax_not_same
eax_alright:
    cmpl $0xFFFFFFFF, %edx
    jz minimum
    cmpl $0x00000000, %edx 
    jz same
    test $0x80000000, %edx
    jnz minimum
    test $0x80000000, %edx
    jz maximum
    

eax_not_same:
    test $0x80000000, %edx
    jnz minimum
    test $0x80000000, %edx
    jz maximum




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