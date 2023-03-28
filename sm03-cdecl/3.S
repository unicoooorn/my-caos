.global main
.text
main:
    pushl %ebp
    movl %esp, %ebp
    // prolog
    pushl $ra
    // misha's prolog
    pushl %ebp
    movl %esp, %ebp
    jmp process

ra:
    pushl %eax
    pushl $outformat
    call printf
    add $8, %esp
    movl $0, %eax
    

    // epilogue
    mov %ebp, %esp
    pop %ebp
    ret

.section .rodata
outformat: .string "%d\n"