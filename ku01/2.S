.global call_process
.text

call_process:
    subl $800, %esp
    pushl %ebp
    pushl %ecx
    addl $808, %esp
    pop %ecx
    movl $ra, %ebp
    jmp process
ra:
    pushl %ecx
    subl $808, %esp
    popl %ecx
    popl %ebp
    addl $800, %esp
    ret

.data
.section .rodata
outformat: .string "%d\n"