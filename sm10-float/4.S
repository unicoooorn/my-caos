	.text
	.global okay
okay:
	pushl %ebp
	movl %esp, %ebp
    // prologue ends
	movsd 8(%ebp), %xmm0
	movsd 16(%ebp), %xmm1

    // x ^ 4
	mulsd %xmm0, %xmm0
	mulsd %xmm0, %xmm0
    // y ^ 4
	mulsd %xmm1, %xmm1
	mulsd %xmm1, %xmm1

    // z = x ^ 4 + y ^ 4
    xorpd %xmm2, %xmm2
	addsd %xmm0, %xmm2
    addsd %xmm1, %xmm2
    // res = sqrt(z)
	sqrtsd %xmm2, %xmm2

    // 
	movl 24(%ebp), %eax
	movsd %xmm2, (%eax) 
    // epilogue starts
	popl %ebp
	ret