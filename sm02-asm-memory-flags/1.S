    .global main
main:
    xor %ecx, %ecx

input:
    call readi32
    jc output
    push %eax
    inc %ecx
    jmp input


output:
    cmp $0, %ecx
    je end
    pop %eax
    call writei32
    dec %ecx
    jmp output
    
end:
    call finish