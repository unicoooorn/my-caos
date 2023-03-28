.global call_process


call_process:
    movl %ebp, EBP
    pop RETURN
    movl $kek, %ebp
    jmp process
kek:
    // esp |
    // stk arg crt 1
    // ebp |
    // ebp = 1
    movl EBP, %ebp
    // ebp = prev
    push RETURN
    // esp     |
    // stk arg ret 1
    // ebp     |
    ret


.data
EBP: .int 0
RETURN: .int 0

.text

.global main
main:
    call call_process
    ret