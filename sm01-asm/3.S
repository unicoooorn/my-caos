    .global main 
main:
    call readi32

    cmp $0, %eax
    jl zero


loop:
    call writei32
    sub $1, %eax
    cmp $0, %eax
    jge loop

zero:
    call finish