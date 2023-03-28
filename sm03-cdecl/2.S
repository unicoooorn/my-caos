.global print_tb
.text
print_tb:
    pushl %ebp
    movl %esp, %ebp
    pushl %esi
    // prologue
    
    // printing "print_tb" - backtrace always starts in print_tb function
    pushl $print_tb_str
    call puts
    addl $4, %esp
    

    // backtracing
    xor %ecx, %ecx
    movl %ebp, %esi
find:
    // считываем return address

    movl 4(%esi), %edx
    movl (%esi), %esi

    // substracting from ra label addresses
    movl $0xFFFFFFFF, %eax
    movl %eax, dists
    movl %eax, dists + 4
    movl %eax, dists + 8

foo_sub:
    cmpl $foo, %edx
    jl bar_sub  // ra cannot be in foo
    movl %edx, dists
    movl $foo, %eax
    subl %eax, dists

bar_sub:
    cmpl $bar, %edx
    jl main_sub  // ra cannot be in bar
    movl %edx, dists + 4
    movl $bar, %eax
    subl %eax, dists + 4

main_sub:
    cmpl $main, %edx
    jl checking  // ra cannot be in main
    movl %edx, dists + 8
    movl $main, %eax
    subl %eax, dists + 8

checking:
    // dists - foo
    movl dists + 4, %eax // bar
    movl dists + 8, %edx // main

foo_check:
    cmpl %eax, dists
    ja bar_check
    cmpl %edx, dists
    ja bar_check
    jmp foo_found

bar_check:
    cmpl %edx, %eax
    ja main_check
    cmpl dists, %eax
    ja main_check
    jmp bar_found


main_check:
    jmp end

foo_found:
    pushl %ecx
    pushl $foo_str
    call puts
    add $4, %esp
    pop %ecx
    incl %ecx
    jmp find

bar_found:
    pushl %ecx
    pushl $bar_str
    call puts
    add $4, %esp
    pop %ecx
    incl %ecx
    jmp find


end:
    // backtrace always ends in main (if ends)
    pushl $main_str
    call puts
    addl $4, %esp
    xorl %eax, %eax // return 0
    // epilogue
    popl %esi
    movl %ebp, %esp
    popl %ebp
    ret


.data
dists: .skip 4*3 // foo bar main
.section .rodata
main_str: .string "main"
foo_str: .string "foo"
bar_str: .string "bar"
print_tb_str: .string "print_tb"