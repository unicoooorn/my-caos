    .global main
main:
    call readi32
    mov %eax, %ebx  // ebx - num
    xor %eax, %eax  // eax - bit counter
    mov $32, %ecx   // ecx - loop counter
    mov $1, %esi

loop:
    test %ebx, %esi
    jz next
    add $1, %eax    // increments counter
next:
    shr $1, %ebx
    sub $1, %ecx
    cmp $0, %ecx
    jge loop


call writei32
call finish