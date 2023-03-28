.text
.global process
// .global main
.global A
.global B
.global R

// op src dst
// 5 * 3 - 4 / 16 = 

process:
// main:
    movl B, %ecx
    sar $4, %ecx
    neg %ecx
    jo end

    movl A, %eax
    addl %eax, %ecx
    jo end
    addl %eax, %ecx
    jo end
    addl %eax, %ecx
    jo end
    movl %ecx, R

end:
    // movl R, %eax
    // call writei32
    xorl %eax, %eax
    ret

.data
A:  .int 0
B:  .int 0
R:  .int 0