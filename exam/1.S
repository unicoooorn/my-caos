

sum13:
    pushl %ebp
    movl %esp, %ebp
    // prolog

    movl 8(%ebp), %eax

    

    // epilogue
    mov %ebp, %esp
    pop %ebp
    ret