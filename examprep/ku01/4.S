.global my.args.forward

my.args.forward:
    push %ebp
    movl %esp, %ebp

    // v1 4(%ebp)
    // v2 8(%ebp) - upper
    // v2 12(%ebp)
    // v3 16(%ebp)
    pushl 16(%ebp)
    pushl 12(%ebp)
    pushl 8(%ebp)
    pushl 20(%ebp)
    call process    // v3 v1 v2
    addl $16, %esp
    neg %eax

    movl %ebp, %esp
    pop %ebp
    ret


.global main
main:
    push %ebp
        movl %esp, %ebp
    push $0
    push $0
    push $0
    push $228
    call my.args.forward
    addl $16, %esp

    pop %ebp
    ret    
