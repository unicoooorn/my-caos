.global main
.text

main:
    pushl %ebp
    movl %esp, %ebp


loop1:
    call getchar
    // проверка на большую букву
    cmpl $65, %eax
    jl not_cap1
    cmpl $90, %eax
    jg not_cap1
    add $32, %eax
    movl $first_count, %ecx
    incl (%ecx, %eax, 4)
    jmp loop1
not_cap1:
    cmpl $'\n', %eax
    jz loop2
    cmpl $32, %eax
    jz loop1
    movl $first_count, %ecx
    incl (%ecx, %eax, 4)
    jmp loop1

loop2:
    call getchar
    // проверка на большую букву
    cmpl $65, %eax
    jl not_cap2
    cmpl $90, %eax
    jg not_cap2
    add $32, %eax
    movl $second_count, %ecx
    incl (%ecx, %eax, 4)
    jmp loop2
not_cap2:
    cmpl $'\n', %eax
    jz check
    cmpl $32, %eax
    jz loop2
    movl $second_count, %ecx
    incl (%ecx, %eax, 4)
    jmp loop2


check:
    xor %ecx, %ecx
check_loop:
    movl $first_count, %edx
    movl (%edx, %ecx, 4), %eax 
    movl $second_count, %edx
    cmpl (%edx, %ecx, 4), %eax
    jnz isnt_anagram
    inc %ecx
    cmpl $128, %ecx
    jz is_anagram
    jmp check_loop


is_anagram:
    pushl $yes
    pushl $outformat
    call printf
    add $8, %esp
    jmp end

isnt_anagram:
    pushl $no
    pushl $outformat
    call printf
    add $8, %esp
    jmp end

end:
    movl %ebp, %esp
    pop %ebp
    xor %eax, %eax
    ret




.bss
first_count:  .skip 4 * 128
second_count: .skip 4 * 128

.data
outformat: .string "%s\n"
yes: .string "YES"
no: .string "NO"

