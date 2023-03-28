.global my.args.forward
// .global main

my.args.forward:    // v1 v2 v3 
    pushl %ebp
    movl %esp, %ebp

    pushl 16(%ebp) // v2
    pushl 12(%ebp) // v2
    pushl 8(%ebp) // v1
    pushl 20(%ebp) // v3
    
    call process    // v3 v1 v2
    addl $16, %esp
    neg %eax

    movl %ebp, %esp
    pop %ebp
    ret

/*
main:
    pushl $1    // v3
    pushl $1    // v2
    pushl $0    // v2
    pushl $1    // v1 
    
    call my.args.forward
    addl $16, %esp
    ret 
*/
