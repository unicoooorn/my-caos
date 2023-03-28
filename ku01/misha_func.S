.globl process

process:
    push %ebp
    mov %esp, %ebp
    xor %eax, %eax
    addl 8(%ebp), %eax  // v1
    addl 16(%ebp), %eax // v2
    addl 20(%ebp), %eax // v3
    pop %ebp
    ret