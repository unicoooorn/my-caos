.globl main
main:
    call readi32
    mov %eax, %esi

    call readi32
    mov %eax, %edi

    mov $array, %ebx

    mov %ebx, %ecx

    read:
        call readi32
        jc part


        mov %eax, (%ebx)
        add $2, %ebx

        jmp read

    part:
        mov $array, %ebx
        call partition

        movl %edx, %eax
        call writei32
    
    loop:
      xor %eax, %eax
      movw (%ebx), %ax
      call writei32
      
      add $2, %ebx
      dec %esi
      jnz loop


    call finish

    .bss
array: .skip 20