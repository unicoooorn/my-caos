.global sort_by_abs, cmp
.text

cmp_my:
    pushl %ebp
    movl %esp, %ebp
    // prologue ends

    // 1st arg 0(ebp) - 1st elem ADDRESS
    // 2nd arg 4(ebp) - 2nd elem ADDRESS

    movl 8(%ebp), %eax
    movw (%eax), %cx
    

    movl 12(%ebp), %eax
    movw (%eax), %dx

    cmpw $0x8000, %cx
    jz cornercase

    cmpw $0x8000, %dx
    jz cornercase
    
    // убираем знак
    cmpw $0, %cx
    jge 1f
    negw %cx
1:
    cmpw $0, %dx
    jge 1f
    neg %dx
1:

    cmpw %cx, %dx
    jg second_is_bigger
    jl first_is_bigger
    jz equivalent

cornercase:
    cmpw %cx, %dx
    jz equivalent
    cmpw $0x8000, %cx
    jz first_is_bigger
    jnz first_is_bigger

equivalent:
    movl $0, %eax
    jmp end

first_is_bigger:
    movl $1, %eax
    jmp end

second_is_bigger:
    movl $0xFFFFFFFF, %eax
    jmp end

end:
    // epilogue starts
    mov %ebp, %esp
    pop %ebp
    ret


sort_by_abs:
    pushl %ebp
    movl %esp, %ebp
    // prologue ends
    // 1st arg 8(ebp) - array address
    // 2nd arg 12(ebp) - array.size()

    pushl $cmp_my
    pushl $2
    pushl 12(%ebp)
    pushl 8(%ebp)
    // qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
    call qsort
    add $16, %esp

    // epilogue starts
    mov %ebp, %esp
    pop %ebp
    ret



