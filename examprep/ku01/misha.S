.global process

process:
    // ebp = crt
    // esp |
    // stk arg
    // ebp
    push %ebp   
    // esp     |
    // stk arg crt
    // ebp
    mov %esp, %ebp
    // esp     |
    // stk arg crt
    // ebp     |
    push %ebp // == 1
    // esp         |
    // stk arg crt 1
    // ebp     |
    mov %esp, %ebp
    // esp         |
    // stk arg crt 1
    // ebp         |
    mov $4, %eax
    mov %ebp, %esp
    // esp         |
    // stk arg crt 1
    // ebp         |
    pop %ebp
    // esp     |
    // stk arg crt 1
    // ebp     |
    // ebp = 1
    ret