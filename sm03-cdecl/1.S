.global main
.text
main:
    push %ebp
    mov %esp, %ebp

    push %ebx
    xor %ebx, %ebx // ebx gonna be acc

loop:
    pushl $inp
    pushl $informat
    call scanf
    add $8, %esp
    cmpl $0, %eax   // checking for the end of the input
    jl input_done
    add inp, %ebx  // addition to acc
    jo overflow     // checking whether overflow took place or not
    jmp loop


input_done:
    pushl %ebx
    pushl $outformat
    jmp end



overflow:
    pushl $overflow_str
    pushl $outformat_str
    jmp end

end:
    call printf
    add $8, %esp
    movl $0, %eax
    pop %ebx
    mov %ebp, %esp
    pop %ebp
    ret


.data
inp: .int 0

.section .rodata
informat: .string "%d"
outformat: .string "%d\n"
outformat_str: .string "%s\n"
overflow_str: .string "Overflow"
